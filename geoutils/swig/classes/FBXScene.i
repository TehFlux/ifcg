/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXScene.i                      FBX Scene (interface).
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
%{
#include "geoutils/FBXScene.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FBXManager;
class FBXNode;

class FBXSceneClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FBXSceneClassInfo();
        virtual ~FBXSceneClassInfo();
};

class FBXScene
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        FBXScene();
		FBXScene(const Ionflux::GeoUtils::FBXScene& other);
        FBXScene(Ionflux::GeoUtils::FBXManager* initFbxManager);
        virtual ~FBXScene();
        virtual bool loadFromFile(const std::string& fileName);
        virtual Ionflux::GeoUtils::FBXNode* getRootNode() const;
        virtual void listNodes(bool recursive = true, unsigned int 
        indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char 
        indentChar = ' ') const;
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::FBXScene* copy() const;
		static Ionflux::GeoUtils::FBXScene* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::FBXScene* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setFbxManager(Ionflux::GeoUtils::FBXManager* 
        newFbxManager);
        virtual Ionflux::GeoUtils::FBXManager* getFbxManager() const;
        virtual std::string getTitle() const;
        virtual std::string getSubject() const;
        virtual std::string getAuthor() const;
        virtual std::string getKeywords() const;
        virtual std::string getRevision() const;
        virtual std::string getComment() const;
};

}

}
