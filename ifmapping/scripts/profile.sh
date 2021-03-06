#!/bin/bash
IFMAPPING_LIB_PATH=/home/flux/svn/stuff/trunk/ifmapping/lib
IFMAPPING_PYTHONPATH=/home/flux/svn/stuff/trunk/ifmapping/swig/python
IFOBJECT_PYTHONPATH=/home/flux/svn/iftools/trunk/ifobject/swig/python
IFOBJECT_BIN_PATH=/home/flux/svn/iftools/trunk/ifobject/bin
IFOBJECT_LIB_PATH=/home/flux/svn/iftools/trunk/ifobject/lib
IFTOOLS_BIN_PATH=/home/flux/svn/iftools/trunk/iftools/bin
IFTOOLS_LIB_PATH=/home/flux/svn/iftools/trunk/iftools/lib
ALTJIRA_LIB_PATH=/home/flux/svn/stuff/trunk/altjira/lib
ALTJIRA_PYTHONPATH=/home/flux/svn/stuff/trunk/altjira/swig/python
GEOUTILS_LIB_PATH=/home/flux/svn/stuff/trunk/geoutils/lib
GEOUTILS_PYTHONPATH=/home/flux/svn/stuff/trunk/geoutils/swig/python
TINYXML_LIB_PATH=/home/flux/svn/stuff/trunk/ifmapping/deps/tinyxml/lib
DEPS_PYTHONPATH=/home/flux/svn/stuff/trunk/ifmapping/deps/python
PATH=$PATH:$IFOBJECT_BIN_PATH:$IFTOOLS_BIN_PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$IFMAPPING_LIB_PATH:$IFOBJECT_LIB_PATH:$IFTOOLS_LIB_PATH:$GEOUTILS_LIB_PATH:$ALTJIRA_LIB_PATH:$TINYXML_LIB_PATH
PYTHONPATH=$PYTHONPATH:$IFMAPPING_PYTHONPATH:$IFOBJECT_PYTHONPATH:$ALTJIRA_PYTHONPATH:$GEOUTILS_PYTHONPATH:$DEPS_PYTHONPATH:./python
export PATH LD_LIBRARY_PATH PYTHONPATH
