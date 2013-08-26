#ifndef IONFLUX_GEOUTILS_CONSTANTS
#define IONFLUX_GEOUTILS_CONSTANTS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * constants.hpp                     Constant definitions.
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
#include <climits>
#include "geoutils/types.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Default tolerance for comparisons.
const double DEFAULT_TOLERANCE = 1.0e-6;

/// Axis ID: X.
const Ionflux::GeoUtils::AxisID AXIS_X = 0;
/// Axis ID: Y.
const Ionflux::GeoUtils::AxisID AXIS_Y = 1;
/// Axis ID: Z.
const Ionflux::GeoUtils::AxisID AXIS_Z = 2;
/// Axis ID: W.
const Ionflux::GeoUtils::AxisID AXIS_W = 3;

/// Handedness ID: left.
const Ionflux::GeoUtils::HandednessID HANDEDNESS_LEFT = 0;
/// Handedness ID: right.
const Ionflux::GeoUtils::HandednessID HANDEDNESS_RIGHT = 1;

/// Range comparison result: ranges are equal.
const Ionflux::GeoUtils::RangeCompResult RANGE_EQUAL = 0;
/// Range comparison result: other range contains first range.
const Ionflux::GeoUtils::RangeCompResult RANGE_OTHER_CONTAINS = -1;
/// Range comparison result: first range contains other range.
const Ionflux::GeoUtils::RangeCompResult RANGE_FIRST_CONTAINS = 1;
/// Range comparison result: ranges overlap.
const Ionflux::GeoUtils::RangeCompResult RANGE_OVERLAP = 2;
/// Range comparison result: ranges are disjoint.
const Ionflux::GeoUtils::RangeCompResult RANGE_DISJOINT = 3;

/// XML header.
const std::string XML_HEADER = "<?xml version=\"1.0\" " 
    "encoding=\"UTF-8\" ?>\n";
/// Default attributes used for rendering SVG polygons.
const std::string SVG_DEFAULT_POLY_STYLE = 
    "style=\"fill:#20e045;fill-opacity:0.53333336;"
    "stroke:#0e1723;stroke-opacity:1;stroke-width:1;stroke-miterlimit:4;"
    "stroke-dasharray:none\"";
/// Template for SVG polygon styles.
const std::string SVG_POLY_STYLE_TEMPLATE = 
"style=\"fill:{$color};fill-opacity:{$fillOpacity};"
    "stroke:{$strokeColor};stroke-opacity:{$strokeOpacity};"
    "stroke-width:{$strokeWidth};stroke-miterlimit:{$strokeMiterLimit};"
    "stroke-dasharray:{$strokeDashArray}\"";
/// SVG template header.
const std::string SVG_DEFAULT_HEADER = "<?xml version=\"1.0\""
    " encoding=\"UTF-8\" standalone=\"no\"?>\n"
    "<!-- Created with Inkscape (http://www.inkscape.org/) -->\n"
    "<svg\n"
    "   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
    "   xmlns:cc=\"http://creativecommons.org/ns#\"\n"
    "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
    "   xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
    "   xmlns=\"http://www.w3.org/2000/svg\"\n"
    "   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
    "   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
    "   width=\"1000px\"\n"
    "   height=\"1000px\"\n"
    "   id=\"svg2\">\n"
    "  <g\n"
    "     inkscape:label=\"Ebene 1\"\n"
    "     inkscape:groupmode=\"layer\"\n"
    "     id=\"layer1\">\n"
    "    <path\n"
    "       style=\"fill:none;fill-rule:evenodd;stroke:#707070;"
    "stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;"
    "stroke-opacity:1\"\n"
    "       d=\"M 500.5,0.5 L 500.5,1000.5\"\n"
    "       id=\"line01\" />\n"
    "    <path\n"
    "       style=\"fill:none;fill-rule:evenodd;stroke:#707070;"
    "stroke-width:1;stroke-linecap:butt;stroke-linejoin:miter;"
    "stroke-opacity:1\"\n"
    "       d=\"M 0.5,500.5 L 1000.5,500.5\"\n"
    "       id=\"line02\" />\n"
    "    <g transform=\"matrix(1, 0, 0, -1, 500, 500)\">\n";
