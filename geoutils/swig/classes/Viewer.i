/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Viewer.i                        Viewer (interface).
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
%{
#include "geoutils/Viewer.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ViewerEventSet;

class ViewerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ViewerClassInfo();
        virtual ~ViewerClassInfo();
};

class Viewer
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const int DEFAULT_WINDOW_POS_X;
		static const int DEFAULT_WINDOW_POS_Y;
		static const int DEFAULT_WINDOW_WIDTH;
		static const int DEFAULT_WINDOW_HEIGHT;
		static const std::string DEFAULT_WINDOW_TITLE;
		static const int DEFAULT_OPENGL_VERSION_MAJOR;
		static const int DEFAULT_OPENGL_VERSION_MINOR;
		static const Ionflux::GeoUtils::OpenGLProfileID DEFAULT_OPENGL_PROFILE;
		static const Ionflux::Altjira::Color DEFAULT_CLEAR_COLOR;
        
        Viewer();
		Viewer(const Ionflux::GeoUtils::Viewer& other);
        Viewer(int initWindowPosX, int initWindowPosY, int initWindowWidth,
        int initWindowHeight, const std::string& initWindowTitle = 
        DEFAULT_WINDOW_TITLE, const Ionflux::Altjira::Color& initClearColor
        = DEFAULT_CLEAR_COLOR, int initOpenGLVersionMajor = 
        DEFAULT_OPENGL_VERSION_MAJOR, int initOpenGLVersionMinor = 
        DEFAULT_OPENGL_VERSION_MINOR, Ionflux::GeoUtils::OpenGLProfileID 
        initOpenGLProfile = DEFAULT_OPENGL_PROFILE);
        virtual ~Viewer();
        virtual void init();
        virtual void cleanup();
        virtual void shutdown(bool shutdownNow = true);
        virtual void clear();
        virtual void closeWindow(bool closeFlag = true);
        virtual void initViewport();
        virtual void swapBuffers();
        virtual void pollEvents();
        virtual void onKey(int key, int scancode, int action, int mods);
        virtual void onWindowSize(int width, int height);
        virtual void onWindowPos(int posX, int posY);
        virtual void onWindowClose();
        virtual void onCursorPos(double posX, double posY);
        virtual void onMouseButton(int mouseButton, int action, int mods);
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Viewer* getInstance();
        static void setInstance(Ionflux::GeoUtils::Viewer* viewer);
        static void cleanupInstance();
		virtual Ionflux::GeoUtils::Viewer* copy() const;
		static Ionflux::GeoUtils::Viewer* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Viewer* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Viewer* create(int initWindowPosX, int 
		initWindowPosY, int initWindowWidth, int initWindowHeight, const 
		std::string& initWindowTitle = DEFAULT_WINDOW_TITLE, const 
		Ionflux::Altjira::Color& initClearColor = DEFAULT_CLEAR_COLOR, int 
		initOpenGLVersionMajor = DEFAULT_OPENGL_VERSION_MAJOR, int 
		initOpenGLVersionMinor = DEFAULT_OPENGL_VERSION_MINOR, 
		Ionflux::GeoUtils::OpenGLProfileID initOpenGLProfile = 
		DEFAULT_OPENGL_PROFILE, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setWindowPosX(int newWindowPosX);
        virtual int getWindowPosX() const;
        virtual void setWindowPosY(int newWindowPosY);
        virtual int getWindowPosY() const;
        virtual void setWindowWidth(int newWindowWidth);
        virtual int getWindowWidth() const;
        virtual void setWindowHeight(int newWindowHeight);
        virtual int getWindowHeight() const;
        virtual void setWindowTitle(const std::string& newWindowTitle);
        virtual std::string getWindowTitle() const;
        virtual void setClearColor(const Ionflux::Altjira::Color& 
        newClearColor);
        virtual Ionflux::Altjira::Color getClearColor() const;
        virtual void setOpenGLVersionMajor(int newOpenGLVersionMajor);
        virtual int getOpenGLVersionMajor() const;
        virtual void setOpenGLVersionMinor(int newOpenGLVersionMinor);
        virtual int getOpenGLVersionMinor() const;
        virtual void setOpenGLProfile(Ionflux::GeoUtils::OpenGLProfileID 
        newOpenGLProfile);
        virtual Ionflux::GeoUtils::OpenGLProfileID getOpenGLProfile() 
        const;
        virtual void setShutdownFlag(bool newShutdownFlag);
        virtual bool getShutdownFlag() const;
        virtual void setEvents(Ionflux::GeoUtils::ViewerEventSet* 
        newEvents);
        virtual Ionflux::GeoUtils::ViewerEventSet* getEvents() const;
};

}

}
