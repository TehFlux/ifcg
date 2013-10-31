/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Camera.cpp                      Camera (implementation).
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

#include "geoutils/Camera.hpp"
#include "ifobject/IFLogMessage.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include "ifobject/constants.hpp"
#include "ifobject/objectutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3.hpp"
#include "ifobject/utils.hpp"
#include "ifobject/xmlutils.hpp"
#include "geoutils/xmlutils.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

CameraClassInfo::CameraClassInfo()
{
	name = "Camera";
	desc = "Camera";
}

CameraClassInfo::~CameraClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::Vector3 Camera::DEFAULT_RIGHT = Ionflux::GeoUtils::Vector3(1.33, 0., 0.);
const Ionflux::GeoUtils::CameraSetupFlags Camera::DEFAULT_SETUP_FLAGS = { true, true, true, false, false, false, false };
const Ionflux::GeoUtils::CameraMode Camera::MODE_PERSPECTIVE = 0;
const Ionflux::GeoUtils::CameraMode Camera::MODE_ORTHO = 1;
const bool Camera::DEFAULT_ADJUST_LOCATION = false;

// run-time type information instance constants
const CameraClassInfo Camera::cameraClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Camera::CLASS_INFO = &Camera::cameraClassInfo;

const std::string Camera::XML_ELEMENT_NAME = "camera";

Camera::Camera()
: location(0), direction(0), lookAt(0), right(0), up(0), sky(0), angle(0.), lens(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Camera::Camera(const Ionflux::GeoUtils::Camera& other)
: location(0), direction(0), lookAt(0), right(0), up(0), sky(0), angle(0.), lens(0.)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Camera::Camera(Ionflux::GeoUtils::Vector3 initLocation, 
Ionflux::GeoUtils::Vector3 initDirection, Ionflux::GeoUtils::Vector3 
initLookAt, Ionflux::GeoUtils::Vector3 initRight, 
Ionflux::GeoUtils::Vector3 initUp, Ionflux::GeoUtils::Vector3 initSky, 
double initAngle, double initLens, Ionflux::GeoUtils::CameraSetupFlags 
initSetupFlags)
: location(0), direction(0), lookAt(0), right(0), up(0), sky(0), 
lens(initLens), setupFlags(initSetupFlags)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	setVectors(initLocation, initDirection, initLookAt, 
	    initRight, initUp, initSky);
}

Camera::~Camera()
{
	// TODO: Nothing ATM. ;-)
}

void Camera::checkVectors()
{
	Ionflux::ObjectBase::nullPointerCheck(location, this, 
	    "checkVectors", "Location vector");
	Ionflux::ObjectBase::nullPointerCheck(direction, this, 
	    "checkVectors", "Direction vector");
	Ionflux::ObjectBase::nullPointerCheck(lookAt, this, 
	    "checkVectors", "Look-at vector");
	Ionflux::ObjectBase::nullPointerCheck(right, this, 
	    "checkVectors", "Right vector");
	Ionflux::ObjectBase::nullPointerCheck(up, this, 
	    "checkVectors", "Up vector");
	Ionflux::ObjectBase::nullPointerCheck(sky, this, 
	    "checkVectors", "Sky vector");
}

Ionflux::GeoUtils::Vector3 Camera::getBarycenter()
{
	if (location == 0)
	    return Vector3::ZERO;
	// Adjust for transformation.
	Vertex3 v0(*location);
	if (useTransform())
	    v0.transform(*getTransformMatrix());
	if (useVI())
	    v0.transformVI(*getViewMatrix(), getImageMatrix());
	return v0.getVector();
}

