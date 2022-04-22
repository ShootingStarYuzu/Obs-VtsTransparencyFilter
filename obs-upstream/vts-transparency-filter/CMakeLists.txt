project(vts-transparency-filter)

add_library(vts-transparency-filter MODULE)
add_library(OBS::vts-transparency-filter ALIAS vts-transparency-filter)

target_sources(
  vts-transparency-filter
  PRIVATE transparency-filter.c
  PRIVATE data/transparency_filter.effect)

get_target_property(_SOURCES vts-transparency-filter SOURCES)
set(_FILTERS ${_SOURCES})
list(FILTER _FILTERS INCLUDE REGEX ".*\\.effect")
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Effect Files"
  FILES ${_FILTERS})

target_link_libraries(vts-transparency-filter PRIVATE OBS::libobs)
set_target_properties(vts-transparency-filter PROPERTIES FOLDER "plugins" PREFIX "")

if(OS_WINDOWS)
  if(MSVC)
    target_link_libraries(vts-transparency-filter PRIVATE OBS::w32-pthreads)
  endif()

  set(MODULE_DESCRIPTION "VTS Transparency Filter")
  configure_file(${CMAKE_SOURCE_DIR}/cmake/bundle/windows/obs-module.rc.in
                 vts-transparency-filter.rc)
  target_sources(vts-transparency-filter PRIVATE vts-transparency-filter.rc)
endif()

setup_plugin_target(vts-transparency-filter)
