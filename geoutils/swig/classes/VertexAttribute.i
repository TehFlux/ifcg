/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VertexAttribute.i               Vertex attribute (OpenGL) (interface).
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
        virtual void allocate(unsigned int newNumElements, unsigned int 
        newElementSize, Ionflux::GeoUtils::DataTypeID newDataType = 
        DATA_TYPE_FLOAT);
        virtual void resize(unsigned int newNumElements, unsigned int 
        newElementSize, Ionflux::GeoUtils::DataTypeID newDataType = 
        DATA_TYPE_FLOAT, double resizeExponent = 0.);
        virtual void append(const Ionflux::GeoUtils::VertexAttribute& 
        source);
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
        Ionflux::GeoUtils::MeshNFaceTypeID nFaceType = 
        Ionflux::GeoUtils::Mesh::NFACE_TYPE_FACE, 
        Ionflux::GeoUtils::FaceDataTypeID faceDataType = 
        FaceData::TYPE_VERTEX_NORMAL);
        virtual float getFloat(unsigned int elementIndex, unsigned int 
        componentIndex = 0);
        virtual unsigned int getUInt(unsigned int elementIndex, unsigned 
        int componentIndex = 0);
        virtual void setData(unsigned int elementIndex, unsigned int 
        componentIndex, float value);
        virtual void setDataComponents(unsigned int elementIndex, float v0,
        float v1, float v2 = 0., float v3 = 0.);
        virtual void setData(unsigned int elementIndex, const 
        Ionflux::GeoUtils::Vector& value);
        virtual void setData(unsigned int elementIndex, unsigned int 
        componentIndex, unsigned int value);
        virtual void setDataComponents(unsigned int elementIndex, unsigned 
        int v0, unsigned int v1, unsigned int v2 = 0, unsigned int v3 = 0);
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
