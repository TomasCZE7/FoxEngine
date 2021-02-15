set(PROJECT_NAME Game)

################################################################################
# Source groups
################################################################################
set(Source_Files
        "src/GameMain.cpp"
        )
source_group("Source Files" FILES ${Source_Files})

set(ALL_FILES
        ${Source_Files}
        )

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Game)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VS_GLOBAL_KEYWORD "Win32Proj"
        )
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        TARGET_NAME_DEBUG        "Game"
        TARGET_NAME_DISTRIBUTION "Game"
        TARGET_NAME_RELEASE      "Game"
        )
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        OUTPUT_DIRECTORY_DEBUG        "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Debug-windows-x86_64/Game/"
        OUTPUT_DIRECTORY_DISTRIBUTION "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Distribution-windows-x86_64/Game/"
        OUTPUT_DIRECTORY_RELEASE      "${CMAKE_CURRENT_SOURCE_DIR}/../bin/Release-windows-x86_64/Game/"
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
        "${CMAKE_CURRENT_SOURCE_DIR}/../FoxEngine/vendor/spdlog/include;"
        "${CMAKE_CURRENT_SOURCE_DIR}/../FoxEngine/src"
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
            /SUBSYSTEM:CONSOLE
            )
endif()

################################################################################
# Dependencies
################################################################################
add_dependencies(${PROJECT_NAME}
        FoxEngine
        )

# Link with other targets.
target_link_libraries(${PROJECT_NAME} PRIVATE
        FoxEngine
        )