void Camera::applyTransform(bool recursive)
{
	if (!useTransform() && !useVI())
	{
	    clearTransformations();
	    return;
	}
	checkVectors();
	Matrix4 T(getTranslationMatrix());
	Matrix4 R(getRotationMatrix(MODE_ORTHO));
	Matrix4 TR(T * R);
	double dirLen = direction->norm();
	/* Calculate the correct length for the direction 
	   vector. */
	CameraSetupFlags sf = setupFlags;
	if (sf.useLens)
	{
	    angle = 2. * ::atan(16. / lens);
	    sf.useAngle = true;
	}
	if (sf.useAngle)
	    dirLen = 0.5 * right->norm() / ::tan(0.5 * angle);
	setVectors(
	    TR.getC3().getV3(), 
	    TR.getC1().getV3() * dirLen, 
	    *lookAt, 
	    TR.getC0().getV3(), 
	    TR.getC2().getV3(), 
	    TR.getC2().getV3()
	);
	validate();
	clearTransformations();
}

void Camera::initVectors()
{
	if (location == 0)
	    setLocation(Vector3::create());
	if (direction == 0)
	    setDirection(Vector3::create());
	if (lookAt == 0)
	    setLookAt(Vector3::create());
	if (right == 0)
	    setRight(Vector3::create());
	if (up == 0)
	    setUp(Vector3::create());
	if (sky == 0)
	    setSky(Vector3::create());
}

void Camera::setVectors(Ionflux::GeoUtils::Vector3 initLocation, 
Ionflux::GeoUtils::Vector3 initDirection, Ionflux::GeoUtils::Vector3 
initLookAt, Ionflux::GeoUtils::Vector3 initRight, 
Ionflux::GeoUtils::Vector3 initUp, Ionflux::GeoUtils::Vector3 initSky)
{
	initVectors();
	*location = initLocation;
	*direction = initDirection;
	*lookAt = initLookAt;
	*right = initRight;
	*up = initUp;
	*sky = initSky;
}

void Camera::setDefault()
{
	initVectors();
	*location = Vector3::ZERO;
	*direction = Vector3::E_Z;
	*lookAt = Vector3::E_Z;
	*right = DEFAULT_RIGHT;
	*up = Vector3::E_Y;
	*sky = Vector3::E_Y;
	angle = 2. * direction->angle((*direction) + 0.5 * (*right));
	lens = 16. / ::tan(0.5 * angle);
	setupFlags = DEFAULT_SETUP_FLAGS;
}

