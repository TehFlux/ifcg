#ifndef IONFLUX_MAPPING_POLYNOMIAL
#define IONFLUX_MAPPING_POLYNOMIAL
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polynomial.hpp                  Polynomial mapping (header).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "ifmapping/ChainableMapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class Polynomial.
class PolynomialClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PolynomialClassInfo();
		/// Destructor.
		virtual ~PolynomialClassInfo();
};

/** Polynomial mapping.
 * \ingroup ifmapping
 *
 * A mapping that maps the parameter to a polynomial function of the 
 * parameter. The degree of the polynomial is equal to the number of 
 * coefficients specified.
 */
class Polynomial
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		/// Coefficients.
		std::vector<Ionflux::Mapping::MappingValue> coefficients;
		
	public:
		/// Class information instance.
		static const PolynomialClassInfo polynomialClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Polynomial object.
		 */
		Polynomial();
		
		/** Constructor.
		 *
		 * Construct new Polynomial object.
		 *
		 * \param other Other object.
		 */
		Polynomial(const Ionflux::Mapping::Polynomial& other);
		
		/** Constructor.
		 *
		 * Construct new Polynomial object.
		 *
		 * \param initCoefficients Coefficients.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 * \param initFunc Source mapping.
		 */
		Polynomial(const Ionflux::Mapping::MappingValueVector& initCoefficients, 
		Ionflux::Mapping::MappingValue initScale = 1., 
		Ionflux::Mapping::MappingValue initOffset = 0., 
		Ionflux::Mapping::Mapping* initFunc = 0);
		
		/** Destructor.
		 *
		 * Destruct Polynomial object.
		 */
		virtual ~Polynomial();
		
		/** Add coefficients.
		 *
		 * Add coefficients from a vector of coefficients.
		 *
		 * \param newCoefficients Coefficients.
		 */
		virtual void addCoefficients(const Ionflux::Mapping::MappingValueVector& 
		newCoefficients);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		callWithParam(Ionflux::Mapping::MappingValue value) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Polynomial& operator=(const 
		Ionflux::Mapping::Polynomial& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Polynomial* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Polynomial* 
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
		static Ionflux::Mapping::Polynomial* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of coefficients.
		 *
		 * \return Number of coefficients.
		 */
		virtual unsigned int getNumCoefficients() const;
		
		/** Get coefficient.
		 *
		 * Get the coefficient at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Coefficient at specified index.
		 */
		virtual Ionflux::Mapping::MappingValue getCoefficient(unsigned int 
		elementIndex = 0) const;
		
		/** Find coefficient.
		 *
		 * Find the specified occurence of a coefficient.
		 *
		 * \param needle Coefficient to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the coefficient, or -1 if the coefficient cannot be 
		 * found.
		 */
		virtual int findCoefficient(Ionflux::Mapping::MappingValue needle, 
		unsigned int occurence = 1) const;
        
		/** Get coefficients.
		 *
		 * \return coefficients.
		 */
		virtual std::vector<Ionflux::Mapping::MappingValue>& getCoefficients();
		
		/** Add coefficient.
		 *
		 * Add a coefficient.
		 *
		 * \param addElement Coefficient to be added.
		 */
		virtual void addCoefficient(Ionflux::Mapping::MappingValue addElement);
		
		/** Remove coefficient.
		 *
		 * Remove a coefficient.
		 *
		 * \param removeElement Coefficient to be removed.
		 */
		virtual void removeCoefficient(Ionflux::Mapping::MappingValue 
		removeElement);
		
		/** Remove coefficient.
		 *
		 * Remove a coefficient.
		 *
		 * \param removeIndex Coefficient to be removed.
		 */
		virtual void removeCoefficientIndex(unsigned int removeIndex);
		
		/** Clear coefficients.
		 *
		 * Clear all coefficients.
		 */
		virtual void clearCoefficients();
};

}

}

/** \file Polynomial.hpp
 * \brief Polynomial mapping (header).
 */
#endif
