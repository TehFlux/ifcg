#ifndef IONFLUX_MAPPING_SEGMENT
#define IONFLUX_MAPPING_SEGMENT
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Segment.hpp                     Segment (header).
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
#include "ifmapping/constants.hpp"
#include "ifmapping/PointMapping.hpp"

namespace Ionflux
{

namespace Mapping
{

class PointSet;
class PointSample;

namespace XMLUtils
{

class SegmentXMLFactory;

}

/// Class information for class Segment.
class SegmentClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		SegmentClassInfo();
		/// Destructor.
		virtual ~SegmentClassInfo();
};

/** Segment.
 * \ingroup ifmapping
 *
 * A segment is a discretization of an underlying point mapping. Each 
 * segment consists of two point samples and provides methods to get 
 * interpolated values on the segment. A segment can have child segments at
 * a finer resolution, creating a hierarchy of segments from which values 
 * can be sampled.
 */
class Segment
: public Ionflux::Mapping::PointMapping
{
	private:
		
	protected:
		/// point mapping.
		Ionflux::Mapping::PointMapping* func;
		/// point sample (0).
		Ionflux::Mapping::PointSample* p0;
		/// point sample (1).
		Ionflux::Mapping::PointSample* p1;
		/// Child segments.
		std::vector<Ionflux::Mapping::Segment*> segments;
		/// arc length estimate.
		Ionflux::Mapping::MappingValue arcLength;
		
	public:
		/// Default error thteshold.
		static const Ionflux::Mapping::MappingValue DEFAULT_ERROR_THRESHOLD;
		/// Class information instance.
		static const SegmentClassInfo segmentClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Segment object.
		 */
		Segment();
		
		/** Constructor.
		 *
		 * Construct new Segment object.
		 *
		 * \param other Other object.
		 */
		Segment(const Ionflux::Mapping::Segment& other);
		
		/** Constructor.
		 *
		 * Construct new Segment object.
		 *
		 * \param initFunc point mapping.
		 * \param t0 parameter (0).
		 * \param t1 parameter (1).
		 */
		Segment(Ionflux::Mapping::PointMapping* initFunc, 
		Ionflux::Mapping::MappingValue t0 = 0., Ionflux::Mapping::MappingValue t1
		= 1.);
		
		/** Constructor.
		 *
		 * Construct new Segment object.
		 *
		 * \param initFunc point mapping.
		 * \param initP0 point sample (0).
		 * \param initP1 point sample (1).
		 */
		Segment(Ionflux::Mapping::PointMapping* initFunc, 
		Ionflux::Mapping::PointSample* initP0, Ionflux::Mapping::PointSample* 
		initP1 = 0);
		
		/** Destructor.
		 *
		 * Destruct Segment object.
		 */
		virtual ~Segment();
		
		/** Get length.
		 *
		 * Get an estimate for the length of the segment, based on the 
		 * endpoint coordinates. If the optional \c recursive argument is set 
		 * to \c true, child segments will be queried recursively to estimate 
		 * the length.
		 *
		 * \param recursive estimate length recursively.
		 * \param maxDepth maximum depth for recursive length estimation.
		 * \param depth current depth for recursive length estimation.
		 *
		 * \return Length of the segment.
		 */
		virtual Ionflux::Mapping::MappingValue getLength(bool recursive = false, 
		unsigned int maxDepth = 0, unsigned int depth = 0) const;
		
		/** Get length error.
		 *
		 * Get an estimate for the length error of the segment relative to the
		 * length of the specified depth level of child segments.
		 *
		 * \param relativeError calculate relative error.
		 * \param maxDepth maximum depth.
		 * \param t Tolerance.
		 *
		 * \return Length error for the segment.
		 */
		virtual Ionflux::Mapping::MappingValue getLengthError(bool relativeError 
		= true, unsigned int maxDepth = 1, double t = 
		Ionflux::Mapping::DEFAULT_TOLERANCE) const;
		
		/** Update arc length estimate.
		 *
		 * Update the estimate for the arc length of the segment, based on the
		 * endpoints or (if available) the child segments. This uses 
		 * getLength() to estimate the arc length. If either of the boundary 
		 * points is zero and \c recursive is set to \c false, the arc length 
		 * estimate will be set to zero.
		 *
		 * \param recursive estimate length recursively.
		 * \param maxDepth maximum depth for recursive length estimation.
		 *
		 * \return Arc length estimate.
		 */
		virtual Ionflux::Mapping::MappingValue updateArcLength(bool recursive = 
		false, unsigned int maxDepth = 0);
		
		/** Split.
		 *
		 * Split the segment by creating a specified number of connected child
		 * segments. If \c recursive is set to \c true, segments will be split
		 * recursively until either the length error between the last and the 
		 * first-to-last depth level is below the threshold for all leaf 
		 * segments, or until the maximum recursion depth is reached, 
		 * whichever comes first.
		 *
		 * \param numSplitSegments number of child segments to be created.
		 * \param recursive split recursively.
		 * \param relativeError use relative error.
		 * \param errorThreshold error threshold.
		 * \param maxDepth maximum recursion depth.
		 * \param depth current recursion depth.
		 * \param t Tolerance.
		 */
		virtual void split(unsigned int numSplitSegments = 2, bool recursive = 
		false, bool relativeError = true, Ionflux::Mapping::MappingValue 
		errorThreshold = Ionflux::Mapping::Segment::DEFAULT_ERROR_THRESHOLD, 
		unsigned int maxDepth = 0, unsigned int depth = 0, double t = 
		Ionflux::Mapping::DEFAULT_TOLERANCE);
		
		/** Find segment.
		 *
		 * Find a child segment for the specified parameter value and sampling
		 * mode.
		 *
		 * \param value Parameter value.
		 * \param samplingMode sampling mode.
		 * \param searchMethod searchMethod.
		 * \param startIndex start index.
		 * \param endIndex end index.
		 * \param recursive find segment recursively.
		 * \param t Tolerance.
		 *
		 * \return Segment.
		 */
		virtual Ionflux::Mapping::Segment* 
		findSegment(Ionflux::Mapping::MappingValue value, 
		Ionflux::Mapping::SamplingMode samplingMode = 
		Ionflux::Mapping::SAMPLING_MODE_PARAM, Ionflux::Mapping::SearchMethod 
		searchMethod = Ionflux::Mapping::SEARCH_LINEAR, int startIndex = 0, int 
		endIndex = -1, bool recursive = false, double t = 
		Ionflux::Mapping::DEFAULT_TOLERANCE);
		
		/** Get sample.
		 *
		 * Get a sample from the segment for the specified parameter value and
		 * sampling mode. No sampling of the underlying point mapping is 
		 * involved when this function is called.
		 *
		 * \param value Parameter value.
		 * \param samplingMode sampling mode.
		 * \param searchMethod searchMethod.
		 * \param recursive sample segments recursively.
		 * \param maxDepth maximum recursion depth.
		 * \param depth current recursion depth.
		 * \param t Tolerance.
		 *
		 * \return Point sample.
		 */
		virtual Ionflux::Mapping::PointSample* 
		getSample0(Ionflux::Mapping::MappingValue value, 
		Ionflux::Mapping::SamplingMode samplingMode = 
		Ionflux::Mapping::SAMPLING_MODE_PARAM, Ionflux::Mapping::SearchMethod 
		searchMethod = Ionflux::Mapping::SEARCH_LINEAR, bool recursive = false, 
		unsigned int maxDepth = 0, unsigned int depth = 0, double t = 
		Ionflux::Mapping::DEFAULT_TOLERANCE);
		
		/** Get leaf segments.
		 *
		 * Get leaf segments from the hierarchy.
		 *
		 * \param target Where to store the leaf segments.
		 */
		virtual void getLeafSegments(Ionflux::Mapping::Segment& target);
		
		/** Get leaf points.
		 *
		 * Get leaf points from the hierarchy.
		 *
		 * \param target Where to store the leaf points.
		 */
		virtual void getLeafPoints(Ionflux::Mapping::PointSet& target);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get parameter for coordinate value.
		 *
		 * Get the parameter value corresponding to the specified  coordinate 
		 * value. Since the coordinate value is interpolated for a segment 
		 * mapping, the \c precision argument is ignored.
		 *
		 * \param value Coordinate value.
		 * \param coord Coordinate.
		 * \param precision Precision.
		 *
		 * \return Parameter value for the specified coordinate value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		getParamCoord(Ionflux::Mapping::MappingValue value, 
		Ionflux::Mapping::CoordinateID coord = Ionflux::Mapping::C_X, 
		Ionflux::Mapping::MappingValue precision = 
		Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
		
		/** Get parameter for arc length.
		 *
		 * Get the parameter value corresponding to the specified arc length. 
		 * Since the arc length is interpolated for a segment mapping, the \c 
		 * relativeError, \c maxNumIterations and \c precision arguments are 
		 * ignored.
		 *
		 * \param value Arc length value.
		 * \param relativeError Relative error.
		 * \param maxNumIterations Maximum number of iterations.
		 * \param precision Precision.
		 *
		 * \return Parameter value for the specified arc length.
		 */
		virtual Ionflux::Mapping::MappingValue 
		getParamArcLength(Ionflux::Mapping::MappingValue value, 
		Ionflux::Mapping::MappingValue relativeError = 
		Ionflux::Mapping::PointMapping::DEFAULT_RELATIVE_ERROR, unsigned int 
		maxNumIterations = 
		Ionflux::Mapping::PointMapping::DEFAULT_MAX_NUM_ITERATIONS, 
		Ionflux::Mapping::MappingValue precision = 
		Ionflux::Mapping::PointMapping::DEFAULT_PRECISION);
		
		/** Get sample.
		 *
		 * Get a sample of the point mapping at the specified parameter value.
		 * If the optional \c calculateArcLength argument is set to \c true, 
		 * the arc length will be calculated for the sample. Otherwise, the 
		 * arc length will be set to zero. The caller is responsible for 
		 * managing the returned object. Since the arc length is interpolated 
		 * for a segment mapping, the \c relativeError and \c maxNumIterations
		 * arguments are ignored.
		 *
		 * \param value Value.
		 * \param calculateArcLength calculate arc length.
		 * \param relativeError Relative error.
		 * \param maxNumIterations Maximum number of iterations.
		 *
		 * \return New point sample object.
		 */
		virtual Ionflux::Mapping::PointSample* 
		getSample(Ionflux::Mapping::MappingValue value, bool calculateArcLength =
		false, Ionflux::Mapping::MappingValue relativeError = 
		Ionflux::Mapping::PointMapping::DEFAULT_RELATIVE_ERROR, unsigned int 
		maxNumIterations = 
		Ionflux::Mapping::PointMapping::DEFAULT_MAX_NUM_ITERATIONS);
		
		/** Get arc length.
		 *
		 * Get the arc length at the specified parameter value.
		 *
		 * \param value Parameter value.
		 * \param relativeError Relative error.
		 * \param maxNumIterations Maximum number of iterations.
		 *
		 * \return Parameter value for the specified arc length.
		 */
		virtual Ionflux::Mapping::MappingValue 
		getArcLength(Ionflux::Mapping::MappingValue value, 
		Ionflux::Mapping::MappingValue relativeError = 
		Ionflux::Mapping::PointMapping::DEFAULT_RELATIVE_ERROR, unsigned int 
		maxNumIterations = 
		Ionflux::Mapping::PointMapping::DEFAULT_MAX_NUM_ITERATIONS);
		
		/** Evaluate the mapping.
		 *
		 * Evaluate the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Point.
		 */
		virtual Ionflux::Mapping::Point call(Ionflux::Mapping::MappingValue 
		value);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Segment& operator=(const 
		Ionflux::Mapping::Segment& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Segment* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Segment* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Segment* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Segment object.
		 *
		 * \param initFunc point mapping.
		 * \param t0 parameter (0).
		 * \param t1 parameter (1).
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::Segment* create(Ionflux::Mapping::PointMapping* 
		initFunc, Ionflux::Mapping::MappingValue t0 = 0., 
		Ionflux::Mapping::MappingValue t1 = 1., Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Segment object.
		 *
		 * \param initFunc point mapping.
		 * \param initP0 point sample (0).
		 * \param initP1 point sample (1).
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::Segment* create(Ionflux::Mapping::PointMapping* 
		initFunc, Ionflux::Mapping::PointSample* initP0, 
		Ionflux::Mapping::PointSample* initP1 = 0, Ionflux::ObjectBase::IFObject*
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
		
		/** Get point mapping.
		 *
		 * \return Current value of point mapping.
		 */
		virtual Ionflux::Mapping::PointMapping* getFunc() const;
		
		/** Set point mapping.
		 *
		 * Set new value of point mapping.
		 *
		 * \param newFunc New value of point mapping.
		 */
		virtual void setFunc(Ionflux::Mapping::PointMapping* newFunc);
		
		/** Get point sample (0).
		 *
		 * \return Current value of point sample (0).
		 */
		virtual Ionflux::Mapping::PointSample* getP0() const;
		
		/** Set point sample (0).
		 *
		 * Set new value of point sample (0).
		 *
		 * \param newP0 New value of point sample (0).
		 */
		virtual void setP0(Ionflux::Mapping::PointSample* newP0);
		
		/** Get point sample (1).
		 *
		 * \return Current value of point sample (1).
		 */
		virtual Ionflux::Mapping::PointSample* getP1() const;
		
		/** Set point sample (1).
		 *
		 * Set new value of point sample (1).
		 *
		 * \param newP1 New value of point sample (1).
		 */
		virtual void setP1(Ionflux::Mapping::PointSample* newP1);
		
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
		virtual Ionflux::Mapping::Segment* getSegment(unsigned int elementIndex =
		0) const;
		
		/** Find segment.
		 *
		 * Find the specified occurence of a segment.
		 *
		 * \param needle Segment to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the segment, or -1 if the segment cannot be found.
		 */
		virtual int findSegment(Ionflux::Mapping::Segment* needle, unsigned int 
		occurence = 1) const;
        
		/** Get child segments.
		 *
		 * \return child segments.
		 */
		virtual std::vector<Ionflux::Mapping::Segment*>& getSegments();
		
		/** Add segment.
		 *
		 * Add a segment.
		 *
		 * \param addElement Segment to be added.
		 */
		virtual void addSegment(Ionflux::Mapping::Segment* addElement);
		
		/** Create segment.
		 *
		 * Create a new segment which is managed by the segment set.
		 *
		 * \return New segment.
		 */
		virtual Ionflux::Mapping::Segment* addSegment();
		
		/** Add segments.
		 *
		 * Add segments from a segment vector.
		 *
		 * \param newSegments segments.
		 */
		virtual void addSegments(const std::vector<Ionflux::Mapping::Segment*>& 
		newSegments);
		
		/** Add segments.
		 *
		 * Add segments from a segment set.
		 *
		 * \param newSegments segments.
		 */
		virtual void addSegments(Ionflux::Mapping::Segment* newSegments);
		
		/** Remove segment.
		 *
		 * Remove a segment.
		 *
		 * \param removeElement Segment to be removed.
		 */
		virtual void removeSegment(Ionflux::Mapping::Segment* removeElement);
		
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
		
		/** Get arc length estimate.
		 *
		 * \return Current value of arc length estimate.
		 */
		virtual Ionflux::Mapping::MappingValue getArcLength() const;
		
		/** Set arc length estimate.
		 *
		 * Set new value of arc length estimate.
		 *
		 * \param newArcLength New value of arc length estimate.
		 */
		virtual void setArcLength(Ionflux::Mapping::MappingValue newArcLength);
};

}

}

/** \file Segment.hpp
 * \brief Segment (header).
 */
#endif
