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

// gltypes.hpp

typedef int VertexAttributeDataTypeID;
typedef int BufferUsageID;
typedef int PrimitiveID;
typedef int OpenGLProfileID;

// Classes


%{
#include "geoutils/Program.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix3;
class Matrix4;

class ProgramClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ProgramClassInfo();
        virtual ~ProgramClassInfo();
};

class Program
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const int INFO_LOG_BUFFER_SIZE;
		static const std::string DEFAULT_VERTEX_SHADER;
		static const std::string FRAGMENT_SHADER_FLAT_COLOR;
        
        Program();
		Program(const Ionflux::GeoUtils::Program& other);
        Program(const std::string& initVertexShaderSource, const 
        std::string& initFragmentShaderSource = 
        FRAGMENT_SHADER_FLAT_COLOR);
        virtual ~Program();
        virtual void cleanup();
        virtual void init();
        virtual void use();
        virtual void setUniform(const std::string& name, const 
        Ionflux::GeoUtils::Matrix4& value);
        virtual void setUniform(const std::string& name, const 
        Ionflux::GeoUtils::Matrix3& value);
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::Program* copy() const;
		static Ionflux::GeoUtils::Program* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Program* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Program* create(const std::string& 
		initVertexShaderSource, const std::string& initFragmentShaderSource = 
		FRAGMENT_SHADER_FLAT_COLOR, Ionflux::ObjectBase::IFObject* parentObject =
		0);
        virtual void setVertexShaderSource(const std::string 
        newVertexShaderSource);
        virtual std::string getVertexShaderSource() const;
        virtual void setFragmentShaderSource(const std::string 
        newFragmentShaderSource);
        virtual std::string getFragmentShaderSource() const;
        virtual GLuint getVertexShaderImpl() const;
        virtual GLuint getFragmentShaderImpl() const;
        virtual GLuint getProgramImpl() const;
};

}

}


%{
#include "geoutils/VertexAttribute.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Vertex3Set;
class VectorSet;

class VertexAttributeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VertexAttributeClassInfo();
        virtual ~VertexAttributeClassInfo();
};

class VertexAttribute
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::VertexAttributeDataTypeID DATA_TYPE_FLOAT;
		static const Ionflux::GeoUtils::VertexAttributeDataTypeID DATA_TYPE_UINT;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_DRAW;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_READ;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_STREAM_COPY;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_DRAW;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_READ;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_STATIC_COPY;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_DRAW;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_READ;
		static const Ionflux::GeoUtils::BufferUsageID USAGE_DYNAMIC_COPY;
		static const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_POINT;
		static const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_LINE;
		static const Ionflux::GeoUtils::PrimitiveID PRIMITIVE_TRIANGLE;
        
        VertexAttribute();
		VertexAttribute(const Ionflux::GeoUtils::VertexAttribute& other);
        virtual ~VertexAttribute();
        virtual void cleanupData();
        virtual void cleanup();
        virtual void init();
        virtual void bind();
        virtual void update(Ionflux::GeoUtils::BufferUsageID usage = 
        USAGE_STATIC_DRAW);
        virtual void enable(unsigned int index);
        virtual void setData(const Ionflux::GeoUtils::Vertex3Set& newData);
        virtual void setData(const Ionflux::GeoUtils::VectorSet& newData, 
        int useNumElements = 0, float defaultValue = 0.);
        virtual void setData(const Ionflux::Altjira::ColorSet& newData);
        virtual void setData(const Ionflux::ObjectBase::UIntVector& 
        newData);
        virtual float getFloat(unsigned int elementIndex, unsigned int 
        componentIndex = 0);
        virtual void setData(unsigned int elementIndex, unsigned int 
        componentIndex, float value);
        virtual void draw(Ionflux::GeoUtils::PrimitiveID primitiveID, 
        unsigned int drawNumPrimitives = 0, unsigned int startIndex = 0);
        virtual std::string getValueString() const;
        static std::string 
        getDataTypeString(Ionflux::GeoUtils::VertexAttributeDataTypeID 
        dataType);
        static unsigned int 
        getNumElementsPerPrimitive(Ionflux::GeoUtils::PrimitiveID 
        primitive);
		virtual Ionflux::GeoUtils::VertexAttribute* copy() const;
		static Ionflux::GeoUtils::VertexAttribute* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::VertexAttribute* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual GLvoid* getData() const;
        virtual GLsizei getDataSize() const;
        virtual Ionflux::GeoUtils::VertexAttributeDataTypeID getDataType() 
        const;
        virtual GLuint getBufferImpl() const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getElementSize() const;
        virtual void setNormalized(bool newNormalized);
        virtual bool getNormalized() const;
};

}

}


