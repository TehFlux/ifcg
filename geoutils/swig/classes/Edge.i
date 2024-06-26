/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Edge.i                          Polygon edge (interface).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "geoutils/Edge.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Edge;

typedef std::vector<Ionflux::GeoUtils::Edge*> EdgeVector;

class EdgeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        EdgeClassInfo();
        virtual ~EdgeClassInfo();
};

class Edge
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Edge();
		Edge(const Ionflux::GeoUtils::Edge& other);
        Edge(int initV0, int initV1);
        Edge(const Ionflux::ObjectBase::IntVector& initVertices);
        virtual ~Edge();
        virtual void setVertices(const Ionflux::ObjectBase::IntVector& 
        newVertices);
        virtual void setVertices(int i0, int i1);
        virtual void getVertices(Ionflux::ObjectBase::IntVector& target) 
        const;
        virtual int getVertex(int index) const;
        virtual Ionflux::ObjectBase::IntVector getVector() const;
        virtual void setVertex(int index, int value);
        virtual void sort();
        virtual bool operator==(const Ionflux::GeoUtils::Edge& other) 
        const;
        virtual bool operator<(const Ionflux::GeoUtils::Edge& other) const;
        virtual bool operator!=(const Ionflux::GeoUtils::Edge& other) 
        const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::Edge* copy() const;
		static Ionflux::GeoUtils::Edge* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::GeoUtils::Edge* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::Edge* create(int initV0, int initV1, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		static Ionflux::GeoUtils::Edge* create(const 
		Ionflux::ObjectBase::IntVector& initVertices, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void setV0(int newV0);
        virtual int getV0() const;
        virtual void setV1(int newV1);
        virtual int getV1() const;
};

}

}
