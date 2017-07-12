cmake_minimum_required(VERSION 2.6)

project(gca)

set(VTK_DIR /Users/dillon/Downloads/VTK-build/)

find_package(CGAL REQUIRED COMPONENTS Core)
include( ${CGAL_USE_FILE} )

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

SET(EXTRA_CXX_COMPILE_FLAGS "-std=c++11 -I./src -I./test -I/opt/local/include -O2 -I/Users/dillon/Downloads/tetgen1.5.1-beta1 -I/Users/dillon/Downloads/mfem-3.3/build/")
#-Werror -Wall")

SET(CXX_OCL_LINK_FLAGS "-locl -locl.11.10.66 -ltet -L/Users/dillon/Downloads/tetgen1.5.1-beta1 -lmfem")
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CXX_OCL_LINK_FLAGS}")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${EXTRA_CXX_COMPILE_FLAGS}")

INCLUDE_DIRECTORIES(./src/)

SET(UTILS_CPPS ./src/utils/arena_allocator.cpp)

SET(UTILS_HEADERS ./src/utils/algorithm.h
		  ./src/utils/arena_allocator.h)

add_library(utils ${UTILS_CPPS} ${UTILS_HEADERS})

SET(GEOMETRY_HEADERS ./src/geometry/line.h
		     ./src/geometry/surface.h
		     ./src/geometry/point.h
		     ./src/geometry/plane.h
		     ./src/geometry/offset.h
		     ./src/geometry/polygon_3.h
	    ./src/geometry/b_spline.h
	    ./src/geometry/extrusion.h
	    ./src/geometry/spline_sampling.h
	    ./src/geometry/matrix.h
	    ./src/geometry/rotation.h
	    ./src/geometry/triangle.h
	    ./src/geometry/triangular_mesh.h
	    ./src/geometry/homogeneous_transformation.h
	    ./src/geometry/mesh_operations.h
	    ./src/geometry/vtk_debug.h
	    ./src/geometry/vtk_utils.h)

SET(GEOMETRY_CPPS ./src/geometry/point.cpp
		  ./src/geometry/surface.cpp
		  ./src/geometry/offset.cpp
		  ./src/geometry/polygon_3.cpp
		  ./src/geometry/extern_triangulate.cpp
	 ./src/geometry/arc.cpp
	 ./src/geometry/box.cpp
	 ./src/geometry/depth_field.cpp
	 ./src/geometry/extrusion.cpp
	 ./src/geometry/plane.cpp
	 ./src/geometry/line.cpp
	 ./src/geometry/matrix.cpp
	 ./src/geometry/polygon.cpp
	 ./src/geometry/polyline.cpp
	 ./src/geometry/spline_sampling.cpp
	 ./src/geometry/rotation.cpp
	 ./src/geometry/triangle.cpp
	 ./src/geometry/triangular_mesh.cpp
	 ./src/geometry/triangular_mesh_utils.cpp
	 ./src/geometry/trimesh.cpp
	 ./src/geometry/trimesh_types.cpp
	 ./src/geometry/homogeneous_transformation.cpp
	 ./src/geometry/mesh_operations.cpp
	 ./src/geometry/voxel_volume.cpp
	 ./src/geometry/voxel_volume_debug.cpp
	 ./src/geometry/vtk_debug.cpp
	 ./src/geometry/vtk_utils.cpp
	 ./src/triangle_lib/triangle.cpp)

add_library(geometry ${GEOMETRY_CPPS} ${GEOMETRY_HEADERS})
target_link_libraries(geometry utils ${CGAL_LIBRARIES})

# /Users/dillon/CppWorkspace/gca/src/triangle_lib/triangle.o)

SET(GEOMETRY_TEST_FILES test/plane_tests.cpp
			test/fem_tests.cpp
			test/rotation_tests.cpp
			test/extrusion_tests.cpp
			test/matrix_tests.cpp
			test/surface_tests.cpp
			test/polygon_tests.cpp
			test/polyline_tests.cpp
			test/triangle_tests.cpp
			test/arc_tests.cpp
			test/ring_tests.cpp
			test/point_tests.cpp
			test/line_tests.cpp
			test/mesh_tests.cpp
			test/spline_tests.cpp
			test/voxel_volume_tests.cpp
			test/axis_field_tests.cpp)
			

add_executable(geometry-tests test/main_geometry.cpp ${GEOMETRY_TEST_FILES})
target_link_libraries(geometry-tests geometry utils gca)

SET(GCODE_HEADERS ./src/gcode/value.h
	    	  ./src/gcode/gcode_program.h
	    	  ./src/gcode/circular_arc.h
	    	  ./src/gcode/linear_cut.h
		  ./src/gcode/machine.h
	    	  ./src/gcode/safe_move.h
	    	  ./src/gcode/hole_punch.h)

SET(GCODE_CPPS 	 ./src/gcode/cut.cpp
	 ./src/gcode/value.cpp
	 ./src/gcode/lexer.cpp
	 ./src/gcode/machine.cpp
	 ./src/gcode/parse_stream.cpp
	 ./src/gcode/linear_cut.cpp
	 ./src/gcode/visual_debug.cpp)

SET(TEST_FILES test/system_algorithm_tests.cpp)

add_executable(all-tests ${TEST_FILES} ${MANUFACTURE_TEST_FILES})
target_link_libraries(all-tests geometry utils gcode gprocess gca backend)
