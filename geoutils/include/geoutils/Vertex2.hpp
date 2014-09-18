#ifndef IONFLUX_GEOUTILS_VERTEX2
#define IONFLUX_GEOUTILS_VERTEX2
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex2.hpp                     Vertex (2D) (header).
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
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Vector2.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Interpolator;
class Vertex2;

namespace XMLUtils
{

class Vertex2XMLFactory;

}

/// Class information for class Vertex2.
class Vertex2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vertex2ClassInfo();
		/// Destructor.
		virtual ~Vertex2ClassInfo();
};

/** Vertex (2D).
 * \ingroup geoutils
 *
 * A vertex in two-dimensional space.
 */
class Vertex2
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// X coordinate.
		double x;
		/// Y coordinate.
		double y;
		
	public:
		/// Origin.
		static const Ionflux::GeoUtils::Vertex2 ORIGIN;
		/// Class information instance.
		static const Vertex2ClassInfo vertex2ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Vertex2 object.
		 */
		Vertex2();
		
		/** Constructor.
		 *
		 * Construct new Vertex2 object.
		 *
		 * \param other Other object.
		 */
		Vertex2(const Ionflux::GeoUtils::Vertex2& other);
		
		/** Constructor.
		 *
		 * Construct new Vertex2 object.
		 *
		 * \param initX Element (X).
		 * \param initY Element (Y).
		 */
		Vertex2(double initX, double initY);
		
		/** Constructor.
		 *
		 * Construct new Vertex2 object.
		 *
		 * \param initCoords Coordinate vector.
		 */
		Vertex2(const Ionflux::ObjectBase::DoubleVector& initCoords);
		
		/** Constructor.
		 *
		 * Construct new Vertex2 object.
		 *
		 * \param initCoords Coordinate vector.
		 */
		Vertex2(const Ionflux::GeoUtils::Vector2& initCoords);
		
		/** Destructor.
		 *
		 * Destruct Vertex2 object.
		 */
		virtual ~Vertex2();
		
		/** Set coordinates.
		 *
		 * Set coordinates from a vector of doubles. If the vector contains 
		 * fewer than the required number of coordinates, the remaining 
		 * coordinates will be left alone.
		 *
		 * \param newCoords Coordinate vector.
		 */
		virtual void setCoords(const Ionflux::ObjectBase::DoubleVector& 
		newCoords);
		
		/** Set coordinates.
		 *
		 * Set coordinates from a vector.
		 *
		 * \param newCoords Coordinate vector.
		 */
		virtual void setCoords(const Ionflux::GeoUtils::Vector2& newCoords);
		
		/** Get coordinates.
		 *
		 * Store the coordinates of the vertex in a vector of doubles.
		 *
		 * \param target Target vector.
		 */
		virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) const;
		
		/** Get coordinates.
		 *
		 * Store the coordinates of the vertex in a vector.
		 *
		 * \param target Target vector.
		 */
		virtual void getCoords(Ionflux::GeoUtils::Vector2& target) const;
		
		/** Get coordinate.
		 *
		 * Get the coordinate with the specified index.
		 *
		 * \param index Index.
		 *
		 * \return Element at the specified index.
		 */
		virtual double getCoord(int index) const;
		
		/** Get coordinates as vector.
		 *
		 * Get the coordinates of the vertex as a vector.
		 *
		 * \return Vector.
		 */
		virtual Ionflux::GeoUtils::Vector2 getVector() const;
		
		/** Set coordinate.
		 *
		 * Set the coordinate with the specified index.
		 *
		 * \param index Index.
		 * \param value Value.
		 */
		virtual void setCoord(int index, double value);
		
		/** Interpolate vertices.
		 *
		 * Interpolate the vertex coordinates and the coordinates of the other
		 * vertex using the specified parameter.
		 *
		 * \param other Vertex.
		 * \param t Parameter.
		 * \param interpolator Interpolator.
		 *
		 * \return Interpolated vertex.
		 */
		virtual Ionflux::GeoUtils::Vertex2 interpolate(const 
		Ionflux::GeoUtils::Vertex2& other, double t, 
		Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
		
		/** Comparison (with tolerance): equal.
		 *
		 * Compare the vector with another vector using the specified 
		 * tolerance.
		 *
		 * \param other Vertex.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool eq(const Ionflux::GeoUtils::Vertex2& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Vertex2.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Vertex2& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Vertex.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Vertex2& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Element at specified index.
		 */
		virtual double operator[](int index) const;
		
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
		virtual Ionflux::GeoUtils::Vertex2& operator=(const 
		Ionflux::GeoUtils::Vertex2& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vertex2* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vertex2* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Vertex2* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vertex2 object.
		 *
		 * \param initX Element (X).
		 * \param initY Element (Y).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vertex2* create(double initX, double initY, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vertex2 object.
		 *
		 * \param initCoords Coordinate vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vertex2* create(const 
		Ionflux::ObjectBase::DoubleVector& initCoords, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vertex2 object.
		 *
		 * \param initCoords Coordinate vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vertex2* create(const 
		Ionflux::GeoUtils::Vector2& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
        
		/** Get XML element name.
		 *
		 * Get the XML element name for the object.
		 *
		 * \return XML element name
		 */
		virtual std::string getXMLElementName() const;
        
		/** Get XML attribute data.
		 *
		 * Get a string containing the XML attributes of the object.
		 *
		 * \return XML attribute data
		 */
		virtual std::string getXMLAttributeData() const;
        
        /** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 */
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
        
        /** Load from XML file.
		 *
		 * Initialize the object from an XML file.
		 *
		 * \param fileName file name
		 * \param elementName element name
		 */
		virtual void loadFromXMLFile(const std::string& fileName, const 
		std::string& elementName = "");
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 * 
		 * return XML object factory
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get x coordinate.
		 *
		 * \return Current value of x coordinate.
		 */
		virtual double getX() const;
		
		/** Set x coordinate.
		 *
		 * Set new value of x coordinate.
		 *
		 * \param newX New value of x coordinate.
		 */
		virtual void setX(double newX);
		
		/** Get y coordinate.
		 *
		 * \return Current value of y coordinate.
		 */
		virtual double getY() const;
		
		/** Set y coordinate.
		 *
		 * Set new value of y coordinate.
		 *
		 * \param newY New value of y coordinate.
		 */
		virtual void setY(double newY);
};

}

}

/** \file Vertex2.hpp
 * \brief Vertex (2D) (header).
 */
#endif