%{
#include "geoutils/Viewer.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ViewerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ViewerClassInfo();
        virtual ~ViewerClassInfo();
};

class Viewer
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const int DEFAULT_WINDOW_POS_X;
		static const int DEFAULT_WINDOW_POS_Y;
		static const int DEFAULT_WINDOW_WIDTH;
		static const int DEFAULT_WINDOW_HEIGHT;
		static const std::string DEFAULT_WINDOW_TITLE;
		static const int DEFAULT_OPENGL_VERSION_MAJOR;
		static const int DEFAULT_OPENGL_VERSION_MINOR;
		static const Ionflux::GeoUtils::OpenGLProfileID DEFAULT_OPENGL_PROFILE;
		static const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_ANY;
		static const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_CORE;
		static const Ionflux::GeoUtils::OpenGLProfileID OPENGL_PROFILE_COMPAT;
		static const Ionflux::Altjira::Color DEFAULT_CLEAR_COLOR;
        
        Viewer();
		Viewer(const Ionflux::GeoUtils::Viewer& other);
        Viewer(int initWindowPosX, int initWindowPosY, int initWindowWidth,
        int initWindowHeight, const std::string& initWindowTitle = 
        DEFAULT_WINDOW_TITLE, const Ionflux::Altjira::Color& initClearColor
        = DEFAULT_CLEAR_COLOR, int initOpenGLVersionMajor = 
        DEFAULT_OPENGL_VERSION_MAJOR, int initOpenGLVersionMinor = 
        DEFAULT_OPENGL_VERSION_MINOR, Ionflux::GeoUtils::OpenGLProfileID 
        initOpenGLProfile = DEFAULT_OPENGL_PROFILE);
        virtual ~Viewer();
        virtual void init();
        virtual void cleanup();
        virtual void shutdown(bool shutdownNow = true);
        virtual void clear();
        virtual void initViewport();
        virtual void swapBuffers();
        virtual void pollEvents();
        virtual void onKey(int key, int scancode, int action, int mods);
        virtual void onWindowSize(int width, int height);
        virtual void onWindowPos(int posX, int posY);
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Viewer* getInstance();
        static void setInstance(Ionflux::GeoUtils::Viewer* viewer);
        static void cleanupInstance();
        static std::string 
        getOpenGLProfileString(Ionflux::GeoUtils::OpenGLProfileID profile);
		virtual Ionflux::GeoUtils::Viewer* copy() const;
		static Ionflux::GeoUtils::Viewer* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Viewer* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Viewer* create(int initWindowPosX, int 
		initWindowPosY, int initWindowWidth, int initWindowHeight, const 
		std::string& initWindowTitle = DEFAULT_WINDOW_TITLE, const 
		Ionflux::Altjira::Color& initClearColor = DEFAULT_CLEAR_COLOR, int 
		initOpenGLVersionMajor = DEFAULT_OPENGL_VERSION_MAJOR, int 
		initOpenGLVersionMinor = DEFAULT_OPENGL_VERSION_MINOR, 
		Ionflux::GeoUtils::OpenGLProfileID initOpenGLProfile = 
		DEFAULT_OPENGL_PROFILE, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setWindowPosX(int newWindowPosX);
        virtual int getWindowPosX() const;
        virtual void setWindowPosY(int newWindowPosY);
        virtual int getWindowPosY() const;
        virtual void setWindowWidth(int newWindowWidth);
        virtual int getWindowWidth() const;
        virtual void setWindowHeight(int newWindowHeight);
        virtual int getWindowHeight() const;
        virtual void setWindowTitle(const std::string& newWindowTitle);
        virtual std::string getWindowTitle() const;
        virtual void setClearColor(const Ionflux::Altjira::Color& 
        newClearColor);
        virtual Ionflux::Altjira::Color getClearColor() const;
        virtual void setOpenGLVersionMajor(int newOpenGLVersionMajor);
        virtual int getOpenGLVersionMajor() const;
        virtual void setOpenGLVersionMinor(int newOpenGLVersionMinor);
        virtual int getOpenGLVersionMinor() const;
        virtual void setOpenGLProfile(Ionflux::GeoUtils::OpenGLProfileID 
        newOpenGLProfile);
        virtual Ionflux::GeoUtils::OpenGLProfileID getOpenGLProfile() 
        const;
        virtual void setShutdownFlag(bool newShutdownFlag);
        virtual bool getShutdownFlag() const;
};

}

}


