#ifndef IONFLUX_GEOUTILS_VERTEX3SET
#define IONFLUX_GEOUTILS_VERTEX3SET
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Vertex3Set.hpp                  Vertex set (3D) (header).
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
#include "geoutils/Matrix4.hpp"
#include "geoutils/Plane3.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Vertex3;

/// Class information for class Vertex3Set.
class Vertex3SetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		Vertex3SetClassInfo();
		/// Destructor.
		virtual ~Vertex3SetClassInfo();
};

/** Vertex set (3D).
 * \ingroup geoutils
 *
 * A set of vertices in three-dimensional space.
 */
class Vertex3Set
: public Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// Vertex vector.
		std::vector<Ionflux::GeoUtils::Vertex3*> vertices;
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the face.
		 */
		virtual void recalculateBounds();
		
	public:
		/// Class information instance.
		static const Vertex3SetClassInfo vertex3SetClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Vertex3Set object.
		 */
		Vertex3Set();
		
		/** Constructor.
		 *
		 * Construct new Vertex3Set object.
		 *
		 * \param other Other object.
		 */
		Vertex3Set(const Ionflux::GeoUtils::Vertex3Set& other);
		
		/** Constructor.
		 *
		 * Construct new Vertex3Set object.
		 *
		 * \param initVertices Vertices.
		 */
		Vertex3Set(Ionflux::GeoUtils::Vertex3Vector& initVertices);
		
		/** Destructor.
		 *
		 * Destruct Vertex3Set object.
		 */
		virtual ~Vertex3Set();
		
		/** Create vertex.
		 *
		 * Create a new vertex which is managed by the vertex set.
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
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for the vertices in the set.
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
		virtual Ionflux::GeoUtils::Vertex3Set& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set& translate(const 
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
		virtual Ionflux::GeoUtils::Vertex3Set& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set& 
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
		virtual Ionflux::GeoUtils::Vertex3Set& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** View/image transformation.
		 *
		 * Apply a view transformation matrix and an optional image 
		 * transformation matrix to the object.
		 *
		 * \param view View transformation matrix.
		 * \param image Image transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set& duplicate();
		
		/** Get covariance matrix.
		 *
		 * Calculate the covariance matrix for vertices in the set.
		 *
		 * \return covariance matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix3 getCovariance();
		
		/** Get PCA base.
		 *
		 * Calculate the PCA base matrix. This is obtained by calculating the 
		 * primary component analysis of the vertices in the set.
		 *
		 * \return PCA base matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix3 getPCABase();
		
		/** Get plane fit.
		 *
		 * Fit a plane to the vertices in the set.
		 *
		 * \return Plane.
		 */
		virtual Ionflux::GeoUtils::Plane3 getPlaneFit();
		
		/** Get XML data representation.
		 *
		 * Get a representation of the object suitable for use in an XML data 
		 * attribute.
		 *
		 * \return XML data representation.
		 */
		virtual std::string getXMLData() const;
		
		/** Get XML representation.
		 *
		 * Get an XML representation of the object.
		 *
		 * \return XML representation.
		 */
		virtual std::string getXML() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set& operator=(const 
		Ionflux::GeoUtils::Vertex3Set& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Vertex3Set* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Vertex3Set* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
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
		static Ionflux::GeoUtils::Vertex3Set* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
};

}

}

/** \file Vertex3Set.hpp
 * \brief Vertex set (3D) (header).
 */
#endif
