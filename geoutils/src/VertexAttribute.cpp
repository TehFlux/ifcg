/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VertexAttribute.cpp             Vertex attribute (OpenGL) 
 * (implementation).
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

#include "geoutils/VertexAttribute.hpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include "ifobject/utils.hpp"
#include "ifobject/objectutils.hpp"
#include "altjira/Color.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/VectorSet.hpp"
#include "geoutils/Vector.hpp"
#include "geoutils/Mesh.hpp"
#include "geoutils/Face.hpp"
#include "geoutils/glutils.hpp"
#include "geoutils/glutils_private.hpp"

using namespace std;

namespace Ionflux
{

namespace GeoUtils
{

VertexAttributeClassInfo::VertexAttributeClassInfo()
{
	name = "VertexAttribute";
	desc = "Vertex attribute (OpenGL)";
	baseClassInfo.push_back(Ionflux::ObjectBase::IFObject::CLASS_INFO);
}

VertexAttributeClassInfo::~VertexAttributeClassInfo()
{
}

// public member constants
const Ionflux::GeoUtils::VertexAttributeTypeID VertexAttribute::TYPE_UNDEFINED = 0;
const Ionflux::GeoUtils::VertexAttributeTypeID VertexAttribute::TYPE_POSITION = 1;
const Ionflux::GeoUtils::VertexAttributeTypeID VertexAttribute::TYPE_DATA = 2;
const Ionflux::GeoUtils::VertexAttributeTypeID VertexAttribute::TYPE_INDEX = 3;

// run-time type information instance constants
const VertexAttributeClassInfo VertexAttribute::vertexAttributeClassInfo;
const Ionflux::ObjectBase::IFClassInfo* VertexAttribute::CLASS_INFO = &VertexAttribute::vertexAttributeClassInfo;

VertexAttribute::VertexAttribute()
: data(0), dataSize(0), dataType(0), bufferImpl(0), numElements(0), elementSize(0), normalized(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

VertexAttribute::VertexAttribute(const Ionflux::GeoUtils::VertexAttribute& other)
: data(0), dataSize(0), dataType(0), bufferImpl(0), numElements(0), elementSize(0), normalized(false)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

VertexAttribute::~VertexAttribute()
{
	cleanup();
}

GLenum VertexAttribute::getOpenGLTarget()
{
	if (dataType == DATA_TYPE_FLOAT)
	    return GL_ARRAY_BUFFER;
	if (dataType == DATA_TYPE_UINT)
	    return GL_ELEMENT_ARRAY_BUFFER;
	std::ostringstream status;
	status << "Invalid vertex attribute data type ID: " << dataType;
	throw GeoUtilsError(getErrorString(status.str(), "getTarget"));
	return 0;
}

void VertexAttribute::cleanupData()
{
	if (data != 0)
	{
	    if (dataType == DATA_TYPE_FLOAT)
	    {
	        GLfloat* d0 = static_cast<GLfloat*>(data);
	        delete[] d0;
	    } else
	    if (dataType == DATA_TYPE_UINT)
	    {
	        GLuint* d0 = static_cast<GLuint*>(data);
	        delete[] d0;
	    } else
	    {
	        std::ostringstream status;
	        status << "Unknown data type (dataType = " 
	            << getDataTypeString(dataType) << ").";
	        throw GeoUtilsError(getErrorString(status.str(), 
	            "cleanupData"));
	    }
	    data = 0;
	    dataSize = 0;
	}
}

void VertexAttribute::cleanup()
{
	if (bufferImpl != 0)
	{
	    glDeleteBuffers(1, &bufferImpl);
	    bufferImpl = 0;
	}
	cleanupData();
}

void VertexAttribute::init()
{
	if (bufferImpl != 0)
	    glDeleteBuffers(1, &bufferImpl);
	glGenBuffers(1, &bufferImpl);
	if (bufferImpl == 0)
	{
	    throw GeoUtilsError(getErrorString(
	        "Could not allocate OpenGL buffer.", "init"));
	}
}

void VertexAttribute::bind()
{
	if (bufferImpl == 0)
	{
	    throw GeoUtilsError(getErrorString(
	        "OpenGL buffer not initialized.", "bind"));
	}
	glBindBuffer(getOpenGLTarget(), bufferImpl);
}

void VertexAttribute::update(Ionflux::GeoUtils::BufferUsageID usage)
{
	if (bufferImpl == 0)
	{
	    throw GeoUtilsError(getErrorString(
	        "OpenGL buffer not initialized.", "update"));
	}
	bind();
	glBufferData(getOpenGLTarget(), dataSize, data, 
	    getOpenGLBufferUsage(usage));
}

void VertexAttribute::enable(unsigned int index)
{
	if (elementSize == 0)
	{
	    throw GeoUtilsError(getErrorString("Element size is zero.", 
	        "enable"));
	}
	GLenum target = getOpenGLTarget();
	if (target != GL_ARRAY_BUFFER)
	{
	    throw GeoUtilsError(getErrorString(
	        "Buffer is not a vertex attribute array.", "enable"));
	}
	if (elementSize == 0)
	{
	    throw GeoUtilsError(getErrorString("Element size is zero.", 
	        "enable"));
	}
	bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, elementSize, 
	    getOpenGLDataType(dataType), normalized, 0, 0);
}

void VertexAttribute::setData(const Ionflux::GeoUtils::Vertex3Set& newData)
{
	unsigned int n0 = newData.getNumVertices();
	if (n0 == 0)
	    return;
	GLsizei n1 = n0 * 3 * sizeof(GLfloat);
	GLfloat* d0 = static_cast<GLfloat*>(data);
	if ((d0 == 0)
	    || (n1 > dataSize))
	{
	    // allocate new buffer
	    cleanupData();
	    d0 = new GLfloat[n0 * 3];
	    dataSize = n1;
	    setData(d0);
	    setDataType(DATA_TYPE_FLOAT);
	}
	Ionflux::ObjectBase::nullPointerCheck(d0, this, 
	    "setData", "Data buffer");
	for (unsigned int i = 0; i < n0; i++)
	{
	    Vertex3* v0 = Ionflux::ObjectBase::nullPointerCheck(
	        newData.getVertex(i), this, "setData", "Vertex");
	    for (int j = 0; j < 3; j++)
	        d0[3 * i + j] = v0->getCoord(j);
	}
	setNumElements(n0);
	setElementSize(3);
}

void VertexAttribute::setData(const Ionflux::GeoUtils::VectorSet& newData, 
int useNumElements, float defaultValue)
{
	unsigned int n0 = newData.getNumVectors();
	if (n0 == 0)
	    return;
	if (useNumElements <= 0)
	{
	    Vector* v0 = Ionflux::ObjectBase::nullPointerCheck(
	        newData.getVector(0), this, "setData", "Vector");
	    useNumElements = v0->getNumElements();
	}
	GLsizei n1 = n0 * useNumElements * sizeof(GLfloat);
	GLfloat* d0 = static_cast<GLfloat*>(data);
	if ((d0 == 0)
	    || (n1 > dataSize))
	{
	    // allocate new buffer
	    cleanupData();
	    d0 = new GLfloat[n0 * useNumElements];
	    dataSize = n1;
	    setData(d0);
	    setDataType(DATA_TYPE_FLOAT);
	}
	for (unsigned int i = 0; i < n0; i++)
	{
	    Vector* v0 = Ionflux::ObjectBase::nullPointerCheck(
	        newData.getVector(i), this, "setData", "Vertex");
	    unsigned int n2 = v0->getNumElements();
	    for (int j = 0; j < useNumElements; j++)
	    {
	        if (static_cast<unsigned int>(j) < n2)
	            d0[useNumElements * i + j] = v0->getElement(j);
	        else
	            d0[useNumElements * i + j] = defaultValue;
	    }
	}
	setNumElements(n0);
	setElementSize(useNumElements);
}

void VertexAttribute::setData(const Ionflux::Altjira::ColorSet& newData)
{
	unsigned int n0 = newData.getNumColors();
	if (n0 == 0)
	    return;
	GLsizei n1 = n0 * 4 * sizeof(GLfloat);
	GLfloat* d0 = static_cast<GLfloat*>(data);
	if ((d0 == 0)
	    || (n1 > dataSize))
	{
	    // allocate new buffer
	    cleanupData();
	    d0 = new GLfloat[n0 * 4];
	    dataSize = n1;
	    setData(d0);
	    setDataType(DATA_TYPE_FLOAT);
	}
	for (unsigned int i = 0; i < n0; i++)
	{
	    Ionflux::Altjira::Color* c0 = 
	        Ionflux::ObjectBase::nullPointerCheck(
	            newData.getColor(i), this, "setData", "Color");
	    d0[4 * i] = c0->getRed();
	    d0[4 * i + 1] = c0->getGreen();
	    d0[4 * i + 2] = c0->getBlue();
	    d0[4 * i + 3] = c0->getAlpha();
	}
	setNumElements(n0);
	setElementSize(4);
}

void VertexAttribute::setData(const Ionflux::ObjectBase::UIntVector& 
newData)
{
	unsigned int n0 = newData.size();
	if (n0 == 0)
	    return;
	GLsizei n1 = n0 * sizeof(GLuint);
	GLuint* d0 = static_cast<GLuint*>(data);
	if ((d0 == 0)
	    || (n1 > dataSize))
	{
	    // allocate new buffer
	    cleanupData();
	    d0 = new GLuint[n0];
	    dataSize = n1;
	    setData(d0);
	    setDataType(DATA_TYPE_UINT);
	}
	for (unsigned int i = 0; i < n0; i++)
	    d0[i] = newData[i];
	setNumElements(n0);
	setElementSize(1);
}

unsigned int VertexAttribute::setData(const Ionflux::GeoUtils::Mesh& mesh, 
Ionflux::GeoUtils::VertexAttributeTypeID attrType, 
Ionflux::GeoUtils::FaceDataTypeID faceDataType)
{
	if (!mesh.isTriMesh())
	{
	    throw GeoUtilsError(getErrorString(
	        "Mesh is not a tri-mesh.", "setData"));
	}
	if ((attrType != TYPE_POSITION) 
	    && (attrType != TYPE_DATA) 
	    && (attrType != TYPE_INDEX))
	{
	    std::ostringstream status;
	    status << "Invalid vertex attribute type: " << attrType;
	    throw GeoUtilsError(getErrorString(
	        status.str(), "setData"));
	}
	unsigned int numFaces = mesh.getNumFaces();
	// <---- DEBUG ----- //
	std::cerr << "[VertexAttribute::setData] DEBUG: "
	    "numFaces = " << numFaces << ", attrType = " 
	    << getTypeIDString(attrType) << ", faceDataType = " 
	    << FaceData::getTypeIDString(faceDataType) << std::endl;
	// ----- DEBUG ----> */
	VectorSet vs0;
	Ionflux::ObjectBase::UIntVector iv0;
	unsigned int numAttr = 0;
	for (unsigned int i = 0; i < numFaces; i++)
	{
	    Face* f0 = mesh.getFace(i);
	    if (f0 != 0)
	    {
	        if (attrType == TYPE_POSITION)
	        {
	            // vertex position
	            for (unsigned int i = 0; i < 3; i++)
	            {
	                Vertex3* v0 = Ionflux::ObjectBase::nullPointerCheck(
	                    mesh.getVertex(f0->getVertex(i)), this, 
	                    "setData", "Vertex");
	                vs0.addVector(v0->getVector().copy());
	            }
	        } else
	        if (attrType == TYPE_DATA)
	        {
	            // vertex data
	            FaceData* fd0 = f0->getFaceDataByType0(faceDataType);
	            if (fd0 == 0)
	            {
	                std::ostringstream status;
	                status << "Face data not set (type = " 
	                    << FaceData::getTypeIDString(faceDataType) 
	                    << "(" << faceDataType << ")" 
	                    << ", face = " << i << ")";
	                throw GeoUtilsError(getErrorString(
	                    status.str(), "setData"));
	            }
	            for (unsigned int i = 0; i < 3; i++)
	            {
	                Vector* v0 = Ionflux::ObjectBase::nullPointerCheck(
	                    fd0->getVector(i), this, "setData", 
	                    "Face data vector");
	                vs0.addVector(v0->copy());
	            }
	        } else
	        if (attrType == TYPE_INDEX)
	        {
	            // vertex indices
	            for (unsigned int i = 0; i < 3; i++)
	                iv0.push_back(f0->getVertex(i));
	        }
	        numAttr += 3;
	    }
	}
	if ((attrType == TYPE_POSITION) 
	    || (attrType == TYPE_DATA))
	    setData(vs0);
	else
	if (attrType == TYPE_INDEX)
	    setData(iv0);
	return numAttr;
}

float VertexAttribute::getFloat(unsigned int elementIndex, unsigned int 
componentIndex)
{
	if (dataType != DATA_TYPE_FLOAT)
	{
	    std::ostringstream status;
	    status << "Data type mismatch (dataType = " 
	        << getDataTypeString(dataType) << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "getFloat"));
	}
	if (elementIndex >= numElements)
	{
	    std::ostringstream status;
	    status << "Element index out of bounds: " << elementIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "getData"));
	}
	if (componentIndex >= elementSize)
	{
	    std::ostringstream status;
	    status << "Component index out of bounds: " << componentIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "getData"));
	}
	GLfloat* d0 = static_cast<GLfloat*>(data);
	return d0[elementIndex * elementSize + componentIndex];
}

