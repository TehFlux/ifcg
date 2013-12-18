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
class VectorN;
class MatrixMN;
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
 * \param v1 GSL matrix
 */
void gslFromMatrix3(const Ionflux::GeoUtils::Matrix3& m0, gsl_matrix* m1);

/** GSL vector conversion (N-D).
 *
 * Convert GSL vector to VectorN.
 *
 * \param v0 GSL vector
 * \param v1 vector (N-D)
 */
void gslToVectorN(gsl_vector* v0, Ionflux::GeoUtils::VectorN& v1);

/** GSL vector conversion (N-D).
 *
 * Convert VectorN to GSL vector.
 *
 * \param v0 vector (N-D)
 * \param v1 GSL vector
 */
void gslFromVectorN(const Ionflux::GeoUtils::VectorN& v0, gsl_vector* v1);

/** GSL matrix conversion (MxN).
 *
 * Convert GSL matrix to MatrixMN.
 *
 * \param v0 GSL matrix
 * \param v1 matrix (MxN)
 */
void gslToMatrixMN(gsl_matrix* m0, Ionflux::GeoUtils::MatrixMN& m1);

/** GSL matrix conversion (MxN).
 *
 * Convert MatrixNM to GSL matrix.
 *
 * \param v0 matrix (MxN)
 * \param v1 GSL matrix
 */
void gslFromMatrixMN(const Ionflux::GeoUtils::MatrixMN& m0, gsl_matrix* m1);

/** QR decomposition (MxN).
 * 
 * Calculate the QR decomposition of the input matrix.
 *
 * \param m input matrix
 * \param q Q
 * \param r R
 */
void qrDecomp(const Ionflux::GeoUtils::MatrixMN& m, 
    Ionflux::GeoUtils::MatrixMN& q, 
    Ionflux::GeoUtils::MatrixMN& r);

/** QR solve.
 * 
 * Solve the system R x = Q^T b.
 *
 * \param q Q
 * \param r R
 * \param b b
 * \param x x
 */
void qrSolve(const Ionflux::GeoUtils::MatrixMN& q, 
    const Ionflux::GeoUtils::MatrixMN& r, 
    const Ionflux::GeoUtils::VectorN& b, 
    Ionflux::GeoUtils::VectorN& x);

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
