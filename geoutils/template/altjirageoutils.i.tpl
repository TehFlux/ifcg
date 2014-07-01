%include <std_string.i>
%include <std_vector.i>
%include <std_set.i>
%include <exception.i>
%module AltjiraGeoUtils
%import "geoutils/geoutils.i"
%import "altjira/altjira.i"
%import "altjira/altjiradraw.i"
%{
#include "ifmapping/xml_factories.hpp"
#include "geoutils/geoutils.hpp"
#include "geoutils/xml_factories.hpp"
#include "altjira/altjira.hpp"
#include "altjira/altjiradraw.hpp"
#include "ifmapping/ifmapping.hpp"
#include "geoutils/altjirageoutils.hpp"
#include "ifobject/ifobjectbase.hpp"
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

namespace GeoUtils
{

// imageutils.hpp

void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::FloatColor& c);
void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::ByteColor& c);
void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::Color& c);
double sample(Ionflux::Altjira::Matrix& m, Ionflux::GeoUtils::Vertex3& v);
double sampleMulti(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, 
    Ionflux::GeoUtils::Matrix3* t = 0, 
    Ionflux::GeoUtils::MatrixSamplingMethod method = SAMPLE_AVERAGE);
Ionflux::GeoUtils::Vector2 sampleMultiRot(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, 
    const Ionflux::GeoUtils::Vector3& offset, double phi0, double phi1, 
    double dPhi, 
    Ionflux::GeoUtils::MatrixSamplingMethod method = SAMPLE_AVERAGE);
void sampleMultiRotMatrix(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, Ionflux::Altjira::Matrix& r0, 
    Ionflux::Altjira::Matrix& r1, const Ionflux::GeoUtils::Vector3& offset, 
    double phi0, double phi1, double dPhi, 
    Ionflux::GeoUtils::MatrixSamplingMethod method = SAMPLE_AVERAGE);

}

}

$SVG
$Image
$LoadSVG
$WritePNG
$Render
$ImageItem
$ImageSource
$ImageLoader

