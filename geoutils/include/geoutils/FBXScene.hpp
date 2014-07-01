#ifndef IONFLUX_GEOUTILS_FBXSCENE
#define IONFLUX_GEOUTILS_FBXSCENE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXScene.hpp                    FBX Scene (header).
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
#include "geoutils/utils.hpp"
#include "geoutils/fbxtypes.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class FBXScene.
class FBXSceneClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FBXSceneClassInfo();
		/// Destructor.
		virtual ~FBXSceneClassInfo();
};

/** FBX Scene.
 * \ingroup geoutils
 *
 * A 3D scene loaded using the Autodesk FBX SDK. This can be used to 
 * convert data loaded from an FBX file to the data structures used by 
 * GeoUtils.
 */
class FBXScene
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// FBX manager.
		FBXSDK_NAMESPACE::FbxManager* fbxManager;
		/// FBX scene.
		FBXSDK_NAMESPACE::FbxScene* fbxScene;
		/// title.
		std::string title;
		/// subject.
		std::string subject;
		/// author.
		std::string author;
		/// keywords.
		std::string keywords;
		/// revision.
		std::string revision;
		/// comment.
		std::string comment;
		
		/** Initialize the FBX manager.
		 *
		 * Initialize the FBX manager.
		 */
		virtual void initFBXManager();
		
		/** Initialize the FBX scene.
		 *
		 * Initialize the FBX scene.
		 */
		virtual void initFBXScene();
		
		/** Initialize metadata.
		 *
		 * Initialize the metadata properties.
		 */
		virtual void initMetaData();
		
		/** Set title.
		 *
		 * Set new value of title.
		 *
		 * \param newTitle New value of title.
		 */
		virtual void setTitle(const std::string& newTitle);
		
		/** Set subject.
		 *
		 * Set new value of subject.
		 *
		 * \param newSubject New value of subject.
		 */
		virtual void setSubject(const std::string& newSubject);
		
		/** Set author.
		 *
		 * Set new value of author.
		 *
		 * \param newAuthor New value of author.
		 */
		virtual void setAuthor(const std::string& newAuthor);
		
		/** Set keywords.
		 *
		 * Set new value of keywords.
		 *
		 * \param newKeywords New value of keywords.
		 */
		virtual void setKeywords(const std::string& newKeywords);
		
		/** Set revision.
		 *
		 * Set new value of revision.
		 *
		 * \param newRevision New value of revision.
		 */
		virtual void setRevision(const std::string& newRevision);
		
		/** Set comment.
		 *
		 * Set new value of comment.
		 *
		 * \param newComment New value of comment.
		 */
		virtual void setComment(const std::string& newComment);
		
	public:
		/// Class information instance.
		static const FBXSceneClassInfo fBXSceneClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new FBXScene object.
		 */
		FBXScene();
		
		/** Constructor.
		 *
		 * Construct new FBXScene object.
		 *
		 * \param other Other object.
		 */
		FBXScene(const Ionflux::GeoUtils::FBXScene& other);
		
		/** Destructor.
		 *
		 * Destruct FBXScene object.
		 */
		virtual ~FBXScene();
		
		/** Load scene from file.
		 *
		 * Load a scene from the specified file.
		 *
		 * \param fileName File name.
		 *
		 * \return \c true on success, \c false otherwise.
		 */
		virtual bool loadFromFile(const std::string& fileName);
		
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
		virtual Ionflux::GeoUtils::FBXScene& operator=(const 
		Ionflux::GeoUtils::FBXScene& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::FBXScene* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::FBXScene* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::GeoUtils::FBXScene* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get fBX manager.
		 *
		 * \return Current value of fBX manager.
		 */
		virtual FBXSDK_NAMESPACE::FbxManager* getFbxManager() const;
		
		/** Set fBX manager.
		 *
		 * Set new value of fBX manager.
		 *
		 * \param newFbxManager New value of fBX manager.
		 */
		virtual void setFbxManager(FBXSDK_NAMESPACE::FbxManager* newFbxManager);
		
		/** Get fBX scene.
		 *
		 * \return Current value of fBX scene.
		 */
		virtual FBXSDK_NAMESPACE::FbxScene* getFbxScene() const;
		
		/** Set fBX scene.
		 *
		 * Set new value of fBX scene.
		 *
		 * \param newFbxScene New value of fBX scene.
		 */
		virtual void setFbxScene(FBXSDK_NAMESPACE::FbxScene* newFbxScene);
		
		/** Get title.
		 *
		 * \return Current value of title.
		 */
		virtual std::string getTitle() const;
		
		/** Get subject.
		 *
		 * \return Current value of subject.
		 */
		virtual std::string getSubject() const;
		
		/** Get author.
		 *
		 * \return Current value of author.
		 */
		virtual std::string getAuthor() const;
		
		/** Get keywords.
		 *
		 * \return Current value of keywords.
		 */
		virtual std::string getKeywords() const;
		
		/** Get revision.
		 *
		 * \return Current value of revision.
		 */
		virtual std::string getRevision() const;
		
		/** Get comment.
		 *
		 * \return Current value of comment.
		 */
		virtual std::string getComment() const;
};

}

}

/** \file FBXScene.hpp
 * \brief FBX Scene (header).
 */
#endif
