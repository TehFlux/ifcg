#ifndef IONFLUX_VOLGFX_SERIALIZE
#define IONFLUX_VOLGFX_SERIALIZE
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * serialize.hpp                        Serialization (header).
 * =========================================================================
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
#include "ifobject/types.hpp"
#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"

namespace Ionflux
{

namespace VolGfx
{

/// Pack node location code.
void pack(
    const Ionflux::VolGfx::NodeLoc& source, 
    std::string& target, bool append = true);

/// Unpack node location code.
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeLoc& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

/// Pack node child mask.
void pack(
    const Ionflux::VolGfx::NodeChildMask& source, 
    std::string& target, bool append = true);

/// Unpack node child mask.
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeChildMask& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

/// Pack node location code (3D).
void pack(
    const Ionflux::VolGfx::NodeLoc3& source, 
    std::string& target, bool append = true);

/// Unpack node location code (3D).
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeLoc3& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

/// Pack node data implementation.
void pack(
    const Ionflux::VolGfx::NodeDataImpl& source, 
    std::string& target, bool append = true);

/// Unpack node data implementation.
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeDataImpl& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

/// Pack node implementation.
void pack(
    const Ionflux::VolGfx::NodeImpl& source, 
    std::string& target, bool append = true);

/// Unpack node implementation.
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeImpl& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

/// Pack node implementation hierarchy header.
void pack(
    const Ionflux::VolGfx::NodeImplHierarchyHeader& source, 
    std::string& target, bool append = true);

/// Unpack node implementation hierarchy header.
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeImplHierarchyHeader& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

/// Pack voxel data (inside/outside/boundary).
void pack(
    const Ionflux::VolGfx::VoxelDataIOB& source, 
    std::string& target, bool append = true);

/// Unpack voxel data (inside/outside/boundary).
Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::VoxelDataIOB& target, 
    Ionflux::ObjectBase::DataSize offset = 0);

}

}

/** \file serialize.hpp
 * \brief Serialization (header).
 */
#endif
