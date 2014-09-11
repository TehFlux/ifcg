#ifndef IONFLUX_GEOUTILS_MESH
#define IONFLUX_GEOUTILS_MESH
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Mesh.hpp                        Mesh (header).
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

#include "geoutils/Face.hpp"
#include "geoutils/FaceCompare.hpp"
#include "geoutils/Polygon3Set.hpp"
#include "geoutils/BoxBoundsItem.hpp"
#include "geoutils/ItemSource.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class MeshXMLFactory;

}

/// Class information for class Mesh.
class MeshClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		MeshClassInfo();
		/// Destructor.
		virtual ~MeshClassInfo();
};

/** Mesh.
 * \ingroup geoutils
 *
 * A mesh.
 */
class Mesh
: virtual public Ionflux::GeoUtils::BoxBoundsItem, virtual public 
Ionflux::GeoUtils::ItemSource, virtual public 
Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// Vertex source.
		Ionflux::GeoUtils::Vertex3Set* vertexSource;
		/// Face vector.
		std::vector<Ionflux::GeoUtils::Face*> faces;
		/// Edge vector.
		std::vector<Ionflux::GeoUtils::NFace*> edges;
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the polygon set.
		 */
		virtual void recalculateBounds();
		
	public:
		/// Default ID.
		static const std::string DEFAULT_ID;
		/// Mesh type: undefined.
		static const Ionflux::GeoUtils::MeshTypeID TYPE_UNDEFINED;
		/// Mesh type: mixed.
		static const Ionflux::GeoUtils::MeshTypeID TYPE_MIXED;
		/// Mesh type: tri.
		static const Ionflux::GeoUtils::MeshTypeID TYPE_TRI;
		/// Mesh type: quad.
		static const Ionflux::GeoUtils::MeshTypeID TYPE_QUAD;
		/// Class information instance.
		static const MeshClassInfo meshClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new Mesh object.
		 */
		Mesh();
		
		/** Constructor.
		 *
		 * Construct new Mesh object.
		 *
		 * \param other Other object.
		 */
		Mesh(const Ionflux::GeoUtils::Mesh& other);
		
		/** Constructor.
		 *
		 * Construct new Mesh object.
		 *
		 * \param initVerts Vertex vector.
		 * \param initFaces Face vector.
		 */
		Mesh(Ionflux::GeoUtils::Vertex3Vector* initVerts, const 
		Ionflux::GeoUtils::FaceVector* initFaces);
		
		/** Constructor.
		 *
		 * Construct new Mesh object.
		 *
		 * \param initVertexSource Vertex source.
		 * \param initFaces Face vector.
		 */
		Mesh(Ionflux::GeoUtils::Vertex3Set* initVertexSource, const 
		Ionflux::GeoUtils::FaceVector* initFaces);
		
		/** Destructor.
		 *
		 * Destruct Mesh object.
		 */
		virtual ~Mesh();
		
		/** Get bounds.
		 *
		 * Get the bounds for the transformable object.
		 *
		 * \return Bounds.
		 */
		virtual Ionflux::GeoUtils::Range3 getBounds();
		
		/** Copy vertices.
		 *
		 * Create a new vertex set with copies of the current vertices. This 
		 * makes the mesh the (current) single owner of its vertices.
		 */
		virtual void copyVertices();
		
		/** Update.
		 *
		 * Update all state according to the faces of the mesh.
		 *
		 * \param updateFaces update faces.
		 * \param updateEdges update edges.
		 */
		virtual void update(bool updateFaces = true, bool updateEdges = true);
		
		/** Clear.
		 *
		 * Removes all items and resets state.
		 */
		virtual void clear();
		
		/** Clear data.
		 *
		 * Clears the mesh data but keeps the vertex source.
		 */
		virtual void clearData();
		
		/** Set face IDs.
		 *
		 * Set the item IDs of the faces. This is useful for saving and 
		 * restoring the bounding box hierarchy, if one has been created.
		 */
		virtual void setFaceIDs();
		
		/** Set edge IDs.
		 *
		 * Set the item IDs of the edges. This is useful for saving and 
		 * restoring the bounding box hierarchy, if one has been created.
		 */
		virtual void setEdgeIDs();
		
		/** Get item.
		 *
		 * Return the item with the specified ID. Throws an error if no valid 
		 * BoxBoundsItem can be returned. The ItemSource class does not 
		 * provide a usable implementation of this function, so it has to be 
		 * provided in a derived class.
		 *
		 * \param itemID Item ID.
		 *
		 * \return Item with the specified ID, or 0 if no matching item exists.
		 */
		virtual Ionflux::GeoUtils::BoxBoundsItem* getItem(const std::string& 
		itemID);
		
		/** Get N-face.
		 *
		 * Get the mesh N-face of the specified type with the specified index.
		 *
		 * \param typeID N-face type ID.
		 * \param index index.
		 *
		 * \return N-face with the specified type and index, or 0 if no matching 
		 * N-face exists.
		 */
		virtual Ionflux::GeoUtils::NFace* getNFace(Ionflux::GeoUtils::NFaceTypeID
		typeID, unsigned int index) const;
		
		/** Get number of N-faces.
		 *
		 * Get the number of mesh N-faces of the specified type.
		 *
		 * \param typeID N-face type ID.
		 *
		 * \return Number of N-faces of the specified type.
		 */
		virtual unsigned int getNumNFaces(Ionflux::GeoUtils::NFaceTypeID typeID) 
		const;
		
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
		
		/** Check line intersection.
		 *
		 * Check whether the specified line intersects the object. Unlike 
		 * checkLine(), this function considers the inner structure of the 
		 * object, not just its bounding box. Returns \c true if the line 
		 * intersects the object, \c false otherwise.
		 *
		 * \param line Line.
		 * \param t Tolerance.
		 *
		 * \return Result of the test.
		 */
		virtual bool checkLineInner(const Ionflux::GeoUtils::Line3& line, double 
		t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
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
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Mesh.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const Ionflux::GeoUtils::Mesh& other) const;
		
		/** Comparison operator: inequality.
		 *
		 * Compare inequality.
		 *
		 * \param other Mesh.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const Ionflux::GeoUtils::Mesh& other) const;
		
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
		virtual Ionflux::GeoUtils::Mesh& scale(const Ionflux::GeoUtils::Vector3& 
		s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Mesh& translate(const 
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
		virtual Ionflux::GeoUtils::Mesh& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Swap axes.
		 *
		 * Swap axes.
		 *
		 * \param x Axis (x).
		 * \param y Axis (y).
		 * \param z Axis (z).
		 * \param w Axis (w).
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Mesh& swapAxes(Ionflux::GeoUtils::AxisID x = 
		Ionflux::GeoUtils::AXIS_X, Ionflux::GeoUtils::AxisID y = 
		Ionflux::GeoUtils::AXIS_Y, Ionflux::GeoUtils::AxisID z = 
		Ionflux::GeoUtils::AXIS_Z, Ionflux::GeoUtils::AxisID w = 
		Ionflux::GeoUtils::AXIS_W);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Mesh& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Mesh& 
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
		virtual Ionflux::GeoUtils::Mesh& transform(const 
		Ionflux::GeoUtils::Matrix4& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::Mesh& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::Mesh& duplicate();
		
		/** Get face polygons.
		 *
		 * Get the face polygons of the (transformed) mesh.
		 *
		 * \param target Where to store the polygons.
		 */
		virtual void getFacePolygons(Ionflux::GeoUtils::Polygon3Set& target);
		
		/** Get edge polygons.
		 *
		 * Get the edge polygons of the (transformed) mesh.
		 *
		 * \param target Where to store the polygons.
		 */
		virtual void getEdgePolygons(Ionflux::GeoUtils::Polygon3Set& target);
		
		/** Remove backfaces.
		 *
		 * Remove faces that face backward relative to the specified front 
		 * vector.
		 *
		 * \param front Front vector.
		 */
		virtual void removeBackfaces(const Ionflux::GeoUtils::Vector3& front);
		
		/** Sort faces.
		 *
		 * Sort faces in the set. If no comparison function is specified, 
		 * faces are sorted according to the Z-axis order of their 
		 * barycenters. \c compFunc will be managed by a temporary object so 
		 * it is possible to create a new instance of a comparison function 
		 * within the call.
		 *
		 * \param compFunc Comparison function.
		 */
		virtual void sortFaces(Ionflux::GeoUtils::FaceCompare* compFunc = 0);
		
		/** Make faces planar.
		 *
		 * Make the faces with the specified indices planar. If the optional 
		 * parameter is specified, vertices will be moved only by the 
		 * specified fraction of the offset required to make the face planar.
		 *
		 * \param indices face indices.
		 * \param maxIterations maximum number of iterations.
		 * \param p Parameter.
		 * \param t Tolerance.
		 *
		 * \return number of non-planar faces remaining.
		 */
		virtual unsigned int makePlanar(const Ionflux::ObjectBase::UIntVector& 
		indices, unsigned int maxIterations = 10000, double p = 1., double t = 
		Ionflux::GeoUtils::DEFAULT_TOLERANCE);
		
		/** Make triangle faces.
		 *
		 * Convert all faces in the mesh to triangles, creating new faces as 
		 * necessary. Existing triangle faces will not be changed.
		 *
		 * \return Number of new faces that were generated.
		 */
		virtual unsigned int makeTris();
		
		/** Set face vertex normals.
		 *
		 * Set the vertex normals for all faces to the face normal.
		 *
		 * \param flip0 flip normals.
		 */
		virtual void setFaceVertexNormals(bool flip0 = false);
		
		/** Set face vertex colors.
		 *
		 * Set the vertex colors for all faces to the specified color vector.
		 *
		 * \param color color vector.
		 */
		virtual void setFaceVertexColors(const Ionflux::GeoUtils::Vector4& 
		color);
		
		/** Get mesh type.
		 *
		 * Get the mesh type.
		 *
		 * \return Mesh type.
		 */
		virtual Ionflux::GeoUtils::MeshTypeID getMeshType() const;
		
		/** Triangle mesh check.
		 *
		 * Check whether all faces of the mesh are triangles.
		 *
		 * \return \c true if the mesh is a triangle mesh, \c false otherwise.
		 */
		virtual bool isTriMesh() const;
		
		/** Create edges.
		 *
		 * Create the unique edges defined by the mesh faces and add them to 
		 * the mesh. Any existing edges will be cleared.
		 *
		 * \return Number of new edges that were generated.
		 */
		virtual unsigned int createEdges();
		
		/** Merge.
		 *
		 * Merge another mesh into the mesh.
		 *
		 * \param other mesh.
		 */
		virtual void merge(Ionflux::GeoUtils::Mesh& other);
		
		/** Write OBJ data.
		 *
		 * Write OBJ data for the mesh.
		 *
		 * \param ioCtx I/O context.
		 * \param precision decimal precision.
		 * \param smoothShading smooth shading.
		 */
		virtual void writeOBJ(Ionflux::ObjectBase::IFIOContext& ioCtx, unsigned 
		int precision = 6, bool smoothShading = false);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Create mesh: plane.
		 *
		 * Create a plane mesh.
		 *
		 * \return Plane mesh.
		 */
		static Ionflux::GeoUtils::Mesh* plane();
		
		/** Create mesh: cube.
		 *
		 * Create a cube mesh.
		 *
		 * \return Cube mesh.
		 */
		static Ionflux::GeoUtils::Mesh* cube();
		
		/** Create mesh: cylinder.
		 *
		 * Create a cylinder mesh.
		 *
		 * \param subDivs Angular subdivisions.
		 * \param length Length.
		 * \param radius Radius.
		 *
		 * \return Cylinder mesh.
		 */
		static Ionflux::GeoUtils::Mesh* cylinder(unsigned int subDivs = 10, 
		double length = 1., double radius = 0.5);
		
		/** Create mesh: arrow.
		 *
		 * Create an arrow mesh.
		 *
		 * \param subDivs Angular subdivisions.
		 * \param length Length.
		 * \param radius Radius.
		 * \param headLength Head length (relative to length).
		 * \param headRadius Head radius (relative to radius).
		 *
		 * \return Arrow mesh.
		 */
		static Ionflux::GeoUtils::Mesh* arrow(unsigned int subDivs = 10, double 
		length = 1., double radius = 0.005, double headLength = 0.1, double 
		headRadius = 4.);
		
		/** Create mesh: grid.
		 *
		 * Create a planar grid mesh.
		 *
		 * \param subDivsX subdivisions (x).
		 * \param subDivsY subdivisions (y).
		 *
		 * \return Grid mesh.
		 */
		static Ionflux::GeoUtils::Mesh* grid(unsigned int subDivsX = 10, unsigned
		int subDivsY = 10);
		
		/** Create mesh: fiber.
		 *
		 * Create a fiber mesh.
		 *
		 * \param aSubDivs Angular subdivisions.
		 * \param lSubDivs Length subdivisions.
		 * \param length Length.
		 * \param radius Radius.
		 *
		 * \return Fiber mesh.
		 */
		static Ionflux::GeoUtils::Mesh* fiber(unsigned int aSubDivs = 10, 
		unsigned int lSubDivs = 10, double length = 1., double radius = 0.05);
		
		/** Get mesh type ID string.
		 *
		 * Get a string representation for a mesh type ID.
		 *
		 * \param typeID Mesh type ID.
		 *
		 * \return String representation.
		 */
		static std::string getMeshTypeIDString(Ionflux::GeoUtils::MeshTypeID 
		typeID);
		
		/** Get number of vertices per face.
		 *
		 * Get number of vertices per face for a mesh type ID.
		 *
		 * \param typeID Mesh type ID.
		 *
		 * \return Number of vertices per face for the specified mesh type, or 0 
		 * if the number of vertices per face is undefined.
		 */
		static unsigned int getNumVerticesPerFace(Ionflux::GeoUtils::MeshTypeID 
		typeID);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::Mesh& operator=(const Ionflux::GeoUtils::Mesh&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::Mesh* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::Mesh* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::GeoUtils::Mesh* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Mesh object.
		 *
		 * \param initVerts Vertex vector.
		 * \param initFaces Face vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Mesh* create(Ionflux::GeoUtils::Vertex3Vector* 
		initVerts, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new Mesh object.
		 *
		 * \param initVertexSource Vertex source.
		 * \param initFaces Face vector.
		 * \param parentObject Parent object.
		 */
		static Ionflux::GeoUtils::Mesh* create(Ionflux::GeoUtils::Vertex3Set* 
		initVertexSource, const Ionflux::GeoUtils::FaceVector* initFaces, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		 * \param newVertices vertices.
		 */
		virtual void addVertices(const std::vector<Ionflux::GeoUtils::Vertex3*>& 
		newVertices);
		
		/** Add vertices.
		 *
		 * Add vertices from a vertex set.
		 *
		 * \param newVertices vertices.
		 */
		virtual void addVertices(Ionflux::GeoUtils::Mesh* newVertices);
		
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
		
		/** Get number of faces.
		 *
		 * \return Number of faces.
		 */
		virtual unsigned int getNumFaces() const;
		
		/** Get face.
		 *
		 * Get the face at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Face at specified index.
		 */
		virtual Ionflux::GeoUtils::Face* getFace(unsigned int elementIndex = 0) 
		const;
		
		/** Find face.
		 *
		 * Find the specified occurence of a face.
		 *
		 * \param needle Face to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the face, or -1 if the face cannot be found.
		 */
		virtual int findFace(Ionflux::GeoUtils::Face* needle, unsigned int 
		occurence = 1) const;
        
		/** Get face vector.
		 *
		 * \return face vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::Face*>& getFaces();
		
		/** Add face.
		 *
		 * Add a face.
		 *
		 * \param addElement Face to be added.
		 */
		virtual void addFace(Ionflux::GeoUtils::Face* addElement);
		
		/** Create face.
		 *
		 * Create a new face which is managed by the face set.
		 *
		 * \return New face.
		 */
		virtual Ionflux::GeoUtils::Face* addFace();
		
		/** Add faces.
		 *
		 * Add faces from a face vector.
		 *
		 * \param newFaces faces.
		 */
		virtual void addFaces(const std::vector<Ionflux::GeoUtils::Face*>& 
		newFaces);
		
		/** Add faces.
		 *
		 * Add faces from a face set.
		 *
		 * \param newFaces faces.
		 */
		virtual void addFaces(Ionflux::GeoUtils::Mesh* newFaces);
		
		/** Remove face.
		 *
		 * Remove a face.
		 *
		 * \param removeElement Face to be removed.
		 */
		virtual void removeFace(Ionflux::GeoUtils::Face* removeElement);
		
		/** Remove face.
		 *
		 * Remove a face.
		 *
		 * \param removeIndex Face to be removed.
		 */
		virtual void removeFaceIndex(unsigned int removeIndex);
		
		/** Clear faces.
		 *
		 * Clear all faces.
		 */
		virtual void clearFaces();
		
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
		virtual Ionflux::GeoUtils::NFace* getEdge(unsigned int elementIndex = 0) 
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
		virtual int findEdge(Ionflux::GeoUtils::NFace* needle, unsigned int 
		occurence = 1) const;
        
		/** Get edge vector.
		 *
		 * \return edge vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::NFace*>& getEdges();
		
		/** Add edge.
		 *
		 * Add a edge.
		 *
		 * \param addElement Edge to be added.
		 */
		virtual void addEdge(Ionflux::GeoUtils::NFace* addElement);
		
		/** Create edge.
		 *
		 * Create a new edge which is managed by the edge set.
		 *
		 * \return New edge.
		 */
		virtual Ionflux::GeoUtils::NFace* addEdge();
		
		/** Add edges.
		 *
		 * Add edges from a edge vector.
		 *
		 * \param newEdges edges.
		 */
		virtual void addEdges(const std::vector<Ionflux::GeoUtils::NFace*>& 
		newEdges);
		
		/** Add edges.
		 *
		 * Add edges from a edge set.
		 *
		 * \param newEdges edges.
		 */
		virtual void addEdges(Ionflux::GeoUtils::Mesh* newEdges);
		
		/** Remove edge.
		 *
		 * Remove a edge.
		 *
		 * \param removeElement Edge to be removed.
		 */
		virtual void removeEdge(Ionflux::GeoUtils::NFace* removeElement);
		
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

/** \file Mesh.hpp
 * \brief Mesh (header).
 */
#endif
