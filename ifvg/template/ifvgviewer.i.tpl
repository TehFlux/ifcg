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
        $$function
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

$Viewer

// Templates


