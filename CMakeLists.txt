cmake_minimum_required(VERSION 3.17)

# Set this to On to include the examples in the project to easier build them
option(INCLUDE_HAXE_EXAMPLES "Include the examples in the project" OFF)

project(HaxeWrapper)
set (CMAKE_CXX_STANDARD 11)

if(UNIX AND NOT APPLE)
    set(ARCH "_x64") # @todo: Determine this dynamically
    set(PLATFORM "${CMAKE_CXX_PLATFORM_ID}")
elseif(WIN32)
    set(ARCH "_${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}")
    string(TOLOWER "${ARCH}" ARCH)
    set(PLATFORM "${CMAKE_CXX_PLATFORM_ID}")
elseif(APPLE)
    set(ARCH "")
    set(PLATFORM "MacOS")
endif()

add_custom_target(CopyHaxewrapperForExamples
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/examples/ModioWrapper.hx)

function(add_example EXAMPLE_NAME EXAMPLE_LIST_NAME)
    string(TOLOWER "${PLATFORM}" COMPILE_PLATFORM)

    # ensure that we keep src/Mod
    add_custom_command(OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/src/examples/ModioWrapper.hx
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/src/ModioWrapper.hx ${CMAKE_CURRENT_SOURCE_DIR}/src/examples/ModioWrapper.hx
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/ModioWrapper.hx)

    add_custom_command(
        OUTPUT    ${CMAKE_CURRENT_SOURCE_DIR}/bin/${EXAMPLE_NAME}${CMAKE_EXECUTABLE_SUFFIX}
        COMMAND   haxe
        ARGS      -cp src/examples -main ${EXAMPLE_NAME} -cpp bin -D "${COMPILE_PLATFORM}"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS   HaxeWrapper CopyHaxewrapperForExamples ${CMAKE_CURRENT_SOURCE_DIR}/src/examples/${EXAMPLE_NAME}.hx
        COMMENT   "Building ${EXAMPLE_NAME}")

    add_custom_target(${EXAMPLE_NAME}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bin/${EXAMPLE_NAME}${CMAKE_EXECUTABLE_SUFFIX})

    add_dependencies(${EXAMPLE_NAME} modio HaxeWrapper)

    if(NOT DEFINED ${EXAMPLE_LIST_NAME})
        set(${EXAMPLE_LIST_NAME} ${EXAMPLE_NAME} PARENT_SCOPE)
    else()
        set(${EXAMPLE_LIST_NAME} ${${EXAMPLE_LIST_NAME}} ${EXAMPLE_NAME} PARENT_SCOPE)
    endif()
endfunction()

find_package(Git REQUIRED)

include(FetchContent)
message(STATUS "Fetching modio/SDK from github...")
FetchContent_Declare( ModioSDK
  GIT_REPOSITORY https://github.com/MarkusRannare/SDK.git
  GIT_TAG 93e7a1e9d2a7b52afcd0b06643935057f740f48e # this is 0.12.16-release but with the changes that you can use the cmake project as a subdirectory
)

FetchContent_Populate(ModioSDK)

add_subdirectory( ${modiosdk_SOURCE_DIR} )

include_directories(HaxeWrapper PUBLIC ${modiosdk_SOURCE_DIR}/include)
link_directories(${modiosdk_BINARY_DIR}/lib)

SET(SOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/modioWrapper.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/modioWrapperCallbacks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/modioWrapperObjects.cpp)

add_library(HaxeWrapper ${SOURCE_FILES})
target_include_directories(HaxeWrapper PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(HaxeWrapper modio)

# Ensure that we have the same output directory as we had in the previous setup
set_target_properties(HaxeWrapper
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Ensure that we don't prefix the ndll with lib as we didn't do that in the previous setup
set(CMAKE_SHARED_LIBRARY_PREFIX "")

# Because OUTPUT option may not use generator expressions,
# extract name of file from target's properties.
get_target_property(MODIO_BASENAME modio OUTPUT_NAME)
get_target_property(MODIO_SUFFIX modio SUFFIX)
set(MODIO_FILENAME ${MODIO_BASENAME}${MODIO_SUFFIX})

# make copied file be dependent from one which is build.
# Note, that DEPENDS here creates dependencies both from the target
# and from the file it creates.
add_custom_command(OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/bin/${MODIO_FILENAME}
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:modio> "${CMAKE_CURRENT_SOURCE_DIR}/bin"
        DEPENDS modio)

# Create target which consume the command via DEPENDS.
add_custom_target(copy_files_modio ALL
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/bin/${MODIO_FILENAME})

set_target_properties(HaxeWrapper PROPERTIES
        OUTPUT_NAME "modioWrapper${PLATFORM}${ARCH}"
        SUFFIX ".ndll")

add_dependencies(HaxeWrapper modio)

# Ability to easily build examples
if(INCLUDE_HAXE_EXAMPLES)
    add_example(Ex01_Authentication EXAMPLES)
    add_example(Ex02_BrowseMods EXAMPLES)
    add_example(Ex03_SubscribeToMod EXAMPLES)
    add_example(Ex04_UnsubscribeFromMod EXAMPLES)
    add_example(Ex05_AutomaticDownloads EXAMPLES)
    add_example(Ex06_AddMod EXAMPLES)
    add_example(Ex07_EditMod EXAMPLES)
    add_example(Ex08_GetUserSubscriptions EXAMPLES)
    add_example(Ex09_SetEventListener EXAMPLES)
    add_example(Ex10_InstallDownloadedMods EXAMPLES)
    add_example(Ex11_GetInstalledMods EXAMPLES)

    # Removed the "All examples target, as we get a error when building it that I don't know how to handle:
    # "error : Uncaught exception on main thread: [file_open,C:/Github/HaxeWrapper/bin/obj/msvc19xp/__pch/haxe/hxcpp.cpp]"
    #add_custom_Target(Examples DEPENDS ${EXAMPLES})
endif()
