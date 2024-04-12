#ifndef IONFLUX_GEOUTILS_FBXMANAGER
#define IONFLUX_GEOUTILS_FBXMANAGER
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXManager.hpp                  FBX Manager (header).
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
#include "geoutils/fbxtypes.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class FBXManager.
class FBXManagerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FBXManagerClassInfo();
		/// Destructor.
		virtual ~FBXManagerClassInfo();
};

/** FBX Manager.
 * \ingroup geoutils
 *
 * A wrapper for the FBX manager, which is used to manage the memory for 
 * FBX objects.
 */
class FBXManager
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// FBX manager implementation.
		FBXSDK_NAMESPACE::FbxManager* impl;
		
		/** Initialize the FBX manager implementation.
		 *
		 * Initialize the FBX manager implementation.
		 */
		virtual void initImpl();
		
	public:
		/// Class information instance.
		static const FBXManagerClassInfo fBXManagerClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new FBXManager object.
		 */
		FBXManager();
		
		/** Constructor.
		 *
		 * Construct new FBXManager object.
		 *
		 * \param other Other object.
		 */
		FBXManager(const Ionflux::GeoUtils::FBXManager& other);
		
		/** Destructor.
		 *
		 * Destruct FBXManager object.
		 */
		virtual ~FBXManager();
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
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
		virtual Ionflux::GeoUtils::FBXManager& operator=(const 
		Ionflux::GeoUtils::FBXManager& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::FBXManager* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::FBXManager* 
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
		static Ionflux::GeoUtils::FBXManager* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get fBX manager implementation.
		 *
		 * \return Current value of fBX manager implementation.
		 */
		virtual FBXSDK_NAMESPACE::FbxManager* getImpl() const;
		
		/** Set fBX manager implementation.
		 *
		 * Set new value of fBX manager implementation.
		 *
		 * \param newImpl New value of fBX manager implementation.
		 */
		virtual void setImpl(FBXSDK_NAMESPACE::FbxManager* newImpl);
};

}

}

/** \file FBXManager.hpp
 * \brief FBX Manager (header).
 */
#endif