unsigned int VertexAttribute::getUInt(unsigned int elementIndex, unsigned 
int componentIndex)
{
	if (dataType != DATA_TYPE_UINT)
	{
	    std::ostringstream status;
	    status << "Data type mismatch (dataType = " 
	        << getDataTypeString(dataType) << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "getFloat"));
	}
	if (elementIndex >= numElements)
	{
	    std::ostringstream status;
	    status << "Element index out of bounds: " << elementIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "getData"));
	}
	if (componentIndex >= elementSize)
	{
	    std::ostringstream status;
	    status << "Component index out of bounds: " << componentIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "getData"));
	}
	GLuint* d0 = static_cast<GLuint*>(data);
	return d0[elementIndex * elementSize + componentIndex];
}

void VertexAttribute::setData(unsigned int elementIndex, unsigned int 
componentIndex, float value)
{
	if (dataType != DATA_TYPE_FLOAT)
	{
	    std::ostringstream status;
	    status << "Data type mismatch (dataType = " 
	        << getDataTypeString(dataType) << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "setData"));
	}
	if (elementIndex >= numElements)
	{
	    std::ostringstream status;
	    status << "Element index out of bounds: " << elementIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "setData"));
	}
	if (componentIndex >= elementSize)
	{
	    std::ostringstream status;
	    status << "Component index out of bounds: " << componentIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "setData"));
	}
	GLfloat* d0 = static_cast<GLfloat*>(data);
	d0[elementIndex * elementSize + componentIndex] = value;
}

