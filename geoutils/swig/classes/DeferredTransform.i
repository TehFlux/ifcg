/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * DeferredTransform.i             Deferred matrix transformation 
 * (interface).
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
#include "geoutils/DeferredTransform.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix4;
class Vector;
class VectorSet;

class DeferredTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DeferredTransformClassInfo();
        virtual ~DeferredTransformClassInfo();
};

class DeferredTransform
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const double COMPARE_TOLERANCE;
        
        DeferredTransform();
		DeferredTransform(const Ionflux::GeoUtils::DeferredTransform& other);
        virtual ~DeferredTransform();
        virtual void resetTransform();
        virtual void resetVI();
        virtual void reset();
        virtual void clear();
        virtual Ionflux::GeoUtils::DeferredTransform& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::DeferredTransform& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual bool checkTransform(double t = COMPARE_TOLERANCE);
        virtual bool checkVI(double t = COMPARE_TOLERANCE);
        virtual bool eq(const Ionflux::GeoUtils::DeferredTransform& other, 
        double t = COMPARE_TOLERANCE) const;
        virtual bool operator==(const Ionflux::GeoUtils::DeferredTransform&
        other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::DeferredTransform&
        other) const;
        virtual bool useTransform() const;
        virtual bool useVI() const;
        virtual bool transformChanged() const;
        virtual bool viChanged() const;
        virtual bool isIdentity() const;
        virtual void applyTransform(const Ionflux::GeoUtils::Vector& v, 
        Ionflux::GeoUtils::Vector& target, bool clearTransform = true);
        virtual void applyVI(const Ionflux::GeoUtils::Vector& v, 
        Ionflux::GeoUtils::Vector& target, bool clearTransform = true);
        virtual void applyTransform(const Ionflux::GeoUtils::VectorSet& 
        vectors, Ionflux::GeoUtils::VectorSet& target, bool clearTransform 
        = true);
        virtual void applyVI(const Ionflux::GeoUtils::VectorSet& vectors, 
        Ionflux::GeoUtils::VectorSet& target, bool clearTransform = true);
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::DeferredTransform* copy() const;
		static Ionflux::GeoUtils::DeferredTransform* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::DeferredTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setTransformMatrix(Ionflux::GeoUtils::Matrix4* 
        newTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getTransformMatrix() const;
        virtual void setViewMatrix(Ionflux::GeoUtils::Matrix4* 
        newViewMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getViewMatrix() const;
        virtual void setImageMatrix(Ionflux::GeoUtils::Matrix4* 
        newImageMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getImageMatrix() const;
        virtual void setLastTransformMatrix(Ionflux::GeoUtils::Matrix4* 
        newLastTransformMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getLastTransformMatrix() const;
        virtual void setLastViewMatrix(Ionflux::GeoUtils::Matrix4* 
        newLastViewMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getLastViewMatrix() const;
        virtual void setLastImageMatrix(Ionflux::GeoUtils::Matrix4* 
        newLastImageMatrix);
        virtual Ionflux::GeoUtils::Matrix4* getLastImageMatrix() const;
};

}

}
