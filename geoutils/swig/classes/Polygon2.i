/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon2.i                      Polygon (2D) (interface).
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
#include "geoutils/Polygon2.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Polygon2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        Polygon2ClassInfo();
        virtual ~Polygon2ClassInfo();
};

class Polygon2
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        Polygon2();
		Polygon2(const Ionflux::GeoUtils::Polygon2& other);
        Polygon2(Ionflux::GeoUtils::Vertex2Vector* initVertices, 
        Ionflux::GeoUtils::EdgeVector* initEdges = 0);
        virtual ~Polygon2();
        virtual void addVertices(Ionflux::GeoUtils::Vertex2Vector& 
        newVertices);
        virtual void addEdges(Ionflux::GeoUtils::EdgeVector& newEdges);
        virtual int createEdges();
        virtual bool checkVertex(const Ionflux::GeoUtils::Vertex2& v, 
        double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		virtual Ionflux::GeoUtils::Polygon2* copy() const;        
        virtual unsigned int getNumVertices() const;
        virtual Ionflux::GeoUtils::Vertex2* getVertex(unsigned int 
        elementIndex = 0) const;
		virtual int findVertex(Ionflux::GeoUtils::Vertex2* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vertex2*>& getVertices();
        virtual void addVertex(Ionflux::GeoUtils::Vertex2* addElement);        
        virtual void removeVertex(Ionflux::GeoUtils::Vertex2* 
        removeElement);
		virtual void removeVertexIndex(unsigned int removeIndex);
		virtual void clearVertices();        
        virtual unsigned int getNumEdges() const;
        virtual Ionflux::GeoUtils::Edge* getEdge(unsigned int elementIndex 
        = 0) const;
		virtual int findEdge(Ionflux::GeoUtils::Edge* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Edge*>& getEdges();
        virtual void addEdge(Ionflux::GeoUtils::Edge* addElement);        
        virtual void removeEdge(Ionflux::GeoUtils::Edge* removeElement);
		virtual void removeEdgeIndex(unsigned int removeIndex);
		virtual void clearEdges();
};

}

}
