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


%{
#include "altjira/Color.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

struct ColorPair;

class ColorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ColorClassInfo();
        virtual ~ColorClassInfo();
};

class Color
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Altjira::Color TRANSPARENT;
		static const Ionflux::Altjira::Color BLACK;
		static const Ionflux::Altjira::Color WHITE;
		static const Ionflux::Altjira::Color GRAY_10;
		static const Ionflux::Altjira::Color GRAY_20;
		static const Ionflux::Altjira::Color GRAY_30;
		static const Ionflux::Altjira::Color GRAY_40;
		static const Ionflux::Altjira::Color GRAY_50;
		static const Ionflux::Altjira::Color GRAY_60;
		static const Ionflux::Altjira::Color GRAY_70;
		static const Ionflux::Altjira::Color GRAY_80;
		static const Ionflux::Altjira::Color GRAY_90;
		static const Ionflux::Altjira::Color RED;
		static const Ionflux::Altjira::Color GREEN;
		static const Ionflux::Altjira::Color BLUE;
		static const Ionflux::Altjira::Color CYAN;
		static const Ionflux::Altjira::Color MAGENTA;
		static const Ionflux::Altjira::Color YELLOW;
		static const Ionflux::Altjira::Color VIOLET;
		static const Ionflux::Altjira::Color ORANGE;
		static const Ionflux::Altjira::ColorSpace SPACE_UNDEFINED;
		static const Ionflux::Altjira::ColorSpace SPACE_RGB;
		static const Ionflux::Altjira::ColorSpace SPACE_HSV;
		static const Ionflux::Altjira::ColorSpace SPACE_HSL;
        
        Color();
		Color(const Ionflux::Altjira::Color& other);
        Color(const ByteColor& initColor);
        Color(const FloatColor& initColor);
        Color(FloatColorValue initRed, FloatColorValue initGreen, 
        FloatColorValue initBlue, FloatColorValue initAlpha);
        Color(ByteColorValue initRed, ByteColorValue initGreen, 
        ByteColorValue initBlue, ByteColorValue initAlpha);
        Color(const std::string& hexColor);
        virtual ~Color();
        virtual Ionflux::Altjira::Color& setFromHex(const std::string& 
        hexColor);
        virtual std::string getHex() const;
        virtual Ionflux::Altjira::Color& clampRed(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        virtual Ionflux::Altjira::Color& clampGreen(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        virtual Ionflux::Altjira::Color& clampBlue(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        virtual Ionflux::Altjira::Color& clampAlpha(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        virtual Ionflux::Altjira::Color& clamp(const 
        Ionflux::Mapping::Range& range = DEFAULT_CLAMP_RANGE);
        static Ionflux::Altjira::Color interpolate(const 
        Ionflux::Altjira::Color& first, const Ionflux::Altjira::Color& 
        second, double factor);
        virtual Ionflux::Altjira::Color& setFromFloatColor(const 
        Ionflux::Altjira::FloatColor& other);
        virtual Ionflux::Altjira::Color& 
        setComponents(Ionflux::Altjira::FloatColorValue newRed, 
        Ionflux::Altjira::FloatColorValue newGreen, 
        Ionflux::Altjira::FloatColorValue newBlue, 
        Ionflux::Altjira::FloatColorValue newAlpha);
        virtual Ionflux::Altjira::Color& 
        setComponents(Ionflux::Altjira::ByteColorValue newRed, 
        Ionflux::Altjira::ByteColorValue newGreen, 
        Ionflux::Altjira::ByteColorValue newBlue, 
        Ionflux::Altjira::ByteColorValue newAlpha);
        virtual void getFloatColor(Ionflux::Altjira::FloatColor& color) 
        const;
        virtual void getByteColor(Ionflux::Altjira::ByteColor& color) 
        const;
        virtual Ionflux::Altjira::Color& setFromByteColor(const 
        Ionflux::Altjira::ByteColor& other);
        virtual void multiply(Ionflux::Altjira::Color& target, double 
        value);
        virtual double getMeanSquaredError(const Ionflux::Altjira::Color& 
        refColor);
        virtual void preMultiply(Ionflux::Altjira::Color& target);
        virtual void divideAlpha(Ionflux::Altjira::Color& target);
        virtual bool operator==(const Ionflux::Altjira::Color& other) 
        const;
        virtual bool operator!=(const Ionflux::Altjira::Color& other) 
        const;
        virtual std::string getValueString() const;
        static Ionflux::Altjira::Color interpolate(const 
        Ionflux::Altjira::ColorPair& colors, double factor = 0.5);
		virtual Ionflux::Altjira::Color* copy() const;
		static Ionflux::Altjira::Color* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Color* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Altjira::Color* create(const ByteColor& initColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Color* create(const FloatColor& initColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Color* create(FloatColorValue initRed, 
		FloatColorValue initGreen, FloatColorValue initBlue, FloatColorValue 
		initAlpha, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Color* create(ByteColorValue initRed, 
		ByteColorValue initGreen, ByteColorValue initBlue, ByteColorValue 
		initAlpha, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::Altjira::Color* create(const std::string& hexColor, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setRed(double newRed);
        virtual double getRed() const;
        virtual void setGreen(double newGreen);
        virtual double getGreen() const;
        virtual void setBlue(double newBlue);
        virtual double getBlue() const;
        virtual void setAlpha(double newAlpha);
        virtual double getAlpha() const;
        virtual void setHue(double newHue);
        virtual double getHue() const;
        virtual void setSaturation(double newSaturation);
        virtual double getSaturation() const;
        virtual void setLuminance(double newLuminance);
        virtual double getLuminance() const;
};

}

}


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


%{
#include "altjira/ColorBand.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class ColorSet;

class ColorBandClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ColorBandClassInfo();
        virtual ~ColorBandClassInfo();
};

class ColorBand
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        ColorBand();
		ColorBand(const Ionflux::Altjira::ColorBand& other);
        ColorBand(Ionflux::Altjira::ColorStopVector initColorStops);
        virtual ~ColorBand();
        virtual void clear();
        virtual std::string getString() const;
        virtual void update();
        virtual void eval(double value, Ionflux::Altjira::FloatColor& 
        target);
        virtual void eval(double value, Ionflux::Altjira::ByteColor& 
        target);
        virtual void eval(double value, Ionflux::Altjira::Color& target);
        virtual Ionflux::Altjira::Color operator()(double value);
        virtual void sample(unsigned int numSamples, 
        Ionflux::Altjira::ColorSet& target);
        static Ionflux::Altjira::ColorBand* rainbow();
        static Ionflux::Altjira::ColorBand* flame();
        static Ionflux::Altjira::ColorBand* ice();
        static Ionflux::Altjira::ColorBand* terrain();
        static Ionflux::Altjira::ColorBand* heat();
        static Ionflux::Altjira::ColorBand* glow(const 
        Ionflux::Altjira::Color& color, double maxL = 1.);
		virtual Ionflux::Altjira::ColorBand* copy() const;
		static Ionflux::Altjira::ColorBand* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Altjira::ColorBand* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Altjira::ColorBand* 
		create(Ionflux::Altjira::ColorStopVector initColorStops, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumColorStops() const;
        virtual Ionflux::Altjira::ColorStop getColorStop(unsigned int 
        elementIndex = 0) const;
		virtual int findColorStop(Ionflux::Altjira::ColorStop needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::Altjira::ColorStop>& getColorStops();
        virtual void addColorStop(Ionflux::Altjira::ColorStop addElement);        
        virtual void removeColorStop(Ionflux::Altjira::ColorStop 
        removeElement);
		virtual void removeColorStopIndex(unsigned int removeIndex);
		virtual void clearColorStops();
};

}

}


%{
#include "altjira/ColorBlender.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class ColorBlenderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ColorBlenderClassInfo();
        virtual ~ColorBlenderClassInfo();
};

class ColorBlender
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        ColorBlender();
		ColorBlender(const Ionflux::Altjira::ColorBlender& other);
        ColorBlender(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 1.);
        virtual ~ColorBlender();
        virtual void blend(Ionflux::Altjira::Color& target, const 
        Ionflux::Altjira::Color& newColor0, const Ionflux::Altjira::Color& 
        newColor1, double newSourceOpacity = 1., double newTargetOpacity = 
        1.) const;
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 1.) const = 0;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
        virtual void operator()(Ionflux::Altjira::Color& target, const 
        Ionflux::Altjira::Color* newColor0 = 0, const 
        Ionflux::Altjira::Color* newColor1 = 0, const double* 
        newSourceOpacity = 0, const double* newTargetOpacity = 0) const;
        virtual std::string getString() const;
        virtual void setColor0(const Ionflux::Altjira::Color& newColor0);
        virtual Ionflux::Altjira::Color getColor0() const;
        virtual void setColor1(const Ionflux::Altjira::Color& newColor1);
        virtual Ionflux::Altjira::Color getColor1() const;
        virtual void setSourceOpacity(double newSourceOpacity);
        virtual double getSourceOpacity() const;
        virtual void setTargetOpacity(double newTargetOpacity);
        virtual double getTargetOpacity() const;
};

}

}


%{
#include "altjira/BlendSrcOver.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class BlendSrcOverClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BlendSrcOverClassInfo();
        virtual ~BlendSrcOverClassInfo();
};

class BlendSrcOver
: public Ionflux::Altjira::ColorBlender
{
    public:
        
        BlendSrcOver();
		BlendSrcOver(const Ionflux::Altjira::BlendSrcOver& other);
        BlendSrcOver(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 1.);
        virtual ~BlendSrcOver();
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 1.) const;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
		virtual Ionflux::Altjira::BlendSrcOver* copy() const;
		static Ionflux::Altjira::BlendSrcOver* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::BlendSrcOver* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


%{
#include "altjira/BlendMultiply.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class BlendMultiplyClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BlendMultiplyClassInfo();
        virtual ~BlendMultiplyClassInfo();
};

class BlendMultiply
: public Ionflux::Altjira::ColorBlender
{
    public:
        
        BlendMultiply();
		BlendMultiply(const Ionflux::Altjira::BlendMultiply& other);
        BlendMultiply(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 1.);
        virtual ~BlendMultiply();
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 1.) const;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
		virtual Ionflux::Altjira::BlendMultiply* copy() const;
		static Ionflux::Altjira::BlendMultiply* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::BlendMultiply* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


%{
#include "altjira/BlendLighten.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class BlendLightenClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BlendLightenClassInfo();
        virtual ~BlendLightenClassInfo();
};

class BlendLighten
: public Ionflux::Altjira::ColorBlender
{
    public:
        
        BlendLighten();
		BlendLighten(const Ionflux::Altjira::BlendLighten& other);
        BlendLighten(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 1.);
        virtual ~BlendLighten();
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 1.) const;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
		virtual Ionflux::Altjira::BlendLighten* copy() const;
		static Ionflux::Altjira::BlendLighten* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::BlendLighten* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


%{
#include "altjira/BlendDarken.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class BlendDarkenClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BlendDarkenClassInfo();
        virtual ~BlendDarkenClassInfo();
};

class BlendDarken
: public Ionflux::Altjira::ColorBlender
{
    public:
        
        BlendDarken();
		BlendDarken(const Ionflux::Altjira::BlendDarken& other);
        BlendDarken(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 1.);
        virtual ~BlendDarken();
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 1.) const;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
		virtual Ionflux::Altjira::BlendDarken* copy() const;
		static Ionflux::Altjira::BlendDarken* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::BlendDarken* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


%{
#include "altjira/BlendPlus.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class BlendPlusClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BlendPlusClassInfo();
        virtual ~BlendPlusClassInfo();
};

class BlendPlus
: public Ionflux::Altjira::ColorBlender
{
    public:
        
        BlendPlus();
		BlendPlus(const Ionflux::Altjira::BlendPlus& other);
        BlendPlus(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 1.);
        virtual ~BlendPlus();
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 1.) const;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 255) const;
		virtual Ionflux::Altjira::BlendPlus* copy() const;
		static Ionflux::Altjira::BlendPlus* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::Altjira::BlendPlus* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