void VertexAttribute::setData(unsigned int elementIndex, unsigned int 
componentIndex, unsigned int value)
{
	if (dataType != DATA_TYPE_UINT)
	{
	    std::ostringstream status;
	    status << "Data type mismatch (dataType = " 
	        << getDataTypeString(dataType) << ").";
	    throw GeoUtilsError(getErrorString(status.str(), "setData"));
	}
	if (elementIndex >= numElements)
	{
	    std::ostringstream status;
	    status << "Element index out of bounds: " << elementIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "setData"));
	}
	if (componentIndex >= elementSize)
	{
	    std::ostringstream status;
	    status << "Component index out of bounds: " << componentIndex;
	    throw GeoUtilsError(getErrorString(status.str(), "setData"));
	}
	GLuint* d0 = static_cast<GLuint*>(data);
	d0[elementIndex * elementSize + componentIndex] = value;
}

void VertexAttribute::draw(Ionflux::GeoUtils::PrimitiveID primitiveID, 
unsigned int drawNumPrimitives, unsigned int startIndex)
{
	unsigned int numElementsPerPrimitive = 
	    getNumElementsPerPrimitive(primitiveID);
	unsigned int maxDrawNumPrimitives = numElements 
	    / numElementsPerPrimitive;
	if ((startIndex >= maxDrawNumPrimitives)
	    || (maxDrawNumPrimitives == 0))
	    return;
	if ((drawNumPrimitives == 0) 
	    || ((startIndex + drawNumPrimitives) > maxDrawNumPrimitives))
	    drawNumPrimitives = maxDrawNumPrimitives - startIndex;
	GLenum target = getOpenGLTarget();
	GLenum mode = getOpenGLPrimitive(primitiveID);
	if (target == GL_ARRAY_BUFFER)
	{
	    // draw array elements
	    glDrawArrays(mode, numElementsPerPrimitive * startIndex, 
	        numElementsPerPrimitive * drawNumPrimitives);
	} else
	if (target == GL_ELEMENT_ARRAY_BUFFER)
	{
	    // draw indexed elements
	    bind();
	    glDrawElements(mode, 
	        numElementsPerPrimitive * drawNumPrimitives, 
	        getOpenGLDataType(dataType), 
	        reinterpret_cast<const void*>(
	            numElementsPerPrimitive * startIndex));
	} else
	{
	    throw GeoUtilsError(getErrorString(
	        "Unknown OpenGL buffer target.", "draw"));
	}
}

