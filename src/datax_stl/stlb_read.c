#include "stl_io.h"

#include "stl_error.h"
#include "internal/stl_rw_common.h"
#include "internal/stlb_byte_swap.h"

#include "../datax_core/endian.h"
#include "../datax_core/error.h"
#include "../datax_core/internal/convert.h"
#include "../datax_core/internal/byte_swap.h"

#include <string.h>

FOUG_INLINE static void read_triangle_memcpy(const uint8_t* buffer,
                                             foug_stl_triangle_t* triangle)
{
  /* *triangle = *((foug_stl_triangle_t*)(buffer)); */
  memcpy(triangle, buffer, FOUG_STLB_TRIANGLE_RAWSIZE);
}

static void foug_stlb_read_facets(foug_stl_geom_creator_t* creator,
                                  const uint8_t* buffer,
                                  const foug_stlb_readwrite_helper* rparams)
{
  const uint32_t facet_count = rparams->facet_count;
  const uint32_t i_facet_offset = rparams->i_facet_offset;
  foug_stl_triangle_t triangle;
  uint32_t buffer_offset = 0;
  uint32_t i_facet = 0;

  if (creator == NULL || creator->add_triangle_func == NULL)
    return;

  for (i_facet = 0; i_facet < facet_count; ++i_facet) {
    /* Decode data */
    read_triangle_memcpy(buffer + buffer_offset, &triangle);
    buffer_offset += FOUG_STLB_TRIANGLE_RAWSIZE;

    if (rparams->fix_endian_func != NULL)
      rparams->fix_endian_func(&triangle);

    /* Declare triangle */
    creator->add_triangle_func(creator->cookie, i_facet_offset + i_facet, &triangle);
  }
}

int foug_stlb_read(foug_stl_geom_creator_t *creator,
                   foug_transfer_t* trsf,
                   foug_endianness_t byte_order)
{
  const foug_endianness_t host_byte_order = foug_host_endianness();
  foug_stlb_readwrite_helper rparams;
  uint8_t  header_data[FOUG_STLB_HEADER_SIZE];
  uint32_t total_facet_count = 0;  /* Count of facets as declared in the stream */
  int error = FOUG_DATAX_NO_ERROR; /* Helper variable to store function result error code  */

  /* Check validity of input parameters */
  if (!foug_stlb_check_params(&error, trsf, byte_order))
    return error;

  /* Initialize rparams */
  memset(&rparams, 0, sizeof(foug_stlb_readwrite_helper));
  if (host_byte_order != byte_order)
    rparams.fix_endian_func = foug_stl_triangle_bswap;

  /* Read header */
  if (foug_stream_read(&trsf->stream, header_data, 1, FOUG_STLB_HEADER_SIZE)
      != FOUG_STLB_HEADER_SIZE)
  {
    return FOUG_STLB_READ_HEADER_WRONG_SIZE_ERROR;
  }

  /* Read facet count */
  if (foug_stream_read(&trsf->stream, trsf->buffer, sizeof(uint32_t), 1) != 1)
    return FOUG_STLB_READ_FACET_COUNT_ERROR;

  memcpy(&total_facet_count, trsf->buffer, sizeof(uint32_t));
  if (host_byte_order != byte_order)
    total_facet_count = foug_uint32_bswap(total_facet_count);

  /* Callback to notify triangle count and header data */
  if (creator != NULL && creator->binary_begin_solid_func != NULL)
    creator->binary_begin_solid_func(creator->cookie, total_facet_count, header_data);

  /* Read triangles */
  while (foug_datax_no_error(error)
         && rparams.i_facet_offset < total_facet_count)
  {
    rparams.facet_count = foug_stream_read(&trsf->stream,
                                           trsf->buffer,
                                           FOUG_STLB_TRIANGLE_RAWSIZE,
                                           trsf->buffer_size / FOUG_STLB_TRIANGLE_RAWSIZE);
    if (foug_stream_error(&trsf->stream) != 0)
      error = FOUG_DATAX_STREAM_ERROR;
    else if (rparams.facet_count > 0)
      error = FOUG_DATAX_NO_ERROR;
    else
      break; /* Exit if no facet to read */

    if (foug_datax_no_error(error)) {
      uint8_t progress_pc;

      foug_stlb_read_facets(creator, trsf->buffer, &rparams);
      rparams.i_facet_offset += rparams.facet_count;
      progress_pc = foug_percentage(0, total_facet_count, rparams.i_facet_offset);
      if (!foug_task_control_handle_progress(&trsf->task_control, progress_pc))
        error = FOUG_DATAX_TASK_STOPPED_ERROR;
    }
  } /* end while */

  if (foug_datax_no_error(error)
      && creator != NULL
      && creator->end_solid_func != NULL)
  {
    creator->end_solid_func(creator->cookie);
  }

  if (foug_datax_no_error(error) && rparams.i_facet_offset != total_facet_count)
    error = FOUG_STLB_READ_FACET_COUNT_ERROR;
  return error;
}
