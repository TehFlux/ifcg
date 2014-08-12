/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * VectorSet.i                     Vector set (interface).
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
#include "geoutils/VectorSet.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

class Vector;

class VectorSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        VectorSetClassInfo();
        virtual ~VectorSetClassInfo();
};

class VectorSet
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        VectorSet();
		VectorSet(const Ionflux::GeoUtils::VectorSet& other);
        VectorSet(Ionflux::GeoUtils::VectorVector& initVectors);
        virtual ~VectorSet();
        virtual void makeOrientationsConsistent(Ionflux::GeoUtils::Vector* 
        flipData = 0, double t = Ionflux::GeoUtils::DEFAULT_TOLERANCE);
        virtual void getCentroid(Ionflux::GeoUtils::Vector& target) const;
        virtual bool operator==(const Ionflux::GeoUtils::VectorSet& other) 
        const;
        virtual bool operator!=(const Ionflux::GeoUtils::VectorSet& other) 
        const;
        virtual std::string getValueStringF(unsigned int fieldWidth = 5, 
        unsigned int precision = 3, const std::string& colSep = " ", const 
        std::string& rowSep = "\n", const std::string& rowPrefix = "") 
        const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::GeoUtils::VectorSet* copy() const;
		static Ionflux::GeoUtils::VectorSet* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::VectorSet* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::GeoUtils::VectorSet* 
		create(Ionflux::GeoUtils::VectorVector& initVectors, 
		Ionflux::ObjectBase::IFObject* parentObject = 0);        
        virtual unsigned int getNumVectors() const;
        virtual Ionflux::GeoUtils::Vector* getVector(unsigned int 
        elementIndex = 0) const;
		virtual int findVector(Ionflux::GeoUtils::Vector* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::Vector*>& getVectors();
        virtual void addVector(Ionflux::GeoUtils::Vector* addElement);
		virtual Ionflux::GeoUtils::Vector* addVector();
		virtual void addVectors(std::vector<Ionflux::GeoUtils::Vector*>& 
		newVectors);
		virtual void addVectors(Ionflux::GeoUtils::VectorSet* newVectors);        
        virtual void removeVector(Ionflux::GeoUtils::Vector* 
        removeElement);
		virtual void removeVectorIndex(unsigned int removeIndex);
		virtual void clearVectors();
};

}

}