void Camera::validate(const Ionflux::GeoUtils::CameraSetupFlags* 
newSetupFlags, double t)
{
	checkVectors();
	if (newSetupFlags != 0)
	    setSetupFlags(*newSetupFlags);
	CameraSetupFlags sf = setupFlags;
	// <---- DEBUG ----- //
	std::ostringstream status;
	// ----- DEBUG ----> */
	if (sf.useLens)
	{
	    angle = 2. * ::atan(16. / lens);
	    sf.useAngle = true;
	}
	// Validate angle and direction vector.
	if (!eq(angle, 2. * direction->angle((*direction) + 0.5 * (*right)), t))
	{
	    if (sf.useAngle)
	    {
	        if (sf.useDirection)
	        {
	            status.str("");
	            status << "Direction vector and angle are both enabled but "
	                "not consistent, recalculating direction vector.";
	            log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	                Ionflux::ObjectBase::VL_WARNING, this, "validate"));
	        }
	        *direction = direction->normalize() * 0.5 * right->norm() 
	            / ::tan(0.5 * angle);
	        // <---- DEBUG ----- //
	        std::cerr << "[Camera::validate] DEBUG: "
	             "Adjusted direction vector: (" 
	            << direction->getValueString() << ")" << std::endl;
	        // ----- DEBUG ----> */
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "direction = " << direction.getString();
	        log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	        // ----- DEBUG ----> */
	        if (!sf.useLens)
	            lens = 16. / ::tan(0.5 * angle);
	    } else
	    {
	        // Angle not enabled.
	        angle = 2. * direction->angle((*direction) + 0.5 * (*right));
	        lens = 16. / ::tan(0.5 * angle);
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "angle = " << angle << ", lens = " << lens;
	        log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	        // ----- DEBUG ----> */
	    }
	}
	// Validate lookAt vector.
	if (!sf.useLookAt)
	{
	    *lookAt = *direction;
	    // <---- DEBUG ----- //
	    std::cerr << "[Camera::validate] DEBUG: "
	         "Adjusted lookAt vector: (" 
	        << lookAt->getValueString() << ")" << std::endl;
	    // ----- DEBUG ----> */
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "lookAt = " << lookAt.getString();
	    log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	    // ----- DEBUG ----> */
	} else
	{
	    Vector3 lookAtDirection((*lookAt) - (*location));
	    if (direction->angle(lookAtDirection) != 0.)
	    {
	        if (sf.useDirection)
	        {
	            status.str("");
	            status << "LookAt and direction vectors are both enabled but "
	                "not consistent, recalculating direction vector.";
	            log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	                Ionflux::ObjectBase::VL_WARNING, this, "validate"));
	        }
	        *direction = lookAtDirection.normalize() * direction->norm();
	        // <---- DEBUG ----- //
	        std::cerr << "[Camera::validate] DEBUG: "
	             "Adjusted direction vector: (" 
	            << direction->getValueString() << ")" << std::endl;
	        // ----- DEBUG ----> */
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "direction = " << direction.getString();
	        log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	        // ----- DEBUG ----> */
	        // Use direction implicitly from now on.
	        sf.useDirection = true;
	    }
	}
	// Validate direction, right and up vectors.
	double pi2 = M_PI / 2.;
	if ((!eq(right->angle(*direction), pi2, t)) 
	    || !eq(direction->angle(*up), pi2, t) 
	    || !eq(right->angle(*up), pi2, t))
	{
	    if (!eq(right->angle(*up), pi2, t))
	    {
	        // Orthogonalize right and up vectors.
	        if (sf.useRight)
	        {
	            // <---- DEBUG ----- //
	            status.str("");
	            status << "Up and right vectors are not orthogonal, "
	                "recalculating up vector";
	            log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG, this, "validate"));
	            // ----- DEBUG ----> */
	            *up = right->ortho(*up);
	            // <---- DEBUG ----- //
	            std::cerr << "[Camera::validate] DEBUG: "
	                 "Adjusted up vector: (" 
	                << up->getValueString() << ")" << std::endl;
	            // ----- DEBUG ----> */
	            /* <---- DEBUG ----- //
	            status.str("");
	            status << "up = " << up.getString();
	            log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	            // ----- DEBUG ----> */
	        } else
	        {
	            // Right not enabled.
	            // <---- DEBUG ----- //
	            status.str("");
	            status << "Up and right vectors are not orthogonal, "
	                "recalculating right vector";
	            log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG, this, "validate"));
	            // ----- DEBUG ----> */
	            *right = up->ortho(*right);
	            // <---- DEBUG ----- //
	            std::cerr << "[Camera::validate] DEBUG: "
	                 "Adjusted right vector: (" 
	                << right->getValueString() << ")" << std::endl;
	            // ----- DEBUG ----> */
	            /* <---- DEBUG ----- //
	            status.str("");
	            status << "right = " << right.getString();
	            log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	            // ----- DEBUG ----> */
	        }
	    }
	    if (!sf.useDirection)
	    {
	        // Recalculate direction based on right and up vectors.
	        double directionLength = direction->norm();
	        *direction = right->cross(*up).normalize() * directionLength;
	        // <---- DEBUG ----- //
	        std::cerr << "[Camera::validate] DEBUG: "
	             "Adjusted direction vector: (" 
	            << direction->getValueString() << ")" << std::endl;
	        // ----- DEBUG ----> */
	        /* <---- DEBUG ----- //
	        status.str("");
	        status << "direction = " << direction.getString();
	        log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	        // ----- DEBUG ----> */
	    } else
	    {
	        // Direction is enabled.
	        if (!eq(right->angle(*direction), pi2, t))
	        {
	            // Orthogonalize direction and right vectors.
	            if (sf.useRight)
	            {
	                // <---- DEBUG ----- //
	                status.str("");
	                status << "Direction and right vectors are not "
	                    "orthogonal, recalculating right vector";
	                log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG, this, 
	                    "validate"));
	                // ----- DEBUG ----> */
	            }
	            *right = direction->ortho(*right);
	            // <---- DEBUG ----- //
	            std::cerr << "[Camera::validate] DEBUG: "
	                 "Adjusted right vector: (" 
	                << direction->getValueString() << ")" << std::endl;
	            // ----- DEBUG ----> */
	            /* <---- DEBUG ----- //
	            status.str("");
	            status << "right = " << right.getString();
	            log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	            // ----- DEBUG ----> */
	        }
	        if (!eq(direction->angle(*up), pi2, t))
	        {
	            // Orthogonalize direction and up vectors.
	            if (sf.useUp)
	            {
	                // <---- DEBUG ----- //
	                status.str("");
	                status << "Direction and up vectors are not "
	                    "orthogonal, recalculating right vector";
	                log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG, this, 
	                    "validate"));
	                // ----- DEBUG ----> */
	            }
	            *up = direction->ortho(*up);
	            // <---- DEBUG ----- //
	            std::cerr << "[Camera::validate] DEBUG: "
	                 "Adjusted up vector: (" 
	                << up->getValueString() << ")" << std::endl;
	            // ----- DEBUG ----> */
	            /* <---- DEBUG ----- //
	            status.str("");
	            status << "up = " << up.getString();
	            log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	            // ----- DEBUG ----> */
	        }
	    }
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "angle(right, direction) = " << right.angle(direction) 
	        << ", angle(direction, up) = " << direction.angle(up) 
	        << ", angle(right, up) = " << right.angle(up);
	    log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	    // ----- DEBUG ----> */
	}
	// Validate sky and direction vectors.
	if (sf.useUp && !sf.useSky)
	    *sky = *up;
	if (!eq(sky->angle(*direction), 0., t)
	    && !eq(sky->angle(*direction), pi2, t))
	{
	    // Orthogonalize sky vector.
	    *sky = direction->ortho(*sky);
	    // <---- DEBUG ----- //
	    std::cerr << "[Camera::validate] DEBUG: "
	         "Adjusted sky vector: (" 
	        << sky->getValueString() << ")" << std::endl;
	    // ----- DEBUG ----> */
	    /* <---- DEBUG ----- //
	    status.str("");
	    status << "sky = " << sky.getString();
	    log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "validate"));
	    // ----- DEBUG ----> */
	} else
	if (eq(sky->angle(*direction), 0., t))
	    *sky = *up;
}

