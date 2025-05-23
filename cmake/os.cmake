if (WIN32)
    set(KITTENPAW_OS_WIN ON)
elseif (APPLE)
    set(KITTENPAW_OS_APPLE ON)

    if (IOS OR CMAKE_SYSTEM_NAME STREQUAL iOS)
        set(KITTENPAW_OS_IOS ON)
    else()
        set(KITTENPAW_OS_MACOS ON)
    endif()
else()
    set(KITTENPAW_OS_UNIX ON)

    if (ANDROID OR CMAKE_SYSTEM_NAME MATCHES "Android")
        set(KITTENPAW_OS_ANDROID ON)
    elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
        set(KITTENPAW_OS_LINUX ON)
    elseif(CMAKE_SYSTEM_NAME STREQUAL FreeBSD OR CMAKE_SYSTEM_NAME STREQUAL DragonFly)
        set(KITTENPAW_OS_FREEBSD ON)
    endif()
endif()


if (KITTENPAW_OS_WIN)
    add_definitions(-DWIN32 -DKITTENPAW_OS_WIN)
elseif(KITTENPAW_OS_APPLE)
    add_definitions(-DKITTENPAW_OS_APPLE)

    if (KITTENPAW_OS_IOS)
        add_definitions(-DKITTENPAW_OS_IOS)
    else()
        add_definitions(-DKITTENPAW_OS_MACOS)
    endif()

    if (KITTENPAW_ARM)
        set(WITH_SECURE_JIT ON)
    endif()
elseif(KITTENPAW_OS_UNIX)
    add_definitions(-DKITTENPAW_OS_UNIX)

    if (KITTENPAW_OS_ANDROID)
        add_definitions(-DKITTENPAW_OS_ANDROID)
    elseif (KITTENPAW_OS_LINUX)
        add_definitions(-DKITTENPAW_OS_LINUX)
    elseif (KITTENPAW_OS_FREEBSD)
        add_definitions(-DKITTENPAW_OS_FREEBSD)
    endif()
endif()

if (WITH_SECURE_JIT)
    add_definitions(-DKITTENPAW_SECURE_JIT)
endif()
