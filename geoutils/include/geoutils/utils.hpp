#ifndef IONFLUX_GEOUTILS_UTILS
#define IONFLUX_GEOUTILS_UTILS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * utils.hpp                     Utility functions (header).
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
#include <string>
#include <cfloat>
#include "ifobject/types.hpp"
#include "ifmapping/Point.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/Vector2.hpp"
#include "geoutils/Vector3.hpp"

namespace Ionflux
{

namespace GeoUtils
{

class Vertex3;
class Vertex3Set;
class BoxBoundsItemCompare;

/** Get range comparison string representation.
 *
 * Get a string representation for a range comparison result.
 * 
 * \param r Range comparison result.
 * 
 * \return String representation for the range comparison result.
 */
std::string rangeCompToString(Ionflux::GeoUtils::RangeCompResult r);

/** Get range comparison string representation (3D).
 *
 * Get a string representation for a range comparison result in three 
 * dimensions.
 * 
 * \param r Range comparison result.
 * \param target String vector in which to store the result.
 */
void rangeCompToString3(const Ionflux::GeoUtils::RangeCompResult3& r, 
    Ionflux::ObjectBase::StringVector& target);

/** Get range comparison string representation (3D).
 *
 * Get a string representation for a range comparison result in three 
 * dimensions.
 * 
 * \param r Range comparison result.
 *
 * \return String representation for the range comparison result.
 */
std::string rangeCompToString3S(const Ionflux::GeoUtils::RangeCompResult3& r);

/** Get axis string representation.
 *
 * Get a string representation for an axis identifier.
 * 
 * \param a Axis identifier.
 * 
 * \return String representation for the axis identifier.
 */
std::string axisToString(Ionflux::GeoUtils::AxisID a);

/** Get axis triple string representation.
 *
 * Get a string representation for an axis triple.
 * 
 * \param a Axis triple.
 * 
 * \return String representation for the axis triple.
 */
std::string axisToString3(Ionflux::GeoUtils::AxisTriple a);

/** Get handedness string representation.
 *
 * Get a string representation for a handedness identifier.
 * 
 * \param h Handedness identifier.
 * 
 * \return String representation for the handedness identifier.
 */
std::string handednessToString(Ionflux::GeoUtils::HandednessID h);

/** Get centering method string representation.
 *
 * Get a string representation for a centering method.
 * 
 * \param m Centering method.
 * 
 * \return String representation for the centering method.
 */
std::string centeringMethodToString(Ionflux::GeoUtils::CenteringMethod m);

/** Create integer vector.
 *
 * Create a vector of integers with 2 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * 
 * \return Vector of integers.
 */
Ionflux::ObjectBase::IntVector createIntVector2(int x0, int x1);

/** Create unsigned integer vector.
 *
 * Create a vector of unsigned integers with 2 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * 
 * \return Vector of unsigned integers.
 */
Ionflux::ObjectBase::UIntVector createUIntVector2(unsigned int x0, 
    unsigned int x1);

/** Create double vector.
 *
 * Create a vector of doubles with 2 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * 
 * \return Vector of doubles.
 */
Ionflux::ObjectBase::DoubleVector createDoubleVector2(double x0, double x1);

/** Create integer vector.
 *
 * Create a vector of integers with 3 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * \param x2 Element 2.
 * 
 * \return Vector of integers.
 */
Ionflux::ObjectBase::IntVector createIntVector3(int x0, int x1, int x2);

/** Create unsigned integer vector.
 *
 * Create a vector of unsigned integers with 3 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * \param x2 Element 2.
 * 
 * \return Vector of unsigned integers.
 */
Ionflux::ObjectBase::UIntVector createUIntVector3(unsigned int x0, 
    unsigned int x1, unsigned int x2);

/** Create double vector.
 *
 * Create a vector of doubles with 3 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * \param x2 Element 2.
 * 
 * \return Vector of doubles.
 */
Ionflux::ObjectBase::DoubleVector createDoubleVector3(double x0, double x1, 
    double x2);

/** Create integer vector.
 *
 * Create a vector of integers with 4 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * \param x2 Element 2.
 * \param x3 Element 3.
 * 
 * \return Vector of integers.
 */
Ionflux::ObjectBase::IntVector createIntVector4(int x0, int x1, 
    int x2, int x3);

/** Create unsigned integer vector.
 *
 * Create a vector of unsigned integers with 3 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * \param x2 Element 2.
 * \param x3 Element 3.
 * 
 * \return Vector of unsigned integers.
 */
Ionflux::ObjectBase::UIntVector createUIntVector4(unsigned int x0, 
    unsigned int x1, unsigned int x2, unsigned int x3);

/** Create double vector.
 *
 * Create a vector of doubles with 4 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * \param x2 Element 2.
 * \param x3 Element 3.
 * 
 * \return Vector of doubles.
 */
Ionflux::ObjectBase::DoubleVector createDoubleVector4(double x0, double x1, 
    double x2, double x3);

/** Create integer vector.
 *
 * Create a vector of integers with 4 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * \param x2 Element 2.
 * \param target Where to store the values.
 * 
 * \return Vector of integers.
 */
void createIntVector3(int x0, int x1, int x2, 
    Ionflux::ObjectBase::IntVector& target);

/** Create integer vector.
 *
 * Create a vector of integers with 4 elements.
 * 
 * \param x0 Element 0.
 * \param x1 Element 1.
 * \param x2 Element 2.
 * \param x3 Element 3.
 * \param target Where to store the values.
 * 
 * \return Vector of integers.
 */
void createIntVector4(int x0, int x1, int x2, int x3, 
    Ionflux::ObjectBase::IntVector& target);

/** Shift elements in vector.
 *
 * Shift the elements in the vector by the specified offset. Elements that 
 * would fall out of the vector are added back at the other end.
 * 
 * \param v vector
 * \param offset shift offset
 */
template<class T> 
void shift(std::vector<T>& v, int offset)
{
    if ((offset == 0) 
        || (offset == static_cast<int>(v.size()))
        || (offset == -static_cast<int>(v.size())))
        return;
    if (offset > 0)
    {
        if (offset > static_cast<int>(v.size()))
            return shift(v, offset % v.size());
        std::vector<T> temp;
        int from = v.size() - offset;
        for (int i = static_cast<int>(v.size()) - 1; i >= 0; i--)
        {
            if (i >= from)
                temp.push_back(v[i]);
            if (i < offset)
                v[i] = temp[offset - i - 1];
            else
                v[i] = v[i - offset];
        }
    } else
    {
        if (offset > -static_cast<int>(v.size()))
            return shift(v, offset % v.size());
        std::vector<T> temp;
        int from = v.size() + offset;
        for (int i = 0; i < static_cast<int>(v.size()); i++)
        {
            if (i < -offset)
                temp.push_back(v[i]);
            if (i >= from)
                v[i] = temp[i - from];
            else
                v[i] = v[i - offset];
        }
    }
}

/// Shift integer vector.
void shiftInt(Ionflux::ObjectBase::IntVector& target, int offset);

/** Comparison (with tolerance): less than.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool lt(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);

/** Comparison (with tolerance): greater than.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool gt(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);

/** Comparison (with tolerance): equal.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool eq(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);

/** Comparison (with tolerance): less than or equal.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool ltOrEq(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);

/** Comparison (with tolerance): less than or equal.
 * 
 * Compare values within the specified tolerance.
 * 
 * \param v0 Value 0.
 * \param v1 Value 1.
 * 
 * \return Result of the comparison.
 */
bool gtOrEq(double v0, double v1, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);

/// Texture coordinates equality check.
bool operator==(const Ionflux::GeoUtils::TexCoords& c0, 
    const Ionflux::GeoUtils::TexCoords& c1);

/// Texture coordinates non-equality check.
bool operator!=(const Ionflux::GeoUtils::TexCoords& c0, 
    const Ionflux::GeoUtils::TexCoords& c1);

/// Color equality check.
bool operator==(const Ionflux::GeoUtils::Color& c0, 
    const Ionflux::GeoUtils::Color& c1);

/// Color non-equality check.
bool operator!=(const Ionflux::GeoUtils::Color& c0, 
    const Ionflux::GeoUtils::Color& c1);

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
 * Extract vertex from SVG.
 *
 * Extract vertex coordinates from an SVG point specification (X,Y).
 *
 * \param rawData Source data.
 * \param target Where to store the vertex data.
 */
void extractSVGVertex(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3& target);

/**
 * Extract vertices from SVG.
 *
 * Extract vertex coordinates for multiple vertices from an SVG point 
 * specification (X,Y).
 *
 * \param rawData Source data.
 * \param target Where to store the vertex data.
 * \param closePath Add a vertex to close the path
 */
void extractSVGVertices(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3Set& target, bool closePath = true);

/**
 * Extract vertex from XML.
 *
 * Extract vertex coordinates from an XML vertex specification (X,Y,Z).
 *
 * \param rawData Source data.
 * \param target Where to store the vertex data.
 */
void extractXMLVertex(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3& target);

/**
 * Extract vertices from XML.
 *
 * Extract vertex coordinates for multiple vertices from an XML vertex 
 * specification (X,Y,Z).
 *
 * \param rawData Source data.
 * \param target Where to store the vertex data.
 */
void extractXMLVertices(const std::string& rawData, 
    Ionflux::GeoUtils::Vertex3Set& target);

/**
 * Find string.
 *
 * Find the first occurence of \c needle in \c haystack, starting at 
 * \c startPos. Characters that are escaped with the escape character are 
 * ignored for purposes of the search.
 *
 * \param haystack String in which to search.
 * \param needle String which to find.
 * \param startPos Position within \c haystack where to start the search.
 * \param escapeChar Escape character.
 * 
 * \return Position of found \c needle, or -1 if \c needle is not found.
 */
int findString(const std::string& haystack, 
    const std::string& needle, int startPos = 0, 
    char escapeChar = '\\');


/**
 * Fill tag.
 * 
 * Search the template \c source for tags with the specified name. Replace 
 * each tag with the replacement string. Tags are delimited by \c tagStart 
 * and \c tagEnd. \c '\\' can be used as an escape character within the 
 * template source.
 * 
 * \param source Source template.
 * \param tagName Tag name.
 * \param replacement Replacement string.
 * \param tagStart Tag start delimiter.
 * \param tagEnd Tag end delimiter.
 *
 * \return Result string.
 */
std::string fillTag(const std::string& source, const std::string& tagName, 
    const std::string& replacement, const std::string& tagStart = "{$", 
    const std::string& tagEnd = "}");

/**
 * Fill tag.
 *
 * Search the template \c source for tags. Replace each tag with the 
 * string specified in the replacement dictionary for that tag. Tags are 
 * delimited by \c tagStart and \c tagEnd. \c '\\' can be used as an escape 
 * character within the template source.
 * 
 * \param source Source template.
 * \param replacement Replacement dictionary.
 * \param partial Keep tags for which a replacement has not been specified.
 * \param tagStart Tag start delimiter.
 * \param tagEnd Tag end delimiter.
 *
 * \return Result string.
 */
std::string fillTags(const std::string& source, 
    const Ionflux::GeoUtils::Dictionary& replacement, bool partial = false, 
    const std::string& tagStart = "{$", const std::string& tagEnd = "}");

/**
 * Get SVG shape style.
 *
 * Get a style specfification for an SVG shape.
 *
 * \param color Fill color.
 * \param fillOpacity Fill opacity.
 * \param strokeColor Stroke color.
 * \param strokeOpacity Stroke opacity.
 * \param strokeWidth Stroke width.
 * \param strokeMiterLimit Stroke miter limit.
 * \param strokeDashArray Stroke dash array.
 * \param shapeType Shape type.
 * \param closePath Close path.
 *
 * \return Polygon style attribute.
 */
Ionflux::GeoUtils::SVGShapeStyle getSVGShapeStyle(
    const std::string& color = "#20e045", double fillOpacity = 0.533, 
    const std::string& strokeColor = "#0e1723", double strokeOpacity = 1., 
    double strokeWidth = 1., double strokeMiterLimit = 4, 
    const std::string& strokeDashArray = "none", 
    Ionflux::GeoUtils::SVGShapeType shapeType = 
    Ionflux::GeoUtils::DEFAULT_SHAPE_TYPE, bool closePath = true);

/// Shape style equality check.
bool operator==(const Ionflux::GeoUtils::SVGShapeStyle& s0, 
    const Ionflux::GeoUtils::SVGShapeStyle & s1);

/// Shape style non-equality check.
bool operator!=(const Ionflux::GeoUtils::SVGShapeStyle& s0, 
    const Ionflux::GeoUtils::SVGShapeStyle & s1);

/**
 * Get SVG polygon style.
 *
 * Get a style attribute for an SVG polygon (or other shape). The style  
 * attribute is created by filling in the corresponding tags in the specified 
 * template.
 *
 * \param color Fill color.
 * \param fillOpacity Fill opacity.
 * \param strokeColor Stroke color.
 * \param strokeOpacity Stroke opacity.
 * \param strokeWidth Stroke width.
 * \param strokeMiterLimit Stroke miter limit.
 * \param strokeDashArray Stroke dash array.
 * \param attrTemplate Attribute template.
 *
 * \return Polygon style attribute.
 */
std::string getSVGPolygonStyle(const std::string& color = "#20e045", 
    double fillOpacity = 0.533, const std::string& strokeColor = "#0e1723", 
    double strokeOpacity = 1., double strokeWidth = 1., 
    double strokeMiterLimit = 4, const std::string& strokeDashArray = "none", 
    const std::string& attrTemplate = SVG_POLY_STYLE_TEMPLATE);

/**
 * Get SVG polygon style.
 *
 * Get a style attribute for an SVG polygon (or other shape).
 *
 * \param style Style specification.
 * \param fillOpacity Fill opacity.
 * \param strokeColor Stroke color.
 * \param strokeOpacity Stroke opacity.
 * \param strokeWidth Stroke width.
 * \param strokeMiterLimit Stroke miter limit.
 * \param strokeDashArray Stroke dash array.
 * \param attrTemplate Attribute template.
 *
 * \return Polygon style attribute.
 */
std::string getSVGPolygonStyle(const Ionflux::GeoUtils::SVGShapeStyle& style, 
    const std::string& attrTemplate = SVG_POLY_STYLE_TEMPLATE);

/**
 * Get SVG image.
 * 
 * Get the full XML code for a ready-to-use, editable SVG image of the 
 * specified dimensions, containing the specified data. The origin of the 
 * coordinate system for the data is initialized to the specified coordinates.
 *
 * \param data SVG data.
 * \param width Image width (in pixels).
 * \param height Image height (in pixels).
 * \param originX X coordinate of origin.
 * \param originY Y coordinate of origin.
 * \param svgTemplate Template for the SVG XML code.
 *
 * \return XML code for an SVG image.
 */
std::string getSVGImage(const std::string& data, unsigned int width = 1000, 
    unsigned int height = 1000, int originX = 500, int originY = 500, 
    const std::string& svgTemplate = SVG_TEMPLATE);

/** Transform coordinates to sequence index.
 * 
 * Transform the specified coordinates for the given dimensions to a sequence 
 * index, where it is assumed that the dimension with the lower index changes 
 * first within the sequence. In other words, this function calculates the 
 * index into a linear array that corresponds to the specified coordinates 
 * within a multi-dimensional array of the specified dimensions. This is the 
 * inverse operation of seqToCoords().
 *
 * \param coords Vector of coordinates.
 * \param dimensions Vector of dimensions.
 * 
 * \return Sequence index.
 */
unsigned int coordsToSeq(const Ionflux::ObjectBase::UIntVector& coords, 
    const Ionflux::ObjectBase::UIntVector& dimensions);

/** Sequence index to coordinates.
 * 
 * Transform the specified sequence index to coordinates for the given 
 * dimensions, where it is assumed that the dimension with the lower index 
 * changes first within the sequence. In other words, this function calculates 
 * the coordinates within a multi-dimensional array of the specified 
 * dimensions that correspond to the index into a linear array given by the 
 * sequence index. This is the inverse operation of coordsToSeq().
 *
 * \param seq Sequence index.
 * \param dimensions Vector of dimensions.
 * \param target Where to store the coordinates.
 */
void seqToCoords(unsigned int seq, 
    const Ionflux::ObjectBase::UIntVector& dimensions, 
    Ionflux::ObjectBase::UIntVector& target);

/** Get relative coordinates.
 * 
 * Transform the specified coordinates to relative values in the interval 
 * [0..1], where 0 corresponds to coordinate 0 and 1 to the highest possible 
 * valid coordinate value.
 *
 * \param coords Vector of coordinates.
 * \param dimensions Vector of dimensions.
 * \param target Where to store the relative coordinates.
 * 
 * \return Sequence index.
 */
void getCoordsRel(const Ionflux::ObjectBase::UIntVector& coords, 
    const Ionflux::ObjectBase::UIntVector& dimensions, 
    Ionflux::ObjectBase::DoubleVector& target);

/** Set to vector.
 * 
 * Add all items from the set to the specified vector.
 * 
 * \param bs set
 * \param bv vector
 */
void setToVector(const Ionflux::GeoUtils::BoxBoundsItemSet& bs,
    Ionflux::GeoUtils::BoxBoundsItemVector& bv);

/** Sort.
 *
 * Sort a vector using the specified comparison function object. If no 
 * comparison function object is specified, a default comparison will be 
 * used. The comparison function object is referenced.
 * 
 * \param bv vector
 * \param comp comparison function object
 */
void sort(Ionflux::GeoUtils::BoxBoundsItemVector& bv, 
    Ionflux::GeoUtils::BoxBoundsItemCompare* comp = 0);

/** Solve quadratic equation.
 * 
 * Solve a quadratic equation of the form ax² + bx + c = 0. An exception is 
 * thrown if the parameters are invalid or if the quadratic equation does not 
 * have real solutions.
 *
 * \param a parameter a
 * \param b parameter b
 * \param c parameter c
 *
 * \return The solutions of the quadratic equation.
 */
Ionflux::GeoUtils::Vector2 solveQuadraticEquation(
    double a, double b, double c);

/** Solve cubic equation.
 * 
 * Solve a cubic equation of the form ax³ + bx² + cx + d = 0. An exception is 
 * thrown if the parameters are invalid.
 *
 * \param a parameter a
 * \param b parameter b
 * \param c parameter c
 * \param d parameter d
 * \param target Where to store the solutions.
 *
 * \return The number of solutions.
 */
int solveCubicEquation(double a, double b, double c, double d, 
    Ionflux::GeoUtils::Vector3& target);

/** Calculate Bezier control points.
 * 
 * Calculate the control point positions for a Bezier curve segment 
 * that connects vertices \c v0 and \c v1. The \c smoothness parameter 
 * specifies the distance of the inner control points of the Bezier curve 
 * segment as a fraction of the edge length.
 *
 * \param v0 vertex (0)
 * \param v1 vertex (1)
 * \param p0 control point (0)
 * \param p1 control point (1)
 * \param p2 control point (2)
 * \param p3 control point (3)
 * \param smoothness smoothness parameter
 */
void calculateLineBezierControlPoints(
    const Ionflux::GeoUtils::Vertex3& v0, 
    const Ionflux::GeoUtils::Vertex3& v1, 
    Ionflux::Mapping::Point& p0, 
    Ionflux::Mapping::Point& p1, 
    Ionflux::Mapping::Point& p2, 
    Ionflux::Mapping::Point& p3, 
    double smoothness = 0.2);

/** Calculate Bezier control points.
 * 
 * Calculate the control point positions for two Bezier curve segments 
 * that connect at vertex \c v1, given its neighbouring vertices \c v0 and 
 * \c v2. The \c smoothness parameter can be used to determine how closely 
 * the curve will follow the original edges. \c smoothness specifies 
 * the distance of the control points of the Bezier curve segments 
 * originating at vertex \c v1 as a fraction of the average edge length at 
 * that vertex, i.e. the average distance of \c v1 to \c v0 and \c v2.
 * Control points are placed on the tangent at \c v1 parallel to the line 
 * connecting \c v0 and \c v1.
 *
 * \param v0 vertex (0)
 * \param v1 vertex (1)
 * \param v2 vertex (2)
 * \param p0 control point (0)
 * \param p1 control point (1)
 * \param p2 control point (2)
 * \param smoothness smoothness parameter
 */
void calculateInnerBezierControlPoints(
    const Ionflux::GeoUtils::Vertex3& v0, 
    const Ionflux::GeoUtils::Vertex3& v1, 
    const Ionflux::GeoUtils::Vertex3& v2, 
    Ionflux::Mapping::Point& p0, 
    Ionflux::Mapping::Point& p1, 
    Ionflux::Mapping::Point& p2, 
    double smoothness = 0.2);

/** Calculate Bezier control points.
 * 
 * Calculate the control point position for an outer vertex of a Bezier 
 * curve segment. Depending on the order of control points in the 
 * parameter list, the position of either p1 or p2 can be calculated. 
 * The \c smoothness parameter can be used to determine how closely the 
 * curve will follow the original edge. \c smoothness specifies the distance 
 * of the control point of the Bezier curve segment originating at point 
 * \c p0 as a fraction of the average edge length at that point. The control 
 * point is placed on the tangent through \c p2 parallel to the line 
 * connecting \c p0 and \c p3.
 *
 * \param p0 control point (0)
 * \param p1 control point (1)
 * \param p2 control point (2)
 * \param p3 control point (3)
 * \param smoothness smoothness parameter
 */
void calculateOuterBezierControlPoint(
    const Ionflux::Mapping::Point* p0, 
    Ionflux::Mapping::Point* p1, 
    const Ionflux::Mapping::Point* p2, 
    const Ionflux::Mapping::Point* p3, 
    double smoothness = 0.2);

namespace TransformNodes
{

/**
 * Create input node specification.
 * 
 * Create an input node specification that can be used to connect input 
 * nodes to a transform node.
 *
 * \param node Node.
 * \param outputID Output ID.
 *
 * \return Input node specification.
 */
Ionflux::GeoUtils::TransformNodes::InputNodeSpec createInputNodeSpec(
    Ionflux::GeoUtils::TransformNodes::TransformNode* node, 
    unsigned int outputID);

/// Input node specification equality check.
bool operator==(const Ionflux::GeoUtils::TransformNodes::InputNodeSpec& s0, 
    const Ionflux::GeoUtils::TransformNodes::InputNodeSpec & s1);

/// Input node specification non-equality check.
bool operator!=(const Ionflux::GeoUtils::TransformNodes::InputNodeSpec& s0, 
    const Ionflux::GeoUtils::TransformNodes::InputNodeSpec & s1);

}

/// Comparison object for axis-aligned plane pair intersection.
struct AAPlanePairIntersectionCompare
{
    /// Comparison operator.
    bool operator()(const AAPlanePairIntersection& i0, 
        const AAPlanePairIntersection& i1);
};

/// Create axis-aligned plane pair intersection.
Ionflux::GeoUtils::AAPlanePairIntersection createAAPlanePairIntersection(
    bool valid = false, double tNear = -DBL_MAX, double tFar = DBL_MAX, 
    Ionflux::GeoUtils::PlaneMask nearPlane = PLANE_UNDEFINED, 
    Ionflux::GeoUtils::PlaneMask farPlane = PLANE_UNDEFINED);

/// Comparison operator.
bool operator==(const Ionflux::GeoUtils::AAPlanePairIntersection& i0, 
    const Ionflux::GeoUtils::AAPlanePairIntersection& i1);

/// Get string representation for plane mask.
std::string getPlaneMaskValueString(Ionflux::GeoUtils::PlaneMask mask);

/// Get string representation for axis-aligned plane pair intersection.
std::string getAAPlanePairIntersectionValueString(
    const AAPlanePairIntersection& i0);

}

}

/** \file utils.hpp
 * \brief Utility functions (header).
 */
#endif
