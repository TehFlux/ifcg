/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * gslutils.cpp             GSL utility functions (implementation).
 * ==========================================================================
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
#include <algorithm>
#include <sstream>
#include "geoutils/gslutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/Matrix3.hpp"
#include "geoutils/VectorN.hpp"
#include "geoutils/MatrixMN.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "gsl/gsl_linalg.h"
#include "gsl/gsl_statistics_double.h"

namespace Ionflux
{

namespace GeoUtils
{

void gslToVector3(gsl_vector* v0, Ionflux::GeoUtils::Vector3& v1)
{
    if (v0 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslToVector3] ERROR: "
            "GSL vector is null.");
    if (v0->size < 3)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslToVector3] ERROR: "
            "GSL vector is too short.");
    v1.setX0(gsl_vector_get(v0, 0));
    v1.setX1(gsl_vector_get(v0, 1));
    v1.setX2(gsl_vector_get(v0, 2));
}

void gslFromVector3(const Ionflux::GeoUtils::Vector3& v0, gsl_vector* v1)
{
    if (v1 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslFromVector3] ERROR: "
            "GSL vector is null.");
    if (v1->size < 3)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslFromVector3] ERROR: "
            "GSL vector is too short.");
    gsl_vector_set(v1, 0, v0.getX0());
    gsl_vector_set(v1, 1, v0.getX1());
    gsl_vector_set(v1, 2, v0.getX2());
}

void gslToMatrix3(gsl_matrix* m0, Ionflux::GeoUtils::Matrix3& m1)
{
    if (m0 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslToMat3] ERROR: "
            "GSL matrix is null.");
    if ((m0->size1 < 3) || (m0->size2 < 3))
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslToMat3] ERROR: "
            "GSL matrix is too small.");
    m1.setElement(0, 0, gsl_matrix_get(m0, 0, 0));
    m1.setElement(0, 1, gsl_matrix_get(m0, 0, 1));
    m1.setElement(0, 2, gsl_matrix_get(m0, 0, 2));
    m1.setElement(1, 0, gsl_matrix_get(m0, 1, 0));
    m1.setElement(1, 1, gsl_matrix_get(m0, 1, 1));
    m1.setElement(1, 2, gsl_matrix_get(m0, 1, 2));
    m1.setElement(2, 0, gsl_matrix_get(m0, 2, 0));
    m1.setElement(2, 1, gsl_matrix_get(m0, 2, 1));
    m1.setElement(2, 2, gsl_matrix_get(m0, 2, 2));
}

void gslFromMatrix3(const Ionflux::GeoUtils::Matrix3& m0, gsl_matrix* m1)
{
    if (m1 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslFromMat2] ERROR: "
            "GSL matrix is null.");
    if ((m1->size1 < 3) || (m1->size2 < 3))
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslFromMat2] ERROR: "
            "GSL matrix is too small.");
    gsl_matrix_set(m1, 0, 0, m0.getElement(0, 0));
    gsl_matrix_set(m1, 0, 1, m0.getElement(0, 1));
    gsl_matrix_set(m1, 0, 2, m0.getElement(0, 2));
    gsl_matrix_set(m1, 1, 0, m0.getElement(1, 0));
    gsl_matrix_set(m1, 1, 1, m0.getElement(1, 1));
    gsl_matrix_set(m1, 1, 2, m0.getElement(1, 2));
    gsl_matrix_set(m1, 2, 0, m0.getElement(2, 0));
    gsl_matrix_set(m1, 2, 1, m0.getElement(2, 1));
    gsl_matrix_set(m1, 2, 2, m0.getElement(2, 2));
}

void gslToVectorN(gsl_vector* v0, Ionflux::GeoUtils::VectorN& v1)
{
    if (v0 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslToVectorN] ERROR: "
            "GSL vector is null.");
    unsigned int ne0 = v1.getNumElements();
    if (v0->size < ne0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslToVectorN] ERROR: "
            "GSL vector is too short.");
    for (unsigned int i = 0; i < ne0; i++)
        v1.setElement(i, gsl_vector_get(v0, i));
}

