/* KITTENpaw
 * Copyright (c) 2018-2024 SChernykh   <https://github.com/SChernykh>
 * Copyright (c) 2016-2024 KITTENpaw       <https://github.com/kittenpaw>, <support@kittenpaw.com>
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

#ifndef KITTENPAW_VERSION_H
#define KITTENPAW_VERSION_H

#define APP_ID        "kittenpaw"
#define APP_NAME      "KITTENpaw"
#define APP_DESC      "KITTENpaw kittenpawger"
#define APP_VERSION   "6.22.2"
#define APP_DOMAIN    "kittenpaw.com"
#define APP_SITE      "www.kittenpaw.com"
#define APP_COPYRIGHT "Copyright (C) 2016-2024 kittenpaw.com"
#define APP_KIND      "kittenpawger"

#define APP_VER_MAJOR  6
#define APP_VER_MINOR  22
#define APP_VER_PATCH  2

#ifdef _MSC_VER
#   if (_MSC_VER >= 1930)
#       define MSVC_VERSION 2022
#   elif (_MSC_VER >= 1920 && _MSC_VER < 1930)
#       define MSVC_VERSION 2019
#   elif (_MSC_VER >= 1910 && _MSC_VER < 1920)
#       define MSVC_VERSION 2017
#   elif _MSC_VER == 1900
#       define MSVC_VERSION 2015
#   elif _MSC_VER == 1800
#       define MSVC_VERSION 2013
#   elif _MSC_VER == 1700
#       define MSVC_VERSION 2012
#   elif _MSC_VER == 1600
#       define MSVC_VERSION 2010
#   else
#       define MSVC_VERSION 0
#   endif
#endif

#ifdef KITTENPAW_OS_WIN
#    define APP_OS "Windows"
#elif defined KITTENPAW_OS_IOS
#    define APP_OS "iOS"
#elif defined KITTENPAW_OS_MACOS
#    define APP_OS "macOS"
#elif defined KITTENPAW_OS_ANDROID
#    define APP_OS "Android"
#elif defined KITTENPAW_OS_LINUX
#    define APP_OS "Linux"
#elif defined KITTENPAW_OS_FREEBSD
#    define APP_OS "FreeBSD"
#else
#    define APP_OS "Unknown OS"
#endif

#define STR(X) #X
#define STR2(X) STR(X)

#ifdef KITTENPAW_ARM
#   define APP_ARCH "ARMv" STR2(KITTENPAW_ARM)
#else
#   if defined(__x86_64__) || defined(__amd64__) || defined(_M_X64) || defined(_M_AMD64)
#       define APP_ARCH "x86-64"
#   else
#       define APP_ARCH "x86"
#   endif
#endif

#ifdef KITTENPAW_64_BIT
#   define APP_BITS "64 bit"
#else
#   define APP_BITS "32 bit"
#endif

#endif // KITTENPAW_VERSION_H