Ionflux::GeoUtils::Matrix4 
Camera::getRotationMatrix(Ionflux::GeoUtils::HandednessID handedness, 
Ionflux::GeoUtils::AxisID upAxis, Ionflux::GeoUtils::AxisID depthAxis, 
Ionflux::GeoUtils::AxisID horizonAxis)
{
	checkVectors();
	// <---- DEBUG ----- //
	std::ostringstream status;
	// ----- DEBUG ----> */
	/* NOTE: There is probably a way easier way of doing this by creating a 
	         matrix from the orthonormalized camera axes and inverting it. */
	Vector3 unitUp = Vector3::axis(upAxis);
	Vector3 unitDepth = Vector3::axis(depthAxis);
	Vector3 unitHorizon = Vector3::axis(horizonAxis);
	/* Constants for obtaining direction of rotation depending on 
	   handedness of the coordinate system. */
	double c[2];
	if (handedness == HANDEDNESS_LEFT)
	{
	    c[0] = -1.;
	    c[1] = 1.;
	} else
	{
	    // Assume right-handed coordinate system.
	    c[0] = 1.;
	    c[1] = -1.;
	}
	// Calculate yaw angle (global up axis rotation).
	double yaw = 0.;
	Vector3 hProj(*direction);
	if (direction->angle(unitUp) != 0.)
	{
	    /* Camera is not pointing up. In this case, the yaw angle is the 
	       angle between the projection of the direction vector in the 
	       horizontal plane and the depth axis. */
	    hProj.setElement(upAxis, 0.0);
	    yaw = unitDepth.angle(hProj);
	} else
	{
	    /* The camera is pointing up, so the yaw angle is undefined.
	       We set the projection to the depth axis unit vector, so the 
	      pitch will still be calculated correctly (this will always yield 
	      pi/2). */
	    hProj = unitDepth;
	}
	if (hProj[horizonAxis] > 0.)
	    yaw *= c[1];
	else
	    yaw *= c[0];
	Matrix3 Y(Matrix3::rotate(yaw, upAxis));
	/* Calculate pitch angle (local X rotation)
	   This is the angle between the direction vector and its projection in 
	   the base plane. */
	double pitch = direction->angle(hProj);
	if ((*direction)[upAxis] > 0.)
	    pitch *= c[0];
	else
	    pitch *= c[1];
	Matrix3 P(Matrix3::rotate(pitch, horizonAxis));
	Matrix3 YP = Y * P;
	/* Rotate the up axis unit vector with the pitch and yaw matrices. The 
	   angle between the rotated up axis unit vector and the camera up vector 
	   then defines the roll angle for rotation around the depth axis. */
	//Matrix3 YPInv(YP.invert());
	Vector3 upRot(YP * unitUp);
	double roll = up->angle(upRot);
	if (upRot[horizonAxis] > 0.)
	    roll *= c[0];
	else
	    roll *= c[1];
	Matrix3 R(Matrix3::rotate(roll, depthAxis));
	Matrix4 YPR(YP * R);
	// <---- DEBUG ----- //
	status.str("");
	Vector4 zDir4(Vector3::E_Z * direction->norm());
	status << "upAxis = " << axisToString(upAxis) 
	    << ", depthAxis = " << axisToString(depthAxis) 
	    << ", horizonAxis = " << axisToString(horizonAxis) 
	    << ", handedness = " << handednessToString(handedness) 
	    << ", yaw = " << yaw << " (" << (yaw * 180.0 / M_PI) << "°)"
	    << ", pitch = " << pitch << " (" << (pitch * 180.0 / M_PI) << "°)"
	    << ", roll = " << roll << " (" << (roll * 180.0 / M_PI) << "°)"
	    << ", Y = " << Y
	    << ", P = " << P
	    << ", R = " << R
	    << ", YPR = " << YPR
	    << ", YPR * zDir4 = " << (YPR * zDir4);
	log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "getRotationMatrix"));
	// ----- DEBUG ----> */
	return YPR;
}

