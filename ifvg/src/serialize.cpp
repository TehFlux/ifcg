/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * serialize.hpp                        Serialization (implementation).
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
#include <sstream>
#include "ifobject/serialize.hpp"
#include "ifobject/utils.hpp"
#include "ifvg/utils.hpp"
#include "ifvg/serialize.hpp"
#include "ifvg/Node.hpp"
#include "ifvg/IFVGError.hpp"

namespace Ionflux
{

namespace VolGfx
{

void pack(
    const Ionflux::VolGfx::NodeLoc& source, 
    std::string& target, bool append)
{
    Ionflux::ObjectBase::pack(static_cast<LocInt>(
        source.to_ulong()), target, append);
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeLoc& target, Ionflux::ObjectBase::DataSize offset)
{
    LocInt t0;
    Ionflux::ObjectBase::DataSize o0 = 
        Ionflux::ObjectBase::unpack(source, t0, offset);
    target = t0;
    return o0;
}

void pack(
    const Ionflux::VolGfx::NodeChildMask& source, 
    std::string& target, bool append)
{
    Ionflux::ObjectBase::pack(static_cast<ChildMaskInt>(
        source.to_ulong()), target, append);
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeChildMask& target, 
    Ionflux::ObjectBase::DataSize offset)
{
    ChildMaskInt t0;
    int o0 = Ionflux::ObjectBase::unpack(source, t0, offset);
    target = t0;
    return o0;
}

void pack(
    const Ionflux::VolGfx::NodeLoc3& source, 
    std::string& target, bool append)
{
    std::string t0;
    pack(source.x, t0, true);
    pack(source.y, t0, true);
    pack(source.z, t0, true);
    if (append)
        target.append(t0);
    else
        target = t0;
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeLoc3& target, Ionflux::ObjectBase::DataSize offset)
{
    Ionflux::ObjectBase::DataSize o0 = unpack(source, target.x, offset);
    o0 = unpack(source, target.y, o0);
    o0 = unpack(source, target.z, o0);
    return o0;
}

void pack(
    const Ionflux::VolGfx::NodeDataImpl& source, 
    std::string& target, bool append)
{
    std::string t0;
    Ionflux::ObjectBase::pack(source.type, t0, true);
    if ((source.type == Node::DATA_TYPE_DENSITY) 
        || (source.type == Node::DATA_TYPE_COLOR_RGBA) 
        || (source.type == Node::DATA_TYPE_DISTANCE_8) 
        || (source.type == Node::DATA_TYPE_COLOR_NORMAL))
    {
        // array data types (including density value)
        NodeDataValue* d0 = static_cast<NodeDataValue*>(source.data);
        Ionflux::ObjectBase::nullPointerCheck(d0, 
            "pack", "Node data value");
        Ionflux::ObjectBase::DataSize n0 = 
            Node::getDataTypeNumElements(source.type);
        for (Ionflux::ObjectBase::DataSize i = 0; i < n0; i++)
            Ionflux::ObjectBase::pack(d0[i], t0, true);
    } else
    if (source.type == Node::DATA_TYPE_VOXEL_CLASS)
    {
        // voxel class
        VoxelClassID c0;
        unpackVoxelClass(source.data, c0);
        Ionflux::ObjectBase::pack(c0, t0, true);
    } else
    if (source.type == Node::DATA_TYPE_VOXEL_IOB)
    {
        // voxel inside/outside/boundary
        VoxelDataIOB* d0 = static_cast<VoxelDataIOB*>(source.data);
        Ionflux::ObjectBase::nullPointerCheck(d0, "pack", 
            "Voxel data (inside/outside/boundary)");
        pack(*d0, t0, true);
    } else
    if (source.type != Node::DATA_TYPE_NULL)
    {
        std::ostringstream status;
        status << "[pack] Node data packing not implemented for type: " 
            << Node::getDataTypeString(source.type) << " (" 
            << source.type << ")";
        throw IFVGError(status.str());
    }
    if (append)
        target.append(t0);
    else
        target = t0;
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeDataImpl& target, 
    Ionflux::ObjectBase::DataSize offset)
{
    if (target.data != 0)
        Node::clearDataImpl(&target);
    NodeDataType t0 = Node::DATA_TYPE_UNKNOWN;
    Ionflux::ObjectBase::DataSize o0 = 
        Ionflux::ObjectBase::unpack(source, t0, offset);
    target.type = t0;
    target.data = 0;
    if ((t0 == Node::DATA_TYPE_DENSITY) 
        || (t0 == Node::DATA_TYPE_COLOR_RGBA) 
        || (t0 == Node::DATA_TYPE_DISTANCE_8) 
        || (t0 == Node::DATA_TYPE_COLOR_NORMAL))
    {
        // array data types (including density value)
        Ionflux::ObjectBase::DataSize n0 = 
            Node::getDataTypeNumElements(t0);
        NodeDataValue* d0 = 0;
        if (n0 == 1)
            d0 = new NodeDataValue;
        else
            d0 = new NodeDataValue[n0];
        Ionflux::ObjectBase::nullPointerCheck(d0, 
            "unpack", "Node data value");
        for (Ionflux::ObjectBase::DataSize i = 0; i < n0; i++)
            o0 = Ionflux::ObjectBase::unpack(source, d0[i], o0);
        target.data = d0;
    } else
    if (t0 == Node::DATA_TYPE_VOXEL_CLASS)
    {
        // voxel class
        VoxelClassID c0;
        Ionflux::ObjectBase::unpack(source, c0, o0);
        packVoxelClass(c0, target.data);
    } else
    if (t0 == Node::DATA_TYPE_VOXEL_IOB)
    {
        // voxel inside/outside/boundary
        VoxelDataIOB* d0 = Ionflux::ObjectBase::create<VoxelDataIOB>(
            "unpack", "Voxel data (inside/outside/boundary)");
        unpack(source, *d0, o0);
        target.data = d0;
    } else
    if (t0 != Node::DATA_TYPE_NULL)
    {
        std::ostringstream status;
        status << "[unpack] Node data unpacking not implemented for type: " 
            << Node::getDataTypeString(t0) << " (" 
            << static_cast<int>(t0) << ")";
        throw IFVGError(status.str());
    }
    return o0;
}

void pack(
    const Ionflux::VolGfx::NodeImpl& source, 
    std::string& target, bool append)
{
    std::string t0;
    // NOTE: skip refCount because packing it does not make much sense
    pack(source.loc, t0, true);
    pack(source.valid, t0, true);
    pack(source.leaf, t0, true);
    // NOTE: pointers are stored as 64-bit integers
    Ionflux::ObjectBase::pack(reinterpret_cast<
        Ionflux::ObjectBase::UInt64>(source.parent), t0, true);
    Ionflux::ObjectBase::pack(reinterpret_cast<
        Ionflux::ObjectBase::UInt64>(source.data), t0, true);
    Ionflux::ObjectBase::pack(reinterpret_cast<
        Ionflux::ObjectBase::UInt64>(source.child), t0, true);
    if (append)
        target.append(t0);
    else
        target = t0;
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeImpl& target, 
    Ionflux::ObjectBase::DataSize offset)
{
    // NOTE: skip refCount because unpacking it does not make much sense
    Ionflux::ObjectBase::DataSize o0 = unpack(source, target.loc, offset);
    o0 = unpack(source, target.valid, o0);
    o0 = unpack(source, target.leaf, o0);
    Ionflux::ObjectBase::UInt64 t0;
    o0 = Ionflux::ObjectBase::unpack(source, t0, o0);
    target.parent = reinterpret_cast<NodeImpl*>(t0);
    o0 = Ionflux::ObjectBase::unpack(source, t0, o0);
    target.data = reinterpret_cast<NodeDataImpl*>(t0);
    o0 = Ionflux::ObjectBase::unpack(source, t0, o0);
    target.child = reinterpret_cast<NodeImpl*>(t0);
    return o0;
}

void pack(
    const Ionflux::VolGfx::NodeImplHierarchyHeader& source, 
    std::string& target, bool append)
{
    std::string t0;
    Ionflux::ObjectBase::pack(source.poMapOffset, t0, true);
    Ionflux::ObjectBase::pack(source.implArrayStride, t0, true);
    Ionflux::ObjectBase::pack(source.implSize, t0, true);
    Ionflux::ObjectBase::pack(source.dataImplSize, t0, true);
    Ionflux::ObjectBase::pack(source.dataValueSize, t0, true);
    Ionflux::ObjectBase::pack(source.rootNodeDepth, t0, true);
    Ionflux::ObjectBase::pack(
        reinterpret_cast<Ionflux::ObjectBase::UInt64>(
            source.rootNodePointer), t0, true);
    if (append)
        target.append(t0);
    else
        target = t0;
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::NodeImplHierarchyHeader& target, 
    Ionflux::ObjectBase::DataSize offset)
{
    Ionflux::ObjectBase::DataSize o0 = Ionflux::ObjectBase::unpack(
        source, target.poMapOffset, offset);
    o0 = Ionflux::ObjectBase::unpack(source, target.implArrayStride, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.implSize, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.dataImplSize, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.dataValueSize, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.rootNodeDepth, o0);
    Ionflux::ObjectBase::UInt64 rp0;
    o0 = Ionflux::ObjectBase::unpack(source, rp0, o0);
    target.rootNodePointer = 
        reinterpret_cast<Ionflux::ObjectBase::GenericPointer>(rp0);
    return o0;
}

void pack(
    const Ionflux::VolGfx::VoxelDataIOB& source, 
    std::string& target, bool append)
{
    std::string t0;
    Ionflux::ObjectBase::pack(source.voxelClass, t0, true);
    Ionflux::ObjectBase::pack(source.numInts0, t0, true);
    Ionflux::ObjectBase::pack(source.numInts1, t0, true);
    Ionflux::ObjectBase::pack(source.votesInside, t0, true);
    Ionflux::ObjectBase::pack(source.votesOutside, t0, true);
    Ionflux::ObjectBase::pack(source.boundaryFaces, t0, true);
    Ionflux::ObjectBase::pack(source.wallThicknessX, t0, true);
    Ionflux::ObjectBase::pack(source.wallThicknessY, t0, true);
    Ionflux::ObjectBase::pack(source.wallThicknessZ, t0, true);
    Ionflux::ObjectBase::pack(source.color, t0, true);
    if (append)
        target.append(t0);
    else
        target = t0;
}

Ionflux::ObjectBase::DataSize unpack(const std::string& source, 
    Ionflux::VolGfx::VoxelDataIOB& target, 
    Ionflux::ObjectBase::DataSize offset)
{
    Ionflux::ObjectBase::DataSize o0 = Ionflux::ObjectBase::unpack(
        source, target.voxelClass, offset);
    o0 = Ionflux::ObjectBase::unpack(source, target.numInts0, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.numInts1, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.votesInside, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.votesOutside, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.boundaryFaces, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.wallThicknessX, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.wallThicknessY, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.wallThicknessZ, o0);
    o0 = Ionflux::ObjectBase::unpack(source, target.color, o0);
    return o0;
}

}

}

/** \file serialize.cpp
 * \brief Serialization (implementation).
 */
