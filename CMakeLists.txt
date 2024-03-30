cmake_minimum_required (VERSION 3.16)

project(AcornCalc)
set(PROJECT_VERSION 0.1)
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT-NAME_VERSION_MINOR 1)

include(GNUInstallDirs)

find_package(Catch2 3 REQUIRED)

# including the Acorn library
include(GNUInstallDirs)
include(/usr/local/${CMAKE_INSTALL_LIBDIR}/cmake/Acorn/AcornTargets.cmake)

# for Qt

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
# for Qt Concurrent
find_package(Qt6 REQUIRED COMPONENTS Concurrent)

set(TS_FILES src/View/calc_en_GB.ts)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calc
        MANUAL_FINALIZATION
        ""


        include/View/PrimaryLineEdit.h
        src/View/PrimaryLineEdit.cpp
        src/View/HistoryItemWidget.ui
        include/View/HistoryItemWidget.h
        src/View/HistoryItemWidget.cpp
        src/View/PreciseOutputWindow.ui
        include/View/PreciseOutputWindow.h
        src/View/PreciseOutputWindow.cpp




    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET calc APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(calc SHARED
            ""
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(calc
            ""
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# this is a simple terminal program
add_executable(test "")

# afterwards:

# see https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/ for the technique
add_subdirectory(src)
add_subdirectory(include)
# should we also add headers later? it helps IDEs

target_link_libraries(calc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
# for Qt Concurrent
target_link_libraries(calc PRIVATE Qt6::Concurrent)

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

install(TARGETS calc
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calc)
endif()
