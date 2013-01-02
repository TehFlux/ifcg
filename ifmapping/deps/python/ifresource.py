#!/usr/bin/python
# -*- coding: utf-8 -*-
# ==========================================================================
# Ionflux's Stuff
# Copyright © 2005-2008 Jörn P. Meier
# mail@ionflux.org
# --------------------------------------------------------------------------
# ifresource.py           Resource management.
# ==========================================================================
# 
# This file is part of Ionflux's Stuff.
# 
# Ionflux's Stuff is free software; you can redistribute it and/or modify 
# it under the terms of the GNU General Public License as published by 
# the Free Software Foundation; either version 2 of the License, or (at 
# your option) any later version.
# 
# Ionflux's Stuff is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
# Public License for more details.
# 
# You should have received a copy of the GNU General Public License along 
# with Ionflux's Stuff; if not, write to the Free Software Foundation, 
# Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
# 
# ==========================================================================
"""Resource management.

This module provides classes to manage resources of various types.

The file resource allows scanning of directories for specific file types and 
checking for changes."""
import os, hashlib

class ResourceError(Exception):
    """Generic exception for Resource errors."""
    value = ""
    """Value which is reported with the exception."""
    
    def __init__(self, value = ""):
        self.value = value
    
    def __str__(self):
        return self.value
    
    def __repr__(self):
        return "ResourceError(" + repr(self.value) + ")"

def msg(text, source = None):
    """Message reporting function."""
    if (source is None):
        print text
    else:
        print "[" + source + "] " + text

RESOURCES = {}
"""Global resource map."""

class Resource:
    """Resource.
    
    A resource is data which depends on other resources or may be depended 
    upon by other resources. This defines a hierarchy of resources."""
    
    def __init__(self):
        pass
    
    def getResourceKey(self):
        """Get resource key.
        
        Get a unique key by which this resource can be identified and 
        referenced. This must be implemented by derived classes."""
        raise ResourceError("Resource key not implemented for unspecialized"
            " resources.")
    
    @classmethod
    def scan(cls):
        """Scan for resources.
        
        Scan the configured sources for resource items. The sources and their 
        configuration are defined by derived classes. The scan yields a list 
        containing maps, indexed by resource ID, of all resources, new 
        resources, resources that have changed since the last scan and 
        resources that are no longer available."""
        return [{}, {}, {}, {}]
    
    @classmethod
    def update(cls, newResources, resources = RESOURCES):
        """Update resources.
        
        Update the resources dictionary with the resources from dictionary 
        newResources. Resources will be indexed by resource keys."""
        for k in newResources:
            r = newResources[k]
            rk = r.getResourceKey()
            # <---- DEBUG -----
            #msg("[Resource.update] DEBUG: "
            #    "Adding resource '" + rk + "'...")
            # ----- DEBUG ---->
            resources[rk] = r
    
    @classmethod
    def saveResourceMap(cls, files, mapFile):
        """Save resource map."""
        open(mapFile, 'w').write("#!/usr/bin/python\n# -*- coding: utf-8 -*-\n" 
            "from ifresource import Resource\n\n"
            "RESOURCES = " + repr(files))
        return True
    
    @classmethod
    def loadResourceMap(cls, fileName):
        """Load resource map."""
        result = {}
        execfile(fileName, result)
        return result["RESOURCES"]

