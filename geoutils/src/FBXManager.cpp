/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * FBXManager.cpp                  FBX Manager (implementation).
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

#include "geoutils/FBXManager.hpp"
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

FBXManagerClassInfo::FBXManagerClassInfo()
{
	name = "FBXManager";
	desc = "FBX Manager";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

FBXManagerClassInfo::~FBXManagerClassInfo()
{
}

// run-time type information instance constants
const FBXManagerClassInfo FBXManager::fBXManagerClassInfo;
const Ionflux::ObjectBase::IFClassInfo* FBXManager::CLASS_INFO = &FBXManager::fBXManagerClassInfo;

FBXManager::FBXManager()
: impl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	initImpl();
}

FBXManager::FBXManager(const Ionflux::GeoUtils::FBXManager& other)
: impl(0)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

FBXManager::~FBXManager()
{
	if (impl != 0)
	{
	    impl->Destroy();
	    impl = 0;
	}
}

void FBXManager::initImpl()
{
	FbxManager* fbxm = FbxManager::Create();
	if (fbxm == 0)
	    throw GeoUtilsError(getErrorString(
	        "Could not create FBX manager.", "initFBXManager"));
	FbxIOSettings* ios = FbxIOSettings::Create(fbxm, IOSROOT);
	fbxm->SetIOSettings(ios);
	setImpl(fbxm);
}

std::string FBXManager::getValueString() const
{
	// TODO: Implementation.
	return "";
}

void FBXManager::setImpl(FBXSDK_NAMESPACE::FbxManager* newImpl)
{
	if (newImpl == impl)
	    return;
	if (impl != 0)
	    impl->Destroy();
	impl = newImpl;
}

FBXSDK_NAMESPACE::FbxManager* FBXManager::getImpl() const
{
    return impl;
}

Ionflux::GeoUtils::FBXManager& FBXManager::operator=(const 
Ionflux::GeoUtils::FBXManager& other)
{
    if (this == &other)
        return *this;
    setImpl(other.impl);
	return *this;
}

Ionflux::GeoUtils::FBXManager* FBXManager::copy() const
{
    FBXManager* newFBXManager = create();
    *newFBXManager = *this;
    return newFBXManager;
}

Ionflux::GeoUtils::FBXManager* 
FBXManager::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<FBXManager*>(other);
}

Ionflux::GeoUtils::FBXManager* 
FBXManager::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    FBXManager* newObject = new FBXManager();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int FBXManager::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file FBXManager.cpp
 * \brief FBX Manager implementation.
 */
