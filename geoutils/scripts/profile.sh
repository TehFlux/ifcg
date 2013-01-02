#!/bin/bash
GEOUTILS_LIB_PATH=/home/flux/svn/stuff/trunk/geoutils/lib
GEOUTILS_PYTHONPATH=/home/flux/svn/stuff/trunk/geoutils/swig/python
IFOBJECT_PYTHONPATH=/home/flux/svn/iftools/trunk/ifobject/swig/python
IFOBJECT_BIN_PATH=/home/flux/svn/iftools/trunk/ifobject/bin
IFTOOLS_BIN_PATH=/home/flux/svn/iftools/trunk/iftools/bin
IFOBJECT_LIB_PATH=/home/flux/svn/iftools/trunk/ifobject/lib
IFTOOLS_LIB_PATH=/home/flux/svn/iftools/trunk/iftools/lib
IFMAPPING_LIB_PATH=/home/flux/svn/stuff/trunk/ifmapping/lib
IFMAPPING_PYTHONPATH=/home/flux/svn/stuff/trunk/ifmapping/swig/python
TINYXML_LIB_PATH=/home/flux/svn/stuff/trunk/geoutils/deps/tinyxml/lib
ALTJIRA_LIB_PATH=/home/flux/svn/stuff/trunk/altjira/lib
ALTJIRA_PYTHONPATH=/home/flux/svn/stuff/trunk/altjira/swig/python
DEPS_PYTHONPATH=/home/flux/svn/stuff/trunk/geoutils/deps/python
PATH=$PATH:$IFOBJECT_BIN_PATH:$IFTOOLS_BIN_PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GEOUTILS_LIB_PATH:$IFOBJECT_LIB_PATH:$IFMAPPING_LIB_PATH:$IFTOOLS_LIB_PATH:$TINYXML_LIB_PATH:$ALTJIRA_LIB_PATH
PYTHONPATH=$PYTHONPATH:$GEOUTILS_PYTHONPATH:$IFOBJECT_PYTHONPATH:$IFMAPPING_PYTHONPATH:$ALTJIRA_PYTHONPATH:$DEPS_PYTHONPATH:./python
export PATH LD_LIBRARY_PATH PYTHONPATH
