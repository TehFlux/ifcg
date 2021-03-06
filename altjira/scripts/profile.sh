#!/bin/bash
FLUXHOME=/home/flux
FLUX_SVN_PATH=$FLUXHOME/svn
IFCG_SVN_PATH=$FLUX_SVN_PATH/ifcg/trunk
ALTJIRA_LIB_PATH=$IFCG_SVN_PATH/altjira/lib
ALTJIRA_BIN_PATH=$IFCG_SVN_PATH/altjira/python
ALTJIRA_PYTHONPATH=$IFCG_SVN_PATH/altjira/swig/python
IFOBJECT_PYTHONPATH=$FLUX_SVN_PATH/iftools/trunk/ifobject/swig/python
IFOBJECT_BIN_PATH=$FLUX_SVN_PATH/iftools/trunk/ifobject/bin
IFOBJECT_LIB_PATH=$FLUX_SVN_PATH/iftools/trunk/ifobject/lib
IFTOOLS_BIN_PATH=$FLUX_SVN_PATH/iftools/trunk/iftools/bin
IFTOOLS_LIB_PATH=$FLUX_SVN_PATH/iftools/trunk/iftools/lib
GEOUTILS_LIB_PATH=$IFCG_SVN_PATH/geoutils/lib
GEOUTILS_PYTHONPATH=$IFCG_SVN_PATH/geoutils/swig/python
IFMAPPING_LIB_PATH=$IFCG_SVN_PATH/ifmapping/lib
IFMAPPING_PYTHONPATH=$IFCG_SVN_PATH/ifmapping/swig/python
DEPS_PYTHONPATH=$IFCG_SVN_PATH/altjira/deps/python
PATH=$PATH:$IFOBJECT_BIN_PATH:$IFTOOLS_BIN_PATH:$ALTJIRA_BIN_PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$ALTJIRA_LIB_PATH:$ALTJIRA_LIB_PATH:$IFOBJECT_LIB_PATH:$IFMAPPING_LIB_PATH:$IFTOOLS_LIB_PATH:$GEOUTILS_LIB_PATH
PYTHONPATH=$PYTHONPATH:$ALTJIRA_PYTHONPATH:$IFOBJECT_PYTHONPATH:$IFMAPPING_PYTHONPATH:$GEOUTILS_PYTHONPATH:$DEPS_PYTHONPATH:./python
export PATH LD_LIBRARY_PATH PYTHONPATH
