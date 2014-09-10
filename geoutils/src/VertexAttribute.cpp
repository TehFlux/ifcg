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

void VertexAttribute::allocate(unsigned int newNumElements, unsigned int 
newElementSize, Ionflux::GeoUtils::DataTypeID newDataType)
{
	if ((newNumElements == 0) 
	    || (newElementSize == 0))
	{
	    std::ostringstream status;
	    status << "Number of elements or element size to be allocated is "
	        "zero (numElements = " << newNumElements << ", elementSize = " 
	        << newElementSize << ")";
	    throw GeoUtilsError(getErrorString(status.str(), "allocate"));
	}
	GLsizei n1 = 0;
	if (newDataType == DATA_TYPE_FLOAT)
	{
	    // float buffer
	    n1 = newNumElements * newElementSize * sizeof(GLfloat);
	    GLfloat* d0 = static_cast<GLfloat*>(data);
	    if ((d0 == 0)
	        || (n1 > dataSize))
	    {
	        // allocate new buffer
	        cleanupData();
	        d0 = new GLfloat[newNumElements * newElementSize];
	        Ionflux::ObjectBase::nullPointerCheck(d0, this, "allocate", 
	            "Data buffer");
	        setData(d0);
	    }
	} else
	if (newDataType == DATA_TYPE_UINT)
	{
	    // unsigned integer buffer
	    n1 = newNumElements * newElementSize * sizeof(GLuint);
	    GLuint* d0 = static_cast<GLuint*>(data);
	    if ((d0 == 0)
	        || (n1 > dataSize))
	    {
	        // allocate new buffer
	        cleanupData();
	        d0 = new GLuint[newNumElements * newElementSize];
	        Ionflux::ObjectBase::nullPointerCheck(d0, this, "allocate", 
	            "Data buffer");
	        setData(d0);
	    }
	} else
	{
	    std::ostringstream status;
	    status << "Unsupported buffer data type: " 
	        << getDataTypeString(newDataType) << " (" << newDataType 
	        << ")";
	    throw GeoUtilsError(getErrorString(status.str(), "allocate"));
	}
	Ionflux::ObjectBase::nullPointerCheck(data, this, 
	    "allocate", "Data buffer");
	setDataSize(n1);
	setDataType(newDataType);
	setNumElements(newNumElements);
	setElementSize(newElementSize);
}

void VertexAttribute::resize(unsigned int newNumElements, unsigned int 
newElementSize, Ionflux::GeoUtils::DataTypeID newDataType, double 
resizeExponent)
{
	if (data == 0)
	{
	    allocate(newNumElements, newElementSize, newDataType);
	    return;
	}
	GLsizei n1 = 0;
	unsigned int ne0 = newNumElements;
	unsigned int ne1 = numElements;
	unsigned int es1 = elementSize;
	if (resizeExponent >= 2.)
	{
	    ne0 = numElements;
	    if (ne0 == 0)
	    {
	        throw GeoUtilsError(getErrorString(
	            "Current number of elements is zero.", "resize"));
	    }
	    while (ne0 < newNumElements)
	        ne0 = static_cast<unsigned int>(resizeExponent * ne0);
	}
	if (newDataType == DATA_TYPE_FLOAT)
	{
	    // float buffer
	    n1 = newNumElements * newElementSize * sizeof(GLfloat);
	    GLfloat* d0 = static_cast<GLfloat*>(data);
	    Ionflux::ObjectBase::nullPointerCheck(d0, this, "resize", 
	        "Data buffer");
	    if (n1 > dataSize)
	    {
	        /* <---- DEBUG ----- //
	        std::cerr << "[VertexAttribute::resize] DEBUG: "
	            "Resizing buffer (ne0 = " << ne0 
	            << ", exponent = " << resizeExponent 
	            << ", n1 = " << n1 
	            << ", dataSize = " << dataSize 
	            << ", numElements = " << ne1 
	            << ", elementSize = " << es1 
	            << ", newNumElements = " << newNumElements 
	            << ", newElementSize = " << newElementSize 
	            << ", type = " << getDataTypeString(newDataType) << ")." 
	            << std::endl;
	        // ----- DEBUG ----> */
	        // copy data to temporary buffer
	        GLfloat* d1 = new GLfloat[ne1 * es1];
	        Ionflux::ObjectBase::nullPointerCheck(d1, this, "resize", 
	            "Temporary data buffer");
	        for (unsigned int i = 0; i < ne1; i++)
	        {
	            for (unsigned int k = 0; k < es1; k++)
	                d1[i * es1 + k] = d0[i * es1 + k];
	        }
	        // allocate new buffer
	        allocate(ne0, newElementSize, newDataType);
	        // copy data back from temporary buffer
	        d0 = static_cast<GLfloat*>(data);
	        for (unsigned int i = 0; i < ne1; i++)
	        {
	            for (unsigned int k = 0; k < es1; k++)
	                d0[i * es1 + k] = d1[i * es1 + k];
	        }
	        delete[] d1;
	    }
	} else
	if (newDataType == DATA_TYPE_UINT)
	{
	    // unsigned integer buffer
	    n1 = newNumElements * newElementSize * sizeof(GLuint);
	    GLuint* d0 = static_cast<GLuint*>(data);
	    if (n1 > dataSize)
	    {
	        /* <---- DEBUG ----- //
	        std::cerr << "[VertexAttribute::resize] DEBUG: "
	            "Resizing buffer (ne0 = " << ne0 
	            << ", exponent = " << resizeExponent 
	            << ", n1 = " << n1 
	            << ", dataSize = " << dataSize 
	            << ", numElements = " << ne1 
	            << ", elementSize = " << es1 
	            << ", newNumElements = " << newNumElements 
	            << ", newElementSize = " << newElementSize 
	            << ", type = " << getDataTypeString(newDataType) << ")." 
	            << std::endl;
	        // ----- DEBUG ----> */
	        // copy data to temporary buffer
	        GLuint* d1 = new GLuint[ne1 * es1];
	        for (unsigned int i = 0; i < ne1; i++)
	        {
	            for (unsigned int k = 0; k < es1; k++)
	                d1[i * es1 + k] = d0[i * es1 + k];
	        }
	        // allocate new buffer
	        allocate(ne0, newElementSize, newDataType);
	        // copy data back from temporary buffer
	        d0 = static_cast<GLuint*>(data);
	        for (unsigned int i = 0; i < ne1; i++)
	        {
	            for (unsigned int k = 0; k < es1; k++)
	                d0[i * es1 + k] = d1[i * es1 + k];
	        }
	        delete[] d1;
	    }
	} else
	{
	    std::ostringstream status;
	    status << "Unsupported buffer data type: " 
	        << getDataTypeString(newDataType) << " (" << newDataType 
	        << ")";
	    throw GeoUtilsError(getErrorString(status.str(), "resize"));
	}
	setDataType(newDataType);
	setNumElements(newNumElements);
	setElementSize(newElementSize);
}

