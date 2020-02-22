cmake_minimum_required(VERSION 3.12...3.15)

set(mpack_SOVERSION 1)
set(mpack_VERSION_MAJOR 1)
set(mpack_VERSION_MINOR 0)
set(mpack_VERSION_PATCH 0)

project(
  mpack
  VERSION ${mpack_VERSION_MAJOR}.${mpack_VERSION_MINOR}.${mpack_VERSION_PATCH}
  LANGUAGES C)

include(GNUInstallDirs)
set(mpack_TARGET_NAME                ${PROJECT_NAME})
set(mpack_CONFIG_INSTALL_DIR         "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(mpack_INCLUDE_INSTALL_DIR        "${CMAKE_INSTALL_INCLUDEDIR}")
set(mpack_TARGETS_EXPORT_NAME        "${PROJECT_NAME}Targets")
set(mpack_CMAKE_CONFIG_TEMPLATE      "cmake/${PROJECT_NAME}Config.cmake.in")
set(mpack_CMAKE_CONFIG_DIR           "${CMAKE_CURRENT_BINARY_DIR}")
set(mpack_CMAKE_VERSION_CONFIG_FILE  "${mpack_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(mpack_CMAKE_PROJECT_CONFIG_FILE  "${mpack_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(mpack_CMAKE_PROJECT_TARGETS_FILE "${mpack_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")
set(mpack_INCLUDE_BUILD_DIR		  "${PROJECT_SOURCE_DIR}/include/")

add_subdirectory(src)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${mpack_CMAKE_VERSION_CONFIG_FILE}
  VERSION ${PACKAGE_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_file(${mpack_CMAKE_CONFIG_TEMPLATE}
               ${mpack_CMAKE_PROJECT_CONFIG_FILE} @ONLY)
install(DIRECTORY ${mpack_INCLUDE_BUILD_DIR}
        DESTINATION ${mpack_INCLUDE_INSTALL_DIR})
install(
  FILES ${mpack_CMAKE_PROJECT_CONFIG_FILE} ${mpack_CMAKE_VERSION_CONFIG_FILE}		
  DESTINATION ${mpack_CONFIG_INSTALL_DIR})

export(PACKAGE ${PROJECT_NAME})

install(
  EXPORT ${mpack_TARGETS_EXPORT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${mpack_CONFIG_INSTALL_DIR})