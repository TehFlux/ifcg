#ifndef IONFLUX_GEOUTILS_VERTEX3
#define IONFLUX_GEOUTILS_VERTEX3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex3.hpp                     Vertex (3D) (header).
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

#include "ifobject/types.hpp"
#include "ifmapping/Point.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Vector4.hpp"
#include "geoutils/Matrix3.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "geoutils/TransformableObject.hpp"
#include <iostream>

// forward declarations for types from the Ionflux Object Base System
namespace Ionflux
{

namespace ObjectBase
{

class IFIOContext;

}

}

namespace Ionflux
{

namespace GeoUtils
{

class Interpolator;
class Plane3;
class Vertex3;

namespace XMLUtils
{

class Vertex3XMLFactory;

}

/// Class information for class Vertex3.
class Vertex3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vertex3ClassInfo();
		/// Destructor.
		virtual ~Vertex3ClassInfo();
};

/** Vertex (3D).
 * \ingroup geoutils
 *
 * A vertex in three-dimensional space.
 */
class Vertex3
: public Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// X coordinate.
		double x;
		/// Y coordinate.
		double y;
		/// Z coordinate.
		double z;
		
	public:
		/// Origin.
		static const Ionflux::GeoUtils::Vertex3 ORIGIN;
		/// Class information instance.
		static const Vertex3ClassInfo vertex3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		/// Magic syllable (object, VE).
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_OBJECT;
		
		/** Constructor.
		 *
		 * Construct new Vertex3 object.
		 */
		Vertex3();
		
		/** Constructor.
		 *
		 * Construct new Vertex3 object.
		 *
		 * \param other Other object.
		 */
		Vertex3(const Ionflux::GeoUtils::Vertex3& other);
		
		/** Constructor.
		 *
		 * Construct new Vertex3 object.
		 *
		 * \param initX Element (X).
		 * \param initY Element (Y).
		 * \param initZ Element (Z).
		 */
		Vertex3(double initX, double initY, double initZ);
		
		/** Constructor.
		 *
		 * Construct new Vertex3 object.
		 *
		 * \param initCoords Coordinate vector.
		 */
		Vertex3(const Ionflux::ObjectBase::DoubleVector& initCoords);
		
		/** Constructor.
		 *
		 * Construct new Vertex3 object.
		 *
		 * \param initCoords Coordinate vector.
		 */
		Vertex3(const Ionflux::GeoUtils::Vector3& initCoords);
		
		/** Constructor.
		 *
		 * Construct new Vertex3 object.
		 *
		 * \param initCoords Coordinate vector.
		 */
		Vertex3(const Ionflux::GeoUtils::Vector4& initCoords);
		
		/** Constructor.
		 *
		 * Construct new Vertex3 object.
		 *
		 * \param initCoords Point.
		 */
		Vertex3(const Ionflux::Mapping::Point& initCoords);
		
		/** Destructor.
		 *
		 * Destruct Vertex3 object.
		 */
		virtual ~Vertex3();
		
		/** Set coordinates.
		 *
		 * Set coordinates.
		 *
		 * \param newX Element (X).
		 * \param newY Element (Y).
		 * \param newZ Element (Z).
		 */
		virtual void setCoords(double newX, double newY, double newZ);
		
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
		virtual void setCoords(const Ionflux::GeoUtils::Vector3& newCoords);
		
		/** Set coordinates.
		 *
		 * Set coordinates from a vector.
		 *
		 * \param newCoords Coordinate vector.
		 */
		virtual void setCoords(const Ionflux::GeoUtils::Vector4& newCoords);
		
		/** Get coordinates.
		 *
		 * Store the coordinates of the vertex in a vector of doubles.
		 *
		 * \param target Target vector.
		 */
		virtual void getCoords(Ionflux::ObjectBase::DoubleVector& target) const;
		
		/** Set coordinates.
		 *
		 * Set coordinates from a point.
		 *
		 * \param newCoords Point.
		 */
		virtual void setCoords(const Ionflux::Mapping::Point& newCoords);
		
		/** Get coordinates.
		 *
		 * Store the coordinates of the vertex in a vector.
		 *
		 * \param target Target vector.
		 */
		virtual void getCoords(Ionflux::GeoUtils::Vector3& target) const;
		
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
		virtual Ionflux::GeoUtils::Vector3 getVector() const;
		
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
		virtual Ionflux::GeoUtils::Vertex3 interpolate(const 
		Ionflux::GeoUtils::Vertex3& other, double t, 
		Ionflux::GeoUtils::Interpolator* interpolator = 0) const;
		
