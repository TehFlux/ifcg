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
#include "geoutils/geoutilsfbx.hpp"
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

// fbxtypes.hpp

namespace Ionflux
{

namespace GeoUtils
{

class FBXNode;

typedef int FBXNodeAttributeType;

typedef std::vector<Ionflux::GeoUtils::FBXNode*> FBXNodeVector;

}

}

// fbxutils.hpp

namespace Ionflux
{

namespace GeoUtils
{

std::string getFBXNodeAttributeTypeString(
    Ionflux::GeoUtils::FBXNodeAttributeType attrType);

}

}


%{
#include "geoutils/FBXManager.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FBXManagerClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FBXManagerClassInfo();
        virtual ~FBXManagerClassInfo();
};

class FBXManager
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        FBXManager();
		FBXManager(const Ionflux::GeoUtils::FBXManager& other);
        virtual ~FBXManager();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::FBXManager* copy() const;
		static Ionflux::GeoUtils::FBXManager* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::FBXManager* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}


%{
#include "geoutils/FBXScene.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FBXManager;
class FBXNode;

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
        FBXScene(Ionflux::GeoUtils::FBXManager* initFbxManager);
        virtual ~FBXScene();
        virtual bool loadFromFile(const std::string& fileName);
        virtual Ionflux::GeoUtils::FBXNode* getRootNode() const;
        virtual void listNodes(bool recursive = true, unsigned int 
        indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char 
        indentChar = ' ') const;
        virtual Ionflux::GeoUtils::FBXNode* findChildNodeByName(const 
        std::string& needle, bool recursive = true);
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::FBXScene* copy() const;
		static Ionflux::GeoUtils::FBXScene* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::FBXScene* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setFbxManager(Ionflux::GeoUtils::FBXManager* 
        newFbxManager);
        virtual Ionflux::GeoUtils::FBXManager* getFbxManager() const;
        virtual std::string getTitle() const;
        virtual std::string getSubject() const;
        virtual std::string getAuthor() const;
        virtual std::string getKeywords() const;
        virtual std::string getRevision() const;
        virtual std::string getComment() const;
};

}

}


%{
#include "geoutils/FBXNode.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Matrix4;
class Mesh;
class FBXNodeSet;

class FBXNodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FBXNodeClassInfo();
        virtual ~FBXNodeClassInfo();
};

class FBXNode
: public Ionflux::ObjectBase::IFObject
{
    public:
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_UNKNOWN;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NULL;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_MARKER;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SKELETON;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_MESH;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBS;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_PATCH;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERA;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERASTEREO;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CAMERASWITCHER;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LIGHT;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_OPTICALREFERENCE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_OPTICALMARKER;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBSCURVE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_TRIMNURBSSURFACE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_BOUNDARY;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_NURBSSURFACE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SHAPE;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LODGROUP;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_SUBDIV;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_CACHEDEFFECT;
		static const Ionflux::GeoUtils::FBXNodeAttributeType TYPE_LINE;
        
        FBXNode();
		FBXNode(const Ionflux::GeoUtils::FBXNode& other);
        virtual ~FBXNode();
        virtual void update();
        virtual int getNumChildNodesFBX() const;
        virtual Ionflux::GeoUtils::FBXNode* getChildNodeFBX(int index) 
        const;
        virtual void addChildNodesFBX(bool recursive = false);
        virtual void listChildNodesFBX(bool recursive = false, unsigned int
        indentWidth = Ionflux::ObjectBase::DEFAULT_INDENT_WIDTH, char 
        indentChar = ' ', unsigned int depth = 0) const;
        virtual Ionflux::GeoUtils::FBXNode* findChildNodeByNameFBX(const 
        std::string& needle, bool recursive = true);
        virtual unsigned int getMesh(Ionflux::GeoUtils::Mesh& target, bool 
        recursive = false, Ionflux::GeoUtils::Matrix4* localTransform0 = 0,
        bool applyNodeTransform0 = true) const;
        virtual unsigned int dumpMesh(const std::string& targetPath, bool 
        recursive = false, Ionflux::GeoUtils::Matrix4* localTransform0 = 0,
        unsigned int startIndex = 0, double scale0 = 1., bool 
        applyNodeTransform0 = true) const;
        virtual void updateTransformFBX(bool recursive = false, 
        Ionflux::GeoUtils::Matrix4* localTransform0 = 0);
        virtual Ionflux::GeoUtils::Range3* updateBoundsFBX(bool recursive =
        false, Ionflux::GeoUtils::Matrix4* localTransform0 = 0);
        virtual void updateMeshDataFBX(bool recursive = false);
        virtual bool getHierarchyBounds(Ionflux::GeoUtils::Range3& target, 
        bool valid = false);
        virtual unsigned int getHierarchyNumVerts();
        virtual unsigned int getHierarchyNumFaces();
        virtual unsigned int assignNodeIDs(const std::string& prefix = "", 
        unsigned int width = 8, char fillChar = '0', unsigned int offset = 
        0);
        virtual Ionflux::GeoUtils::FBXNode* findNodeByName(const 
        std::string& needle, bool recursive = true);
        virtual Ionflux::GeoUtils::FBXNode* findNodeByID(const std::string&
        needle, bool recursive = true);
        virtual unsigned int 
        findNodesByAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType t,
        Ionflux::GeoUtils::FBXNodeSet& target, bool recursive = true);
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::FBXNode* copy() const;
		static Ionflux::GeoUtils::FBXNode* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::FBXNode* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setLocalTransform(Ionflux::GeoUtils::Matrix4* 
        newLocalTransform);
        virtual Ionflux::GeoUtils::Matrix4* getLocalTransform() const;
        virtual void setGlobalTransform(Ionflux::GeoUtils::Matrix4* 
        newGlobalTransform);
        virtual Ionflux::GeoUtils::Matrix4* getGlobalTransform() const;        
        virtual unsigned int getNumChildNodes() const;
        virtual Ionflux::GeoUtils::FBXNode* getChildNode(unsigned int 
        elementIndex = 0) const;
		virtual int findChildNode(Ionflux::GeoUtils::FBXNode* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::FBXNode*>& getChildNodes();
        virtual void addChildNode(Ionflux::GeoUtils::FBXNode* addElement);
		virtual Ionflux::GeoUtils::FBXNode* addChildNode();
		virtual void addChildNodes(std::vector<Ionflux::GeoUtils::FBXNode*>& 
		newChildNodes);
		virtual void addChildNodes(Ionflux::GeoUtils::FBXNode* newChildNodes);        
        virtual void removeChildNode(Ionflux::GeoUtils::FBXNode* 
        removeElement);
		virtual void removeChildNodeIndex(unsigned int removeIndex);
		virtual void clearChildNodes();
        virtual void 
        setAttributeType(Ionflux::GeoUtils::FBXNodeAttributeType 
        newAttributeType);
        virtual Ionflux::GeoUtils::FBXNodeAttributeType getAttributeType() 
        const;
        virtual void setName(const std::string& newName);
        virtual std::string getName() const;
        virtual void setBounds(Ionflux::GeoUtils::Range3* newBounds);
        virtual Ionflux::GeoUtils::Range3* getBounds() const;
        virtual void setNumVerts(unsigned int newNumVerts);
        virtual unsigned int getNumVerts() const;
        virtual void setNumFaces(unsigned int newNumFaces);
        virtual unsigned int getNumFaces() const;
};

}

}


