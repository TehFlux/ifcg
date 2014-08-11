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
        $function
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
void colorToVec(const Ionflux::Altjira::Color& c, 
    Ionflux::GeoUtils::Vector4& target);
void vecToColor(const Ionflux::GeoUtils::Vector4& v, 
    Ionflux::Altjira::Color& target);
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


%{
#include "geoutils/SVG.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class SVGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        SVGClassInfo();
        virtual ~SVGClassInfo();
};

class SVG
: public Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::SVGType TYPE_UNDEFINED;
		static const Ionflux::GeoUtils::SVGType TYPE_FILE;
		static const Ionflux::GeoUtils::SVGType TYPE_DATA;
        
        SVG();
		SVG(const Ionflux::GeoUtils::SVG& other);
        SVG(const std::string& initSource, Ionflux::GeoUtils::SVGType 
        initType);
        virtual ~SVG();
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::SVG& duplicate();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::SVG* copy() const;
		static Ionflux::GeoUtils::SVG* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::SVG* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        virtual void setSource(const std::string& newSource);
        virtual std::string getSource() const;
        virtual void setType(Ionflux::GeoUtils::SVGType newType);
        virtual Ionflux::GeoUtils::SVGType getType() const;
};

}

}


%{
#include "geoutils/Image.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImageClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageClassInfo();
        virtual ~ImageClassInfo();
};

class Image
: public Ionflux::Altjira::Drawable, public 
Ionflux::GeoUtils::TransformableObject
{
    public:
		static const Ionflux::GeoUtils::Vector3 TANGENT_VECTORS[3][3];
        
        Image();
		Image(const Ionflux::GeoUtils::Image& other);
        Image(const std::string& fileName);
        Image(const Ionflux::Altjira::Image& initImage);
        Image(const Ionflux::Altjira::Drawable& initDrawable);
        Image(unsigned int initWidth, unsigned int initHeight, bool 
        initAlpha = true, unsigned int initBitsPerSample = 8, 
        Ionflux::Altjira::ColorSpace initColorSpace = 
        Ionflux::Altjira::Color::SPACE_RGB);
        virtual ~Image();
        virtual void drawPolygons(Ionflux::GeoUtils::Polygon3Set& polygons,
        const Ionflux::GeoUtils::SVGShapeStyleVector* styles = 0, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, bool 
        closePath = true, int originX = 0, int originY = 0);
        virtual void drawSVG(Ionflux::GeoUtils::SVG& svg, int originX = 0, 
        int originY = 0);
        virtual void drawImage(Ionflux::GeoUtils::Image* image, int originX
        = 0, int originY = 0);
        virtual void valueToNormal(Ionflux::Altjira::Image& target, double 
        maxHeight) const;
        virtual Ionflux::GeoUtils::TransformableObject& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::TransformableObject& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::TransformableObject& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual void drawTranslate(double tx, double ty);
        virtual void drawScale(double sx, double sy);
        virtual void drawRotate(double phi);
        virtual void setDrawingMatrix(const Ionflux::GeoUtils::Matrix4& m);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual Ionflux::GeoUtils::Image& duplicate();
        virtual std::string getString() const;
        virtual void getValueMatrix(Ionflux::Altjira::Matrix& target);
        virtual void setValueMatrix(const Ionflux::Altjira::Matrix& m);
        virtual void getPixelTree(Ionflux::GeoUtils::BoundingBox* target);
        virtual void markPixels(Ionflux::GeoUtils::BoxBoundsItemSet& 
        markPixels, const Ionflux::Altjira::Color& color = 
        Ionflux::Altjira::Color::BLUE, const 
        Ionflux::Altjira::ColorBlender* blender = 0);
		virtual Ionflux::GeoUtils::Image* copy() const;
		static Ionflux::GeoUtils::Image* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Image* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
};

}

}


%{
#include "geoutils/LoadSVG.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class LoadSVGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LoadSVGClassInfo();
        virtual ~LoadSVGClassInfo();
};

class LoadSVG
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
        
        LoadSVG();
		LoadSVG(const Ionflux::GeoUtils::TransformNodes::LoadSVG& other);
        LoadSVG(const std::string& initFileName, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~LoadSVG();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::LoadSVG* copy() const;
		static Ionflux::GeoUtils::TransformNodes::LoadSVG* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::LoadSVG* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFileName(const std::string& newFileName);
        virtual std::string getFileName() const;        
        virtual unsigned int getNumElementIDs() const;
        virtual std::string getElementID(unsigned int elementIndex = 0) 
        const;
		virtual int findElementID(std::string needle, unsigned int occurence = 1)
		const;
        virtual std::vector<std::string>& getElementIDs();
        virtual void addElementID(std::string addElement);        
        virtual void removeElementID(std::string removeElement);
		virtual void removeElementIDIndex(unsigned int removeIndex);
		virtual void clearElementIDs();
};

}

}

}


