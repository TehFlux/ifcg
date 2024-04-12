#ifndef IONFLUX_GEOUTILS_VERTEXARRAYOBJECT
#define IONFLUX_GEOUTILS_VERTEXARRAYOBJECT
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VertexArrayObject.hpp           Vertex array object (OpenGL) (header).
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

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ifobject/types.hpp"
#include "altjira/ColorSet.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/gltypes.hpp"
#include "geoutils/glconstants.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class VertexAttribute;

/// Class information for class VertexArrayObject.
class VertexArrayObjectClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		VertexArrayObjectClassInfo();
		/// Destructor.
		virtual ~VertexArrayObjectClassInfo();
};

/** Vertex array object (OpenGL).
 * \ingroup ifvg
 *
 * An OpenGL vertex array object.
 */
class VertexArrayObject
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Vertex array object implementation (OpenGL).
		GLuint vaoImpl;
		/// Vector of vertex attributes.
		std::vector<Ionflux::GeoUtils::VertexAttribute*> attributes;
		
		/** Set vertex array object implementation (OpenGL).
		 *
		 * Set new value of vertex array object implementation (OpenGL).
		 *
		 * \param newVaoImpl New value of vertex array object implementation 
		 * (OpenGL).
		 */
		virtual void setVaoImpl(GLuint newVaoImpl);
		
	public:
		/// Class information instance.
		static const VertexArrayObjectClassInfo vertexArrayObjectClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new VertexArrayObject object.
		 */
		VertexArrayObject();
		
		/** Constructor.
		 *
		 * Construct new VertexArrayObject object.
		 *
		 * \param other Other object.
		 */
		VertexArrayObject(const Ionflux::GeoUtils::VertexArrayObject& other);
		
		/** Destructor.
		 *
		 * Destruct VertexArrayObject object.
		 */
		virtual ~VertexArrayObject();
		
		/** Clean up.
		 *
		 * Clean up state maintained by the vertex array object.
		 */
		virtual void cleanup();
		
		/** Initialize.
		 *
		 * Initialize the vertex attribute.
		 */
		virtual void init();
		
		/** Bind.
		 *
		 * Bind the OpenGL vertex array object.
		 */
		virtual void bind();
		
		/** Update.
		 *
		 * Update the OpenGL vertex array object with the current set of 
		 * vertex attributes.
		 */
		virtual void update();
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
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
		virtual Ionflux::GeoUtils::VertexArrayObject& operator=(const 
		Ionflux::GeoUtils::VertexArrayObject& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::VertexArrayObject* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::VertexArrayObject* 
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
		static Ionflux::GeoUtils::VertexArrayObject* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get vertex array object implementation (OpenGL).
		 *
		 * \return Current value of vertex array object implementation (OpenGL).
		 */
		virtual GLuint getVaoImpl() const;
		
		/** Get number of attributes.
		 *
		 * \return Number of attributes.
		 */
		virtual unsigned int getNumAttributes() const;
		
		/** Get attribute.
		 *
		 * Get the attribute at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Attribute at specified index.
		 */
		virtual Ionflux::GeoUtils::VertexAttribute* getAttribute(unsigned int 
		elementIndex = 0) const;
		
		/** Find attribute.
		 *
		 * Find the specified occurence of a attribute.
		 *
		 * \param needle Attribute to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the attribute, or -1 if the attribute cannot be 
		 * found.
		 */
		virtual int findAttribute(Ionflux::GeoUtils::VertexAttribute* needle, 
		unsigned int occurence = 1) const;
        
		/** Get vector of vertex attributes.
		 *
		 * \return vector of vertex attributes.
		 */
		virtual std::vector<Ionflux::GeoUtils::VertexAttribute*>& 
		getAttributes();
		
		/** Add attribute.
		 *
		 * Add a attribute.
		 *
		 * \param addElement Attribute to be added.
		 */
		virtual void addAttribute(Ionflux::GeoUtils::VertexAttribute* 
		addElement);
		
		/** Create attribute.
		 *
		 * Create a new attribute which is managed by the attribute set.
		 *
		 * \return New attribute.
		 */
		virtual Ionflux::GeoUtils::VertexAttribute* addAttribute();
		
		/** Add attributes.
		 *
		 * Add attributes from a attribute vector.
		 *
		 * \param newAttributes attributes.
		 */
		virtual void addAttributes(const 
		std::vector<Ionflux::GeoUtils::VertexAttribute*>& newAttributes);
		
		/** Add attributes.
		 *
		 * Add attributes from a attribute set.
		 *
		 * \param newAttributes attributes.
		 */
		virtual void addAttributes(Ionflux::GeoUtils::VertexArrayObject* 
		newAttributes);
		
		/** Remove attribute.
		 *
		 * Remove a attribute.
		 *
		 * \param removeElement Attribute to be removed.
		 */
		virtual void removeAttribute(Ionflux::GeoUtils::VertexAttribute* 
		removeElement);
		
		/** Remove attribute.
		 *
		 * Remove a attribute.
		 *
		 * \param removeIndex Attribute to be removed.
		 */
		virtual void removeAttributeIndex(unsigned int removeIndex);
		
		/** Clear attributes.
		 *
		 * Clear all attributes.
		 */
		virtual void clearAttributes();
};

}

}

/** \file VertexArrayObject.hpp
 * \brief Vertex array object (OpenGL) (header).
 */
#endif
