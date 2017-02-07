# IFCG - Ionflux Computer Graphics Toolkit
Copyright © 2013-2017 Joern P. Meier <mail@ionflux.org>

---
## README
---

### What is it?

The Ionflux Computer Graphics Toolkit (IFCG) is a collection of 
libraries for 2D and 3D graphics processing. The toolkit is written 
primarily in C++ and has full Python bindings for all components.

Components of IFCG include:

IFMapping    Mapping library.
             IFMapping is used to create mappings of scalar values to 
             scalar values or vectors at run-time. The library is based 
             on modules that can be chained and combined as necessary 
             to create the desired mapping.

Altjira      Image processing library.
             Altjira is used for processing of 2D images.

GeoUtils     2D/3D geometry library.
             GeoUtils is a 2D and 3D geometry library. It provides 
             features such as polygon and mesh transformations and an 
             AABB tree. It also contains a fully featured modular 
             transform node framework.
             
IFVG         Volumetric graphics library
             IFVG is a library for volumetric graphics processing and 
             visualization. It includes an efficient and versatile 
             octree data structure, a mesh voxelization engine and an 
             OpenGL viewer.

### Dependencies

IFCG depends on the following packages:

* Ionflux Object Base System (http://sf.net/projects/iftools)
* Ionflux Tools (http://sf.net/projects/iftools, optional, required for 
  generating the source files from the class configuration files)

Make sure you get a recent SVN version of Ionflux Object Base System and 
Ionflux Tools. Older packages will most likely not work.

You can checkout the recent source code from GitHub like this:

git clone https://github.com/TehFlux/ifcg.git
git clone https://github.com/TehFlux/iftools.git

The individual libraries that are part of IFCG may have additional 
dependencies. Please refer to the documentation included with these 
libraries.

### Building

Build all of the dependencies before you try to build IFCG. There 
are build instructions included with the individual projects.

Note that all of the code is created using the Ionflux Tools template 
system and Ionflux Object Base System ifclassgen.

However, the completed build of IFMapping will not depend on Ionflux 
Tools.

IFMapping uses SCons as the build system (http://www.scons.org/).

If you want to use custom configuration for the build process (for 
example, Python and library paths), copy 
site_scons/local_config.py.default to site_scons/local_config.py and 
adjust the settings as required.

If everything is set up correctly, you can build the project with 
'scons' in the main directory.

### Using

The libraries in this project are intended for developers, so you should 
be able to derive how it is meant to be used from the source code 
documentation and the scripts in the 'test' directories. If you have any 
questions, you can still contact me by mail (mail@ionflux.org).

Enjoy!

### Licensing

This software is released under the terms of the GNU General Public 
License version 2.