%{
#include "geoutils/WritePNG.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class WritePNGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        WritePNGClassInfo();
        virtual ~WritePNGClassInfo();
};

class WritePNG
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_COMPOSITE;
        
        WritePNG();
		WritePNG(const Ionflux::GeoUtils::TransformNodes::WritePNG& other);
        WritePNG(const std::string& initFileName, Ionflux::GeoUtils::AxisID
        initAxis = Ionflux::GeoUtils::AXIS_Z, bool initClosePath = true, 
        const Ionflux::GeoUtils::SVGShapeStyleVector* initStyles = 0, 
        unsigned int initWidth = 1000, unsigned int initHeight = 1000, 
        unsigned int initOriginX = 0, unsigned int initOriginY = 0, const 
        Ionflux::Altjira::Color& initBackgroundColor = 
        Ionflux::Altjira::Color::TRANSPARENT, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~WritePNG();
        virtual std::string getString() const;
        virtual void addStyles(const 
        Ionflux::GeoUtils::SVGShapeStyleVector& newStyles);
		virtual Ionflux::GeoUtils::TransformNodes::WritePNG* copy() const;
		static Ionflux::GeoUtils::TransformNodes::WritePNG* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::WritePNG* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setFileName(const std::string& newFileName);
        virtual std::string getFileName() const;        
        virtual unsigned int getNumStyles() const;
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(unsigned int 
        elementIndex = 0) const;
		virtual int findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& 
        getStyles();
        virtual void addStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        addElement);        
        virtual void removeStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        removeElement);
		virtual void removeStyleIndex(unsigned int removeIndex);
		virtual void clearStyles();
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
        virtual void setClosePath(bool newClosePath);
        virtual bool getClosePath() const;
        virtual void setWidth(unsigned int newWidth);
        virtual unsigned int getWidth() const;
        virtual void setHeight(unsigned int newHeight);
        virtual unsigned int getHeight() const;
        virtual void setOriginX(unsigned int newOriginX);
        virtual unsigned int getOriginX() const;
        virtual void setOriginY(unsigned int newOriginY);
        virtual unsigned int getOriginY() const;
        virtual void setBackgroundColor(const Ionflux::Altjira::Color& 
        newBackgroundColor);
        virtual Ionflux::Altjira::Color getBackgroundColor() const;
};

}

}

}


%{
#include "geoutils/Render.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class RenderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        RenderClassInfo();
        virtual ~RenderClassInfo();
};

class Render
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_COMPOSITE;
        
        Render();
		Render(const Ionflux::GeoUtils::TransformNodes::Render& other);
        Render(Ionflux::GeoUtils::Image* initImage, 
        Ionflux::GeoUtils::AxisID initAxis = Ionflux::GeoUtils::AXIS_Z, 
        bool initClosePath = true, const 
        Ionflux::GeoUtils::SVGShapeStyleVector* initStyles = 0, unsigned 
        int initWidth = 1000, unsigned int initHeight = 1000, unsigned int 
        initOriginX = 0, unsigned int initOriginY = 0, const 
        Ionflux::Altjira::Color& initBackgroundColor = 
        Ionflux::Altjira::Color::TRANSPARENT, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~Render();
        virtual std::string getString() const;
        virtual void addStyles(const 
        Ionflux::GeoUtils::SVGShapeStyleVector& newStyles);
		virtual Ionflux::GeoUtils::TransformNodes::Render* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Render* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Render* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setImage(Ionflux::GeoUtils::Image* newImage);
        virtual Ionflux::GeoUtils::Image* getImage() const;        
        virtual unsigned int getNumStyles() const;
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(unsigned int 
        elementIndex = 0) const;
		virtual int findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& 
        getStyles();
        virtual void addStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        addElement);        
        virtual void removeStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        removeElement);
		virtual void removeStyleIndex(unsigned int removeIndex);
		virtual void clearStyles();
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
        virtual void setClosePath(bool newClosePath);
        virtual bool getClosePath() const;
        virtual void setOriginX(unsigned int newOriginX);
        virtual unsigned int getOriginX() const;
        virtual void setOriginY(unsigned int newOriginY);
        virtual unsigned int getOriginY() const;
        virtual void setBackgroundColor(const Ionflux::Altjira::Color& 
        newBackgroundColor);
        virtual Ionflux::Altjira::Color getBackgroundColor() const;
};

}

}

}


%{
#include "geoutils/ImageItem.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImageItemClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageItemClassInfo();
        virtual ~ImageItemClassInfo();
};