class FileResource(Resource):
    """Resource which is represented by a file."""
    path = ""
    """Full path of the file."""
    fileType = None
    """File type."""
    lastChangeTime = 0.
    """Time of last change."""
    md5Hash = None
    """MD5 hash."""
    fileTypes = {}
    """Source file types."""
    
    def __init__(self, path = "", fileType = None, lastChangeTime = 0., 
        md5Hash = None):
        Resource.__init__(self)
        self.path = path
        self.fileType = fileType
        self.lastChangeTime = lastChangeTime
        self.md5Hash = md5Hash
    
    def getLastChangeTime(self):
        """Get time of last change."""
        si = os.lstat(self.path)
        self.lastChangeTime = si.st_mtime
        return self.lastChangeTime
    
    def getMD5Hash(self):
        """Get md5 hash of the file."""
        d = open(self.path).read()
        h = hashlib.md5()
        h.update(d)
        self.md5Hash = h.hexdigest()
        return 
    
    def hasChanged(self):
        """Check whether the file has changed.
        
        Returns True if the file appears to have changed since its change time 
        and hash were last checked. Returns False otherwise."""
        oldCT = self.lastChangeTime
        oldHash = self.md5Hash
        self.getLastChangeTime()
        if (self.lastChangeTime == oldCT):
            return False
        self.getMD5Hash()
        if (self.md5Hash != oldHash):
            return True
        return False
    
    def getResourceKey(self):
        """Get resource key.
        
        Get a unique key by which this resource can be identified and 
        referenced. (Implemented from Resource.)"""
        return FileResource.makeKey(self.path)
    
    def __str__(self):
        return "FileResource[" + str(self.path) + "]"
    
    def __repr__(self):
        return ("FileResource(" + repr(self.path) + ", " 
            + repr(self.fileType) + ", " + repr(self.lastChangeTime) + ", " 
            + repr(self.md5Hash) + ")")
    
    @classmethod
    def makeKey(self, path):
        """Make resource key.
        
        Make resource key from file path."""
        return "FileResource:" + str(path)
    
    @classmethod
    def scanDir(cls, dirName, recursive = True, types = None):
        """Scan directory for data files.
        
        Scans the specified directory for data files. Returns a map of 
        FileResource objects indexed by resource key. If the optional recursive 
        flag is set to True, subdirectories will be scanned for data files 
        recursively. File types will be determined from the types map which 
        maps file suffixes to type IDs. If a file has a suffix not included in 
        the map, it will not be added to the result map."""
        if (types is None):
            types = cls.fileTypes
        result = {}
        l = os.listdir(dirName)
        for it in l:
            fp = dirName + os.path.sep + it
            if (recursive 
                and os.path.isdir(fp)):
                result.update(cls.scanDir(fp, recursive, types))
            elif (os.path.isfile(fp)):
                base, ext = os.path.splitext(fp)
                if (ext in types):
                    fileType = types[ext]
                    # <---- DEBUG -----
                    #msg("[FileResource.scanDir] DEBUG: "
                    #    "Adding file: " + fp + " (type: " + str(fileType) 
                    #    + ")")
                    # ----- DEBUG ---->
                    fr = cls(fp, fileType)
                    result[fr.getResourceKey()] = fr
                #else:
                    # <---- DEBUG -----
                    #msg("[FileResource.scanDir] DEBUG: "
                    #    "Ignoring file of unknown type: " + fp)
                    # ----- DEBUG ---->
        return result
    
    @classmethod
    def scanDirs(cls, dirList, recursive = True, types = None):
        """Scan multiple directories for data files.
        
        Scans the specified directories for data files. Returns a map of 
        FileResource objects indexed by resource key. This function works much 
        like scanDir."""
        if (types is None):
            types = cls.fileTypes
        result = {}
        for d in dirList:
            # <---- DEBUG -----
            #msg("[FileResource.scanDirs] DEBUG: "
            #    "Scanning directory: " + d)
            # ----- DEBUG ---->
            r = cls.scanDir(d, recursive, types)
            result.update(r)
        return result
    
    @classmethod
    def saveResourceMap(cls, files, mapFile):
        """Save resource map."""
        open(mapFile, 'w').write("#!/usr/bin/python\n# -*- coding: utf-8 -*-\n" 
            "from ifresource import FileResource\n\n"
            "RESOURCES = " + repr(files))
        return True
    
    @classmethod
    def scan(cls, dirList, mapFile, recursive = True, types = None):
        """Scan for file resources.
        
        Scan the specified directories for files. Use mapFile to obtain data 
        about results of the previous scan. Returns a list containing maps of 
        all resources, new resources, resources that have changed since the 
        last scan and resources that are no longer available."""
        if (types is None):
            types = cls.fileTypes
        allFiles = cls.scanDirs(dirList, recursive, types)
        if (os.path.isfile(mapFile)):
            # <---- DEBUG -----
            #msg("[FileResource.scan] DEBUG: "
            #    "Using file map: " + mapFile)
            # ----- DEBUG ---->
            prevFiles = cls.loadResourceMap(mapFile)
        else:
            # <---- DEBUG -----
            #msg("[FileResource.scan] DEBUG: "
            #    "File map '" + mapFile + "' does not seem to exist.")
            # ----- DEBUG ---->
            prevFiles = {}
        # Determine new and removed files.
        newFiles = {}
        removedFiles = {}
        changeCandidates = {}
        for k in allFiles:
            it = allFiles[k]
            if (not k in prevFiles):
                # <---- DEBUG -----
                #msg("[FileResource.scan] DEBUG: "
                #    "New file: " + it.path)
                # ----- DEBUG ---->
                newFiles[k] = it
                it.getMD5Hash()
            else:
                # File is not new, so we need to check for changes.
                it.md5Hash = prevFiles[k].md5Hash
                changeCandidates[k] = it
        for k in prevFiles:
            it = prevFiles[k]
            if (not k in allFiles):
                # <---- DEBUG -----
                #msg("[FileResource.scan] DEBUG: "
                #    "File has been removed: " + it.path)
                # ----- DEBUG ---->
                removedFiles[k] = it
        # Determine changed files.
        changedFiles = {}
        for k in changeCandidates:
            it = changeCandidates[k]
            if (it.hasChanged()):
                # <---- DEBUG -----
                #msg("[FileResource.scan] DEBUG: "
                #    "File has changed: " + it.path)
                # ----- DEBUG ---->
                changedFiles[k] = it
        cls.saveResourceMap(allFiles, mapFile)
        return [ allFiles, newFiles, changedFiles, removedFiles ]

