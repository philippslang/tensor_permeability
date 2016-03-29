cmake_minimum_required(VERSION 2.8)
project(tensor_permeability)

SET(EXECUTABLE_OUTPUT_PATH ${BIN_DIR}/tensor_permeability)

INCLUDE(${CSMP_DIR}/source_code/FindCSMP.cmake)

find_package(Boost 1.48 REQUIRED)
   
if(Boost_FOUND)

INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} .
										../../../json/src
										../../../Catch/include
										../../src)

SET (tensor_permeability_SRC 
		../../src/setting.cpp
		../../src/setting_test.cpp
		../../test/main.cpp
		../../test/dev.cpp)

SET (tensor_permeability_HEADER
		../../src/setting.h)

LINK_DIRECTORIES(${BOOST_LIBRARYDIR})
ADD_EXECUTABLE(tensor_permeability ${tensor_permeability_SRC} ${tensor_permeability_HEADER})
TARGET_LINK_LIBRARIES(tensor_permeability csmp_core ${Boost_LIBRARIES})

endif()