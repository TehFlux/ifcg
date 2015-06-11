#ifndef IONFLUX_VOLGFX_VIEWER
#define IONFLUX_VOLGFX_VIEWER
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Viewer.hpp                      Viewer (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifvg/viewertypes.hpp"
#include "geoutils/Viewer.hpp"

namespace Ionflux
{

namespace VolGfx
{

/// Class information for class Viewer.
class ViewerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ViewerClassInfo();
		/// Destructor.
		virtual ~ViewerClassInfo();
};

/** Viewer.
 * \ingroup ifvg
 *
 * A viewer, used to visualize graphics in a window.
 */
class Viewer
: public Ionflux::GeoUtils::Viewer
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const ViewerClassInfo viewerClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Viewer object.
		 */
		Viewer();
		
		/** Constructor.
		 *
		 * Construct new Viewer object.
		 *
		 * \param other Other object.
		 */
		Viewer(const Ionflux::VolGfx::Viewer& other);
		
		/** Constructor.
		 *
		 * Construct new Viewer object.
		 *
		 * \param initWindowPosX Window position (X).
		 * \param initWindowPosY Window position (Y).
		 * \param initWindowWidth Window width.
		 * \param initWindowHeight Window height.
		 * \param initWindowTitle Window title.
		 * \param initClearColor Clear color.
		 * \param initOpenGLVersionMajor OpenGL version (major).
		 * \param initOpenGLVersionMinor OpenGL version (minor).
		 * \param initOpenGLProfile OpenGL profile.
		 */
		Viewer(int initWindowPosX, int initWindowPosY, int initWindowWidth, int 
		initWindowHeight, const std::string& initWindowTitle = 
		Ionflux::GeoUtils::Viewer::DEFAULT_WINDOW_TITLE, const 
		Ionflux::Altjira::Color& initClearColor = 
		Ionflux::GeoUtils::Viewer::DEFAULT_CLEAR_COLOR, int 
		initOpenGLVersionMajor = 
		Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_VERSION_MAJOR, int 
		initOpenGLVersionMinor = 
		Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_VERSION_MINOR, 
		Ionflux::GeoUtils::OpenGLProfileID initOpenGLProfile = 
		Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_PROFILE);
		
		/** Destructor.
		 *
		 * Destruct Viewer object.
		 */
		virtual ~Viewer();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::VolGfx::Viewer& operator=(const Ionflux::VolGfx::Viewer&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::Viewer* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::Viewer* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::VolGfx::Viewer* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Viewer object.
		 *
		 * \param initWindowPosX Window position (X).
		 * \param initWindowPosY Window position (Y).
		 * \param initWindowWidth Window width.
		 * \param initWindowHeight Window height.
		 * \param initWindowTitle Window title.
		 * \param initClearColor Clear color.
		 * \param initOpenGLVersionMajor OpenGL version (major).
		 * \param initOpenGLVersionMinor OpenGL version (minor).
		 * \param initOpenGLProfile OpenGL profile.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::Viewer* create(int initWindowPosX, int 
		initWindowPosY, int initWindowWidth, int initWindowHeight, const 
		std::string& initWindowTitle = 
		Ionflux::GeoUtils::Viewer::DEFAULT_WINDOW_TITLE, const 
		Ionflux::Altjira::Color& initClearColor = 
		Ionflux::GeoUtils::Viewer::DEFAULT_CLEAR_COLOR, int 
		initOpenGLVersionMajor = 
		Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_VERSION_MAJOR, int 
		initOpenGLVersionMinor = 
		Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_VERSION_MINOR, 
		Ionflux::GeoUtils::OpenGLProfileID initOpenGLProfile = 
		Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_PROFILE, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
};

}

}

/** \file Viewer.hpp
 * \brief Viewer (header).
 */
#endif
