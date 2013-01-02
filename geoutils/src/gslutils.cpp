/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * gslutils.cpp             GSL utility functions (implementation).
 * ========================================================================== */
#include "geoutils/gslutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vector3.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/Matrix3.hpp"
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
