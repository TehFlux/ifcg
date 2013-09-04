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


%{
#include "altjira/Drawable.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Pattern;

class DrawableClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        DrawableClassInfo();
        virtual ~DrawableClassInfo();
};

class Drawable
: public Ionflux::Altjira::Image
{
    public:
        
        Drawable();
		Drawable(const Ionflux::Altjira::Drawable& other);
        Drawable(const std::string& fileName);
        Drawable(const Ionflux::Altjira::Image& initImage);
        Drawable(unsigned int initWidth, unsigned int initHeight, bool 
        initAlpha = true, unsigned int initBitsPerSample = 8, 
        Ionflux::Altjira::ColorSpace initColorSpace = 
        Ionflux::Altjira::Color::SPACE_RGB);
        virtual ~Drawable();
        virtual void begin(double originX = 0., double originY = 0.);
        virtual void discard();
        virtual void finish(const Ionflux::Altjira::ColorBlender* blender =
        0);
        virtual void save();
        virtual void restore();
        virtual void translate(double tx, double ty);
        virtual void scale(double sx, double sy);
        virtual void rotate(double phi);
        virtual void newPath();
        virtual void newSubPath();
        virtual void closePath();
        virtual void moveTo(double x, double y);
        virtual void lineTo(double x, double y);
        virtual void curveTo(double x0, double y0, double x1, double y1, 
        double x2, double y2);
        virtual void rectangle(double x, double y, double width, double 
        height);
        virtual void arc(double x, double y, double radius, double phi0 = 
        0., double phi1 = 2. * M_PI);
        virtual void setSourceColor(const Ionflux::Altjira::Color& color);
        virtual void setSource(Ionflux::Altjira::Pattern& pattern);
        virtual void setSourceImage(Ionflux::Altjira::Image* image, double 
        x = 0., double y = 0.);
        virtual void setFillRule(Ionflux::Altjira::FillRule fillRule);
        virtual void stroke(double lineWidth = 1., bool preserve = false);
        virtual void fillPath(bool preserve = false);
        virtual void paint();
        virtual Ionflux::Altjira::ImageRect getTextSize(const std::string& 
        text, const std::string& fontDesc = DEFAULT_FONT_DESCRIPTION, 
        double fontSize = DEFAULT_FONT_SIZE) const;
        virtual void drawText(double x, double y, const std::string& text, 
        const std::string& fontDesc = DEFAULT_FONT_DESCRIPTION, double 
        fontSize = DEFAULT_FONT_SIZE, const Ionflux::Altjira::Color& color 
        = Ionflux::Altjira::Color::BLACK);
        virtual void drawSVG(const std::string& svgData, int originX = 0, 
        int originY = 0);
        virtual void drawSVGFile(const std::string& svgFileName, int 
        originX = 0, int originY = 0);
        virtual bool drawingInProgress() const;
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Drawable* copy() const;
		static Ionflux::Altjira::Drawable* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Drawable* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}


%{
#include "altjira/Pattern.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Drawable;

class PatternClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PatternClassInfo();
        virtual ~PatternClassInfo();
};

class Pattern
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Pattern();
		Pattern(const Ionflux::Altjira::Pattern& other);
        virtual ~Pattern();
        virtual void clear();
        virtual void translate(double tx, double ty);
        virtual void scale(double sx, double sy);
        virtual void rotate(double phi);
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Pattern* copy() const;
		static Ionflux::Altjira::Pattern* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Pattern* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}


%{
#include "altjira/ImagePattern.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class Image;
class ColorBlender;

class ImagePatternClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImagePatternClassInfo();
        virtual ~ImagePatternClassInfo();
};

class ImagePattern
: public Ionflux::Altjira::Pattern
{
    public:
        
        ImagePattern();
		ImagePattern(const Ionflux::Altjira::ImagePattern& other);
        ImagePattern(Ionflux::Altjira::Image* initImage, double initOffsetX
        = 0., double initOffsetY = 0.);
        virtual ~ImagePattern();
        virtual void clear();
        virtual void update();
        virtual std::string getString() const;
		virtual Ionflux::Altjira::ImagePattern* copy() const;
		static Ionflux::Altjira::ImagePattern* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::ImagePattern* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setImage(Ionflux::Altjira::Image* newImage);
        virtual Ionflux::Altjira::Image* getImage() const;
        virtual void setOffsetX(double newOffsetX);
        virtual double getOffsetX() const;
        virtual void setOffsetY(double newOffsetY);
        virtual double getOffsetY() const;
};

}

}


%{
#include "altjira/Gradient.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class GradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        GradientClassInfo();
        virtual ~GradientClassInfo();
};

class Gradient
: public Ionflux::Altjira::Pattern
{
    public:
        
        Gradient();
		Gradient(const Ionflux::Altjira::Gradient& other);
        virtual ~Gradient();
        virtual void addColorStop(double offset, const 
        Ionflux::Altjira::Color& color);
        virtual unsigned int getNumColorStops() const;
        virtual void setFromColorBand(Ionflux::Altjira::ColorBand& 
        colorBand, Ionflux::Mapping::Mapping* sampleFunc = 0, unsigned int 
        numSamples = 20);
        virtual std::string getString() const;
		virtual Ionflux::Altjira::Gradient* copy() const;
		static Ionflux::Altjira::Gradient* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Altjira::Gradient* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}


%{
#include "altjira/RadialGradient.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class RadialGradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RadialGradientClassInfo();
        virtual ~RadialGradientClassInfo();
};

class RadialGradient
: public Ionflux::Altjira::Gradient
{
    public:
        
        RadialGradient();
		RadialGradient(const Ionflux::Altjira::RadialGradient& other);
        RadialGradient(double cx0, double cy0, double r0, double cx1, 
        double cy1, double r1);
        virtual ~RadialGradient();
        virtual void init(double cx0, double cy0, double r0, double cx1, 
        double cy1, double r1);
        static Ionflux::Altjira::RadialGradient* create(double cx0, double 
        cy0, double r0, double cx1, double cy1, double r1);
		virtual Ionflux::Altjira::RadialGradient* copy() const;
		static Ionflux::Altjira::RadialGradient* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::RadialGradient* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}


%{
#include "altjira/LinearGradient.hpp"
%}

namespace Ionflux
{

namespace Altjira
{

class LinearGradientClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LinearGradientClassInfo();
        virtual ~LinearGradientClassInfo();
};

class LinearGradient
: public Ionflux::Altjira::Gradient
{
    public:
        
        LinearGradient();
		LinearGradient(const Ionflux::Altjira::LinearGradient& other);
        LinearGradient(double x0, double y0, double x1, double y1);
        virtual ~LinearGradient();
        virtual void init(double x0, double y0, double x1, double y1);
        static Ionflux::Altjira::LinearGradient* create(double x0, double 
        y0, double x1, double y1);
		virtual Ionflux::Altjira::LinearGradient* copy() const;
		static Ionflux::Altjira::LinearGradient* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::Altjira::LinearGradient* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}

