#ifndef IONFLUX_ALTJIRA_NOISE
#define IONFLUX_ALTJIRA_NOISE
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2009-2010 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * altjiranoise.hpp             Altjira/libnoise utilities (header).
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

#include "noise/noiseutils.h"
#include "altjira/Image.hpp"
#include "altjira/NoiseMap.hpp"

namespace Ionflux
{

namespace Altjira
{

namespace Noise
{

/** Initialize image from libnoise image.
 *
 * Initialize an Altjira image from a libnoise image.
 *
 * \param source Source image.
 * \param target Target image.
 */
void setImage(const noise::utils::Image& source, 
    Ionflux::Altjira::Image& target);

}

}

}

/** \file altjiranoise.hpp
 * \brief Altjira/libnoise utilities (header).
 */
#endif
