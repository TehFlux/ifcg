/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * altjiranoise.cpp             Altjira/libnoise utilities (implementation).
 * ==========================================================================
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

#include "altjira/altjiranoise.hpp"
#include "altjira/imageutils.hpp"

namespace Ionflux
{

namespace Altjira
{

namespace Noise
{

void setImage(const noise::utils::Image& source, 
    Ionflux::Altjira::Image& target)
{
    unsigned int sw = static_cast<unsigned int>(source.GetWidth());
    unsigned int sh = static_cast<unsigned int>(source.GetHeight());
    unsigned int tw = target.getWidth();
    unsigned int th = target.getHeight();
    if ((sw != tw) || (tw != th))
        // Resize target image.
        target.createNewData(sw, sh, true, 8, 
            Ionflux::Altjira::Color::SPACE_RGB);
    unsigned int stride = source.GetStride();
    const noise::utils::Color* sp = source.GetConstSlabPtr();
    for (unsigned int i = 0; i < sh; i++)
        for (unsigned int j = 0; j < sw; j++)
        {
            /* Is this painfully inefficient? Probably. 
               But it will work for now. */
            noise::utils::Color sc = *(sp + (sh - i - 1) * stride + j);
            ByteColor tc = createByteColor(sc.red, sc.green, sc.blue, 
                sc.alpha, Ionflux::Altjira::Color::SPACE_RGB);
            target.setPixel(j, i, tc);
        }
}

}

}

}

/** \file altjiranoise.hpp
 * \brief Altjira/libnoise utilities (implementation).
 */

