#ifndef IONFLUX_VOLGFX_CONSTANTS
#define IONFLUX_VOLGFX_CONSTANTS
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * constants.hpp                     Constant definitions.
 * ==========================================================================
 *
 * This file is part of IFVG - Ionflux' Volumetric Graphics Library.
 * 
 * IFVG - Ionflux' Volumetric Graphics Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFVG - Ionflux' Volumetric Graphics Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFVG - Ionflux' Volumetric Graphics Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <string>
#include <climits>
#include "ifvg/types.hpp"

namespace Ionflux
{

namespace VolGfx
{

/// Maximum reference count.
const Ionflux::ObjectBase::UInt16 MAX_REF_COUNT = 65535;

/// Tolerance used for comparisons..
const double DEFAULT_TOLERANCE = 1e-6;
/// sqrt(3).
const double SQRT_3 = 1.7320508075688772;
/// Inverse of sqrt(3).
const double SQRT_3_INV = 0.5773502691896258;

/// Separability ID: 6
const Ionflux::VolGfx::SeparabilityID SEPARABILITY_6 = 6;
/// Separability ID: 26
const Ionflux::VolGfx::SeparabilityID SEPARABILITY_26 = 26;

/// Unspecified depth value.
const int DEPTH_UNSPECIFIED = -1;
/// Unspecified color index value.
const int COLOR_INDEX_UNSPECIFIED = -1;

/// Voxelization target: density
const Ionflux::VolGfx::VoxelizationTargetID 
    VOXELIZATION_TARGET_DENSITY = 0;
/// Voxelization target: color/normal
const Ionflux::VolGfx::VoxelizationTargetID 
    VOXELIZATION_TARGET_COLOR_NORMAL = 1;
/// Voxelization target: voxel class
const Ionflux::VolGfx::VoxelizationTargetID 
    VOXELIZATION_TARGET_CLASS = 2;

/// Density: empty
const Ionflux::VolGfx::NodeDataValue DENSITY_EMPTY = 0.;
/// Density: filled
const Ionflux::VolGfx::NodeDataValue DENSITY_FILLED = 1.;

/// Magic syllable: base (VG)
const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_BASE = 0x5647;

/// Voxel class ID: undefined
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_UNDEFINED = 0;
/// Voxel class ID: empty
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_EMPTY = 1;
/// Voxel class ID: filled
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_FILLED = 2;
/// Voxel class ID: inside
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_INSIDE = 4;
/// Voxel class ID: outside
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_OUTSIDE = 8;
/// Voxel class ID: boundary
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_BOUNDARY = 16;
/// Voxel class ID: hit
const Ionflux::VolGfx::VoxelClassID VOXEL_CLASS_HIT = 32;

/// Face mask: undefined.
const Ionflux::VolGfx::FaceMaskInt FACE_UNDEFINED = 0;
/// Face mask: X (0).
const Ionflux::VolGfx::FaceMaskInt FACE_X0 = 1;
/// Face mask: X (1).
const Ionflux::VolGfx::FaceMaskInt FACE_X1 = 2;
/// Face mask: Y (0).
const Ionflux::VolGfx::FaceMaskInt FACE_Y0 = 4;
/// Face mask: Y (1).
const Ionflux::VolGfx::FaceMaskInt FACE_Y1 = 8;
/// Face mask: Z (0).
const Ionflux::VolGfx::FaceMaskInt FACE_Z0 = 16;
/// Face mask: Z (1).
const Ionflux::VolGfx::FaceMaskInt FACE_Z1 = 32;
/// Face mask: all.
const Ionflux::VolGfx::FaceMaskInt FACE_ALL = 63;

/// Leaf status ID: any
const Ionflux::VolGfx::LeafStatusID NODE_ANY = 0;
/// Leaf status ID: leaf node
const Ionflux::VolGfx::LeafStatusID NODE_LEAF = 1;
/// Leaf status ID: non-leaf node
const Ionflux::VolGfx::LeafStatusID NODE_NON_LEAF = 2;

/// Merge policy ID: keep target.
const Ionflux::VolGfx::MergePolicyID MERGE_POLICY_KEEP_TARGET = 0;
/// Merge policy ID: take over source.
const Ionflux::VolGfx::MergePolicyID MERGE_POLICY_TAKE_OVER_SOURCE = 1;

}

}

/** \file constants.hpp
 * \brief Constants (header).
 */
#endif
