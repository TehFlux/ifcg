#!/usr/bin/python
# -*- coding: utf-8 -*-
# ==========================================================================
# Ionflux Object Base System
# Copyright © 2006-2013 Joern P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# builders.py                  SCons builders.
# ==========================================================================
# 
# This file is part of Ionflux Object Base System.
# 
# Ionflux Object Base System is free software; you can redistribute it 
# and/or modify it under the terms of the GNU General Public License as 
# published by the Free Software Foundation; either version 2 of the 
# License, or (at  your option) any later version.
# 
# Ionflux Object Base System is distributed in the hope that it will be 
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
# General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Ionflux Object Base System; if not, write to the Free 
# Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
# 02111-1307 USA
# 
# ==========================================================================
import os, shlex, shutil, subprocess, re, string
import local_config as lc

def buildSource(source, target, env):
    """Builder function to build source files from class configuration."""
    classNames = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
    sourcePath = os.path.dirname(source[0].path)
    targetIncludePath = os.path.dirname(target[0].path)
    targetSrcPath = os.path.dirname(target[1].path)
    for cn in classNames:
        c0 = ("ifclassgen0 -t " + lc.ifobjectTemplatePath 
            + " -c " + sourcePath + " -m conf/main.conf -i " 
            + targetIncludePath + " -s " + targetSrcPath + " " + cn)
        print(c0)
        sp0 = subprocess.call(shlex.split(c0))

def buildClassInterface(source, target, env):
    """Builder function to build SWIG interface files from class 
       configuration."""
    classNames = []
    sourceFiles = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
            sourceFiles += [it.path]
    for k in range(0, len(classNames)):
        cn = classNames[k]
        c0 = ("iftpl0 -I " + lc.ifobjectTemplatePath 
            + " swig.interface " + sourceFiles[k] + " conf/main.conf")
        print(c0)
        f0 = open(target[k].path, 'w')
        sp0 = subprocess.call(shlex.split(c0), stdout = f0)
        f0.close()

def buildInterface(source, target, env):
    """Builder function to build a SWIG interface declaration."""
    classNames = []
    sourceFiles = []
    if (isinstance(lc.swigInterfaceTemplateFile, str)):
        templateFile = lc.swigInterfaceTemplateFile
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.i'):
            classNames += [cn]
            sourceFiles += [it.path]
        elif (ext == '.tpl'):
            templateFile = it.path
    tplData = {}
    p0 = re.compile("/\\*.*?\\*/", re.DOTALL)
    for k in range(0, len(classNames)):
        cn = classNames[k]
        tplData[cn] = p0.sub('', open(sourceFiles[k]).read())
    tplStr = open(templateFile).read()
    tpl = string.Template(tplStr)
    for it in target:
        f0 = open(it.path, 'w')
        f0.write(tpl.substitute(tplData))
        f0.close()

def buildClassXMLFactory(source, target, env):
    """Builder function to build an XML object factory configuration file 
       from class configuration."""
    classNames = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
    for cn in classNames:
        c0 = ("iftpl0 -I " + lc.ifobjectTemplatePath 
            + " xml.conf.xml_object_factory conf/class/" + cn 
            + ".conf conf/main.conf")
        print(c0)
        f0 = open("conf/class/xmlio/" + cn + "XMLFactory.conf", 'w')
        sp0 = subprocess.call(shlex.split(c0), stdout = f0)
        f0.close()

