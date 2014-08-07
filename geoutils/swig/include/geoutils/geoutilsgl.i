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
void enableOpenGLDepthBufferTest(bool enable = true);

}

}

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
class VectorSet;

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
        virtual void setUniform(const std::string& name, const 
        Ionflux::GeoUtils::VectorSet& value);
        virtual void setUniform(const std::string& name, const 
        Ionflux::Altjira::ColorSet& value);
        virtual std::string getValueString() const;
        static unsigned int getOpenGLMaxVertexUniformComponents();
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
class Mesh;

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
		static const Ionflux::GeoUtils::VertexAttributeTypeID TYPE_UNDEFINED;
		static const Ionflux::GeoUtils::VertexAttributeTypeID TYPE_POSITION;
		static const Ionflux::GeoUtils::VertexAttributeTypeID TYPE_DATA;
		static const Ionflux::GeoUtils::VertexAttributeTypeID TYPE_INDEX;
        
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
        virtual unsigned int setData(const Ionflux::GeoUtils::Mesh& mesh, 
        Ionflux::GeoUtils::VertexAttributeTypeID attrType = TYPE_POSITION, 
        Ionflux::GeoUtils::FaceDataTypeID faceDataType = 
        FaceData::TYPE_VERTEX_NORMAL);
        virtual float getFloat(unsigned int elementIndex, unsigned int 
        componentIndex = 0);
        virtual unsigned int getUInt(unsigned int elementIndex, unsigned 
        int componentIndex = 0);
        virtual void setData(unsigned int elementIndex, unsigned int 
        componentIndex, float value);
        virtual void setData(unsigned int elementIndex, unsigned int 
        componentIndex, unsigned int value);
        virtual void draw(Ionflux::GeoUtils::PrimitiveID primitiveID, 
        unsigned int drawNumPrimitives = 0, unsigned int startIndex = 0);
        virtual std::string getValueString() const;
        static std::string 
        getTypeIDString(Ionflux::GeoUtils::VertexAttributeTypeID typeID);
		virtual Ionflux::GeoUtils::VertexAttribute* copy() const;
		static Ionflux::GeoUtils::VertexAttribute* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::VertexAttribute* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual GLvoid* getData() const;
        virtual GLsizei getDataSize() const;
        virtual Ionflux::GeoUtils::DataTypeID getDataType() const;
        virtual GLuint getBufferImpl() const;
        virtual unsigned int getNumElements() const;
        virtual unsigned int getElementSize() const;
        virtual void setNormalized(bool newNormalized);
        virtual bool getNormalized() const;
};

}

}


%{
#include "geoutils/VertexArrayObject.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VertexAttribute;

class VertexArrayObjectClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VertexArrayObjectClassInfo();
        virtual ~VertexArrayObjectClassInfo();
};

class VertexArrayObject
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        VertexArrayObject();
		VertexArrayObject(const Ionflux::GeoUtils::VertexArrayObject& other);
        virtual ~VertexArrayObject();
        virtual void cleanup();
        virtual void init();
        virtual void bind();
        virtual void update();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::VertexArrayObject* copy() const;
		static Ionflux::GeoUtils::VertexArrayObject* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::VertexArrayObject* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual GLuint getVaoImpl() const;        
        virtual unsigned int getNumAttributes() const;
        virtual Ionflux::GeoUtils::VertexAttribute* getAttribute(unsigned 
        int elementIndex = 0) const;
		virtual int findAttribute(Ionflux::GeoUtils::VertexAttribute* needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::VertexAttribute*>& 
        getAttributes();
        virtual void addAttribute(Ionflux::GeoUtils::VertexAttribute* 
        addElement);
		virtual Ionflux::GeoUtils::VertexAttribute* addAttribute();
		virtual void 
		addAttributes(std::vector<Ionflux::GeoUtils::VertexAttribute*>& 
		newAttributes);
		virtual void addAttributes(Ionflux::GeoUtils::VertexArrayObject* 
		newAttributes);        
        virtual void removeAttribute(Ionflux::GeoUtils::VertexAttribute* 
        removeElement);
		virtual void removeAttributeIndex(unsigned int removeIndex);
		virtual void clearAttributes();
};

}

}


%{
#include "geoutils/ViewerEvent.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Viewer;

class ViewerEventClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ViewerEventClassInfo();
        virtual ~ViewerEventClassInfo();
};

