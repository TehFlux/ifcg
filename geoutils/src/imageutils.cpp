/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2012 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * imageutils.cpp                Image utility functions (implementation).
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
#include "altjira/imageutils.hpp"
#include "geoutils/imageutils.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/Vertex3Set.hpp"

namespace Ionflux
{

namespace GeoUtils
{

void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::FloatColor& c)
{
    Ionflux::Altjira::FloatColor r;
    r.c0 = 0.5 * n[0] + 0.5;
    r.c1 = 0.5 * n[1] + 0.5;
    r.c2 = n[2];
    r.alpha = 1.;
    r.space = Ionflux::Altjira::Color::SPACE_RGB;
    Ionflux::Altjira::clamp(r);
    toColorSpace(r, c.space);
    c = r;
}

void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::ByteColor& c)
{
    Ionflux::Altjira::FloatColor fc;
    Ionflux::Altjira::byteToFloat(c, fc);
    normalToColor(n, fc);
    Ionflux::Altjira::floatToByte(fc, c);
}

void normalToColor(const Ionflux::GeoUtils::Vector3& n, 
    Ionflux::Altjira::Color& c)
{
    c.setRed(0.5 * n[0] + 0.5);
    c.setGreen(0.5 * n[1] + 0.5);
    c.setBlue(n[2]);
    c.setAlpha(1.);
    c.clamp();
}

double sample(Ionflux::Altjira::Matrix& m, Ionflux::GeoUtils::Vertex3& v)
{
    int x0 = static_cast<int>(v.getX());
    int y0 = static_cast<int>(v.getY());
    if ((x0 < 0) || (x0 >= static_cast<int>(m.getNumCols())) 
        || (y0 < 0) || (y0 >= static_cast<int>(m.getNumRows())))
        return 0.;
    return m.v(y0, x0);
}

double sampleMulti(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, 
    Ionflux::GeoUtils::Matrix3* t, 
    Ionflux::GeoUtils::MatrixSamplingMethod method)
{
    Vertex3Set* vs0 = 0;
    bool ownVS = false;
    if (t != 0)
    {
        vs0 = vs.copy();
        vs0->transform(*t);
        vs0->applyTransform();
        ownVS = true;
    } else
        vs0 = &vs;
    double r0 = 0.;
    if (method == SAMPLE_MULTIPLY)
        r0 = 1;
    unsigned int numVerts = vs0->getNumVertices();
    for (unsigned int i = 0; i < numVerts; i++)
    {
        Vertex3* v0 = vs0->getVertex(i);
        if (method == SAMPLE_MULTIPLY)
            r0 *= sample(m, *v0);
        else
            r0 += sample(m, *v0);
    }
    if (ownVS)
        delete vs0;
    if (method == SAMPLE_MULTIPLY)
        return r0;
    return r0 / numVerts;
}

Ionflux::GeoUtils::Vector2 sampleMultiRot(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, 
    const Ionflux::GeoUtils::Vector3& offset, double phi0, double phi1, 
    double dPhi, 
    Ionflux::GeoUtils::MatrixSamplingMethod method)
{
    double phi = phi0;
    Vector2 result;
    bool first = true;
    while (phi < phi1)
    {
        Matrix3 T0 = Matrix3::translate(offset.getX0(), offset.getX1());
        Matrix3 R0 = Matrix3::rotate(phi);
        Matrix3 TM0(T0 * R0);
        double r0 = sampleMulti(m, vs, &TM0, method);
        if (first 
            || (r0 > result.getX1()))
        {
            result.setElements(phi, r0);
            first = false;
        }
        phi += dPhi;
    }
    return result;
}

void sampleMultiRotMatrix(Ionflux::Altjira::Matrix& m, 
    Ionflux::GeoUtils::Vertex3Set& vs, Ionflux::Altjira::Matrix& r0, 
    Ionflux::Altjira::Matrix& r1, const Ionflux::GeoUtils::Vector3& offset, 
    double phi0, double phi1, double dPhi, 
    Ionflux::GeoUtils::MatrixSamplingMethod method)
{
    unsigned int numRows = m.getNumRows();
    unsigned int numCols = m.getNumCols();
    r0.init(numRows, numCols);
    r1.init(numRows, numCols);
    unsigned int k = 0;
    for (unsigned int i = 0; i < numRows; i++)
        for (unsigned int j = 0; j < numCols; j++)
        {
            // <---- DEBUG ----- //
            if (k % 1000 == 0)
                std::cerr << "[sampleMultiRotMatrix] DEBUG: "
            << "k = " << k << std::endl;
            // ----- DEBUG ----> */
            Vector3 pos0(static_cast<double>(j), 
                static_cast<double>(i), 0.);
            Vector2 cr = sampleMultiRot(m, vs, pos0 + offset, 
                phi0, phi1, dPhi, method);
            r0.setValue(i, j, cr.getX0());
            r1.setValue(i, j, cr.getX1());
            k++;
        }
}

}

}

/** \file imageutils.cpp
 * \brief Image utility functions (implementation).
 */
