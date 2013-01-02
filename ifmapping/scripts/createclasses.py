#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
from ifresource import FileResource

FILE_TYPES = {
    '.conf' : 0
}
"""Class configuration file types."""
IFCLASSGEN_BIN = "ifclassgen"
"""Ionflux class generator binary."""
IFTPL_BIN = "iftpl"
"""Ionflux template engine binary."""
IFMAPPING_PREFIX = "/home/flux2/svn/stuff/trunk/ifmapping"
"""Ionflux Mapping Library prefix."""
IFOBJECT_TEMPLATE_PATH = IFMAPPING_PREFIX + os.path.sep + "template"
"""Ionflux Object Base System template path."""

sourceDir = IFMAPPING_PREFIX + os.path.sep + "conf" + os.path.sep + "class"
"""Source directory."""
mapFile = (IFMAPPING_PREFIX + os.path.sep + "temp" + os.path.sep 
    + "classes_map.py")
"""Map file."""

def createClass(fileRecord, includePrefix):
    prefix, fn0 = os.path.split(fileRecord.path)
    root, ext = os.path.splitext(fn0)
    print "  Class '" + str(root) + "'..."
    c0 = (IFCLASSGEN_BIN + " -t " + IFOBJECT_TEMPLATE_PATH + os.path.sep 
        + "class -c conf" + os.path.sep + "class -m conf" + os.path.sep 
        + "main.conf -i include" + os.path.sep + includePrefix + " -s src " 
        + root)
    c1 = (IFTPL_BIN + " " + IFOBJECT_TEMPLATE_PATH + os.path.sep 
        + "interface.i.tpl conf" + os.path.sep + "class" + os.path.sep 
        + root + ".conf conf" + os.path.sep + "main.conf >swig" + os.path.sep 
        + "classes" + os.path.sep + root + ".i")
    print os.popen(c0).read(),
    print os.popen(c1).read(),

print "Scanning '" + sourceDir + "' for class configuration files..."
allFiles, newFiles, changedFiles, removedFiles = FileResource.scan(
    [ sourceDir ], mapFile, True, FILE_TYPES)
print (str(len(allFiles)) + ' files found (' + str(len(newFiles)) 
    + " new, " + str(len(changedFiles)) + " changed).")

for xk in newFiles:
    createClass(allFiles[xk], 'ifmapping')
for xk in changedFiles:
    createClass(allFiles[xk], 'ifmapping')

print "All done!"
