#ifndef IONFLUX_MAPPING_RESCALE
#define IONFLUX_MAPPING_RESCALE
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Rescale.hpp                     Rescale mapping (header).
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
#include "ifmapping/Mapping.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class Rescale.
class RescaleClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		RescaleClassInfo();
		/// Destructor.
		virtual ~RescaleClassInfo();
};

/** Rescale mapping.
 * \ingroup ifmapping
 *
 * Rescales the function values to the range 0...1, using the specified 
 * arguments to find extreme points.
 */
class Rescale
: public Ionflux::Mapping::Mapping
{
	private:
		
	protected:
		/// Minimum value.
		Ionflux::Mapping::MappingValue vMin;
		/// Maximum value.
		Ionflux::Mapping::MappingValue vMax;
		/// Source mapping.
		Ionflux::Mapping::Mapping* func;
		/// Extreme point arguments.
		std::vector<Ionflux::Mapping::MappingValue> args;
		
	public:
		/// Class information instance.
		static const RescaleClassInfo rescaleClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Rescale object.
		 */
		Rescale();
		
		/** Constructor.
		 *
		 * Construct new Rescale object.
		 *
		 * \param other Other object.
		 */
		Rescale(const Ionflux::Mapping::Rescale& other);
		
		/** Constructor.
		 *
		 * Construct new Rescale object.
		 *
		 * \param initFunc Source function.
		 * \param initArgs Extreme point arguments.
		 */
		Rescale(Ionflux::Mapping::Mapping* initFunc, const 
		Ionflux::Mapping::MappingValueVector* initArgs = 0);
		
		/** Destructor.
		 *
		 * Destruct Rescale object.
		 */
		virtual ~Rescale();
		
		/** Add arguments.
		 *
		 * Add arguments for finding extreme values.
		 *
		 * \param newArgs Arguments.
		 */
		virtual void addArgs(const Ionflux::Mapping::MappingValueVector& 
		newArgs);
		
		/** Find extreme points of the source function.
		 *
		 * Find the extreme points of the source function by checking the 
		 * arguments supplied to the mapping.
		 */
		virtual void findExtremePoints();
		
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
		call(Ionflux::Mapping::MappingValue value) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Rescale& operator=(const 
		Ionflux::Mapping::Rescale& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Rescale* copy() const;
		
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
		static Ionflux::Mapping::Rescale* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get source mapping.
		 *
		 * \return Current value of source mapping.
		 */
		virtual Ionflux::Mapping::Mapping* getFunc() const;
		
		/** Set source mapping.
		 *
		 * Set new value of source mapping.
		 *
		 * \param newFunc New value of source mapping.
		 */
		virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
		
		/** Get number of args.
		 *
		 * \return Number of args.
		 */
		virtual unsigned int getNumArgs() const;
		
		/** Get arg.
		 *
		 * Get the arg at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Arg at specified index.
		 */
		virtual Ionflux::Mapping::MappingValue getArg(unsigned int elementIndex =
		0) const;
		
		/** Find arg.
		 *
		 * Find the specified occurence of a arg.
		 *
		 * \param needle Arg to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the arg, or -1 if the arg cannot be found.
		 */
		virtual int findArg(Ionflux::Mapping::MappingValue needle, unsigned int 
		occurence = 1) const;
        
		/** Get extreme point arguments.
		 *
		 * \return extreme point arguments.
		 */
		virtual std::vector<Ionflux::Mapping::MappingValue>& getArgs();
		
		/** Add arg.
		 *
		 * Add a arg.
		 *
		 * \param addElement Arg to be added.
		 */
		virtual void addArg(Ionflux::Mapping::MappingValue addElement);
		
		/** Remove arg.
		 *
		 * Remove a arg.
		 *
		 * \param removeElement Arg to be removed.
		 */
		virtual void removeArg(Ionflux::Mapping::MappingValue removeElement);
		
		/** Remove arg.
		 *
		 * Remove a arg.
		 *
		 * \param removeIndex Arg to be removed.
		 */
		virtual void removeArgIndex(unsigned int removeIndex);
		
		/** Clear args.
		 *
		 * Clear all args.
		 */
		virtual void clearArgs();
};

}

}

/** \file Rescale.hpp
 * \brief Rescale mapping (header).
 */
#endif
