/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Batch.i                         Transform node: Batch (interface).
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
#include "geoutils/Batch.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class BatchClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        BatchClassInfo();
        virtual ~BatchClassInfo();
};

class Batch
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_FIRST;
		static const unsigned int DEFAULT_PROCESSOR_INPUT_ID;
        
        Batch();
		Batch(const Ionflux::GeoUtils::TransformNodes::Batch& other);
        Batch(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        initProcessor, unsigned int initProcessorInputID = 
        DEFAULT_PROCESSOR_INPUT_ID, const Ionflux::ObjectBase::IFObjectID& 
        nodeID = "");
        virtual ~Batch();
        virtual std::string getString() const;
        virtual void addControls(Ionflux::GeoUtils::ParamControlVector& 
        newControls);
		virtual Ionflux::GeoUtils::TransformNodes::Batch* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Batch* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::Batch* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        virtual void 
        setProcessor(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        newProcessor);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getProcessor() const;        
        virtual unsigned int getNumControls() const;
        virtual Ionflux::GeoUtils::TransformNodes::ParamControl* 
        getControl(unsigned int elementIndex = 0) const;
		virtual int findControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::ParamControl*>& 
        getControls();
        virtual void 
        addControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
        addElement);        
        virtual void 
        removeControl(Ionflux::GeoUtils::TransformNodes::ParamControl* 
        removeElement);
		virtual void removeControlIndex(unsigned int removeIndex);
		virtual void clearControls();
        virtual void setProcessorInputID(unsigned int newProcessorInputID);
        virtual unsigned int getProcessorInputID() const;        
        virtual unsigned int getNumDimensions() const;
        virtual unsigned int getDimension(unsigned int elementIndex = 0) 
        const;
		virtual int findDimension(unsigned int needle, unsigned int occurence = 
		1) const;
        virtual std::vector<unsigned int>& getDimensions();
        virtual void addDimension(unsigned int addElement);        
        virtual void removeDimension(unsigned int removeElement);
		virtual void removeDimensionIndex(unsigned int removeIndex);
		virtual void clearDimensions();
};

}

}

}
