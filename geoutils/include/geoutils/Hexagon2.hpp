#ifndef IONFLUX_GEOUTILS_HEXAGON2
#define IONFLUX_GEOUTILS_HEXAGON2
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Hexagon2.hpp                    Hexagon (2D) (header).
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

#include "geoutils/Polygon2.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Hexagon2.
class Hexagon2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Hexagon2ClassInfo();
		/// Destructor.
		virtual ~Hexagon2ClassInfo();
};

/** Hexagon (2D).
 * \ingroup geoutils
 *
 * A hexagon in two-dimensional space.
 */
class Hexagon2
: public Ionflux::GeoUtils::Polygon2
{
	private:
		
	protected:
		/// Base length.
		double baseLength;
		
		/** Create vertices.
		 *
		 * Create the vertices of the hexagon.
		 */
		virtual void createVertices();
		
	public:
		/// Class information instance.
		static const Hexagon2ClassInfo hexagon2ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Hexagon2 object.
		 */
		Hexagon2();
		
		/** Constructor.
		 *
		 * Construct new Hexagon2 object.
		 *
		 * \param other Other object.
		 */
		Hexagon2(const Ionflux::GeoUtils::Hexagon2& other);
		
		/** Constructor.
		 *
		 * Construct new Hexagon2 object.
		 *
		 * \param initBaseLength Base length.
		 */
		Hexagon2(double initBaseLength);
		
		/** Destructor.
		 *
		 * Destruct Hexagon2 object.
		 */
		virtual ~Hexagon2();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Hexagon2& operator=(const 
		Ionflux::GeoUtils::Hexagon2& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Hexagon2* copy() const;
		
		/** Get base length.
		 *
		 * \return Current value of base length.
		 */
		virtual double getBaseLength() const;
		
		/** Set base length.
		 *
		 * Set new value of base length.
		 *
		 * \param newBaseLength New value of base length.
		 */
		virtual void setBaseLength(double newBaseLength);
};

}

}

/** \file Hexagon2.hpp
 * \brief Hexagon (2D) (header).
 */
#endif
