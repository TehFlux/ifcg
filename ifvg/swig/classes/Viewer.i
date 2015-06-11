/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Viewer.i                        Viewer (interface).
 * ========================================================================== */
%{
#include "ifvg/Viewer.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class ViewerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ViewerClassInfo();
        virtual ~ViewerClassInfo();
};

class Viewer
: public Ionflux::GeoUtils::Viewer
{
    public:
        
        Viewer();
		Viewer(const Ionflux::VolGfx::Viewer& other);
        Viewer(int initWindowPosX, int initWindowPosY, int initWindowWidth,
        int initWindowHeight, const std::string& initWindowTitle = 
        Ionflux::GeoUtils::Viewer::DEFAULT_WINDOW_TITLE, const 
        Ionflux::Altjira::Color& initClearColor = 
        Ionflux::GeoUtils::Viewer::DEFAULT_CLEAR_COLOR, int 
        initOpenGLVersionMajor = 
        Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_VERSION_MAJOR, int 
        initOpenGLVersionMinor = 
        Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_VERSION_MINOR, 
        Ionflux::GeoUtils::OpenGLProfileID initOpenGLProfile = 
        Ionflux::GeoUtils::Viewer::DEFAULT_OPENGL_PROFILE);
        virtual ~Viewer();
		virtual Ionflux::VolGfx::Viewer* copy() const;
		static Ionflux::VolGfx::Viewer* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::Viewer* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
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
};

}

}
