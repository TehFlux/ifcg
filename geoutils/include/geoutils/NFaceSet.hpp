#ifndef IONFLUX_GEOUTILS_NFACESET
#define IONFLUX_GEOUTILS_NFACESET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NFaceSet.hpp                    N-face set (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class NFace;

/// Class information for class NFaceSet.
class NFaceSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NFaceSetClassInfo();
		/// Destructor.
		virtual ~NFaceSetClassInfo();
};

/** N-face set.
 * \ingroup ifvg
 *
 * An set of N-faces.
 */
class NFaceSet
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Vector of nfaces.
		std::vector<Ionflux::GeoUtils::NFace*> nfaces;
		
	public:
		/// Class information instance.
		static const NFaceSetClassInfo nFaceSetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NFaceSet object.
		 */
		NFaceSet();
		
		/** Constructor.
		 *
		 * Construct new NFaceSet object.
		 *
		 * \param other Other object.
		 */
		NFaceSet(const Ionflux::GeoUtils::NFaceSet& other);
		
		/** Destructor.
		 *
		 * Destruct NFaceSet object.
		 */
		virtual ~NFaceSet();
		
		/** Triangle set check.
		 *
		 * Check whether all N-faces in the set are triangles.
		 *
		 * \return \c true if the N-face set is a triangle set, \c false 
		 * otherwise.
		 */
		virtual bool isTriSet() const;
		
		/** Quad set check.
		 *
		 * Check whether all N-faces in the set are quads.
		 *
		 * \return \c true if the N-face set is a quad set, \c false otherwise.
		 */
		virtual bool isQuadSet() const;
		
		/** Edge set check.
		 *
		 * Check whether all N-faces in the set are edges.
		 *
		 * \return \c true if the N-face set is an edge set, \c false otherwise.
		 */
		virtual bool isEdgeSet() const;
		
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
		virtual Ionflux::GeoUtils::NFaceSet& operator=(const 
		Ionflux::GeoUtils::NFaceSet& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::NFaceSet* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::NFaceSet* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::GeoUtils::NFaceSet* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of nFaces.
		 *
		 * \return Number of nFaces.
		 */
		virtual unsigned int getNumNFaces() const;
		
		/** Get nFace.
		 *
		 * Get the nFace at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return NFace at specified index.
		 */
		virtual Ionflux::GeoUtils::NFace* getNFace(unsigned int elementIndex = 0)
		const;
		
		/** Find nFace.
		 *
		 * Find the specified occurence of a nFace.
		 *
		 * \param needle NFace to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the nFace, or -1 if the nFace cannot be found.
		 */
		virtual int findNFace(Ionflux::GeoUtils::NFace* needle, unsigned int 
		occurence = 1) const;
        
		/** Get vector of nfaces.
		 *
		 * \return vector of nfaces.
		 */
		virtual std::vector<Ionflux::GeoUtils::NFace*>& getNFaces();
		
		/** Add nFace.
		 *
		 * Add a nFace.
		 *
		 * \param addElement NFace to be added.
		 */
		virtual void addNFace(Ionflux::GeoUtils::NFace* addElement);
		
		/** Create nFace.
		 *
		 * Create a new nFace which is managed by the nFace set.
		 *
		 * \return New nFace.
		 */
		virtual Ionflux::GeoUtils::NFace* addNFace();
		
		/** Add nFaces.
		 *
		 * Add nFaces from a nFace vector.
		 *
		 * \param newNFaces nFaces.
		 */
		virtual void addNFaces(const std::vector<Ionflux::GeoUtils::NFace*>& 
		newNFaces);
		
		/** Add nFaces.
		 *
		 * Add nFaces from a nFace set.
		 *
		 * \param newNFaces nFaces.
		 */
		virtual void addNFaces(Ionflux::GeoUtils::NFaceSet* newNFaces);
		
		/** Remove nFace.
		 *
		 * Remove a nFace.
		 *
		 * \param removeElement NFace to be removed.
		 */
		virtual void removeNFace(Ionflux::GeoUtils::NFace* removeElement);
		
		/** Remove nFace.
		 *
		 * Remove a nFace.
		 *
		 * \param removeIndex NFace to be removed.
		 */
		virtual void removeNFaceIndex(unsigned int removeIndex);
		
		/** Clear nFaces.
		 *
		 * Clear all nFaces.
		 */
		virtual void clearNFaces();
};

}

}

/** \file NFaceSet.hpp
 * \brief N-face set (header).
 */
#endif
