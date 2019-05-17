cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project(RankAndSort VERSION 0.1 LANGUAGES CXX)
set(PROJECT_NAME_L rankandsort)

# -----------------------------------------------------------------------------
# Build settings
# -----------------------------------------------------------------------------

# Set the C standard
# ------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Set the C++ standard
# --------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
# -------
OPTION(BUILD_SHARED_LIBS
    "Build ${PROJECT_NAME}.a rather than ${PROJECT_NAME}.so" OFF)

# Include additional cmake/ settings
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/build")

include(BuildType)
include(BuildLocation)
include(CompilerFlags)

# -----------------------------------------------------------------------------
# Create and set target properties
# -----------------------------------------------------------------------------

message(STATUS "Setting target properties")

# Set the library sources
# -----------------------
set(libsrc
    src/MasterRanker.cpp
    src/rankandsort.cpp
)

set(clibsrc
#    src/model/main.c
#    src/model/tu0.c
#    src/model/tu1.c
#    src/model/tu2.c
#    src/model/tu3.c
#    src/model/tu4.c
#    src/model/tu5.c
#    src/model/tu6.c
#    src/model/tu7.c
)

# Add the library
# ---------------
if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME_L} OBJECT ${libsrc} ${clibsrc})
    add_library(${PROJECT_NAME_L} SHARED $<TARGET_OBJECTS:objlib>)
else()
    add_library(${PROJECT_NAME_L} STATIC ${libsrc} ${clibsrc})
endif()

# Create an alias
add_library(${PROJECT_NAME}::${PROJECT_NAME_L} ALIAS ${PROJECT_NAME_L})

# Include project directories in target
# -------------------------------------
target_include_directories(${PROJECT_NAME_L}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

#target_compile_features(${PROJECT_NAME_L} PRIVATE cxx_auto_type)

# Include external libs
# ---------------------
target_include_directories(${PROJECT_NAME_L}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/libs
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/lowletorfeats/include
)

# Add sub-directories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/lowletorfeats)

# Link against the project
target_link_libraries(${PROJECT_NAME_L}
    PRIVATE
        lowletorfeats
)

message(STATUS "Setting target properties - done")

# -----------------------------------------------------------------------------
# Installation instructions
# -----------------------------------------------------------------------------

message(STATUS "Installing project")

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

# Create a a version file for the project
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Create a config file for the project
configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
    INSTALL_DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Install the ProjectConfig.cmake and ProjectConfigVersion.cmake
install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Add the library to the "export-set"
install(
    TARGETS
        ${PROJECT_NAME_L}
    EXPORT
        ${PROJECT_NAME_L}-targets
    LIBRARY DESTINATION
        ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION
        ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)

set_target_properties(${PROJECT_NAME_L} PROPERTIES EXPORT_NAME ${PROJECT_NAME})

install(
    DIRECTORY
        include/
    DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export the targets to a script
install(
    EXPORT
        ${PROJECT_NAME_L}-targets
    FILE
        ${PROJECT_NAME}Targets.cmake
    NAMESPACE
        ${PROJECT_NAME}::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

message(STATUS "Installing project - done")

# -----------------------------------------------------------------------------
# Export from the build tree
# -----------------------------------------------------------------------------
message(STATUS "Exporting project")

# Allow use of find_package(MyLib)
export(
    EXPORT
        ${PROJECT_NAME_L}-targets
    FILE
        ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Targets.cmake
    NAMESPACE
        ${PROJECT_NAME}
)

# Register package
export(PACKAGE ${PROJECT_NAME})

message(STATUS "Exporting project - done")

# -----------------------------------------------------------------------------
# Testing
# -----------------------------------------------------------------------------
add_subdirectory(tests)
