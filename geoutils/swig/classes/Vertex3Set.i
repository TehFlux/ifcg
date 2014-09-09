/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex3Set.i                    Vertex set (3D) (interface).
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
#include "geoutils/Vertex3Set.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Vertex3;

class Vertex3SetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Vertex3SetClassInfo();
        virtual ~Vertex3SetClassInfo();
};

class Vertex3Set
: public Ionflux::GeoUtils::TransformableObject
{
    public:
        
        Vertex3Set();
		Vertex3Set(const Ionflux::GeoUtils::Vertex3Set& other);
        Vertex3Set(Ionflux::GeoUtils::Vertex3Vector& initVertices);
        virtual ~Vertex3Set();
        virtual void addPoints(Ionflux::Mapping::PointSet& points);
        virtual Ionflux::GeoUtils::Vector3 getBarycenter();
        virtual void applyTransform(bool recursive = false);
        virtual Ionflux::GeoUtils::Vertex3Set& scale(const 
        Ionflux::GeoUtils::Vector3& s);
        virtual Ionflux::GeoUtils::Vertex3Set& translate(const 
        Ionflux::GeoUtils::Vector3& t);
        virtual Ionflux::GeoUtils::Vertex3Set& rotate(double phi, 
        Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
        virtual Ionflux::GeoUtils::Vertex3Set& normalize();
        virtual Ionflux::GeoUtils::Vertex3Set& 
        center(Ionflux::GeoUtils::CenteringMethod method = 
        Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* 
        origin = 0);
        virtual Ionflux::GeoUtils::Vertex3Set& transform(const 
        Ionflux::GeoUtils::Matrix3& matrix);
        virtual Ionflux::GeoUtils::Vertex3Set& transform(const 
        Ionflux::GeoUtils::Matrix4& matrix);
        virtual Ionflux::GeoUtils::Vertex3Set& transformVI(const 
        Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4*
        image = 0);
        virtual Ionflux::GeoUtils::Vertex3Set& duplicate();
        virtual Ionflux::GeoUtils::Matrix3 getCovariance();
        virtual Ionflux::GeoUtils::Matrix3 getPCABase();
        virtual Ionflux::GeoUtils::Plane3 getPlaneFit();
        virtual std::string getValueString() const;
        virtual std::string getXMLData_legacy() const;
        virtual std::string getXML_legacy() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Vertex3Set* copy() const;
		static Ionflux::GeoUtils::Vertex3Set* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::Vertex3Set* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Vertex3Set* 
		create(Ionflux::GeoUtils::Vertex3Vector& initVertices, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual bool serialize(std::string& target) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(const std::string& source, int offset = 0);
        virtual bool serialize(Ionflux::ObjectBase::IFIOContext& ioCtx, bool addMagicWord = true) const;
        virtual Ionflux::ObjectBase::DataSize deserialize(Ionflux::ObjectBase::IFIOContext& ioCtx, Ionflux::ObjectBase::DataSize offset = Ionflux::ObjectBase::DATA_SIZE_INVALID, bool checkMagicWord = true);
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllable() const;
        virtual Ionflux::ObjectBase::MagicSyllable getMagicSyllableBase() const;        
        virtual unsigned int getNumVertices() const;
        virtual Ionflux::GeoUtils::Vertex3* getVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vertex3*>& getVertices();
        virtual void addVertex(Ionflux::GeoUtils::Vertex3* addElement);
		virtual Ionflux::GeoUtils::Vertex3* addVertex();
		virtual void addVertices(std::vector<Ionflux::GeoUtils::Vertex3*>& 
		newVertices);
		virtual void addVertices(Ionflux::GeoUtils::Vertex3Set* newVertices);        
        virtual void removeVertex(Ionflux::GeoUtils::Vertex3* 
        removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();
};

}

}
