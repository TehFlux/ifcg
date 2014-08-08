#ifndef IONFLUX_GEOUTILS_FACE
#define IONFLUX_GEOUTILS_FACE
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Face.hpp                        Mesh face (header).
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
#include "geoutils/Matrix3.hpp"
#include "geoutils/NFace.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class VectorSetSet;
class FaceData;
class NFaceSet;

namespace XMLUtils
{

class FaceXMLFactory;

}

/// Class information for class Face.
class FaceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		FaceClassInfo();
		/// Destructor.
		virtual ~FaceClassInfo();
};

/** Mesh face.
 * \ingroup geoutils
 *
 * A mesh face.
 */
class Face
: public Ionflux::GeoUtils::NFace
{
	private:
		
	protected:
		/// Tangent vector.
		Ionflux::GeoUtils::Vector3* tangent;
		/// Normal vector.
		Ionflux::GeoUtils::Vector3* normal;
		/// Binormal vector.
		Ionflux::GeoUtils::Vector3* binormal;
		
	public:
		/// Class information instance.
		static const FaceClassInfo faceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Face object.
		 */
		Face();
		
		/** Constructor.
		 *
		 * Construct new Face object.
		 *
		 * \param other Other object.
		 */
		Face(const Ionflux::GeoUtils::Face& other);
		
		/** Constructor.
		 *
		 * Construct new Face object.
		 *
		 * \param initVerts Vertex index vector.
		 * \param initVertexSource Vertex source.
		 * \param initUV Texture coordinates.
		 * \param initVertexColors Vertex colors.
		 */
		Face(const Ionflux::ObjectBase::UIntVector* initVerts, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0);
		
		/** Constructor.
		 *
		 * Construct new Face object.
		 *
		 * \param v0 Vertex index (0).
		 * \param v1 Vertex index (1).
		 * \param v2 Vertex index (2).
		 * \param v3 Vertex index (3).
		 * \param initVertexSource Vertex source.
		 * \param initUV Texture coordinates.
		 * \param initVertexColors Vertex colors.
		 */
		Face(unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3 =
		Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0);
		
		/** Destructor.
		 *
		 * Destruct Face object.
		 */
		virtual ~Face();
		
		/** Update.
		 *
		 * Update all state according to the vertices of the face.
		 */
		virtual void update();
		
		/** Clear tangent space.
		 *
		 * Clear the tangent space vectors.
		 */
		virtual void clearTangentSpace();
		
		/** Clear.
		 *
		 * Removes all items and resets state.
		 */
		virtual void clear();
		
		/** Set face vertex normals.
		 *
		 * Set the vertex normals for the face to the face normal.
		 */
		virtual void setFaceVertexNormals();
		
		/** Get tangent vector.
		 *
		 * Get the tangent vector for the face.
		 *
		 * \return Tangent vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getTangent();
		
		/** .
		 *
		 * Get the binormal vector for the face.
		 *
		 * \return Binormal vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBinormal();
		
		/** .
		 *
		 * Get the normal vector for the face.
		 *
		 * \return Normal vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getNormal();
		
		/** .
		 *
		 * Calculates the base matrix of the tangent space for the face.
		 *
		 * \return Tangent space base matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix3 getTangentBase();
		
		/** Get triangle faces.
		 *
		 * Create triangles for a quad face. The new faces are not referenced 
		 * and must be managed by the caller.
		 *
		 * \param target where to store the triangles.
		 */
		virtual void getTris(Ionflux::GeoUtils::FaceVector& target);
		
		/** Get triangle faces.
		 *
		 * Create triangles for a quad face. The new faces are not referenced 
		 * and must be managed by the caller.
		 *
		 * \param target where to store the triangles.
		 */
		virtual void getTris(Ionflux::GeoUtils::NFaceSet& target);
		
		/** Get triangle faces.
		 *
		 * Create triangles for a quad face. The new faces are not referenced 
		 * and must be managed by the caller.
		 *
		 * \return Vector containing triangle faces.
		 */
		virtual Ionflux::GeoUtils::FaceVector getTris0();
		
		/** Get triangle edges.
		 *
		 * Create edges for a face. The new edges are not referenced and must 
		 * be managed by the caller.
		 *
		 * \param target where to store the edges.
		 * \param copyFaceData copy corresponding face data to the new edges.
		 */
		virtual void getEdges(Ionflux::GeoUtils::NFaceVector& target, bool 
		copyFaceData = true);
		
		/** Get triangle edges.
		 *
		 * Create edges for a face.
		 *
		 * \param target where to store the edges.
		 * \param copyFaceData copy corresponding face data to the new edges.
		 */
		virtual void getEdges(Ionflux::GeoUtils::NFaceSet& target, bool 
		copyFaceData = true);
		
		/** Make face planar.
		 *
		 * Make the face planar. If the optional parameter is specified, 
		 * vertices will be moved only by the specified fraction of the offset
		 * required to make the face planar. The transformations (if any) are 
		 * applied immediately to the vertices.
		 *
		 * \param p Parameter.
		 * \param t Tolerance.
		 */
		virtual void makePlanar(double p = 1., double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Backface check.
		 *
		 * Check whether the face faces backwards relative to the specified 
		 * front vector.
		 *
		 * \param front Front vector.
		 *
		 * \return The duplicated object.
		 */
		virtual bool isBackface(const Ionflux::GeoUtils::Vector3& front);
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Face& scale(const Ionflux::GeoUtils::Vector3& 
		s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Face& translate(const 
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
		virtual Ionflux::GeoUtils::Face& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Face& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Face& 
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
		virtual Ionflux::GeoUtils::Face& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Face& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Face& duplicate();
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Face& operator=(const Ionflux::GeoUtils::Face&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Face* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Face* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Face* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Face object.
		 *
		 * \param initVerts Vertex index vector.
		 * \param initVertexSource Vertex source.
		 * \param initUV Texture coordinates.
		 * \param initVertexColors Vertex colors.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Face* create(const 
		Ionflux::ObjectBase::UIntVector* initVerts, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Face object.
		 *
		 * \param v0 Vertex index (0).
		 * \param v1 Vertex index (1).
		 * \param v2 Vertex index (2).
		 * \param v3 Vertex index (3).
		 * \param initVertexSource Vertex source.
		 * \param initUV Texture coordinates.
		 * \param initVertexColors Vertex colors.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Face* create(unsigned int v0, unsigned int v1, 
		unsigned int v2, unsigned int v3 = 
		Ionflux::GeoUtils::NFace::VERTEX_INDEX_NONE, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0, Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
        
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
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 *
		 * \param fileName file name
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
};

}

}

/** \file Face.hpp
 * \brief Mesh face (header).
 */
#endif
