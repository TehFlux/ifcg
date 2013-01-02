/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Voxel.i                         Voxel (interface).
 * =========================================================================

 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "geoutils/Voxel.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VoxelClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VoxelClassInfo();
        virtual ~VoxelClassInfo();
};

class Voxel
: public Ionflux::GeoUtils::BoxBoundsItem
{
    public:
        
        Voxel();
		Voxel(const Ionflux::GeoUtils::Voxel& other);
        Voxel(const Ionflux::GeoUtils::Vector3& initIndex, double 
        initEdgeLength = 1., const Ionflux::GeoUtils::Vector3& initOffset =
        Ionflux::GeoUtils::Vector3::ZERO);
        virtual ~Voxel();
        virtual void clear();
        virtual void initBounds();
        virtual std::string getString() const;
        static Ionflux::GeoUtils::Voxel* create(const 
        Ionflux::GeoUtils::Vector3& initIndex, double initEdgeLength = 1., 
        const Ionflux::GeoUtils::Vector3& initOffset = 
        Ionflux::GeoUtils::Vector3::ZERO);
        static void toVertexSet(Ionflux::GeoUtils::BoxBoundsItemSet& 
        source, Ionflux::GeoUtils::Vertex3Set& target);
		virtual Ionflux::GeoUtils::Voxel* copy() const;
		static Ionflux::GeoUtils::Voxel* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Voxel* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setIndex(const Ionflux::GeoUtils::Vector3& newIndex);
        virtual Ionflux::GeoUtils::Vector3 getIndex() const;
        virtual void setEdgeLength(double newEdgeLength);
        virtual double getEdgeLength() const;
        virtual void setOffset(const Ionflux::GeoUtils::Vector3& 
        newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
};

}

}
