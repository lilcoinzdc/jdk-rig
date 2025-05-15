if (WITH_ASM AND NOT JDKRIG_ARM AND CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(JDKRIG_ASM_LIBRARY "jdkrig-asm")

    if (CMAKE_C_COMPILER_ID MATCHES MSVC)
        enable_language(ASM_MASM)

        if (MSVC_TOOLSET_VERSION GREATER_EQUAL 141)
            set(JDKRIG_ASM_FILES
                "src/crypto/cn/asm/cn_main_loop.asm"
                "src/crypto/cn/asm/CryptonightR_template.asm"
            )
        else()
            set(JDKRIG_ASM_FILES
                "src/crypto/cn/asm/win64/cn_main_loop.asm"
                "src/crypto/cn/asm/win64/CryptonightR_template.asm"
            )
        endif()

        set_property(SOURCE ${JDKRIG_ASM_FILES} PROPERTY ASM_MASM)
    else()
        enable_language(ASM)

        if (WIN32 AND CMAKE_C_COMPILER_ID MATCHES GNU)
            set(JDKRIG_ASM_FILES
                "src/crypto/cn/asm/win64/cn_main_loop.S"
                "src/crypto/cn/asm/CryptonightR_template.S"
            )
        else()
            set(JDKRIG_ASM_FILES
                "src/crypto/cn/asm/cn_main_loop.S"
                "src/crypto/cn/asm/CryptonightR_template.S"
            )
        endif()

        set_property(SOURCE ${JDKRIG_ASM_FILES} PROPERTY C)
    endif()

    add_library(${JDKRIG_ASM_LIBRARY} STATIC ${JDKRIG_ASM_FILES})
    set(JDKRIG_ASM_SOURCES
        src/crypto/common/Assembly.h
        src/crypto/common/Assembly.cpp
        src/crypto/cn/r/CryptonightR_gen.cpp
        )
    set_property(TARGET ${JDKRIG_ASM_LIBRARY} PROPERTY LINKER_LANGUAGE C)

    add_definitions(/DJDKRIG_FEATURE_ASM)
else()
    set(JDKRIG_ASM_SOURCES "")
    set(JDKRIG_ASM_LIBRARY "")

    remove_definitions(/DJDKRIG_FEATURE_ASM)
endif()
