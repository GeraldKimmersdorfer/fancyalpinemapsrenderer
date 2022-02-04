/*****************************************************************************
 * Alpine Terrain Builder
 * Copyright (C) 2022 alpinemaps.org
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

#include "srs.h"

constexpr unsigned int cSemiMajorAxis = 6378137;
constexpr double cEarthCircumference = 2 * M_PI * cSemiMajorAxis;
constexpr double cOriginShift = cEarthCircumference / 2.0;


srs::Bounds srs::tile_bounds(const Tile& tile)
{
  const auto width_of_a_tile = cEarthCircumference / srs::number_of_horizontal_tiles_for_zoom_level(tile.zoom_level);
  const auto height_of_a_tile = cEarthCircumference / srs::number_of_vertical_tiles_for_zoom_level(tile.zoom_level);
  glm::dvec2 absolute_min = {-cOriginShift, -cOriginShift};
  const auto min = absolute_min + glm::dvec2{tile.coords.x * width_of_a_tile, tile.coords.y * height_of_a_tile};
  const auto max = min + glm::dvec2{width_of_a_tile, height_of_a_tile};
  return {min, max};
}
