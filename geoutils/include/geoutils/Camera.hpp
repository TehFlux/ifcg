#ifndef IONFLUX_GEOUTILS_CAMERA
#define IONFLUX_GEOUTILS_CAMERA
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Camera.hpp                      Camera (header).
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
#include "geoutils/Vector3.hpp"
#include "geoutils/Vector4.hpp"
#include "geoutils/Matrix4.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Camera.
class CameraClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		CameraClassInfo();
		/// Destructor.
		virtual ~CameraClassInfo();
};

/** Camera.
 * \ingroup geoutils
 *
 * This class implements calculation of camera transformations which are 
 * useful if a scene needs to be transformed as it would be seen from a 
 * camera set up at a specific point in 3D-space.
 * 
 * The camera orientation can be controlled using several direction 
 * vectors:
 * 
 * direction -- The direction in which the camera is pointing. The length 
 * of this  vector determines perspective.
 * lookAt -- A point in space at which the camera is pointed.
 * right -- Vector pointing from the left to the right edge of the screen. 
 * This vector in conjunction with up determines the screen size.
 * up -- Vector pointing from the bottom to the top edge of the screen. 
 * This vector in conjunction with right determines the screen size.
 * sky -- Vector pointing towards the sky. This vector can be used to roll 
 * the camera along the direction axis without explicitly calculating the 
 * up vector.
 * angle -- View angle. This is equal to the twice the angle between the 
 * direction vector and the sum of the direction vector and half the right 
 * vector.
 */
