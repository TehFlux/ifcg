#ifndef IONFLUX_MAPPING_PIECEWISE
#define IONFLUX_MAPPING_PIECEWISE
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Piecewise.hpp                   Piecewise mapping (header).
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
#include "ifmapping/constants.hpp"
#include "ifmapping/PointSet.hpp"
#include "ifmapping/ChainableMapping.hpp"

namespace Ionflux
{

namespace Mapping
{

class Piece;

/// Class information for class Piecewise.
class PiecewiseClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		PiecewiseClassInfo();
		/// Destructor.
		virtual ~PiecewiseClassInfo();
};

/** Piecewise mapping.
 * \ingroup ifmapping
 *
 * A mapping consisting of several pieces. Each piece consists of a Mapping
 * and the value at which the piece starts.
 */
class Piecewise
: public Ionflux::Mapping::ChainableMapping
{
	private:
		
	protected:
		/// Pieces.
		std::vector<Ionflux::Mapping::Piece*> pieces;
		
	public:
		/// Class information instance.
		static const PiecewiseClassInfo piecewiseClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Piecewise object.
		 */
		Piecewise();
		
		/** Constructor.
		 *
		 * Construct new Piecewise object.
		 *
		 * \param other Other object.
		 */
		Piecewise(const Ionflux::Mapping::Piecewise& other);
		
		/** Constructor.
		 *
		 * Construct new Piecewise object.
		 *
		 * \param initPieces Pieces.
		 * \param initFunc Source mapping.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 */
		Piecewise(const Ionflux::Mapping::PieceVector& initPieces, 
		Ionflux::Mapping::Mapping* initFunc = 0, Ionflux::Mapping::MappingValue 
		initScale = 1., Ionflux::Mapping::MappingValue initOffset = 0.);
		
		/** Constructor.
		 *
		 * Construct new Piecewise object.
		 *
		 * \param points Points.
		 * \param initFunc Source mapping.
		 * \param initScale Scale factor.
		 * \param initOffset Offset.
		 */
		Piecewise(const Ionflux::Mapping::PointSet& points, 
		Ionflux::Mapping::Mapping* initFunc = 0, Ionflux::Mapping::MappingValue 
		initScale = 1., Ionflux::Mapping::MappingValue initOffset = 0.);
		
		/** Destructor.
		 *
		 * Destruct Piecewise object.
		 */
		virtual ~Piecewise();
		
		/** Add pieces.
		 *
		 * Add pieces from a vector of pieces.
		 *
		 * \param newPieces Pieces.
		 */
		virtual void addPieces(const Ionflux::Mapping::PieceVector& newPieces);
		
		/** Get a piece of the mapping.
		 *
		 * Get the piece of function definition that applies for t. Also 
		 * rescale t so it can be used to get a corrent interpolated value 
		 * from the piece. Returns a piece containing a mapping and the 
		 * rescaled parameter. If no suitable piece exists for t, the mapping 
		 * field of the resulting piece will be set to 0.
		 *
		 * \param t Parameter.
		 * \param tolerance Tolerance.
		 *
		 * \return Piece.
		 */
		virtual Ionflux::Mapping::Piece 
		getPieceForT(Ionflux::Mapping::MappingValue t, 
		Ionflux::Mapping::MappingValue tolerance = 
		Ionflux::Mapping::DEFAULT_TOLERANCE) const;
		
		/** Call the mapping.
		 *
		 * Calls the mapping with the specified parameter.
		 *
		 * \param value Value.
		 *
		 * \return Mapped value.
		 */
		virtual Ionflux::Mapping::MappingValue 
		callWithParam(Ionflux::Mapping::MappingValue value) const;
		
		/** Create sawtooth function.
		 *
		 * Create a sawtooth function over the interval [0...1]. This is a 
		 * piecewise function consisting of a linear segment which is repeated
		 * within the interval [0...1] a number of times equal to the 
		 * frequency.
		 *
		 * \param freq Frequency.
		 * \param ampMin Minimum amplitude.
		 * \param ampMax Maximum amplitude.
		 *
		 * \return Sawtooth function.
		 */
		static Ionflux::Mapping::Piecewise* 
		sawtooth(Ionflux::Mapping::MappingValue freq = 1., 
		Ionflux::Mapping::MappingValue ampMin = 0., 
		Ionflux::Mapping::MappingValue ampMax = 1.);
		
		/** Create step function.
		 *
		 * Create a step function over the interval [0...1]. This is a 
		 * piecewise function consisting of constant segments of equal length 
		 * within the interval [0...1]. The function value for each segment is
		 * chosen so that the first step equals the minimum value, the last 
		 * step equals the maximum value, and all steps have the same 
		 * difference in value.
		 *
		 * \param numSteps Number of steps.
		 * \param minValue Minimum value.
		 * \param maxValue Maximum value.
		 *
		 * \return Step function.
		 */
		static Ionflux::Mapping::Piecewise* step(Ionflux::Mapping::MappingValue 
		numSteps = 1., Ionflux::Mapping::MappingValue minValue = 0., 
		Ionflux::Mapping::MappingValue maxValue = 1.);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::Mapping::Piecewise& operator=(const 
		Ionflux::Mapping::Piecewise& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::Mapping::Piecewise* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::Mapping::Piecewise* upcast(Ionflux::ObjectBase::IFObject*
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
		static Ionflux::Mapping::Piecewise* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
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

/** \file Piecewise.hpp
 * \brief Piecewise mapping (header).
 */
#endif
