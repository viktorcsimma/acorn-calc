cmake_minimum_required (VERSION 3.16)

project(AcornCalc)

include(GNUInstallDirs)

find_package(Catch2 3 REQUIRED)

# including the Acorn library
include(GNUInstallDirs)
include(/usr/local/${CMAKE_INSTALL_LIBDIR}/cmake/Acorn/AcornTargets.cmake)

# see https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/ for the technique
add_executable(calc "")
add_executable(test "")

add_subdirectory(src)
# should we also add headers later? it helps IDEs

target_link_libraries(test PRIVATE Catch2::Catch2)

target_link_libraries(calc PRIVATE Acorn)
target_include_directories(calc
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_options(calc PRIVATE -fuse-ld=gold -no-pie -fno-PIC -lstdc++ -ltinfo -lrt -lutil -ldl -lpthread -lgmp)

target_link_libraries(test PRIVATE Acorn)
target_include_directories(test
                           PUBLIC
                           "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_options(test PRIVATE -fuse-ld=gold -no-pie -fno-PIC -lstdc++ -ltinfo -lrt -lutil -ldl -lpthread -lgmp)
