/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * TransformGraph.i                Transform graph (interface).
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
#include "geoutils/TransformGraph.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class TransformGraphClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        TransformGraphClassInfo();
        virtual ~TransformGraphClassInfo();
};

class TransformGraph
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int NODE_INDEX_LAST;
        
        TransformGraph();
		TransformGraph(const Ionflux::GeoUtils::TransformNodes::TransformGraph& other);
        virtual ~TransformGraph();
        virtual void 
        addLinked(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        newNode);
        virtual void clear();
        virtual void addNodes(Ionflux::GeoUtils::TransformNodeVector& 
        newNodes);
        virtual Ionflux::GeoUtils::TransformNodes::Connection* 
        findConnection(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        source = 0, Ionflux::GeoUtils::TransformNodes::TransformNode* 
        target = 0, unsigned int outputID = 0, unsigned int inputID = 0, 
        bool connectLater = false);
        virtual bool 
        connect(Ionflux::GeoUtils::TransformNodes::TransformNode* source = 
        0, Ionflux::GeoUtils::TransformNodes::TransformNode* target = 0, 
        unsigned int outputID = 0, unsigned int inputID = INPUT_NEXT_FREE, 
        bool connectLater = false);
        virtual bool 
        disconnect(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, 
        unsigned int outputID = 0, unsigned int inputID = 0);
        virtual void chain(unsigned int first = 0, unsigned int last = 
        NODE_INDEX_LAST);
        virtual void 
        connectRange(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, 
        unsigned int numOutputSlots, unsigned int firstOutputID = 0, 
        unsigned int firstInputID = INPUT_NEXT_FREE);
        virtual void 
        connectFan(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        source, Ionflux::GeoUtils::TransformNodes::TransformNode* target, 
        unsigned int numInputSlots, unsigned int outputID = 0, unsigned int
        firstInputID = INPUT_NEXT_FREE);
        virtual void setIO(unsigned int sourceIndex = 0, unsigned int 
        drainIndex = NODE_INDEX_LAST);
        virtual std::string getString() const;
        virtual void addInputs(const 
        Ionflux::GeoUtils::InputNodeSpecVector& newInputs);
        virtual void 
        getLinkedInputs(Ionflux::GeoUtils::TransformNodeVector& target);
        virtual void setInput(const 
        Ionflux::GeoUtils::TransformNodes::InputNodeSpec& newInput, 
        unsigned int inputID = INPUT_NEXT_FREE);
        virtual void update();
		virtual Ionflux::GeoUtils::TransformNodes::TransformGraph* copy() const;
		static Ionflux::GeoUtils::TransformNodes::TransformGraph* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::TransformGraph* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;        
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
        virtual unsigned int getNumConnections() const;
        virtual Ionflux::GeoUtils::TransformNodes::Connection* 
        getConnection(unsigned int elementIndex = 0) const;
		virtual int findConnection(Ionflux::GeoUtils::TransformNodes::Connection*
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::Connection*>& 
        getConnections();
        virtual void 
        addConnection(Ionflux::GeoUtils::TransformNodes::Connection* 
        addElement);        
        virtual void 
        removeConnection(Ionflux::GeoUtils::TransformNodes::Connection* 
        removeElement);
		virtual void removeConnectionIndex(unsigned int removeIndex);
		virtual void clearConnections();        
        virtual unsigned int getNumNodes() const;
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getNode(unsigned int elementIndex = 0) const;
		virtual int findNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		needle, unsigned int occurence = 1) const;
        virtual 
        std::vector<Ionflux::GeoUtils::TransformNodes::TransformNode*>& 
        getNodes();
        virtual void 
        addNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        addElement);        
        virtual void 
        removeNode(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        removeElement);
		virtual void removeNodeIndex(unsigned int removeIndex);
		virtual void clearNodes();
        virtual void 
        setSource(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        newSource);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getSource() const;
        virtual void 
        setDrain(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        newDrain);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getDrain() const;
};

}

}

}
