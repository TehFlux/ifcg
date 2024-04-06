# GeoUtils - Ionflux' Geometry Library
Copyright © 2009-2024 • Jörn Meier <webmaster@ionflux.org>

## README

### What is it?

GeoUtils (Ionflux' Geometry Library) is an utility library for computer graphics applications.

Implementations (in various states of completeness) are provided for C++, Python and JavaScript.

Using SWIG, bindings for a large variety of programming languages can be created for the C++ library. The package currently supports Python, but it should not be too hard to generate bindings for other languages as well.

### Features

+ Basic vector math
+ Matrix transformations
+ Primitive 3D objects (Vertex, Line, Plane, Box, Sphere)
+ 3D Meshes
+ Tangent space (UV) calculations
+ Intersection checking
+ Axis-aligned bounding box (AABB) tree data structure
+ Node-based modular transform and drawing
+ Procedural brush creation for GIMP (http://www.gimp.org/)
+ Integration with Blender (http://www.blender.org/) via Python
+ Drawing polygons and transformed images with SVG and PNG support
+ OpenGL viewer

### Licensing

GeoUtils is free software released under the [GNU General Public License version 3](docs/gpl-3.0.md).

**Please note that this program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.**

### Dependencies

GeoUtils depends on the following packages:

+ [Ionflux Object Base System](https://github.com/TehFlux/iftools)
+ [Ionflux Template Processor](https://github.com/TehFlux/iftools)
+ [IFMapping - Ionflux Mapping Library](https://github.com/TehFlux/ifcg)
  
The following dependencies are optional, but highly recommended:

+ [Python](https://www.python.org/) >= 3.3  
  required for the Python bindings
+ [Altjira - Ionflux' Image Processing Library](https://github.com/TehFlux/ifcg)  
  required for pixel based image output
+ [Autodesk FBX SDK](https://www.autodesk.com/developer-network/platform-technologies/fbx-sdk-2020-3)  
  required for FBX file I/O

If you want to build the GeoUtils GL library, which provides OpenGL rendering capabilities, you will also need to provide the following dependencies:

+ OpenGL  
  this should be provided with your OS
+ [GLUT](http://freeglut.sourceforge.net)
+ [glad](https://github.com/Dav1dde/glad)  
  This can also be installed using pip. See notes below for how it is intended to be used with GeoUtils.
+ [GLFW](http://www.glfw.org)

Make sure you get a recent Git version of Ionflux Object Base System and Ionflux Template Processor. Older packages will most likely not work.

You can checkout the recent source code from GitHub like this:

`git clone git@github.com:TehFlux/iftools.git`

### Building

Build all of the dependencies before you try to build GeoUtils. There are build instructions included with the individual projects.

Note that all of the code is created using the Ionflux Template Processor.

However, the completed build of GeoUtils will not depend on Ionflux Template Processor.

GeoUtils uses [SCons](http://www.scons.org/) as the build system.

If you want to use custom configuration for the build process (for example, Python and ibrary paths), copy `site_scons/local_config.py.default` to `site_scons/local_config.py` and adjust the settings as required.

It is recommended to use a [virtualenv](https://virtualenv.pypa.io/en/latest/) for the Python components of GeoUtils.

You can easily create a virtualenv with e.g. `virtualenv ifcg_env` in a directory of your choice and then configure the build process to use this virtualenv for installation in `site_scons/local_config.py`.

Enable the virtualenv using `source <path to virtualenv>/bin/activate`.

When not installing to a system location (which is highly recommended), it is also ecommended to set up an environment with all of the required paths for development in `scripts/profile-local.sh`. You can use one of the provided templates to get started.

This environment can then be used with `source scripts/profile-local.sh`.

If everything is set up correctly, you can build the project by running 

`scons`

Install with

`scons install prefix=<installation base directory>`

where <installation base directory> ist the directory where GeoUtils should be installed.

### WARNING
 
 It is not recommended at this point to install GeoUtils in a system directory, since this is an alpha version under development. (No harm should be done even if you decide otherwise, but there is no guarantee.)

 **This software is not intended for use in production environments! Ignore this warning at your own peril.**

### Notes

For building the OpenGL utility library, an OpenGL loader needs to be generated for the specific system and OpenGL version using glad. This is expected to be compiled into a dynamic library named libglad.so (or similar, depending on the system). A suitable OpenGL loader can be generated using glad in the following way:

    glad --profile core --api "gl=3.3" --generator c \
        --spec=gl --out-path=generated

You can use the script provided in the `deps/glad/scripts` directory, as well as the provided SCons build files, to generate the code and build the shared loader library.

See also the [documentation](http://www.glfw.org/docs/latest/context.html#context_glext_auto) provided by GLFW.

### Using

This library is intended for developers, so you should be able to derive how it is meant to be used from the source code documentation and the scripts in the `test` directory. If you have any questions, you can still contact me by mail.

**Enjoy!**