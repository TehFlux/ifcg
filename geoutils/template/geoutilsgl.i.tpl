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

namespace Ionflux
{

namespace GeoUtils
{

// gltypes.hpp

typedef int VertexAttributeDataTypeID;
typedef int BufferUsageID;
typedef int PrimitiveID;
typedef int OpenGLProfileID;
class VertexAttribute;
typedef std::vector<Ionflux::GeoUtils::VertexAttribute*> 
    VertexAttributeVector;
typedef int ViewerEventTypeID;
class ViewerEvent;
typedef std::vector<Ionflux::GeoUtils::ViewerEvent*>
    ViewerEventVector;
typedef int VertexAttributeTypeID;

// glconstants.hpp

const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_ANY = 0;
const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_CORE = 1;
const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_COMPAT = 2;

const Ionflux::GeoUtils::DataTypeID DATA_TYPE_FLOAT = 0;
const Ionflux::GeoUtils::DataTypeID DATA_TYPE_UINT = 1;

const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_DRAW = 0;
const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_READ = 1;
const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_COPY = 2;
const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_DRAW = 3;
const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_READ = 4;
const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_COPY = 5;
const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_DRAW = 6;
const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_READ = 7;
const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_COPY = 8;

const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_POINT = 0;
const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_LINE = 1;
const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_TRIANGLE = 2;

// glutils.hpp

std::string getOpenGLProfileString(
    Ionflux::GeoUtils::OpenGLProfileID profile);
std::string getDataTypeString(
    Ionflux::GeoUtils::DataTypeID dataType);
unsigned int getNumElementsPerPrimitive(
    Ionflux::GeoUtils::PrimitiveID primitive);
void enableOpenGLBackFaceCulling(bool enable = true);

}

}

// Classes

$Program
$VertexAttribute
$VertexArrayObject
$ViewerEvent
$ViewerEventSet
$Viewer

// Templates

%template(VertexAttributeVector) std::vector<Ionflux::GeoUtils::VertexAttribute*>;
%template(ViewerEventVector) std::vector<Ionflux::GeoUtils::ViewerEvent*>;

