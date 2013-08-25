%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module AltjiraNoise
%import "altjira.i"
%import "noise.i"
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
        $function
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


%{
#include "altjira/NoiseMap.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

namespace Noise
{

class NoiseMapClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NoiseMapClassInfo();
        virtual ~NoiseMapClassInfo();
};

class NoiseMap
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        NoiseMap();
		NoiseMap(const Ionflux::Altjira::Noise::NoiseMap& other);
        NoiseMap(noise::utils::NoiseMap* initNoiseMap);
        virtual ~NoiseMap();
        virtual Ionflux::Mapping::Range getRange();
        virtual void rescale(const Ionflux::Mapping::Range& range = 
        Ionflux::Mapping::DEFAULT_CLAMP_RANGE);
        virtual void transform(double offsetIn = 0., double scaleIn = 1., 
        double offsetOut = 0., double scaleOut = 1., 
        Ionflux::Mapping::Mapping* func = 0);
        virtual void render(Ionflux::Altjira::Image& image, 
        Ionflux::Altjira::ColorBand* colors = 0);
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Noise::NoiseMap* copy() const;
		static Ionflux::Altjira::Noise::NoiseMap* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::Noise::NoiseMap* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setNoiseMap(noise::utils::NoiseMap* newNoiseMap);
        virtual noise::utils::NoiseMap* getNoiseMap() const;
};

}

}

}