%{
#include "altjira/BlendChannel.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class BlendChannelClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BlendChannelClassInfo();
        virtual ~BlendChannelClassInfo();
};

class BlendChannel
: public Ionflux::Altjira::ColorBlender
{
    public:
        
        BlendChannel();
		BlendChannel(const Ionflux::Altjira::BlendChannel& other);
        BlendChannel(const Ionflux::Altjira::Color& initColor0, const 
        Ionflux::Altjira::Color& initColor1 = 
        Ionflux::Altjira::Color::WHITE, double initSourceOpacity = 1., 
        double initTargetOpacity = 0., Ionflux::Altjira::ChannelID 
        initSrcChannel = Ionflux::Altjira::CH_VALUE, 
        Ionflux::Altjira::ChannelID initDestChannel = 
        Ionflux::Altjira::CH_VALUE, Ionflux::Altjira::ColorSpace 
        initSrcSpace = Ionflux::Altjira::Color::SPACE_UNDEFINED, 
        Ionflux::Altjira::ColorSpace initDestSpace = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED, 
        Ionflux::Mapping::Mapping* initSrcFunc = 0, 
        Ionflux::Mapping::Mapping* initDestFunc = 0);
        virtual ~BlendChannel();
        virtual void blend(Ionflux::Altjira::FloatColor& target, const 
        Ionflux::Altjira::FloatColor& newColor0, const 
        Ionflux::Altjira::FloatColor& newColor1, double newSourceOpacity = 
        1., double newTargetOpacity = 0.) const;
        virtual void blend(Ionflux::Altjira::ByteColor& target, const 
        Ionflux::Altjira::ByteColor& newColor0, const 
        Ionflux::Altjira::ByteColor& newColor1, const 
        Ionflux::Altjira::ByteColorValue& newSourceOpacity = 255, const 
        Ionflux::Altjira::ByteColorValue& newTargetOpacity = 0) const;
		virtual Ionflux::Altjira::BlendChannel* copy() const;
		static Ionflux::Altjira::BlendChannel* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setSrcFunc(Ionflux::Mapping::Mapping* newSrcFunc);
        virtual Ionflux::Mapping::Mapping* getSrcFunc() const;
        virtual void setDestFunc(Ionflux::Mapping::Mapping* newDestFunc);
        virtual Ionflux::Mapping::Mapping* getDestFunc() const;
        virtual void setSrcChannel(Ionflux::Altjira::ChannelID 
        newSrcChannel);
        virtual Ionflux::Altjira::ChannelID getSrcChannel() const;
        virtual void setDestChannel(Ionflux::Altjira::ChannelID 
        newDestChannel);
        virtual Ionflux::Altjira::ChannelID getDestChannel() const;
        virtual void setSrcSpace(Ionflux::Altjira::ColorSpace newSrcSpace);
        virtual Ionflux::Altjira::ColorSpace getSrcSpace() const;
        virtual void setDestSpace(Ionflux::Altjira::ColorSpace 
        newDestSpace);
        virtual Ionflux::Altjira::ColorSpace getDestSpace() const;
};

}

}


