/****************************************************************************
** gmio
** Copyright Fougue (2 Mar. 2015)
** contact@fougue.pro
**
** This software is a reusable library whose purpose is to provide complete
** I/O support for various CAD file formats (eg. STL)
**
** This software is governed by the CeCILL-B license under French law and
** abiding by the rules of distribution of free software.  You can  use,
** modify and/ or redistribute the software under the terms of the CeCILL-B
** license as circulated by CEA, CNRS and INRIA at the following URL
** "http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html".
****************************************************************************/

/*! \file global.h
 *  Fundamental global declarations, included by almost all other header/source
 *  files
 *
 *  \defgroup gmio_core gmioCore
 *  All other gmio modules rely on this module
 *
 *  \addtogroup gmio_core
 *  @{
 */

#ifndef GMIO_GLOBAL_H
#define GMIO_GLOBAL_H

/* "config.h" is generated by cmake, it should reside in the out-of-source
 * build dir.
 * In CMakeFiles.txt, the directory where resides "config.h" is added to the
 * include path list
 */
#include "config.h"

/* GMIO_OS_WIN */
#if defined(WIN64) || defined(_WIN64) || defined(__WIN64__) \
      || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) \
      || defined(__NT__)
#  define GMIO_OS_WIN
#endif

/* GMIO_OS_LINUX */
#if defined(__linux) || defined(__linux__) || defined(linux)
#  define GMIO_OS_LINUX
#endif

/* GMIO_OS_MAC */
#if defined(__APPLE__)
#  define GMIO_OS_MAC
#endif

/* GMIO_DECL_IMPORT */
/* GMIO_DECL_EXPORT */
#ifdef GMIO_OS_WIN
#  define GMIO_DECL_EXPORT __declspec(dllexport)
#  define GMIO_DECL_IMPORT __declspec(dllimport)
#else
/*! Expands to the C compiler extension to export functions to a DLL */
#  define GMIO_DECL_EXPORT
/*! Expands to the C compiler extension to import functions from a DLL */
#  define GMIO_DECL_IMPORT
#endif

/* GMIO_API */
#ifdef GMIO_DLL
#  ifdef GMIO_MAKING_DLL
#    define GMIO_API GMIO_DECL_EXPORT
#  else
#    define GMIO_API GMIO_DECL_IMPORT
#  endif /* GMIO_MAKING_DLL */
#else
/*! Expands either to GMIO_DECL_EXPORT or GMIO_DECL_IMPORT when respectively
 *  compiling/using the DLL */
#  define GMIO_API
#endif

/* Typedefs for specific width integers */
#ifdef GMIO_HAVE_STDINT_H
#  include <stdint.h>
#else
typedef char          int8_t;
typedef unsigned char uint8_t;

#  if GMIO_SIZEOF_SHORT == 2
typedef short          int16_t;
typedef unsigned short uint16_t;
#  else
#    error Not supported: sizeof(short) != 2
#  endif

#  if GMIO_SIZEOF_INT == 4
typedef int          int32_t;
typedef unsigned int uint32_t;
#  elif GMIO_SIZEOF_LONG == 4
typedef long          int32_t;
typedef unsigned long uint32_t;
#  else
#    error Failed to find a 32bit integer type with 'int' and 'long'
#  endif

#endif

/* (u)int64_t */
#ifndef GMIO_HAVE_INT64_T
#  if defined(GMIO_HAVE_MSVC_INT64)
typedef __int64_t          int64_t;
typedef unsigned __int64_t uint64_t;
#  elif defined(GMIO_HAVE_LONG_LONG)
typedef long long          int64_t;
typedef unsigned long long uint64_t;
#  endif
#endif

/* GMIO_HAVE_INT64_TYPE */
#if defined(GMIO_HAVE_INT64_T) \
      || defined(GMIO_HAVE_MSVC_INT64) \
      || defined(GMIO_HAVE_LONG_LONG)
#  define GMIO_HAVE_INT64_TYPE
#endif

/* GMIO_HAVE_STDBOOL_H */
#ifdef GMIO_HAVE_STDBOOL_H
#  include <stdbool.h>
#elif !defined(DOXYGEN) && !defined(__cplusplus)
typedef int bool;
enum gmio_bool_value
{
    false = 0,
    true = 1
};
#endif

/* GMIO_UNUSED */
/*! Tells the compiler that a parameter is not used in the body of a function */
#define GMIO_UNUSED(x) (void)x;

/* GMIO_INLINE */
#ifndef GMIO_INLINE
#  if defined(__GNUC__)
#    define GMIO_INLINE __inline__ static  /* Compatible with C90 */
#  elif defined(_MSC_VER)
#    define GMIO_INLINE __inline static
#  elif !defined(DOXYGEN)
#    define GMIO_INLINE static
#  else
/*! Expands to the C compiler specific inline keyword (if any) */
#    define GMIO_INLINE
#  endif
#endif

/* GMIO_RESTRICT */
#ifndef GMIO_RESTRICT
#  if defined(__GNUC__)
#    define GMIO_RESTRICT __restrict__  /* Compatible with C90 */
#  elif defined(_MSC_VER)
#    define GMIO_RESTRICT __restrict
#  elif defined(GMIO_HAVE_C99_RESTRICT) /* TODO: add cmake detectection */
#    define GMIO_RESTRICT restrict
#  else
/*! Expands to the C compiler specific restrict keyword (if any) */
#    define GMIO_RESTRICT
#  endif
#endif

/* GMIO_C_LINKAGE_BEGIN */
/* GMIO_C_LINKAGE_END */
#ifdef __cplusplus
#  define GMIO_C_LINKAGE_BEGIN extern "C" {
#  define GMIO_C_LINKAGE_END   }
#else
/*! Expands to <tt>extern "C" {</tt> when building with a C++ compiler */
#  define GMIO_C_LINKAGE_BEGIN
/*! Expands to \c } when building with a C++ compiler */
#  define GMIO_C_LINKAGE_END
#endif

/* GMIO_PRAGMA_MSVC_WARNING_PUSH_AND_DISABLE */
/* GMIO_PRAGMA_MSVC_WARNING_POP */
#if defined(_MSC_VER) && _MSC_VER >= 1400 /* Visual C++ 2008 */
#  define GMIO_PRAGMA_MSVC_WARNING_PUSH_AND_DISABLE(__code__) \
     __pragma(warning(push)) \
     __pragma(warning(disable: __code__))
#  define GMIO_PRAGMA_MSVC_WARNING_POP() \
     __pragma(warning(pop))
#else
/*! MSVC specific macro that disable the compiler warning of code \p __code__
 *
 * With Visual C++, expands to :
 *    \code{.c}
 *      #pragma warning(push)
 *      #pragma warning(disable: __code__)
 *    \endcode
 */
#  define GMIO_PRAGMA_MSVC_WARNING_PUSH_AND_DISABLE(__code__)
/*! MSVC specific macro that pop the changes made after last warning(pop)
 *
 * With Visual C++, expands to :
 *    \code{.c}
 *      #pragma warning(pop)
 *    \endcode
 */
#  define GMIO_PRAGMA_MSVC_WARNING_POP()
#endif

/*! Expands to the size(item count) of an array */
#define GMIO_ARRAY_SIZE(array) sizeof(array) / sizeof(*array)

#endif /* GMIO_GLOBAL_H */
/*! @} */
