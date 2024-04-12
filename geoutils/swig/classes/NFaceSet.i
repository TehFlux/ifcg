/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NFaceSet.i                      N-face set (interface).
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
#include "geoutils/NFaceSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class NFace;

class NFaceSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NFaceSetClassInfo();
        virtual ~NFaceSetClassInfo();
};

class NFaceSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        NFaceSet();
		NFaceSet(const Ionflux::GeoUtils::NFaceSet& other);
        virtual ~NFaceSet();
        virtual bool isTriSet() const;
        virtual bool isQuadSet() const;
        virtual bool isEdgeSet() const;
        virtual std::string getValueString() const;
		virtual Ionflux::GeoUtils::NFaceSet* copy() const;
		static Ionflux::GeoUtils::NFaceSet* upcast(Ionflux::ObjectBase::IFObject*
		other);
		static Ionflux::GeoUtils::NFaceSet* create(Ionflux::ObjectBase::IFObject*
		parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumNFaces() const;
        virtual Ionflux::GeoUtils::NFace* getNFace(unsigned int 
        elementIndex = 0) const;
		virtual int findNFace(Ionflux::GeoUtils::NFace* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::NFace*>& getNFaces();
        virtual void addNFace(Ionflux::GeoUtils::NFace* addElement);
		virtual Ionflux::GeoUtils::NFace* addNFace();
		virtual void addNFaces(std::vector<Ionflux::GeoUtils::NFace*>& 
		newNFaces);
		virtual void addNFaces(Ionflux::GeoUtils::NFaceSet* newNFaces);        
        virtual void removeNFace(Ionflux::GeoUtils::NFace* removeElement);
		virtual void removeNFaceIndex(unsigned int removeIndex);
		virtual void clearNFaces();
};

}

}
