#ifndef IONFLUX_MAPPING_PIECE
#define IONFLUX_MAPPING_PIECE
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Piece.hpp                       Piece (header).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include "ifmapping/types.hpp"
#include "ifmapping/constants.hpp"
#include "ifmapping/PointSet.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace Mapping
{

class Mapping;

/// Class information for class Piece.
class PieceClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PieceClassInfo();
		/// Destructor.
		virtual ~PieceClassInfo();
};

/** Piece for piecewise mapping.
 * \ingroup ifmapping
 *
 * A Piece for a piecewise mapping. This consists of a mapping and a 
 * parameter. The parameter can denote the start value for the piece, the 
 * rescaled parameter for the piece, or a factor, depending on where the 
 * piece is used.
 */
class Piece
: public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Mapping.
		Ionflux::Mapping::Mapping* mapping;
		/// Parameter.
		Ionflux::Mapping::MappingValue param;
		
	public:
		/// Class information instance.
		static const PieceClassInfo pieceClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Piece object.
		 */
		Piece();
		
		/** Constructor.
		 *
		 * Construct new Piece object.
		 *
		 * \param other Other object.
		 */
		Piece(const Ionflux::Mapping::Piece& other);
		
		/** Constructor.
		 *
		 * Construct new Piece object.
		 *
		 * \param initMapping Mapping.
		 * \param initParam Parameter.
		 */
		Piece(Ionflux::Mapping::Mapping* initMapping, 
		Ionflux::Mapping::MappingValue initParam = 0.);
		
		/** Destructor.
		 *
		 * Destruct Piece object.
		 */
		virtual ~Piece();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Create piece.
		 *
		 * Create piece
		 *
		 * \param initMapping Mapping.
		 * \param initParam Parameter.
		 *
		 * \return New piece.
		 */
		static Ionflux::Mapping::Piece* create(Ionflux::Mapping::Mapping* 
		initMapping, Ionflux::Mapping::MappingValue initParam);
		
		/** Create pieces from points.
		 *
		 * Create pieces from a collection of points. The pieces are linear 
		 * mappings that interpolate the points. The points will be offset by 
		 * \c offset and scaled by \c scale before the pieces are created. If 
		 * \c addConstant is \c true, a constant piece propagating the last 
		 * Y-value will be added to the target vector.
		 *
		 * \param points Points.
		 * \param target Where to store the pieces.
		 * \param offset Offset.
		 * \param scale Scale.
		 * \param addConstant Add a constant piece at the end.
		 */
		static void createPieces(const Ionflux::Mapping::PointSet& points, 
		Ionflux::Mapping::PieceVector& target, const Ionflux::Mapping::Point& 
		offset = Ionflux::Mapping::Point::ORIGIN, const Ionflux::Mapping::Point& 
		scale = Ionflux::Mapping::Point::ONES, bool addConstant = true);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Piece& operator=(const Ionflux::Mapping::Piece&
		other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Piece* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Piece* upcast(Ionflux::ObjectBase::IFObject* 
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
		static Ionflux::Mapping::Piece* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get mapping.
		 *
		 * \return Current value of mapping.
		 */
		virtual Ionflux::Mapping::Mapping* getMapping() const;
		
		/** Set mapping.
		 *
		 * Set new value of mapping.
		 *
		 * \param newMapping New value of mapping.
		 */
		virtual void setMapping(Ionflux::Mapping::Mapping* newMapping);
		
		/** Get parameter.
		 *
		 * \return Current value of parameter.
		 */
		virtual Ionflux::Mapping::MappingValue getParam() const;
		
		/** Set parameter.
		 *
		 * Set new value of parameter.
		 *
		 * \param newParam New value of parameter.
		 */
		virtual void setParam(Ionflux::Mapping::MappingValue newParam);
};

}

}

/** \file Piece.hpp
 * \brief Piece (header).
 */
#endif