Ionflux::GeoUtils::Matrix4 Camera::getTranslationMatrix(bool 
adjustLocation)
{
	checkVectors();
	if (adjustLocation)
	    return Matrix4::translate((*location) + (*direction));
	return Matrix4::translate(*location);
}

Ionflux::GeoUtils::Matrix4 
Camera::getPerspectiveMatrix(Ionflux::GeoUtils::AxisID depthAxis)
{
	checkVectors();
	return Matrix4::perspective(direction->norm(), depthAxis);
}

Ionflux::GeoUtils::Matrix4 
Camera::getModelViewMatrix(Ionflux::GeoUtils::CameraMode mode, bool 
adjustLocation, Ionflux::GeoUtils::HandednessID handedness, 
Ionflux::GeoUtils::AxisID upAxis, Ionflux::GeoUtils::AxisID depthAxis, 
Ionflux::GeoUtils::AxisID horizonAxis)
{
	/* <---- DEBUG ----- //
	ostringstream status;
	// ----- DEBUG ----> */
	Matrix4 T(getTranslationMatrix(adjustLocation));
	Matrix4 R(getRotationMatrix(handedness, upAxis, depthAxis, horizonAxis));
	Matrix4 P;
	if (mode == MODE_ORTHO)
	    P = Matrix4::UNIT;
	else
	    P = getPerspectiveMatrix();
	Matrix4 TR(T * R);
	Matrix4 TRInv = TR.invert();
	/* <---- DEBUG ----- //
	status.str("");
	status << "T = " << T.getString() 
	    << ", R = " << R.getString() 
	    << ", P = " << P.getString();
	log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "getViewMatrix"));
	// ----- DEBUG ----> */
	return P * TRInv;
}

