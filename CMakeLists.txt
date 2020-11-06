cmake_minimum_required(VERSION 3.14)

project("srmtools")

# build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()
# hide other incomplete configurations from Visual Studio
set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE INTERNAL "Active configuration" FORCE)
mark_as_advanced(FORCE CMAKE_CONFIGURATION_TYPES)

# installation
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/INSTALL" CACHE PATH "Installation prefix" FORCE)
endif()
set(CMAKE_INSTALL_MESSAGE LAZY)

set(CMAKE_CXX_STANDARD 17)

# Visual Studio settings
if(MSVC)
    # build MT configuration by default
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    string(REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS_MINSIZEREL}")
    
    # enable multithreaded build
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

    # disable annoying warnings
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# packaging
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_FILE_NAME "srm-tools-0.9")
include(CPack)

macro(SetTargetCategory target category)
	file(GLOB_RECURSE files LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *)
    foreach(i IN LISTS files)
        get_filename_component(source_path "${i}" PATH)
        string(REPLACE "/" "\\" source_path "${source_path}")
        source_group("${source_path}" FILES ${i})
    endforeach()
	
	set_property(TARGET ${target} PROPERTY FOLDER ${category})
endmacro()

add_subdirectory("src")
