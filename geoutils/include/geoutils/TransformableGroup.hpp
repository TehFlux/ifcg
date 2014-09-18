#ifndef IONFLUX_GEOUTILS_TRANSFORMABLEGROUP
#define IONFLUX_GEOUTILS_TRANSFORMABLEGROUP
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformableGroup.hpp          Transformable object group (header).
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
#include "geoutils/Range3.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace XMLUtils
{

class TransformableGroupXMLFactory;

}

/// Class information for class TransformableGroup.
class TransformableGroupClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		TransformableGroupClassInfo();
		/// Destructor.
		virtual ~TransformableGroupClassInfo();
};

/** Transformable object group.
 * \ingroup geoutils
 *
 * A group of transformable objects that is itself a transformable object. 
 * This allows to build hierarchies of transformable objects.
 */
class TransformableGroup
: public Ionflux::GeoUtils::TransformableObject
{
	private:
		
	protected:
		/// Item vector.
		std::vector<Ionflux::GeoUtils::TransformableObject*> items;
		
		/** Recalculate bounds.
		 *
		 * Recalculate the bounds for the group.
		 */
		virtual void recalculateBounds();
		
	public:
		/// Class information instance.
		static const TransformableGroupClassInfo transformableGroupClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		/// XML element name.
		static const std::string XML_ELEMENT_NAME;
		
		/** Constructor.
		 *
		 * Construct new TransformableGroup object.
		 */
		TransformableGroup();
		
		/** Constructor.
		 *
		 * Construct new TransformableGroup object.
		 *
		 * \param other Other object.
		 */
		TransformableGroup(const Ionflux::GeoUtils::TransformableGroup& other);
		
		/** Destructor.
		 *
		 * Destruct TransformableGroup object.
		 */
		virtual ~TransformableGroup();
		
		/** Clear.
		 *
		 * Removes all items and resets state.
		 */
		virtual void clear();
		
		/** Apply transformations.
		 *
		 * Apply transformations that have been accumulated in the 
		 * transformation matrices. The tolerance is used to compare matrices 
		 * against the identity matrix and avoid unnecessary transformations.
		 *
		 * \param recursive Apply transformations recursively.
		 */
		virtual void applyTransform(bool recursive = false);
		
		/** Get barycenter.
		 *
		 * Get the barycenter vector for all polygons.
		 *
		 * \return Barycenter vector.
		 */
		virtual Ionflux::GeoUtils::Vector3 getBarycenter() const;
		
		/** Scale.
		 *
		 * Scale the object by the specified scale factors.
		 *
		 * \param s Vector of scale factors.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup& scale(const 
		Ionflux::GeoUtils::Vector3& s);
		
		/** Translate.
		 *
		 * Translate the object by the specified vector.
		 *
		 * \param t Translation vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup& translate(const 
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
		virtual Ionflux::GeoUtils::TransformableGroup& rotate(double phi, 
		Ionflux::GeoUtils::AxisID axis = Ionflux::GeoUtils::AXIS_Z);
		
		/** Normalize.
		 *
		 * Normalize the object, i.e. scale to unit size.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup& normalize();
		
		/** Center.
		 *
		 * Center the object using the specified method and origin vector.
		 *
		 * \param method Centering method.
		 * \param origin Origin or offset vector.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup& 
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
		virtual Ionflux::GeoUtils::TransformableGroup& transform(const 
		Ionflux::GeoUtils::Matrix3& matrix);
		
		/** Matrix transformation.
		 *
		 * Apply a transformation matrix to the object.
		 *
		 * \param matrix Transformation matrix.
		 *
		 * \return The transformed object.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup& transform(const 
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
		virtual Ionflux::GeoUtils::TransformableGroup& transformVI(const 
		Ionflux::GeoUtils::Matrix4& view, const Ionflux::GeoUtils::Matrix4* image
		= 0);
		
		/** Duplicate.
		 *
		 * Create an exact duplicate of the object. The duplicate is a new 
		 * object which must be managed by the caller.
		 *
		 * \return The duplicated object.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup& duplicate();
		
		/** Flatten hierarchy.
		 *
		 * Flatten the hierarchy starting at this group by finding all leaf 
		 * items and replacing the items in the group with the set of leaf 
		 * items.
		 *
		 * \return The group containing leaf items only.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup& flatten();
		
		/** Get leaf items.
		 *
		 * Get leaf items of the group hierarchy starting at this group, i.e. 
		 * all items that are not themselves groups. The leaf items are added 
		 * to the specified transformable group.
		 *
		 * \param target Target group.
		 * \param level Recursion level.
		 */
		virtual void getLeafItems(Ionflux::GeoUtils::TransformableGroup& target, 
		unsigned int level = 0);
		
		/** Get debugging information.
		 *
		 * Get a representation of the group and its contents that is usable 
		 * for debugging.
		 *
		 * \param expand Display information about non-group items.
		 * \param level Recursion level.
		 *
		 * \return Debugging information.
		 */
		virtual std::string getDebugInfo(bool expand = true, unsigned int level =
		0);
		
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
		virtual Ionflux::GeoUtils::TransformableGroup& operator=(const 
		Ionflux::GeoUtils::TransformableGroup& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformableGroup* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformableGroup* 
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
		static Ionflux::GeoUtils::TransformableGroup* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
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
		 * \param elementName element name
		 */
		virtual void loadFromXMLFile(const std::string& fileName, const 
		std::string& elementName = "");
        
        /** Get XML object factory
		 *
		 * Get the XML object factory singleton for the class.
		 * 
		 * return XML object factory
		 */
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		
		/** Get number of items.
		 *
		 * \return Number of items.
		 */
		virtual unsigned int getNumItems() const;
		
		/** Get item.
		 *
		 * Get the item at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Item at specified index.
		 */
		virtual Ionflux::GeoUtils::TransformableObject* getItem(unsigned int 
		elementIndex = 0) const;
		
		/** Find item.
		 *
		 * Find the specified occurence of a item.
		 *
		 * \param needle Item to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the item, or -1 if the item cannot be found.
		 */
		virtual int findItem(Ionflux::GeoUtils::TransformableObject* needle, 
		unsigned int occurence = 1) const;
        
		/** Get item vector.
		 *
		 * \return item vector.
		 */
		virtual std::vector<Ionflux::GeoUtils::TransformableObject*>& getItems();
		
		/** Add item.
		 *
		 * Add a item.
		 *
		 * \param addElement Item to be added.
		 */
		virtual void addItem(Ionflux::GeoUtils::TransformableObject* addElement);
		
		/** Create item.
		 *
		 * Create a new item which is managed by the item set.
		 *
		 * \return New item.
		 */
		virtual Ionflux::GeoUtils::TransformableObject* addItem();
		
		/** Add items.
		 *
		 * Add items from a item vector.
		 *
		 * \param newItems items.
		 */
		virtual void addItems(const 
		std::vector<Ionflux::GeoUtils::TransformableObject*>& newItems);
		
		/** Add items.
		 *
		 * Add items from a item set.
		 *
		 * \param newItems items.
		 */
		virtual void addItems(Ionflux::GeoUtils::TransformableGroup* newItems);
		
		/** Remove item.
		 *
		 * Remove a item.
		 *
		 * \param removeElement Item to be removed.
		 */
		virtual void removeItem(Ionflux::GeoUtils::TransformableObject* 
		removeElement);
		
		/** Remove item.
		 *
		 * Remove a item.
		 *
		 * \param removeIndex Item to be removed.
		 */
		virtual void removeItemIndex(unsigned int removeIndex);
		
		/** Clear items.
		 *
		 * Clear all items.
		 */
		virtual void clearItems();
};

}

}

/** \file TransformableGroup.hpp
 * \brief Transformable object group (header).
 */
#endif
