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
IFOBJECT_TEMPLATE_PATH = "/home/flux/svn/stuff/trunk/geoutils/template"
"""Ionflux Object Base System template path."""

sourceDir = "/home/flux2/svn/stuff/trunk/geoutils/conf/class"
"""Source directory."""
mapFile = "/home/flux2/svn/stuff/trunk/geoutils/temp/classes_map.py"
"""Map file."""

ignoreClasses = None
"""Classes to be ignored."""

def createClass(fileRecord, ignoreClasses = None):
    prefix, fn0 = os.path.split(fileRecord.path)
    root, ext = os.path.splitext(fn0)
    if (not ignoreClasses is None):
        if (root in ignoreClasses):
            return
    print "  Class '" + str(root) + "'..."
    c0 = (IFCLASSGEN_BIN + " -t " + IFOBJECT_TEMPLATE_PATH + os.path.sep 
        + "class -c conf" + os.path.sep + "class -m conf" + os.path.sep 
        + "main.conf -i include" + os.path.sep + "geoutils -s src " 
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
    createClass(allFiles[xk], ignoreClasses)
for xk in changedFiles:
    createClass(allFiles[xk], ignoreClasses)

print "All done!"
