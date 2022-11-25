cmake_minimum_required(VERSION 3.16)
project (project)

enable_testing()
add_subdirectory(googletest)
include_directories(${GTEST_INCLUDE_DIRS}/ ${gtest_SOURCE_DIR})

find_package(OpenCV REQUIRED)
set(CMAKE_CXX_STANDARD 14)

include_directories(${OpenCV_INCLUDE_DIRS})




add_executable(image_process main.cpp helper.cpp ImageClass.cpp imageFourierClass.cpp FFTcalcul.cpp FFTcalcul.h)
target_link_libraries(image_process ${OpenCV_LIBS})



add_executable(runTests tests.cpp ImageClass.cpp ImageClass.hpp FFTcalcul.cpp FFTcalcul.h)
target_link_libraries(runTests gtest gtest_main)
add_test(runTests runTests)


find_package(Doxygen)
if(DOXYGEN_FOUND)

    # We then check if the Doxygen.in configuration file exists
    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found.
         - Generate one in the project folder with doxygen -g Doxyfile.in")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

    # We configure the doxyfile for make.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)
