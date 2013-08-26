#ifndef IONFLUX_GEOUTILS_ARRAY
#define IONFLUX_GEOUTILS_ARRAY
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Array.hpp                       Transform node: Array (header).
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
#include "geoutils/Range.hpp"
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Array.
class ArrayClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ArrayClassInfo();
		/// Destructor.
		virtual ~ArrayClassInfo();
};

/** Transform node: Array.
 * \ingroup geoutils
 *
 * Arrange elements from the input group in rows and columns of the 
 * specified dimensions within the XY plane. The array is centered around 
 * the origin, translated by the offset vector.
 */
class Array
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Offset.
		Ionflux::GeoUtils::Vector3 offset;
		/// Number of rows.
		unsigned int numRows;
		/// Number of columns.
		unsigned int numColumns;
		/// cell width.
		double cellWidth;
		/// cell height.
		double cellHeight;
		
		/** Process inputs.
		 *
		 * Update the outputs of the node by processing the inputs. This 
		 * should be implemented by derived classes.
		 */
		virtual void process();
		
	public:
		/// Input ID: source.
		static const unsigned int INPUT_SOURCE;
		/// Output ID: target.
		static const unsigned int OUTPUT_TARGET;
		/// Default number of rows.
		static const unsigned int DEFAULT_NUM_ROWS;
		/// Default number of columns.
		static const unsigned int DEFAULT_NUM_COLUMNS;
		/// Default cell width.
		static const double DEFAULT_CELL_WIDTH;
		/// Default cell height.
		static const double DEFAULT_CELL_HEIGHT;
		/// Class information instance.
		static const ArrayClassInfo arrayClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Array object.
		 */
		Array();
		
		/** Constructor.
		 *
		 * Construct new Array object.
		 *
		 * \param other Other object.
		 */
		Array(const Ionflux::GeoUtils::TransformNodes::Array& other);
		
		/** Constructor.
		 *
		 * Construct new Array object.
		 *
		 * \param initNumRows Number of rows.
		 * \param initNumColumns Number of columns.
		 * \param initCellWidth Cell width.
		 * \param initCellHeight Cell height.
		 * \param initOffset Offset.
		 * \param nodeID Node ID.
		 */
		Array(unsigned int initNumRows, unsigned int initNumColumns = 
		DEFAULT_NUM_COLUMNS, double initCellWidth = DEFAULT_CELL_WIDTH, double 
		initCellHeight = DEFAULT_CELL_HEIGHT, const Ionflux::GeoUtils::Vector3& 
		initOffset = GeoUtils::Vector3::ZERO, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct Array object.
		 */
		virtual ~Array();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Array& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Array& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Array* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Array* 
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
		static Ionflux::GeoUtils::TransformNodes::Array* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get offset.
		 *
		 * \return Current value of offset.
		 */
		virtual Ionflux::GeoUtils::Vector3 getOffset() const;
		
		/** Set offset.
		 *
		 * Set new value of offset.
		 *
		 * \param newOffset New value of offset.
		 */
		virtual void setOffset(const Ionflux::GeoUtils::Vector3& newOffset);
		
		/** Get number of rows.
		 *
		 * \return Current value of number of rows.
		 */
		virtual unsigned int getNumRows() const;
		
		/** Set number of rows.
		 *
		 * Set new value of number of rows.
		 *
		 * \param newNumRows New value of number of rows.
		 */
		virtual void setNumRows(unsigned int newNumRows);
		
		/** Get number of columns.
		 *
		 * \return Current value of number of columns.
		 */
		virtual unsigned int getNumColumns() const;
		
		/** Set number of columns.
		 *
		 * Set new value of number of columns.
		 *
		 * \param newNumColumns New value of number of columns.
		 */
		virtual void setNumColumns(unsigned int newNumColumns);
		
		/** Get cell width.
		 *
		 * \return Current value of cell width.
		 */
		virtual double getCellWidth() const;
		
		/** Set cell width.
		 *
		 * Set new value of cell width.
		 *
		 * \param newCellWidth New value of cell width.
		 */
		virtual void setCellWidth(double newCellWidth);
		
		/** Get cell height.
		 *
		 * \return Current value of cell height.
		 */
		virtual double getCellHeight() const;
		
		/** Set cell height.
		 *
		 * Set new value of cell height.
		 *
		 * \param newCellHeight New value of cell height.
		 */
		virtual void setCellHeight(double newCellHeight);
};

}

}

}

/** \file Array.hpp
 * \brief Transform node: Array (header).
 */
#endif
