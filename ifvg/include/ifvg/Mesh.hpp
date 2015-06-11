#ifndef IONFLUX_VOLGFX_MESH
#define IONFLUX_VOLGFX_MESH
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Mesh.hpp                        Mesh (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifvg/viewertypes.hpp"
#include "geoutils/Mesh.hpp"
#include <iostream>

// forward declarations for types from the Ionflux Object Base System
namespace Ionflux
{

namespace ObjectBase
{

class IFIOContext;

}

}

namespace Ionflux
{

namespace VolGfx
{

namespace XMLUtils
{

class MeshXMLFactory;

}

/// Class information for class Mesh.
class MeshClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		MeshClassInfo();
		/// Destructor.
		virtual ~MeshClassInfo();
};

/** Mesh.
 * \ingroup ifvg
 *
 * A polygonal mesh.
 */
class Mesh
: public Ionflux::GeoUtils::Mesh
{
	private:
		
	protected:
		
	public:
		/// Class information instance.
		static const MeshClassInfo meshClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		/// Magic syllable (object, ME).
		static const Ionflux::ObjectBase::MagicSyllable MAGIC_SYLLABLE_OBJECT;
		
		/** Constructor.
		 *
		 * Construct new Mesh object.
		 */
		Mesh();
		
		/** Constructor.
		 *
		 * Construct new Mesh object.
		 *
		 * \param other Other object.
		 */
		Mesh(const Ionflux::VolGfx::Mesh& other);
		
		/** Constructor.
		 *
		 * Construct new Mesh object.
		 *
		 * \param initVerts Vertex vector.
		 * \param initFaces Face vector.
		 */
		Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
		Ionflux::GeoUtils::FaceVector* initFaces);
		
		/** Constructor.
		 *
		 * Construct new Mesh object.
		 *
		 * \param initVertexSource Vertex source.
		 * \param initFaces Face vector.
		 */
		Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
		Ionflux::GeoUtils::FaceVector* initFaces);
		
		/** Destructor.
		 *
		 * Destruct Mesh object.
		 */
		virtual ~Mesh();
		
		/** Serialize.
		 *
		 * Serialize the object. This creates a string which contains data 
		 * from which the internal state of the object (as supported 
		 * by serialization) can be restored using deserialize().
		 *
		 * \param target where to store the result
		 *
		 * \return \c true on success, \c false otherwise.
		 *
		 * \sa deserialize()
		 */
		virtual bool serialize(std::string& target) const;
		
		/** Deserialize.
		 *
		 * Initialize the object from a serialized representation of its 
		 * internal state. The serialized representation can be obtained 
		 * using serialize().
		 *
		 * \param source serialized data buffer
		 * \param offset position where to start deserialization
		 *
		 * \return offset of remaining data, or DATA_SIZE_INVALID if an error occured.
		 *
		 * \sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, Ionflux::ObjectBase::DataSize offset = 0);
		
		/** Serialize.
		 *
		 * Serialize the object to a stream.
		 *
		 * \param target target stream
		 * \param addMagicWord add magic word
		 *
		 * \return \c true on success, \c false otherwise.
		 *
		 * \sa deserialize()
		 */
		virtual bool serialize(std::ostream& target, bool addMagicWord = true) const;
		
		/** Deserialize.
		 *
		 * Deserialize the object from a stream.
		 *
		 * \param source source stream
		 * \param offset stream position from where to start deserialization
		 * \param checkMagicWord add magic word
		 *
		 * \return offset of remaining data
		 *
		 * \sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(std::istream& source, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
		
		/** Serialize.
		 *
		 * Serialize the object.
		 *
		 * \param ioCtx I/O context
		 * \param addMagicWord add magic word
		 *
		 * \return \c true on success, \c false otherwise.
		 *
		 * \sa deserialize()
		 */
		virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
		
		/** Deserialize.
		 *
		 * Deserialize the object from a stream.
		 *
		 * \param ioCtx I/O context
		 * \param offset stream position from where to start deserialization
		 * \param checkMagicWord add magic word
		 *
		 * \return offset of remaining data
		 *
		 * \sa serialize()
		 */
		virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
		
		/** Get magic syllable (object).
		 *
		 * Get the magic syllable for the object.
		 *
		 * \return magic syllable
		 */
		virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
		
		/** Get magic syllable (base).
		 *
		 * Get the magic syllable for the namespace.
		 *
		 * \return magic syllable
		 */
		virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::VolGfx::Mesh& operator=(const Ionflux::VolGfx::Mesh& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::Mesh* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::Mesh* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::VolGfx::Mesh* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Mesh object.
		 *
		 * \param initVerts Vertex vector.
		 * \param initFaces Face vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::Mesh* create(Ionflux::GeoUtils::Vertex3Vector* 
		initVerts, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Mesh object.
		 *
		 * \param initVertexSource Vertex source.
		 * \param initFaces Face vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::Mesh* create(Ionflux::GeoUtils::Vertex3Set* 
		initVertexSource, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
        
		/** Get XML element name.
		 *
		 * Get the XML element name for the object.
		 *
		 * \return XML element name
		 */
		virtual std::string getXMLElementName() const;
        
		/** Get XML attribute data.
		 *
		 * Get a string containing the XML attributes of the object.
		 *
		 * \return XML attribute data
		 */
		virtual std::string getXMLAttributeData() const;
        
        /** Get XML child data.
		 *
		 * Get the XML child data for the object.
		 *
		 * \param target Where to store the XML data.
		 * \param indentLevel Indentation level.
		 */
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
        
        /** Load from XML file.
		 *
		 * Initialize the object from an XML file.
		 *
		 * \param fileName file name
		 * \param elementName element name
		 */
		virtual void loadFromXMLFile(const std::string& fileName, const 
		std::string& elementName = "");
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 * 
		 * return XML object factory
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
};

}

}

/** \file Mesh.hpp
 * \brief Mesh (header).
 */
#endif
