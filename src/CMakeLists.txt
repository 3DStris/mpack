add_library(mpack mpack.c ${mpack_SOURCE_DIR}/include/mpack/mpack.h)
set_target_properties(mpack PROPERTIES POSITION_INDEPENDENT_CODE 1)
set_target_properties(mpack PROPERTIES SOVERSION ${mpack_SOVERSION})
add_library(mpack::mpack ALIAS mpack)

target_include_directories(
  mpack
  PUBLIC $<BUILD_INTERFACE:${mpack_SOURCE_DIR}/include>
		 $<INSTALL_INTERFACE:include>)

if(MSVC)
  target_compile_options(mpack PRIVATE $<$<CONFIG:RELEASE>:/Ox> /W4)
else()
  target_compile_options(mpack PRIVATE $<$<CONFIG:RELEASE>:-O3> -Wall -Wextra
                                        -pedantic)
endif()

export(
  TARGETS ${mpack_TARGET_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${mpack_CMAKE_PROJECT_TARGETS_FILE})
install(
  TARGETS ${mpack_TARGET_NAME}
  EXPORT ${mpack_TARGETS_EXPORT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES DESTINATION ${mpack_INCLUDE_INSTALL_DIR})