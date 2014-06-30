#ifndef IONFLUX_GEOUTILS_POLYGON3COMPARE
#define IONFLUX_GEOUTILS_POLYGON3COMPARE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3Compare.hpp             Polygon comparison function object 
 * (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Polygon3.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Polygon3Compare.
class Polygon3CompareClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Polygon3CompareClassInfo();
		/// Destructor.
		virtual ~Polygon3CompareClassInfo();
};

/** Polygon comparison function object.
 * \ingroup geoutils
 *
 * Abstract base class for function objects that compare polygons.
 */
class Polygon3Compare
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Invert order.
		bool invert;
		/// Target comparison object.
		Ionflux::GeoUtils::Polygon3Compare* target;
		
	public:
		/// Class information instance.
		static const Polygon3CompareClassInfo polygon3CompareClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Polygon3Compare object.
		 */
		Polygon3Compare();
		
		/** Constructor.
		 *
		 * Construct new Polygon3Compare object.
		 *
		 * \param other Other object.
		 */
		Polygon3Compare(const Ionflux::GeoUtils::Polygon3Compare& other);
		
		/** Constructor.
		 *
		 * Construct new Polygon3Compare object.
		 *
		 * \param initInvert Invert order.
		 * \param initTarget Target comparison object.
		 */
		Polygon3Compare(bool initInvert, Ionflux::GeoUtils::Polygon3Compare* 
		initTarget = 0);
		
		/** Destructor.
		 *
		 * Destruct Polygon3Compare object.
		 */
		virtual ~Polygon3Compare();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Call operator.
		 *
		 * Compare two polygons.
		 *
		 * \param p0 Polygon (0).
		 * \param p1 Polygon (1).
		 *
		 * \return \c true if the polygon p0 goes before the polygon p1, \c false
		 * otherwise.
		 */
		virtual bool operator()(Ionflux::GeoUtils::Polygon3* p0, 
		Ionflux::GeoUtils::Polygon3* p1);
		
		/** Compare polygons.
		 *
		 * Compare two polygons.
		 *
		 * \param p0 Polygon (0).
		 * \param p1 Polygon (1).
		 *
		 * \return \c true if the polygon p0 goes before the polygon p1, \c false
		 * otherwise.
		 */
		virtual bool compare(Ionflux::GeoUtils::Polygon3& p0, 
		Ionflux::GeoUtils::Polygon3& p1);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Polygon3Compare& operator=(const 
		Ionflux::GeoUtils::Polygon3Compare& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Compare* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Polygon3Compare* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::GeoUtils::Polygon3Compare* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get invert order.
		 *
		 * \return Current value of invert order.
		 */
		virtual bool getInvert() const;
		
		/** Set invert order.
		 *
		 * Set new value of invert order.
		 *
		 * \param newInvert New value of invert order.
		 */
		virtual void setInvert(bool newInvert);
		
		/** Get target comparison object.
		 *
		 * \return Current value of target comparison object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Compare* getTarget() const;
		
		/** Set target comparison object.
		 *
		 * Set new value of target comparison object.
		 *
		 * \param newTarget New value of target comparison object.
		 */
		virtual void setTarget(Ionflux::GeoUtils::Polygon3Compare* newTarget);
};

}

}

/** \file Polygon3Compare.hpp
 * \brief Polygon comparison function object (header).
 */
#endif
