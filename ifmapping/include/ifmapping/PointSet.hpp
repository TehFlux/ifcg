#ifndef IONFLUX_MAPPING_POINTSET
#define IONFLUX_MAPPING_POINTSET
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointSet.hpp                    Point set (header).
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
#include "ifmapping/Point.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Class information for class PointSet.
class PointSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PointSetClassInfo();
		/// Destructor.
		virtual ~PointSetClassInfo();
};

/** Point set.
 * \ingroup ifmapping
 *
 * A collection of points.
 */
class PointSet
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Point vector.
		std::vector<Ionflux::Mapping::Point*> points;
		
	public:
		/// Class information instance.
		static const PointSetClassInfo pointSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new PointSet object.
		 */
		PointSet();
		
		/** Constructor.
		 *
		 * Construct new PointSet object.
		 *
		 * \param other Other object.
		 */
		PointSet(const Ionflux::Mapping::PointSet& other);
		
		/** Constructor.
		 *
		 * Construct new PointSet object.
		 *
		 * \param initPoints Control point vector.
		 */
		PointSet(const Ionflux::Mapping::PointVector& initPoints);
		
		/** Destructor.
		 *
		 * Destruct PointSet object.
		 */
		virtual ~PointSet();
		
		/** Get SVG path data.
		 *
		 * Get SVG path data for the point set. The specified image plane 
		 * normal coordinate will be assumed to be orthogonal to the image 
		 * plane and omitted from the path data. The optional \c startIndex 
		 * specified the index of the first point that should be included in 
		 * the path data. The optional \c numPoints specified the number of 
		 * points that should be included in the path data. If this is set to 
		 * zero or a value greater than the number of points in the set, all 
		 * points will be included.
		 *
		 * \param imagePlaneNormal Image plane normal axis.
		 * \param startIndex Start index.
		 * \param numPoints Number of points.
		 *
		 * \return SVG path data.
		 */
		virtual std::string getSVGPathData(const Ionflux::Mapping::CoordinateID 
		imagePlaneNormal = Ionflux::Mapping::C_Z, unsigned int startIndex = 0, 
		unsigned int numPoints = 0) const;
		
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
		virtual Ionflux::Mapping::PointSet& operator=(const 
		Ionflux::Mapping::PointSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::PointSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::PointSet* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::PointSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new PointSet object.
		 *
		 * \param initPoints Control point vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::Mapping::PointSet* create(const 
		Ionflux::Mapping::PointVector& initPoints, Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		
		/** Get number of points.
		 *
		 * \return Number of points.
		 */
		virtual unsigned int getNumPoints() const;
		
		/** Get point.
		 *
		 * Get the point at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Point at specified index.
		 */
		virtual Ionflux::Mapping::Point* getPoint(unsigned int elementIndex = 0) 
		const;
		
		/** Find point.
		 *
		 * Find the specified occurence of a point.
		 *
		 * \param needle Point to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the point, or -1 if the point cannot be found.
		 */
		virtual int findPoint(Ionflux::Mapping::Point* needle, unsigned int 
		occurence = 1) const;
        
		/** Get point vector.
		 *
		 * \return point vector.
		 */
		virtual std::vector<Ionflux::Mapping::Point*>& getPoints();
		
		/** Add point.
		 *
		 * Add a point.
		 *
		 * \param addElement Point to be added.
		 */
		virtual void addPoint(Ionflux::Mapping::Point* addElement);
		
		/** Create point.
		 *
		 * Create a new point which is managed by the point set.
		 *
		 * \return New point.
		 */
		virtual Ionflux::Mapping::Point* addPoint();
		
		/** Add points.
		 *
		 * Add points from a point vector.
		 *
		 * \param newPoints points.
		 */
		virtual void addPoints(const std::vector<Ionflux::Mapping::Point*>& 
		newPoints);
		
		/** Add points.
		 *
		 * Add points from a point set.
		 *
		 * \param newPoints points.
		 */
		virtual void addPoints(Ionflux::Mapping::PointSet* newPoints);
		
		/** Remove point.
		 *
		 * Remove a point.
		 *
		 * \param removeElement Point to be removed.
		 */
		virtual void removePoint(Ionflux::Mapping::Point* removeElement);
		
		/** Remove point.
		 *
		 * Remove a point.
		 *
		 * \param removeIndex Point to be removed.
		 */
		virtual void removePointIndex(unsigned int removeIndex);
		
		/** Clear points.
		 *
		 * Clear all points.
		 */
		virtual void clearPoints();
};

}

}

/** \file PointSet.hpp
 * \brief Point set (header).
 */
#endif
