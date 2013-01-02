/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Connection.i                    Connection (interface).
 * =========================================================================

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
#include "geoutils/Connection.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class ConnectionClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        ConnectionClassInfo();
        virtual ~ConnectionClassInfo();
};

class Connection
: virtual public Ionflux::ObjectBase::IFObject
{
    public:
        
        Connection();
		Connection(const Ionflux::GeoUtils::TransformNodes::Connection& other);
        Connection(Ionflux::GeoUtils::TransformNodes::TransformNode* 
        initSource, Ionflux::GeoUtils::TransformNodes::TransformNode* 
        initTarget, unsigned int outputID = 0, unsigned int inputID = 
        INPUT_NEXT_FREE, bool connectLater = false);
        virtual ~Connection();
        virtual bool 
        connect(Ionflux::GeoUtils::TransformNodes::TransformNode* newSource
        = 0, Ionflux::GeoUtils::TransformNodes::TransformNode* newTarget = 
        0, unsigned int newOutputID = 0, unsigned int newInputID = 
        INPUT_NEXT_FREE, bool connectLater = false);
        virtual bool disconnect();
        virtual void clear();
        virtual bool isConnected();
        virtual std::string getString() const;
        virtual bool operator==(const 
        Ionflux::GeoUtils::TransformNodes::Connection& other) const;
        virtual bool operator!=(const 
        Ionflux::GeoUtils::TransformNodes::Connection& other) const;
        static bool check(Ionflux::GeoUtils::TransformNodes::TransformNode*
        checkSource, Ionflux::GeoUtils::TransformNodes::TransformNode* 
        checkTarget, unsigned int checkOutputID = 0, unsigned int 
        checkInputID = 0);
		virtual Ionflux::GeoUtils::TransformNodes::Connection* copy() const;
		static Ionflux::GeoUtils::TransformNodes::Connection* 
		upcast(Ionflux::ObjectBase::IFObject* other);
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getSource() const;
        virtual Ionflux::GeoUtils::TransformNodes::TransformNode* 
        getTarget() const;
        virtual unsigned int getOutputID() const;
        virtual unsigned int getInputID() const;
};

}

}

}
