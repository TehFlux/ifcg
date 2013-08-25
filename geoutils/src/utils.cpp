/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.cpp                     Utility functions (implementation).
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
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include "geoutils/utils.hpp"
#include "geoutils/Vertex3.hpp"
#include "geoutils/Vertex3Set.hpp"
#include "geoutils/GeoUtilsError.hpp"
#include "geoutils/BoxBoundsItemCompare.hpp"
#include "geoutils/BoxBoundsItemCompareAxis.hpp"

namespace Ionflux
{

namespace GeoUtils
{

std::string rangeCompToString(Ionflux::GeoUtils::RangeCompResult r)
{
    if (r == RANGE_EQUAL)
        return "RANGE_EQUAL";
    if (r == RANGE_OTHER_CONTAINS)
        return "RANGE_OTHER_CONTAINS";
    if (r == RANGE_FIRST_CONTAINS)
        return "RANGE_FIRST_CONTAINS";
    if (r == RANGE_OVERLAP)
        return "RANGE_OVERLAP";
    if (r == RANGE_DISJOINT)
        return "RANGE_DISJOINT";
    return "<unknown>";
}

void rangeCompToString3(const Ionflux::GeoUtils::RangeCompResult3& r, 
    Ionflux::ObjectBase::StringVector& target)
{
    target.clear();
    target.push_back(rangeCompToString(r.x));
    target.push_back(rangeCompToString(r.y));
    target.push_back(rangeCompToString(r.z));
}

std::string rangeCompToString3S(const Ionflux::GeoUtils::RangeCompResult3& r)
{
    std::ostringstream result;
    result << "[" << rangeCompToString(r.x) << ", " 
        << rangeCompToString(r.y) << ", " << rangeCompToString(r.z) << "]";
    return result.str();
}

std::string axisToString(Ionflux::GeoUtils::AxisID a)
{
    if (a == AXIS_X)
        return "AXIS_X";
    if (a == AXIS_Y)
        return "AXIS_Y";
    if (a == AXIS_Z)
        return "AXIS_Z";
    if (a == AXIS_W)
        return "AXIS_W";
    return "<unknown>";
}

std::string axisToString3(Ionflux::GeoUtils::AxisTriple a)
{
    std::ostringstream result;
    result << "[" << axisToString(a.a0) << ", " 
        << axisToString(a.a1) << ", " << axisToString(a.a2) << "]";
    return result.str();
}

std::string handednessToString(Ionflux::GeoUtils::HandednessID h)
{
    if (h == HANDEDNESS_RIGHT)
        return "HANDEDNESS_RIGHT";
    if (h == HANDEDNESS_LEFT)
        return "HANDEDNESS_LEFT";
    return "<unknown>";
}

std::string centeringMethodToString(Ionflux::GeoUtils::CenteringMethod m)
{
    if (m == CENTER_BARYCENTER)
        return "CENTER_BARYCENTER";
    if (m == CENTER_BOUNDS)
        return "CENTER_BOUNDS";
    if (m == CENTER_ORIGIN)
        return "CENTER_ORIGIN";
    return "<unknown>";
}

Ionflux::ObjectBase::IntVector createIntVector2(int x0, int x1)
{
    Ionflux::ObjectBase::IntVector v0;
    v0.push_back(x0);
    v0.push_back(x1);
    return v0;
}

Ionflux::ObjectBase::UIntVector createUIntVector2(unsigned int x0, 
    unsigned int x1)
{
    Ionflux::ObjectBase::UIntVector v0;
    v0.push_back(x0);
    v0.push_back(x1);
    return v0;
}

Ionflux::ObjectBase::DoubleVector createDoubleVector2(double x0, double x1)
{
    Ionflux::ObjectBase::DoubleVector v0;
    v0.push_back(x0);
    v0.push_back(x1);
    return v0;
}

Ionflux::ObjectBase::IntVector createIntVector3(int x0, int x1, int x2)
{
    Ionflux::ObjectBase::IntVector v0;
    v0.push_back(x0);
    v0.push_back(x1);
    v0.push_back(x2);
    return v0;
}

Ionflux::ObjectBase::UIntVector createUIntVector3(unsigned int x0, 
    unsigned int x1, unsigned int x2)
{
    Ionflux::ObjectBase::UIntVector v0;
    v0.push_back(x0);
    v0.push_back(x1);
    v0.push_back(x2);
    return v0;
}

Ionflux::ObjectBase::DoubleVector createDoubleVector3(double x0, double x1, 
    double x2)
{
    Ionflux::ObjectBase::DoubleVector v0;
    v0.push_back(x0);
    v0.push_back(x1);
    v0.push_back(x2);
    return v0;
}

bool lt(double v0, double v1, double t)
{
    if (v0 < (v1 - t))
        return true;
    return false;
}

bool gt(double v0, double v1, double t)
{
    if (v0 > (v1 + t))
        return true;
    return false;
}

bool eq(double v0, double v1, double t)
{
    if (!(gt(v0, v1, t) || lt(v0, v1, t)))
        return true;
    return false;
}

bool ltOrEq(double v0, double v1, double t)
{
    if (!gt(v0, v1, t))
        return true;
    return false;
}

bool gtOrEq(double v0, double v1, double t)
{
    if (!lt(v0, v1, t))
        return true;
    return false;
}

bool operator==(const Ionflux::GeoUtils::TexCoords& c0, 
    const Ionflux::GeoUtils::TexCoords& c1)
{
    return (c0.u == c1.u) && (c0.v == c1.v);
}

bool operator!=(const Ionflux::GeoUtils::TexCoords& c0, 
    const Ionflux::GeoUtils::TexCoords& c1)
{
    return !(c0 == c1);
}

bool operator==(const Ionflux::GeoUtils::Color& c0, 
    const Ionflux::GeoUtils::Color& c1)
{
    return (c0.red == c1.red) && (c0.green == c1.green) 
        && (c0.blue == c1.blue) && (c0.alpha == c1.alpha);
}

bool operator!=(const Ionflux::GeoUtils::Color& c0, 
    const Ionflux::GeoUtils::Color& c1)
{
    return !(c0 == c1);
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

void extractSVGVertex(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3& target)
{
    Ionflux::ObjectBase::StringVector parts0;
    explode(rawData, ",", parts0);
    if (parts0.size() < 2)
    {
        std::ostringstream message;
        message << "[extractSVGVertex] Invalid vertex specification: '" 
            << rawData << "'";
        throw GeoUtilsError(message.str());
    }
    target.setX(strtod(parts0[0].c_str(), 0));
    target.setY(strtod(parts0[1].c_str(), 0));
    target.setZ(0.);
    /* <---- DEBUG ----- //
    std::cerr << "[extractSVGVertex] v = " << target.getString() 
        << std::endl;
    // ----- DEBUG ----> */
}

void extractSVGVertices(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3Set& target, bool closePath)
{
    Ionflux::ObjectBase::StringVector parts0;
    if (rawData.size() == 0)
        return;
    // NOTE: This is rather ugly. Implement proper SVG path parsing.
    bool relative = false;
    if (rawData[0] == 'm')
        relative = true;
    explode(rawData, " ", parts0);
    Vertex3* first = 0;
    Vertex3* prev = 0;
    for (Ionflux::ObjectBase::StringVector::iterator i = parts0.begin(); 
        i != parts0.end(); i++)
    {
        std::string it0 = *i;
        if (it0.size() >= 3)
        {
            Vertex3* v0 = Vertex3::create();
            extractSVGVertex(it0, *v0);
            if (relative)
            {
                if (first == 0)
                    first = v0;
                else
                    v0->translate(prev->getVector());
                prev = v0;
            }
            target.addVertex(v0);
        }
    }
    if (closePath 
        && relative 
        && (first != 0))
    {
        Vertex3* v0 = Vertex3::create();
        *v0 = *first;
        target.addVertex(v0);
    }
}

void extractXMLVertex(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3& target)
{
    Ionflux::ObjectBase::StringVector parts0;
    explode(rawData, ",", parts0);
    if (parts0.size() < 3)
    {
        std::ostringstream message;
        message << "[extractXMLVertex] Invalid vertex specification: '" 
            << rawData << "'";
        throw GeoUtilsError(message.str());
    }
    target.setX(strtod(parts0[0].c_str(), 0));
    target.setY(strtod(parts0[1].c_str(), 0));
    target.setZ(strtod(parts0[2].c_str(), 0));
}

void extractXMLVertices(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3Set& target)
{
    Ionflux::ObjectBase::StringVector parts0;
    explode(rawData, " ", parts0);
    for (Ionflux::ObjectBase::StringVector::iterator i = parts0.begin(); 
        i != parts0.end(); i++)
    {
        std::string it0 = *i;
        if (it0.size() >= 5)
        {
            Vertex3* v0 = Vertex3::create();
            extractXMLVertex(it0, *v0);
            target.addVertex(v0);
        }
    }
}

int findString(const std::string& haystack, const std::string& needle, 
    int startPos, char escapeChar)
{
    /* <---- DEBUG ----- //
    std::ostringstream message;
    // <---- DEBUG ----- */
    while (startPos < 0)
        startPos += haystack.size();
    if (static_cast<unsigned int>(startPos) >= haystack.size())
        return -1;
    unsigned int i = startPos;
    unsigned int j = 0;
    unsigned int k = 0;
    bool found = false;
    unsigned int needleSize = needle.size();
    while (!found 
        && (i < haystack.size()))
    {
        /* <---- DEBUG ----- //
        message.str("");
        message << "[findString] DEBUG: i = " << i << ", j = " << j 
            << ", k = " << k << ", " << "haystack[i] = " << haystack[i] 
            << ", needle[j] = " << needle[j];
            std::cerr << message.str() << std::endl;
        // <---- DEBUG ----- */
        char c = haystack[i];
        if (c == escapeChar)
            // Skip next character.
            i++;
        else
        if (c == needle[j])
        {
            // Current haystack character matches current needle character.
            if (j == 0)
                /* Start of needle comparison.
                   Save search start position in case the comparison fails. */
                k = i;
            if ((needleSize == 1) 
                || (j == (needleSize - 1)))
                // Success!
                found = true;
            j++;
        } else
        {
            /* Current haystack character does not match current needle 
               character. */
            if (j > 0)
            {
                /* If inside a needle comparison, reset needle and haystack 
                   positions. */
                j = 0;
                i = k;
            }
        }
        i++;
    }
    if (found)
        return k;
    return -1;
}

std::string fillTag(const std::string& source, const std::string& tagName, 
    const std::string& replacement, const std::string& tagStart, 
    const std::string& tagEnd)
{
    unsigned int i = 0;
    unsigned int k = 0;
    std::ostringstream result;
    std::string tag(tagStart + tagName + tagEnd);
    while (i < source.size())
    {
        int nextTagPos = findString(source, tag, i);
        if (nextTagPos > 0)
        {
            result << source.substr(i, nextTagPos - i) << replacement;
            i = nextTagPos + tag.size();
            k++;
        } else
        {
            result << source.substr(i);
            i = source.size();
        }
    }
    return result.str();
}

std::string fillTags(const std::string& source, 
    const Ionflux::GeoUtils::Dictionary& replacement, bool partial, 
    const std::string& tagStart, const std::string& tagEnd)
{
    unsigned int i = 0;
    unsigned int k = 0;
    std::ostringstream result;
    std::string tagName = "";
    while (i < source.size())
    {
        int nextTagPos = findString(source, tagStart, i);
        if (nextTagPos > 0)
        {
            int tagEndPos = findString(source, tagEnd, nextTagPos 
                + tagStart.size());
            tagName = "";
            if (tagEndPos > 0)
            {
                // Append data preceding the tag.
                result << source.substr(i, nextTagPos - i);
                tagName = source.substr(nextTagPos + tagStart.size(), 
                    tagEndPos - nextTagPos - tagStart.size());
                Dictionary::const_iterator r = replacement.find(tagName);
                if (r != replacement.end())
                    // Append the replacement.
                    result << (*r).second;
                else
                {
                    if (!partial)
                    {
                        result.str("");
                        result << "No replacement given for tag '" << tagName 
                            << "'.";
                        throw GeoUtilsError(result.str());
                    } else
                        // Append the tag.
                        result << tagStart << tagName << tagEnd;
                }
            } else
            {
                result.str("");
                result << "Incomplete tag at position " << nextTagPos << ".";
                throw GeoUtilsError(result.str());
            }
            i = nextTagPos + tagStart.size() + tagName.size() + tagEnd.size();
            k++;
        } else
        {
            result << source.substr(i);
            i = source.size();
        }
    }
    return result.str();
}

Ionflux::GeoUtils::SVGShapeStyle getSVGShapeStyle(
    const std::string& color, double fillOpacity, 
    const std::string& strokeColor, double strokeOpacity, 
    double strokeWidth, double strokeMiterLimit, 
    const std::string& strokeDashArray, 
    Ionflux::GeoUtils::SVGShapeType shapeType, bool closePath)
{
    SVGShapeStyle result;
    result.color = color;
    result.fillOpacity = fillOpacity;
    result.strokeColor = strokeColor;
    result.strokeOpacity = strokeOpacity;
    result.strokeWidth = strokeWidth;
    result.strokeMiterLimit = strokeMiterLimit;
    result.strokeDashArray = strokeDashArray;
    result.shapeType = shapeType;
    result.closePath = closePath;
    return result;
}

bool operator==(const Ionflux::GeoUtils::SVGShapeStyle& s0, 
    const Ionflux::GeoUtils::SVGShapeStyle & s1)
{
    return (s0.color == s1.color) 
        && (s0.fillOpacity == s1.fillOpacity) 
        && (s0.strokeColor == s1.strokeColor) 
        && (s0.strokeOpacity == s1.strokeOpacity) 
        && (s0.strokeWidth == s1.strokeWidth) 
        && (s0.strokeMiterLimit == s1.strokeMiterLimit) 
        && (s0.strokeDashArray == s1.strokeDashArray) 
        && (s0.shapeType == s1.shapeType) 
        && (s0.closePath == s1.closePath);
}

bool operator!=(const Ionflux::GeoUtils::SVGShapeStyle& s0, 
    const Ionflux::GeoUtils::SVGShapeStyle & s1)
{
    return !(s0 == s1);
}

std::string getSVGPolygonStyle(const std::string& color, 
    double fillOpacity, const std::string& strokeColor, 
    double strokeOpacity, double strokeWidth, 
    double strokeMiterLimit, const std::string& strokeDashArray, 
    const std::string& attrTemplate)
{
    std::ostringstream v0;
    Dictionary d0;
    d0["color"] = color;
    d0["strokeColor"] = strokeColor;
    d0["strokeDashArray"] = strokeDashArray;
    v0.str("");
    v0 << fillOpacity;
    d0["fillOpacity"] = v0.str();
    v0.str("");
    v0 << strokeOpacity;
    d0["strokeOpacity"] = v0.str();
    v0.str("");
    v0 << strokeWidth;
    d0["strokeWidth"] = v0.str();
    v0.str("");
    v0 << strokeMiterLimit;
    d0["strokeMiterLimit"] = v0.str();
    return fillTags(attrTemplate, d0);
}

std::string getSVGPolygonStyle(const Ionflux::GeoUtils::SVGShapeStyle& style, 
    const std::string& attrTemplate)
{
    return getSVGPolygonStyle(style.color, style.fillOpacity, 
        style.strokeColor, style.strokeOpacity, style.strokeWidth, 
        style.strokeMiterLimit, style.strokeDashArray, attrTemplate);
}

std::string getSVGImage(const std::string& data, unsigned int width, 
    unsigned int height, int originX, int originY, 
    const std::string& svgTemplate)
{
    std::ostringstream v0;
    Dictionary d0;
    d0["data"] = data;
    v0.str("");
    v0 << width;
    d0["width"] = v0.str();
    v0.str("");
    v0 << height;
    d0["height"] = v0.str();
    v0.str("");
    v0 << originX;
    d0["originX"] = v0.str();
    v0.str("");
    v0 << originY;
    d0["originY"] = v0.str();
    return fillTags(svgTemplate, d0);
}

unsigned int coordsToSeq(const Ionflux::ObjectBase::UIntVector& coords, 
    const Ionflux::ObjectBase::UIntVector& dimensions)
{
    unsigned int maxIndex = coords.size();
    if (coords.size() > dimensions.size())
        maxIndex = dimensions.size();
    unsigned int result = 0;
    unsigned int f = 1;
    for (unsigned int i = 0; i < maxIndex; i++)
    {
        unsigned int d = dimensions[i];
        unsigned int c = coords[i];
        if (c >= d)
        {
            std::ostringstream status;
            status << "[coordsToSeq] Invalid coordinate (i = " << i 
                << ", c = " << c << ", dimensions = (";
            for (unsigned int i = 0; i < dimensions.size(); i++)
            {
                if (i > 0)
                    status << ", ";
                status << dimensions[i];
            }
            status << ")!";
            throw GeoUtilsError(status.str());
        }
        result += f * c;
        f *= d;
    }
    return result;
}

void seqToCoords(unsigned int seq, 
    const Ionflux::ObjectBase::UIntVector& dimensions, 
    Ionflux::ObjectBase::UIntVector& target)
{
    target.clear();
    unsigned int c0 = seq;
    for (unsigned int i = 0; i < dimensions.size(); i++)
    {
        unsigned int d = dimensions[i];
        unsigned int r = c0 % d;
        c0 = static_cast<unsigned int>(c0 / d);
        target.push_back(r);
    }
    if (c0 != 0)
    {
        std::ostringstream status;
        status << "[seqToCoords] Invalid sequence index (seq = " << seq 
            << ", dimensions = (";
        for (unsigned int i = 0; i < dimensions.size(); i++)
        {
            if (i > 0)
                status << ", ";
            status << dimensions[i];
        }
        status << ")!";
        throw GeoUtilsError(status.str());
    }
}

void getCoordsRel(const Ionflux::ObjectBase::UIntVector& coords, 
    const Ionflux::ObjectBase::UIntVector& dimensions, 
    Ionflux::ObjectBase::DoubleVector& target)
{
    target.clear();
    unsigned int maxIndex = coords.size();
    if (coords.size() > dimensions.size())
        maxIndex = dimensions.size();
    /* <---- DEBUG ----- //
    std::cout << "[getCoordsRel] DEBUG: maxIndex = " << maxIndex 
        << std::endl;
    // ----- DEBUG ----> */
    for (unsigned int i = 0; i < maxIndex; i++)
    {
        unsigned int d = dimensions[i];
        unsigned int c = coords[i];
        if (c >= d)
        {
            std::ostringstream status;
            status << "[getCoordsRel] Invalid coordinate (i = " << i 
                << ", c = " << c << ", dimensions = (";
            for (unsigned int k = 0; k < dimensions.size(); k++)
            {
                if (k > 0)
                    status << ", ";
                status << dimensions[k];
            }
            status << ")!";
            throw GeoUtilsError(status.str());
        }
        double r0 = static_cast<double>(c) / (d - 1);
        /* <---- DEBUG ----- //
        std::cout << "[getCoordsRel] DEBUG: Adding relCoord: " << r0 
            << std::endl;
        // ----- DEBUG ----> */
        target.push_back(r0);
    }
}

void setToVector(const Ionflux::GeoUtils::BoxBoundsItemSet& bs,
    Ionflux::GeoUtils::BoxBoundsItemVector& bv)
{
    Ionflux::GeoUtils::BoxBoundsItemSet::const_iterator i;
    for (i = bs.begin(); i != bs.end(); i++)
        bv.push_back(*i);
}

void sort(Ionflux::GeoUtils::BoxBoundsItemVector& bv, 
    Ionflux::GeoUtils::BoxBoundsItemCompare* comp)
{
    BoxBoundsItemCompare wrap0;
    if (comp == 0)\
        wrap0.setTarget(BoxBoundsItemCompareAxis::create(AXIS_Z));
    else
        wrap0.setTarget(comp);
    std::sort(bv.begin(), bv.end(), wrap0);
}

Ionflux::GeoUtils::Vector2 solveQuadraticEquation(
    double a, double b, double c)
{
    if (a == 0)
    {
        std::ostringstream status;
        status << "[solveQuadraticEquation] "
            "Invalid parameter value: a = " << a;
        throw GeoUtilsError(status.str());
    }
    double d = -b / (2. * a);
    double e = b * b - 4. * c * a;
    if (e < 0)
    {
        std::ostringstream status;
        status << "[solveQuadraticEquation] "
            "Quadratic equation does not have real solutions "
            "(a = " << a << ", b = " << b << ", c = " << c << ").";
        throw GeoUtilsError(status.str());
    }
    return Vector2(d + ::sqrt(e), d - ::sqrt(e));
}

namespace TransformNodes
{

Ionflux::GeoUtils::TransformNodes::InputNodeSpec createInputNodeSpec(
    Ionflux::GeoUtils::TransformNodes::TransformNode* node, 
    unsigned int outputID)
{
    InputNodeSpec s0;
    s0.node = node;
    s0.outputID = outputID;
    return s0;
}

bool operator==(const Ionflux::GeoUtils::TransformNodes::InputNodeSpec& s0, 
    const Ionflux::GeoUtils::TransformNodes::InputNodeSpec & s1)
{
    return (s0.node == s1.node) && (s0.outputID == s1.outputID);
}

bool operator!=(const Ionflux::GeoUtils::TransformNodes::InputNodeSpec& s0, 
    const Ionflux::GeoUtils::TransformNodes::InputNodeSpec & s1)
{
    return !(s0 == s1);
}

}

}

}

/** \file utils.cpp
 * \brief Utility functions (implementation).
 */
