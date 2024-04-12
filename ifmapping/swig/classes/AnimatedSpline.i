/* ==========================================================================
 * IFMapping - Ionflux Mapping Library
 * Copyright © 2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * AnimatedSpline.i                Animated Bezier spline (interface).
 * =========================================================================
 * 
 * This file is part of IFMapping - Ionflux Mapping Library.
 * 
 * IFMapping - Ionflux Mapping Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 3 of the License, or (at your option) any later version.
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
#include "ifmapping/AnimatedSpline.hpp"
%}

namespace Ionflux
{

namespace Mapping
{

class AnimatedSplineClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        AnimatedSplineClassInfo();
        virtual ~AnimatedSplineClassInfo();
};

class AnimatedSpline
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        AnimatedSpline();
		AnimatedSpline(const Ionflux::Mapping::AnimatedSpline& other);
        virtual ~AnimatedSpline();
        virtual void getShape(Ionflux::Mapping::MappingValue t, 
        Ionflux::Mapping::BezierSpline& target) const;
        virtual Ionflux::Mapping::BezierSpline 
        call(Ionflux::Mapping::MappingValue value) const;
        virtual std::string getString() const;
		virtual Ionflux::Mapping::AnimatedSpline* copy() const;        
        virtual unsigned int getNumKeys() const;
        virtual Ionflux::Mapping::BezierSplineKey* getKey(unsigned int 
        elementIndex = 0) const;
		virtual int findKey(Ionflux::Mapping::BezierSplineKey* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::Mapping::BezierSplineKey*>& getKeys();
        virtual void addKey(Ionflux::Mapping::BezierSplineKey* addElement);        
        virtual void removeKey(Ionflux::Mapping::BezierSplineKey* 
        removeElement);
		virtual void removeKeyIndex(unsigned int removeIndex);
		virtual void clearKeys();
};

}

}