/// SVG template footer.
const std::string SVG_DEFAULT_FOOTER = "    </g>\n"
    "  </g>\n"
    "</svg>";
/// SVG template.
const std::string SVG_TEMPLATE = "<?xml version=\"1.0\""
    " encoding=\"UTF-8\" standalone=\"no\"?>\n"
    "<!-- Created with Inkscape (http://www.inkscape.org/) -->\n"
    "<svg\n"
    "   xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
    "   xmlns:cc=\"http://creativecommons.org/ns#\"\n"
    "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
    "   xmlns:svg=\"http://www.w3.org/2000/svg\"\n"
    "   xmlns=\"http://www.w3.org/2000/svg\"\n"
    "   xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
    "   xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\"\n"
    "   width=\"{$width}px\"\n"
    "   height=\"{$height}px\"\n"
    "   id=\"svg2\">\n"
    "  <g\n"
    "     inkscape:label=\"Ebene 1\"\n"
    "     inkscape:groupmode=\"layer\"\n"
    "     id=\"layer1\">\n"
    "    <g transform=\"matrix(1, 0, 0, -1, {$originX}, {$originY})\">\n"
    "      {$data}"
    "    </g>\n"
    "  </g>\n"
    "</svg>";

/// Default texture coordinates.
const Ionflux::GeoUtils::TexCoords DEFAULT_TEX_COORDS = { 0., 0. };
/// Default vertex color.
const Ionflux::GeoUtils::Color DEFAULT_VERTEX_COLOR = { 0., 0., 0., 1. };

/// Centering method: Barycenter.
const Ionflux::GeoUtils::CenteringMethod CENTER_BARYCENTER = 0;
/// Centering method: Bounds.
const Ionflux::GeoUtils::CenteringMethod CENTER_BOUNDS = 1;
/// Centering method: Origin.
const Ionflux::GeoUtils::CenteringMethod CENTER_ORIGIN = 2;

/// SVG shape type: Polygon.
const Ionflux::GeoUtils::SVGShapeType SHAPE_TYPE_POLYGON = 0;
/// SVG shape type: Path.
const Ionflux::GeoUtils::SVGShapeType SHAPE_TYPE_PATH = 1;
/// Default SVG shape type.
const Ionflux::GeoUtils::SVGShapeType DEFAULT_SHAPE_TYPE = SHAPE_TYPE_POLYGON;

/// Default SVG shape style.
const Ionflux::GeoUtils::SVGShapeStyle DEFAULT_SHAPE_STYLE = { 
    "#20e045", 0.533, "#0e1723", 1., 1., 4., "none", DEFAULT_SHAPE_TYPE, true
};

/// Coordinate index: not set.
const unsigned int COORDINATE_NOT_SET = UINT_MAX;

/// Matrix sampling method: average.
const Ionflux::GeoUtils::MatrixSamplingMethod SAMPLE_AVERAGE = 0;
/// Matrix sampling method: multiply.
const Ionflux::GeoUtils::MatrixSamplingMethod SAMPLE_MULTIPLY = 1;

/// Quad interpolation type ID: symmetric.
const Ionflux::GeoUtils::QuadInterpolationTypeID 
    QUAD_INTERPOLATION_SYMMETRIC = 0;
/// Quad interpolation type ID: bilinear.
const Ionflux::GeoUtils::QuadInterpolationTypeID 
    QUAD_INTERPOLATION_BILINEAR = 1;

namespace TransformNodes
{

/// Default maximum number of transform node inputs.
const unsigned int DEFAULT_MAX_NUM_INPUTS = 9999;
/// Input ID: next free input.
const unsigned int INPUT_NEXT_FREE = UINT_MAX;

/// Default input node specification.
const Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
    DEFAULT_INPUT_NODE_SPEC = {0, 0};

}

}

}

/** \file constants.hpp
 * \brief Constants (header).
 */
#endif