class ImageItem
: public Ionflux::GeoUtils::BoxBoundsItem
{
    public:
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_UNDEFINED;
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_FILE;
		static const Ionflux::GeoUtils::SVGType SOURCE_TYPE_SOURCE;
        
        ImageItem();
		ImageItem(const Ionflux::GeoUtils::ImageItem& other);
        ImageItem(const std::string& initImageID, 
        Ionflux::GeoUtils::ImageSourceType initSourceType, const 
        Ionflux::GeoUtils::Vector3& initOffset = 
        Ionflux::GeoUtils::Vector3::ZERO, Ionflux::Altjira::ColorBlender* 
        initBlender = 0, Ionflux::GeoUtils::Image* initImage = 0, 
        Ionflux::GeoUtils::ImageSource* initSource = 0);
        virtual ~ImageItem();
        virtual void clear();
        virtual void update();
        virtual void acquire();
        virtual void release();
        virtual void load();
        virtual void clearData();
        virtual std::string getString() const;
        static std::string 
        getSourceTypeString(Ionflux::GeoUtils::ImageSourceType sourceType);
		virtual Ionflux::GeoUtils::ImageItem* copy() const;
		static Ionflux::GeoUtils::ImageItem* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ImageItem* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setImage(Ionflux::GeoUtils::Image* newImage);
        virtual Ionflux::GeoUtils::Image* getImage() const;
        virtual void setImageID(const std::string& newImageID);
        virtual std::string getImageID() const;
        virtual void setSourceType(Ionflux::GeoUtils::ImageSourceType 
        newSourceType);
        virtual Ionflux::GeoUtils::ImageSourceType getSourceType() const;
        virtual void setBlender(Ionflux::Altjira::ColorBlender* 
        newBlender);
        virtual Ionflux::Altjira::ColorBlender* getBlender() const;
        virtual void setNumUsers(unsigned int newNumUsers);
        virtual unsigned int getNumUsers() const;
        virtual void setSource(Ionflux::GeoUtils::ImageSource* newSource);
        virtual Ionflux::GeoUtils::ImageSource* getSource() const;
        virtual void setOffset(Ionflux::GeoUtils::Vector3 newOffset);
        virtual Ionflux::GeoUtils::Vector3 getOffset() const;
};

}

}


%{
#include "geoutils/ImageSource.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImageSourceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageSourceClassInfo();
        virtual ~ImageSourceClassInfo();
};

class ImageSource
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        ImageSource();
		ImageSource(const Ionflux::GeoUtils::ImageSource& other);
        virtual ~ImageSource();
        virtual Ionflux::GeoUtils::Image* getImage(const 
        Ionflux::GeoUtils::ImageID& imageID) = 0;
        virtual std::string getString() const;
		static Ionflux::GeoUtils::ImageSource* 
		upcast(Ionflux::ObjectBase::IFObject* other);
};

}

}


%{
#include "geoutils/ImageLoader.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ImageLoaderClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ImageLoaderClassInfo();
        virtual ~ImageLoaderClassInfo();
};

class ImageLoader
: public Ionflux::GeoUtils::ImageSource
{
    public:
        
        ImageLoader();
		ImageLoader(const Ionflux::GeoUtils::ImageLoader& other);
        ImageLoader(const std::string& initMappedPrefix, const std::string&
        initUnmappedPrefix = "", Ionflux::ObjectBase::IFCache* initCache = 
        0);
        virtual ~ImageLoader();
        virtual void setPrefix(const std::string& prefix);
        virtual void addImage(const Ionflux::GeoUtils::ImageID& imageID, 
        Ionflux::GeoUtils::Image* image, const std::string& fileName = "");
        virtual Ionflux::GeoUtils::Image* getImage(const 
        Ionflux::GeoUtils::ImageID& imageID);
        virtual void initCache(Ionflux::ObjectBase::UInt64 maxSize = 0);
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::ImageLoader* copy() const;
		static Ionflux::GeoUtils::ImageLoader* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ImageLoader* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual unsigned int getNumImageIDs() const;
        virtual Ionflux::GeoUtils::ImageID getImageID(const std::string& 
        elementKey) const;

        virtual std::map<std::string, Ionflux::GeoUtils::ImageID>& 
        getImageIDs();
        virtual void addImageID(const std::string& elementKey, 
        Ionflux::GeoUtils::ImageID addElement);        
        virtual void removeImageID(const std::string& elementKey);
		virtual void clearImageIDs();
        virtual void setMappedPrefix(const std::string& newMappedPrefix);
        virtual std::string getMappedPrefix() const;
        virtual void setUnmappedPrefix(const std::string& 
        newUnmappedPrefix);
        virtual std::string getUnmappedPrefix() const;
        virtual void setCache(Ionflux::ObjectBase::IFCache* newCache);
        virtual Ionflux::ObjectBase::IFCache* getCache() const;
};

}

}


