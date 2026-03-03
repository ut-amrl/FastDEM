// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Ikhyeon Cho <tre0430@korea.ac.kr>

/*
 * inpainting.hpp
 *
 * Iterative neighbor averaging for filling NaN holes in height maps.
 *
 *  Created on: Dec 2024
 *      Author: Ikhyeon Cho
 *       Institute: Korea Univ. ISR (Intelligent Systems & Robotics) Lab
 *       Email: tre0430@korea.ac.kr
 */

#ifndef FASTDEM_POSTPROCESS_INPAINTING_HPP
#define FASTDEM_POSTPROCESS_INPAINTING_HPP

#include "fastdem/elevation_map.hpp"

namespace fastdem {

namespace layer {
constexpr auto elevation_inpainted = "elevation_inpainted";
}  // namespace layer

/**
 * @brief Fills NaN holes in elevation using neighbor averaging.
 *
 * @param map Height map to process
 * @param max_iterations Maximum number of fill passes (default: 3)
 * @param min_valid_neighbors Minimum valid neighbors to fill a cell (default: 2)
 * @param inplace If true, writes to elevation layer directly.
 *                If false, writes to elevation_inpainted layer (original unchanged).
 * @param fill_nan If true, fills any remaining NaNs with fill_nan_value at the end.
 * @param fill_nan_value Value to assign to remaining NaNs (e.g. vehicle height [m]).
 */
void applyInpainting(ElevationMap& map, int max_iterations = 3,
                     int min_valid_neighbors = 2, bool inplace = false,
                     bool fill_nan = false, float fill_nan_value = 0.0f);

}  // namespace fastdem

#endif  // FASTDEM_POSTPROCESS_INPAINTING_HPP
