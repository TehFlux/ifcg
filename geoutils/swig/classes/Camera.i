/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Camera.i                        Camera (interface).
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
#include "geoutils/Camera.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class CameraClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        CameraClassInfo();
        virtual ~CameraClassInfo();
};

class Camera
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::Vector3 DEFAULT_RIGHT;
		static const Ionflux::GeoUtils::CameraSetupFlags DEFAULT_SETUP_FLAGS;
		static const Ionflux::GeoUtils::CameraMode MODE_PERSPECTIVE;
		static const Ionflux::GeoUtils::CameraMode MODE_ORTHO;
		static const bool DEFAULT_ADJUST_LOCATION;
        
        Camera();
		Camera(const Ionflux::GeoUtils::Camera& other);
        Camera(Ionflux::GeoUtils::Vector3 initLocation, 
        Ionflux::GeoUtils::Vector3 initDirection = 
        Ionflux::GeoUtils::Vector3::E_Z, Ionflux::GeoUtils::Vector3 
        initLookAt = Ionflux::GeoUtils::Vector3::E_Z, 
        Ionflux::GeoUtils::Vector3 initRight = 
        Ionflux::GeoUtils::Camera::DEFAULT_RIGHT, 
        Ionflux::GeoUtils::Vector3 initUp = 
        Ionflux::GeoUtils::Vector3::E_Y, Ionflux::GeoUtils::Vector3 initSky
        = Ionflux::GeoUtils::Vector3::E_Y, double initAngle = 1., double 
        initLens = 24., Ionflux::GeoUtils::CameraSetupFlags initSetupFlags 
        = Ionflux::GeoUtils::Camera::DEFAULT_SETUP_FLAGS);
        virtual ~Camera();
        virtual void setDefault();
        virtual void validate(const Ionflux::GeoUtils::CameraSetupFlags* 
        newSetupFlags = 0, double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual Ionflux::GeoUtils::Matrix4 
        getRotationMatrix(Ionflux::GeoUtils::HandednessID handedness = 
        Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID 
        upAxis = Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID 
        depthAxis = Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID 
        horizonAxis = Ionflux::GeoUtils::AXIS_X);
        virtual Ionflux::GeoUtils::Matrix4 getTranslationMatrix(bool 
        adjustLocation = 
        Ionflux::GeoUtils::Camera::DEFAULT_ADJUST_LOCATION);
        virtual Ionflux::GeoUtils::Matrix4 
        getPerspectiveMatrix(Ionflux::GeoUtils::AxisID depthAxis = 
        Ionflux::GeoUtils::AXIS_Y);
        virtual Ionflux::GeoUtils::Matrix4 
        getViewMatrix(Ionflux::GeoUtils::CameraMode mode = 
        Ionflux::GeoUtils::Camera::MODE_PERSPECTIVE, bool adjustLocation = 
        Ionflux::GeoUtils::Camera::DEFAULT_ADJUST_LOCATION, 
        Ionflux::GeoUtils::HandednessID handedness = 
        Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID 
        upAxis = Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID 
        depthAxis = Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID 
        horizonAxis = Ionflux::GeoUtils::AXIS_X);
        virtual void setOriginCam(double distance = 10., double rotX = 
        -30., double rotY = 0., double rotZ = 30.);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::Camera* copy() const;
        virtual void setLocation(const Ionflux::GeoUtils::Vector3& 
        newLocation);
        virtual Ionflux::GeoUtils::Vector3 getLocation() const;
        virtual void setDirection(const Ionflux::GeoUtils::Vector3& 
        newDirection);
        virtual Ionflux::GeoUtils::Vector3 getDirection() const;
        virtual void setLookAt(const Ionflux::GeoUtils::Vector3& 
        newLookAt);
        virtual Ionflux::GeoUtils::Vector3 getLookAt() const;
        virtual void setRight(const Ionflux::GeoUtils::Vector3& newRight);
        virtual Ionflux::GeoUtils::Vector3 getRight() const;
        virtual void setUp(const Ionflux::GeoUtils::Vector3& newUp);
        virtual Ionflux::GeoUtils::Vector3 getUp() const;
        virtual void setSky(const Ionflux::GeoUtils::Vector3& newSky);
        virtual Ionflux::GeoUtils::Vector3 getSky() const;
        virtual void setAngle(double newAngle);
        virtual double getAngle() const;
        virtual void setLens(double newLens);
        virtual double getLens() const;
        virtual void setSetupFlags(const 
        Ionflux::GeoUtils::CameraSetupFlags& newSetupFlags);
        virtual Ionflux::GeoUtils::CameraSetupFlags getSetupFlags() const;
};

}

}
