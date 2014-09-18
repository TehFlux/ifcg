#ifndef IONFLUX_MAPPING_POINTSAMPLE
#define IONFLUX_MAPPING_POINTSAMPLE
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointSample.hpp                 Point sample (header).
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
#include "ifmapping/Point.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

namespace XMLUtils
{

class PointSampleXMLFactory;

}

/// Class information for class PointSample.
class PointSampleClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PointSampleClassInfo();
		/// Destructor.
		virtual ~PointSampleClassInfo();
};

/** Point sample.
 * \ingroup ifmapping
 *
 * A sample of a single parameter value of a point mapping. The sample can 
 * include additional data such as the arc length.
 */
class PointSample
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// parameter value.
		Ionflux::Mapping::MappingValue param;
		/// coordinates.
		Ionflux::Mapping::Point* coords;
		/// arc length.
		Ionflux::Mapping::MappingValue arcLength;
		
	public:
		/// Class information instance.
		static const PointSampleClassInfo pointSampleClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new PointSample object.
		 */
		PointSample();
		
		/** Constructor.
		 *
		 * Construct new PointSample object.
		 *
		 * \param other Other object.
		 */
		PointSample(const Ionflux::Mapping::PointSample& other);
		
		/** Constructor.
		 *
		 * Construct new PointSample object.
		 *
		 * \param initParam parameter.
		 * \param initCoords coordinates.
		 * \param initArcLength arc length.
		 */
		PointSample(Ionflux::Mapping::MappingValue initParam, 
		Ionflux::Mapping::Point* initCoords = 0, Ionflux::Mapping::MappingValue 
		initArcLength = 0.);
		
		/** Destructor.
		 *
		 * Destruct PointSample object.
		 */
		virtual ~PointSample();
		
		/** Get value.
		 *
		 * Get a value of the sample according to the specified sampling mode.
		 *
		 * \param samplingMode sampling mode.
		 *
		 * \return Sample value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		getValue(Ionflux::Mapping::SamplingMode samplingMode = 
		Ionflux::Mapping::SAMPLING_MODE_PARAM);
		
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
		virtual Ionflux::Mapping::PointSample& operator=(const 
		Ionflux::Mapping::PointSample& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::PointSample* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::PointSample* 
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
		static Ionflux::Mapping::PointSample* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new PointSample object.
		 *
		 * \param initParam parameter.
		 * \param initCoords coordinates.
		 * \param initArcLength arc length.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::PointSample* 
		create(Ionflux::Mapping::MappingValue initParam, Ionflux::Mapping::Point*
		initCoords = 0, Ionflux::Mapping::MappingValue initArcLength = 0., 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		
		/** Get parameter value.
		 *
		 * \return Current value of parameter value.
		 */
		virtual Ionflux::Mapping::MappingValue getParam() const;
		
		/** Set parameter value.
		 *
		 * Set new value of parameter value.
		 *
		 * \param newParam New value of parameter value.
		 */
		virtual void setParam(Ionflux::Mapping::MappingValue newParam);
		
		/** Get coordinates.
		 *
		 * \return Current value of coordinates.
		 */
		virtual Ionflux::Mapping::Point* getCoords() const;
		
		/** Set coordinates.
		 *
		 * Set new value of coordinates.
		 *
		 * \param newCoords New value of coordinates.
		 */
		virtual void setCoords(Ionflux::Mapping::Point* newCoords);
		
		/** Get arc length.
		 *
		 * \return Current value of arc length.
		 */
		virtual Ionflux::Mapping::MappingValue getArcLength() const;
		
		/** Set arc length.
		 *
		 * Set new value of arc length.
		 *
		 * \param newArcLength New value of arc length.
		 */
		virtual void setArcLength(Ionflux::Mapping::MappingValue newArcLength);
};

}

}

/** \file PointSample.hpp
 * \brief Point sample (header).
 */
#endif
