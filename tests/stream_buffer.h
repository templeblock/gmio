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

#ifndef GMIO_STREAM_BUFFER_H
#define GMIO_STREAM_BUFFER_H

#include "../src/gmio_core/stream.h"

struct gmio_stream_buffer
{
    const void* readonly_ptr;
    void* readwrite_ptr;
    size_t len;
    size_t pos;
};
typedef struct gmio_stream_buffer gmio_stream_buffer_t;

void gmio_stream_set_buffer(gmio_stream_t* stream, gmio_stream_buffer_t* buff);

#endif /* GMIO_STREAM_BUFFER_H */
