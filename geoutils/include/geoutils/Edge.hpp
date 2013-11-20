#ifndef IONFLUX_GEOUTILS_EDGE
#define IONFLUX_GEOUTILS_EDGE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Edge.hpp                        Polygon edge (header).
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

#include "ifobject/types.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Edge;

typedef std::vector<Ionflux::GeoUtils::Edge*> EdgeVector;

/// Class information for class Edge.
class EdgeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		EdgeClassInfo();
		/// Destructor.
		virtual ~EdgeClassInfo();
};

/** Polygon edge.
 * \ingroup geoutils
 *
 * A polygon edge, which is specified by two vertex indices.
 */
class Edge
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// First vertex index.
		int v0;
		/// Second vertex index.
		int v1;
		
	public:
		/// Class information instance.
		static const EdgeClassInfo edgeClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Edge object.
		 */
		Edge();
		
		/** Constructor.
		 *
		 * Construct new Edge object.
		 *
		 * \param other Other object.
		 */
		Edge(const Ionflux::GeoUtils::Edge& other);
		
		/** Constructor.
		 *
		 * Construct new Edge object.
		 *
		 * \param initV0 First vertex index.
		 * \param initV1 Second vertex index.
		 */
		Edge(int initV0, int initV1);
		
		/** Constructor.
		 *
		 * Construct new Edge object.
		 *
		 * \param initVertices Vertex index vector.
		 */
		Edge(const Ionflux::ObjectBase::IntVector& initVertices);
		
		/** Destructor.
		 *
		 * Destruct Edge object.
		 */
		virtual ~Edge();
		
		/** Set vertices.
		 *
		 * Set vertices from a vector of integers. If the vector contains 
		 * fewer than the required number of vertex indices, the remaining 
		 * vertex indices will be left alone.
		 *
		 * \param newVertices Vertex index vector.
		 */
		virtual void setVertices(const Ionflux::ObjectBase::IntVector& 
		newVertices);
		
		/** Set vertices.
		 *
		 * Set vertex indices.
		 *
		 * \param i0 Vertex Index (0).
		 * \param i1 Vertex Index (1).
		 */
		virtual void setVertices(int i0, int i1);
		
		/** Get vertices.
		 *
		 * Store the vertex indices in a vector of integers.
		 *
		 * \param target Target vector.
		 */
		virtual void getVertices(Ionflux::ObjectBase::IntVector& target) const;
		
		/** Get vertex.
		 *
		 * Get the vertex index with the specified index.
		 *
		 * \param index Index.
		 *
		 * \return Element at the specified index.
		 */
		virtual int getVertex(int index) const;
		
		/** Get coordinates as vector.
		 *
		 * Get the coordinates of the vertex as a vector.
		 *
		 * \return Vector.
		 */
		virtual Ionflux::ObjectBase::IntVector getVector() const;
		
		/** Set vertex.
		 *
		 * Set the vertex index with the specified index.
		 *
		 * \param index Index.
		 * \param value Value.
		 */
		virtual void setVertex(int index, int value);
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Edge.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Edge& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Edge.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Edge& other) const;
		
		/** Subscript operator.
		 *
		 * Subscript operator.
		 *
		 * \param index Index.
		 *
		 * \return Element at specified index.
		 */
		virtual double operator[](int index) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Edge& operator=(const Ionflux::GeoUtils::Edge&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Edge* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Edge* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Edge* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Edge object.
		 *
		 * \param initV0 First vertex index.
		 * \param initV1 Second vertex index.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Edge* create(int initV0, int initV1, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Edge object.
		 *
		 * \param initVertices Vertex index vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Edge* create(const 
		Ionflux::ObjectBase::IntVector& initVertices, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
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
		 */
		virtual void loadFromXMLFile(const std::string& FileName);
		
		/** Get first vertex index.
		 *
		 * \return Current value of first vertex index.
		 */
		virtual int getV0() const;
		
		/** Set first vertex index.
		 *
		 * Set new value of first vertex index.
		 *
		 * \param newV0 New value of first vertex index.
		 */
		virtual void setV0(int newV0);
		
		/** Get second vertex index.
		 *
		 * \return Current value of second vertex index.
		 */
		virtual int getV1() const;
		
		/** Set second vertex index.
		 *
		 * Set new value of second vertex index.
		 *
		 * \param newV1 New value of second vertex index.
		 */
		virtual void setV1(int newV1);
};

}

}

/** \file Edge.hpp
 * \brief Polygon edge (header).
 */
#endif
