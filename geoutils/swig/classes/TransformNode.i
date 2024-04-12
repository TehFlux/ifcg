/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformNode.i                 Transform node (interface).
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
#include "geoutils/TransformNode.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class TransformNodeClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformNodeClassInfo();
        virtual ~TransformNodeClassInfo();
};

class TransformNode
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
		static const unsigned int DEFAULT_LOOP_MAX;
        
        TransformNode();
		TransformNode(const Ionflux::GeoUtils::TransformNodes::TransformNode& other);
        TransformNode(const Ionflux::ObjectBase::IFObjectID& nodeID);
        virtual ~TransformNode();
        virtual void addInputs(const 
        Ionflux::GeoUtils::InputNodeSpecVector& newInputs);
        virtual void 
        getLinkedInputs(Ionflux::GeoUtils::TransformNodeVector& target);
        virtual void setInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& newInput, 
        unsigned int inputID = INPUT_NEXT_FREE);
        virtual void clearInputCache();
        virtual void updateInputs();
        virtual void clearInputGroups();
        virtual void cleanup();
        virtual void update();
        virtual std::string getString() const;
        virtual std::string getDebugInfo(bool expand = true);
        virtual void enableDebugMode(bool newDebugMode = true, bool expand 
        = false);
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* copy() const;
		static Ionflux::GeoUtils::TransformNodes::TransformNode* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		virtual void setParam(Ionflux::ObjectBase::IFParamID paramID, 
		Ionflux::Mapping::MappingValue paramValue);
		virtual Ionflux::Mapping::MappingValue 
		getParam(Ionflux::ObjectBase::IFParamID paramID);        
        virtual unsigned int getNumInputs() const;
        virtual Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
        getInput(unsigned int elementIndex = 0) const;
		virtual int findInput(Ionflux::GeoUtils::TransformNodes::InputNodeSpec 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::InputNodeSpec>& 
        getInputs();
        virtual void addInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& addElement);        
        virtual void removeInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& removeElement);
		virtual void removeInputIndex(unsigned int removeIndex);
		virtual void clearInputs();        
        virtual unsigned int getNumOutputs() const;
        virtual Ionflux::GeoUtils::TransformableGroup* getOutput(unsigned 
        int elementIndex = 0) const;
		virtual int findOutput(Ionflux::GeoUtils::TransformableGroup* needle, 
		unsigned int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::TransformableGroup*>& 
        getOutputs();
        virtual void addOutput(Ionflux::GeoUtils::TransformableGroup* 
        addElement);        
        virtual void removeOutput(Ionflux::GeoUtils::TransformableGroup* 
        removeElement);
		virtual void removeOutputIndex(unsigned int removeIndex);
		virtual void clearOutputs();
        virtual void setLoopMax(unsigned int newLoopMax);
        virtual unsigned int getLoopMax() const;
        virtual void setMaxNumInputs(unsigned int newMaxNumInputs);
        virtual unsigned int getMaxNumInputs() const;
        virtual void setUpdateCounter(unsigned int newUpdateCounter);
        virtual unsigned int getUpdateCounter() const;
};

}

}

}
