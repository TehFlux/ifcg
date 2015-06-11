/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeSet.i                       Node set (interface).
 * ========================================================================== */
%{
#include "ifvg/NodeSet.hpp"
%}

namespace Ionflux
{

namespace VolGfx
{

class Node;

class NodeSetClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        NodeSetClassInfo();
        virtual ~NodeSetClassInfo();
};

class NodeSet
: public Ionflux::ObjectBase::IFObject
{
    public:
        
        NodeSet();
		NodeSet(const Ionflux::VolGfx::NodeSet& other);
        virtual ~NodeSet();
        virtual std::string getValueString() const;
		virtual Ionflux::VolGfx::NodeSet* copy() const;
		static Ionflux::VolGfx::NodeSet* upcast(Ionflux::ObjectBase::IFObject* 
		other);
		static Ionflux::VolGfx::NodeSet* create(Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		virtual unsigned int getMemSize() const;        
        virtual unsigned int getNumNodes() const;
        virtual Ionflux::VolGfx::Node* getNode(unsigned int elementIndex = 
        0) const;
		virtual int findNode(Ionflux::VolGfx::Node* needle, unsigned int 
		occurence = 1) const;
        virtual std::vector<Ionflux::VolGfx::Node*>& getNodes();
        virtual void addNode(Ionflux::VolGfx::Node* addElement);
		virtual Ionflux::VolGfx::Node* addNode();
		virtual void addNodes(std::vector<Ionflux::VolGfx::Node*>& newNodes);
		virtual void addNodes(Ionflux::VolGfx::NodeSet* newNodes);        
        virtual void removeNode(Ionflux::VolGfx::Node* removeElement);
		virtual void removeNodeIndex(unsigned int removeIndex);
		virtual void clearNodes();
};

}

}
