#ifndef IONFLUX_ALTJIRA_CONSTANTS
#define IONFLUX_ALTJIRA_CONSTANTS
/* ==========================================================================
 * Altjira - Ionflux' Image Processing Library
 * Copyright © 2009 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * constants.hpp                     Constants (header).
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

#include <string>
#include "ifmapping/types.hpp"
#include "altjira/types.hpp"

namespace Ionflux
{

namespace Altjira
{

/// Default clamp range.
const Ionflux::Mapping::Range DEFAULT_CLAMP_RANGE = { 0., 1. };

/// Default brush name.
const std::string DEFAULT_BRUSH_NAME = "brush";
/// Default brush spacing.
const unsigned int DEFAULT_BRUSH_SPACING = 20;

/// Desaturation method: By value.
const Ionflux::Altjira::DesaturationMethod DESATURATION_BY_VALUE = 0;
/// Desaturation method: By luminance.
const Ionflux::Altjira::DesaturationMethod DESATURATION_BY_LUMINANCE = 1;
/// Default desaturation method.
const Ionflux::Altjira::DesaturationMethod DEFAULT_DESATURATION_METHOD = 
    DESATURATION_BY_VALUE;

/// GIMP GIH default rank specification.
const Ionflux::Altjira::GIHRankSpec GIH_DEFAULT_RANK_SPEC = { "random", 0 };

/// Channel: red.
const Ionflux::Altjira::ChannelID CH_RED = 0;
/// Channel: green.
const Ionflux::Altjira::ChannelID CH_GREEN = 1;
/// Channel: blue.
const Ionflux::Altjira::ChannelID CH_BLUE = 2;
/// Channel: hue.
const Ionflux::Altjira::ChannelID CH_HUE = 3;
/// Channel: saturation.
const Ionflux::Altjira::ChannelID CH_SATURATION = 4;
/// Channel: value.
const Ionflux::Altjira::ChannelID CH_VALUE = 5;
/// Channel: luminance.
const Ionflux::Altjira::ChannelID CH_LUMINANCE = 6;
/// Channel: alpha.
const Ionflux::Altjira::ChannelID CH_ALPHA = 7;

/// Fill rule: winding.
const Ionflux::Altjira::FillRule FILL_RULE_WINDING = 0;
/// Fill rule: even/odd.
const Ionflux::Altjira::FillRule FILL_RULE_EVEN_ODD = 1;

/// Default font description.
const std::string DEFAULT_FONT_DESCRIPTION = "Bitstream Vera Sans";
/// Default font size.
const double DEFAULT_FONT_SIZE = 20.;

}

}

/** \file constants.hpp
 * \brief Constants (header).
 */
#endif