%{
#include "altjira/Image.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class ImageSet;

class ImageClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageClassInfo();
        virtual ~ImageClassInfo();
};

class Image
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::Altjira::ImageType TYPE_PNG;
		static const Ionflux::Altjira::ImageType TYPE_JPEG;
		static const Ionflux::Altjira::ImageType TYPE_GBR_GRAYSCALE;
		static const Ionflux::Altjira::ImageType TYPE_GBR_RGBA;
		static const Ionflux::Altjira::ImageType TYPE_GIH_GRAYSCALE;
		static const Ionflux::Altjira::ImageType TYPE_GIH_RGBA;
		static const std::string GIH_DEFAULT_PLACEMENT;
		static const unsigned int GIH_CELL_SIZE_MAX;
		static const unsigned int GIH_DEFAULT_CELL_WIDTH;
		static const unsigned int GIH_DEFAULT_CELL_HEIGHT;
        
        Image();
		Image(const Ionflux::Altjira::Image& other);
        Image(const std::string& fileName);
        Image(unsigned int initWidth, unsigned int initHeight, bool 
        initAlpha = true, unsigned int initBitsPerSample = 8, 
        Ionflux::Altjira::ColorSpace initColorSpace = 
        Ionflux::Altjira::Color::SPACE_RGB);
        virtual ~Image();
        virtual void createNewData(unsigned int initWidth, unsigned int 
        initHeight, bool initAlpha = true, unsigned int initBitsPerSample =
        8, Ionflux::Altjira::ColorSpace initColorSpace = 
        Ionflux::Altjira::Color::SPACE_RGB);
        virtual bool loadFromFile(const std::string& fileName);
        virtual void getGIHData(std::string& target, unsigned int cellWidth
        = GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
        GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector*
        ranks = 0, const std::string& placement = 
        Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
        brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int 
        spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
        virtual void getGBRData(std::string& target, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
        brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int 
        spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
        virtual bool writeGBR(const std::string& fileName, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
        brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int 
        spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
        virtual bool writeGIH(const std::string& fileName, unsigned int 
        cellWidth = GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
        GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector*
        ranks = 0, const std::string& placement = 
        Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_GBR_GRAYSCALE, const std::string& 
        brushName = Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int 
        spacing = Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD);
        virtual bool writeToFile(const std::string& fileName, 
        Ionflux::Altjira::ImageType type = 
        Ionflux::Altjira::Image::TYPE_PNG, const std::string& brushName = 
        Ionflux::Altjira::DEFAULT_BRUSH_NAME, unsigned int spacing = 
        Ionflux::Altjira::DEFAULT_BRUSH_SPACING, 
        Ionflux::Altjira::DesaturationMethod desaturationMethod = 
        Ionflux::Altjira::DEFAULT_DESATURATION_METHOD, unsigned int 
        cellWidth = GIH_DEFAULT_CELL_WIDTH, unsigned int cellHeight = 
        GIH_DEFAULT_CELL_HEIGHT, const Ionflux::Altjira::GIHRankSpecVector*
        ranks = 0, const std::string& placement = 
        Ionflux::Altjira::Image::GIH_DEFAULT_PLACEMENT);
        virtual void clear();
        virtual bool setPixel(unsigned int x, unsigned int y, const 
        Ionflux::Altjira::ByteColor& color);
        virtual bool setPixel(unsigned int x, unsigned int y, const 
        Ionflux::Altjira::FloatColor& color);
        virtual bool setPixel(unsigned int x, unsigned int y, const 
        Ionflux::Altjira::Color& color);
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::ByteColor& color);
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::FloatColor& color) const;
        virtual bool getPixel(unsigned int x, unsigned int y, 
        Ionflux::Altjira::Color& color) const;
        virtual bool fill(const Ionflux::Altjira::ByteColor& color);
        virtual bool fill(const Ionflux::Altjira::FloatColor& color);
        virtual bool fill(const Ionflux::Altjira::Color& color);
        virtual bool fill(const Ionflux::Altjira::Image& other, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual bool composite(const Ionflux::Altjira::Image& other, const 
        Ionflux::Altjira::ColorBlender* blender = 0, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual void createArray(Ionflux::Altjira::ImageSet& target, 
        unsigned int cellWidth, unsigned int cellHeight) const;
        virtual void compositeArray(const Ionflux::Altjira::ImageSet& 
        source, unsigned int cellWidth, unsigned int cellHeight, unsigned 
        int numCols, unsigned int numRows, const 
        Ionflux::Altjira::ColorBlender* blender = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual bool convolveFill(const Ionflux::Altjira::Image& other, 
        const Ionflux::Mapping::Matrix& matrix, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual bool setChannel(Ionflux::Altjira::Image& other, 
        Ionflux::Altjira::ChannelID source, Ionflux::Altjira::ChannelID 
        target, Ionflux::Mapping::Mapping* mapping = 0, 
        Ionflux::Altjira::ColorSpace sourceSpace = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED, 
        Ionflux::Altjira::ColorSpace targetSpace = 
        Ionflux::Altjira::Color::SPACE_UNDEFINED, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual bool mask(Ionflux::Altjira::Image& other, 
        Ionflux::Altjira::ChannelID source = Ionflux::Altjira::CH_VALUE, 
        Ionflux::Mapping::Mapping* mapping = 0, 
        Ionflux::Altjira::ColorSpace sourceSpace = 
        Ionflux::Altjira::Color::SPACE_HSV, const 
        Ionflux::Altjira::ImageRect* sourceRect = 0, unsigned int offsetX =
        0, unsigned int offsetY = 0);
        virtual void valuesToColor(Ionflux::Altjira::ColorBand& colors);
        virtual void colorToAlpha(const Ionflux::Altjira::Color& color);
        virtual void luminize(const Ionflux::Altjira::Image& source, double
        amount = 1.);
        virtual bool hasAlpha() const;
        virtual void clamp(Ionflux::Altjira::ImageRect& r0) const;
        virtual void getRandomPoints(unsigned int numPoints, 
        Ionflux::Mapping::PointSet& target, unsigned int maxIters = 100) 
        const;
        virtual void getColorDifference(const Ionflux::Altjira::Color& 
        refColor, Ionflux::Altjira::Image& targetImage, 
        Ionflux::Mapping::Mapping* mapping = 0) const;
        virtual void getChannel(Ionflux::Altjira::ChannelID channel, 
        Ionflux::Mapping::Matrix& target, Ionflux::Altjira::ColorSpace 
        colorSpace = Ionflux::Altjira::Color::SPACE_HSV) const;
        virtual Ionflux::ObjectBase::UInt64 getSize() const;
        virtual std::string getString() const;
        static Ionflux::Altjira::Image* create(unsigned int initWidth, 
        unsigned int initHeight, bool initAlpha = true, unsigned int 
        initBitsPerSample = 8, Ionflux::Altjira::ColorSpace initColorSpace 
        = Ionflux::Altjira::Color::SPACE_RGB);
		virtual Ionflux::Altjira::Image* copy() const;
		static Ionflux::Altjira::Image* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Image* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual unsigned int getNumChannels() const;
        virtual unsigned int getBitsPerSample() const;
        virtual Ionflux::Altjira::ColorSpace getColorSpace() const;
        virtual unsigned int getWidth() const;
        virtual unsigned int getHeight() const;
        virtual unsigned int getRowStride() const;
        virtual Ionflux::Altjira::PixelData getPixels() const;
};

}

}


%{
#include "altjira/ImageSet.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Image;

class ImageSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageSetClassInfo();
        virtual ~ImageSetClassInfo();
};

class ImageSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        ImageSet();
		ImageSet(const Ionflux::Altjira::ImageSet& other);
        ImageSet(const Ionflux::Altjira::ImageVector& initImages);
        virtual ~ImageSet();
        virtual void addImages(const Ionflux::Altjira::ImageVector& 
        newImages);
        virtual std::string getString() const;
		virtual Ionflux::Altjira::ImageSet* copy() const;
		static Ionflux::Altjira::ImageSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::ImageSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumImages() const;
        virtual Ionflux::Altjira::Image* getImage(unsigned int elementIndex
        = 0) const;
		virtual int findImage(Ionflux::Altjira::Image* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Altjira::Image*>& getImages();
        virtual void addImage(Ionflux::Altjira::Image* addElement);        
        virtual void removeImage(Ionflux::Altjira::Image* removeElement);
		virtual void removeImageIndex(unsigned int removeIndex);
		virtual void clearImages();
};

}

}


%{
#include "altjira/ColorSet.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Color;

class ColorSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ColorSetClassInfo();
        virtual ~ColorSetClassInfo();
};

class ColorSet
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        ColorSet();
		ColorSet(const Ionflux::Altjira::ColorSet& other);
        ColorSet(Ionflux::Altjira::ColorVector& initColors);
        virtual ~ColorSet();
        virtual bool operator==(const Ionflux::Altjira::ColorSet& other) 
        const;
        virtual bool operator!=(const Ionflux::Altjira::ColorSet& other) 
        const;
        virtual std::string getValueString() const;
		virtual Ionflux::Altjira::ColorSet* copy() const;
		static Ionflux::Altjira::ColorSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::ColorSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Altjira::ColorSet* create(Ionflux::Altjira::ColorVector& 
		initColors, Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumColors() const;
        virtual Ionflux::Altjira::Color* getColor(unsigned int elementIndex
        = 0) const;
		virtual int findColor(Ionflux::Altjira::Color* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Altjira::Color*>& getColors();
        virtual void addColor(Ionflux::Altjira::Color* addElement);
		virtual Ionflux::Altjira::Color* addColor();
		virtual void addColors(std::vector<Ionflux::Altjira::Color*>& newColors);
		virtual void addColors(Ionflux::Altjira::ColorSet* newColors);        
        virtual void removeColor(Ionflux::Altjira::Color* removeElement);
		virtual void removeColorIndex(unsigned int removeIndex);
		virtual void clearColors();
};

}

}


%template(ImageRect) Ionflux::Altjira::Rectangle<unsigned int>;
%template(ColorStopVector) std::vector<Ionflux::Altjira::ColorStop>;
%template(ImageVector) std::vector<Ionflux::Altjira::Image*>;
%template(GIHRankSpecVector) std::vector<Ionflux::Altjira::GIHRankSpec>;
%template(ColorVector) std::vector<Ionflux::Altjira::Color*>;
%template(ColorObjVector) std::vector<Ionflux::Altjira::Color>;
