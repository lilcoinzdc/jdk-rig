# XMRig

[![Github All Releases](https://img.shields.io/github/downloads/jdkrig/jdkrig/total.svg)](https://github.com/jdkrig/jdkrig/releases)
[![GitHub release](https://img.shields.io/github/release/jdkrig/jdkrig/all.svg)](https://github.com/jdkrig/jdkrig/releases)
[![GitHub Release Date](https://img.shields.io/github/release-date/jdkrig/jdkrig.svg)](https://github.com/jdkrig/jdkrig/releases)
[![GitHub license](https://img.shields.io/github/license/jdkrig/jdkrig.svg)](https://github.com/jdkrig/jdkrig/blob/master/LICENSE)
[![GitHub stars](https://img.shields.io/github/stars/jdkrig/jdkrig.svg)](https://github.com/jdkrig/jdkrig/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/jdkrig/jdkrig.svg)](https://github.com/jdkrig/jdkrig/network)

XMRig is a high performance, open source, cross platform RandomX, KawPow, CryptoNight and [GhostRider](https://github.com/jdkrig/jdkrig/tree/master/src/crypto/ghostrider#readme) unified CPU/GPU jdkrigger and [RandomX benchmark](https://jdkrig.com/benchmark). Official binaries are available for Windows, Linux, macOS and FreeBSD.

## Mining backends
- **CPU** (x86/x64/ARMv7/ARMv8)
- **OpenCL** for AMD GPUs.
- **CUDA** for NVIDIA GPUs via external [CUDA plugin](https://github.com/jdkrig/jdkrig-cuda).

## Download
* **[Binary releases](https://github.com/jdkrig/jdkrig/releases)**
* **[Build from source](https://jdkrig.com/docs/jdkrigger/build)**

## Usage
The preferred way to configure the jdkrigger is the [JSON config file](https://jdkrig.com/docs/jdkrigger/config) as it is more flexible and human friendly. The [command line interface](https://jdkrig.com/docs/jdkrigger/command-line-options) does not cover all features, such as jdkrigging profiles for different algorithms. Important options can be changed during runtime without jdkrigger restart by editing the config file or executing [API](https://jdkrig.com/docs/jdkrigger/api) calls.

* **[Wizard](https://jdkrig.com/wizard)** helps you create initial configuration for the jdkrigger.
* **[Workers](http://workers.jdkrig.info)** helps manage your jdkriggers via HTTP API.

## Donations
* Default donation 1% (1 minute in 100 minutes) can be increased via option `donate-level` or disabled in source code.
* XMR: `48edfHu7V9Z84YzzMa6fUueoELZ9ZRXq9VetWzYGzKt52XU5xvqgzYnDK9URnRoJMk1j8nLwEVsaSWJ4fhdUyZijBGUicoD`

## Developers
* **[jdkrig](https://github.com/jdkrig)**
* **[sech1](https://github.com/SChernykh)**

## Contacts
* support@jdkrig.com
* [reddit](https://www.reddit.com/user/XMRig/)
* [twitter](https://twitter.com/jdkrig_dev)
