#ifndef IONFLUX_GEOUTILS_POLYGON2
#define IONFLUX_GEOUTILS_POLYGON2
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon2.hpp                    Polygon (2D) (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Vertex2.hpp"
#include "geoutils/Edge.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Class information for class Polygon2.
class Polygon2ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Polygon2ClassInfo();
		/// Destructor.
		virtual ~Polygon2ClassInfo();
};

/** Polygon (2D).
 * \ingroup geoutils
 *
 * A polygon in two-dimensional space.
 */
class Polygon2
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Vertex vector.
		std::vector<Ionflux::GeoUtils::Vertex2*> vertices;
		/// Edge vector.
		std::vector<Ionflux::GeoUtils::Edge*> edges;
		
	public:
		/// Class information instance.
		static const Polygon2ClassInfo polygon2ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Polygon2 object.
		 */
		Polygon2();
		
		/** Constructor.
		 *
		 * Construct new Polygon2 object.
		 *
		 * \param other Other object.
		 */
		Polygon2(const Ionflux::GeoUtils::Polygon2& other);
		
		/** Constructor.
		 *
		 * Construct new Polygon2 object.
		 *
		 * \param initVertices Vertices.
		 * \param initEdges Edges.
		 */
		Polygon2(Ionflux::GeoUtils::Vertex2Vector* initVertices, 
		Ionflux::GeoUtils::EdgeVector* initEdges = 0);
		
		/** Destructor.
		 *
		 * Destruct Polygon2 object.
		 */
		virtual ~Polygon2();
		
		/** Add vertices.
		 *
		 * Add vertices from a vector of vertices.
		 *
		 * \param newVertices Vertex vector.
		 */
		virtual void addVertices(Ionflux::GeoUtils::Vertex2Vector& newVertices);
		
		/** Add edges.
		 *
		 * Add edges from a vector of edges.
		 *
		 * \param newEdges Edge vector.
		 */
		virtual void addEdges(Ionflux::GeoUtils::EdgeVector& newEdges);
		
		/** Create edges.
		 *
		 * Takes two subsequent vertices from the list to create edges.
		 *
		 * \return The number of edges created.
		 */
		virtual int createEdges();
		
		/** Vertex in polygon check.
		 *
		 * Check whether a vertex is inside the polygon.
		 *
		 * \param v Vertex.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool checkVertex(const Ionflux::GeoUtils::Vertex2& v, double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Polygon2& operator=(const 
		Ionflux::GeoUtils::Polygon2& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Polygon2* copy() const;
		
		/** Get number of vertices.
		 *
		 * \return Number of vertices.
		 */
		virtual unsigned int getNumVertices() const;
		
		/** Get vertex.
		 *
		 * Get the vertex at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Vertex at specified index.
		 */
		virtual Ionflux::GeoUtils::Vertex2* getVertex(unsigned int elementIndex =
		0) const;
		
		/** Find vertex.
		 *
		 * Find the specified occurence of a vertex.
		 *
		 * \param needle Vertex to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the vertex, or -1 if the vertex cannot be found.
		 */
		virtual int findVertex(Ionflux::GeoUtils::Vertex2* needle, unsigned int 
		occurence = 1) const;
        
		/** Get vertex vector.
		 *
		 * \return vertex vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::Vertex2*>& getVertices();
		
		/** Add vertex.
		 *
		 * Add a vertex.
		 *
		 * \param addElement Vertex to be added.
		 */
		virtual void addVertex(Ionflux::GeoUtils::Vertex2* addElement);
		
		/** Remove vertex.
		 *
		 * Remove a vertex.
		 *
		 * \param removeElement Vertex to be removed.
		 */
		virtual void removeVertex(Ionflux::GeoUtils::Vertex2* removeElement);
		
		/** Remove vertex.
		 *
		 * Remove a vertex.
		 *
		 * \param removeIndex Vertex to be removed.
		 */
		virtual void removeVertexIndex(unsigned int removeIndex);
		
		/** Clear vertices.
		 *
		 * Clear all vertices.
		 */
		virtual void clearVertices();
		
		/** Get number of edges.
		 *
		 * \return Number of edges.
		 */
		virtual unsigned int getNumEdges() const;
		
		/** Get edge.
		 *
		 * Get the edge at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Edge at specified index.
		 */
		virtual Ionflux::GeoUtils::Edge* getEdge(unsigned int elementIndex = 0) 
		const;
		
		/** Find edge.
		 *
		 * Find the specified occurence of a edge.
		 *
		 * \param needle Edge to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the edge, or -1 if the edge cannot be found.
		 */
		virtual int findEdge(Ionflux::GeoUtils::Edge* needle, unsigned int 
		occurence = 1) const;
        
		/** Get edge vector.
		 *
		 * \return edge vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::Edge*>& getEdges();
		
		/** Add edge.
		 *
		 * Add a edge.
		 *
		 * \param addElement Edge to be added.
		 */
		virtual void addEdge(Ionflux::GeoUtils::Edge* addElement);
		
		/** Remove edge.
		 *
		 * Remove a edge.
		 *
		 * \param removeElement Edge to be removed.
		 */
		virtual void removeEdge(Ionflux::GeoUtils::Edge* removeElement);
		
		/** Remove edge.
		 *
		 * Remove a edge.
		 *
		 * \param removeIndex Edge to be removed.
		 */
		virtual void removeEdgeIndex(unsigned int removeIndex);
		
		/** Clear edges.
		 *
		 * Clear all edges.
		 */
		virtual void clearEdges();
};

}

}

/** \file Polygon2.hpp
 * \brief Polygon (2D) (header).
 */
#endif
