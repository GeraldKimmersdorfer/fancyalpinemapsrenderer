 /*****************************************************************************
 * Alpine Renderer
 * Copyright (C) 2024 Gerald Kimmersdorfer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *****************************************************************************/

#include "Window.h"

#include <QTimer>

using webgpu_engine::Window;

Window::Window()
{
    QTimer::singleShot(1, [this]() { emit update_requested(); });
#ifdef ALP_ENABLE_TRACK_OBJECT_LIFECYCLE
    qDebug("webgpu_engine::~Window()");
#endif
}

Window::~Window()
{
#ifdef ALP_ENABLE_TRACK_OBJECT_LIFECYCLE
    qDebug("webgpu_engine::~Window()");
#endif
}

void Window::initialise_gpu()
{
}

void Window::resize_framebuffer(int width, int height)
{
}

void Window::paint(QOpenGLFramebufferObject* framebuffer)
{
}



void Window::set_permissible_screen_space_error(float new_error)
{
}

void Window::update_camera(const nucleus::camera::Definition& new_definition)
{
    emit update_requested();
}

void Window::update_debug_scheduler_stats(const QString& stats)
{
}

void Window::update_gpu_quads(const std::vector<nucleus::tile_scheduler::tile_types::GpuTileQuad>& new_quads, const std::vector<tile::Id>& deleted_quads)
{
}

float Window::depth(const glm::dvec2& normalised_device_coordinates)
{
    return 0.0;
}

glm::dvec3 Window::position(const glm::dvec2& normalised_device_coordinates)
{
    return glm::dvec3(0.0);
}

void Window::deinit_gpu()
{
    emit gpu_ready_changed(false);
}

void Window::set_aabb_decorator(const nucleus::tile_scheduler::utils::AabbDecoratorPtr& new_aabb_decorator)
{
}

void Window::remove_tile(const tile::Id& id)
{
}

nucleus::camera::AbstractDepthTester* Window::depth_tester()
{
    return this;
}
