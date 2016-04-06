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

#ifndef GMIO_INTERNAL_STRING_H
#define GMIO_INTERNAL_STRING_H

#include "../global.h"

#include <stddef.h>

/*! Stores a read-only string of 8-bit chars
 *
 *  For faster lookups, it knowns the length of its contents.
 */
struct gmio_const_string
{
    const char* ptr; /*!< Contents */
    size_t len;      /*!< Size(length) of current contents */
};

/*! Stores a mutable string of 8-bit chars
 *
 *  For faster lookups, it knowns the length of its contents. Length must not
 *  exceeds the maximum size(capacity).
 */
struct gmio_string
{
    char*  ptr; /*!< Contents */
    size_t len; /*!< Size(length) of current contents */
    size_t max_len; /*!< Maximum contents size(capacity) */
};

/*! Expands to bracket initialization of a gmio_const_string from const char[]
 *
 *  Example:
 *  \code{.c}
 *      static const char token[] = "woops";
 *      struct gmio_const_string token_s = GMIO_CONST_STRING_FROM_ARRAY(token);
 *  \endcode
 */
#define GMIO_CONST_STRING_FROM_ARRAY(array) { &(array)[0], sizeof(array) - 1 }

/*! Returns an initialized struct gmio_const_string object */
GMIO_INLINE struct gmio_const_string gmio_const_string(const char* ptr, size_t len);

/*! Returns an initialized struct gmio_string object
 *
 *  string.max_len is set to max(len,max_len)
 */
GMIO_INLINE struct gmio_string gmio_string(char* ptr, size_t len, size_t max_len);

/*! Clears the contents of the string \p str and makes it null */
GMIO_INLINE void gmio_string_clear(struct gmio_string* str);

/*! Returns a pointer after the last character of \p str */
GMIO_INLINE const char* gmio_string_end(const struct gmio_string* str);

/*! Copies contents of \p src into \p dst */
GMIO_INLINE void gmio_string_copy(
        struct gmio_string* dst, const struct gmio_string* src);

/*! Copies contents of C-string \p src into \p dst */
GMIO_INLINE char* gmio_cstr_copy(
        char* dst, size_t dst_capacity, const char* src, size_t src_len);

/*
 * -- Implementation
 */

#include <string.h>
#include "min_max.h"

struct gmio_const_string gmio_const_string(const char* ptr, size_t len)
{
    struct gmio_const_string cstr;
    cstr.ptr = ptr;
    cstr.len = len;
    return cstr;
}

struct gmio_string gmio_string(char* ptr, size_t len, size_t max_len)
{
    struct gmio_string str;
    str.ptr = ptr;
    str.len = len;
    str.max_len = GMIO_MAX(len, max_len);
    return str;
}

void gmio_string_clear(struct gmio_string* str)
{
    str->ptr[0] = 0;
    str->len = 0;
}

const char* gmio_string_end(const struct gmio_string* str)
{
    return &str->ptr[str->len];
}

void gmio_string_copy(
        struct gmio_string* dst, const struct gmio_string* src)
{
    const size_t dst_new_len = GMIO_MIN(dst->max_len, src->len);
    strncpy(dst->ptr, src->ptr, dst_new_len);
    dst->len = dst_new_len;
}

char* gmio_cstr_copy(
        char* dst, size_t dst_capacity, const char* src, size_t src_len)
{
    const size_t copy_len =
            dst_capacity > 0 ?
                GMIO_MIN(dst_capacity - 1, src_len) :
                0;
    if (copy_len > 0) {
        strncpy(dst, src, copy_len);
        dst[copy_len] = '\0';
    }
    return dst + copy_len;
}

#endif /* GMIO_INTERNAL_STRING_H */