%{
#include "geoutils/FBXNodeSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class FBXNode;

class FBXNodeSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FBXNodeSetClassInfo();
        virtual ~FBXNodeSetClassInfo();
};

class FBXNodeSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        FBXNodeSet();
		FBXNodeSet(const Ionflux::GeoUtils::FBXNodeSet& other);
        FBXNodeSet(Ionflux::GeoUtils::FBXNodeVector& initNodes);
        virtual ~FBXNodeSet();
		virtual Ionflux::GeoUtils::FBXNodeSet* copy() const;
		static Ionflux::GeoUtils::FBXNodeSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::FBXNodeSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::FBXNodeSet* 
		create(Ionflux::GeoUtils::FBXNodeVector& initNodes, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumNodes() const;
        virtual Ionflux::GeoUtils::FBXNode* getNode(unsigned int 
        elementIndex = 0) const;
		virtual int findNode(Ionflux::GeoUtils::FBXNode* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::FBXNode*>& getNodes();
        virtual void addNode(Ionflux::GeoUtils::FBXNode* addElement);
		virtual Ionflux::GeoUtils::FBXNode* addNode();
		virtual void addNodes(std::vector<Ionflux::GeoUtils::FBXNode*>& 
		newNodes);
		virtual void addNodes(Ionflux::GeoUtils::FBXNodeSet* newNodes);        
        virtual void removeNode(Ionflux::GeoUtils::FBXNode* removeElement);
		virtual void removeNodeIndex(unsigned int removeIndex);
		virtual void clearNodes();
};

}

}


%{
#include "geoutils/xmlio/FBXNodeXMLFactory.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class FBXNodeXMLFactoryClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FBXNodeXMLFactoryClassInfo();
        virtual ~FBXNodeXMLFactoryClassInfo();
};

class FBXNodeXMLFactory
: public Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory
{
    public:
        
        FBXNodeXMLFactory();
		FBXNodeXMLFactory(const Ionflux::GeoUtils::XMLUtils::FBXNodeXMLFactory& other);
        virtual ~FBXNodeXMLFactory();
        virtual std::string getObjectXMLElementName() const;
        virtual std::string getObjectClassName() const;
        virtual void initObject(const std::string& data, 
        Ionflux::GeoUtils::FBXNode& target, const std::string& elementName 
        = "") const;
        virtual Ionflux::GeoUtils::FBXNode* createObject() const;
        virtual Ionflux::GeoUtils::FBXNode* createObject(const std::string&
        data, const std::string& elementName = "") const;
        virtual Ionflux::GeoUtils::FBXNode* loadFromXMLFile(const 
        std::string& fileName, const std::string& elementName = "") const;
		virtual Ionflux::GeoUtils::XMLUtils::FBXNodeXMLFactory* copy() const;
		static Ionflux::GeoUtils::XMLUtils::FBXNodeXMLFactory* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::XMLUtils::FBXNodeXMLFactory* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
};

}

}

}


%template(FBXNodeVector) std::vector<Ionflux::GeoUtils::FBXNode*>;