std::string VertexAttribute::getValueString() const
{
	std::ostringstream status;
	status << "dataType = " << getDataTypeString(dataType) 
	    << ", numElements = " << numElements 
	    << ", elementSize = " << elementSize 
	    << ", normalized = " << normalized;
	return status.str();
}

std::string 
VertexAttribute::getTypeIDString(Ionflux::GeoUtils::VertexAttributeTypeID 
typeID)
{
	if (typeID == TYPE_UNDEFINED)
	    return "undefined";
	else
	if (typeID == TYPE_POSITION)
	    return "position";
	else
	if (typeID == TYPE_DATA)
	    return "data";
	else
	if (typeID == TYPE_INDEX)
	    return "index";
	return "<unknown>";
}

void VertexAttribute::setData(GLvoid* newData)
{
	data = newData;
}

GLvoid* VertexAttribute::getData() const
{
    return data;
}

void VertexAttribute::setDataSize(GLsizei newDataSize)
{
	dataSize = newDataSize;
}

GLsizei VertexAttribute::getDataSize() const
{
    return dataSize;
}

void VertexAttribute::setDataType(Ionflux::GeoUtils::DataTypeID 
newDataType)
{
	dataType = newDataType;
}

Ionflux::GeoUtils::DataTypeID VertexAttribute::getDataType() const
{
    return dataType;
}