class Camera
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Location vector.
		Ionflux::GeoUtils::Vector3 location;
		/// Direction vector.
		Ionflux::GeoUtils::Vector3 direction;
		/// Look-at vector.
		Ionflux::GeoUtils::Vector3 lookAt;
		/// Right vector.
		Ionflux::GeoUtils::Vector3 right;
		/// Up vector.
		Ionflux::GeoUtils::Vector3 up;
		/// Sky vector.
		Ionflux::GeoUtils::Vector3 sky;
		/// Angle.
		double angle;
		/// Lens.
		double lens;
		/// Setup flags.
		Ionflux::GeoUtils::CameraSetupFlags setupFlags;
		
	public:
		/// Default right vector.
		static const Ionflux::GeoUtils::Vector3 DEFAULT_RIGHT;
		/// Default camera setup flags.
		static const Ionflux::GeoUtils::CameraSetupFlags DEFAULT_SETUP_FLAGS;
		/// Camera mode: perspective.
		static const Ionflux::GeoUtils::CameraMode MODE_PERSPECTIVE;
		/// Camera mode: orthogonal.
		static const Ionflux::GeoUtils::CameraMode MODE_ORTHO;
		/// Offset camera location by direction vector by default.
		static const bool DEFAULT_ADJUST_LOCATION;
		/// Class information instance.
		static const CameraClassInfo cameraClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Camera object.
		 */
		Camera();
		
		/** Constructor.
		 *
		 * Construct new Camera object.
		 *
		 * \param other Other object.
		 */
		Camera(const Ionflux::GeoUtils::Camera& other);
		
		/** Constructor.
		 *
		 * Construct new Camera object.
		 *
		 * \param initLocation Location vector.
		 * \param initDirection Direction vector.
		 * \param initLookAt Look-at vector.
		 * \param initRight Right vector.
		 * \param initUp Up vector.
		 * \param initSky Sky vector.
		 * \param initAngle Angle.
		 * \param initLens Lens.
		 * \param initSetupFlags Setup flags.
		 */
		Camera(Ionflux::GeoUtils::Vector3 initLocation, 
		Ionflux::GeoUtils::Vector3 initDirection = 
		Ionflux::GeoUtils::Vector3::E_Z, Ionflux::GeoUtils::Vector3 initLookAt = 
		Ionflux::GeoUtils::Vector3::E_Z, Ionflux::GeoUtils::Vector3 initRight = 
		Ionflux::GeoUtils::Camera::DEFAULT_RIGHT, Ionflux::GeoUtils::Vector3 
		initUp = Ionflux::GeoUtils::Vector3::E_Y, Ionflux::GeoUtils::Vector3 
		initSky = Ionflux::GeoUtils::Vector3::E_Y, double initAngle = 1., double 
		initLens = 24., Ionflux::GeoUtils::CameraSetupFlags initSetupFlags = 
		Ionflux::GeoUtils::Camera::DEFAULT_SETUP_FLAGS);
		
		/** Destructor.
		 *
		 * Destruct Camera object.
		 */
		virtual ~Camera();
		
		/** Use default settings.
		 *
		 * Initializes the camera settings with default values. The default 
		 * camera is at the coordinate origin, looking in positive Z 
		 * direction, with a screen aspect ratio of 1.33:1.
		 */
		virtual void setDefault();
		
		/** Validate camera settings.
		 *
		 * This method ensures that the camera settings are consistent and 
		 * usable to generate the view transformation. The following steps are
		 * taken in order:
		 * 
		 * 1) Validate angle and direction vector. If angle is defined, 
		 * direction is adjusted according to angle and right vector. If angle
		 * is not defined, angle is calculated according to right and 
		 * direction vectors.
		 * 2) Validate lookAt vector. If lookAt is not defined, it is set to 
		 * direction. If lookAt is defined, direction is calculated according 
		 * to lookAt vector.
		 * 3) Validate direction, right and up vectors. This step ensures that
		 * the direction, right and up vectors are orthogonal to each other.
		 * 4) Validate sky and direction vectors. If sky is not defined, sky 
		 * is set to up. Otherwise, if sky and direction are not orthogonal, 
		 * sky is orthogonalized to direction.
		 * 
		 * A new set of setup flags for the camera can be specified as an 
		 * optional parameter.
		 *
		 * \param newSetupFlags Setup flags.
		 * \param t Tolerance.
		 */
		virtual void validate(const Ionflux::GeoUtils::CameraSetupFlags* 
		newSetupFlags = 0, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Get rotation matrix.
		 *
		 * Calculate the rotation matrix for the camera.
		 *
		 * \param handedness Handedness of the coordinate system.
		 * \param upAxis Up axis.
		 * \param depthAxis Depth axis.
		 * \param horizonAxis Horizon axis.
		 *
		 * \return Rotation matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4 
		getRotationMatrix(Ionflux::GeoUtils::HandednessID handedness = 
		Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID upAxis = 
		Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID depthAxis = 
		Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID horizonAxis = 
		Ionflux::GeoUtils::AXIS_X);
		
		/** Get translation matrix.
		 *
		 * Calculate the camera translation matrix from the camera location. 
		 * If adjustLocation is set to \c true, the location of the camera 
		 * will be offset by the direction vector.
		 *
		 * \param adjustLocation Offset camera location by direction vector.
		 *
		 * \return Translation matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4 getTranslationMatrix(bool 
		adjustLocation = Ionflux::GeoUtils::Camera::DEFAULT_ADJUST_LOCATION);
		
		/** Get perspective matrix.
		 *
		 * Calculate the camera perspective matrix.
		 *
		 * \param depthAxis Depth axis.
		 *
		 * \return Perspective matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4 
		getPerspectiveMatrix(Ionflux::GeoUtils::AxisID depthAxis = 
		Ionflux::GeoUtils::AXIS_Y);
		
		/** Get view matrix.
		 *
		 * Get the view matrix which can be applied to object coordinates to
		 * create the camera view. mode can be either MODE_PERSPECTIVE (the 
		 * default) for perspective projection, or MODE_ORTHO for orthogonal 
		 * projection. If adjustLocation is set to True, the location of the 
		 * camera will be offset by the direction vector.
		 *
		 * \param mode Camera mode.
		 * \param adjustLocation Offset camera location by direction vector.
		 * \param handedness Handedness of the coordinate system.
		 * \param upAxis Up axis.
		 * \param depthAxis Depth axis.
		 * \param horizonAxis Horizon axis.
		 *
		 * \return View matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4 
		getViewMatrix(Ionflux::GeoUtils::CameraMode mode = 
		Ionflux::GeoUtils::Camera::MODE_PERSPECTIVE, bool adjustLocation = 
		Ionflux::GeoUtils::Camera::DEFAULT_ADJUST_LOCATION, 
		Ionflux::GeoUtils::HandednessID handedness = 
		Ionflux::GeoUtils::HANDEDNESS_RIGHT, Ionflux::GeoUtils::AxisID upAxis = 
		Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID depthAxis = 
		Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID horizonAxis = 
		Ionflux::GeoUtils::AXIS_X);
		
		/** Set up camera focused at the origin.
		 *
		 * Set up the camera to be pointed at the origin. The camera is 
		 * created at the specified distance in negative Y-direction and 
		 * rotated around the global coordinate axes as specified.
		 *
		 * \param distance Distance to origin.
		 * \param rotX Rotation around X axis (in degrees).
		 * \param rotY Rotation around Y axis (in degrees).
		 * \param rotZ Rotation around Z axis (in degrees).
		 */
		virtual void setOriginCam(double distance = 10., double rotX = -30., 
		double rotY = 0., double rotZ = 30.);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Camera& operator=(const 
		Ionflux::GeoUtils::Camera& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Camera* copy() const;
		
		/** Get location vector.
		 *
		 * \return Current value of location vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getLocation() const;
		
		/** Set location vector.
		 *
		 * Set new value of location vector.
		 *
		 * \param newLocation New value of location vector.
		 */
		virtual void setLocation(const Ionflux::GeoUtils::Vector3& newLocation);
		
		/** Get direction vector.
		 *
		 * \return Current value of direction vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getDirection() const;
		
		/** Set direction vector.
		 *
		 * Set new value of direction vector.
		 *
		 * \param newDirection New value of direction vector.
		 */
		virtual void setDirection(const Ionflux::GeoUtils::Vector3& 
		newDirection);
		
		/** Get look-at vector.
		 *
		 * \return Current value of look-at vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getLookAt() const;
		
		/** Set look-at vector.
		 *
		 * Set new value of look-at vector.
		 *
		 * \param newLookAt New value of look-at vector.
		 */
		virtual void setLookAt(const Ionflux::GeoUtils::Vector3& newLookAt);
		
		/** Get right vector.
		 *
		 * \return Current value of right vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getRight() const;
		
		/** Set right vector.
		 *
		 * Set new value of right vector.
		 *
		 * \param newRight New value of right vector.
		 */
		virtual void setRight(const Ionflux::GeoUtils::Vector3& newRight);
		
		/** Get up vector.
		 *
		 * \return Current value of up vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getUp() const;
		
		/** Set up vector.
		 *
		 * Set new value of up vector.
		 *
		 * \param newUp New value of up vector.
		 */
		virtual void setUp(const Ionflux::GeoUtils::Vector3& newUp);
		
		/** Get sky vector.
		 *
		 * \return Current value of sky vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getSky() const;
		
		/** Set sky vector.
		 *
		 * Set new value of sky vector.
		 *
		 * \param newSky New value of sky vector.
		 */
		virtual void setSky(const Ionflux::GeoUtils::Vector3& newSky);
		
		/** Get angle.
		 *
		 * \return Current value of angle.
		 */
		virtual double getAngle() const;
		
		/** Set angle.
		 *
		 * Set new value of angle.
		 *
		 * \param newAngle New value of angle.
		 */
		virtual void setAngle(double newAngle);
		
		/** Get lens.
		 *
		 * \return Current value of lens.
		 */
		virtual double getLens() const;
		
		/** Set lens.
		 *
		 * Set new value of lens.
		 *
		 * \param newLens New value of lens.
		 */
		virtual void setLens(double newLens);
		
		/** Get setup flags.
		 *
		 * \return Current value of setup flags.
		 */
		virtual Ionflux::GeoUtils::CameraSetupFlags getSetupFlags() const;
		
		/** Set setup flags.
		 *
		 * Set new value of setup flags.
		 *
		 * \param newSetupFlags New value of setup flags.
		 */
		virtual void setSetupFlags(const Ionflux::GeoUtils::CameraSetupFlags& 
		newSetupFlags);
};

}

}

/** \file Camera.hpp
 * \brief Camera (header).
 */
#endif
