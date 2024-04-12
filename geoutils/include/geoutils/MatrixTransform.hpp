#ifndef IONFLUX_GEOUTILS_MATRIXTRANSFORM
#define IONFLUX_GEOUTILS_MATRIXTRANSFORM
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * MatrixTransform.hpp             Transform node: Matrix transform 
 * (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/TransformNode.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class MatrixTransform.
class MatrixTransformClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		MatrixTransformClassInfo();
		/// Destructor.
		virtual ~MatrixTransformClassInfo();
};

/** Transform node: Matrix transform.
 * \ingroup geoutils
 *
 * Transform elements from the input group using the specified matrix.
 */
class MatrixTransform
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
	private:
		
	protected:
		/// Transformation matrix.
		Ionflux::GeoUtils::Matrix4 matrix;
		
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
		/// Class information instance.
		static const MatrixTransformClassInfo matrixTransformClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new MatrixTransform object.
		 */
		MatrixTransform();
		
		/** Constructor.
		 *
		 * Construct new MatrixTransform object.
		 *
		 * \param other Other object.
		 */
		MatrixTransform(const Ionflux::GeoUtils::TransformNodes::MatrixTransform& other);
		
		/** Constructor.
		 *
		 * Construct new MatrixTransform object.
		 *
		 * \param initMatrix Transformation matrix.
		 * \param nodeID Node ID.
		 */
		MatrixTransform(const Ionflux::GeoUtils::Matrix4& initMatrix, const 
		Ionflux::ObjectBase::IFObjectID& nodeID = "");
		
		/** Destructor.
		 *
		 * Destruct MatrixTransform object.
		 */
		virtual ~MatrixTransform();
		
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
		virtual Ionflux::GeoUtils::TransformNodes::MatrixTransform& 
		operator=(const Ionflux::GeoUtils::TransformNodes::MatrixTransform& 
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::MatrixTransform* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
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
		static Ionflux::GeoUtils::TransformNodes::MatrixTransform* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get transformation matrix.
		 *
		 * \return Current value of transformation matrix.
		 */
		virtual Ionflux::GeoUtils::Matrix4 getMatrix() const;
		
		/** Set transformation matrix.
		 *
		 * Set new value of transformation matrix.
		 *
		 * \param newMatrix New value of transformation matrix.
		 */
		virtual void setMatrix(const Ionflux::GeoUtils::Matrix4& newMatrix);
};

}

}

}

/** \file MatrixTransform.hpp
 * \brief Transform node: Matrix transform (header).
 */
#endif
