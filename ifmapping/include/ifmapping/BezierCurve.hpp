#ifndef IONFLUX_MAPPING_BEZIERCURVE
#define IONFLUX_MAPPING_BEZIERCURVE
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierCurve.hpp                 Cubic Bezier curve (header).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/types.hpp"
#include "ifmapping/PointMapping.hpp"
#include "ifmapping/PointSet.hpp"

namespace Ionflux
{

namespace Mapping
{

namespace XMLUtils
{

class BezierCurveXMLFactory;

}

/// Class information for class BezierCurve.
class BezierCurveClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BezierCurveClassInfo();
		/// Destructor.
		virtual ~BezierCurveClassInfo();
};

/** Cubic Bezier curve.
 * \ingroup ifmapping
 *
 * A cubic bezier curve.
 */
class BezierCurve
: public Ionflux::Mapping::PointMapping, public Ionflux::Mapping::PointSet
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const BezierCurveClassInfo bezierCurveClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new BezierCurve object.
		 */
		BezierCurve();
		
		/** Constructor.
		 *
		 * Construct new BezierCurve object.
		 *
		 * \param other Other object.
		 */
		BezierCurve(const Ionflux::Mapping::BezierCurve& other);
		
		/** Constructor.
		 *
		 * Construct new BezierCurve object.
		 *
		 * \param initP0 Control point (0).
		 * \param initP1 Control point (1).
		 * \param initP2 Control point (2).
		 * \param initP3 Control point (3).
		 */
		BezierCurve(const Ionflux::Mapping::Point& initP0, const 
		Ionflux::Mapping::Point& initP1, const Ionflux::Mapping::Point& initP2, 
		const Ionflux::Mapping::Point& initP3);
		
		/** Constructor.
		 *
		 * Construct new BezierCurve object.
		 *
		 * \param initPoints Control point vector.
		 */
		BezierCurve(const Ionflux::Mapping::PointVector& initPoints);
		
		/** Constructor.
		 *
		 * Construct new BezierCurve object.
		 *
		 * \param initPoints Control point set.
		 */
		BezierCurve(Ionflux::Mapping::PointSet& initPoints);
		
		/** Destructor.
		 *
		 * Destruct BezierCurve object.
		 */
		virtual ~BezierCurve();
		
		/** Validate control points.
		 *
		 * Validate the four control points of the bezier curve. This ensures 
		 * that all control points are non-null.
		 */
		virtual void validate();
		
		/** Set control points.
		 *
		 * Set control points from a vector of points.
		 *
		 * \param newPoints Points.
		 */
		virtual void setControlPoints(const Ionflux::Mapping::PointVector& 
		newPoints);
		
		/** Set control points.
		 *
		 * Set control points from a set of points.
		 *
		 * \param newPoints Points.
		 */
		virtual void setControlPoints(const Ionflux::Mapping::PointSet& 
		newPoints);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Evaluate the bezier curve.
		 *
		 * Evaluate the bezier curve with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue 
		value);
		
		/** Interpolate bezier curves.
		 *
		 * Calculate a linear interpolation of two bezier curves.
		 *
		 * \param other Other curve.
		 * \param t Interpolation parameter.
		 *
		 * \return Interpolated bezier curve.
		 */
		virtual Ionflux::Mapping::BezierCurve interpolate(const 
		Ionflux::Mapping::BezierCurve& other, Ionflux::Mapping::MappingValue t = 
		0.5) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::BezierCurve& operator=(const 
		Ionflux::Mapping::BezierCurve& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::BezierCurve* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::BezierCurve* 
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
		static Ionflux::Mapping::BezierCurve* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new BezierCurve object.
		 *
		 * \param initP0 Control point (0).
		 * \param initP1 Control point (1).
		 * \param initP2 Control point (2).
		 * \param initP3 Control point (3).
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::BezierCurve* create(const 
		Ionflux::Mapping::Point& initP0, const Ionflux::Mapping::Point& initP1, 
		const Ionflux::Mapping::Point& initP2, const Ionflux::Mapping::Point& 
		initP3, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new BezierCurve object.
		 *
		 * \param initPoints Control point vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::BezierCurve* create(const 
		Ionflux::Mapping::PointVector& initPoints, Ionflux::ObjectBase::IFObject*
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new BezierCurve object.
		 *
		 * \param initPoints Control point set.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::BezierCurve* create(Ionflux::Mapping::PointSet& 
		initPoints, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		 */
		virtual void loadFromXMLFile(const std::string& fileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 * 
		 * return XML object factory
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get control point (0).
		 *
		 * \return Current value of control point (0).
		 */
		virtual Ionflux::Mapping::Point getP0() const;
		
		/** Set control point (0).
		 *
		 * Set new value of control point (0).
		 *
		 * \param newP0 New value of control point (0).
		 */
		virtual void setP0(const Ionflux::Mapping::Point& newP0);
		
		/** Get control point (1).
		 *
		 * \return Current value of control point (1).
		 */
		virtual Ionflux::Mapping::Point getP1() const;
		
		/** Set control point (1).
		 *
		 * Set new value of control point (1).
		 *
		 * \param newP1 New value of control point (1).
		 */
		virtual void setP1(const Ionflux::Mapping::Point& newP1);
		
		/** Get control point (2).
		 *
		 * \return Current value of control point (2).
		 */
		virtual Ionflux::Mapping::Point getP2() const;
		
		/** Set control point (2).
		 *
		 * Set new value of control point (2).
		 *
		 * \param newP2 New value of control point (2).
		 */
		virtual void setP2(const Ionflux::Mapping::Point& newP2);
		
		/** Get control point (3).
		 *
		 * \return Current value of control point (3).
		 */
		virtual Ionflux::Mapping::Point getP3() const;
		
		/** Set control point (3).
		 *
		 * Set new value of control point (3).
		 *
		 * \param newP3 New value of control point (3).
		 */
		virtual void setP3(const Ionflux::Mapping::Point& newP3);
};

}

}

/** \file BezierCurve.hpp
 * \brief Cubic Bezier curve (header).
 */
#endif
