/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Face.i                          Mesh face (interface).
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
#include "geoutils/Face.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VectorSetSet;
class FaceData;
class NFaceSet;

class FaceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        FaceClassInfo();
        virtual ~FaceClassInfo();
};

class Face
: public Ionflux::GeoUtils::NFace
{
    public:
        
        Face();
		Face(const Ionflux::GeoUtils::Face& other);
        Face(const Ionflux::ObjectBase::UIntVector* initVerts, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        Face(unsigned int v0, unsigned int v1, unsigned int v2, unsigned 
        int v3 = Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
        Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
        Ionflux::GeoUtils::FaceData* initUV = 0, 
        Ionflux::GeoUtils::FaceData* initVertexColors = 0);
        virtual ~Face();
        virtual void update();
        virtual void clearTangentSpace();
        virtual void clear();
        virtual void setFaceVertexNormals();
        virtual void setVertexColors(const Ionflux::GeoUtils::Vector4& 
        color);
        virtual Ionflux::GeoUtils::Vector3 getTangent();
        virtual Ionflux::GeoUtils::Vector3 getBinormal();
        virtual Ionflux::GeoUtils::Vector3 getNormal();
        virtual Ionflux::GeoUtils::Matrix3 getTangentBase();
        virtual void makePlanar(double p = 1., double t = 
        Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual bool isBackface(const Ionflux::GeoUtils::Vector3& front);
        virtual void getTris(Ionflux::GeoUtils::FaceVector& target);
        virtual Ionflux::GeoUtils::Face& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Face& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Face& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Face& normalize();
        virtual Ionflux::GeoUtils::Face& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Face& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Face& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Face& duplicate();
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Face* copy() const;
		static Ionflux::GeoUtils::Face* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Face* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Face* create(const 
		Ionflux::ObjectBase::UIntVector* initVerts, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Face* create(unsigned int v0, unsigned int v1, 
		unsigned int v2, unsigned int v3 = 
		Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
};

}

}
