/* XMRig
 * Copyright 2010      Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2012-2014 pooler      <pooler@litecoinpool.org>
 * Copyright 2014      Lucas Jones <https://github.com/lucasjones>
 * Copyright 2014-2016 Wolf9466    <https://github.com/OhGodAPet>
 * Copyright 2016      Jay D Dee   <jayddee246@gmail.com>
 * Copyright 2017-2018 XMR-Stak    <https://github.com/fireice-uk>, <https://github.com/psychocrypt>
 * Copyright 2018      Lee Clagett <https://github.com/vtnerd>
 * Copyright 2019      Howard Chu  <https://github.com/hyc>
 * Copyright 2018-2024 SChernykh   <https://github.com/SChernykh>
 * Copyright 2016-2024 XMRig       <https://github.com/jdkrig>, <support@jdkrig.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <cassert>
#include <cstring>

#include "base/net/stratum/Job.h"
#include "base/tools/Alignment.h"
#include "base/tools/Buffer.h"
#include "base/tools/Cvt.h"
#include "base/tools/cryptonote/BlockTemplate.h"
#include "base/tools/cryptonote/Signatures.h"
#include "base/crypto/keccak.h"


jdkrig::Job::Job(bool nicehash, const Algorithm &algorithm, const String &clientId) :
    m_algorithm(algorithm),
    m_nicehash(nicehash),
    m_clientId(clientId)
{
}


bool jdkrig::Job::isEqual(const Job &other) const
{
    return m_id == other.m_id && m_clientId == other.m_clientId && isEqualBlob(other) && m_target == other.m_target;
}


bool jdkrig::Job::isEqualBlob(const Job &other) const
{
    return (m_size == other.m_size) && (memcmp(m_blob, other.m_blob, m_size) == 0);
}


bool jdkrig::Job::setBlob(const char *blob)
{
    if (!blob) {
        return false;
    }

    size_t size = strlen(blob);
    if (size % 2 != 0) {
        return false;
    }

    size /= 2;

    const size_t minSize = nonceOffset() + nonceSize();
    if (size < minSize || size >= sizeof(m_blob)) {
        return false;
    }

    if (!Cvt::fromHex(m_blob, sizeof(m_blob), blob, size * 2)) {
        return false;
    }

    if (readUnaligned(nonce()) != 0 && !m_nicehash) {
        m_nicehash = true;
    }

#   ifdef JDKRIG_PROXY_PROJECT
    memset(m_rawBlob, 0, sizeof(m_rawBlob));
    memcpy(m_rawBlob, blob, size * 2);
#   endif

    m_size = size;
    return true;
}


bool jdkrig::Job::setSeedHash(const char *hash)
{
    if (!hash || (strlen(hash) != kMaxSeedSize * 2)) {
        return false;
    }

#   ifdef JDKRIG_PROXY_PROJECT
    m_rawSeedHash = hash;
#   endif

    m_seed = Cvt::fromHex(hash, kMaxSeedSize * 2);

    return !m_seed.empty();
}


bool jdkrig::Job::setTarget(const char *target)
{
    static auto parse = [](const char *target, size_t size, const Algorithm &algorithm) -> uint64_t {
        if (algorithm == Algorithm::RX_YADA) {
            return strtoull(target, nullptr, 16);
        }

        const auto raw = Cvt::fromHex(target, size);

        switch (raw.size()) {
        case 4:
            return 0xFFFFFFFFFFFFFFFFULL / (0xFFFFFFFFULL / uint64_t(*reinterpret_cast<const uint32_t *>(raw.data())));

        case 8:
            return *reinterpret_cast<const uint64_t *>(raw.data());

        default:
            break;
        }

        return 0;
    };

    const size_t size = target ? strlen(target) : 0;

    if (size < 4 || (m_target = parse(target, size, algorithm())) == 0) {
        return false;
    }

    m_diff = toDiff(m_target);

#   ifdef JDKRIG_PROXY_PROJECT
    if (size >= sizeof(m_rawTarget)) {
        return false;
    }

    memset(m_rawTarget, 0, sizeof(m_rawTarget));
    memcpy(m_rawTarget, target, size);
#   endif

    return true;
}


size_t jdkrig::Job::nonceOffset() const
{
    switch (algorithm().family()) {
    case Algorithm::KAWPOW:
        return 32;

    case Algorithm::GHOSTRIDER:
        return 76;

    default:
        break;
    }

    if (algorithm() == Algorithm::RX_YADA) {
        return 147;
    }

    return 39;
}


void jdkrig::Job::setDiff(uint64_t diff)
{
    m_diff   = diff;
    m_target = toDiff(diff);

#   ifdef JDKRIG_PROXY_PROJECT
    Cvt::toHex(m_rawTarget, sizeof(m_rawTarget), reinterpret_cast<uint8_t *>(&m_target), sizeof(m_target));
#   endif
}


void jdkrig::Job::setSigKey(const char *sig_key)
{
    constexpr const size_t size = 64;

    if (!sig_key || strlen(sig_key) != size * 2) {
        return;
    }

#   ifndef JDKRIG_PROXY_PROJECT
    const auto buf = Cvt::fromHex(sig_key, size * 2);
    if (buf.size() == size) {
        setEphemeralKeys(buf.data(), buf.data() + 32);
    }
#   else
    m_rawSigKey = sig_key;
#   endif
}


uint32_t jdkrig::Job::getNumTransactions() const
{
    if (!(m_algorithm.isCN() || m_algorithm.family() == Algorithm::RANDOM_X)) {
        return 0;
    }

    uint32_t num_transactions = 0;

    // Monero (and some other coins) has the number of transactions encoded as varint in the end of hashing blob
    const size_t expected_tx_offset = (m_algorithm == Algorithm::RX_WOW) ? 141 : 75;

    if ((m_size > expected_tx_offset) && (m_size <= expected_tx_offset + 4)) {
        for (size_t i = expected_tx_offset, k = 0; i < m_size; ++i, k += 7) {
            const uint8_t b = m_blob[i];
            num_transactions |= static_cast<uint32_t>(b & 0x7F) << k;
            if ((b & 0x80) == 0) {
                break;
            }
        }
    }

    return num_transactions;
}


void jdkrig::Job::copy(const Job &other)
{
    m_algorithm  = other.m_algorithm;
    m_nicehash   = other.m_nicehash;
    m_size       = other.m_size;
    m_clientId   = other.m_clientId;
    m_id         = other.m_id;
    m_backend    = other.m_backend;
    m_diff       = other.m_diff;
    m_height     = other.m_height;
    m_target     = other.m_target;
    m_index      = other.m_index;
    m_seed       = other.m_seed;
    m_extraNonce = other.m_extraNonce;
    m_poolWallet = other.m_poolWallet;

    memcpy(m_blob, other.m_blob, sizeof(m_blob));

#   ifdef JDKRIG_PROXY_PROJECT
    m_rawSeedHash = other.m_rawSeedHash;
    m_rawSigKey   = other.m_rawSigKey;

    memcpy(m_rawBlob, other.m_rawBlob, sizeof(m_rawBlob));
    memcpy(m_rawTarget, other.m_rawTarget, sizeof(m_rawTarget));
#   endif

#   ifdef JDKRIG_FEATURE_BENCHMARK
    m_benchSize = other.m_benchSize;
#   endif

#   ifdef JDKRIG_PROXY_PROJECT
    memcpy(m_spendSecretKey, other.m_spendSecretKey, sizeof(m_spendSecretKey));
    memcpy(m_viewSecretKey, other.m_viewSecretKey, sizeof(m_viewSecretKey));
    memcpy(m_spendPublicKey, other.m_spendPublicKey, sizeof(m_spendPublicKey));
    memcpy(m_viewPublicKey, other.m_viewPublicKey, sizeof(m_viewPublicKey));
    m_jdkriggerTxPrefix = other.m_jdkriggerTxPrefix;
    m_jdkriggerTxEphPubKeyOffset = other.m_jdkriggerTxEphPubKeyOffset;
    m_jdkriggerTxPubKeyOffset = other.m_jdkriggerTxPubKeyOffset;
    m_jdkriggerTxExtraNonceOffset = other.m_jdkriggerTxExtraNonceOffset;
    m_jdkriggerTxExtraNonceSize = other.m_jdkriggerTxExtraNonceSize;
    m_jdkriggerTxMerkleTreeBranch = other.m_jdkriggerTxMerkleTreeBranch;
    m_hasViewTag = other.m_hasViewTag;
#   else
    memcpy(m_ephPublicKey, other.m_ephPublicKey, sizeof(m_ephPublicKey));
    memcpy(m_ephSecretKey, other.m_ephSecretKey, sizeof(m_ephSecretKey));
#   endif

    m_hasJdkriggerSignature = other.m_hasJdkriggerSignature;
}


void jdkrig::Job::move(Job &&other)
{
    m_algorithm  = other.m_algorithm;
    m_nicehash   = other.m_nicehash;
    m_size       = other.m_size;
    m_clientId   = std::move(other.m_clientId);
    m_id         = std::move(other.m_id);
    m_backend    = other.m_backend;
    m_diff       = other.m_diff;
    m_height     = other.m_height;
    m_target     = other.m_target;
    m_index      = other.m_index;
    m_seed       = std::move(other.m_seed);
    m_extraNonce = std::move(other.m_extraNonce);
    m_poolWallet = std::move(other.m_poolWallet);

    memcpy(m_blob, other.m_blob, sizeof(m_blob));

    other.m_size        = 0;
    other.m_diff        = 0;
    other.m_algorithm   = Algorithm::INVALID;

#   ifdef JDKRIG_PROXY_PROJECT
    m_rawSeedHash = std::move(other.m_rawSeedHash);
    m_rawSigKey   = std::move(other.m_rawSigKey);

    memcpy(m_rawBlob, other.m_rawBlob, sizeof(m_rawBlob));
    memcpy(m_rawTarget, other.m_rawTarget, sizeof(m_rawTarget));
#   endif

#   ifdef JDKRIG_FEATURE_BENCHMARK
    m_benchSize = other.m_benchSize;
#   endif

#   ifdef JDKRIG_PROXY_PROJECT
    memcpy(m_spendSecretKey, other.m_spendSecretKey, sizeof(m_spendSecretKey));
    memcpy(m_viewSecretKey, other.m_viewSecretKey, sizeof(m_viewSecretKey));
    memcpy(m_spendPublicKey, other.m_spendPublicKey, sizeof(m_spendPublicKey));
    memcpy(m_viewPublicKey, other.m_viewPublicKey, sizeof(m_viewPublicKey));

    m_jdkriggerTxPrefix             = std::move(other.m_jdkriggerTxPrefix);
    m_jdkriggerTxEphPubKeyOffset    = other.m_jdkriggerTxEphPubKeyOffset;
    m_jdkriggerTxPubKeyOffset       = other.m_jdkriggerTxPubKeyOffset;
    m_jdkriggerTxExtraNonceOffset   = other.m_jdkriggerTxExtraNonceOffset;
    m_jdkriggerTxExtraNonceSize     = other.m_jdkriggerTxExtraNonceSize;
    m_jdkriggerTxMerkleTreeBranch   = std::move(other.m_jdkriggerTxMerkleTreeBranch);
    m_hasViewTag                = other.m_hasViewTag;
#   else
    memcpy(m_ephPublicKey, other.m_ephPublicKey, sizeof(m_ephPublicKey));
    memcpy(m_ephSecretKey, other.m_ephSecretKey, sizeof(m_ephSecretKey));
#   endif

    m_hasJdkriggerSignature = other.m_hasJdkriggerSignature;
}


#ifdef JDKRIG_PROXY_PROJECT


void jdkrig::Job::setSpendSecretKey(const uint8_t *key)
{
    m_hasJdkriggerSignature = true;
    memcpy(m_spendSecretKey, key, sizeof(m_spendSecretKey));

    derive_view_secret_key(m_spendSecretKey, m_viewSecretKey);
    secret_key_to_public_key(m_spendSecretKey, m_spendPublicKey);
    secret_key_to_public_key(m_viewSecretKey, m_viewPublicKey);
}


void jdkrig::Job::setJdkriggerTx(const uint8_t *begin, const uint8_t *end, size_t jdkriggerTxEphPubKeyOffset, size_t jdkriggerTxPubKeyOffset, size_t jdkriggerTxExtraNonceOffset, size_t jdkriggerTxExtraNonceSize, const Buffer &jdkriggerTxMerkleTreeBranch, bool hasViewTag)
{
    m_jdkriggerTxPrefix.assign(begin, end);
    m_jdkriggerTxEphPubKeyOffset    = jdkriggerTxEphPubKeyOffset;
    m_jdkriggerTxPubKeyOffset       = jdkriggerTxPubKeyOffset;
    m_jdkriggerTxExtraNonceOffset   = jdkriggerTxExtraNonceOffset;
    m_jdkriggerTxExtraNonceSize     = jdkriggerTxExtraNonceSize;
    m_jdkriggerTxMerkleTreeBranch   = jdkriggerTxMerkleTreeBranch;
    m_hasViewTag                = hasViewTag;
}


void jdkrig::Job::setViewTagInJdkriggerTx(uint8_t view_tag)
{
    memcpy(m_jdkriggerTxPrefix.data() + m_jdkriggerTxEphPubKeyOffset + 32, &view_tag, 1);
}


void jdkrig::Job::setExtraNonceInJdkriggerTx(uint32_t extra_nonce)
{
    memcpy(m_jdkriggerTxPrefix.data() + m_jdkriggerTxExtraNonceOffset, &extra_nonce, std::min(m_jdkriggerTxExtraNonceSize, sizeof(uint32_t)));
}


void jdkrig::Job::generateSignatureData(String &signatureData, uint8_t& view_tag) const
{
    uint8_t* eph_public_key = m_jdkriggerTxPrefix.data() + m_jdkriggerTxEphPubKeyOffset;
    uint8_t* txkey_pub = m_jdkriggerTxPrefix.data() + m_jdkriggerTxPubKeyOffset;

    uint8_t txkey_sec[32];

    generate_keys(txkey_pub, txkey_sec);

    uint8_t derivation[32];

    generate_key_derivation(m_viewPublicKey, txkey_sec, derivation, &view_tag);
    derive_public_key(derivation, 0, m_spendPublicKey, eph_public_key);

    uint8_t buf[32 * 3] = {};
    memcpy(buf, txkey_pub, 32);
    memcpy(buf + 32, eph_public_key, 32);

    generate_key_derivation(txkey_pub, m_viewSecretKey, derivation, nullptr);
    derive_secret_key(derivation, 0, m_spendSecretKey, buf + 64);

    signatureData = Cvt::toHex(buf, sizeof(buf));
}

void jdkrig::Job::generateHashingBlob(String &blob) const
{
    uint8_t root_hash[32];
    const uint8_t* p = m_jdkriggerTxPrefix.data();
    BlockTemplate::calculateRootHash(p, p + m_jdkriggerTxPrefix.size(), m_jdkriggerTxMerkleTreeBranch, root_hash);

    uint64_t root_hash_offset = nonceOffset() + nonceSize();

    if (m_hasJdkriggerSignature) {
        root_hash_offset += BlockTemplate::kSignatureSize + 2 /* vote */;
    }

    blob = rawBlob();
    Cvt::toHex(blob.data() + root_hash_offset * 2, 64, root_hash, BlockTemplate::kHashSize);
}


#else


void jdkrig::Job::generateJdkriggerSignature(const uint8_t* blob, size_t size, uint8_t* out_sig) const
{
    uint8_t tmp[kMaxBlobSize];
    memcpy(tmp, blob, size);

    // Fill signature with zeros
    memset(tmp + nonceOffset() + nonceSize(), 0, BlockTemplate::kSignatureSize);

    uint8_t prefix_hash[32];
    jdkrig::keccak(tmp, static_cast<int>(size), prefix_hash, sizeof(prefix_hash));
    jdkrig::generate_signature(prefix_hash, m_ephPublicKey, m_ephSecretKey, out_sig);
}


#endif
