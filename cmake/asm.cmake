if (WITH_ASM AND NOT KITTENPAW_ARM AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(KITTENPAW_ASM_LIBRARY "kittenpaw-asm")

    if (CMAKE_C_COMPILER_ID MATCHES MSVC)
        enable_language(ASM_MASM)

        if (MSVC_TOOLSET_VERSION GREATER_EQUAL 141)
            set(KITTENPAW_ASM_FILES
                "src/crypto/cn/asm/cn_main_loop.asm"
                "src/crypto/cn/asm/CryptonightR_template.asm"
            )
        else()
            set(KITTENPAW_ASM_FILES
                "src/crypto/cn/asm/win64/cn_main_loop.asm"
                "src/crypto/cn/asm/win64/CryptonightR_template.asm"
            )
        endif()

        set_property(SOURCE ${KITTENPAW_ASM_FILES} PROPERTY ASM_MASM)
    else()
        enable_language(ASM)

        if (WIN32 AND CMAKE_C_COMPILER_ID MATCHES GNU)
            set(KITTENPAW_ASM_FILES
                "src/crypto/cn/asm/win64/cn_main_loop.S"
                "src/crypto/cn/asm/CryptonightR_template.S"
            )
        else()
            set(KITTENPAW_ASM_FILES
                "src/crypto/cn/asm/cn_main_loop.S"
                "src/crypto/cn/asm/CryptonightR_template.S"
            )
        endif()

        set_property(SOURCE ${KITTENPAW_ASM_FILES} PROPERTY C)
    endif()

    add_library(${KITTENPAW_ASM_LIBRARY} STATIC ${KITTENPAW_ASM_FILES})
    set(KITTENPAW_ASM_SOURCES
        src/crypto/common/Assembly.h
        src/crypto/common/Assembly.cpp
        src/crypto/cn/r/CryptonightR_gen.cpp
        )
    set_property(TARGET ${KITTENPAW_ASM_LIBRARY} PROPERTY LINKER_LANGUAGE C)

    add_definitions(/DKITTENPAW_FEATURE_ASM)
else()
    set(KITTENPAW_ASM_SOURCES "")
    set(KITTENPAW_ASM_LIBRARY "")

    remove_definitions(/DKITTENPAW_FEATURE_ASM)
endif()
