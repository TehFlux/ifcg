#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Local configuration.

Use this to add local configuration that will be used for the build. To do 
this, create a copy of this file named local_config.py in the site_scons 
directory.

If you do not want to use any local configuration, a default copy will be 
created for you automatically."""

# Base name.
# Do not change this unless you know what you are doing.
baseName = 'ifvg'
## Prefix.
## Set this if you do not want to use the default or the SCons command line 
## parameter.
prefix = '/home/flux4/usr'

# Enable debug mode.
debug = True

# Python version.
pythonVersion = "3.4"
# Python site packages path.
pythonSitePackagesPath = ('/python' + pythonVersion + '/lib/python' 
    + pythonVersion + '/site-packages')

# Ionflux Object Base system template path
#ifobjectTemplatePath = 'template'
ifobjectTemplatePath = '/home/flux4/svn/iftools/trunk/ifobject/template'

# The SWIG interface template file.
swigInterfaceTemplateFile = [
    'template/' + baseName + '.i.tpl', 
    'template/' + baseName + 'viewer.i.tpl'
]
# The SWIG interface file.
swigInterfaceFile = [
    'swig/include/' + baseName + '/' + baseName + '.i', 
    'swig/include/' + baseName + '/' + baseName + 'viewer.i'
]

# Paths.
PATH = 'bin'
CPPPATH = [
    prefix + '/python' + pythonVersion + '/include/python' 
        + pythonVersion, 
    '/home/flux4/svn/iftools/trunk/ifobject/include', 
    '/home/flux4/svn/iftools/trunk/ifobject/swig/include', 
    '/home/flux4/svn/iftools/trunk/iftemplate/include', 
    '/home/flux4/svn/ifcg/trunk/ifmapping/include', 
    '/home/flux4/svn/ifcg/trunk/ifmapping/swig/include', 
    '/home/flux4/svn/ifcg/trunk/altjira/include', 
    '/home/flux4/svn/ifcg/trunk/altjira/swig/include', 
    '/home/flux4/svn/ifcg/trunk/geoutils/include', 
    '/home/flux4/svn/ifcg/trunk/geoutils/swig/include', 
    prefix + '/include', 
    prefix + '/include/noise', 
    prefix + '/fbx20151/include', 
    prefix + '/glfw-git-2014-07/include'
]
LIBPATH = [
    prefix + '/python' + pythonVersion + '/lib', 
    prefix + '/lib', 
    '/home/flux4/svn/iftools/trunk/ifobject/lib', 
    '/home/flux4/svn/iftools/trunk/iftemplate/lib', 
    '/home/flux4/svn/ifcg/trunk/ifmapping/lib', 
    '/home/flux4/svn/ifcg/trunk/altjira/lib', 
    '/home/flux4/svn/ifcg/trunk/geoutils/lib', 
    prefix + '/noise/lib', 
    prefix + '/fbx20151/lib/gcc4/x64/debug', 
    prefix + '/glfw-git-2014-07/lib', 
    '/usr/lib/nvidia-331'
]