void VertexAttribute::setBufferImpl(GLuint newBufferImpl)
{
	bufferImpl = newBufferImpl;
}

GLuint VertexAttribute::getBufferImpl() const
{
    return bufferImpl;
}

void VertexAttribute::setNumElements(unsigned int newNumElements)
{
	numElements = newNumElements;
}

unsigned int VertexAttribute::getNumElements() const
{
    return numElements;
}

void VertexAttribute::setElementSize(unsigned int newElementSize)
{
	elementSize = newElementSize;
}

unsigned int VertexAttribute::getElementSize() const
{
    return elementSize;
}

void VertexAttribute::setNormalized(bool newNormalized)
{
	normalized = newNormalized;
}

bool VertexAttribute::getNormalized() const
{
    return normalized;
}

Ionflux::GeoUtils::VertexAttribute& VertexAttribute::operator=(const 
Ionflux::GeoUtils::VertexAttribute& other)
{
    if (this == &other)
        return *this;
	return *this;
}

Ionflux::GeoUtils::VertexAttribute* VertexAttribute::copy() const
{
    VertexAttribute* newVertexAttribute = create();
    *newVertexAttribute = *this;
    return newVertexAttribute;
}

Ionflux::GeoUtils::VertexAttribute* 
VertexAttribute::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<VertexAttribute*>(other);
}

Ionflux::GeoUtils::VertexAttribute* 
VertexAttribute::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    VertexAttribute* newObject = new VertexAttribute();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

unsigned int VertexAttribute::getMemSize() const
{
    return sizeof *this;
}

}

}

/** \file VertexAttribute.cpp
 * \brief Vertex attribute (OpenGL) implementation.
 */
