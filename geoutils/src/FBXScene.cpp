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

#include "geoutils/FBXScene.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fbxsdk.h>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/FBXManager.hpp"
#include "geoutils/FBXNode.hpp"

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
: fbxManager(0), impl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

FBXScene::FBXScene(const Ionflux::GeoUtils::FBXScene& other)
: fbxManager(0), impl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FBXScene::FBXScene(Ionflux::GeoUtils::FBXManager* initFbxManager)
: fbxManager(0), impl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	if (initFbxManager != 0)
	    setFbxManager(initFbxManager);
}

FBXScene::~FBXScene()
{
	if (impl != 0)
	{
	    impl->Destroy();
	    impl = 0;
	}
}

void FBXScene::initImpl()
{
	Ionflux::ObjectBase::nullPointerCheck(fbxManager, this, 
	    "initFBXScene", "FBX manager");
	std::string sceneName(id);
	if (sceneName.size() == 0)
	    sceneName = "Unnamed Scene";
	FbxScene* fbxs = FbxScene::Create(fbxManager->getImpl(), 
	    sceneName.c_str());
	if (fbxs == 0)
	    throw GeoUtilsError(getErrorString(
	        "Could not create FBX scene.", "initFBXScene"));
	setImpl(fbxs);
}

void FBXScene::initMetaData()
{
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "initMetadata", "FBX scene");
	FbxDocumentInfo* sceneInfo = impl->GetSceneInfo();
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
	if (impl == 0)
	    initImpl();
	Ionflux::ObjectBase::nullPointerCheck(impl, this, 
	    "loadFromFile", "FBX scene");
	FbxManager* mImpl = fbxManager->getImpl();
	FbxImporter* imp0 = FbxImporter::Create(mImpl, "");
	bool result = imp0->Initialize(fileName.c_str(), -1, 
	    mImpl->GetIOSettings());
	if (!result)
	{
	    FbxString es0 = imp0->GetStatus().GetErrorString();
	    std::ostringstream status;
	    status << "Error importing file '" << fileName << ": " 
	        << es0.Buffer();
	    throw GeoUtilsError(getErrorString(status.str(), 
	        "loadFromFile"));
	}
	result = imp0->Import(impl);
	if (!result)
	{
	    FbxString es0 = imp0->GetStatus().GetErrorString();
	    std::ostringstream status;
	    status << "Error importing file '" << fileName << ": " 
	        << es0.Buffer();
	    throw GeoUtilsError(getErrorString(status.str(), 
	        "loadFromFile"));
	}
	imp0->Destroy();
	initMetaData();
	return true;
}

Ionflux::GeoUtils::FBXNode* FBXScene::getRootNode() const
{
	if (impl == 0)
	    return 0;
	FBXNode* r0 = FBXNode::create(impl->GetRootNode());
	return r0;
}

void FBXScene::listNodes(bool recursive, unsigned int indentWidth, char 
indentChar) const
{
	FBXNode* r0 = getRootNode();
	if (r0 == 0)
	    return;
	addLocalRef(r0);
	std::cout << "[root: " << r0->getValueString() << "]" << std::endl;
	r0->listChildNodesFBX(recursive, indentWidth, indentChar, 1);
	removeLocalRef(r0);
}

Ionflux::GeoUtils::FBXNode* FBXScene::findChildNodeByName(const 
std::string& needle, bool recursive)
{
	FBXNode* r0 = getRootNode();
	if (r0 == 0)
	    return 0;
	if (r0->getName() == needle)
	    return r0;
	if (!recursive)
	    return r0;
	addLocalRef(r0);
	FBXNode* result = r0->findChildNodeByNameFBX(needle, recursive);
	removeLocalRef(r0);
	return result;
}

std::string FBXScene::getValueString() const
{
	// TODO: Implementation.
	return "";
}

void FBXScene::setFbxManager(Ionflux::GeoUtils::FBXManager* newFbxManager)
{
	if (fbxManager == newFbxManager)
		return;
    if (newFbxManager != 0)
        addLocalRef(newFbxManager);
	if (fbxManager != 0)
		removeLocalRef(fbxManager);
	fbxManager = newFbxManager;
}

Ionflux::GeoUtils::FBXManager* FBXScene::getFbxManager() const
{
    return fbxManager;
}

void FBXScene::setImpl(FBXSDK_NAMESPACE::FbxScene* newImpl)
{
	if (newImpl == impl)
	    return;
	if (impl != 0)
	    impl->Destroy();
	impl = newImpl;
}

FBXSDK_NAMESPACE::FbxScene* FBXScene::getImpl() const
{
    return impl;
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
    setImpl(other.impl);
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