class ViewerEvent
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_NONE;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_KEY;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_WINDOW_SIZE;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_WINDOW_POS;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_WINDOW_CLOSE;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_CURSOR_POS;
		static const Ionflux::GeoUtils::ViewerEventTypeID TYPE_MOUSE_BUTTON;
        
        ViewerEvent();
		ViewerEvent(const Ionflux::GeoUtils::ViewerEvent& other);
        ViewerEvent(Ionflux::GeoUtils::Viewer* initViewer, 
        Ionflux::GeoUtils::ViewerEventTypeID initEventType = TYPE_NONE, int
        initKeyCode = 0, int initScanCode = 0, int initAction = 0, int 
        initKeyMods = 0, double initPosX = 0, double initPosY = 0, int 
        initMouseButton = 0);
        virtual ~ViewerEvent();
        virtual std::string getValueString() const;
        static std::string 
        getTypeString(Ionflux::GeoUtils::ViewerEventTypeID eventType);
		virtual Ionflux::GeoUtils::ViewerEvent* copy() const;
		static Ionflux::GeoUtils::ViewerEvent* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ViewerEvent* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::ViewerEvent* create(Ionflux::GeoUtils::Viewer* 
		initViewer, Ionflux::GeoUtils::ViewerEventTypeID initEventType = 
		TYPE_NONE, int initKeyCode = 0, int initScanCode = 0, int initAction = 0,
		int initKeyMods = 0, double initPosX = 0, double initPosY = 0, int 
		initMouseButton = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setViewer(Ionflux::GeoUtils::Viewer* newViewer);
        virtual Ionflux::GeoUtils::Viewer* getViewer() const;
        virtual void setEventType(Ionflux::GeoUtils::ViewerEventTypeID 
        newEventType);
        virtual Ionflux::GeoUtils::ViewerEventTypeID getEventType() const;
        virtual void setKeyCode(int newKeyCode);
        virtual int getKeyCode() const;
        virtual void setScanCode(int newScanCode);
        virtual int getScanCode() const;
        virtual void setAction(int newAction);
        virtual int getAction() const;
        virtual void setKeyMods(int newKeyMods);
        virtual int getKeyMods() const;
        virtual void setPosX(double newPosX);
        virtual double getPosX() const;
        virtual void setPosY(double newPosY);
        virtual double getPosY() const;
        virtual void setMouseButton(int newMouseButton);
        virtual int getMouseButton() const;
};

}

}


%{
#include "geoutils/ViewerEventSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class ViewerEvent;

class ViewerEventSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ViewerEventSetClassInfo();
        virtual ~ViewerEventSetClassInfo();
};

class ViewerEventSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        ViewerEventSet();
		ViewerEventSet(const Ionflux::GeoUtils::ViewerEventSet& other);
        virtual ~ViewerEventSet();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::ViewerEventSet* copy() const;
		static Ionflux::GeoUtils::ViewerEventSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::ViewerEventSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumEvents() const;
        virtual Ionflux::GeoUtils::ViewerEvent* getEvent(unsigned int 
        elementIndex = 0) const;
		virtual int findEvent(Ionflux::GeoUtils::ViewerEvent* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::ViewerEvent*>& getEvents();
        virtual void addEvent(Ionflux::GeoUtils::ViewerEvent* addElement);
		virtual Ionflux::GeoUtils::ViewerEvent* addEvent();
		virtual void addEvents(std::vector<Ionflux::GeoUtils::ViewerEvent*>& 
		newEvents);
		virtual void addEvents(Ionflux::GeoUtils::ViewerEventSet* newEvents);        
        virtual void removeEvent(Ionflux::GeoUtils::ViewerEvent* 
        removeElement);
		virtual void removeEventIndex(unsigned int removeIndex);
		virtual void clearEvents();
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

class ViewerEventSet;

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
        virtual void closeWindow(bool closeFlag = true);
        virtual void initViewport();
        virtual void swapBuffers();
        virtual void pollEvents();
        virtual void onKey(int key, int scancode, int action, int mods);
        virtual void onWindowSize(int width, int height);
        virtual void onWindowPos(int posX, int posY);
        virtual void onWindowClose();
        virtual void onCursorPos(double posX, double posY);
        virtual void onMouseButton(int mouseButton, int action, int mods);
        virtual std::string getValueString() const;
        static Ionflux::GeoUtils::Viewer* getInstance();
        static void setInstance(Ionflux::GeoUtils::Viewer* viewer);
        static void cleanupInstance();
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
        virtual void setEvents(Ionflux::GeoUtils::ViewerEventSet* 
        newEvents);
        virtual Ionflux::GeoUtils::ViewerEventSet* getEvents() const;
};

}

}


// Templates

%template(VertexAttributeVector) std::vector<Ionflux::GeoUtils::VertexAttribute*>;
%template(ViewerEventVector) std::vector<Ionflux::GeoUtils::ViewerEvent*>;

