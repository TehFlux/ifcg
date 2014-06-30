/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * PointSet.i                      Point set (interface).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFMapping - Ionflux Mapping Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFMapping - Ionflux Mapping Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "ifmapping/PointSet.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class PointSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        PointSetClassInfo();
        virtual ~PointSetClassInfo();
};

class PointSet
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        PointSet();
		PointSet(const Ionflux::Mapping::PointSet& other);
        PointSet(const Ionflux::Mapping::PointVector& initPoints);
        virtual ~PointSet();
        virtual std::string getSVGPathData(const 
        Ionflux::Mapping::CoordinateID imagePlaneNormal = 
        Ionflux::Mapping::C_Z, unsigned int startIndex = 0, unsigned int 
        numPoints = 0) const;
        virtual std::string getValueString() const;
		virtual std::string getXMLElementName() const;
		virtual std::string getXMLAttributeData() const;
		virtual void getXMLChildData(std::string& target, unsigned int 
		indentLevel = 0) const;
		virtual void loadFromXMLFile(const std::string& FileName);
		static Ionflux::ObjectBase::XMLUtils::IFXMLObjectFactory* 
		getXMLObjectFactory();
		virtual Ionflux::Mapping::PointSet* copy() const;
		static Ionflux::Mapping::PointSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::Mapping::PointSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;
		static Ionflux::Mapping::PointSet* create(const 
		Ionflux::Mapping::PointVector& initPoints, Ionflux::ObjectBase::IFObject*
		parentObject = 0);        
        virtual unsigned int getNumPoints() const;
        virtual Ionflux::Mapping::Point* getPoint(unsigned int elementIndex
        = 0) const;
		virtual int findPoint(Ionflux::Mapping::Point* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::Point*>& getPoints();
        virtual void addPoint(Ionflux::Mapping::Point* addElement);
		virtual Ionflux::Mapping::Point* addPoint();
		virtual void addPoints(std::vector<Ionflux::Mapping::Point*>& newPoints);
		virtual void addPoints(Ionflux::Mapping::PointSet* newPoints);        
        virtual void removePoint(Ionflux::Mapping::Point* removeElement);
		virtual void removePointIndex(unsigned int removeIndex);
		virtual void clearPoints();
};

}

}
