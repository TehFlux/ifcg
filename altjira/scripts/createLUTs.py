#!/usr/bin/python
# -*- coding: utf-8 -*-
# ==========================================================================
# Altjira - Ionflux' Image Processing Library
# Copyright © 2008-2010 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# createLUTs.py          Create lookup tables.
# ==========================================================================
# 
# This file is part of Altjira - Ionflux' Image Processing Library.
# 
# Altjira - Ionflux' Image Processing Library is free software; you can 
# redistribute it and/or modify it under the terms of the GNU General 
# Public  License as published by the Free Software Foundation; either 
# version 2 of the License, or (at your option) any later version.
# 
# Altjira - Ionflux' Image Processing Library is distributed in the hope 
# that it will be useful, but WITHOUT ANY WARRANTY; without even the 
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Ionflux Star Database; if not, write to the Free Software 
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# 
# ==========================================================================
"""Create lookup tables for byte operations."""

lutTemplate = """#ifndef IONFLUX_ALTJIRA_LUT_%s
#define IONFLUX_ALTJIRA_LUT_%s
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2008-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * lut_%s.hpp                %s lookup table (header).
 * =========================================================================
 *
 * This file is part of Altjira - Ionflux' Image Processing Library.
 * 
 * Altjira - Ionflux' Image Processing Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * Altjira - Ionflux' Image Processing Library is distributed in the hope 
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the 
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with Altjira - Ionflux' Image Processing Library; if not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */

namespace Ionflux
{

namespace Altjira
{

/// %s lookup table.
const unsigned char LUT_%s[] = {\n    %s\n};

}

}

/** \\file lut_%s.hpp
 * \\brief %s lookup table (header).
 */
#endif"""

def createLUT(identifier, name, fileName, op):
    """Create LUT for operation."""
    d = ""
    k = 0
    for i in xrange(0, 256):
        x0 = float(i) / 255.
        for j in xrange(0, 256):
          k = 256 * i + j
          y0 = float(j) / 255.
          r = op(x0, y0)
          rc = int(round(255. * r))
          if (rc > 255):
              rc = 255
          if (rc < 0):
              rc = 0
          if (k > 0):
            d += ', '
            if (k % 8 == 0):
                d += '\n    '
          d += ("(unsigned char)'\\x%02x'" % rc)
    l0 = lutTemplate % (identifier, identifier, identifier.lower(), 
        name, name, identifier, d, identifier.lower(), name)
    f = open(fileName, 'w')
    f.write(l0)
    f.close()

def mult(x, y):
    return x * y

def add(x, y):
    return x + y

def sub(x, y):
    return x - y

def div(x, y):
    if (y == 0.):
        return 1.
    return x / y

createLUT('MULT', 'Multiplication', 'include/altjira/lut_mult.hpp', mult)
createLUT('ADD', 'Addition', 'include/altjira/lut_add.hpp', add)
createLUT('SUB', 'Subtraction', 'include/altjira/lut_sub.hpp', sub)
createLUT('DIV', 'Division', 'include/altjira/lut_div.hpp', div)

