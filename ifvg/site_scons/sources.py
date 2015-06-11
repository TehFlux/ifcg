#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Sources.

This file contains lists of source files used by the build system."""

# IFVG library
ifvgLibHeaders = [
    'include/ifvg/constants.hpp',
	'include/ifvg/types.hpp', 
	'include/ifvg/utils.hpp', 
	'include/ifvg/serialize.hpp', 
	'include/ifvg/ifvg.hpp', 
    'include/ifvg/IFVGError.hpp', 
    'include/ifvg/Context.hpp', 
    'include/ifvg/IOContext.hpp', 
    'include/ifvg/Node.hpp',
    'include/ifvg/NodeSet.hpp', 
    'include/ifvg/Mesh.hpp', 
    'include/ifvg/NodeProcessor.hpp', 
    'include/ifvg/ChainableNodeProcessor.hpp', 
    'include/ifvg/NodeVoxelizationProcessor.hpp', 
    'include/ifvg/NodeFilter.hpp', 
    'include/ifvg/NodeIntersectionProcessor.hpp', 
    'include/ifvg/NodeFillProcessor.hpp', 
    'include/ifvg/NodeIOBEvalProcessor.hpp', 
    'include/ifvg/NodeIOBWallThicknessProcessor.hpp'
]

ifvgLibSources = [
    'build/utils.cpp', 
    'build/serialize.cpp', 
    'build/IFVGError.cpp', 
    'build/Context.cpp', 
    'build/IOContext.cpp', 
    'build/Node.cpp', 
    'build/NodeSet.cpp', 
    'build/Mesh.cpp', 
    'build/NodeProcessor.cpp', 
    'build/ChainableNodeProcessor.cpp', 
    'build/NodeVoxelizationProcessor.cpp', 
    'build/NodeFilter.cpp', 
    'build/NodeIntersectionProcessor.cpp', 
    'build/NodeFillProcessor.cpp', 
    'build/NodeIOBEvalProcessor.cpp', 
    'build/NodeIOBWallThicknessProcessor.cpp'
]

ifvgLibClasses = [
    'IFVGError', 
    'Context', 
    'IOContext', 
    'Node', 
    'NodeSet', 
    'Mesh', 
    'NodeProcessor', 
    'ChainableNodeProcessor', 
    'NodeVoxelizationProcessor', 
    'NodeFilter', 
    'NodeIntersectionProcessor', 
    'NodeFillProcessor', 
    'NodeIOBEvalProcessor', 
    'NodeIOBWallThicknessProcessor'
]

ifvgLibXMLClasses = [
    'Mesh'
]

# IFVG viewer library
ifvgViewerLibHeaders = [
    'include/ifvg/Viewer.hpp'
]

ifvgViewerLibSources = [
    'build/Viewer.cpp'
]

ifvgViewerLibClasses = [
    'Viewer'
]

ifvgViewerLibXMLClasses = [
#    'Node'
]

