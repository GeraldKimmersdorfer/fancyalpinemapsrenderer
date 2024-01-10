#############################################################################
# Alpine Terrain Renderer
# Copyright (C) 2023 Adam Celarek <family name at cg tuwien ac at>
# Copyright (C) 2023 Gerald Kimmersdorfer
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
project(alpine-renderer-webgpu_engine LANGUAGES CXX)

#http://localhost:5500/
qt_add_library(webgpu_engine STATIC
    Window.cpp Window.h
)
target_link_libraries(webgpu_engine PUBLIC nucleus Qt::OpenGL)
target_include_directories(webgpu_engine PRIVATE .)

qt_add_resources(webgpu_engine "shaders"
    PREFIX "/webgpu_shaders"
    BASE "shaders/"
    FILES
    shaders/tmp.wgls
)
target_compile_definitions(webgpu_engine PUBLIC ALP_RESOURCES_PREFIX="${CMAKE_CURRENT_SOURCE_DIR}/shaders/")