void VertexAttribute::append(const Ionflux::GeoUtils::VertexAttribute& 
source)
{
	DataTypeID t0 = source.getDataType();
	if (t0 != dataType)
	{
	    std::ostringstream status;
	    status << "Buffer data type mismatch (source: " 
	        << getDataTypeString(t0) << ", target: " << dataType << ")";
	    throw GeoUtilsError(getErrorString(status.str(), "append"));
	}
	unsigned int es0 = source.getElementSize();
	if (es0 != elementSize)
	{
	    std::ostringstream status;
	    status << "Element size type mismatch (source: " 
	        << es0 << ", target: " << elementSize << ")";
	    throw GeoUtilsError(getErrorString(status.str(), "append"));
	}
	unsigned int ne0 = source.getNumElements();
	resize(ne0 + numElements, elementSize, dataType);
	if (dataType == DATA_TYPE_FLOAT)
	{
	    GLfloat* d0 = static_cast<GLfloat*>(data);
	    GLfloat* d1 = static_cast<GLfloat*>(source.data);
	    for (unsigned int i = 0; i < ne0; i++)
	    {
	        for (unsigned int k = 0; k < elementSize; k++)
	        {
	            d0[(i + numElements) * elementSize + k] = 
	                d1[i * elementSize + k];
	        }
	    }
	} else
	if (dataType == DATA_TYPE_UINT)
	{
	    GLuint* d0 = static_cast<GLuint*>(data);
	    GLuint* d1 = static_cast<GLuint*>(source.data);
	    for (unsigned int i = 0; i < ne0; i++)
	    {
	        for (unsigned int k = 0; k < elementSize; k++)
	        {
	            d0[(i + numElements) * elementSize + k] = 
	                d1[i * elementSize + k];
	        }
	    }
	}
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
	    numElements = 0;
	    elementSize = 0;
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
	allocate(n0, 3, DATA_TYPE_FLOAT);
	GLfloat* d0 = static_cast<GLfloat*>(data);
	for (unsigned int i = 0; i < n0; i++)
	{
	    Vertex3* v0 = Ionflux::ObjectBase::nullPointerCheck(
	        newData.getVertex(i), this, "setData", "Vertex");
	    for (int j = 0; j < 3; j++)
	        d0[3 * i + j] = v0->getCoord(j);
	}
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
	allocate(n0, useNumElements, DATA_TYPE_FLOAT);
	GLfloat* d0 = static_cast<GLfloat*>(data);
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
}

