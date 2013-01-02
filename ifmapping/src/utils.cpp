/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.cpp                     Utility functions (implementation).
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

#include <cmath>
#include <sstream>
#include <cstdlib>
#include "ifmapping/utils.hpp"
#include "ifmapping/MappingError.hpp"
#include "MersenneTwister.h"

using namespace Ionflux::ObjectBase;

namespace Ionflux
{

namespace Mapping
{

bool lt(Ionflux::Mapping::MappingValue v0, Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t)
{
    if (v0 < (v1 - t))
        return true;
    return false;
}

bool gt(Ionflux::Mapping::MappingValue v0, Ionflux::Mapping::MappingValue v1, 
    Ionflux::Mapping::MappingValue t)
{
    if (v0 > (v1 + t))
        return true;
    return false;
}

bool eq(Ionflux::Mapping::MappingValue v0, Ionflux::Mapping::MappingValue v1,
    Ionflux::Mapping::MappingValue t)
{
    if (!(gt(v0, v1, t) || lt(v0, v1, t)))
        return true;
    return false;
}

bool ltOrEq(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, Ionflux::Mapping::MappingValue t)
{
    if (!gt(v0, v1, t))
        return true;
    return false;
}

bool gtOrEq(Ionflux::Mapping::MappingValue v0, 
    Ionflux::Mapping::MappingValue v1, Ionflux::Mapping::MappingValue t)
{
    if (!lt(v0, v1, t))
        return true;
    return false;
}

std::string coordToString(Ionflux::Mapping::CoordinateID coord)
{
    if (coord == C_X)
        return "C_X";
    if (coord == C_Y)
        return "C_Y";
    if (coord == C_Z)
        return "C_Z";
    return "<unknown>";
}

double clamp(double v, const Ionflux::Mapping::Range& r)
{
    if (v < r.lower)
        return r.lower;
    if (v > r.upper)
        return r.upper;
    return v;
}

double wrap(double v, const Ionflux::Mapping::Range& r)
{
    double l = r.upper - r.lower;
    while (v < r.lower)
        v += l;
    while (v > r.upper)
        v -= l;
    return v;
}

bool isInRange(const Ionflux::Mapping::Range& r, double v)
{
    if (v < r.lower)
        return false;
    if (v > r.upper)
        return false;
    return true;
}

void explode(const std::string& bytes, const std::string& splitString, 
    Ionflux::ObjectBase::StringVector& result)
{
	result.clear();
	if ((bytes.size() == 0) 
        || (splitString.size() == 0))
		return;
    std::string::size_type currentPos = 0;
	std::string::size_type nextPos;
	while ((currentPos < bytes.size()) 
		&& ((nextPos = bytes.find(splitString, currentPos)) 
            != std::string::npos))
	{
		if ((nextPos - currentPos) > 0)
			result.push_back(bytes.substr(currentPos, nextPos - currentPos));
		else
			result.push_back("");
		currentPos = nextPos + 1;
	}
	result.push_back(bytes.substr(currentPos, bytes.size() - currentPos));
}

void extractSVGPoint(const std::string& rawData, 
    Ionflux::Mapping::Point& target)
{
    StringVector parts0;
    explode(rawData, ",", parts0);
    if (parts0.size() < 2)
    {
        std::ostringstream message;
        message << "Invalid vertex specification: '" << rawData << "'";
        throw MappingError(message.str());
    }
    target.setX(strtod(parts0[0].c_str(), 0));
    target.setY(strtod(parts0[1].c_str(), 0));
    target.setZ(0.);
}

void extractSVGControlPoints(const std::string& rawData, 
    Ionflux::Mapping::PointSet& target)
{
    StringVector parts0;
    explode(rawData, " ", parts0);
    unsigned int i = 0;
    Point prevPoint;
    Point p0;
    std::string pl;
    while (i < parts0.size())
    {
        std::string p = parts0[i];
        if (p.size() > 1)
        {
            // Use previous command if none is given.
            p = pl;
            i--;
        }
        if (p == "M")
        {
            // Move to: Start a new segment.
            pl = p;
            i++;
            if (i >= parts0.size())
            {
                std::ostringstream message;
                message << "Invalid path specification: '" << rawData 
                    << "' (point missing).";
                throw MappingError(message.str());
            }
            p = parts0[i];
            extractSVGPoint(p, prevPoint);
        } else
        if (p == "C")
        {
            /* Curve to: Extract the remaining three control points 
               and use the previous point as the first control point. */
            pl = p;
            target.addPoint(new Point(prevPoint));
            for (unsigned int j = 0; j < 3; j++)
            {
                i++;
                if (i >= parts0.size())
                {
                    std::ostringstream message;
                    message << "Invalid path specification: '" << rawData 
                        << "' (point missing).";
                    throw MappingError(message.str());
                }
                p = parts0[i];
                extractSVGPoint(p, p0);
                target.addPoint(new Point(p0));
            }
            prevPoint = *(target.getPoint(target.getNumPoints() - 1));
        } else
        {
            std::ostringstream message;
            message << "Invalid path specification: '" << rawData 
                << "' (unknown path token: '" << p << "').";
            throw MappingError(message.str());
        }
        i++;
    }
}

void updateSample(const Ionflux::Mapping::Sample current, 
    Ionflux::Mapping::Sample& previous, 
    const Ionflux::Mapping::Sample& other)
{
    if (!previous.valid)
        // We do not have a sample yet, initialize it.
        previous = current;
    else
    if (other.valid)
    {
        /* Check if the current sample is better, 
           i.e. closer to the other sample. */
       if (fabs(current.x - other.x) < fabs(previous.x - other.x))
           previous = current;
    }
}

double sign(double v)
{
    if (v == 0.)
        return 0.;
    return v / fabs(v);
}

Ionflux::Mapping::MappingValue bernstein(
    const Ionflux::Mapping::MappingValueVector& c, 
    Ionflux::Mapping::MappingValue t, unsigned int n, unsigned int i)
{
    if (n == 0)
        return c[i];
    return bernstein(c, t, n - 1, i) * (1. - t) 
        + bernstein(c, t, n - 1, i + 1) * t;
}

Ionflux::Mapping::Point bezier(Ionflux::Mapping::MappingValue t, 
    const Ionflux::Mapping::PointVector& controlPoints)
{
    if (controlPoints.size() < 4)
        throw MappingError("Need four control points for cubic bezier "
            "spline.");
    MappingValueVector cx;
    cx.push_back(controlPoints[0]->getX());
    cx.push_back(controlPoints[1]->getX());
    cx.push_back(controlPoints[2]->getX());
    cx.push_back(controlPoints[3]->getX());
    MappingValueVector cy;
    cy.push_back(controlPoints[0]->getY());
    cy.push_back(controlPoints[1]->getY());
    cy.push_back(controlPoints[2]->getY());
    cy.push_back(controlPoints[3]->getY());
    MappingValueVector cz;
    cz.push_back(controlPoints[0]->getZ());
    cz.push_back(controlPoints[1]->getZ());
    cz.push_back(controlPoints[2]->getZ());
    cz.push_back(controlPoints[3]->getZ());
    return Point(bernstein(cx, t), bernstein(cy, t), bernstein(cz, t));
}

/// Mersenne Twister random number generator.
MTRand* MT_RANDOMIZER = 0;

void initRandom()
{
    if (MT_RANDOMIZER == 0)
        MT_RANDOMIZER = new MTRand();
}

void initRandom(unsigned int seed)
{
    if (MT_RANDOMIZER == 0)
        MT_RANDOMIZER = new MTRand(seed);
    else
        MT_RANDOMIZER->seed(seed);
}

void disposeRandom()
{
    if (MT_RANDOMIZER != 0)
    {
        delete MT_RANDOMIZER;
        MT_RANDOMIZER = 0;
    }
}

unsigned int getRandomInt()
{
    if (MT_RANDOMIZER == 0)
        initRandom();
    return MT_RANDOMIZER->randInt();
}

double getRandomDouble()
{
    if (MT_RANDOMIZER == 0)
        initRandom();
    return MT_RANDOMIZER->rand();
}

double getRandomDoubleExc()
{
    if (MT_RANDOMIZER == 0)
        initRandom();
    return MT_RANDOMIZER->randExc();
}

double getRandomNorm(double mean, double stdDev)
{
    if (MT_RANDOMIZER == 0)
        initRandom();
    return MT_RANDOMIZER->randNorm(mean, stdDev);
}

Ionflux::Mapping::Point getRandomPoint()
{
    return Point(
        getRandomDouble(), 
        getRandomDouble(), 
        getRandomDouble()
    );
}

Ionflux::Mapping::Point getRandomPointExc()
{
    return Point(
        getRandomDoubleExc(), 
        getRandomDoubleExc(), 
        getRandomDoubleExc()
    );
}

Ionflux::Mapping::Point getRandomPointNorm(double meanX, 
    double stdDevX, double meanY, double stdDevY, double meanZ, 
    double stdDevZ)
{
    return Point(
        getRandomNorm(meanX, stdDevX), 
        getRandomNorm(meanY, stdDevY), 
        getRandomNorm(meanZ, stdDevZ)
    );
}

std::string defaultStr(const std::string& source, 
    const std::string& d)
{
    if (source.size() > 0)
        return source;
    return d;
}

}

}

/** \file utils.cpp
 * \brief Utility functions (implementation).
 */
