#ifndef IONFLUX_GEOUTILS_VECTORN
#define IONFLUX_GEOUTILS_VECTORN
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorN.hpp                     Vector (N-D) (header).
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
#include "ifmapping/Mapping.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/Interpolator.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/Vector.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class VectorNXMLFactory;

}

/// Class information for class VectorN.
class VectorNClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		VectorNClassInfo();
		/// Destructor.
		virtual ~VectorNClassInfo();
};

/** Vector (N-D).
 * \ingroup ifphysim
 *
 * A numeric N-dimensional vector.
 */
class VectorN
: public Ionflux::GeoUtils::Vector
{
	private:
		
	protected:
		/// Number of elements.
		unsigned int numElements;
		
	public:
		/// Class information instance.
		static const VectorNClassInfo vectorNClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new VectorN object.
		 */
		VectorN();
		
		/** Constructor.
		 *
		 * Construct new VectorN object.
		 *
		 * \param other Other object.
		 */
		VectorN(const Ionflux::GeoUtils::VectorN& other);
		
		/** Constructor.
		 *
		 * Construct new VectorN object.
		 *
		 * \param initNumElements Number of elements.
		 */
		VectorN(unsigned int initNumElements);
		
		/** Constructor.
		 *
		 * Construct new VectorN object.
		 *
		 * \param initNumElements Number of elements.
		 * \param x0 element (0).
		 * \param x1 element (1).
		 * \param x2 element (2).
		 * \param x3 element (3).
		 * \param x4 element (4).
		 * \param x5 element (5).
		 * \param x6 element (6).
		 * \param x7 element (7).
		 * \param x8 element (8).
		 * \param x9 element (9).
		 * \param x10 element (10).
		 * \param x11 element (11).
		 * \param x12 element (12).
		 */
		VectorN(unsigned int initNumElements, double x0, double x1 = 0., double 
		x2 = 0., double x3 = 0., double x4 = 0., double x5 = 0., double x6 = 0., 
		double x7 = 0., double x8 = 0., double x9 = 0., double x10 = 0., double 
		x11 = 0., double x12 = 0.);
		
		/** Destructor.
		 *
		 * Destruct VectorN object.
		 */
		virtual ~VectorN();
		
		/** Interpolate vectors.
		 *
		 * Interpolate vectors.
		 *
		 * \param other Vector.
		 * \param t Interpolation parameter.
		 * \param interp Interpolator.
		 *
		 * \return Interpolated vector.
		 */
		virtual Ionflux::GeoUtils::VectorN interpolate(const 
		Ionflux::GeoUtils::VectorN& other, double t = 0.5, 
		Ionflux::GeoUtils::Interpolator* interp = 0);
		
		/** Add vectors.
		 *
		 * Add vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::VectorN operator+(const 
		Ionflux::GeoUtils::VectorN& other) const;
		
		/** Subtract vectors.
		 *
		 * Subtract vectors.
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::VectorN operator-(const 
		Ionflux::GeoUtils::VectorN& other) const;
		
		/** Multiply vector by scalar.
		 *
		 * Multiply vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::VectorN operator*(double c) const;
		
		/** Multiply vectors (dot product).
		 *
		 * Multiply vectors (dot product).
		 *
		 * \param other Vector.
		 *
		 * \return Result of the calculation.
		 */
		virtual double operator*(const Ionflux::GeoUtils::VectorN& other) const;
		
		/** Divide vector by scalar.
		 *
		 * Divide vector by a scalar.
		 *
		 * \param c Scalar factor.
		 *
		 * \return Result of the calculation.
		 */
		virtual Ionflux::GeoUtils::VectorN operator/(double c) const;
		
		/** Sample mapping.
		 *
		 * Sample a mapping uniformly in the specified interval. Return the  
		 * sample values as a new vector.
		 *
		 * \param mapping mapping.
		 * \param numPoints sample points.
		 * \param t0 start parameter.
		 * \param t1 end parameter.
		 *
		 * \return New vector.
		 */
		static Ionflux::GeoUtils::VectorN* sample(const 
		Ionflux::Mapping::Mapping& mapping, unsigned int numPoints, double t0 = 
		0., double t1 = 1.);
		
		/** Sample linear mapping.
		 *
		 * Sample a linear mapping uniformly in the specified interval. Return
		 * the sample values as a new vector.
		 *
		 * \param numPoints sample points.
		 * \param t0 start parameter.
		 * \param t1 end parameter.
		 * \param lower Lower value.
		 * \param upper Upper value.
		 * \param scale Scale factor.
		 * \param offset Offset.
		 *
		 * \return New vector.
		 */
		static Ionflux::GeoUtils::VectorN* linear(unsigned int numPoints, double 
		t0 = 0., double t1 = 1., Ionflux::Mapping::MappingValue lower = 0., 
		Ionflux::Mapping::MappingValue upper = 1., Ionflux::Mapping::MappingValue
		scale = 1., Ionflux::Mapping::MappingValue offset = 0.);
		
		/** Sample cubic mapping.
		 *
		 * Sample a cubic mapping uniformly in the specified interval. Return 
		 * the sample values as a new vector.
		 *
		 * \param numPoints sample points.
		 * \param t0 start parameter.
		 * \param t1 end parameter.
		 * \param lower Lower value.
		 * \param upper Upper value.
		 *
		 * \return New vector.
		 */
		static Ionflux::GeoUtils::VectorN* cubic(unsigned int numPoints, double 
		t0 = 0., double t1 = 1., Ionflux::Mapping::MappingValue lower = 0., 
		Ionflux::Mapping::MappingValue upper = 1.);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::VectorN& operator=(const 
		Ionflux::GeoUtils::VectorN& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::VectorN* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::VectorN* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::VectorN* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new VectorN object.
		 *
		 * \param initNumElements Number of elements.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::VectorN* create(unsigned int initNumElements, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new VectorN object.
		 *
		 * \param initNumElements Number of elements.
		 * \param x0 element (0).
		 * \param x1 element (1).
		 * \param x2 element (2).
		 * \param x3 element (3).
		 * \param x4 element (4).
		 * \param x5 element (5).
		 * \param x6 element (6).
		 * \param x7 element (7).
		 * \param x8 element (8).
		 * \param x9 element (9).
		 * \param x10 element (10).
		 * \param x11 element (11).
		 * \param x12 element (12).
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::VectorN* create(unsigned int initNumElements, 
		double x0, double x1 = 0., double x2 = 0., double x3 = 0., double x4 = 
		0., double x5 = 0., double x6 = 0., double x7 = 0., double x8 = 0., 
		double x9 = 0., double x10 = 0., double x11 = 0., double x12 = 0., 
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
		
		/** Get number of elements.
		 *
		 * \return Current value of number of elements.
		 */
		virtual unsigned int getNumElements() const;
		
		/** Set number of elements.
		 *
		 * Set new value of number of elements.
		 *
		 * \param newNumElements New value of number of elements.
		 */
		virtual void setNumElements(unsigned int newNumElements);
};

/** Multiply vector by scalar.
 *
 * Multiply vector by a scalar.
 *
 * \param c Scalar factor.
 * \param v Vector.
 *
 * \return Result of the calculation.
 */
Ionflux::GeoUtils::VectorN operator*(double c, const 
Ionflux::GeoUtils::VectorN& v);

}

}

/** \file VectorN.hpp
 * \brief Vector (N-D) (header).
 */
#endif
