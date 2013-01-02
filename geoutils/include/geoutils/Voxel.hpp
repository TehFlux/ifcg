#ifndef IONFLUX_GEOUTILS_VOXEL
#define IONFLUX_GEOUTILS_VOXEL
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Voxel.hpp                       Voxel (header).
 * =========================================================================
 *
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

#include "ifobject/types.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "geoutils/BoxBoundsItem.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Voxel.
class VoxelClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		VoxelClassInfo();
		/// Destructor.
		virtual ~VoxelClassInfo();
};

/** Voxel.
 * \ingroup geoutils
 *
 * A voxel.
 */
class Voxel
: public Ionflux::GeoUtils::BoxBoundsItem
{
	private:
		
	protected:
		/// index.
		Ionflux::GeoUtils::Vector3 index;
		/// edge length.
		double edgeLength;
		/// offset.
		Ionflux::GeoUtils::Vector3 offset;
		
	public:
		/// Class information instance.
		static const VoxelClassInfo voxelClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Voxel object.
		 */
		Voxel();
		
		/** Constructor.
		 *
		 * Construct new Voxel object.
		 *
		 * \param other Other object.
		 */
		Voxel(const Ionflux::GeoUtils::Voxel& other);
		
		/** Constructor.
		 *
		 * Construct new Voxel object.
		 *
		 * \param initIndex index.
		 * \param initEdgeLength edge length.
		 * \param initOffset offset.
		 */
		Voxel(const Ionflux::GeoUtils::Vector3& initIndex, double initEdgeLength 
		= 1., const Ionflux::GeoUtils::Vector3& initOffset = 
		Ionflux::GeoUtils::Vector3::ZERO);
		
		/** Destructor.
		 *
		 * Destruct Voxel object.
		 */
		virtual ~Voxel();
		
		/** Clear item.
		 *
		 * Clears the bounds data of the item.
		 */
		virtual void clear();
		
		/** Initialize bounds.
		 *
		 * Initialize the bounds of the voxel from the index, edge length and 
		 * offset properties.
		 */
		virtual void initBounds();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Create voxel.
		 *
		 * Create a voxel.
		 *
		 * \param initIndex index.
		 * \param initEdgeLength edge length.
		 * \param initOffset offset.
		 *
		 * \return New voxel.
		 */
		static Ionflux::GeoUtils::Voxel* create(const Ionflux::GeoUtils::Vector3&
		initIndex, double initEdgeLength = 1., const Ionflux::GeoUtils::Vector3& 
		initOffset = Ionflux::GeoUtils::Vector3::ZERO);
		
		/** Convert voxels to a vertices.
		 *
		 * Convert voxels in the box bounds item set to vertices. The center 
		 * of the voxel is taken as the vertex position..
		 *
		 * \param source set of voxels.
		 * \param target vertex set.
		 */
		static void toVertexSet(Ionflux::GeoUtils::BoxBoundsItemSet& source, 
		Ionflux::GeoUtils::Vertex3Set& target);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Voxel& operator=(const 
		Ionflux::GeoUtils::Voxel& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Voxel* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Voxel* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::GeoUtils::Voxel* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get index.
		 *
		 * \return Current value of index.
		 */
		virtual Ionflux::GeoUtils::Vector3 getIndex() const;
		
		/** Set index.
		 *
		 * Set new value of index.
		 *
		 * \param newIndex New value of index.
		 */
		virtual void setIndex(const Ionflux::GeoUtils::Vector3& newIndex);
		
		/** Get edge length.
		 *
		 * \return Current value of edge length.
		 */
		virtual double getEdgeLength() const;
		
		/** Set edge length.
		 *
		 * Set new value of edge length.
		 *
		 * \param newEdgeLength New value of edge length.
		 */
		virtual void setEdgeLength(double newEdgeLength);
		
		/** Get offset.
		 *
		 * \return Current value of offset.
		 */
		virtual Ionflux::GeoUtils::Vector3 getOffset() const;
		
		/** Set offset.
		 *
		 * Set new value of offset.
		 *
		 * \param newOffset New value of offset.
		 */
		virtual void setOffset(const Ionflux::GeoUtils::Vector3& newOffset);
};

}

}

/** \file Voxel.hpp
 * \brief Voxel (header).
 */
#endif
