# Copyright (C) 2025 by Arm Limited (or its affiliates). All rights reserved.
include_guard(GLOBAL)

# ###
# Find various optional tools
# ###
find_file(CLANG_FORMAT NAMES "clang-format${CMAKE_EXECUTABLE_SUFFIX}"
    NO_CMAKE_FIND_ROOT_PATH)

if(EXISTS ${CLANG_FORMAT})
    execute_process(
        COMMAND "${CLANG_FORMAT}" --version
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        RESULT_VARIABLE _cf_res
        OUTPUT_VARIABLE _cf_out
        ERROR_QUIET)
    string(REGEX REPLACE "[\n\r\t]" " " _cf_out "${_cf_out}")
    string(STRIP "${_cf_out}" _cf_out)

    if(NOT "${_cf_res}" EQUAL 0)
        message(STATUS "Failed to execute '${CLANG_FORMAT} --version'")
        unset(CLANG_FORMAT)
    elseif(NOT "${_cf_out}" MATCHES ".*clang-format version ([^ ]+).*")
        message(STATUS "Failed to understand '${CLANG_FORMAT} --version' output")
        unset(CLANG_FORMAT)
    else()
        string(REGEX REPLACE ".*clang-format version ([^ ]+).*" "\\1" _cf_ver "${_cf_out}")
        message(STATUS "Detected clang-format version '${_cf_ver}'")

        if("${_cf_ver}" VERSION_LESS "18.0.0")
            message(STATUS "The version of clang-format is too old")
            unset(CLANG_FORMAT)
        endif()
    endif()

    unset(_cf_res)
    unset(_cf_out)
    unset(_cf_ver)
endif()

# ###
# Add a custom targets for running clang-format
# ###
if(EXISTS ${CLANG_FORMAT})
    add_custom_target(clang-format
        COMMENT "Run clang-format on all targets")
endif()

# used to get the root project directory
file(REAL_PATH "${CMAKE_CURRENT_LIST_DIR}/.." _cf_root)

function(add_clang_tools)
    if(EXISTS ${CLANG_FORMAT})
        # Determine the name to give the custom target; base it on the folder path relative to the repo root
        file(RELATIVE_PATH _cf_relpath "${_cf_root}" "${CMAKE_CURRENT_SOURCE_DIR}")
        string(REGEX REPLACE "[^0-9A-Za-z_\-]" "-" _cf_name "${_cf_relpath}")

        # find the sources
        file(
            GLOB_RECURSE _cf_srcs
            LIST_DIRECTORIES false
            RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
            CONFIGURE_DEPENDS "*.cpp" "*.hpp")

        # add the task
        add_custom_target(clang-format-${_cf_name}
            COMMAND ${CLANG_FORMAT} -i ${_cf_srcs}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            SOURCES ${_cf_srcs}
            COMMENT "Run clang-format on the sources in ${CMAKE_CURRENT_SOURCE_DIR} for ${_cf_name}")
        add_dependencies(clang-format clang-format-${_cf_name})
    endif()
endfunction()
