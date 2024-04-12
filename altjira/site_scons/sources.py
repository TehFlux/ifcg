#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Sources.

This file contains lists of source files used by the build system."""

altjiraLibHeaders = [
    'include/altjira/constants.hpp',
	'include/altjira/types.hpp', 
	'include/altjira/utils.hpp', 
	'include/altjira/imageutils.hpp', 
	'include/altjira/altjira.hpp', 
	'include/altjira/AltjiraError.hpp', 
	'include/altjira/Color.hpp', 
	'include/altjira/ColorBand.hpp', 
	'include/altjira/ColorBlender.hpp', 
	'include/altjira/BlendSrcOver.hpp', 
	'include/altjira/BlendMultiply.hpp', 
	'include/altjira/BlendLighten.hpp', 
	'include/altjira/BlendDarken.hpp', 
	'include/altjira/BlendPlus.hpp', 
	'include/altjira/BlendChannel.hpp', 
	'include/altjira/Image.hpp', 
	'include/altjira/ImageSet.hpp', 
	'include/altjira/ColorSet.hpp'
]

altjiraLibSources = [
    'build/utils.cpp',
	'build/imageutils.cpp',
	'build/AltjiraError.cpp', 
	'build/Color.cpp', 
	'build/ColorBand.cpp', 
	'build/ColorBlender.cpp', 
	'build/BlendSrcOver.cpp', 
	'build/BlendMultiply.cpp', 
	'build/BlendLighten.cpp', 
	'build/BlendDarken.cpp', 
	'build/BlendPlus.cpp', 
	'build/BlendChannel.cpp', 
	'build/Image.cpp', 
	'build/ImageSet.cpp', 
	'build/ColorSet.cpp'
]

altjiraLibClasses = [
	'AltjiraError', 
	'Color', 
	'ColorBand', 
	'ColorBlender', 
	'BlendSrcOver', 
	'BlendMultiply', 
	'BlendLighten', 
	'BlendDarken', 
	'BlendPlus', 
	'BlendChannel', 
	'Image', 
	'ImageSet', 
	'ColorSet'
]

altjiraNoiseLibHeaders = [
    'include/altjira/altjiranoise.hpp', 
    'include/altjira/NoiseMap.hpp'
]

altjiraNoiseLibSources = [
    'build/altjiranoise.cpp', 
    'build/NoiseMap.cpp'
]

altjiraNoiseLibClasses = [
    'NoiseMap'
]

altjiraDrawLibHeaders = [
    'include/altjira/altjiradraw.hpp', 
    'include/altjira/Pattern.hpp', 
    'include/altjira/ImagePattern.hpp', 
    'include/altjira/Gradient.hpp', 
    'include/altjira/RadialGradient.hpp', 
    'include/altjira/LinearGradient.hpp', 
	'include/altjira/Drawable.hpp'
]

altjiraDrawLibSources = [
    'build/Pattern.cpp', 
    'build/ImagePattern.cpp', 
    'build/Gradient.cpp', 
    'build/RadialGradient.cpp', 
    'build/LinearGradient.cpp', 
    'build/Drawable.cpp'
]

altjiraDrawLibClasses = [
    'Pattern', 
    'ImagePattern', 
    'Gradient', 
    'RadialGradient', 
    'LinearGradient', 
    'Drawable'
]
