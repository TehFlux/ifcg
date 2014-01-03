#ifndef IONFLUX_MAPPING_TYPES
#define IONFLUX_MAPPING_TYPES
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * types.hpp                       Types (header).
 * =========================================================================
 *
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

#include <vector>
#include <string>
#include "ifobject/types.hpp"

namespace Ionflux
{

namespace Mapping
{

/// Mapping value.
typedef double MappingValue;
/// Mapping value vector.
typedef Ionflux::ObjectBase::DoubleVector MappingValueVector;
/// Coordinate ID.
typedef unsigned int CoordinateID;

/** A range of values.
 * \ingroup ifmapping
 */
struct Range
{
	/// Lower bound.
	double lower;
	/// Upper bound.
	double upper;
};

/// Range vector.
typedef std::vector<Range> RangeVector;

class Point;
class Mapping;
class Piece;
class BezierCurve;
class BezierSpline;
class BezierSplineKey;
class PointMapping;
class Segment;

/// Vector of points.
typedef std::vector<Ionflux::Mapping::Point*> PointVector;
/// Vector of mappings.
typedef std::vector<Ionflux::Mapping::Mapping*> MappingVector;
/// Vector of pieces.
typedef std::vector<Ionflux::Mapping::Piece*> PieceVector;
/// Vector of point mappings.
typedef std::vector<Ionflux::Mapping::PointMapping*> PointMappingVector;

/// Sample of a mapping.
struct Sample
{
    /// X value.
    Ionflux::Mapping::MappingValue x;
    /// Y value.
    Ionflux::Mapping::MappingValue y;
    /// Sign.
    Ionflux::Mapping::MappingValue s;
    /// Valid flag.
    bool valid;
};

/// Bezier curve vector.
typedef std::vector<Ionflux::Mapping::BezierCurve*> BezierCurveVector;
/// Bezier spline vector.
typedef std::vector<Ionflux::Mapping::BezierSpline*> BezierSplineVector;
/// Bezier spline key vector.
typedef std::vector<Ionflux::Mapping::BezierSplineKey*> BezierSplineKeyVector;
/// Vector of segments.
typedef std::vector<Ionflux::Mapping::Segment*> SegmentVector;

/// Sampling mode.
typedef int SamplingMode;

}

}

/** \file types.hpp
 * \brief Types (header).
 */
#endif
