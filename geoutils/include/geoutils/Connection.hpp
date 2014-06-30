#ifndef IONFLUX_GEOUTILS_CONNECTION
#define IONFLUX_GEOUTILS_CONNECTION
/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * Connection.hpp                  Connection (header).
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

#include "geoutils/types.hpp"
#include "geoutils/constants.hpp"
#include "geoutils/utils.hpp"
#include "geoutils/TransformNode.hpp"
#include "ifobject/IFObject.hpp"

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

/// Class information for class Connection.
class ConnectionClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		ConnectionClassInfo();
		/// Destructor.
		virtual ~ConnectionClassInfo();
};

/** Transform node connection.
 * \ingroup geoutils
 *
 * An object that can be used to conveniently establish and dispose of 
 * connections between the outputs and inputs of transform nodes. Although 
 * not strictly necessary to connect nodes, the Connection object is the 
 * recommended way to do this.
 */
class Connection
: virtual public Ionflux::ObjectBase::IFObject
{
	private:
		
	protected:
		/// Connected flag.
		bool connected;
		/// Source node.
		Ionflux::GeoUtils::TransformNodes::TransformNode* source;
		/// Target node.
		Ionflux::GeoUtils::TransformNodes::TransformNode* target;
		/// Output ID.
		unsigned int outputID;
		/// Input ID.
		unsigned int inputID;
		
	public:
		/// Class information instance.
		static const ConnectionClassInfo connectionClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new Connection object.
		 */
		Connection();
		
		/** Constructor.
		 *
		 * Construct new Connection object.
		 *
		 * \param other Other object.
		 */
		Connection(const Ionflux::GeoUtils::TransformNodes::Connection& other);
		
		/** Constructor.
		 *
		 * Construct new Connection object.
		 *
		 * \param initSource Source node.
		 * \param initTarget Target node.
		 * \param outputID Output ID.
		 * \param inputID Input ID.
		 * \param connectLater Connect later.
		 */
		Connection(Ionflux::GeoUtils::TransformNodes::TransformNode* initSource, 
		Ionflux::GeoUtils::TransformNodes::TransformNode* initTarget, unsigned 
		int outputID = 0, unsigned int inputID = INPUT_NEXT_FREE, bool 
		connectLater = false);
		
		/** Destructor.
		 *
		 * Destruct Connection object.
		 */
		virtual ~Connection();
		
		/** Connect.
		 *
		 * Establish a connection from the specified output slot of the input 
		 * node to the specified input slot of the output node. If \c 
		 * connectLater is \c true, the internal state will be set up but the 
		 * connection will not be established immediately.
		 *
		 * \param newSource Source node.
		 * \param newTarget Target node.
		 * \param newOutputID New output ID.
		 * \param newInputID New input ID.
		 * \param connectLater Connect later.
		 *
		 * \return \c true if a connection has been established, \c false 
		 * otherwise.
		 */
		virtual bool connect(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		newSource = 0, Ionflux::GeoUtils::TransformNodes::TransformNode* 
		newTarget = 0, unsigned int newOutputID = 0, unsigned int newInputID = 
		INPUT_NEXT_FREE, bool connectLater = false);
		
		/** Disconnect.
		 *
		 * Disconnect the connection.
		 *
		 * \return \c true if the connection has been discarded, \c false 
		 * otherwise.
		 */
		virtual bool disconnect();
		
		/** Clear.
		 *
		 * Reset the object to an uninitialized state.
		 */
		virtual void clear();
		
		/** Connection check.
		 *
		 * Check whether the connection is established.
		 *
		 * \return \c true if the connection is established, \c false otherwise.
		 */
		virtual bool isConnected();
		
		/** Get string representation.
		 *
		 * Get a string representation of the object
		 *
		 * \return String representation.
		 */
		virtual std::string getString() const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Connection.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator==(const 
		Ionflux::GeoUtils::TransformNodes::Connection& other) const;
		
		/** Comparison operator: equality.
		 *
		 * Compare equality.
		 *
		 * \param other Connection.
		 *
		 * \return Result of the comparison.
		 */
		virtual bool operator!=(const 
		Ionflux::GeoUtils::TransformNodes::Connection& other) const;
		
		/** Check connection.
		 *
		 * Check whether a connection between the specified node input and 
		 * output actually exists. Note that this does not check whether a 
		 * corresponding connection object exists. it just checks whether the 
		 * internal state of the target node indicates such a connection.
		 *
		 * \param checkSource Source node.
		 * \param checkTarget Target node.
		 * \param checkOutputID Output ID.
		 * \param checkInputID Input ID.
		 *
		 * \return \c true if the connection exists, \c false otherwise.
		 */
		static bool check(Ionflux::GeoUtils::TransformNodes::TransformNode* 
		checkSource, Ionflux::GeoUtils::TransformNodes::TransformNode* 
		checkTarget, unsigned int checkOutputID = 0, unsigned int checkInputID = 
		0);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Connection& operator=(const 
		Ionflux::GeoUtils::TransformNodes::Connection& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::Connection* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::GeoUtils::TransformNodes::Connection* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get source node.
		 *
		 * \return Current value of source node.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* getSource() 
		const;
		
		/** Get target node.
		 *
		 * \return Current value of target node.
		 */
		virtual Ionflux::GeoUtils::TransformNodes::TransformNode* getTarget() 
		const;
		
		/** Get output ID.
		 *
		 * \return Current value of output ID.
		 */
		virtual unsigned int getOutputID() const;
		
		/** Get input ID.
		 *
		 * \return Current value of input ID.
		 */
		virtual unsigned int getInputID() const;
};

}

}

}

/** \file Connection.hpp
 * \brief Connection (header).
 */
#endif
