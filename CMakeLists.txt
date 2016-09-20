cmake_minimum_required(VERSION 2.8.9)

project(HessianVesselnessImage)

#-----------------------------------------------------------------------------
# Extension meta-information
set(EXTENSION_HOMEPAGE "http://slicer.org/slicerWiki/index.php/Documentation/Nightly/Extensions/HessianVesselnessImage")
set(EXTENSION_CATEGORY "itk CLI Module")
set(EXTENSION_CONTRIBUTORS "Longquan Chen (BWH)")
set(EXTENSION_DESCRIPTION "ITK CLI module for HessianVesselnessImage filter")
set(EXTENSION_ICONURL "http://www.example.com/Slicer/Extensions/HessianVesselnessImage.png")
set(EXTENSION_SCREENSHOTURLS "http://www.example.com/Slicer/Extensions/HessianVesselnessImage/Screenshots/1.png")

#-----------------------------------------------------------------------------
# Extension dependencies
#find_package(SlicerExecutionModel REQUIRED)
#find_package(Slicer REQUIRED)
#include(${Slicer_USE_FILE})

#-----------------------------------------------------------------------------
# Extension modules
add_subdirectory(HessianRecursiveGaussianImage)
add_subdirectory(Hessian3DToVesselnessMeasureImage)
add_subdirectory(HessianVesselnessImage)
## NEXT_MODULE

#-----------------------------------------------------------------------------
include(${Slicer_EXTENSION_CPACK})
