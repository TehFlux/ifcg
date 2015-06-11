/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Mesh.i                          Mesh (interface).
 * ========================================================================== */
%{
#include "ifvg/Mesh.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class MeshClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        MeshClassInfo();
        virtual ~MeshClassInfo();
};

class Mesh
: public Ionflux::GeoUtils::Mesh
{
    public:
        
        Mesh();
		Mesh(const Ionflux::VolGfx::Mesh& other);
        Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
        Ionflux::GeoUtils::FaceVector* initFaces);
        virtual ~Mesh();
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::VolGfx::Mesh* copy() const;
		static Ionflux::VolGfx::Mesh* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::Mesh* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::VolGfx::Mesh* create(Ionflux::GeoUtils::Vertex3Vector* 
		initVerts, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::VolGfx::Mesh* create(Ionflux::GeoUtils::Vertex3Set* 
		initVertexSource, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual bool serialize(std::string& target) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, int offset = 0);
        virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;
};

}

}
