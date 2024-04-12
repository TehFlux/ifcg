%include <std_string.i>
%include <std_map.i>
%include <std_set.i>
%include <std_pair.i>
%include <std_vector.i>
%module Altjira
%import "ifobject/ifobject.i"
%import "ifmapping/ifmapping.i"
%{
#include "altjira/altjira.hpp"
#include "ifmapping/ifmapping.hpp"
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

namespace Ionflux
{

namespace Altjira
{

// types.hpp

typedef unsigned int ImageType;
typedef unsigned int ColorSpace;
typedef guchar* PixelData;
typedef double FloatColorValue;
typedef unsigned char ByteColorValue;
typedef unsigned int DesaturationMethod;
typedef unsigned int ChannelID;
typedef int FillRule;

struct ByteColor
{
    ByteColorValue c0;
    ByteColorValue c1;
    ByteColorValue c2;
    ByteColorValue alpha;
    ColorSpace space;
};

struct FloatColor
{
    FloatColorValue c0;
    FloatColorValue c1;
    FloatColorValue c2;
    FloatColorValue alpha;
    ColorSpace space;
};

template<class T>
struct Rectangle
{
	T x;
	T y;
    T width;
    T height;
};

typedef Rectangle<unsigned int> ImageRect;

class Image;

typedef std::vector<Ionflux::Altjira::Image*> ImageVector;

struct GIHRankSpec
{
    std::string selection;
    unsigned int size;
};

typedef std::vector<Ionflux::Altjira::GIHRankSpec> GIHRankSpecVector;

class Color;

typedef std::vector<Ionflux::Altjira::Color*> ColorVector;

// constants.hpp

const Ionflux::Mapping::Range DEFAULT_CLAMP_RANGE = { 0., 1. };

const std::string DEFAULT_BRUSH_NAME = "brush";
const unsigned int DEFAULT_BRUSH_SPACING = 20;

const Ionflux::Altjira::DesaturationMethod DESATURATION_BY_VALUE = 0;
const Ionflux::Altjira::DesaturationMethod DESATURATION_BY_LUMINANCE = 1;
const Ionflux::Altjira::DesaturationMethod DEFAULT_DESATURATION_METHOD = 
    DESATURATION_BY_VALUE;

const Ionflux::Altjira::GIHRankSpec GIH_DEFAULT_RANK_SPEC = { "random", 0 };

const Ionflux::Altjira::ChannelID CH_RED = 0;
const Ionflux::Altjira::ChannelID CH_GREEN = 1;
const Ionflux::Altjira::ChannelID CH_BLUE = 2;
const Ionflux::Altjira::ChannelID CH_HUE = 3;
const Ionflux::Altjira::ChannelID CH_SATURATION = 4;
const Ionflux::Altjira::ChannelID CH_VALUE = 5;
const Ionflux::Altjira::ChannelID CH_LUMINANCE = 6;
const Ionflux::Altjira::ChannelID CH_ALPHA = 7;

const Ionflux::Altjira::FillRule FILL_RULE_WINDING = 0;
const Ionflux::Altjira::FillRule FILL_RULE_EVEN_ODD = 1;

const std::string DEFAULT_FONT_DESCRIPTION = "Bitstream Vera Sans";
const double DEFAULT_FONT_SIZE = 20.;

const unsigned int EXTENT_INFINITE = std::numeric_limits<unsigned int>::max();

// utils.hpp

unsigned char floatToByte(double v);
double byteToFloat(unsigned char v);
unsigned char lutAdd(unsigned char x, unsigned char y);
unsigned char lutMult(unsigned char x, unsigned char y);
unsigned char lutSub(unsigned char x, unsigned char y);
unsigned char lutDiv(unsigned char x, unsigned char y);
Ionflux::Altjira::GIHRankSpec createGIHRankSpec(std::string selection, 
    unsigned int size);
void initRectangle(Ionflux::Altjira::ImageRect& r, double x, double y, 
    double width, double height);
Ionflux::Altjira::ImageRect intersect(const Ionflux::Altjira::ImageRect& r0, 
    const Ionflux::Altjira::ImageRect& r1);

}

}

// Color (required by some types).

$Color

namespace Ionflux
{

namespace Altjira
{

// imageutils.hpp

struct ColorPair
{
    Color first;
    Color second;
};

void init();
Ionflux::Altjira::FloatColor createFloatColor(
    Ionflux::Altjira::FloatColorValue c0 = 0., 
    Ionflux::Altjira::FloatColorValue c1 = 0., 
    Ionflux::Altjira::FloatColorValue c2 = 0., 
    Ionflux::Altjira::FloatColorValue alpha = 1., 
    Ionflux::Altjira::ColorSpace space = Ionflux::Altjira::Color::SPACE_HSV);
Ionflux::Altjira::ByteColor createByteColor(
    Ionflux::Altjira::ByteColorValue c0 = 0., 
    Ionflux::Altjira::ByteColorValue c1 = 0., 
    Ionflux::Altjira::ByteColorValue c2 = 0., 
    Ionflux::Altjira::ByteColorValue alpha = 1., 
    Ionflux::Altjira::ColorSpace space = Ionflux::Altjira::Color::SPACE_HSV);
void floatToByte(const Ionflux::Altjira::FloatColor& c0, 
    Ionflux::Altjira::ByteColor& c1);
void byteToFloat(const Ionflux::Altjira::ByteColor& c0, 
    Ionflux::Altjira::FloatColor& c1);
void clamp(Ionflux::Altjira::FloatColor& c, 
    const Ionflux::Mapping::Range& r = DEFAULT_CLAMP_RANGE);
void wrap(Ionflux::Altjira::FloatColor& c, 
    const Ionflux::Mapping::Range& r = DEFAULT_CLAMP_RANGE);
void toHSV(Ionflux::Altjira::FloatColor& c);
void toRGB(Ionflux::Altjira::FloatColor& c);
void toHSL(Ionflux::Altjira::FloatColor& c);
void toColorSpace(Ionflux::Altjira::FloatColor& c, 
    Ionflux::Altjira::ColorSpace space);
void toHSV(Ionflux::Altjira::ByteColor& c);
void toRGB(Ionflux::Altjira::ByteColor& c);
void toHSL(Ionflux::Altjira::ByteColor& c);
void toColorSpace(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ColorSpace space);
void copy(const Ionflux::Altjira::FloatColor& s, 
    Ionflux::Altjira::FloatColor& t);
void multiply(Ionflux::Altjira::FloatColor& c, double value);
void preMultiply(Ionflux::Altjira::FloatColor& c);
void divideAlpha(Ionflux::Altjira::FloatColor& c);
Ionflux::Altjira::FloatColorValue getComponent(
    Ionflux::Altjira::FloatColor& c, Ionflux::Altjira::ChannelID channel);
void setComponent(Ionflux::Altjira::FloatColor& c, 
    Ionflux::Altjira::ChannelID channel, 
    Ionflux::Altjira::FloatColorValue value);
void copy(const Ionflux::Altjira::ByteColor& s, 
    Ionflux::Altjira::ByteColor& t);
void multiply(Ionflux::Altjira::ByteColor& c, double value);
void multiply(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ByteColorValue value);
void preMultiply(Ionflux::Altjira::ByteColor& c);
void divideAlpha(Ionflux::Altjira::ByteColor& c);
Ionflux::Altjira::ByteColorValue getComponent(
    Ionflux::Altjira::ByteColor& c, Ionflux::Altjira::ChannelID channel);
void setComponent(Ionflux::Altjira::ByteColor& c, 
    Ionflux::Altjira::ChannelID channel, 
    Ionflux::Altjira::ByteColorValue value);
Ionflux::ObjectBase::UInt32 toUInt(const Ionflux::Altjira::ByteColor& c, 
    bool preMultiplied = true);
void fromUInt(Ionflux::ObjectBase::UInt32 v, Ionflux::Altjira::ByteColor& c, 
    bool preMultiplied = true);
std::string colorSpaceToString(const Ionflux::Altjira::ColorSpace& space);
std::string getString(const Ionflux::Altjira::FloatColor& c);
std::string getString(const Ionflux::Altjira::ByteColor& c);

struct ColorStop
{
    Ionflux::Altjira::Color color;
    double param;
};

typedef std::vector<Ionflux::Altjira::ColorStop> ColorStopVector;

bool operator==(const Ionflux::Altjira::ColorStop& s0, 
    const Ionflux::Altjira::ColorStop& s1);

typedef std::vector<Ionflux::Altjira::Color> ColorObjVector;

void createColors(Ionflux::Altjira::ColorObjVector& target, 
    const Ionflux::Altjira::FloatColor& c0, 
    const Ionflux::Altjira::FloatColor& c1, 
    unsigned int stepsC0 = 2, unsigned int stepsC1 = 2, 
    unsigned int stepsC2 = 2, unsigned int stepsAlpha = 1);

Ionflux::Altjira::ColorSpace getColorSpaceForChannel(
    Ionflux::Altjira::ChannelID channel, Ionflux::Altjira::ColorSpace hint = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED);

}

}

// Classes.

$ColorBand
$ColorBlender
$BlendSrcOver
$BlendMultiply
$BlendLighten
$BlendDarken
$BlendPlus
$BlendChannel
$PixelSource
$MatrixSource
$Image
$ImageSet
$ColorSet

%template(ImageRect) Ionflux::Altjira::Rectangle<unsigned int>;
%template(ColorStopVector) std::vector<Ionflux::Altjira::ColorStop>;
%template(ImageVector) std::vector<Ionflux::Altjira::Image*>;
%template(GIHRankSpecVector) std::vector<Ionflux::Altjira::GIHRankSpec>;
%template(ColorVector) std::vector<Ionflux::Altjira::Color*>;
%template(ColorObjVector) std::vector<Ionflux::Altjira::Color>;
