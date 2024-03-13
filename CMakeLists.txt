cmake_minimum_required (VERSION 3.16)

project(AcornCalc)

# find_package(Qt5 CONFIG COMPONENTS Widgets Sql Test REQUIRED)

# add_subdirectory(ViewModel)
# add_subdirectory(View)

# including the Acorn library
include(GNUInstallDirs)
include(/usr/local/${CMAKE_INSTALL_LIBDIR}/cmake/Acorn/AcornTargets.cmake)

add_executable(calc src/test.cpp src/ViewModel/HsCalcStateWrapper.cpp)

target_link_libraries(calc PRIVATE Acorn)
target_include_directories(calc
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_options(calc PRIVATE -fuse-ld=gold -no-pie -fno-PIC -lstdc++ -ltinfo -lrt -lutil -ldl -lpthread -lgmp)
