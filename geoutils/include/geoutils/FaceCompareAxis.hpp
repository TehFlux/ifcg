#ifndef IONFLUX_GEOUTILS_FACECOMPAREAXIS
#define IONFLUX_GEOUTILS_FACECOMPAREAXIS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FaceCompareAxis.hpp             Face comparison function object: Axis 
 * coordinate (header).
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
#include "geoutils/FaceCompare.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class FaceCompareAxis.
class FaceCompareAxisClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FaceCompareAxisClassInfo();
		/// Destructor.
		virtual ~FaceCompareAxisClassInfo();
};

/** Face comparison function object: Axis coordinate.
 * \ingroup geoutils
 *
 * A function object that compares faces based on a coordinate of their 
 * barycenter.
 */
class FaceCompareAxis
: public Ionflux::GeoUtils::FaceCompare
{
	private:
		
	protected:
		/// Axis.
		Ionflux::GeoUtils::AxisID axis;
		
	public:
		/// Class information instance.
		static const FaceCompareAxisClassInfo faceCompareAxisClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new FaceCompareAxis object.
		 */
		FaceCompareAxis();
		
		/** Constructor.
		 *
		 * Construct new FaceCompareAxis object.
		 *
		 * \param other Other object.
		 */
		FaceCompareAxis(const Ionflux::GeoUtils::FaceCompareAxis& other);
		
		/** Constructor.
		 *
		 * Construct new FaceCompareAxis object.
		 *
		 * \param initAxis Axis.
		 * \param initInvert Invert order.
		 */
		FaceCompareAxis(Ionflux::GeoUtils::AxisID initAxis, bool initInvert = 
		true);
		
		/** Destructor.
		 *
		 * Destruct FaceCompareAxis object.
		 */
		virtual ~FaceCompareAxis();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
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
		
		/** Create comparison function.
		 *
		 * Create a comparison function object.
		 *
		 * \param initAxis Axis.
		 * \param initInvert Invert order.
		 *
		 * \return New comparison function object.
		 */
		static Ionflux::GeoUtils::FaceCompareAxis* 
		create(Ionflux::GeoUtils::AxisID initAxis, bool initInvert = true);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::FaceCompareAxis& operator=(const 
		Ionflux::GeoUtils::FaceCompareAxis& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::FaceCompareAxis* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::FaceCompareAxis* 
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
		static Ionflux::GeoUtils::FaceCompareAxis* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get axis.
		 *
		 * \return Current value of axis.
		 */
		virtual Ionflux::GeoUtils::AxisID getAxis() const;
		
		/** Set axis.
		 *
		 * Set new value of axis.
		 *
		 * \param newAxis New value of axis.
		 */
		virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
};

}

}

/** \file FaceCompareAxis.hpp
 * \brief Face comparison function object: Axis coordinate (header).
 */
#endif
