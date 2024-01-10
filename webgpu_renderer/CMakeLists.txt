#############################################################################
# Alpine Terrain Renderer
# Copyright (C) 2023 Adam Celarek <family name at cg tuwien ac at>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#############################################################################

cmake_minimum_required(VERSION 3.24)
project(alpine-renderer-webgpu_renderer LANGUAGES CXX C)

qt_add_executable(webgpu_renderer
    main.cpp
    save_image.h
    stb_image_write.h
)

set_target_properties(webgpu_renderer PROPERTIES
    CXX_STANDARD 17
    CXX_EXTENSIONS OFF
    COMPILE_WARNING_AS_ERROR ON
)


#if (MSVC)
#    target_compile_options(webgpu_renderer PRIVATE /W4)
#else()
#    target_compile_options(webgpu_renderer PRIVATE -Wall -Wextra -pedantic)
#endif()

if(XCODE)
    set_target_properties(webgpu_renderer PROPERTIES
        XCODE_GENERATE_SCHEME ON
        XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE "Metal")
endif()

set_target_properties(webgpu_renderer PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

#target_link_libraries(webgpu_renderer PRIVATE glfw)
add_subdirectory(webgpu)
#add_subdirectory(glfw)
#add_subdirectory(glfw3webgpu)
#target_link_libraries(webgpu_renderer PRIVATE webgpu glfw glfw3webgpu)
target_link_libraries(webgpu_renderer PRIVATE webgpu)

target_copy_webgpu_binaries(webgpu_renderer)

target_include_directories(webgpu_renderer PRIVATE .)

qt_add_resources(webgpu_renderer "height_data"
    PREFIX "/map"
    BASE ${renderer_static_data_SOURCE_DIR}
    FILES ${renderer_static_data_SOURCE_DIR}/height_data.atb
)

if (EMSCRIPTEN)
    message(NOTICE "ALP_WWW_INSTALL_DIR = ${ALP_WWW_INSTALL_DIR}")
    configure_file(../site/mascot.png mascot.png COPYONLY)
    set(ALP_INSTALL_FILES
        "$<TARGET_FILE_DIR:webgpu_renderer>/webgpu_renderer.js"
        "$<TARGET_FILE_DIR:webgpu_renderer>/webgpu_renderer.wasm"
        "$<TARGET_FILE_DIR:webgpu_renderer>/webgpu_renderer.html"
        "$<TARGET_FILE_DIR:webgpu_renderer>/qtloader.js"
        "${CMAKE_SOURCE_DIR}/site/mascot.png"
    )
    if (ALP_ENABLE_THREADING)
        list(APPEND ALP_INSTALL_FILES "$<TARGET_FILE_DIR:webgpu_renderer>/webgpu_renderer.worker.js")
    endif()
    install(FILES ${ALP_INSTALL_FILES} DESTINATION ${ALP_WWW_INSTALL_DIR})

    # Add Emscripten-specific link options
    target_link_options(webgpu_renderer PRIVATE
        -sUSE_GLFW=3 # Use Emscripten-provided GLFW
        -sUSE_WEBGPU # Handle WebGPU symbols
        -sASYNCIFY # Required by WebGPU-C++
    )

endif()
