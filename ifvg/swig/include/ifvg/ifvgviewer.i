%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module CIFVGViewer
%import "ifobject/ifobject.i"
%import "ifmapping/ifmapping.i"
%import "altjira/altjira.i"
%import "altjira/altjiradraw.i"
%import "geoutils/geoutils.i"
%import "geoutils/altjirageoutils.i"
%import "geoutils/geoutilsgl.i"
%import "ifvg.i"
%{
#include "ifobject/ifobjectbase.hpp"
#include "ifmapping/ifmapping.hpp"
#include "altjira/altjira.hpp"
#include "altjira/altjiradraw.hpp"
#include "geoutils/geoutils.hpp"
#include "geoutils/altjirageoutils.hpp"
#include "geoutils/geoutilsgl.hpp"
#include "ifvg/ifvg.hpp"
#include "ifvg/ifvgviewer.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $function
    } catch(Ionflux::VolGfx::IFVGError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::GeoUtils::GeoUtilsError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::Altjira::AltjiraError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::Mapping::MappingError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::ObjectBase::IFError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

namespace Ionflux
{

namespace VolGfx
{

// viewertypes.hpp

}

}

// Classes


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


// Templates


