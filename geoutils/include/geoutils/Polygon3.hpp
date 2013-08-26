#ifndef IONFLUX_GEOUTILS_POLYGON3
#define IONFLUX_GEOUTILS_POLYGON3
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Polygon3.hpp                    Polygon (3D) (header).
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
#include "geoutils/Vertex3.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "geoutils/Edge.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Matrix3.hpp"
#include "geoutils/Plane3.hpp"
#include "geoutils/Polygon2.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/Range3.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Polygon3;

/// Class information for class Polygon3.
class Polygon3ClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Polygon3ClassInfo();
		/// Destructor.
		virtual ~Polygon3ClassInfo();
};

/** Polygon (3D).
 * \ingroup geoutils
 *
 * A polygon in three-dimensional space.
 */
class Polygon3
: public Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// Vertex source.
		Ionflux::GeoUtils::Vertex3Set* vertexSource;
		/// Edge vector.
		std::vector<Ionflux::GeoUtils::Edge*> edges;
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the polygon.
		 */
		virtual void recalculateBounds();
		
	public:
		/// Point UV coordinate range.
		static const Ionflux::GeoUtils::Range UV_RANGE;
		/// Class information instance.
		static const Polygon3ClassInfo polygon3ClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Polygon3 object.
		 */
		Polygon3();
		
		/** Constructor.
		 *
		 * Construct new Polygon3 object.
		 *
		 * \param other Other object.
		 */
		Polygon3(const Ionflux::GeoUtils::Polygon3& other);
		
		/** Constructor.
		 *
		 * Construct new Polygon3 object.
		 *
		 * \param initVertices Vertices.
		 * \param initEdges Edges.
		 */
		Polygon3(Ionflux::GeoUtils::Vertex3Vector* initVertices, 
		Ionflux::GeoUtils::EdgeVector* initEdges = 0);
		
		/** Constructor.
		 *
		 * Construct new Polygon3 object.
		 *
		 * \param initVertexSource Vertex source.
		 * \param initEdges Edges.
		 */
		Polygon3(Ionflux::GeoUtils::Vertex3Set* initVertexSource, 
		Ionflux::GeoUtils::EdgeVector* initEdges = 0);
		
		/** Constructor.
		 *
		 * Construct new Polygon3 object.
		 *
		 * \param v0 Vertex (0).
		 * \param v1 Vertex (1).
		 * \param v2 Vertex (2).
		 * \param v3 Vertex (3).
		 */
		Polygon3(const Ionflux::GeoUtils::Vertex3* v0, const 
		Ionflux::GeoUtils::Vertex3* v1, const Ionflux::GeoUtils::Vertex3* v2, 
		const Ionflux::GeoUtils::Vertex3* v3 = 0);
		
		/** Destructor.
		 *
		 * Destruct Polygon3 object.
		 */
		virtual ~Polygon3();
		
		/** Copy vertices.
		 *
		 * Create a new vertex set with copies of the current vertices. This 
		 * makes the polygon the (current) single owner of its vertices.
		 */
		virtual void copyVertices();
		
		/** Create vertex.
		 *
		 * Create a new vertex which is managed by the vertex source.
		 *
		 * \return New vertex.
		 */
		virtual Ionflux::GeoUtils::Vertex3* addVertex();
		
		/** Add vertices.
		 *
		 * Add vertices from a vertex vector.
		 *
		 * \param newVerts Vertices.
		 */
		virtual void addVertices(Ionflux::GeoUtils::Vertex3Vector& newVerts);
		
		/** Add vertices.
		 *
		 * Add vertices from a vertex set.
		 *
		 * \param newVerts Vertices.
		 */
		virtual void addVertices(Ionflux::GeoUtils::Vertex3Set& newVerts);
		
		/** Add edge.
		 *
		 * Add a new edges which will be managed by this polygon.
		 *
		 * \return New edge.
		 */
		virtual Ionflux::GeoUtils::Edge* addEdge();
		
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
		
		/** Get plane spanned by vertices.
		 *
		 * Get the plane spanned by the specified three vertex indices. If the
		 * vertices parameter is not specified, the first two and the last 
		 * vertices are used.
		 *
		 * \param v0 First vertex index.
		 * \param v1 Second vertex index.
		 * \param v2 Third vertex index.
		 *
		 * \return Plane spanned by the vertices.
		 */
		virtual Ionflux::GeoUtils::Plane3 getPlane(int v0 = 0, int v1 = 1, int v2
		= -1) const;
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get SVG representation.
		 *
		 * Get a Scalable Vector Graphics (XML) representation of the polygon.
		 * The polygon will be projected orthogonally to the appropriate 
		 * coordinate plane along the specified axis. The type of SVG element 
		 * that is created to represent the polygon depends on the \c 
		 * shapeType parameter. If the shape type is \c SHAPE_TYPE_PATH and \c
		 * closePath is \c true (the default), the path will be closed.
		 *
		 * \param attrs Element attributes.
		 * \param elementID Element ID.
		 * \param axis Projection axis.
		 * \param shapeType Shape type.
		 * \param closePath Close path.
		 *
		 * \return SVG representation.
		 */
		virtual std::string getSVG(const std::string& attrs = 
		SVG_DEFAULT_POLY_STYLE, const std::string& elementID = "polygon", 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Y, 
		Ionflux::GeoUtils::SVGShapeType shapeType = 
		Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
		
		/** Get SVG representation.
		 *
		 * Get a Scalable Vector Graphics (XML) representation of the polygon.
		 * The polygon will be projected orthogonally to the appropriate 
		 * coordinate plane along the specified axis. The type of SVG element 
		 * that is created to represent the polygon depends on the \c 
		 * shapeType parameter. If the shape type is \c SHAPE_TYPE_PATH and \c
		 * closePath is \c true (the default), the path will be closed.
		 *
		 * \param style Shape style.
		 * \param elementID Element ID.
		 * \param axis Projection axis.
		 * \param shapeType Shape type.
		 * \param closePath Close path.
		 *
		 * \return SVG representation.
		 */
		virtual std::string getSVG(const Ionflux::GeoUtils::SVGShapeStyle& style,
		const std::string& elementID = "polygon", Ionflux::GeoUtils::AxisID axis 
		= Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::SVGShapeType shapeType = 
		Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for the polygon.
		 *
		 * \return Barycenter vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBarycenter();
		
		/** Apply transformations.
		 *
		 * Apply transformations that have been accumulated in the 
		 * transformation matrices.
		 *
		 * \param recursive Apply transformations recursively.
		 */
		virtual void applyTransform(bool recursive = false);
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3& translate(const 
		Ionflux::GeoUtils::Vector3& t);
		
		/** Rotate.
		 *
		 * Rotate the object by the specified angle around the specified axis.
		 *
		 * \param phi Angle.
		 * \param axis Axis.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3& 
		center(Ionflux::GeoUtils::CenteringMethod method = 
		Ionflux::GeoUtils::CENTER_BARYCENTER, Ionflux::GeoUtils::Vector3* origin 
		= 0);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Polygon3& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Polygon3& duplicate();
		
		/** Planarity check.
		 *
		 * Check whether the polygon is planar.
		 *
		 * \param t Tolerance.
		 *
		 * \return Check result.
		 */
		virtual bool isPlanar(double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Get polygon (2D).
		 *
		 * Create a 2D polygon from the 3D polygon. The vertex coordinates are
		 * projected along the Z axis.
		 *
		 * \param target target polygon.
		 */
		virtual void getPolygon2(Ionflux::GeoUtils::Polygon2& target);
		
		/** Create polygon: square.
		 *
		 * Create a square polygon.
		 *
		 * \return Square polygon.
		 */
		static Ionflux::GeoUtils::Polygon3* square();
		
		/** Triangle check.
		 *
		 * Check whether the polygon is a triangle.
		 *
		 * \return Check result.
		 */
		virtual bool isTri();
		
		/** Quadrilateral check.
		 *
		 * Check whether the polygon is a quadrilateral.
		 *
		 * \return Check result.
		 */
		virtual bool isQuad();
		
		/** Calculate UV coefficients.
		 *
		 * Calculate the coefficients for the system of cubic equations needed
		 * to obtain the UV coordinates for the specified point. The result of
		 * the calculation is a 4x4 matrix, where each row contains the 
		 * coefficients for one of the cubic equations used to calculate the 
		 * point UV coordinates. The coefficients can be used to calculate 
		 * either the U or V coordinate of the point, depending on the 
		 * ordering of vertices. To calculate both the U and V coordinates, 
		 * the function needs to be called twice with the appropriate 
		 * permutation of vertex indices.
		 * 
		 * \sa getUV()
		 *
		 * \param p point.
		 * \param target where to store the coefficients.
		 * \param indices Vertex indices.
		 * \param s scale factor for the coefficients.
		 */
		virtual void calculateUVCoefficients(const Ionflux::GeoUtils::Vertex3& p,
		Ionflux::GeoUtils::Matrix4& target, Ionflux::ObjectBase::IntVector* 
		indices = 0, double s = 1.);
		
		/** Get UV coordinates for vertex.
		 *
		 * Calculate the UV coordinates of the specified vertex relative to 
		 * the (quadrilateral) polygon. The vertex order can be specified by 
		 * the optional \c indices parameter.
		 *
		 * \param p point.
		 * \param indices Vertex indices.
		 * \param interpolationType interpolation type.
		 * \param s scale factor for the coefficients.
		 * \param t tolerance for comparisons.
		 *
		 * \return UV coordinates of point.
		 */
		virtual Ionflux::GeoUtils::Vector2 getUV(const 
		Ionflux::GeoUtils::Vertex3& p, Ionflux::ObjectBase::IntVector* indices = 
		0, Ionflux::GeoUtils::QuadInterpolationTypeID interpolationType = 
		QUAD_INTERPOLATION_BILINEAR, double s = 1., double t = 
		DEFAULT_TOLERANCE);
		
		/** Get a vertex from UV coordinates.
		 *
		 * Get a vertex from the (quadrilateral) polygon by evaluating the 
		 * specified UV coordinates. The vertex order can be specified by the 
		 * optional \c indices parameter.
		 *
		 * \param uv UV coordinates.
		 * \param indices Vertex indices.
		 * \param interpolationType interpolation type.
		 *
		 * \return UV vertex.
		 */
		virtual Ionflux::GeoUtils::Vertex3 getUVVertex(const 
		Ionflux::GeoUtils::Vector2& uv, Ionflux::ObjectBase::IntVector* indices =
		0, Ionflux::GeoUtils::QuadInterpolationTypeID interpolationType = 
		QUAD_INTERPOLATION_BILINEAR);
		
		/** Create polygon: circle.
		 *
		 * Create a circle polygon.
		 *
		 * \param resolution Resolution.
		 *
		 * \return Square polygon.
		 */
		static Ionflux::GeoUtils::Polygon3* circle(unsigned int resolution = 20);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Polygon3& operator=(const 
		Ionflux::GeoUtils::Polygon3& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Polygon3* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Polygon3* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::GeoUtils::Polygon3* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		
		/** Get vertex source.
		 *
		 * \return Current value of vertex source.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set* getVertexSource() const;
		
		/** Set vertex source.
		 *
		 * Set new value of vertex source.
		 *
		 * \param newVertexSource New value of vertex source.
		 */
		virtual void setVertexSource(Ionflux::GeoUtils::Vertex3Set* 
		newVertexSource);
		
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
		virtual Ionflux::GeoUtils::Vertex3* getVertex(unsigned int elementIndex =
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
		virtual int findVertex(Ionflux::GeoUtils::Vertex3* needle, unsigned int 
		occurence = 1) const;
        
		/** Get vertex vector.
		 *
		 * \return vertex vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::Vertex3*>& getVertices();
		
		/** Add vertex.
		 *
		 * Add a vertex.
		 *
		 * \param addElement Vertex to be added.
		 */
		virtual void addVertex(Ionflux::GeoUtils::Vertex3* addElement);
		
		/** Remove vertex.
		 *
		 * Remove a vertex.
		 *
		 * \param removeElement Vertex to be removed.
		 */
		virtual void removeVertex(Ionflux::GeoUtils::Vertex3* removeElement);
		
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

/** \file Polygon3.hpp
 * \brief Polygon (3D) (header).
 */
#endif
