cmake_minimum_required(VERSION 3.5)

project(smartcalc VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_INSTALL_PREFIX ../project_dir)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

include_directories(
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
)

set(TS_FILES frontend_ru_RU.ts)

set(BACKEND_SOURCES
    ./backend/s21_smartcalc_model.h
    ./backend/s21_smartcalc_controller.h
)

set(CREDIT_SOURCES
    ./frontend/creditwindow.h
    ./frontend/creditwindow.cc
    ./frontend/creditwindow.ui
    )

set(DEPOSIT_SOURCES
    ./frontend/depositwindow.h
    ./frontend/depositwindow.cc
    ./frontend/depositwindow.ui
    )

set(GRAPH_SOURCES
    qcustomplot.h
    qcustomplot.cc
    ./frontend/graphwindow.h
    ./frontend/graphwindow.cc
    ./frontend/graphwindow.ui
    )

set(FRONTEND_SOURCES
    main.cc
    ./frontend/mainwindow.cc
    ./frontend/mainwindow.h
    ./frontend/mainwindow.ui
    ./frontend/financewindow.h
    ${CREDIT_SOURCES}
    ${DEPOSIT_SOURCES}
    ${GRAPH_SOURCES}
    ./frontend/resultdialog.h
)

set(PROJECT_SOURCES
    ${FRONTEND_SOURCES}
    ${TS_FILES}
    ${BACKEND_SOURCES}
)

set(TEST_SOURCES
    ./tests/test_s21_smartcalc.cc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(smartcalc
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(smartcalc SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(smartcalc
            ${PROJECT_SOURCES}
        )
    endif()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(smartcalc PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport)

set_target_properties(smartcalc PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(smartcalc)
endif()


enable_testing()
find_package(GTest REQUIRED)
include_directories(${Qt${QT_VERSION_MAJOR}_INCLUDE_DIRS})

add_executable(tests ${TEST_SOURCES})
target_link_libraries(tests PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${GTEST_LIBRARIES} Qt${QT_VERSION_MAJOR}::PrintSupport pthread)

find_program(VALGRIND_EXECUTABLE valgrind)
if(VALGRIND_EXECUTABLE)
    add_test(NAME valgrind_tests
             COMMAND ${VALGRIND_EXECUTABLE} --leak-check=full --error-exitcode=1 $<TARGET_FILE:tests>)
else()
    message(WARNING "Valgrind not found. Unable to run memory checks.")
endif()

add_custom_target(dvi
    COMMAND ${CMAKE_COMMAND} -E echo "Opening DVI file..."
    COMMAND open ./files/dvi.txt
)
add_custom_target(dist
    COMMAND ${CMAKE_COMMAND} -E echo "Creating distribution..."
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/../other
    COMMAND ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_BINARY_DIR}/../other/smartcalc.tar" "${CMAKE_SOURCE_DIR}"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()

install(TARGETS smartcalc RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(TARGETS tests RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/tests)

if(TS_FILES)
    install(FILES ${TS_FILES} DESTINATION ${CMAKE_INSTALL_PREFIX}/translations)
endif()
