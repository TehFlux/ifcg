#ifndef IONFLUX_GEOUTILS_FACECOMPARE
#define IONFLUX_GEOUTILS_FACECOMPARE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FaceCompare.hpp                 Face comparison function object 
 * (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "geoutils/Face.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class FaceCompare.
class FaceCompareClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FaceCompareClassInfo();
		/// Destructor.
		virtual ~FaceCompareClassInfo();
};

/** Face comparison function object.
 * \ingroup geoutils
 *
 * Abstract base class for function objects that compare faces.
 */
class FaceCompare
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Invert order.
		bool invert;
		/// Target comparison object.
		Ionflux::GeoUtils::FaceCompare* target;
		
	public:
		/// Class information instance.
		static const FaceCompareClassInfo faceCompareClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new FaceCompare object.
		 */
		FaceCompare();
		
		/** Constructor.
		 *
		 * Construct new FaceCompare object.
		 *
		 * \param other Other object.
		 */
		FaceCompare(const Ionflux::GeoUtils::FaceCompare& other);
		
		/** Constructor.
		 *
		 * Construct new FaceCompare object.
		 *
		 * \param initInvert Invert order.
		 * \param initTarget Target comparison object.
		 */
		FaceCompare(bool initInvert, Ionflux::GeoUtils::FaceCompare* initTarget =
		0);
		
		/** Destructor.
		 *
		 * Destruct FaceCompare object.
		 */
		virtual ~FaceCompare();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Call operator.
		 *
		 * Compare two faces.
		 *
		 * \param f0 Face (0).
		 * \param f1 Face (1).
		 *
		 * \return \c true if the face f0 goes before the face f1, \c false 
		 * otherwise.
		 */
		virtual bool operator()(Ionflux::GeoUtils::Face* f0, 
		Ionflux::GeoUtils::Face* f1);
		
		/** Compare faces.
		 *
		 * Compare two faces.
		 *
		 * \param f0 Face (0).
		 * \param f1 Face (1).
		 *
		 * \return \c true if the face f0 goes before the face f1, \c false 
		 * otherwise.
		 */
		virtual bool compare(Ionflux::GeoUtils::Face& f0, 
		Ionflux::GeoUtils::Face& f1);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::FaceCompare& operator=(const 
		Ionflux::GeoUtils::FaceCompare& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::FaceCompare* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::FaceCompare* 
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
		static Ionflux::GeoUtils::FaceCompare* 
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
		virtual Ionflux::GeoUtils::FaceCompare* getTarget() const;
		
		/** Set target comparison object.
		 *
		 * Set new value of target comparison object.
		 *
		 * \param newTarget New value of target comparison object.
		 */
		virtual void setTarget(Ionflux::GeoUtils::FaceCompare* newTarget);
};

}

}

/** \file FaceCompare.hpp
 * \brief Face comparison function object (header).
 */
#endif
