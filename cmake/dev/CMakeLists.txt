cmake_minimum_required(VERSION 2.8)
project(tensor_permeability)

SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR}/tensor_permeability)

INCLUDE(${CSMP_DIR}/source_code/FindCSMP.cmake)

find_package(Boost 1.48 REQUIRED)
   
if(Boost_FOUND)

INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} .
										../../../json/src
										../../../Catch/include
										../../src
										../../configurator/src
										../../solver/src
										../../analysis/src
										../..
										${EIGEN_DIR})

SET (tensor_permeability_SRC 
		../../src/settings.cpp
		../../src/configurator.cpp
		../../src/null_configurator.cpp
		../../src/configurator_factory.cpp
		../../src/model_io.cpp
		../../src/run.cpp
		../../analysis/src/report.cpp
		../../analysis/src/fetch.cpp
		../../analysis/src/analyze.cpp
		../../analysis/src/results.cpp
		../../analysis/src/omega.cpp
		../../analysis/src/omega_generator.cpp
		../../analysis/src/dfn_omega.cpp
		../../analysis/src/make_omega_generator.cpp
		../../analysis/src/omega_configurator_factory.cpp
		../../analysis/src/omega_bdistance_configurator.cpp
		../../analysis/src/omega_bdistance_generator.cpp
		../../analysis/src/omega_corner_points_configurator.cpp
		../../analysis/src/omega_corner_points_generator.cpp
		../../solver/src/pressure_solver.cpp
		../../solver/src/boundaries.cpp
		../../solver/src/sort_boundaries.cpp
		../../configurator/src/matrix_configurator_factory.cpp
		../../configurator/src/fracture_configurator_factory.cpp
		../../configurator/src/uniform_matrix_configurator.cpp
		../../configurator/src/uniform_fracture_configurator.cpp
		../../configurator/src/regional_uniform_fracture_configurator.cpp)


SET (tensor_permeability_callable_SRC 
		${tensor_permeability_SRC}
		../../src/main.cpp)


SET (tensor_permeability_test_SRC 
		${tensor_permeability_SRC}
		../../src/ttrans_test.cpp
		../../src/settings_test.cpp
		../../test/main.cpp
		../../test/dev.cpp
		../../analysis/src/omega_test.cpp)


SET (tensor_permeability_HEADER
		../../src/defs.h
		../../src/bpreds.h
		../../src/elops.h
		../../src/ttrans.h
		../../src/settings.h
		../../src/configurator.h
		../../src/null_configurator.h
		../../src/configurator_factory.h
		../../src/model_io.h
		../../src/run.h
		../../analysis/src/report.h
		../../analysis/src/fetch.h
		../../analysis/src/analyze.h
		../../analysis/src/results.h
		../../analysis/src/omega.h
		../../analysis/src/omega_generator.h
		../../analysis/src/dfn_omega.h
		../../analysis/src/make_omega_generator.h
		../../analysis/src/omega_configurator_factory.h
		../../analysis/src/omega_corner_points_configurator.h
		../../analysis/src/omega_corner_points_generator.h
		../../analysis/src/omega_bdistance_configurator.h
		../../analysis/src/omega_bdistance_generator.h
		../../solver/src/pressure_solver.h
		../../solver/src/boundaries.h
		../../solver/src/sort_boundaries.h
		../../configurator/src/matrix_configurator_factory.h
		../../configurator/src/fracture_configurator_factory.h
		../../configurator/src/uniform_matrix_configurator.h
		../../configurator/src/uniform_fracture_configurator.h
		../../configurator/src/regional_uniform_fracture_configurator.h)


LINK_DIRECTORIES(${BOOST_LIBRARYDIR})
ADD_EXECUTABLE(tensor_permeability_test ${tensor_permeability_test_SRC} ${tensor_permeability_HEADER})
ADD_EXECUTABLE(tensor_permeability ${tensor_permeability_callable_SRC} ${tensor_permeability_HEADER})
TARGET_LINK_LIBRARIES(tensor_permeability csmp_core ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(tensor_permeability_test csmp_core ${Boost_LIBRARIES})

endif()