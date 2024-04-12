#ifndef IONFLUX_MAPPING_ANIMATEDSPLINE
#define IONFLUX_MAPPING_ANIMATEDSPLINE
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AnimatedSpline.hpp              Animated Bezier spline (header).
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
#include "ifmapping/BezierSplineKey.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class AnimatedSpline.
class AnimatedSplineClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		AnimatedSplineClassInfo();
		/// Destructor.
		virtual ~AnimatedSplineClassInfo();
};

/** Animated Bezier spline.
 * \ingroup altjira
 *
 * A collection of key splines which are used for interpolating a spline 
 * over a parameter. Each key is a tuple containing the parameter value 
 * associated with the key and a spline representing the key shape. The 
 * spline for a particular parameter value can be obtained by calling the 
 * object with the parameter value. Note that all keys in the 
 * AnimatedSpline must have the same number of control points.
 */
class AnimatedSpline
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Spline key vector.
		std::vector<Ionflux::Mapping::BezierSplineKey*> keys;
		
	public:
		/// Class information instance.
		static const AnimatedSplineClassInfo animatedSplineClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new AnimatedSpline object.
		 */
		AnimatedSpline();
		
		/** Constructor.
		 *
		 * Construct new AnimatedSpline object.
		 *
		 * \param other Other object.
		 */
		AnimatedSpline(const Ionflux::Mapping::AnimatedSpline& other);
		
		/** Destructor.
		 *
		 * Destruct AnimatedSpline object.
		 */
		virtual ~AnimatedSpline();
		
		/** Get shape.
		 *
		 * Get the interpolated Bezier spline shape for the specified 
		 * parameter value.
		 *
		 * \param t Parameter.
		 * \param target Target spline.
		 */
		virtual void getShape(Ionflux::Mapping::MappingValue t, 
		Ionflux::Mapping::BezierSpline& target) const;
		
		/** Evaluate the animated spline.
		 *
		 * Evaluate the animated spline with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::BezierSpline 
		call(Ionflux::Mapping::MappingValue value) const;
		
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
		virtual Ionflux::Mapping::AnimatedSpline& operator=(const 
		Ionflux::Mapping::AnimatedSpline& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::AnimatedSpline* copy() const;
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of keys.
		 *
		 * \return Number of keys.
		 */
		virtual unsigned int getNumKeys() const;
		
		/** Get key.
		 *
		 * Get the key at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Key at specified index.
		 */
		virtual Ionflux::Mapping::BezierSplineKey* getKey(unsigned int 
		elementIndex = 0) const;
		
		/** Find key.
		 *
		 * Find the specified occurence of a key.
		 *
		 * \param needle Key to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the key, or -1 if the key cannot be found.
		 */
		virtual int findKey(Ionflux::Mapping::BezierSplineKey* needle, unsigned 
		int occurence = 1) const;
        
		/** Get spline key vector.
		 *
		 * \return spline key vector.
		 */
		virtual std::vector<Ionflux::Mapping::BezierSplineKey*>& getKeys();
		
		/** Add key.
		 *
		 * Add a key.
		 *
		 * \param addElement Key to be added.
		 */
		virtual void addKey(Ionflux::Mapping::BezierSplineKey* addElement);
		
		/** Remove key.
		 *
		 * Remove a key.
		 *
		 * \param removeElement Key to be removed.
		 */
		virtual void removeKey(Ionflux::Mapping::BezierSplineKey* removeElement);
		
		/** Remove key.
		 *
		 * Remove a key.
		 *
		 * \param removeIndex Key to be removed.
		 */
		virtual void removeKeyIndex(unsigned int removeIndex);
		
		/** Clear keys.
		 *
		 * Clear all keys.
		 */
		virtual void clearKeys();
};

}

}

/** \file AnimatedSpline.hpp
 * \brief Animated Bezier spline (header).
 */
#endif
