/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * LoadSVG.i                       Transform node: Load SVG (interface).
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
%{
#include "geoutils/LoadSVG.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class LoadSVGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        LoadSVGClassInfo();
        virtual ~LoadSVGClassInfo();
};

class LoadSVG
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
        
        LoadSVG();
		LoadSVG(const Ionflux::GeoUtils::TransformNodes::LoadSVG& other);
        LoadSVG(const std::string& initFileName, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~LoadSVG();
        virtual std::string getString() const;
		virtual Ionflux::GeoUtils::TransformNodes::LoadSVG* copy() const;
		static Ionflux::GeoUtils::TransformNodes::LoadSVG* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::LoadSVG* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setFileName(const std::string& newFileName);
        virtual std::string getFileName() const;        
        virtual unsigned int getNumElementIDs() const;
        virtual std::string getElementID(unsigned int elementIndex = 0) 
        const;
		virtual int findElementID(std::string needle, unsigned int occurence = 1)
		const;
        virtual std::vector<std::string>& getElementIDs();
        virtual void addElementID(std::string addElement);        
        virtual void removeElementID(std::string removeElement);
		virtual void removeElementIDIndex(unsigned int removeIndex);
		virtual void clearElementIDs();
};

}

}

}
