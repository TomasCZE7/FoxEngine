set(PROJECT_NAME FoxEngine)

################################################################################
# Source groups
################################################################################
set(no_group_source_files
        "src/FoxEngine.h"
        )
source_group("" FILES ${no_group_source_files})

set(FoxEngine
        "src/FoxEngine/Application.cpp"
        "src/FoxEngine/Application.h"
        "src/FoxEngine/Core.h"
        "src/FoxEngine/EntryPoint.h"
        "src/FoxEngine/Log.cpp"
        "src/FoxEngine/Log.h"
        )
source_group("FoxEngine" FILES ${FoxEngine})

set(ALL_FILES
        ${no_group_source_files}
        ${FoxEngine}
        )

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE FoxEngine)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG        "FoxEngine"
        TARGET_NAME_DISTRIBUTION "FoxEngine"
        TARGET_NAME_RELEASE      "FoxEngine"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG        "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86_64/FoxEngine/"
        OUTPUT_DIRECTORY_DISTRIBUTION "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Distribution-windows-x86_64/FoxEngine/"
        OUTPUT_DIRECTORY_RELEASE      "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86_64/FoxEngine/"
        )
set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG        "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86_64/FoxEngine"
        ARCHIVE_OUTPUT_DIRECTORY_DISTRIBUTION "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Distribution-windows-x86_64/FoxEngine"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE      "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86_64/FoxEngine"
        )
set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_NAME_DEBUG        "FoxEngine"
        ARCHIVE_OUTPUT_NAME_DISTRIBUTION "FoxEngine"
        ARCHIVE_OUTPUT_NAME_RELEASE      "FoxEngine"
        )
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
        $<$<CONFIG:Debug>:
        MultiThreadedDebug
        >
        $<$<CONFIG:Distribution>:
        MultiThreaded
        >
        $<$<CONFIG:Release>:
        MultiThreaded
        >
        $<$<NOT:$<OR:$<CONFIG:Debug>,$<CONFIG:Distribution>,$<CONFIG:Release>>>:${MSVC_RUNTIME_LIBRARY_DEFAULT}>
        )
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include"
        )

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
        "$<$<CONFIG:Debug>:"
        "FE_DEBUG"
        ">"
        "$<$<CONFIG:Distribution>:"
        "FE_DISTRIBUTION"
        ">"
        "$<$<CONFIG:Release>:"
        "FE_RELEASE"
        ">"
        "FOX_PLATFORM_WINDOWS;"
        "FOX_BUILD_DLL;"
        "UNICODE;"
        "_UNICODE"
        )

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /Od;
            /ZI
            >
            $<$<CONFIG:Distribution>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            $<$<CONFIG:Release>:
            /Gm-;
            /Ox;
            /Oi;
            /GF;
            /Gy;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT}
            >
            /std:c++17;
            /W3;
            ${DEFAULT_CXX_EXCEPTION_HANDLING};
            /Y-
            )
    target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
            /DEBUG;
            /INCREMENTAL
            >
            $<$<CONFIG:Distribution>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
            >
            $<$<CONFIG:Release>:
            /DEBUG:FULL;
            /OPT:REF;
            /OPT:ICF;
            /INCREMENTAL:NO
            >
            /SUBSYSTEM:WINDOWS
            )
endif()

################################################################################
# Post build events
################################################################################
#Copy .dll files into game for testing purposes
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/bin/Debug-windows-x86_64/${PROJECT_NAME}/FoxEngine.dll ${PROJECT_SOURCE_DIR}/bin/Debug-windows-x86_64/Game
        )