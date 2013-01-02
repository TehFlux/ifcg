%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module IFMappingNoise
%import "ifmapping.i"
%import "noise.i"
%{
#include "ifmapping/ifmapping.hpp"
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
        $function
    } catch(Ionflux::Mapping::MappingError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    } catch(Ionflux::ObjectBase::IFError& e)
    {
        SWIG_exception(SWIG_RuntimeError, e.what());
    }
}


%{
#include "ifmapping/NoiseMapping.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

namespace Noise
{

class NoiseMappingClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NoiseMappingClassInfo();
        virtual ~NoiseMappingClassInfo();
};

class NoiseMapping
: public Ionflux::ObjectBase::IFObject, public noise::module::Module
{
    public:
        
        NoiseMapping();
        NoiseMapping(Ionflux::Mapping::Mapping* initFunc, 
        Ionflux::Mapping::MappingValue initScale = 0.5, 
        Ionflux::Mapping::MappingValue initOffset = 0.5, 
        Ionflux::Mapping::MappingValue initResultScale = 2., 
        Ionflux::Mapping::MappingValue initResultOffset = -1.);
        virtual ~NoiseMapping();
        virtual int GetSourceModuleCount() const;
        virtual double GetValue(double x, double y, double z) const;
        virtual void SetSourceModule(const noise::module::Module& 
        sourceModule);
        virtual std::string getString() const;
		static Ionflux::Mapping::Noise::NoiseMapping* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::Noise::NoiseMapping* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
        virtual void setScale(Ionflux::Mapping::MappingValue newScale);
        virtual Ionflux::Mapping::MappingValue getScale() const;
        virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
        virtual Ionflux::Mapping::MappingValue getOffset() const;
        virtual void setResultScale(Ionflux::Mapping::MappingValue 
        newResultScale);
        virtual Ionflux::Mapping::MappingValue getResultScale() const;
        virtual void setResultOffset(Ionflux::Mapping::MappingValue 
        newResultOffset);
        virtual Ionflux::Mapping::MappingValue getResultOffset() const;
};

}

}

}


%{
#include "ifmapping/NoiseMapTransform.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

namespace Noise
{

class NoiseMapTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NoiseMapTransformClassInfo();
        virtual ~NoiseMapTransformClassInfo();
};

class NoiseMapTransform
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        NoiseMapTransform();
        NoiseMapTransform(Ionflux::Mapping::Mapping* initFunc, 
        Ionflux::Mapping::MappingValue initScale = 0.5, 
        Ionflux::Mapping::MappingValue initOffset = 0.5, 
        Ionflux::Mapping::MappingValue initResultScale = 2., 
        Ionflux::Mapping::MappingValue initResultOffset = -1.);
        virtual ~NoiseMapTransform();
        virtual void transform(noise::utils::NoiseMap& map);
        virtual std::string getString() const;
		static Ionflux::Mapping::Noise::NoiseMapTransform* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Mapping::Noise::NoiseMapTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFunc(Ionflux::Mapping::Mapping* newFunc);
        virtual Ionflux::Mapping::Mapping* getFunc() const;
        virtual void setScale(Ionflux::Mapping::MappingValue newScale);
        virtual Ionflux::Mapping::MappingValue getScale() const;
        virtual void setOffset(Ionflux::Mapping::MappingValue newOffset);
        virtual Ionflux::Mapping::MappingValue getOffset() const;
        virtual void setResultScale(Ionflux::Mapping::MappingValue 
        newResultScale);
        virtual Ionflux::Mapping::MappingValue getResultScale() const;
        virtual void setResultOffset(Ionflux::Mapping::MappingValue 
        newResultOffset);
        virtual Ionflux::Mapping::MappingValue getResultOffset() const;
};

}

}

}

