#ifndef IONFLUX_GEOUTILS_LOADSVG
#define IONFLUX_GEOUTILS_LOADSVG
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LoadSVG.hpp                     Transform node: Load SVG (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class LoadSVG.
class LoadSVGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		LoadSVGClassInfo();
		/// Destructor.
		virtual ~LoadSVGClassInfo();
};

/** Transform node: Load SVG.
 * \ingroup geoutils
 *
 * A transform node that creates transformable objects from an SVG file. If
 * both file name and element IDs are specified, LoadSVG reads path data 
 * from the SVG file and creates a polygon for each element ID. If no 
 * element IDs are specified, LoadSVG wraps the whole contents of the SVG 
 * file in an SVG object. The node has no inputs and provides one output 
 * group, containing the objects created from the SVG data.
 */
class LoadSVG
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Input file name.
		std::string fileName;
		/// Input element IDs.
		std::vector<std::string> elementIDs;
		
		/** Process inputs.
		 *
		 * Update the outputs of the node by processing the inputs. This 
		 * should be implemented by derived classes.
		 */
		virtual void process();
		
	public:
		/// Class information instance.
		static const LoadSVGClassInfo loadSVGClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new LoadSVG object.
		 */
		LoadSVG();
		
		/** Constructor.
		 *
		 * Construct new LoadSVG object.
		 *
		 * \param other Other object.
		 */
		LoadSVG(const Ionflux::GeoUtils::TransformNodes::LoadSVG& other);
		
		/** Constructor.
		 *
		 * Construct new LoadSVG object.
		 *
		 * \param initFileName .
		 * \param nodeID Node ID.
		 */
		LoadSVG(const std::string& initFileName, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct LoadSVG object.
		 */
		virtual ~LoadSVG();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::LoadSVG& operator=(const 
		Ionflux::GeoUtils::TransformNodes::LoadSVG& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::LoadSVG* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::LoadSVG* 
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
		static Ionflux::GeoUtils::TransformNodes::LoadSVG* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get input file name.
		 *
		 * \return Current value of input file name.
		 */
		virtual std::string getFileName() const;
		
		/** Set input file name.
		 *
		 * Set new value of input file name.
		 *
		 * \param newFileName New value of input file name.
		 */
		virtual void setFileName(const std::string& newFileName);
		
		/** Get number of elementIDs.
		 *
		 * \return Number of elementIDs.
		 */
		virtual unsigned int getNumElementIDs() const;
		
		/** Get elementID.
		 *
		 * Get the elementID at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return ElementID at specified index.
		 */
		virtual std::string getElementID(unsigned int elementIndex = 0) const;
		
		/** Find elementID.
		 *
		 * Find the specified occurence of a elementID.
		 *
		 * \param needle ElementID to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the elementID, or -1 if the elementID cannot be 
		 * found.
		 */
		virtual int findElementID(std::string needle, unsigned int occurence = 1)
		const;
        
		/** Get input element IDs.
		 *
		 * \return input element IDs.
		 */
		virtual std::vector<std::string>& getElementIDs();
		
		/** Add elementID.
		 *
		 * Add a elementID.
		 *
		 * \param addElement ElementID to be added.
		 */
		virtual void addElementID(std::string addElement);
		
		/** Remove elementID.
		 *
		 * Remove a elementID.
		 *
		 * \param removeElement ElementID to be removed.
		 */
		virtual void removeElementID(std::string removeElement);
		
		/** Remove elementID.
		 *
		 * Remove a elementID.
		 *
		 * \param removeIndex ElementID to be removed.
		 */
		virtual void removeElementIDIndex(unsigned int removeIndex);
		
		/** Clear elementIDs.
		 *
		 * Clear all elementIDs.
		 */
		virtual void clearElementIDs();
};

}

}

}

/** \file LoadSVG.hpp
 * \brief Transform node: Load SVG (header).
 */
#endif
