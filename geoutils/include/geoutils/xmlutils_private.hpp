#ifndef IONFLUX_GEOUTILS_XMLUTILS
#define IONFLUX_GEOUTILS_XMLUTILS
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * xmlutils_private.hpp                  XML utility functions (header).
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



namespace Ionflux
{

namespace GeoUtils
{

class TransformableObject;

namespace XMLUtils
{

void getTransformableObject(TiXmlElement* e0, 
    Ionflux::GeoUtils::TransformableObject& target, const std::string& 
elementName = Ionflux::GeoUtils::TransformableObject::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::TransformableObject>(TiXmlElement* e0, 
Ionflux::GeoUtils::TransformableObject& target, const std::string& 
elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vertex3;

namespace XMLUtils
{

void getVertex3(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3& target, const std::string& elementName = 
Ionflux::GeoUtils::Vertex3::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Vertex3>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vertex3& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Vertex3Set;

namespace XMLUtils
{

void getVertex3Set(TiXmlElement* e0, 
    Ionflux::GeoUtils::Vertex3Set& target, const std::string& elementName =
Ionflux::GeoUtils::Vertex3Set::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Vertex3Set>(TiXmlElement* e0, 
Ionflux::GeoUtils::Vertex3Set& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Face;

namespace XMLUtils
{

void getFace(TiXmlElement* e0, 
    Ionflux::GeoUtils::Face& target, const std::string& elementName = 
Ionflux::GeoUtils::Face::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Face>(TiXmlElement* e0, 
Ionflux::GeoUtils::Face& target, const std::string& elementName);

}

}

}



namespace Ionflux
{

namespace GeoUtils
{

class Mesh;

namespace XMLUtils
{

void getMesh(TiXmlElement* e0, 
    Ionflux::GeoUtils::Mesh& target, const std::string& elementName = 
Ionflux::GeoUtils::Mesh::XML_ELEMENT_NAME);

}

}

}

namespace Ionflux
{

namespace ObjectBase
{

namespace XMLUtils
{

template<>
void getObject0<Ionflux::GeoUtils::Mesh>(TiXmlElement* e0, 
Ionflux::GeoUtils::Mesh& target, const std::string& elementName);

}

}

}


/** \file xmlutils_private.hpp
 * \brief XML utility functions (header).
 */
#endif
