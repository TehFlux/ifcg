%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module GeoUtilsFBX
%import "ifobject/ifobject.i"
%import "ifmapping/ifmapping.i"
%import "geoutils/geoutils.i"
%{
#include "ifobject/ifobjectbase.hpp"
#include "ifmapping/ifmapping.hpp"
#include "geoutils/geoutils.hpp"
#include <assert.h>
using namespace std;
%}

%exception {
    try
    {
        $function
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


%{
#include "geoutils/FBXScene.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FBXSceneClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FBXSceneClassInfo();
        virtual ~FBXSceneClassInfo();
};

class FBXScene
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        FBXScene();
		FBXScene(const Ionflux::GeoUtils::FBXScene& other);
        virtual ~FBXScene();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::FBXScene* copy() const;
		static Ionflux::GeoUtils::FBXScene* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::FBXScene* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


