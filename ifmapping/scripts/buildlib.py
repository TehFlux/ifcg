#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
from ifresource import FileResource

FILE_TYPES = {
    '.cpp' : 0
}
"""Source code file types."""

IFMAPPING_PREFIX = "/home/flux2/svn/stuff/trunk/ifmapping"
IFOBJECT_PREFIX = "/home/flux2/svn/iftools/trunk/ifobject"

IFOBJECT_INCLUDE_PATH = IFOBJECT_PREFIX + os.path.sep + "include"
IFOBJECT_LIB_PATH = IFOBJECT_PREFIX + os.path.sep + "lib"
IFMAPPING_INCLUDE_PATH = IFMAPPING_PREFIX + os.path.sep + "include"
IFMAPPING_LIB_PATH = IFMAPPING_PREFIX + os.path.sep + "lib"

sourceDir = IFMAPPING_PREFIX + os.path.sep + "src"
"""Source directory."""
mapFile = (IFMAPPING_PREFIX + os.path.sep + "temp" + os.path.sep 
    + "libifmapping_src_map.py")
"""Map file."""

IFMAPPING_LIB_MODULES = None
"""Modules to be used for the library."""

def buildModule(fileRecord):
    """Build a library."""
    prefix, fn0 = os.path.split(fileRecord.path)
    root, ext = os.path.splitext(fn0)
    print "  Compiling module '" + str(root) + "'..."
    c0 = ("g++ -fPIC -shared -g -c -o build" + os.path.sep + root + ".os " 
        + "-Iinclude -Iinclude" + os.path.sep + "geoutils -I" 
        + IFOBJECT_INCLUDE_PATH + " -Ideps" + os.path.sep + "tinyxml" 
        + os.path.sep + "include -Ideps" + os.path.sep + "MersenneTwister" 
        + os.path.sep + "include $(pkg-config --cflags-only-I sigc++-2.0) " 
        + "src" + os.path.sep + fn0)
    os.popen(c0).read()

def linkLib(files, libName, modules = None):
    """Link the library."""
    print "  Linking library '" + libName + "'..."
    fileNames = ""
    if (modules is None):
        m0 = None
    else:
        m0 = set(modules)
    for xk in files:
        it = files[xk]
        prefix, fn0 = os.path.split(it.path)
        root, ext = os.path.splitext(fn0)
        if ((m0 is None) 
            or (root in m0)):
            fileNames += (' build' + os.path.sep + root + '.os')
    c0 = ("g++ -fPIC -shared -g -o lib" + os.path.sep + "lib" + libName + ".so " 
        + "$(pkg-config --libs sigc++-2.0) -L" + IFOBJECT_LIB_PATH 
        + " -lifobject -Ldeps" + os.path.sep + "tinyxml" + os.path.sep 
        + "lib -ltinyxml" + fileNames)
    #print c0
    os.popen(c0).read()

print "Scanning '" + sourceDir + "' for source files..."
allFiles, newFiles, changedFiles, removedFiles = FileResource.scan(
    [ sourceDir ], mapFile, True, FILE_TYPES)
print (str(len(allFiles)) + ' files found (' + str(len(newFiles)) 
    + " new, " + str(len(changedFiles)) + " changed).")

for xk in newFiles:
    buildModule(allFiles[xk])
for xk in changedFiles:
    buildModule(allFiles[xk])

if ((len(newFiles) > 0)
    or (len(changedFiles) > 0)):
    linkLib(allFiles, 'ifmapping', IFMAPPING_LIB_MODULES)

print "All done!"
