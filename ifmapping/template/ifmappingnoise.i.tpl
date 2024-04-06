%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module IFMappingNoise
%import "ifmapping.i"
%import "noise/noise.i"
%{
#include "ifmapping/ifmapping.hpp"
#include "ifmapping/xml_factories.hpp"
#include "ifmapping/ifmappingnoise.hpp"
#include "ifmapping/MappingError.hpp"
#include "noise/noise.h"
#include "ifobject/ifobjectbase.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $$function
    } catch(Ionflux::Mapping::MappingError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::ObjectBase::IFError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}

$NoiseMapping
$NoiseMapTransform
