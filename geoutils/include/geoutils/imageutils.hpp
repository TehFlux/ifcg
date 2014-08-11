#ifndef IONFLUX_GEOUTILS_IMAGE_UTILS
#define IONFLUX_GEOUTILS_IMAGE_UTILS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * imageutils.hpp                  Image utility functions (header).
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
#include "altjira/Color.hpp"
#include "altjira/Matrix.hpp"
#include "geoutils/Vector2.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Vector4.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Vertex3;
class Vertex3Set;
class Matrix3;

/** Convert normal vector to RGBA color.
 *
 * Convert a normal vector to an RGBA color.
 * 
 * \param n normal vector
 * \param c color
 */
void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::FloatColor& c);

/** Convert normal vector to RGBA color.
 *
 * Convert a normal vector to an RGBA color.
 * 
 * \param n normal vector
 * \param c color
 */
void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::ByteColor& c);

/** Convert normal vector to RGBA color.
 *
 * Convert a normal vector to an RGBA color.
 * 
 * \param n normal vector
 * \param c color
 */
void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::Color& c);

/** Convert RGBA color to vector.
 *
 * Convert an RGBA color to a vector.
 * 
 * \param c color
 * \param target target vector
 */
void colorToVec(const Ionflux::Altjira::Color& c, 
    Ionflux::GeoUtils::Vector4& target);

/** Convert vector to RGBA color.
 *
 * Convert a vector to an RGBA color.
 * 
 * \param v vector
 * \param target target color
 */
void vecToColor(const Ionflux::GeoUtils::Vector4& v, 
    Ionflux::Altjira::Color& target);

/** Sample matrix.
 *
 * Sample a matrix at a vertex position.
 * 
 * \param m matrix
 * \param v vertex
 *
 * \return sample value
 */
double sample(Ionflux::Altjira::Matrix& m, Ionflux::GeoUtils::Vertex3& v);

/** Sample matrix.
 *
 * Sample a matrix at multiple vertex positions. If the optional matrix 
 * \c t is specified, the vertices will be transformed according to that 
 * matrix before the sample is taken. The function returns the average value 
 * of the samples.
 * 
 * \param m matrix
 * \param vs vertex set
 * \param t transform matrix
 *
 * \return sample value
 */
double sampleMulti(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, 
    Ionflux::GeoUtils::Matrix3* t = 0, 
    Ionflux::GeoUtils::MatrixSamplingMethod method = SAMPLE_AVERAGE);

/** Sample matrix.
 *
 * Sample a matrix at multiple vertex positions, using a fixed offset and 
 * multiple orientations between \c phi0 and \c phi1. The function returns a 
 * vector containing the angle that yielded the maximum sample and the 
 * average value of the samples for that angle.
 * 
 * \param m matrix
 * \param vs vertex set
 * \param offset offset
 * \param phi0 start angle
 * \param phi1 end angle
 * \param dPhi angle step
 *
 * \return sample value
 */
Ionflux::GeoUtils::Vector2 sampleMultiRot(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, 
    const Ionflux::GeoUtils::Vector3& offset, double phi0, double phi1, 
    double dPhi, 
    Ionflux::GeoUtils::MatrixSamplingMethod method = SAMPLE_AVERAGE);

/** Sample matrix.
 *
 * Sample a matrix at multiple vertex positions, using the row and column 
 * indices as variable offsets, the \c offset argument as a fixed offset, 
 * and multiple orientations between \c phi0 and \c phi1. The function 
 * stores the angle angle that yielded the maximum sample in the argument 
 * \c r0 and the average value of the samples for that angle in \c r1.
 * 
 * \param m matrix
 * \param vs vertex set
 * \param r0 result matrix (angle)
 * \param r1 result matrix (sample value)
 * \param offset offset
 * \param phi0 start angle
 * \param phi1 end angle
 * \param dPhi angle step
 *
 * \return sample value
 */
void sampleMultiRotMatrix(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, Ionflux::Altjira::Matrix& r0, 
    Ionflux::Altjira::Matrix& r1, const Ionflux::GeoUtils::Vector3& offset, 
    double phi0, double phi1, double dPhi, 
    Ionflux::GeoUtils::MatrixSamplingMethod method = SAMPLE_AVERAGE);

}

}

/** \file imageutils.hpp
 * \brief Image utility functions (header).
 */
#endif
