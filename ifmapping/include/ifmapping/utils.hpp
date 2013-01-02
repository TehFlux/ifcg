#ifndef IONFLUX_MAPPING_UTILITY
#define IONFLUX_MAPPING_UTILITY
/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.hpp                     Utility functions (header).
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
#include "ifobject/types.hpp"
#include "ifmapping/types.hpp"
#include "ifmapping/constants.hpp"
#include "ifmapping/PointSet.hpp"
#include "ifmapping/constants.hpp"

namespace Ionflux
{

namespace Mapping
{

/** Comparison (with tolerance): less than.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool lt(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);

/** Comparison (with tolerance): greater than.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool gt(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);

/** Comparison (with tolerance): equal.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool eq(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);

/** Comparison (with tolerance): less than or equal.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool ltOrEq(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);

/** Comparison (with tolerance): less than or equal.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool gtOrEq(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t = Ionflux::Mapping::DEFAULT_TOLERANCE);

class BezierSpline;

/** Get coordinate string representation.
 * 
 * Get a string representation for a coordinate ID.
 * 
 * \param coord Coordinate ID.
 *
 * \return String representation.
 */
std::string coordToString(Ionflux::Mapping::CoordinateID coord);

/** Clamp value.
 * 
 * Clamp a value to a range.
 * 
 * \param v Value.
 * \param r Range.
 */
double clamp(double v, const Ionflux::Mapping::Range& r = 
    Ionflux::Mapping::DEFAULT_CLAMP_RANGE);

/** Wrap value.
 * 
 * Wrap a value to a range.
 * 
 * \param v Value.
 * \param r Range.
 */
double wrap(double v, const Ionflux::Mapping::Range& r = 
    Ionflux::Mapping::DEFAULT_CLAMP_RANGE);

/** Range check.
 * 
 * Range check.
 * 
 * \param r Range.
 * \param v Value.
 */
bool isInRange(const Ionflux::Mapping::Range& r, double v);

/**
 * Update sample.
 * 
 * Update the previous mapping sample. The previous sample is updated if 
 * either it is not valid or if the other sample is valid and the current 
 * sample is closer to the other sample than the previous sample.
 */
void updateSample(const Ionflux::Mapping::Sample current, 
    Ionflux::Mapping::Sample& previous, 
    const Ionflux::Mapping::Sample& other);

/// Sign function.
double sign(double v);

/**
 * Evaluate Bernstein polynomial.
 *
 * Evaluate the Bernstein polynomial of degree n at t, using de Casteljau's 
 * algorithm.
 *
 * \param c Vector of coefficients to be used.
 * \param t Parameter.
 * \param n Degree of the polynomial.
 * \param i Step parameter.
 *
 * \return Result of the calculation.
 */
Ionflux::Mapping::MappingValue bernstein(
    const Ionflux::Mapping::MappingValueVector& c, 
    Ionflux::Mapping::MappingValue t, unsigned int n = 3, unsigned int i = 0);

/**
 * Evaluate cubic bezier curve.
 * 
 * Evaluate a cubic bezier curve at the specified parameter (0 <= t <= 1). 
 *
 * \param t Parameter.
 * \param controlPoints Control points.
 *
 * \return Result of the calculation.
 */
Ionflux::Mapping::Point bezier(Ionflux::Mapping::MappingValue t, 
    const Ionflux::Mapping::PointVector& controlPoints);

/** Explode a string.
 *
 * Splits up a string of bytes at 'splitString', creating a vector containing 
 * the separated elements.
 *
 * \param bytes Byte String to be exploded.
 * \param splitString Separator string.
 * \param result Vector to store the result in.
 */
void explode(const std::string& bytes, const std::string& splitString, 
    Ionflux::ObjectBase::StringVector& result);

/**
 * Extract point from SVG.
 *
 * Extract point coordinates from an SVG point specification (X,Y).
 *
 * \param rawData Source data.
 * \param target Where to store the vertex data.
 */
void extractSVGPoint(const std::string& rawData, 
    Ionflux::Mapping::Point& target);

/**
 * Extract control points from SVG.
 *
 * Extract control point coordinates for multiple cubic bezier curve 
 * segments from an SVG path specification.
 *
 * \param rawData Source data.
 * \param target Where to store the control point data.
 */
void extractSVGControlPoints(const std::string& rawData, 
    Ionflux::Mapping::PointSet& target);

/**
 * Initialize random number generator.
 * 
 * Initialize the random number generator.
 */
void initRandom();

/**
 * Initialize random number generator.
 * 
 * Initialize the random number generator.
 * 
 * \param seed Seed.
 */
void initRandom(unsigned int seed);

/**
 * Dispose random number generator.
 * 
 * Clean up resources allocated for the random number generator.
 */
void disposeRandom();

/**
 * Get random integer.
 * 
 * Get a random integer in the range [0, 2^32-1].
 *
 * \return Random value.
 */
unsigned int getRandomInt();

/**
 * Get random double.
 * 
 * Get a random double precision float number in the range [0, 1].
 *
 * \return Random value.
 */
double getRandomDouble();

/**
 * Get random double.
 * 
 * Get a random double precision float number in the range [0, 1).
 *
 * \return Random value.
 */
double getRandomDoubleExc();

/**
 * Get random double.
 * 
 * Get a random double precision float number from a normal distribution.
 *
 * \param mean Mean value.
 * \param stdDev Standard deviation.
 *
 * \return Random value.
 */
double getRandomNorm(double mean = 0., double stdDev = 1.);

/**
 * Get random point.
 * 
 * Get a random point in the range [0, 1] x [0, 1] x [0, 1].
 *
 * \return Random point.
 */
Ionflux::Mapping::Point getRandomPoint();

/**
 * Get random point.
 * 
 * Get a random point in the range [0, 1) x [0, 1) x [0, 1).
 *
 * \return Random point.
 */
Ionflux::Mapping::Point getRandomPointExc();

/**
 * Get random double.
 * 
 * Get a random point number from a normal distribution in each dimension.
 *
 * \param meanX Mean value (X).
 * \param stdDevX Standard deviation (X).
 * \param meanX Mean value (Y).
 * \param stdDevX Standard deviation (Y).
 * \param meanX Mean value (Z).
 * \param stdDevX Standard deviation (Z).
 *
 * \return Random value.
 */
Ionflux::Mapping::Point getRandomPointNorm(double meanX = 0., 
    double stdDevX = 1., double meanY = 0., 
    double stdDevY = 1., double meanZ = 0., 
    double stdDevZ = 1.);

/**
 * Get string or default value.
 * 
 * Return the source string or a default string if the source string is empty.
 *
 * \param source Source string.
 * \param d Default value.
 *
 * \return Source string or default value.
 */
std::string defaultStr(const std::string& source, 
    const std::string& d = "<none>");

}

}

/** \file utility.hpp
 * \brief Utility functions (header).
 */
#endif
