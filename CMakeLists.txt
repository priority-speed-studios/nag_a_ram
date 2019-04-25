cmake_minimum_required(VERSION 3.0)

project(nag_a_ram)
project(nag_a_ram
    VERSION "0.7.0")
FILE(GLOB CSources src/*.c)
add_executable(${PROJECT_NAME} ${CSources})
target_include_directories(${PROJECT_NAME} PRIVATE ./includes)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-rdynamic")

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${GTK3_LIBRARIES} ${CMAKE_DL_LIBS})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/layouts/mainWindow.xml ${CMAKE_CURRENT_BINARY_DIR}/mainWindow.xml)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/layouts/stylesheets.css ${CMAKE_CURRENT_BINARY_DIR}/stylesheets.css COPYONLY)
file(COPY plugins/plugs DESTINATION .)
