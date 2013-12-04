#ifndef IONFLUX_GEOUTILS_POLYGON3SET
#define IONFLUX_GEOUTILS_POLYGON3SET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3Set.hpp                 Polygon set (3D) (header).
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
#include "geoutils/Range3.hpp"
#include "geoutils/Polygon3CompareAxis.hpp"
#include "geoutils/SVGImageProperties.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3;

namespace XMLUtils
{

class Polygon3SetXMLFactory;

}

/// Class information for class Polygon3Set.
class Polygon3SetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Polygon3SetClassInfo();
		/// Destructor.
		virtual ~Polygon3SetClassInfo();
};

/** Polygon set (3D).
 * \ingroup geoutils
 *
 * A set of Polygons in three-dimensional space.
 */
class Polygon3Set
: public Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// Polygon vector.
		std::vector<Ionflux::GeoUtils::Polygon3*> polys;
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the polygon set.
		 */
		virtual void recalculateBounds();
		
	public:
		/// Polygon comparison function: X axis.
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_X;
		/// Polygon comparison function: Y axis.
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_Y;
		/// Polygon comparison function: Z axis.
		static const Ionflux::GeoUtils::Polygon3CompareAxis COMPARE_AXIS_Z;
		/// Class information instance.
		static const Polygon3SetClassInfo polygon3SetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Polygon3Set object.
		 */
		Polygon3Set();
		
		/** Constructor.
		 *
		 * Construct new Polygon3Set object.
		 *
		 * \param other Other object.
		 */
		Polygon3Set(const Ionflux::GeoUtils::Polygon3Set& other);
		
		/** Constructor.
		 *
		 * Construct new Polygon3Set object.
		 *
		 * \param initPolygons Polygons.
		 */
		Polygon3Set(Ionflux::GeoUtils::Polygon3Vector& initPolygons);
		
		/** Destructor.
		 *
		 * Destruct Polygon3Set object.
		 */
		virtual ~Polygon3Set();
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for all polygons.
		 *
		 * \return Barycenter vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBarycenter();
		
		/** Apply transformations.
		 *
		 * Apply transformations that have been accumulated in the 
		 * transformation matrices.
		 *
		 * \param recursive Apply transformations recursively.
		 */
		virtual void applyTransform(bool recursive = false);
		
		/** Get SVG representation.
		 *
		 * Get a Scalable Vector Graphics (XML) representation of the polygons
		 * in the set. The polygons will be projected orthogonally to the 
		 * appropriate coordinate plane along the specified axis.
		 *
		 * \param attrs Element attributes.
		 * \param elementIDPrefix Element ID prefix.
		 * \param axis Projection axis.
		 * \param shapeType Shape type.
		 * \param closePath Close path.
		 *
		 * \return SVG representation.
		 */
		virtual std::string getSVG(const std::string& attrs = 
		SVG_DEFAULT_POLY_STYLE, const std::string& elementIDPrefix = "polygon", 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, 
		Ionflux::GeoUtils::SVGShapeType shapeType = 
		Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
		
		/** Get SVG representation.
		 *
		 * Get a Scalable Vector Graphics (XML) representation of the polygons
		 * in the set. The polygons will be projected orthogonally to the 
		 * appropriate coordinate plane along the specified axis. For each 
		 * polygon, a style is selected from the \c styles vector in order 
		 * (modulo the number of styles in the vector).
		 *
		 * \param styles Element styles.
		 * \param elementIDPrefix Element ID prefix.
		 * \param axis Projection axis.
		 * \param shapeType Shape type.
		 * \param closePath Close path.
		 *
		 * \return SVG representation.
		 */
		virtual std::string getSVG(const Ionflux::GeoUtils::SVGShapeStyleVector& 
		styles, const std::string& elementIDPrefix = "polygon", 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, 
		Ionflux::GeoUtils::SVGShapeType shapeType = 
		Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
		
		/** Get SVG representation.
		 *
		 * Get a Scalable Vector Graphics (XML) representation of the polygons
		 * in the set. The polygons will be projected orthogonally to the 
		 * appropriate coordinate plane along the specified axis.
		 *
		 * \param imageProperties SVG image properties.
		 * \param elementIDPrefix Element ID prefix.
		 * \param axis Projection axis.
		 *
		 * \return SVG representation.
		 */
		virtual std::string getSVG(Ionflux::GeoUtils::SVGImageProperties& 
		imageProperties, const std::string& elementIDPrefix = "polygon", 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y);
		
		/** Write SVG representation to file.
		 *
		 * Create a Scalable Vector Graphics (XML) representation of the 
		 * polygons in the set and write it to a file.
		 *
		 * \param fileName File name.
		 * \param attrs Element attributes.
		 * \param elementIDPrefix Element ID prefix.
		 * \param axis Projection axis.
		 * \param shapeType Shape type.
		 * \param closePath Close path.
		 */
		virtual void writeSVG(const std::string& fileName, const std::string& 
		attrs = SVG_DEFAULT_POLY_STYLE, const std::string& elementIDPrefix = 
		"polygon", Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, 
		Ionflux::GeoUtils::SVGShapeType shapeType = 
		Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
		
		/** Write SVG representation to file.
		 *
		 * Create a Scalable Vector Graphics (XML) representation of the 
		 * polygons in the set and write it to a file.
		 *
		 * \param fileName File name.
		 * \param styles Element styles.
		 * \param elementIDPrefix Element ID prefix.
		 * \param axis Projection axis.
		 * \param shapeType Shape type.
		 * \param closePath Close path.
		 */
		virtual void writeSVG(const std::string& fileName, const 
		Ionflux::GeoUtils::SVGShapeStyleVector& styles, const std::string& 
		elementIDPrefix = "polygon", Ionflux::GeoUtils::AxisID axis = 
		Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType shapeType = 
		Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
		
		/** Write SVG representation to file.
		 *
		 * Create a Scalable Vector Graphics (XML) representation of the 
		 * polygons in the set and write it to a file.
		 *
		 * \param imageProperties SVG image properties.
		 * \param elementIDPrefix Element ID prefix.
		 * \param axis Projection axis.
		 */
		virtual void writeSVG(Ionflux::GeoUtils::SVGImageProperties& 
		imageProperties, const std::string& elementIDPrefix = "polygon", 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y);
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set& translate(const 
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
		virtual Ionflux::GeoUtils::Polygon3Set& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set& 
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
		virtual Ionflux::GeoUtils::Polygon3Set& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** View/image transformation.
		 *
		 * Apply a view transformation matrix and an optional image 
		 * transformation matrix to the object.
		 *
		 * \param view View transformation matrix.
		 * \param image Image transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set& duplicate();
		
		/** Sort.
		 *
		 * Sort polygons in the set. If no comparison function is specified, 
		 * polygons are sorted according to the Z-axis order of their 
		 * barycenters. \c compFunc will be managed by a temporary object so 
		 * it is possible to create a new instance of a comparison function 
		 * within the call.
		 *
		 * \param compFunc Comparison function.
		 */
		virtual void sort(Ionflux::GeoUtils::Polygon3Compare* compFunc = 0);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set& operator=(const 
		Ionflux::GeoUtils::Polygon3Set& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Polygon3Set* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Polygon3Set* 
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
		static Ionflux::GeoUtils::Polygon3Set* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Polygon3Set object.
		 *
		 * \param initPolygons Polygons.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Polygon3Set* 
		create(Ionflux::GeoUtils::Polygon3Vector& initPolygons, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
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
		 */
		virtual void loadFromXMLFile(const std::string& FileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \param fileName file name
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get number of polygons.
		 *
		 * \return Number of polygons.
		 */
		virtual unsigned int getNumPolygons() const;
		
		/** Get polygon.
		 *
		 * Get the polygon at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Polygon at specified index.
		 */
		virtual Ionflux::GeoUtils::Polygon3* getPolygon(unsigned int elementIndex
		= 0) const;
		
		/** Find polygon.
		 *
		 * Find the specified occurence of a polygon.
		 *
		 * \param needle Polygon to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the polygon, or -1 if the polygon cannot be found.
		 */
		virtual int findPolygon(Ionflux::GeoUtils::Polygon3* needle, unsigned int
		occurence = 1) const;
        
		/** Get polygon vector.
		 *
		 * \return polygon vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::Polygon3*>& getPolygons();
		
		/** Add polygon.
		 *
		 * Add a polygon.
		 *
		 * \param addElement Polygon to be added.
		 */
		virtual void addPolygon(Ionflux::GeoUtils::Polygon3* addElement);
		
		/** Create polygon.
		 *
		 * Create a new polygon which is managed by the polygon set.
		 *
		 * \return New polygon.
		 */
		virtual Ionflux::GeoUtils::Polygon3* addPolygon();
		
		/** Add polygons.
		 *
		 * Add polygons from a polygon vector.
		 *
		 * \param newPolygons polygons.
		 */
		virtual void addPolygons(const std::vector<Ionflux::GeoUtils::Polygon3*>&
		newPolygons);
		
		/** Add polygons.
		 *
		 * Add polygons from a polygon set.
		 *
		 * \param newPolygons polygons.
		 */
		virtual void addPolygons(Ionflux::GeoUtils::Polygon3Set* newPolygons);
		
		/** Remove polygon.
		 *
		 * Remove a polygon.
		 *
		 * \param removeElement Polygon to be removed.
		 */
		virtual void removePolygon(Ionflux::GeoUtils::Polygon3* removeElement);
		
		/** Remove polygon.
		 *
		 * Remove a polygon.
		 *
		 * \param removeIndex Polygon to be removed.
		 */
		virtual void removePolygonIndex(unsigned int removeIndex);
		
		/** Clear polygons.
		 *
		 * Clear all polygons.
		 */
		virtual void clearPolygons();
};

}

}

/** \file Polygon3Set.hpp
 * \brief Polygon set (3D) (header).
 */
#endif
