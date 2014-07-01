/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXScene.cpp                    FBX Scene (implementation).
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

#include "geoutils/FBXScene.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fbxsdk.h>
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"

namespace Ionflux
{

namespace GeoUtils
{

FBXSceneClassInfo::FBXSceneClassInfo()
{
	name = "FBXScene";
	desc = "FBX Scene";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

FBXSceneClassInfo::~FBXSceneClassInfo()
{
}

// run-time type information instance constants
const FBXSceneClassInfo FBXScene::fBXSceneClassInfo;
const Ionflux::ObjectBase::IFClassInfo* FBXScene::CLASS_INFO = &FBXScene::fBXSceneClassInfo;

FBXScene::FBXScene()
: fbxManager(0), fbxScene(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initFBXManager();
}

FBXScene::FBXScene(const Ionflux::GeoUtils::FBXScene& other)
: fbxManager(0), fbxScene(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FBXScene::~FBXScene()
{
	if (fbxManager != 0)
	{
	    fbxManager->Destroy();
	    fbxManager = 0;
	}
	fbxScene = 0;
}

void FBXScene::initFBXManager()
{
	FbxManager* fbxm = FbxManager::Create();
	if (fbxm == 0)
	    throw GeoUtilsError(getErrorString(
	        "Could not create FBX manager.", "initFBXManager"));
	FbxIOSettings* ios = FbxIOSettings::Create(fbxm, IOSROOT);
	fbxm->SetIOSettings(ios);
	setFbxManager(fbxm);
}

void FBXScene::initFBXScene()
{
	Ionflux::ObjectBase::nullPointerCheck(fbxManager, this, 
	    "initFBXScene", "FBX manager");
	std::string sceneName(id);
	if (sceneName.size() == 0)
	    sceneName = "Unnamed Scene";
	FbxScene* fbxs = FbxScene::Create(fbxManager, sceneName.c_str());
	if (fbxs == 0)
	    throw GeoUtilsError(getErrorString(
	        "Could not create FBX scene.", "initFBXScene"));
	setFbxScene(fbxs);
}

void FBXScene::initMetaData()
{
	Ionflux::ObjectBase::nullPointerCheck(fbxScene, this, 
	    "initMetadata", "FBX scene");
	FbxDocumentInfo* sceneInfo = fbxScene->GetSceneInfo();
	if (sceneInfo != 0)
	{
	    setTitle(sceneInfo->mTitle.Buffer());
	    setSubject(sceneInfo->mSubject.Buffer());
	    setAuthor(sceneInfo->mAuthor.Buffer());
	    setKeywords(sceneInfo->mKeywords.Buffer());
	    setRevision(sceneInfo->mRevision.Buffer());
	    setComment(sceneInfo->mComment.Buffer());
	}
}

bool FBXScene::loadFromFile(const std::string& fileName)
{
	Ionflux::ObjectBase::nullPointerCheck(fbxManager, this, 
	    "loadFromFile", "FBX manager");
	if (fbxScene == 0)
	    initFBXScene();
	Ionflux::ObjectBase::nullPointerCheck(fbxScene, this, 
	    "loadFromFile", "FBX scene");
	FbxImporter* imp = FbxImporter::Create(fbxManager, "");
	bool result = imp->Initialize(fileName.c_str(), -1, 
	    fbxManager->GetIOSettings());
	if (!result)
	{
	    FbxString es0 = imp->GetStatus().GetErrorString();
	    std::ostringstream status;
	    status << "Error importing file '" << fileName << ": " 
	        << es0.Buffer();
	    throw GeoUtilsError(getErrorString(status.str(), 
	        "loadFromFile"));
	}
	result = imp->Import(fbxScene);
	if (!result)
	{
	    FbxString es0 = imp->GetStatus().GetErrorString();
	    std::ostringstream status;
	    status << "Error importing file '" << fileName << ": " 
	        << es0.Buffer();
	    throw GeoUtilsError(getErrorString(status.str(), 
	        "loadFromFile"));
	}
	imp->Destroy();
	initMetaData();
	return true;
}

std::string FBXScene::getValueString() const
{
	// TODO: Implementation.
	return "";
}

void FBXScene::setFbxManager(FBXSDK_NAMESPACE::FbxManager* newFbxManager)
{
	if (newFbxManager == fbxManager)
	    return;
	if (fbxManager != 0)
	    fbxManager->Destroy();
	fbxManager = newFbxManager;
}

FBXSDK_NAMESPACE::FbxManager* FBXScene::getFbxManager() const
{
    return fbxManager;
}

void FBXScene::setFbxScene(FBXSDK_NAMESPACE::FbxScene* newFbxScene)
{
	if (newFbxScene == fbxScene)
	    return;
	if (fbxScene != 0)
	    fbxScene->Destroy();
	fbxScene = newFbxScene;
}

FBXSDK_NAMESPACE::FbxScene* FBXScene::getFbxScene() const
{
    return fbxScene;
}

void FBXScene::setTitle(const std::string& newTitle)
{
	title = newTitle;
}

std::string FBXScene::getTitle() const
{
    return title;
}

void FBXScene::setSubject(const std::string& newSubject)
{
	subject = newSubject;
}

std::string FBXScene::getSubject() const
{
    return subject;
}

void FBXScene::setAuthor(const std::string& newAuthor)
{
	author = newAuthor;
}

std::string FBXScene::getAuthor() const
{
    return author;
}

void FBXScene::setKeywords(const std::string& newKeywords)
{
	keywords = newKeywords;
}

std::string FBXScene::getKeywords() const
{
    return keywords;
}

void FBXScene::setRevision(const std::string& newRevision)
{
	revision = newRevision;
}

std::string FBXScene::getRevision() const
{
    return revision;
}

void FBXScene::setComment(const std::string& newComment)
{
	comment = newComment;
}

std::string FBXScene::getComment() const
{
    return comment;
}

Ionflux::GeoUtils::FBXScene& FBXScene::operator=(const 
Ionflux::GeoUtils::FBXScene& other)
{
    if (this == &other)
        return *this;
    setFbxManager(other.fbxManager);
    setFbxScene(other.fbxScene);
	return *this;
}

Ionflux::GeoUtils::FBXScene* FBXScene::copy() const
{
    FBXScene* newFBXScene = create();
    *newFBXScene = *this;
    return newFBXScene;
}

Ionflux::GeoUtils::FBXScene* 
FBXScene::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<FBXScene*>(other);
}

Ionflux::GeoUtils::FBXScene* 
FBXScene::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    FBXScene* newObject = new FBXScene();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int FBXScene::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file FBXScene.cpp
 * \brief FBX Scene implementation.
 */
