/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * test_serialization_01.cpp       IFVG test: Node hierarchy serialization.
 * ==========================================================================
 * 
 * This file is part of IFVG - Ionflux' Volumetric Graphics Library.
 * 
 * IFVG - Ionflux' Volumetric Graphics Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * IFVG - Ionflux' Volumetric Graphics Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with IFVG - Ionflux' Volumetric Graphics Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA

 * ========================================================================== */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include "ifobject/utils.hpp"
#include "ifobject/utf8.hpp"
#include "ifvg/Node.hpp"
#include "ifvg/IFVGError.hpp"

using namespace Ionflux::VolGfx;

// Name of the test.
const std::string TEST_NAME = "IFVG test: Node hierarchy serialization";

int main(int argc, char* argv[])
{
    std::cout << "IFVG test: " << TEST_NAME << std::endl;
    // memory management
    Ionflux::ObjectBase::IFObject mm;
    
    std::cout << "  Creating context..." << std::endl;
    
    const unsigned int octreeMaxNumLevels = 7;
    const unsigned int octreeOrder = 2;
    const double octreeScale = 4.;
    
    Context* ctx = Context::create(octreeMaxNumLevels, 
        octreeOrder, octreeScale);
    mm.addLocalRef(ctx);
    
    std::cout << "  Creating root node..." << std::endl;
    
    Node* root0 = Node::create(ctx);
    mm.addLocalRef(root0);
    
    Ionflux::ObjectBase::DoubleVector dv0;
    dv0.push_back(2.3251);
    root0->setData(Node::DATA_TYPE_DENSITY, &dv0);
    
    root0->printDebugInfo();
    
    std::cout << "  Serializing node hierarchy..." << std::endl;
    
    std::ostringstream os0;
    root0->serializeHierarchy(os0);
    
    std::string data0(os0.str());
    
    std::cout << Ionflux::ObjectBase::utf8MakeNiceHexForData(data0);
    
    std::cout << "  Deserializing node hierarchy..." << std::endl;
    
    std::istringstream is0(data0);
    
    root0->deserializeHierarchy(is0);
	
	std::cout << "All done!" << std::endl;
	return 0;
}

/** \file test_serialization_01.cpp
 * \brief IFVG test: Node hierarchy serialization.
 */
