/*
Copyright (c) 2018-2020, tevador    <tevador@gmail.com>
Copyright (c) 2019-2020, SChernykh  <https://github.com/SChernykh>
Copyright (c) 2019-2020, KITTENpaw      <https://github.com/kittenpaw>, <support@kittenpaw.com>

All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	  notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	  notice, this list of conditions and the following disclaimer in the
	  documentation and/or other materials provided with the distribution.
	* Neither the name of the copyright holder nor the
	  names of its contributors may be used to endorse or promote products
	  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "crypto/randomx/vm_compiled_light.hpp"
#include "crypto/randomx/common.hpp"
#include <stdexcept>

namespace randomx {

	template<int softAes>
	void CompiledLightVm<softAes>::setCache(randomx_cache* cache) {
		cachePtr = cache;
		mem.memory = cache->memory;

#		ifdef KITTENPAW_SECURE_JIT
		compiler.enableWriting();
#		endif

		compiler.generateSuperscalarHash(cache->programs);
	}

	template<int softAes>
	void CompiledLightVm<softAes>::run(void* seed) {
		VmBase<softAes>::generateProgram(seed);
		randomx_vm::initialize();

#		ifdef KITTENPAW_SECURE_JIT
		compiler.enableWriting();
#		endif

		compiler.generateProgramLight(program, config, datasetOffset);

		CompiledVm<softAes>::execute();
	}

	template class CompiledLightVm<false>;
	template class CompiledLightVm<true>;
}
