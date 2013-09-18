#ifndef IONFLUX_GEOUTILS_TRANSFORM_UTILS
#define IONFLUX_GEOUTILS_TRANSFORM_UTILS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * transformutils.hpp            Transformation utility functions (header).
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
#include "ifobject/types.hpp"
#include "ifobject/utils.hpp"
#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/Matrix4.hpp"
#include "geoutils/TransformableObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

/// Apply transformations to a vector of child objects.
template<class T>
void applyTransform(Ionflux::GeoUtils::TransformableObject& obj, 
    std::vector<T>& elements, bool recursive = false, 
    const std::string elementName = "Object")
{
    if (!recursive 
        && !obj.useTransform() 
        && !obj.useVI())
    {
        obj.clearTransformations();
        return;
    }
    Matrix4* tm0 = 0;
    Matrix4* vm0 = 0;
    Matrix4* im0 = 0;
    if (obj.useTransform())
        tm0 = obj.getTransformMatrix();
    if (obj.useVI())
    {
        vm0 = obj.getViewMatrix();
        im0 = obj.getImageMatrix();
    }
    for (typename std::vector<T>::iterator i = elements.begin(); 
        i != elements.end(); i++)
    {
        T vt0 = Ionflux::ObjectBase::nullPointerCheck(
            *i, "applyTransform", elementName);
        if (obj.useTransform())
            vt0->transform(*tm0);
        if (obj.useVI())
            vt0->transformVI(*vm0, im0);
        if (recursive)
            vt0->applyTransform(recursive);
    }
    obj.clearTransformations();
}

}

}

/** \file utils.hpp
 * \brief Utility functions (header).
 */
#endif