void gslFromVectorN(const Ionflux::GeoUtils::VectorN& v0, gsl_vector* v1)
{
    if (v1 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslFromVectorN] ERROR: "
            "GSL vector is null.");
    unsigned int ne0 = v0.getNumElements();
    if (v1->size < ne0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslFromVector3] ERROR: "
            "GSL vector is too short.");
    for (unsigned int i = 0; i < ne0; i++)
        gsl_vector_set(v1, i, v0.getElement(i));
}

void gslToMatrixMN(gsl_matrix* m0, Ionflux::GeoUtils::MatrixMN& m1)
{
    if (m0 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslToMatrixMN] ERROR: "
            "GSL matrix is null.");
    unsigned int nr0 = m1.getNumRows();
    unsigned int nc0 = m1.getNumCols();
    if ((m0->size1 < nr0) || (m0->size2 < nc0))
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslToMatrixMN] ERROR: "
            "GSL matrix is too small.");
    for (unsigned int i = 0; i < nr0; i++)
        for (unsigned int k = 0; k < nc0; k++)
            m1.setElement(i, k, gsl_matrix_get(m0, i, k));
}

void gslFromMatrixMN(const Ionflux::GeoUtils::MatrixMN& m0, gsl_matrix* m1)
{
    if (m1 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslFromMatrixMN] ERROR: "
            "GSL matrix is null.");
    unsigned int nr0 = m0.getNumRows();
    unsigned int nc0 = m0.getNumCols();
    if ((m1->size1 < nr0) || (m1->size2 < nc0))
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::gslFromMatrixMN] ERROR: "
            "GSL matrix is too small.");
    for (unsigned int i = 0; i < nr0; i++)
        for (unsigned int k = 0; k < nc0; k++)
            gsl_matrix_set(m1, i, k, m0.getElement(i, k));
}

void qrDecomp(const Ionflux::GeoUtils::MatrixMN& m, 
    Ionflux::GeoUtils::MatrixMN& q, 
    Ionflux::GeoUtils::MatrixMN& r)
{
    unsigned int nr0 = m.getNumRows();
    unsigned int nc0 = m.getNumCols();
    unsigned int nr1 = m.getNumRows();
    unsigned int nc1 = m.getNumCols();
    unsigned int nr2 = m.getNumRows();
    unsigned int nc2 = m.getNumCols();
    if ((nr1 != nc1) 
        || (nr0 != nr1) 
        || (nr0 != nr2) 
        || (nc0 != nc2))
    {
        std::ostringstream status;
        status << "[Ionflux::GeoUtils::qrDecomp] ERROR: "
            "Matrix dimensions mismatch (M: " << nr0 << "x" 
            << nc0 << ", Q: " << nr1 << "x" 
            << nc1 << ", R: " << nr2 << "x" 
            << nc2 << ").";
        throw GeoUtilsError(status.str());
    }
    unsigned int nMin = std::min(nr0, nc0);
    gsl_matrix* ga = gsl_matrix_alloc(nr0, nc0);
    gsl_vector* gTau = gsl_vector_alloc(nMin);
    gslFromMatrixMN(m, ga);
    gsl_linalg_QR_decomp(ga, gTau);
    gsl_matrix* gq = gsl_matrix_alloc(nr0, nr0);
    gsl_matrix* gr = gsl_matrix_alloc(nr0, nc0);
    gsl_linalg_QR_unpack(ga, gTau, gq, gr);
    gslToMatrixMN(gq, q);
    gslToMatrixMN(gr, r);
    gsl_matrix_free(gq);
    gsl_matrix_free(gr);
    gsl_matrix_free(ga);
    gsl_vector_free(gTau);
}

