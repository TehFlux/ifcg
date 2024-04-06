%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module AltjiraNoise
%import "altjira.i"
%import "noise/noise.i"
%{
#include "altjira/altjira.hpp"
#include "altjira/altjiranoise.hpp"
#include "altjira/AltjiraError.hpp"
#include "ifobject/ifobjectbase.hpp"
#include "ifmapping/ifmapping.hpp"
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

namespace Ionflux
{

namespace Altjira
{

namespace Noise
{

/** Initialize image from libnoise image.
 *
 * Initialize an Altjira image from a libnoise image.
 *
 * \param source Source image.
 * \param target Target image.
 */
void setImage(const noise::utils::Image& source, 
    Ionflux::Altjira::Image& target);

}

}

}

$NoiseMap