void VertexAttribute::setData(const Ionflux::Altjira::ColorSet& newData)
{
	unsigned int n0 = newData.getNumColors();
	if (n0 == 0)
	    return;
	allocate(n0, 4, DATA_TYPE_FLOAT);
	GLfloat* d0 = static_cast<GLfloat*>(data);
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
}

void VertexAttribute::setData(const Ionflux::ObjectBase::UIntVector& 
newData)
{
	unsigned int n0 = newData.size();
	if (n0 == 0)
	    return;
	allocate(n0, 1, DATA_TYPE_UINT);
	GLuint* d0 = static_cast<GLuint*>(data);
	for (unsigned int i = 0; i < n0; i++)
	    d0[i] = newData[i];
	setNumElements(n0);
	setElementSize(1);
}

unsigned int VertexAttribute::setData(const Ionflux::GeoUtils::Mesh& mesh, 
Ionflux::GeoUtils::VertexAttributeTypeID attrType, 
Ionflux::GeoUtils::NFaceTypeID nFaceType, Ionflux::GeoUtils::FaceDataTypeID
faceDataType)
{
	if ((nFaceType == Ionflux::GeoUtils::NFace::TYPE_FACE) 
	    && !mesh.isTriMesh())
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
	unsigned int numNFaces = mesh.getNumNFaces(nFaceType);
	// <---- DEBUG ----- //
	std::cerr << "[VertexAttribute::setData] DEBUG: "
	    "numNFaces = " << numNFaces 
	    << ", attrType = " << getTypeIDString(attrType) 
	    << ", nFaceType = " 
	        << Ionflux::GeoUtils::NFace::getNFaceTypeIDString(nFaceType)
	    << ", faceDataType = " << FaceData::getTypeIDString(faceDataType) 
	    << std::endl;
	// ----- DEBUG ----> */
	VectorSet vs0;
	Ionflux::ObjectBase::UIntVector iv0;
	unsigned int numAttr = 0;
	unsigned int nv0 = 0;
	for (unsigned int i = 0; i < numNFaces; i++)
	{
	    NFace* f0 = mesh.getNFace(nFaceType, i);
	    if (f0 != 0)
	    {
	        if (i == 0)
	            nv0 = f0->getNumVertices();
	        else
	        {
	            unsigned int nv1 = f0->getNumVertices();
	            if (nv0 != nv1)
	            {
	                std::ostringstream status;
	                status << "Inconsistent vertex count (type = " 
	                    << Ionflux::GeoUtils::NFace::getNFaceTypeIDString(
	                        nFaceType) << ", N-face = " << i << ", nv0 = " 
	                    << nv0 << ", nv1 = " << nv1 << ")";
	                throw GeoUtilsError(getErrorString(
	                    status.str(), "setData"));
	            }
	        }
	        if (attrType == TYPE_POSITION)
	        {
	            // vertex position
	            for (unsigned int i = 0; i < nv0; i++)
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
	                status << "N-face data not set (type = " 
	                    << FaceData::getTypeIDString(faceDataType) 
	                    << "(" << faceDataType << ")" 
	                    << ", face = " << i << ")";
	                throw GeoUtilsError(getErrorString(
	                    status.str(), "setData"));
	            }
	            for (unsigned int i = 0; i < nv0; i++)
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
	            for (unsigned int i = 0; i < nv0; i++)
	                iv0.push_back(f0->getVertex(i));
	        }
	        numAttr += nv0;
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

void VertexAttribute::setDataComponents(unsigned int elementIndex, float 
v0, float v1, float v2, float v3)
{
	if (elementSize > 0)
	    setData(elementIndex, 0, v0);
	if (elementSize > 1)
	    setData(elementIndex, 1, v1);
	if (elementSize > 2)
	    setData(elementIndex, 2, v2);
	if (elementSize > 3)
	    setData(elementIndex, 3, v3);
}

void VertexAttribute::setData(unsigned int elementIndex, const 
Ionflux::GeoUtils::Vector& value)
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
	GLfloat* d0 = static_cast<GLfloat*>(data);
	unsigned int ne0 = value.getNumElements();
	for (unsigned int i = 0; i < elementSize; i++)
	{
	    if (i < ne0)
	        d0[elementIndex * elementSize + i] = value[i];
	    else
	        d0[elementIndex * elementSize + i] = 0.;
	}
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

void VertexAttribute::setDataComponents(unsigned int elementIndex, unsigned
int v0, unsigned int v1, unsigned int v2, unsigned int v3)
{
	if (elementSize > 0)
	    setData(elementIndex, 0, v0);
	if (elementSize > 1)
	    setData(elementIndex, 1, v1);
	if (elementSize > 2)
	    setData(elementIndex, 2, v2);
	if (elementSize > 3)
	    setData(elementIndex, 3, v3);
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
