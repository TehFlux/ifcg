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
    for cn in classNames:
        c0 = ("ifclassgen0 -t " + lc.ifobjectTemplatePath 
            + " -c conf/class -m conf/main.conf -i include/" 
            + lc.baseName + " -s src " + cn)
        print c0
        sp0 = subprocess.call(shlex.split(c0))

def buildClassInterface(source, target, env):
    """Builder function to build SWIG interface files from class 
       configuration."""
    classNames = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
    for cn in classNames:
        c0 = ("iftpl0 -I " + lc.ifobjectTemplatePath 
            + " swig.interface conf/class/" + cn + ".conf conf/main.conf")
        print c0
        f0 = open("swig/classes/" + cn + ".i", 'w')
        sp0 = subprocess.call(shlex.split(c0), stdout = f0)
        f0.close()

def buildInterface(source, target, env):
    """Builder function to build a SWIG interface declaration."""
    classNames = []
    if (isinstance(lc.swigInterfaceTemplateFile, str)):
        templateFile = lc.swigInterfaceTemplateFile
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.i'):
            classNames += [cn]
        elif (ext == '.tpl'):
            templateFile = it.path
    tplData = {}
    p0 = re.compile("/\*.*?\*/", re.DOTALL)
    for cn in classNames:
        tplData[cn] = p0.sub('', open('swig/classes/' + cn + '.i').read())
    tplStr = open(templateFile).read()
    tpl = string.Template(tplStr)
    for it in target:
        f0 = open(it.path, 'w')
        f0.write(tpl.substitute(tplData))
        f0.close()

def buildClassXMLIO(source, target, env):
    """Builder function to build XML I/O header and implementation file 
       fragments from class configuration."""
    classNames = []
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (ext == '.conf'):
            classNames += [cn]
    # Figure out the template module and output file suffix to be used.
    templateModule = "unknown"
    suffix = ".none"
    cn, ext = os.path.splitext(os.path.basename(target[0].path))
    if (ext == '.cpp'):
        templateModule = "xml.impl.xmlutils_fragment"
        suffix = "_xml.cpp"
    elif (ext == '.hpp'):
        if (cn.endswith("_xml")):
            templateModule = "xml.header.xmlutils_fragment"
            suffix = "_xml.hpp"
        elif (cn.endswith("_xml_private")):
            templateModule = "xml.header.xmlutils_fragment_private"
            suffix = "_xml_private.hpp"
    for cn in classNames:
        c0 = ("iftpl0 -I " + lc.ifobjectTemplatePath 
            + " " + templateModule + " conf/class/" 
                + cn + ".conf conf/main.conf")
        print c0
        f0 = open("temp/xmlutils/" + cn + suffix, 'w')
        sp0 = subprocess.call(shlex.split(c0), stdout = f0)
        f0.close()

def buildXMLIO(source, target, env):
    """Builder function to build XML I/O header and implementation 
       files from class XML I/O file fragments."""
    classNames = []
    suffix = ".none"
    for it in source:
        cn, ext = os.path.splitext(os.path.basename(it.path))
        if (((ext == '.hpp')
            or (ext == '.cpp'))):
            if (cn.endswith("_xml")): 
                classNames += [ cn[:-4] ]
            elif (cn.endswith("_xml_private")):
                classNames += [ cn[:-12] ]
        elif (ext == '.tpl'):
            templateFile = it.path
        if (suffix == ".none"):
            # Figure out the suffix for the source files.
            if (ext == '.cpp'):
                suffix = "_xml.cpp"
            elif (ext == '.hpp'):
                if (cn.endswith("_xml")):
                    suffix = "_xml.hpp"
                elif (cn.endswith("_xml_private")):
                    suffix = "_xml_private.hpp"
    p0 = re.compile("/\*.*?\*/", re.DOTALL)
    tplData = {}
    for cn in classNames:
        tplData[cn] = p0.sub('', open('temp/xmlutils/' + cn 
            + suffix).read())
    tplStr = open(templateFile).read()
    tpl = string.Template(tplStr)
    for it in target:
        f0 = open(it.path, 'w')
        f0.write(tpl.substitute(tplData))
        f0.close()


