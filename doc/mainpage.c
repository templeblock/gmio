/*! \mainpage

\section intro Introduction

  gmio is a reusable C library whose purpose is to provide complete I/O
  support for various CAD file formats (eg. <a href="https://en.wikipedia.org/wiki/STL_%28file_format%29">STL</a>)

  gmio aims to be <a href="https://github.com/fougue/gmio/wiki/4.-Benchmarks">fast</a>,
  portable (C90 conformance) and feature-rich.
  Main highlights:

  \li "Abstract" streams that does not tie the user to C stream (`FILE*`)\n
      gmio provides a general stream structure based on callbacks, so that any API
      can be used (C++ streams, QFile, ...)

  \li Buffering of input/ouput for efficient device usage
  \li Operations can be easily aborted
  \li Progress report about the I/O operation
  \li Available under the CeCILL-B license, which is fully BSD compatible

\section sup_cadf Supported CAD files format

Current version only supports the STL file format (STereoLithography), but
support is complete :

  \li ASCII format: Case-insensitive reading
  \li ASCII format: Output format(%f, %e, ...) and precision of floats support
  \li Binary format: Little/big endian support
  \li Binary format: 80-byte header and facet "attribute byte count" support
  \li Detection of the input format
  \li Retrieval of infomations about contents(facet count, solid name, ...)

In addition, the STL module has the following advatanges:

  \li The user keeps its own geometry data structures, no conversion needed\n
      This reduces the effort so that the user just specifies callbacks for
      retrieval/creation of mesh data

  \li Constant memory footprint\n
      Memory consumption is indenpendant of the mesh size ie. the amount of memory
      used remains constant during the I/O operation

  \li Extended support of OpenCascade\n
      `StlMesh_Mesh` objects can be used seamlessly with gmio

\section build Building gmio

gmio can be built with CMake, by default a static library is generated.

Read the <a href="https://github.com/fougue/gmio/wiki/2.-Build-instructions">Build instructions</a>

\section bug_report How to report a bug

If you think you have found a bug in gmio, we would like to hear
about it so that we can fix it.\n
The gmio bug tracking system is open to the public at https://github.com/fougue/gmio/issues.

Always include the following information in your bug report:
  \li the name and version number of your compiler
  \li the name and version number of your operating system
  \li the version of gmio you are using
  \li what configure options it was compiled with.

If the problem you are reporting is only visible at run-time, try to
create a small test program that shows the problem when run.

\section lic License

This software is governed by the CeCILL-B license under French law and
abiding by the rules of distribution of free software.\n
You can  use, modify and/ or redistribute the software under the terms of the CeCILL-B
license as circulated by CEA, CNRS and INRIA at this
<a href="http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html">URL</a>

\section creds Credits

"gmio" logo rendered with Prism font (thanks to Erik Yin !)

*/

/*!
   \example ../examples/occstl_read_file.cpp
   \example ../examples/occstl_redefine_mesh_creator.cpp
   \example ../examples/occstl_write_file.cpp
   \example ../examples/stl_get_infos.c
   \example ../examples/stl_read_file.c
   \example ../examples/stl_write_file.c
 */