#ifndef FOUG_DATAX_C_LIBSTL_TRIANGLE_H
#define FOUG_DATAX_C_LIBSTL_TRIANGLE_H

#include "stl_global.h"

/*! Cartesian coordinate entity in 3D space, specifically tailored for STL needs (single-float) */
struct foug_stl_coords
{
  foug_real32_t x;
  foug_real32_t y;
  foug_real32_t z;
};

typedef struct foug_stl_coords foug_stl_coords_t;

/*! STL mesh triangle defined three geometric vertices and an orientation(normal) */
struct foug_stl_triangle
{
  foug_stl_coords_t normal;
  foug_stl_coords_t v1;
  foug_stl_coords_t v2;
  foug_stl_coords_t v3;
  uint16_t          attribute_byte_count; /*!< Useful only for STL binary format */
};

typedef struct foug_stl_triangle foug_stl_triangle_t;

/*! Compact size of a foug_stl_coords_t object */
#define FOUG_STL_COORDS_RAWSIZE (3 * sizeof(foug_real32_t))

/*! Compact size of a foug_stl_triangle_t object for STL ascii format */
#define FOUG_STLA_TRIANGLE_RAWSIZE (4 * FOUG_STL_COORDS_RAWSIZE)

/*! Compact size of a foug_stl_triangle_t object for STL binary format */
#define FOUG_STLB_TRIANGLE_RAWSIZE (FOUG_STLA_TRIANGLE_RAWSIZE + sizeof(uint16_t))

#endif /* FOUG_DATAX_C_LIBSTL_TRIANGLE_H */