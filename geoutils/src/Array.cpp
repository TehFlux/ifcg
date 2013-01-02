/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Array.cpp                       Transform node: Array (implementation).
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

#include "geoutils/Array.hpp"
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "ifmapping/utils.hpp"
#include "geoutils/GeoUtilsError.hpp"

using namespace std;
using namespace Ionflux::ObjectBase;
using Ionflux::Mapping::defaultStr;

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

ArrayClassInfo::ArrayClassInfo()
{
	name = "Array";
	desc = "Transform node: Array";
}

ArrayClassInfo::~ArrayClassInfo()
{
}

// public member constants
const unsigned int Array::INPUT_SOURCE = 0;
const unsigned int Array::OUTPUT_TARGET = 0;
const unsigned int Array::DEFAULT_NUM_ROWS = 10;
const unsigned int Array::DEFAULT_NUM_COLUMNS = 10;
const double Array::DEFAULT_CELL_WIDTH = 100.;
const double Array::DEFAULT_CELL_HEIGHT = 100.;

// run-time type information instance constants
const ArrayClassInfo Array::arrayClassInfo;
const Ionflux::ObjectBase::IFClassInfo* Array::CLASS_INFO = &Array::arrayClassInfo;

Array::Array()
: offset(GeoUtils::Vector3::ZERO), numRows(DEFAULT_NUM_ROWS), numColumns(DEFAULT_NUM_COLUMNS), cellWidth(DEFAULT_CELL_WIDTH), cellHeight(DEFAULT_CELL_HEIGHT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Array::Array(const Ionflux::GeoUtils::TransformNodes::Array& other)
: offset(GeoUtils::Vector3::ZERO), numRows(DEFAULT_NUM_ROWS), numColumns(DEFAULT_NUM_COLUMNS), cellWidth(DEFAULT_CELL_WIDTH), cellHeight(DEFAULT_CELL_HEIGHT)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	*this = other;
}

Array::Array(unsigned int initNumRows, unsigned int initNumColumns, double 
initCellWidth, double initCellHeight, const Ionflux::GeoUtils::Vector3& 
initOffset, const Ionflux::ObjectBase::IFObjectID& nodeID)
: TransformNode(nodeID), offset(initOffset), numRows(initNumRows), 
numColumns(initNumColumns), cellWidth(initCellWidth), 
cellHeight(initCellWidth)
{
	// NOTE: The following line is required for run-time type information.
	theClass = CLASS_INFO;
	// TODO: Nothing ATM. ;-)
}

Array::~Array()
{
	// TODO: Nothing ATM. ;-)
}

void Array::process()
{
	if (inputCache.size() < 1)
	    throw GeoUtilsError("Input cache is empty.");
	clearInputGroups();
	TransformableGroup* g0 = inputCache[0];
	/* Since we are going to manipulate the individual elements, 
	   any existing group transformations must be applied first. */
	g0->applyTransform();
	double width = numColumns * cellWidth;
	double height = numRows * cellHeight;
	// Translation to center the array around the origin.
	Vector3 v0(-0.5 * width, -0.5 * height, 0.);
	unsigned int numSourceItems = g0->getNumItems();
	for (unsigned int i = 0; i < numSourceItems; i++)
	{
	    TransformableObject* o0 = g0->getItem(i);
	    unsigned int row = (i / numColumns) % numRows;
	    unsigned int col = i % numColumns;
	    // Translation for the cell.
	    Vector3 v1((col + 0.5) * cellWidth, 
	        (numRows - row - 0.5) * cellHeight, 0);
	    // Translate the object.
	    o0->translate(v0 + v1 + offset);
	}
	addOutput(g0);
}

std::string Array::getString() const
{
	ostringstream status;
	status << getClassName() << "[" << defaultStr(id, "<unnamed>") 
	    << "; " << offset << ", " << numRows << " x " << numColumns 
	    << ", " << cellWidth << " x " << cellHeight << "]";
	return status.str();
}

void Array::setOffset(const Ionflux::GeoUtils::Vector3& newOffset)
{
	offset = newOffset;
}

Ionflux::GeoUtils::Vector3 Array::getOffset() const
{
	return offset;
}

void Array::setNumRows(unsigned int newNumRows)
{
	numRows = newNumRows;
}

unsigned int Array::getNumRows() const
{
	return numRows;
}

void Array::setNumColumns(unsigned int newNumColumns)
{
	numColumns = newNumColumns;
}

unsigned int Array::getNumColumns() const
{
	return numColumns;
}

void Array::setCellWidth(double newCellWidth)
{
	cellWidth = newCellWidth;
}

double Array::getCellWidth() const
{
	return cellWidth;
}

void Array::setCellHeight(double newCellHeight)
{
	cellHeight = newCellHeight;
}

double Array::getCellHeight() const
{
	return cellHeight;
}

Ionflux::GeoUtils::TransformNodes::Array& Array::operator=(const 
Ionflux::GeoUtils::TransformNodes::Array& other)
{
    TransformNode::operator=(other);
    offset = other.offset;
    numRows = other.numRows;
    numColumns = other.numColumns;
    cellWidth = other.cellWidth;
    cellHeight = other.cellHeight;
	return *this;
}

Ionflux::GeoUtils::TransformNodes::Array* Array::copy() const
{
    Array* newArray = create();
    *newArray = *this;
    return newArray;
}

Ionflux::GeoUtils::TransformNodes::Array* 
Array::upcast(Ionflux::ObjectBase::IFObject* other)
{
    return dynamic_cast<Array*>(other);
}

Ionflux::GeoUtils::TransformNodes::Array* 
Array::create(Ionflux::ObjectBase::IFObject* parentObject)
{
    Array* newObject = new Array();
    if (newObject == 0)
    {
        throw GeoUtilsError("Could not allocate object.");
    }
    if (parentObject != 0)
        parentObject->addLocalRef(newObject);
    return newObject;
}

}

}

}

/** \file Array.cpp
 * \brief Transform node: Array implementation.
 */
