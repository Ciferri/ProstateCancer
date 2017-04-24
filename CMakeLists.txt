# General CMake configuration
################################################################################

cmake_minimum_required(VERSION 2.8)
set(CMAKE_VERBOSE_MAKEFILE OFF)


################################################################################
# General Project configuration
################################################################################

# project name
project(M2SLV01)

################################################################################
# Source code declarations
################################################################################

# m2sl basic header files



set(m2sl_HEADER_FILES
#BeelerReuterModel.h
#generic2dtissue.h
generic2dtissueProstate.h
#genericbrischtissue.h
#ischbr.h
Model.h
#modelType.h
#SimMeth.h
#Simulator.h
prostateCell.h
)

# m2sl basic source files
set(m2sl_SOURCE_FILES
#BeelerReuterModel.cpp
#generic2dtissue.cpp
generic2dtissueProstate.cpp
#genericbrischtissue.cpp
#ischbr.cpp
Model.cpp
#modelType.cpp
SimMeth.cpp
Simulator.cpp
prostateCell.cpp
)

set(TOOLS
main.cpp
)

# add_library(M2SLV01 SHARED   ${m2sl_SOURCE_FILES})
# 
# 
# install(TARGETS M2SL
#   RUNTIME DESTINATION bin COMPONENT libraries-core
#   LIBRARY DESTINATION lib COMPONENT libraries-core
#   ARCHIVE DESTINATION lib/static COMPONENT libraries-core
#   )
# 

set(${PROJECT_NAME}_CMAKE_DIRS
   ${CMAKE_SOURCE_DIR}/superbuild
   )

set(CMAKE_MODULE_PATH
  ${${PROJECT_NAME}_CMAKE_DIRS}
  ${CMAKE_MODULE_PATH}
  )
include(GenerateExportHeader)

include(ExternalProject)
include(ConfigureExternalProjectVariables)

# ITK
option(USE_SYSTEM_ITK "Use system installed ITK" OFF)

if (USE_SYSTEM_ITK)
  find_package(ITK REQUIRED)
  set(ITK_BUILD_DIR ${ITK_DIR})
else()
  include(ITK)
endif()


configure_file(${CMAKE_SOURCE_DIR}/superbuild/BinariesPackaging.cmake.in
  ${CMAKE_BINARY_DIR}/BinariesPackaging.cmake
  @ONLY IMMEDIATE)

add_custom_target(pack-binaries
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/BinariesPackaging.cmake
  # DEPENDS Anima_Private
  COMMENT "-- Generating binary packages"
  )



# cmake_minimum_required(VERSION 2.8)
# 
# PROJECT(spline)

# SET(SRCS_C Path3D_Splinetest.cpp path3d.cpp) #--- Les sources C++ ---
ADD_EXECUTABLE(m2slv01 ${m2sl_SOURCE_FILES} ${TOOLS})

# SET(SRCS_C Path3D_SplineInterpolation.cpp path3d.cpp) #--- Les sources C++ ---
# ADD_EXECUTABLE(Path3D_SplineInterpolation ${SRCS_C})
# 
# SET(SRCS_C Path3D_ComputeSSDdistance.cpp path3d.cpp) #--- Les sources C++ ---
# ADD_EXECUTABLE(Path3D_ComputeSSDdistance ${SRCS_C})

# ADD_DEFINITIONS(-g -Wall -Wextra)


# Include and Link Directories
# INCLUDE_DIRECTORIES(${AT_INCLUDE_DIR} ${NII_DIR})
#INCLUDE_DIRECTORIES(${VTK_INCLUDE_DIRS} ${AT_INCLUDE_DIR} ${NII_DIR})
# LINK_DIRECTORIES(${AT_LIBRARY_DIR})
#INK_DIRECTORIES(${VTK_LIBRARY_DIRS} ${AT_LIBRARY_DIR})


# Executables and "stand-alone " librairies
# ADD_EXECUTABLE(DDC ${SRC} ${TOOLS} ${NII_SRC})

