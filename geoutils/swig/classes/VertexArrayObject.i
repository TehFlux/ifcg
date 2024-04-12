/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VertexArrayObject.i             Vertex array object (OpenGL) 
 * (interface).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
%{
#include "geoutils/VertexArrayObject.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class VertexAttribute;

class VertexArrayObjectClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VertexArrayObjectClassInfo();
        virtual ~VertexArrayObjectClassInfo();
};

class VertexArrayObject
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        VertexArrayObject();
		VertexArrayObject(const Ionflux::GeoUtils::VertexArrayObject& other);
        virtual ~VertexArrayObject();
        virtual void cleanup();
        virtual void init();
        virtual void bind();
        virtual void update();
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::VertexArrayObject* copy() const;
		static Ionflux::GeoUtils::VertexArrayObject* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::VertexArrayObject* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual GLuint getVaoImpl() const;        
        virtual unsigned int getNumAttributes() const;
        virtual Ionflux::GeoUtils::VertexAttribute* getAttribute(unsigned 
        int elementIndex = 0) const;
		virtual int findAttribute(Ionflux::GeoUtils::VertexAttribute* needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::VertexAttribute*>& 
        getAttributes();
        virtual void addAttribute(Ionflux::GeoUtils::VertexAttribute* 
        addElement);
		virtual Ionflux::GeoUtils::VertexAttribute* addAttribute();
		virtual void 
		addAttributes(std::vector<Ionflux::GeoUtils::VertexAttribute*>& 
		newAttributes);
		virtual void addAttributes(Ionflux::GeoUtils::VertexArrayObject* 
		newAttributes);        
        virtual void removeAttribute(Ionflux::GeoUtils::VertexAttribute* 
        removeElement);
		virtual void removeAttributeIndex(unsigned int removeIndex);
		virtual void clearAttributes();
};

}

}
