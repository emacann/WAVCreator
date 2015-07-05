#pragma once

#ifndef _SIZE_H
#define _SIZE_H

////////////////////////////////////////////////////////////////////////////////
/// Collision avoidance ////////////////////////////////////////////////////////

#ifndef _STDINT
#define _STDINT

////////////////////////////////////////////////////////////////////////////////
/// Arch check /////////////////////////////////////////////////////////////////

/// Windows
#if (_WIN32 || _WIN64)
 #if _WIN64
  #define ENV_64
 #else
  #define ENV_32
 #endif
#endif

/// GCC
#if __GNUC__
 #if __x86_64__ || __ppc64__
  #define ENV_64
 #else
  #define ENV_32
 #endif
#endif

#if !defined(ENV_32) && !defined(ENV_64)
 #error Unrecognized environment.
#endif // (ENV_32 || ENV_64)

////////////////////////////////////////////////////////////////////////////////
/// Integer types //////////////////////////////////////////////////////////////

#if defined(__INT8_TYPE__)
 typedef __INT8_TYPE__      int8_t;
#else
 typedef signed char        int8_t;
#endif // !__INT8_TYPE__

#if defined(__UINT8_TYPE__)
 typedef __UINT8_TYPE__     uint8_t;
#else
 typedef unsigned char      uint8_t;
#endif // !__UINT8_TYPE__

#if defined(__INT16_TYPE__)
 typedef __INT16_TYPE__     int16_t;
#else
 typedef signed short       int16_t;
#endif // !__INT16_TYPE__

#if defined(__UINT16_TYPE__)
 typedef __UINT16_TYPE__    uint16_t;
#else
 typedef unsigned short     uint16_t;
#endif // !__UINT16_TYPE__

#if defined(__INT32_TYPE__)
 typedef __INT32_TYPE__     int32_t;
#else
 typedef signed int         int32_t;
#endif // !__INT32_TYPE__

#if defined(__UINT32_TYPE__)
 typedef __UINT32_TYPE__    uint32_t;
#else
 typedef unsigned int       uint32_t;
#endif // !__UINT32_TYPE__

#if defined(__INT64_TYPE__)
 typedef __INT64_TYPE__     int64_t;
#else
 typedef signed long long   int64_t;
#endif // !__INT64_TYPE__

#if defined(__UINT64_TYPE__)
 typedef __UINT64_TYPE__    uint64_t;
#else
 typedef unsigned long long uint64_t;
#endif // !__UINT64_TYPE__

typedef int64_t             intmax_t;
typedef uint64_t            uintmax_t;

////////////////////////////////////////////////////////////////////////////////
/// Defines ////////////////////////////////////////////////////////////////////

#if defined(__INT8_MAX__)
 #undef INT8_MAX
 #define INT8_MAX           __INT8_MAX__
#else
 #define INT8_MAX           (127i8)
#endif // !__INT8_MAX__

#define INT8_MIN            (-INT8_MAX - 1)

#if defined(__UINT8_MAX__)
 #undef UINT8_MAX
 #define UINT8_MAX          __UINT8_MAX__
#else
 #define UINT8_MAX          (0xFFui8)
#endif // !__UINT8_MAX__

#if defined(__INT16_MAX__)
 #undef INT16_MAX
 #define INT16_MAX          __INT16_MAX__
#else
 #define INT16_MAX          (32767i16)
#endif // !__INT16_MAX__

#define INT16_MIN           (-INT16_MAX - 1)

#if defined(__UINT16_MAX__)
 #undef UINT16_MAX
 #define UINT16_MAX         __UINT16_MAX__
#else
 #define UINT16_MAX         (0xFFFFui16)
#endif // !__UINT16_MAX__

#if defined(__INT32_MAX__)
 #undef INT32_MAX
 #define INT32_MAX          __INT32_MAX__
#else
 #define INT32_MAX          (2147483647i32)
#endif // !__INT32_MAX__

#define INT32_MIN           (-INT32_MAX - 1)

#if defined(__UINT32_MAX__)
 #undef UINT32_MAX
 #define UINT32_MAX         __UINT32_MAX__
#else
 #define UINT32_MAX         (0xFFFFFFFFui32)
#endif // !__UINT32_MAX__

#if defined(__INT64_MAX__)
 #undef INT64_MAX
 #define INT64_MAX          __INT64_MAX__
#else
 #define INT64_MAX          (9223372036854775807i64)
#endif // !__INT64_MAX__

#define INT64_MIN           (-INT64_MAX - 1)

#if defined(__UINT64_MAX__)
 #undef UINT64_MAX
 #define UINT64_MAX         __UINT64_MAX__
#else
 #define UINT64_MAX         (0xFFFFFFFFFFFFFFFFui64)
#endif // !__UINT64_MAX__

////////////////////////////////////////////////////////////////////////////////
/// Size type //////////////////////////////////////////////////////////////////

#ifndef _SIZE_T_DEFINED
#define _SIZE_T_DEFINED
#if defined(ENV_64)
 typedef uint64_t           size_t;
 #define SIZE_T_MAX         UINT64_MAX
#elif defined(ENV_32)
 typedef uint32_t           size_t;
 #define SIZE_T_MAX         UINT32_MAX
#endif // !ENV_64
#endif // !_SIZE_T_DEFINED

////////////////////////////////////////////////////////////////////////////////
/// Pointer type ///////////////////////////////////////////////////////////////

typedef void *              ptr_t;

#ifndef _INTPTR_T_DEFINED
#define _INTPTR_T_DEFINED
#if defined(ENV_64)
 typedef int64_t            intptr_t;
#elif defined(ENV_32)
 typedef int32_t            intptr_t;
#endif // !ENV_64
#endif // !_INTPTR_T_DEFINED

#ifndef _UINTPTR_T_DEFINED
#define _UINTPTR_T_DEFINED
 #if defined(ENV_64)
  typedef uint64_t           uintptr_t;
 #elif defined(ENV_32)
  typedef uint32_t           uintptr_t;
 #endif // !ENV_64
#endif // !_UINTPTR_T_DEFINED

////////////////////////////////////////////////////////////////////////////////
/// Macros /////////////////////////////////////////////////////////////////////

#define INT8_C(x)           (x)
#define UINT8_C(x)          (x)

#define INT16_C(x)          (x)
#define UINT16_C(x)         (x)

#define INT32_C(x)          (x)
#define UINT32_C(x)         (x ## u)

#define INT64_C(x)          (x ## ll)
#define UINT64_C(x)         (x ## ull)

#define INTMAX_C(x)         INT64_C(x)
#define UINTMAX_C(x)        UINT64_C(x)

#endif // !_STDINT
#endif // !_SIZE_H
