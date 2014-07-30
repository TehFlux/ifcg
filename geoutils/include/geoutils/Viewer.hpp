#ifndef IONFLUX_GEOUTILS_VIEWER
#define IONFLUX_GEOUTILS_VIEWER
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Viewer.hpp                      Viewer (header).
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
#include "geoutils/gltypes.hpp"
#include "geoutils/glconstants.hpp"
#include "altjira/Color.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class ViewerEventSet;

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
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Global viewer instance.
		static Ionflux::GeoUtils::Viewer* instance;
		/// Window implementation (GLFW).
		GLFWwindow* windowImpl;
		/// Window position (X).
		int windowPosX;
		/// Window position (Y).
		int windowPosY;
		/// Window width.
		int windowWidth;
		/// Window height.
		int windowHeight;
		/// Window title.
		std::string windowTitle;
		/// Clear color.
		Ionflux::Altjira::Color clearColor;
		/// OpenGL version (major).
		int openGLVersionMajor;
		/// OpenGL version (minor).
		int openGLVersionMinor;
		/// OpenGL profile.
		Ionflux::GeoUtils::OpenGLProfileID openGLProfile;
		/// Shutdown flag.
		bool shutdownFlag;
		/// Events.
		Ionflux::GeoUtils::ViewerEventSet* events;
		
	public:
		/// Default window position (X).
		static const int DEFAULT_WINDOW_POS_X;
		/// Default window position (Y).
		static const int DEFAULT_WINDOW_POS_Y;
		/// Default window width.
		static const int DEFAULT_WINDOW_WIDTH;
		/// Default window height.
		static const int DEFAULT_WINDOW_HEIGHT;
		/// Default window title.
		static const std::string DEFAULT_WINDOW_TITLE;
		/// Default OpenGL version (major).
		static const int DEFAULT_OPENGL_VERSION_MAJOR;
		/// Default OpenGL version (minor).
		static const int DEFAULT_OPENGL_VERSION_MINOR;
		/// Default OpenGL profile.
		static const Ionflux::GeoUtils::OpenGLProfileID DEFAULT_OPENGL_PROFILE;
		/// Default clear color.
		static const Ionflux::Altjira::Color DEFAULT_CLEAR_COLOR;
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
		Viewer(const Ionflux::GeoUtils::Viewer& other);
		
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
		DEFAULT_WINDOW_TITLE, const Ionflux::Altjira::Color& initClearColor = 
		DEFAULT_CLEAR_COLOR, int initOpenGLVersionMajor = 
		DEFAULT_OPENGL_VERSION_MAJOR, int initOpenGLVersionMinor = 
		DEFAULT_OPENGL_VERSION_MINOR, Ionflux::GeoUtils::OpenGLProfileID 
		initOpenGLProfile = DEFAULT_OPENGL_PROFILE);
		
		/** Destructor.
		 *
		 * Destruct Viewer object.
		 */
		virtual ~Viewer();
		
		/** Initialize.
		 *
		 * Initialize the viewer.
		 */
		virtual void init();
		
		/** Clean up.
		 *
		 * Clean up state maintained by the viewer.
		 */
		virtual void cleanup();
		
		/** Shutdown.
		 *
		 * Perform a clean shutdown of the viewer. The exact behavior of this 
		 * function depends on the value of the \c shutdownFlag property and 
		 * the \c shutdownNow parameter. If \c shutdownNow is \c false and \c 
		 * shutdownFlag is \c true, the viewer will be shut down immediately. 
		 * Otherwise, \c shutdownFlag is set to \c true. If \c shutdownNow is 
		 * \c true, the viewer will be shut down immediately, regardless of 
		 * the current value of \c shutdownFlag.
		 *
		 * \param shutdownNow Shutdown now flag.
		 */
		virtual void shutdown(bool shutdownNow = true);
		
		/** Clear framebuffer.
		 *
		 * Clear the framebuffer.
		 */
		virtual void clear();
		
		/** Close viewer window.
		 *
		 * Request closing the viewer window. If \c closeFlag is set to \c 
		 * false and closing the window was requested, the closing of the 
		 * window will be cancelled.
		 *
		 * \param closeFlag close flag.
		 */
		virtual void closeWindow(bool closeFlag = true);
		
		/** Initialize viewport.
		 *
		 * Set the OpenGL viewport so it reflects the size of the window 
		 * framebuffer.
		 */
		virtual void initViewport();
		
		/** Swap buffers.
		 *
		 * Swap buffers.
		 */
		virtual void swapBuffers();
		
		/** Poll events.
		 *
		 * Poll events. Any events that have occured are added to the event 
		 * set of the viewer. Any previous events still in the event set when 
		 * pollEvents() is called are cleared.
		 */
		virtual void pollEvents();
		
		/** Key handler.
		 *
		 * Handler for key events.
		 *
		 * \param key Key code.
		 * \param scancode Scancode.
		 * \param action Action.
		 * \param mods Modifier keys.
		 */
		virtual void onKey(int key, int scancode, int action, int mods);
		
		/** Window size handler.
		 *
		 * Handler for window size events.
		 *
		 * \param width Width.
		 * \param height Height.
		 */
		virtual void onWindowSize(int width, int height);
		
		/** Window position handler.
		 *
		 * Handler for window position events.
		 *
		 * \param posX position (X).
		 * \param posY position (Y).
		 */
		virtual void onWindowPos(int posX, int posY);
		
		/** Window close handler.
		 *
		 * Handler for window close events.
		 */
		virtual void onWindowClose();
		
		/** Cursor position handler.
		 *
		 * Handler for cursor position events.
		 *
		 * \param posX position (X).
		 * \param posY position (Y).
		 */
		virtual void onCursorPos(double posX, double posY);
		
		/** Mouse button handler.
		 *
		 * Handler for mouse button events.
		 *
		 * \param mouseButton mouse button.
		 * \param action Action.
		 * \param mods Modifier keys.
		 */
		virtual void onMouseButton(int mouseButton, int action, int mods);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get global instance.
		 *
		 * Get the current global viewer instance. If no global viewer 
		 * instance exists, a new one will be created.
		 * 
		 * \sa cleanupInstance()
		 *
		 * \return Global viewer instance.
		 */
		static Ionflux::GeoUtils::Viewer* getInstance();
		
		/** Set global instance.
		 *
		 * Set the current global viewer instance.
		 *
		 * \param viewer Viewer.
		 */
		static void setInstance(Ionflux::GeoUtils::Viewer* viewer);
		
		/** Cleanup global instance.
		 *
		 * Clean up the global viewer instance. This should be called to clean
		 * up the global viewer instance that can be obtained by getInstance()
		 * before exiting the application.
		 * 
		 * \sa getInstance()
		 */
		static void cleanupInstance();
		
		/** Error handler (GLFW).
		 *
		 * Callback for GLFW errors.
		 *
		 * \param errorCode Error code.
		 * \param description error description.
		 */
		static void errorHandlerGLFW(int errorCode, const char* description);
		
		/** Key handler (GLFW).
		 *
		 * Callback for GLFW key events.
		 *
		 * \param window Window.
		 * \param key Key code.
		 * \param scancode Scancode.
		 * \param action Action.
		 * \param mods Modifier keys.
		 */
		static void keyHandlerGLFW(GLFWwindow* window, int key, int scancode, int
		action, int mods);
		
		/** Window size handler (GLFW).
		 *
		 * Callback for GLFW window size events.
		 *
		 * \param window Window.
		 * \param width Width.
		 * \param height Height.
		 */
		static void windowSizeHandlerGLFW(GLFWwindow* window, int width, int 
		height);
		
		/** Window position handler (GLFW).
		 *
		 * Callback for GLFW window position events.
		 *
		 * \param window Window.
		 * \param posX position (X).
		 * \param posY position (Y).
		 */
		static void windowPosHandlerGLFW(GLFWwindow* window, int posX, int posY);
		
		/** Window close handler (GLFW).
		 *
		 * Callback for GLFW window close events.
		 *
		 * \param window Window.
		 */
		static void windowCloseHandlerGLFW(GLFWwindow* window);
		
		/** Cursor position handler (GLFW).
		 *
		 * Callback for GLFW cursor position events.
		 *
		 * \param window Window.
		 * \param posX position (X).
		 * \param posY position (Y).
		 */
		static void cursorPosHandlerGLFW(GLFWwindow* window, double posX, double 
		posY);
		
		/** Mouse button handler (GLFW).
		 *
		 * Callback for GLFW mouse button events.
		 *
		 * \param window Window.
		 * \param mouseButton mouse button.
		 * \param action Action.
		 * \param mods Modifier keys.
		 */
		static void mouseButtonHandlerGLFW(GLFWwindow* window, int mouseButton, 
		int action, int mods);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Viewer& operator=(const 
		Ionflux::GeoUtils::Viewer& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Viewer* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Viewer* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Viewer* create(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Viewer* create(int initWindowPosX, int 
		initWindowPosY, int initWindowWidth, int initWindowHeight, const 
		std::string& initWindowTitle = DEFAULT_WINDOW_TITLE, const 
		Ionflux::Altjira::Color& initClearColor = DEFAULT_CLEAR_COLOR, int 
		initOpenGLVersionMajor = DEFAULT_OPENGL_VERSION_MAJOR, int 
		initOpenGLVersionMinor = DEFAULT_OPENGL_VERSION_MINOR, 
		Ionflux::GeoUtils::OpenGLProfileID initOpenGLProfile = 
		DEFAULT_OPENGL_PROFILE, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get window implementation (GLFW).
		 *
		 * \return Current value of window implementation (GLFW).
		 */
		virtual GLFWwindow* getWindowImpl() const;
		
		/** Set window implementation (GLFW).
		 *
		 * Set new value of window implementation (GLFW).
		 *
		 * \param newWindowImpl New value of window implementation (GLFW).
		 */
		virtual void setWindowImpl(GLFWwindow* newWindowImpl);
		
		/** Get window position (X).
		 *
		 * \return Current value of window position (X).
		 */
		virtual int getWindowPosX() const;
		
		/** Set window position (X).
		 *
		 * Set new value of window position (X).
		 *
		 * \param newWindowPosX New value of window position (X).
		 */
		virtual void setWindowPosX(int newWindowPosX);
		
		/** Get window position (Y).
		 *
		 * \return Current value of window position (Y).
		 */
		virtual int getWindowPosY() const;
		
		/** Set window position (Y).
		 *
		 * Set new value of window position (Y).
		 *
		 * \param newWindowPosY New value of window position (Y).
		 */
		virtual void setWindowPosY(int newWindowPosY);
		
		/** Get window width.
		 *
		 * \return Current value of window width.
		 */
		virtual int getWindowWidth() const;
		
		/** Set window width.
		 *
		 * Set new value of window width.
		 *
		 * \param newWindowWidth New value of window width.
		 */
		virtual void setWindowWidth(int newWindowWidth);
		
		/** Get window height.
		 *
		 * \return Current value of window height.
		 */
		virtual int getWindowHeight() const;
		
		/** Set window height.
		 *
		 * Set new value of window height.
		 *
		 * \param newWindowHeight New value of window height.
		 */
		virtual void setWindowHeight(int newWindowHeight);
		
		/** Get window title.
		 *
		 * \return Current value of window title.
		 */
		virtual std::string getWindowTitle() const;
		
		/** Set window title.
		 *
		 * Set new value of window title.
		 *
		 * \param newWindowTitle New value of window title.
		 */
		virtual void setWindowTitle(const std::string& newWindowTitle);
		
		/** Get clear color.
		 *
		 * \return Current value of clear color.
		 */
		virtual Ionflux::Altjira::Color getClearColor() const;
		
		/** Set clear color.
		 *
		 * Set new value of clear color.
		 *
		 * \param newClearColor New value of clear color.
		 */
		virtual void setClearColor(const Ionflux::Altjira::Color& newClearColor);
		
		/** Get openGL version (major).
		 *
		 * \return Current value of openGL version (major).
		 */
		virtual int getOpenGLVersionMajor() const;
		
		/** Set openGL version (major).
		 *
		 * Set new value of openGL version (major).
		 *
		 * \param newOpenGLVersionMajor New value of openGL version (major).
		 */
		virtual void setOpenGLVersionMajor(int newOpenGLVersionMajor);
		
		/** Get openGL version (minor).
		 *
		 * \return Current value of openGL version (minor).
		 */
		virtual int getOpenGLVersionMinor() const;
		
		/** Set openGL version (minor).
		 *
		 * Set new value of openGL version (minor).
		 *
		 * \param newOpenGLVersionMinor New value of openGL version (minor).
		 */
		virtual void setOpenGLVersionMinor(int newOpenGLVersionMinor);
		
		/** Get openGL profile.
		 *
		 * \return Current value of openGL profile.
		 */
		virtual Ionflux::GeoUtils::OpenGLProfileID getOpenGLProfile() const;
		
		/** Set openGL profile.
		 *
		 * Set new value of openGL profile.
		 *
		 * \param newOpenGLProfile New value of openGL profile.
		 */
		virtual void setOpenGLProfile(Ionflux::GeoUtils::OpenGLProfileID 
		newOpenGLProfile);
		
		/** Get shutdown flag.
		 *
		 * \return Current value of shutdown flag.
		 */
		virtual bool getShutdownFlag() const;
		
		/** Set shutdown flag.
		 *
		 * Set new value of shutdown flag.
		 *
		 * \param newShutdownFlag New value of shutdown flag.
		 */
		virtual void setShutdownFlag(bool newShutdownFlag);
		
		/** Get events.
		 *
		 * \return Current value of events.
		 */
		virtual Ionflux::GeoUtils::ViewerEventSet* getEvents() const;
		
		/** Set events.
		 *
		 * Set new value of events.
		 *
		 * \param newEvents New value of events.
		 */
		virtual void setEvents(Ionflux::GeoUtils::ViewerEventSet* newEvents);
};

}

}

/** \file Viewer.hpp
 * \brief Viewer (header).
 */
#endif
