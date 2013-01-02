#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
from ifresource import FileResource

FILE_TYPES = {
    '.cpp' : 0
}
"""Source code file types."""

IFOBJECT_PREFIX = "/home/flux/svn/iftools/trunk/ifobject"
IFMAPPING_PREFIX = "/home/flux2/svn/stuff/trunk/ifmapping"
ALTJIRA_PREFIX = "/home/flux/svn/stuff/trunk/altjira"

IFOBJECT_INCLUDE_PATH = IFOBJECT_PREFIX + os.path.sep + "include"
IFOBJECT_LIB_PATH = IFOBJECT_PREFIX + os.path.sep + "lib"
IFMAPPING_INCLUDE_PATH = IFMAPPING_PREFIX + os.path.sep + "include"
IFMAPPING_LIB_PATH = IFMAPPING_PREFIX + os.path.sep + "lib"
ALTJIRA_INCLUDE_PATH = ALTJIRA_PREFIX + os.path.sep + "include"
ALTJIRA_LIB_PATH = ALTJIRA_PREFIX + os.path.sep + "lib"

sourceDir = "/home/flux2/svn/stuff/trunk/geoutils/src"
"""Source directory."""
mapFile = "/home/flux2/svn/stuff/trunk/geoutils/temp/libgeoutils_src_map.py"
"""Map file."""

altjiraModules = [ 'Image', 'WritePNG', 'Render' ]

def buildModule(fileRecord):
    """Build a library."""
    prefix, fn0 = os.path.split(fileRecord.path)
    root, ext = os.path.splitext(fn0)
    print "  Compiling module '" + str(root) + "'..."
    c0 = ("g++ -fPIC -shared -g -c -o build" + os.path.sep + root + ".os " 
        + "-Iinclude -Iinclude" + os.path.sep + "geoutils " 
        + "-I" + IFMAPPING_INCLUDE_PATH + " "
        + "-I" + IFOBJECT_INCLUDE_PATH + " "
        + "-I" + ALTJIRA_INCLUDE_PATH + " "
        + "-Ideps" + os.path.sep + "tinyxml" + os.path.sep + "include " 
        + "$(pkg-config --cflags-only-I sigc++-2.0) " 
        + "$(pkg-config --cflags-only-I gdk-pixbuf-2.0) "
        + "$(pkg-config --cflags-only-I cairo) "
        + "src" + os.path.sep + fn0)
    os.popen(c0).read()

def linkLib(files, libName, modules = None, excludeModules = None, 
    flags = None):
    """Link the library."""
    print "  Linking library '" + libName + "'..."
    fileNames = ""
    for xk in files:
        it = files[xk]
        prefix, fn0 = os.path.split(it.path)
        root, ext = os.path.splitext(fn0)
        if (((modules is None) 
                or (root in modules))
            and ((excludeModules is None) 
                or (root not in excludeModules))):
            fileNames += (' build' + os.path.sep + root + '.os')
    c0 = ("g++ -fPIC -shared -g -o lib" + os.path.sep + "lib" + libName + ".so " 
        + "$(pkg-config --libs sigc++-2.0) "
        + "-L" + IFOBJECT_LIB_PATH + " -lifobject "
        + "-L" + IFMAPPING_LIB_PATH + " -lifmapping "
        + "-Ldeps" + os.path.sep + "tinyxml" + os.path.sep 
        + "lib -ltinyxml")
    if (not flags is None):
        c0 += (" " + flags + " ")
    c0 += fileNames
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
    linkLib(allFiles, 'geoutils', None, altjiraModules)
    linkLib(allFiles, 'altjirageoutils', altjiraModules, None, 
        "-L" + ALTJIRA_LIB_PATH + " -laltjira " 
        + "$(pkg-config --libs cairo) ")

print "All done!"
