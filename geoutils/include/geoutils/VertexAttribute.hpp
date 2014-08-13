#ifndef IONFLUX_GEOUTILS_VERTEXATTRIBUTE
#define IONFLUX_GEOUTILS_VERTEXATTRIBUTE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VertexAttribute.hpp             Vertex attribute (OpenGL) (header).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ifobject/types.hpp"
#include "altjira/ColorSet.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/gltypes.hpp"
#include "geoutils/glconstants.hpp"
#include "geoutils/FaceData.hpp"
#include "geoutils/Mesh.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Vertex3Set;
class VectorSet;
class Mesh;

/// Class information for class VertexAttribute.
class VertexAttributeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		VertexAttributeClassInfo();
		/// Destructor.
		virtual ~VertexAttributeClassInfo();
};

/** Vertex attribute (OpenGL).
 * \ingroup ifvg
 *
 * An OpenGL vertex attribute. This can be used to manage vertex 
 * attributes.
 */
class VertexAttribute
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Data buffer.
		GLvoid* data;
		/// Data buffer size.
		GLsizei dataSize;
		/// Data buffer type.
		Ionflux::GeoUtils::DataTypeID dataType;
		/// Buffer implementation (OpenGL).
		GLuint bufferImpl;
		/// Number of elements.
		unsigned int numElements;
		/// Element size.
		unsigned int elementSize;
		/// Normalized flag.
		bool normalized;
		
		/** Set data buffer.
		 *
		 * Set new value of data buffer.
		 *
		 * \param newData New value of data buffer.
		 */
		virtual void setData(GLvoid* newData);
		
		/** Set data buffer size.
		 *
		 * Set new value of data buffer size.
		 *
		 * \param newDataSize New value of data buffer size.
		 */
		virtual void setDataSize(GLsizei newDataSize);
		
		/** Set data buffer type.
		 *
		 * Set new value of data buffer type.
		 *
		 * \param newDataType New value of data buffer type.
		 */
		virtual void setDataType(Ionflux::GeoUtils::DataTypeID newDataType);
		
		/** Set buffer implementation (OpenGL).
		 *
		 * Set new value of buffer implementation (OpenGL).
		 *
		 * \param newBufferImpl New value of buffer implementation (OpenGL).
		 */
		virtual void setBufferImpl(GLuint newBufferImpl);
		
		/** Set number of elements.
		 *
		 * Set new value of number of elements.
		 *
		 * \param newNumElements New value of number of elements.
		 */
		virtual void setNumElements(unsigned int newNumElements);
		
		/** Set element size.
		 *
		 * Set new value of element size.
		 *
		 * \param newElementSize New value of element size.
		 */
		virtual void setElementSize(unsigned int newElementSize);
		
	public:
		/// Vertex attribute type: undefined.
		static const Ionflux::GeoUtils::VertexAttributeTypeID TYPE_UNDEFINED;
		/// Vertex attribute type: position.
		static const Ionflux::GeoUtils::VertexAttributeTypeID TYPE_POSITION;
		/// Vertex attribute type: data.
		static const Ionflux::GeoUtils::VertexAttributeTypeID TYPE_DATA;
		/// Vertex attribute type: index.
		static const Ionflux::GeoUtils::VertexAttributeTypeID TYPE_INDEX;
		/// Class information instance.
		static const VertexAttributeClassInfo vertexAttributeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new VertexAttribute object.
		 */
		VertexAttribute();
		
		/** Constructor.
		 *
		 * Construct new VertexAttribute object.
		 *
		 * \param other Other object.
		 */
		VertexAttribute(const Ionflux::GeoUtils::VertexAttribute& other);
		
		/** Destructor.
		 *
		 * Destruct VertexAttribute object.
		 */
		virtual ~VertexAttribute();
		
		/** Get buffer target (OpenGL).
		 *
		 * Get the OpenGL buffer target for the current data type.
		 *
		 * \return OpenGL buffer target.
		 */
		virtual GLenum getOpenGLTarget();
		
		/** Allocate buffer.
		 *
		 * Allocate a new data buffer. If the current size of the buffer is 
		 * appropriate to accomodate the specified number of elements of the 
		 * specified size, the data buffer will not be re-allocated, but its 
		 * type will still be set according to the \c newDataType parameter.
		 *
		 * \param newNumElements number of elements.
		 * \param newElementSize element size.
		 * \param newDataType data buffer type.
		 */
		virtual void allocate(unsigned int newNumElements, unsigned int 
		newElementSize, Ionflux::GeoUtils::DataTypeID newDataType = 
		DATA_TYPE_FLOAT);
		
		/** Resize buffer.
		 *
		 * Resize the data buffer. If the current size of the buffer is 
		 * appropriate to accomodate the specified number of elements of the 
		 * specified size, the data buffer will not be resized, but its type 
		 * will still be set according to the \c newDataType parameter.
		 *
		 * \param newNumElements number of elements.
		 * \param newElementSize element size.
		 * \param newDataType data buffer type.
		 */
		virtual void resize(unsigned int newNumElements, unsigned int 
		newElementSize, Ionflux::GeoUtils::DataTypeID newDataType = 
		DATA_TYPE_FLOAT);
		
		/** Append data.
		 *
		 * Append data from the source vertex attribute to the vertex 
		 * attribute. The data type and element size of the two vertex 
		 * attributes must match. If the buffer of the target vertex attribute
		 * is not sufficiently large to accomodate the new data, it will be 
		 * resized.
		 *
		 * \param source vertex attribute.
		 */
		virtual void append(const Ionflux::GeoUtils::VertexAttribute& source);
		
		/** Clean up data.
		 *
		 * Clean up the data buffer.
		 */
		virtual void cleanupData();
		
		/** Clean up.
		 *
		 * Clean up state maintained by the vertex attribute.
		 */
		virtual void cleanup();
		
		/** Initialize.
		 *
		 * Initialize the vertex attribute.
		 */
		virtual void init();
		
		/** Bind.
		 *
		 * Bind the OpenGL buffer.
		 */
		virtual void bind();
		
		/** Update.
		 *
		 * Update the OpenGL buffer with the vertex array data.
		 *
		 * \param usage Buffer usage.
		 */
		virtual void update(Ionflux::GeoUtils::BufferUsageID usage = 
		USAGE_STATIC_DRAW);
		
		/** Enable.
		 *
		 * Enable the OpenGL vertex attribute for the specified index.
		 *
		 * \param index Vertex attribute index.
		 */
		virtual void enable(unsigned int index);
		
		/** Set data.
		 *
		 * Set the data for the vertex attribute.
		 *
		 * \param newData Data.
		 */
		virtual void setData(const Ionflux::GeoUtils::Vertex3Set& newData);
		
		/** Set data.
		 *
		 * Set the data for the vertex attribute. Data will be taken from the 
		 * specified vector set. If \c useNumElements is 0, the number of 
		 * elements to be used will be determined from the number of elements 
		 * of the first vector in the set. If any of the vectors in the set 
		 * have less than this number of elements, remaining elements will be 
		 * set to the default value. Any elements in one of the vectors beyond
		 * the specified number of elements will be ignored.
		 *
		 * \param newData Data.
		 * \param useNumElements Number of vector elements to be used.
		 * \param defaultValue Default value.
		 */
		virtual void setData(const Ionflux::GeoUtils::VectorSet& newData, int 
		useNumElements = 0, float defaultValue = 0.);
		
		/** Set data.
		 *
		 * Set the data for the vertex attribute.
		 *
		 * \param newData Data.
		 */
		virtual void setData(const Ionflux::Altjira::ColorSet& newData);
		
		/** Set data.
		 *
		 * Set the data for the vertex attribute.
		 *
		 * \param newData Data.
		 */
		virtual void setData(const Ionflux::ObjectBase::UIntVector& newData);
		
		/** Set data (mesh).
		 *
		 * Set the data for the vertex attribute from a tri-mesh. \c attrType 
		 * determines what subset of data from the mesh is assigned to the 
		 * vertex attribute. If \c attrType is \c TYPE_DATA, the \c 
		 * faceDataType parameter determines the type of face data that is 
		 * assigned to the vertex attribute. This function creates one vertex 
		 * attribute element per face vertex, i.e. vertices are duplicated for
		 * each face. An exception will be thrown if \c mesh is not a 
		 * tri-mesh.
		 *
		 * \param mesh mesh.
		 * \param attrType vertex attribute type.
		 * \param nFaceType Mesh N-face type.
		 * \param faceDataType face data type.
		 *
		 * \return number of vertex attribute elements that were created.
		 */
		virtual unsigned int setData(const Ionflux::GeoUtils::Mesh& mesh, 
		Ionflux::GeoUtils::VertexAttributeTypeID attrType = TYPE_POSITION, 
		Ionflux::GeoUtils::MeshNFaceTypeID nFaceType = 
		Ionflux::GeoUtils::Mesh::NFACE_TYPE_FACE, 
		Ionflux::GeoUtils::FaceDataTypeID faceDataType = 
		FaceData::TYPE_VERTEX_NORMAL);
		
		/** Get data (float).
		 *
		 * Get the data value with the specified element and component index.
		 *
		 * \param elementIndex Element index.
		 * \param componentIndex Component index.
		 *
		 * \return Data value.
		 */
		virtual float getFloat(unsigned int elementIndex, unsigned int 
		componentIndex = 0);
		
		/** Get data (uint).
		 *
		 * Get the data value with the specified element and component index.
		 *
		 * \param elementIndex Element index.
		 * \param componentIndex Component index.
		 *
		 * \return Data value.
		 */
		virtual unsigned int getUInt(unsigned int elementIndex, unsigned int 
		componentIndex = 0);
		
		/** Set data (float).
		 *
		 * Set the data value with the specified element and component index.
		 *
		 * \param elementIndex Element index.
		 * \param componentIndex Component index.
		 * \param value Value.
		 */
		virtual void setData(unsigned int elementIndex, unsigned int 
		componentIndex, float value);
		
		/** Set data (float).
		 *
		 * Set the data value with the specified element index to the 
		 * specified component values.
		 *
		 * \param elementIndex Element index.
		 * \param v0 Value (0).
		 * \param v1 Value (1).
		 * \param v2 Value (2).
		 * \param v3 Value (3).
		 */
		virtual void setDataComponents(unsigned int elementIndex, float v0, float
		v1, float v2 = 0., float v3 = 0.);
		
		/** Set data (uint).
		 *
		 * Set the data value with the specified element and component index.
		 *
		 * \param elementIndex Element index.
		 * \param componentIndex Component index.
		 * \param value Value.
		 */
		virtual void setData(unsigned int elementIndex, unsigned int 
		componentIndex, unsigned int value);
		
		/** Set data (uint).
		 *
		 * Set the data value with the specified element index to the 
		 * specified component values.
		 *
		 * \param elementIndex Element index.
		 * \param v0 Value (0).
		 * \param v1 Value (1).
		 * \param v2 Value (2).
		 * \param v3 Value (3).
		 */
		virtual void setDataComponents(unsigned int elementIndex, unsigned int 
		v0, unsigned int v1, unsigned int v2 = 0, unsigned int v3 = 0);
		
		/** Draw.
		 *
		 * Draw primitives. If \c drawNumPrimitives is 0, the maximum possible
		 * number of primitives of the specified type will be drawn. 
		 * Otherwise, the specified number of primitives, up to the maximum 
		 * possible, will be drawn. If \c startIndex is not 0, primitives will
		 * be drawn starting from the primitive with index \c startIndex.
		 *
		 * \param primitiveID Primitive ID.
		 * \param drawNumPrimitives Number of primitives to be drawn.
		 * \param startIndex Start index.
		 */
		virtual void draw(Ionflux::GeoUtils::PrimitiveID primitiveID, unsigned 
		int drawNumPrimitives = 0, unsigned int startIndex = 0);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get vertex attribute type string representation.
		 *
		 * Get a string representation for a vertex attribute type ID.
		 *
		 * \param typeID Vertex attribute type ID.
		 *
		 * \return String representation.
		 */
		static std::string 
		getTypeIDString(Ionflux::GeoUtils::VertexAttributeTypeID typeID);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::VertexAttribute& operator=(const 
		Ionflux::GeoUtils::VertexAttribute& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::VertexAttribute* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::VertexAttribute* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::GeoUtils::VertexAttribute* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get data buffer.
		 *
		 * \return Current value of data buffer.
		 */
		virtual GLvoid* getData() const;
		
		/** Get data buffer size.
		 *
		 * \return Current value of data buffer size.
		 */
		virtual GLsizei getDataSize() const;
		
		/** Get data buffer type.
		 *
		 * \return Current value of data buffer type.
		 */
		virtual Ionflux::GeoUtils::DataTypeID getDataType() const;
		
		/** Get buffer implementation (OpenGL).
		 *
		 * \return Current value of buffer implementation (OpenGL).
		 */
		virtual GLuint getBufferImpl() const;
		
		/** Get number of elements.
		 *
		 * \return Current value of number of elements.
		 */
		virtual unsigned int getNumElements() const;
		
		/** Get element size.
		 *
		 * \return Current value of element size.
		 */
		virtual unsigned int getElementSize() const;
		
		/** Get normalized flag.
		 *
		 * \return Current value of normalized flag.
		 */
		virtual bool getNormalized() const;
		
		/** Set normalized flag.
		 *
		 * Set new value of normalized flag.
		 *
		 * \param newNormalized New value of normalized flag.
		 */
		virtual void setNormalized(bool newNormalized);
};

}

}

/** \file VertexAttribute.hpp
 * \brief Vertex attribute (OpenGL) (header).
 */
#endif
