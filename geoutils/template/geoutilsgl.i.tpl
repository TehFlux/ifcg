%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module GeoUtilsGL
%import "ifobject/ifobject.i"
%import "ifmapping/ifmapping.i"
%import "geoutils/geoutils.i"
%{
#include "ifobject/ifobjectbase.hpp"
#include "ifmapping/ifmapping.hpp"
#include "geoutils/geoutils.hpp"
#include "geoutils/geoutilsgl.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $$function
    } catch(Ionflux::GeoUtils::GeoUtilsError& e)
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

// gltypes.hpp



// Classes

$Program

