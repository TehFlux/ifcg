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
#include "geoutils/BoxBoundsItem.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class VectorSetSet;
class FaceData;

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
: public Ionflux::GeoUtils::BoxBoundsItem, public 
Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// Tangent vector.
		Ionflux::GeoUtils::Vector3* tangent;
		/// Normal vector.
		Ionflux::GeoUtils::Vector3* normal;
		/// Binormal vector.
		Ionflux::GeoUtils::Vector3* binormal;
		/// Polygon.
		Ionflux::GeoUtils::Polygon3* polygon;
		/// Vertex index vector.
		std::vector<unsigned int> vertices;
		/// Vertex source.
		Ionflux::GeoUtils::Vertex3Set* vertexSource;
		/// face data.
		Ionflux::GeoUtils::VectorSetSet* faceData;
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the face.
		 */
		virtual void recalculateBounds();
		
	public:
		/// Vertex index not pointing at any vertex.
		static const unsigned int VERTEX_INDEX_NONE;
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
		Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE, 
		Ionflux::GeoUtils::Vertex3Set* initVertexSource = 0, 
		Ionflux::GeoUtils::FaceData* initUV = 0, Ionflux::GeoUtils::FaceData* 
		initVertexColors = 0);
		
		/** Destructor.
		 *
		 * Destruct Face object.
		 */
		virtual ~Face();
		
		/** Copy vertices.
		 *
		 * Create a new vertex set with copies of the current vertices. This 
		 * makes the face the (current) single owner of its vertices.
		 */
		virtual void copyVertices();
		
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
		
		/** Clear polygon.
		 *
		 * Clear the face polygon.
		 */
		virtual void clearPolygon();
		
		/** Clear.
		 *
		 * Removes all items and resets state.
		 */
		virtual void clear();
		
		/** Add vertex indices.
		 *
		 * Add vertex indices for a triangle or quad.
		 *
		 * \param v0 Vertex index (0).
		 * \param v1 Vertex index (1).
		 * \param v2 Vertex index (2).
		 * \param v3 Vertex index (3).
		 */
		virtual void addVertices(unsigned int v0, unsigned int v1, unsigned int 
		v2, unsigned int v3 = Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE);
		
		/** Add face data.
		 *
		 * Add a face data entry.
		 *
		 * \param newFaceData Face data.
		 *
		 * \return New face data.
		 */
		virtual Ionflux::GeoUtils::VectorSet* 
		addFaceData(Ionflux::GeoUtils::FaceData* newFaceData);
		
		/** Add face data.
		 *
		 * Add a face data entry of a certain type.
		 *
		 * \param dataType Face data type ID.
		 *
		 * \return New face data.
		 */
		virtual Ionflux::GeoUtils::VectorSet* 
		addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType);
		
		/** Add face data.
		 *
		 * Add a face data entry of a certain type. The face data entry will 
		 * be composed of the specified input vectors.
		 *
		 * \param dataType Face data type ID.
		 * \param v0 Face data vector (0).
		 * \param v1 Face data vector (1).
		 * \param v2 Face data vector (2).
		 * \param v3 Face data vector (3).
		 *
		 * \return New face data.
		 */
		virtual Ionflux::GeoUtils::VectorSet* 
		addFaceData(Ionflux::GeoUtils::FaceDataTypeID dataType, 
		Ionflux::GeoUtils::Vector* v0, Ionflux::GeoUtils::Vector* v1 = 0, 
		Ionflux::GeoUtils::Vector* v2 = 0, Ionflux::GeoUtils::Vector* v3 = 0);
		
		/** Add texture coordinates.
		 *
		 * Add texture coordinates. The face data entry will be composed of 
		 * the specified input vectors.
		 *
		 * \param v0 Face data vector (0).
		 * \param v1 Face data vector (1).
		 * \param v2 Face data vector (2).
		 * \param v3 Face data vector (3).
		 *
		 * \return New face data.
		 */
		virtual Ionflux::GeoUtils::VectorSet* 
		addTexCoords(Ionflux::GeoUtils::Vector* v0, Ionflux::GeoUtils::Vector* v1
		= 0, Ionflux::GeoUtils::Vector* v2 = 0, Ionflux::GeoUtils::Vector* v3 = 
		0);
		
		/** Add vertex colors.
		 *
		 * Add vertex colors. The face data entry will be composed of the 
		 * specified input vectors.
		 *
		 * \param v0 Face data vector (0).
		 * \param v1 Face data vector (1).
		 * \param v2 Face data vector (2).
		 * \param v3 Face data vector (3).
		 *
		 * \return New face data.
		 */
		virtual Ionflux::GeoUtils::VectorSet* 
		addVertexColors(Ionflux::GeoUtils::Vector* v0, Ionflux::GeoUtils::Vector*
		v1 = 0, Ionflux::GeoUtils::Vector* v2 = 0, Ionflux::GeoUtils::Vector* v3 
		= 0);
		
		/** Add vertex normals.
		 *
		 * Add vertex normals. The face data entry will be composed of the 
		 * specified input vectors.
		 *
		 * \param v0 Face data vector (0).
		 * \param v1 Face data vector (1).
		 * \param v2 Face data vector (2).
		 * \param v3 Face data vector (3).
		 *
		 * \return New face data.
		 */
		virtual Ionflux::GeoUtils::VectorSet* 
		addVertexNormals(Ionflux::GeoUtils::Vector* v0, 
		Ionflux::GeoUtils::Vector* v1 = 0, Ionflux::GeoUtils::Vector* v2 = 0, 
		Ionflux::GeoUtils::Vector* v3 = 0);
		
		/** Set face vertex normals.
		 *
		 * Set the vertex normals for the face to the face normal.
		 */
		virtual void setFaceVertexNormals();
		
		/** Get face data by type.
		 *
		 * Get face data entries of a certain type.
		 *
		 * \param dataType Face data type ID.
		 * \param target Where to store the face data.
		 */
		virtual void getFaceDataByType(Ionflux::GeoUtils::FaceDataTypeID 
		dataType, Ionflux::GeoUtils::VectorSetSet& target);
		
		/** Get face data by type and index..
		 *
		 * Get face data by type and index. This gets the face data record 
		 * that represents the \c index-th occurence of face data of the 
		 * specified type.
		 *
		 * \param dataType Face data type ID.
		 * \param index face data index.
		 *
		 * \return Face data entry, or 0 if no matching face data exists.
		 */
		virtual Ionflux::GeoUtils::FaceData* 
		getFaceDataByType0(Ionflux::GeoUtils::FaceDataTypeID dataType, unsigned 
		int index = 0);
		
		/** Get texture coordinates.
		 *
		 * Get texture coordinates.
		 *
		 * \param target Where to store the face data.
		 */
		virtual void getTexCoords(Ionflux::GeoUtils::VectorSetSet& target);
		
		/** Get texture coordinates.
		 *
		 * Get texture coordinates by index.
		 *
		 * \param index face data index.
		 *
		 * \return .
		 */
		virtual Ionflux::GeoUtils::FaceData* getTexCoords0(unsigned int index = 
		0);
		
		/** Get vertex colors.
		 *
		 * Get vertex colors.
		 *
		 * \param target Where to store the face data.
		 */
		virtual void getVertexColors(Ionflux::GeoUtils::VectorSetSet& target);
		
		/** Get vertex colors.
		 *
		 * Get vertex colors by index.
		 *
		 * \param index face data index.
		 *
		 * \return .
		 */
		virtual Ionflux::GeoUtils::FaceData* getVertexColors0(unsigned int index 
		= 0);
		
		/** Get vertex normals.
		 *
		 * Get vertex normals.
		 *
		 * \param target Where to store the face data.
		 */
		virtual void getVertexNormals(Ionflux::GeoUtils::VectorSetSet& target);
		
		/** Get vertex normals.
		 *
		 * Get vertex normals by index.
		 *
		 * \param index face data index.
		 *
		 * \return .
		 */
		virtual Ionflux::GeoUtils::FaceData* getVertexNormals0(unsigned int index
		= 0);
		
		/** Get face data by vertex.
		 *
		 * Get face data for the vertices specified by the indices in \c 
		 * faceVertexIndices, where each index refers to one vertex of the 
		 * face (not the underlying vertex set).
		 *
		 * \param faceVertexIndices Vertex indices.
		 * \param target Where to store the face data.
		 */
		virtual void getFaceDataByVertex(Ionflux::ObjectBase::UIntVector& 
		faceVertexIndices, Ionflux::GeoUtils::VectorSetSet& target);
		
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
		
		/** .
		 *
		 * Get a polygon corresponding to the (transformed) face. The polygon 
		 * uses copies of the face vertices since polygons may be transformed 
		 * individually.
		 *
		 * \return Polygon corresponding to the face.
		 */
		virtual Ionflux::GeoUtils::Polygon3* getPolygon();
		
		/** Check line intersection.
		 *
		 * Check whether the specified line intersects the object. Returns \c 
		 * true if the line intersects the object, \c false otherwise.
		 *
		 * \param line Line.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, double 
		t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check position relative to plane.
		 *
		 * Check the object position relative to a plane. Unlike checkPlane(),
		 * this function considers the inner structure of the object, not just
		 * its bounding box. Returns 1 if the object is above the plane (in 
		 * direction of the normal of the plane), 0 if the object intersects 
		 * the plane, and -1 if the object is below the plane.
		 *
		 * \param plane Plane.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual int checkPlaneInner(const Ionflux::GeoUtils::Plane3& plane, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check position relative to sphere.
		 *
		 * Check the object position relative to a sphere. Unlike 
		 * checkSphere(), this function considers the inner structure of the 
		 * object, not just its bounding box. Returns 1 if the object is 
		 * inside the sphere, 0 if the object intersects the sphere, and -1 if
		 * the object is outside the sphere.
		 *
		 * \param sphere Sphere.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual int checkSphereInner(const Ionflux::GeoUtils::Sphere3& sphere, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Check box intersection..
		 *
		 * Check whether the specified box intersects the object. Unlike 
		 * checkBox(), this function considers the inner structure of the 
		 * object, not just its bounding box. Returns 1 if the object is 
		 * inside the other box, 0 if the object intersects the other box, and
		 * -1 if the object is outside the other box.
		 *
		 * \param other Box bounds item.
		 * \param t Tolerance.
		 *
		 * \return Result of the comparison.
		 */
		virtual int checkBoxInner(const Ionflux::GeoUtils::BoxBoundsItem& other, 
		double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
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
		 * \return Vector containing triangle faces.
		 */
		virtual Ionflux::GeoUtils::FaceVector getTris0();
		
		/** Get vertex data.
		 *
		 * Get the vertex data for the face vertex with the specified index.
		 *
		 * \param index Vertex index.
		 *
		 * \return Vertex data.
		 */
		virtual Ionflux::GeoUtils::Vertex3* getVertexData(unsigned int index) 
		const;
		
		/** Triangle check.
		 *
		 * Check whether the face is a triangle.
		 *
		 * \return \c true if the face is a triangle, \c false otherwise.
		 */
		virtual bool isTri() const;
		
		/** Quad check.
		 *
		 * Check whether the face is a quad.
		 *
		 * \return \c true if the face is a quad, \c false otherwise.
		 */
		virtual bool isQuad() const;
		
		/** Planar face check.
		 *
		 * Check whether the face is planar.
		 *
		 * \param t Tolerance.
		 *
		 * \return \c true if the face is planar, \c false otherwise.
		 */
		virtual bool isPlanar(double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
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
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Face.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Face& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Face.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Face& other) const;
		
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
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for the face.
		 *
		 * \return Barycenter vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBarycenter();
		
		/** Get bounds.
		 *
		 * Get the bounds for the transformable object.
		 *
		 * \return Bounds.
		 */
		virtual Ionflux::GeoUtils::Range3 getBounds();
		
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
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get XML data representation for vertex indices.
		 *
		 * Get a representation of the vertex indices suitable for use in an 
		 * XML data attribute.
		 *
		 * \return XML data representation of vertex indices.
		 */
		virtual std::string getXMLDataVertices_legacy() const;
		
		/** Get XML data representation for texture coordinates.
		 *
		 * Get a representation of the texture coordinates suitable for use in
		 * an XML data attribute.
		 *
		 * \return XML data representation of UV coordinates.
		 */
		virtual std::string getXMLDataTexCoords_legacy() const;
		
		/** Get XML representation.
		 *
		 * Get an XML representation of the object.
		 *
		 * \return XML representation.
		 */
		virtual std::string getXML_legacy() const;
		
		/** Initialize from XML data.
		 *
		 * Initialize the face from XML data.
		 *
		 * \param vertexData Vertex index data.
		 * \param texCoordData Texture coordinate data.
		 */
		virtual void setFromXMLData_legacy(const std::string& vertexData, const 
		std::string& texCoordData);
		
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
		Ionflux::GeoUtils::Face::VERTEX_INDEX_NONE, 
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
		virtual unsigned int getVertex(unsigned int elementIndex = 0) const;
		
		/** Find vertex.
		 *
		 * Find the specified occurence of a vertex.
		 *
		 * \param needle Vertex to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the vertex, or -1 if the vertex cannot be found.
		 */
		virtual int findVertex(unsigned int needle, unsigned int occurence = 1) 
		const;
        
		/** Get vertex index vector.
		 *
		 * \return vertex index vector.
		 */
		virtual std::vector<unsigned int>& getVertices();
		
		/** Add vertex.
		 *
		 * Add a vertex.
		 *
		 * \param addElement Vertex to be added.
		 */
		virtual void addVertex(unsigned int addElement);
		
		/** Create vertex.
		 *
		 * Create a new vertex which is managed by the vertex set.
		 *
		 * \return New vertex.
		 */
		virtual unsigned int addVertex();
		
		/** Add vertices.
		 *
		 * Add vertices from a vertex vector.
		 *
		 * \param newVertices vertices.
		 */
		virtual void addVertices(const std::vector<unsigned int>& newVertices);
		
		/** Add vertices.
		 *
		 * Add vertices from a vertex set.
		 *
		 * \param newVertices vertices.
		 */
		virtual void addVertices(Ionflux::GeoUtils::Face* newVertices);
		
		/** Remove vertex.
		 *
		 * Remove a vertex.
		 *
		 * \param removeElement Vertex to be removed.
		 */
		virtual void removeVertex(unsigned int removeElement);
		
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
		
		/** Get face data.
		 *
		 * \return Current value of face data.
		 */
		virtual Ionflux::GeoUtils::VectorSetSet* getFaceData() const;
		
		/** Set face data.
		 *
		 * Set new value of face data.
		 *
		 * \param newFaceData New value of face data.
		 */
		virtual void setFaceData(Ionflux::GeoUtils::VectorSetSet* newFaceData);
};

}

}

/** \file Face.hpp
 * \brief Mesh face (header).
 */
#endif