void Camera::setOriginCam(double distance0, double rotX, double rotY, 
double rotZ)
{
	initVectors();
	/* <---- DEBUG ----- //
	ostringstream status;
	// ----- DEBUG ----> */
	Matrix3 RX(Matrix3::rotate(rotX * M_PI / 180., AXIS_X));
	Matrix3 RY(Matrix3::rotate(rotY * M_PI / 180., AXIS_Y));
	Matrix3 RZ(Matrix3::rotate(rotZ * M_PI / 180., AXIS_Z));
	Matrix3 R(RZ * RX * RY);
	*location = R * (-distance0 * Vector3::E_Y);
	*lookAt = Vector3::ZERO;
	*direction = R * Vector3::E_Y;
	*up = R * Vector3::E_Z;
	*right = R * (1.33 * Vector3::E_X);
	*sky = *up;
	setupFlags = DEFAULT_SETUP_FLAGS;
	/* <---- DEBUG ----- //
	status.str("");
	status << "RX = " << RX 
	    << ", RY = " << RY 
	    << ", RZ = " << RZ 
	    << ", R = " << R;
	log(Ionflux::ObjectBase::IFLogMessage(status.str(), 
	Ionflux::ObjectBase::VL_DEBUG_OPT, this, "setOriginCam"));
	// ----- DEBUG ----> */
	validate();
}

std::string Camera::getValueString() const
{
	std::ostringstream status;
	if (location != 0)
	    status << "loc: (" << location->getValueString() << ")";
	else
	    status << "<none>";
	if (direction != 0)
	    status << ", dir: (" << direction->getValueString() << ")";
	else
	    status << "<none>";
	if (lookAt != 0)
	    status << ", lookAt: (" << lookAt->getValueString() << ")";
	else
	    status << "<none>";
	if (up != 0)
	    status << ", up: (" << up->getValueString() << ")";
	else
	    status << "<none>";
	if (right != 0)
	    status << ", right: (" << right->getValueString() << ")";
	else
	    status << "<none>";
	if (sky != 0)
	    status << ", sky: (" << sky->getValueString() << ")";
	else
	    status << "<none>";
	status << ", angle: " << angle << ", lens: " << lens;
	return status.str();
}

void Camera::setLocation(Ionflux::GeoUtils::Vector3* newLocation)
{
	if (location == newLocation)
		return;
    if (newLocation != 0)
        addLocalRef(newLocation);
	if (location != 0)
		removeLocalRef(location);
	location = newLocation;
}

Ionflux::GeoUtils::Vector3* Camera::getLocation() const
{
    return location;
}

void Camera::setDirection(Ionflux::GeoUtils::Vector3* newDirection)
{
	if (direction == newDirection)
		return;
    if (newDirection != 0)
        addLocalRef(newDirection);
	if (direction != 0)
		removeLocalRef(direction);
	direction = newDirection;
}

Ionflux::GeoUtils::Vector3* Camera::getDirection() const
{
    return direction;
}

void Camera::setLookAt(Ionflux::GeoUtils::Vector3* newLookAt)
{
	if (lookAt == newLookAt)
		return;
    if (newLookAt != 0)
        addLocalRef(newLookAt);
	if (lookAt != 0)
		removeLocalRef(lookAt);
	lookAt = newLookAt;
}

Ionflux::GeoUtils::Vector3* Camera::getLookAt() const
{
    return lookAt;
}

void Camera::setRight(Ionflux::GeoUtils::Vector3* newRight)
{
	if (right == newRight)
		return;
    if (newRight != 0)
        addLocalRef(newRight);
	if (right != 0)
		removeLocalRef(right);
	right = newRight;
}

Ionflux::GeoUtils::Vector3* Camera::getRight() const
{
    return right;
}

void Camera::setUp(Ionflux::GeoUtils::Vector3* newUp)
{
	if (up == newUp)
		return;
    if (newUp != 0)
        addLocalRef(newUp);
	if (up != 0)
		removeLocalRef(up);
	up = newUp;
}

Ionflux::GeoUtils::Vector3* Camera::getUp() const
{
    return up;
}

void Camera::setSky(Ionflux::GeoUtils::Vector3* newSky)
{
	if (sky == newSky)
		return;
    if (newSky != 0)
        addLocalRef(newSky);
	if (sky != 0)
		removeLocalRef(sky);
	sky = newSky;
}

