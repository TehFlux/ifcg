#ifndef IONFLUX_MAPPING_BEZIERSPLINE
#define IONFLUX_MAPPING_BEZIERSPLINE
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * BezierSpline.hpp                Cubic Bezier spline (header).
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
#include "ifmapping/BezierCurve.hpp"
#include "ifmapping/PointMapping.hpp"

namespace Ionflux
{

namespace Mapping
{

namespace XMLUtils
{

class BezierSplineXMLFactory;

}

/// Class information for class BezierSpline.
class BezierSplineClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		BezierSplineClassInfo();
		/// Destructor.
		virtual ~BezierSplineClassInfo();
};

/** Cubic Bezier spline.
 * \ingroup ifmapping
 *
 * A cubic bezier spline.
 */
class BezierSpline
: public Ionflux::Mapping::PointMapping
{
	private:
		
	protected:
		/// Segment vector.
		std::vector<Ionflux::Mapping::BezierCurve*> segments;
		
	public:
		/// Class information instance.
		static const BezierSplineClassInfo bezierSplineClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new BezierSpline object.
		 */
		BezierSpline();
		
		/** Constructor.
		 *
		 * Construct new BezierSpline object.
		 *
		 * \param other Other object.
		 */
		BezierSpline(const Ionflux::Mapping::BezierSpline& other);
		
		/** Destructor.
		 *
		 * Destruct BezierSpline object.
		 */
		virtual ~BezierSpline();
		
		/** Get segment index for parameter.
		 *
		 * Get the segment index for a parameter value
		 *
		 * \param t Parameter.
		 *
		 * \return Segment index.
		 */
		virtual unsigned int getSegmentIndex(Ionflux::Mapping::MappingValue t) 
		const;
		
		/** Get points on the spline.
		 *
		 * Get a number of points within the specified coordinate interval. 
		 * The points will be stored in the target point set.
		 *
		 * \param target Target set.
		 * \param x0 Lower bound.
		 * \param x1 Upper bound.
		 * \param numPoints Number of points.
		 * \param coord Coordinate.
		 * \param precision Precision.
		 */
		virtual void getPoints(Ionflux::Mapping::PointSet& target, 
		Ionflux::Mapping::MappingValue x0 = 0., Ionflux::Mapping::MappingValue x1
		= 1., unsigned int numPoints = 10, Ionflux::Mapping::CoordinateID coord =
		Ionflux::Mapping::C_X, Ionflux::Mapping::MappingValue precision = 
		Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
		
		/** Initialize from SVG data.
		 *
		 * Initialize the spline from SVG path data.
		 *
		 * \param rawData SVG path data.
		 */
		virtual void initFromSVG(const std::string& rawData);
		
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
		
		/** Interpolate bezier splines.
		 *
		 * Calculate a linear interpolation of two bezier splines.
		 *
		 * \param other Other spline.
		 * \param t Interpolation parameter.
		 *
		 * \return Interpolated bezier spline.
		 */
		virtual Ionflux::Mapping::BezierSpline interpolate(const 
		Ionflux::Mapping::BezierSpline& other, Ionflux::Mapping::MappingValue t =
		0.5) const;
		
		/** Create functional mapping.
		 *
		 * Create a mapping that generates values from the spline.
		 *
		 * \param paramScale Parameter scale.
		 * \param paramOffset Parameter offset.
		 * \param outputScale Output scale.
		 * \param outputOffset Output offset.
		 * \param inCoord Input coordinate.
		 * \param outCoord Output coordinate.
		 *
		 * \return Mapping.
		 */
		virtual Ionflux::Mapping::Mapping* 
		createFunc(Ionflux::Mapping::MappingValue paramScale = 1., 
		Ionflux::Mapping::MappingValue paramOffset = 0., const 
		Ionflux::Mapping::Point& outputScale = Ionflux::Mapping::Point::ONES, 
		const Ionflux::Mapping::Point& outputOffset = 
		Ionflux::Mapping::Point::ORIGIN, Ionflux::Mapping::CoordinateID inCoord =
		Ionflux::Mapping::C_X, Ionflux::Mapping::CoordinateID outCoord = 
		Ionflux::Mapping::C_Y);
		
		/** Get SVG path data.
		 *
		 * Get SVG path data for the bezier spline. The specified image plane 
		 * normal coordinate will be assumed to be orthogonal to the image 
		 * plane and omitted from the path data.
		 *
		 * \param imagePlaneNormal Image plane normal axis.
		 *
		 * \return SVG path data.
		 */
		virtual std::string getSVGPathData(const Ionflux::Mapping::CoordinateID 
		imagePlaneNormal = Ionflux::Mapping::C_Z) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
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
		virtual Ionflux::Mapping::BezierSpline& operator=(const 
		Ionflux::Mapping::BezierSpline& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::BezierSpline* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::BezierSpline* 
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
		static Ionflux::Mapping::BezierSpline* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		virtual void loadFromXMLFile(const std::string& FileName);
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \param fileName file name
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get number of segments.
		 *
		 * \return Number of segments.
		 */
		virtual unsigned int getNumSegments() const;
		
		/** Get segment.
		 *
		 * Get the segment at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Segment at specified index.
		 */
		virtual Ionflux::Mapping::BezierCurve* getSegment(unsigned int 
		elementIndex = 0) const;
		
		/** Find segment.
		 *
		 * Find the specified occurence of a segment.
		 *
		 * \param needle Segment to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the segment, or -1 if the segment cannot be found.
		 */
		virtual int findSegment(Ionflux::Mapping::BezierCurve* needle, unsigned 
		int occurence = 1) const;
        
		/** Get segment vector.
		 *
		 * \return segment vector.
		 */
		virtual std::vector<Ionflux::Mapping::BezierCurve*>& getSegments();
		
		/** Add segment.
		 *
		 * Add a segment.
		 *
		 * \param addElement Segment to be added.
		 */
		virtual void addSegment(Ionflux::Mapping::BezierCurve* addElement);
		
		/** Create segment.
		 *
		 * Create a new segment which is managed by the segment set.
		 *
		 * \return New segment.
		 */
		virtual Ionflux::Mapping::BezierCurve* addSegment();
		
		/** Add segments.
		 *
		 * Add segments from a segment vector.
		 *
		 * \param newSegments segments.
		 */
		virtual void addSegments(const 
		std::vector<Ionflux::Mapping::BezierCurve*>& newSegments);
		
		/** Add segments.
		 *
		 * Add segments from a segment set.
		 *
		 * \param newSegments segments.
		 */
		virtual void addSegments(Ionflux::Mapping::BezierSpline* newSegments);
		
		/** Remove segment.
		 *
		 * Remove a segment.
		 *
		 * \param removeElement Segment to be removed.
		 */
		virtual void removeSegment(Ionflux::Mapping::BezierCurve* removeElement);
		
		/** Remove segment.
		 *
		 * Remove a segment.
		 *
		 * \param removeIndex Segment to be removed.
		 */
		virtual void removeSegmentIndex(unsigned int removeIndex);
		
		/** Clear segments.
		 *
		 * Clear all segments.
		 */
		virtual void clearSegments();
};

}

}

/** \file BezierSpline.hpp
 * \brief Cubic Bezier spline (header).
 */
#endif
