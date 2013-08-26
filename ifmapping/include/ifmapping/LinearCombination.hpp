#ifndef IONFLUX_MAPPING_LINEARCOMBINATION
#define IONFLUX_MAPPING_LINEARCOMBINATION
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LinearCombination.hpp           Linear combination mapping (header).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
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
#include "ifmapping/Mapping.hpp"

namespace Ionflux
{

namespace Mapping
{

class Piece;

/// Class information for class LinearCombination.
class LinearCombinationClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		LinearCombinationClassInfo();
		/// Destructor.
		virtual ~LinearCombinationClassInfo();
};

/** Linear combination mapping.
 * \ingroup ifmapping
 *
 * Linearly combines several mappings. Each component mapping is specified 
 * as a piece consisting of a mapping and the factor for the linear 
 * combination.
 */
class LinearCombination
: public Ionflux::Mapping::Mapping
{
	private:
		
	protected:
		/// Pieces.
		std::vector<Ionflux::Mapping::Piece*> pieces;
		
	public:
		/// Class information instance.
		static const LinearCombinationClassInfo linearCombinationClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new LinearCombination object.
		 */
		LinearCombination();
		
		/** Constructor.
		 *
		 * Construct new LinearCombination object.
		 *
		 * \param other Other object.
		 */
		LinearCombination(const Ionflux::Mapping::LinearCombination& other);
		
		/** Constructor.
		 *
		 * Construct new LinearCombination object.
		 *
		 * \param initPieces Pieces.
		 */
		LinearCombination(const Ionflux::Mapping::PieceVector& initPieces);
		
		/** Destructor.
		 *
		 * Destruct LinearCombination object.
		 */
		virtual ~LinearCombination();
		
		/** Add pieces.
		 *
		 * Add pieces from a vector of pieces.
		 *
		 * \param newPieces Pieces.
		 */
		virtual void addPieces(const Ionflux::Mapping::PieceVector& newPieces);
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		call(Ionflux::Mapping::MappingValue value) const;
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::LinearCombination& operator=(const 
		Ionflux::Mapping::LinearCombination& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::LinearCombination* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::LinearCombination* 
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
		static Ionflux::Mapping::LinearCombination* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		
		/** Get number of pieces.
		 *
		 * \return Number of pieces.
		 */
		virtual unsigned int getNumPieces() const;
		
		/** Get piece.
		 *
		 * Get the piece at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Piece at specified index.
		 */
		virtual Ionflux::Mapping::Piece* getPiece(unsigned int elementIndex = 0) 
		const;
		
		/** Find piece.
		 *
		 * Find the specified occurence of a piece.
		 *
		 * \param needle Piece to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the piece, or -1 if the piece cannot be found.
		 */
		virtual int findPiece(Ionflux::Mapping::Piece* needle, unsigned int 
		occurence = 1) const;
        
		/** Get pieces.
		 *
		 * \return pieces.
		 */
		virtual std::vector<Ionflux::Mapping::Piece*>& getPieces();
		
		/** Add piece.
		 *
		 * Add a piece.
		 *
		 * \param addElement Piece to be added.
		 */
		virtual void addPiece(Ionflux::Mapping::Piece* addElement);
		
		/** Remove piece.
		 *
		 * Remove a piece.
		 *
		 * \param removeElement Piece to be removed.
		 */
		virtual void removePiece(Ionflux::Mapping::Piece* removeElement);
		
		/** Remove piece.
		 *
		 * Remove a piece.
		 *
		 * \param removeIndex Piece to be removed.
		 */
		virtual void removePieceIndex(unsigned int removeIndex);
		
		/** Clear pieces.
		 *
		 * Clear all pieces.
		 */
		virtual void clearPieces();
};

}

}

/** \file LinearCombination.hpp
 * \brief Linear combination mapping (header).
 */
#endif