		/** Calculate distance to plane.
		 *
		 * Returns the distance of the vertex to the specified plane.
		 *
		 * \param plane Plane.
		 *
		 * \return Distance to plane.
		 */
		virtual double distanceToPlane(const Ionflux::GeoUtils::Plane3& plane) 
		const;
		
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
		virtual bool eq(const Ionflux::GeoUtils::Vertex3& other, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Vertex3.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Vertex3& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Vertex.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Vertex3& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Element at specified index.
		 */
		virtual double operator[](int index) const;
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& translate(const 
		Ionflux::GeoUtils::Vector3& t);
		
		/** Rotate.
		 *
		 * Rotate the object by the specified angle around the specified axis.
		 *
		 * \param phi Angle.
		 * \param axis Axis.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& 
		center(Ionflux::GeoUtils::CenteringMethod method = 
		Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* origin 
		= 0);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for the vertices in the set.
		 *
		 * \return Barycenter vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBarycenter();
		
		/** Get bounds.
		 *
		 * Get the bounds for the vertex set.
		 *
		 * \return Bounds.
		 */
		virtual Ionflux::GeoUtils::Range3 getBounds();
		
		/** Apply transformations.
		 *
		 * Apply transformations that have been accumulated in the 
		 * transformation matrices.
		 *
		 * \param recursive Apply transformations recursively.
		 */
		virtual void applyTransform(bool recursive = false);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object. Note that this applies
		 * the transformation immediately to the vertex coordinates. For 
		 * deferred transformations, use setTransformMatrix() in conjunction 
		 * with applyTransform().
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** View/image transformation.
		 *
		 * Apply a view transformation matrix and an optional image 
		 * transformation matrix to the object. Note that this applies the 
		 * transformation immediately to the vertex coordinates. For deferred 
		 * transformations, use setViewMatrix() and setImageMatrix() in 
		 * conjunction with applyTransform().
		 *
		 * \param view View transformation matrix.
		 * \param image Image transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Vertex3& duplicate();
		
		/** Create point.
		 *
		 * Create a point.
		 *
		 * \return Point.
		 */
		virtual Ionflux::Mapping::Point getPoint() const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get XML data representation.
		 *
		 * Get a representation of the object suitable for use in an XML data 
		 * attribute.
		 *
		 * \return String representation.
		 */
		virtual std::string getXMLData_legacy() const;
		
		/** Get XML representation.
		 *
		 * Get an XML representation of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getXML_legacy() const;
		
		/** Serialize.
		 *
		 * Serialize the object. This creates a string which contains data 
		 * from which the internal state of the object (as supported 
		 * by serialization) can be restored using deserialize().
		 *
		 * \param target where to store the result
		 *
		 * \return \c true on success, \c false otherwise.
		 *
		 * \sa deserialize()
		 */
		virtual bool serialize(std::string& target) const;
		
		/** Deserialize.
		 *
		 * Initialize the object from a serialized representation of its 
		 * internal state. The serialized representation can be obtained 
		 * using serialize().
		 *
		 * \param source serialized data buffer
		 * \param offset position where to start deserialization
		 *
		 * \return offset of remaining data, or DATA_SIZE_INVALID if an error occured.
		 *
		 * \sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, Ionflux::ObjectBase::DataSize offset = 0);
		
		/** Serialize.
		 *
		 * Serialize the object to a stream.
		 *
		 * \param target target stream
		 * \param addMagicWord add magic word
		 *
		 * \return \c true on success, \c false otherwise.
		 *
		 * \sa deserialize()
		 */
		virtual bool serialize(std::ostream& target, bool addMagicWord = true) const;
		
		/** Deserialize.
		 *
		 * Deserialize the object from a stream.
		 *
		 * \param source source stream
		 * \param offset stream position from where to start deserialization
		 * \param checkMagicWord add magic word
		 *
		 * \return offset of remaining data
		 *
		 * \sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
		
		/** Serialize.
		 *
		 * Serialize the object.
		 *
		 * \param ioCtx I/O context
		 * \param addMagicWord add magic word
		 *
		 * \return \c true on success, \c false otherwise.
		 *
		 * \sa deserialize()
		 */
		virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
		
		/** Deserialize.
		 *
		 * Deserialize the object from a stream.
		 *
		 * \param ioCtx I/O context
		 * \param offset stream position from where to start deserialization
		 * \param checkMagicWord add magic word
		 *
		 * \return offset of remaining data
		 *
		 * \sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
		
		/** Get magic syllable (object).
		 *
		 * Get the magic syllable for the object.
		 *
		 * \return magic syllable
		 */
		virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
		
		/** Get magic syllable (base).
		 *
		 * Get the magic syllable for the namespace.
		 *
		 * \return magic syllable
		 */
		virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Vertex3& operator=(const 
		Ionflux::GeoUtils::Vertex3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vertex3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vertex3* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Vertex3* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vertex3 object.
		 *
		 * \param initX Element (X).
		 * \param initY Element (Y).
		 * \param initZ Element (Z).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vertex3* create(double initX, double initY, 
		double initZ, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vertex3 object.
		 *
		 * \param initCoords Coordinate vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::ObjectBase::DoubleVector& initCoords, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vertex3 object.
		 *
		 * \param initCoords Coordinate vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::GeoUtils::Vector3& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vertex3 object.
		 *
		 * \param initCoords Coordinate vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vertex3* create(const 
		Ionflux::GeoUtils::Vector4& initCoords, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Vertex3 object.
		 *
		 * \param initCoords Point.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Vertex3* create(const Ionflux::Mapping::Point& 
		initCoords, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		
		/** Get z coordinate.
		 *
		 * \return Current value of z coordinate.
		 */
		virtual double getZ() const;
		
		/** Set z coordinate.
		 *
		 * Set new value of z coordinate.
		 *
		 * \param newZ New value of z coordinate.
		 */
		virtual void setZ(double newZ);
};

}

}

/** \file Vertex3.hpp
 * \brief Vertex (3D) (header).
 */
#endif
