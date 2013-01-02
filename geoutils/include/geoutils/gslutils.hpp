#ifndef IONFLUX_GEOUTILS_GSLUTILS
#define IONFLUX_GEOUTILS_GSLUTILS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * gslutils.hpp                     GSL utility functions (header).
 * ========================================================================== */
#include "gsl/gsl_vector.h"
#include "gsl/gsl_matrix.h"

namespace Ionflux
{

namespace GeoUtils
{

class Vector3;
class Matrix3;
class Vertex3Set;

/** GSL vector conversion (3D).
 *
 * Convert GSL vector to Vector3.
 *
 * \param v0 GSL vector
 * \param v1 vector (3D)
 */
void gslToVector3(gsl_vector* v0, Ionflux::GeoUtils::Vector3& v1);

/** GSL vector conversion (3D).
 *
 * Convert Vector3 to GSL vector.
 *
 * \param v0 vector (3D)
 * \param v1 GSL vector
 */
void gslFromVector3(const Ionflux::GeoUtils::Vector3& v0, gsl_vector* v1);

/** GSL matrix conversion (3x3).
 *
 * Convert GSL matrix to Matrix3.
 *
 * \param v0 GSL vector
 * \param v1 matrix (3x3)
 */
void gslToMatrix3(gsl_matrix* m0, Ionflux::GeoUtils::Matrix3& m1);

/** GSL matrix conversion (3x3).
 *
 * Convert Matrix3 to GSL matrix.
 *
 * \param v0 matrix (3x3)
 * \param v1 GSL vector
 */
void gslFromMatrix3(const Ionflux::GeoUtils::Matrix3& m0, gsl_matrix* m1);

/** Singular value decomposition (3D).
 *
 * Calculate the singular value decomposition M = U S V^T of the input 
 * matrix.
 *
 * \param m input matrix.
 * \param u U
 * \param s singular values
 * \param v V
 */
void svd(const Ionflux::GeoUtils::Matrix3& m, 
    Ionflux::GeoUtils::Matrix3& u, Ionflux::GeoUtils::Vector3& s, 
    Ionflux::GeoUtils::Matrix3& v);

/** Calculate covariance matrix (3D).
 *
 * Calculate the covariance matrix for the vertices in the vertex set.
 *
 * \param vs vertex set
 * \param c covariance matrix
 */
void covariance(Ionflux::GeoUtils::Vertex3Set& vs, 
    Ionflux::GeoUtils::Matrix3& c);

}

}

/** \file gslutils.hpp
 * \brief GSL utility functions (header).
 */
#endif