Ionflux::GeoUtils::Vector3* Camera::getSky() const
{
    return sky;
}

void Camera::setAngle(double newAngle)
{
	angle = newAngle;
}

double Camera::getAngle() const
{
    return angle;
}

void Camera::setLens(double newLens)
{
	lens = newLens;
}

double Camera::getLens() const
{
    return lens;
}

void Camera::setSetupFlags(const Ionflux::GeoUtils::CameraSetupFlags& 
newSetupFlags)
{
	setupFlags = newSetupFlags;
}

Ionflux::GeoUtils::CameraSetupFlags Camera::getSetupFlags() const
{
    return setupFlags;
}

Ionflux::GeoUtils::Camera& Camera::operator=(const 
Ionflux::GeoUtils::Camera& other)
{
    if (this == &other)
        return *this;
    TransformableObject::operator=(other);
    if (other.location != 0)
        setLocation(other.location->copy());
    else
        setLocation(0);
    if (other.direction != 0)
        setDirection(other.direction->copy());
    else
        setDirection(0);
    if (other.lookAt != 0)
        setLookAt(other.lookAt->copy());
    else
        setLookAt(0);
    if (other.right != 0)
        setRight(other.right->copy());
    else
        setRight(0);
    if (other.up != 0)
        setUp(other.up->copy());
    else
        setUp(0);
    if (other.sky != 0)
        setSky(other.sky->copy());
    else
        setSky(0);
    lens = other.lens;
    angle = other.angle;
    setupFlags = other.setupFlags;
	return *this;
}

Ionflux::GeoUtils::Camera* Camera::copy() const
{
    Camera* newCamera = create();
    *newCamera = *this;
    return newCamera;
}

Ionflux::GeoUtils::Camera* Camera::upcast(Ionflux::ObjectBase::IFObject* 
other)
{
    return dynamic_cast<Camera*>(other);
}

Ionflux::GeoUtils::Camera* Camera::create(Ionflux::ObjectBase::IFObject* 
parentObject)
{
    Camera* newObject = new Camera();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

Ionflux::GeoUtils::Camera* Camera::create(Ionflux::GeoUtils::Vector3 
initLocation, Ionflux::GeoUtils::Vector3 initDirection, 
Ionflux::GeoUtils::Vector3 initLookAt, Ionflux::GeoUtils::Vector3 
initRight, Ionflux::GeoUtils::Vector3 initUp, Ionflux::GeoUtils::Vector3 
initSky, double initAngle, double initLens, 
Ionflux::GeoUtils::CameraSetupFlags initSetupFlags, 
Ionflux::ObjectBase::IFObject* parentObject)
{
    Camera* newObject = new Camera(initLocation, initDirection, initLookAt,
    initRight, initUp, initSky, initAngle, initLens, initSetupFlags);
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

std::string Camera::getXMLElementName() const
{
	return XML_ELEMENT_NAME;
}

std::string Camera::getXMLAttributeData() const
{
	std::string a0(Ionflux::GeoUtils::TransformableObject::getXMLAttributeData());
	std::ostringstream d0;
	if (a0.size() > 0)
	    d0 << a0 << " ";
	d0 << "angle=\"" << angle << "\"";
	d0 << " " << "lens=\"" << lens << "\"";
	return d0.str();
}

void Camera::getXMLChildData(std::string& target, unsigned int indentLevel)
const
{
	std::ostringstream d0;
	std::string bc0;
	Ionflux::GeoUtils::TransformableObject::getXMLChildData(bc0, indentLevel);
	d0 << bc0;
	target = d0.str();
}

void Camera::loadFromXMLFile(const std::string& fileName)
{
	std::string data;
	Ionflux::ObjectBase::readFile(fileName, data);
	/* <---- DEBUG ----- //
	std::cerr << "[Camera::loadFromXMLFile] data = " << data 
	    << std::endl;
	// <---- DEBUG ----- */
	Ionflux::GeoUtils::XMLUtils::getCamera(data, *this);
}

}

}

/** \file Camera.cpp
 * \brief Camera implementation.
 */