void qrSolve(const Ionflux::GeoUtils::MatrixMN& q, 
    const Ionflux::GeoUtils::MatrixMN& r, 
    const Ionflux::GeoUtils::VectorN& b, 
    Ionflux::GeoUtils::VectorN& x)
{
    unsigned int nr0 = q.getNumRows();
    unsigned int nc0 = q.getNumCols();
    unsigned int nr1 = r.getNumRows();
    unsigned int nc1 = r.getNumCols();
    unsigned int ne0 = b.getNumElements();
    unsigned int ne1 = x.getNumElements();
    if ((nr0 != nc0) 
        || (nr0 != nr1) 
        || (nc1 != ne0) 
        || (nc1 != ne1))
    {
        std::ostringstream status;
        status << "[Ionflux::GeoUtils::qrDecomp] ERROR: "
            "Matrix/vector dimensions mismatch (Q: " << nr0 << "x" 
            << nc0 << ", R: " << nr1 << "x" 
            << nc1 << ", b: " << ne0 << ", x: " 
            << ne1 << ").";
        throw GeoUtilsError(status.str());
    }
    gsl_matrix* gq = gsl_matrix_alloc(nr0, nr0);
    gsl_matrix* gr = gsl_matrix_alloc(nr1, nc1);
    gsl_vector* gb = gsl_vector_alloc(ne0);
    gsl_vector* gx = gsl_vector_alloc(ne1);
    gslFromMatrixMN(q, gq);
    gslFromMatrixMN(r, gr);
    gslFromVectorN(b, gb);
    gsl_linalg_QR_QRsolve(gq, gr, gb, gx);
    gslToVectorN(gx, x);
    gsl_matrix_free(gq);
    gsl_matrix_free(gr);
    gsl_vector_free(gb);
    gsl_vector_free(gx);
}

void svd(const Ionflux::GeoUtils::Matrix3& m, 
    Ionflux::GeoUtils::Matrix3& u, Ionflux::GeoUtils::Vector3& s, 
    Ionflux::GeoUtils::Matrix3& v)
{
    gsl_matrix* gu = gsl_matrix_alloc(3, 3);
    gsl_vector* gs = gsl_vector_alloc(3);
    gsl_matrix* gv = gsl_matrix_alloc(3, 3);
    gsl_vector* w = gsl_vector_alloc(3);
    gslFromMatrix3(m, gu);
    gsl_linalg_SV_decomp(gu, gv, gs, w);
    gslToMatrix3(gu, u);
    gslToVector3(gs, s);
    gslToMatrix3(gv, v);
    gsl_matrix_free(gu);
    gsl_vector_free(gs);
    gsl_matrix_free(gv);
    gsl_vector_free(w);
}

void covariance(Ionflux::GeoUtils::Vertex3Set& vs, 
    Ionflux::GeoUtils::Matrix3& c)
{
    unsigned int numVerts = vs.getNumVertices();
    double* d1 = new double[numVerts];
    if (d1 == 0)
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::covariance] ERROR: "
            "Could not allocate data buffer.");
    double* d2 = new double[numVerts];
    if (d2 == 0)
    {
        delete[] d1;
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::covariance] ERROR: "
            "Could not allocate data buffer.");
    }
    double* d3 = new double[numVerts];
    if (d3 == 0)
    {
        delete[] d1;
        delete[] d2;
        throw GeoUtilsError(
            "[Ionflux::GeoUtils::covariance] ERROR: "
            "Could not allocate data buffer.");
    }
    for (unsigned int k = 0; k < numVerts; k++)
    {
        Vertex3* v = vs.getVertex(k);
        d1[k] = v->getX();
        d2[k] = v->getY();
        d3[k] = v->getZ();
    }
    c.setElement(0, 0, gsl_stats_covariance(d1, 1, d1, 1, numVerts));
    c.setElement(0, 1, gsl_stats_covariance(d1, 1, d2, 1, numVerts));
    c.setElement(0, 2, gsl_stats_covariance(d1, 1, d3, 1, numVerts));
    c.setElement(1, 0, gsl_stats_covariance(d2, 1, d1, 1, numVerts));
    c.setElement(1, 1, gsl_stats_covariance(d2, 1, d2, 1, numVerts));
    c.setElement(1, 2, gsl_stats_covariance(d2, 1, d3, 1, numVerts));
    c.setElement(2, 0, gsl_stats_covariance(d3, 1, d1, 1, numVerts));
    c.setElement(2, 1, gsl_stats_covariance(d3, 1, d2, 1, numVerts));
    c.setElement(2, 2, gsl_stats_covariance(d3, 1, d3, 1, numVerts));
    delete[] d1;
    delete[] d2;
    delete[] d3;
}

}

}

/** \file gslutils.cpp
 * \brief GSL utility functions (implementation).
 */
