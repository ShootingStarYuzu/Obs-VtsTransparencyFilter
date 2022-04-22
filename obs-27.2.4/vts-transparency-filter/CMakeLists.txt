project(vts-transparency-filter)

if(MSVC)
	set(vts-transparency-filter_PLATFORM_DEPS
		w32-pthreads)
endif()

set(vts-transparency-filter_SOURCES
  transparency-filter.c)

if(WIN32)
	set(MODULE_DESCRIPTION "VTS Transparency Filter")
	configure_file(${CMAKE_SOURCE_DIR}/cmake/winrc/obs-module.rc.in vts-transparency-filter.rc)
	list(APPEND vts-transparency-filter_SOURCES
		vts-transparency-filter.rc)
endif()

add_library(vts-transparency-filter MODULE
	${vts-transparency-filter_SOURCES})
target_link_libraries(vts-transparency-filter
	libobs
	${vts-transparency-filter_PLATFORM_DEPS})
set_target_properties(vts-transparency-filter PROPERTIES FOLDER "plugins")

install_obs_plugin_with_data(vts-transparency-filter data)
