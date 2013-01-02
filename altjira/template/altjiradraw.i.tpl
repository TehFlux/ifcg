%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module AltjiraDraw
%import "altjira.i"
%{
#include "ifmapping/ifmapping.hpp"
#include "altjira/altjira.hpp"
#include "altjira/altjiradraw.hpp"
#include "ifobject/ifobjectbase.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $$function
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

$Drawable
$Pattern
$ImagePattern
$Gradient
$RadialGradient
$LinearGradient
