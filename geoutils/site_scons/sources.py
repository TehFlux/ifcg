#!/usr/bin/python
# -*- coding: utf-8 -*-
"""Sources.

This file contains lists of source files used by the build system."""

# GeoUtils library
geoutilsLibHeaders = [
    'include/geoutils/constants.hpp',
	'include/geoutils/types.hpp', 
	'include/geoutils/utils.hpp', 
	'include/geoutils/xmlutils.hpp', 
	'include/geoutils/geoutils.hpp', 
	'include/geoutils/mappings.hpp', 
	'include/geoutils/transformnodes.hpp', 
    'include/geoutils/Accept3.hpp', 
    'include/geoutils/AcceptLength3.hpp', 
    'include/geoutils/AcceptVolume3.hpp', 
    'include/geoutils/Array.hpp', 
    'include/geoutils/Batch.hpp', 
    'include/geoutils/BoundingBox.hpp', 
    'include/geoutils/BoxBoundsItem.hpp', 
    'include/geoutils/BoxBoundsItemCompare.hpp', 
    'include/geoutils/BoxBoundsItemCompareAxis.hpp', 
    'include/geoutils/BoxBoundsItemCompareDistanceVec3.hpp', 
    'include/geoutils/BoxBoundsItemCompareDistancePlane3.hpp', 
    'include/geoutils/Cache.hpp', 
    'include/geoutils/Camera.hpp', 
    'include/geoutils/Center.hpp', 
    'include/geoutils/Clock.hpp', 
    'include/geoutils/Clone.hpp', 
    'include/geoutils/Compose3.hpp', 
    'include/geoutils/Connection.hpp', 
    'include/geoutils/Duplicate.hpp', 
    'include/geoutils/Edge.hpp', 
    'include/geoutils/Explode.hpp', 
    'include/geoutils/Face.hpp', 
    'include/geoutils/Flatten.hpp', 
    'include/geoutils/GeoUtilsError.hpp', 
    'include/geoutils/Hexagon2.hpp', 
    'include/geoutils/Interpolator.hpp', 
    'include/geoutils/ItemSource.hpp', 
    'include/geoutils/Iterate.hpp', 
    'include/geoutils/Line3.hpp', 
    'include/geoutils/LinearInterpolator.hpp', 
    'include/geoutils/Lookup3.hpp', 
    'include/geoutils/Matrix.hpp', 
    'include/geoutils/Matrix2.hpp', 
    'include/geoutils/Matrix3.hpp', 
    'include/geoutils/Matrix4.hpp', 
    'include/geoutils/MatrixMN.hpp', 
    'include/geoutils/MatrixTransform.hpp', 
    'include/geoutils/Merge.hpp', 
    'include/geoutils/Mesh.hpp', 
    'include/geoutils/Normalize.hpp', 
    'include/geoutils/Object3.hpp', 
    'include/geoutils/Shape3.hpp', 
    'include/geoutils/ParamControl.hpp', 
    'include/geoutils/Plane3.hpp', 
    'include/geoutils/Polygon2.hpp', 
    'include/geoutils/Polygon3.hpp', 
    'include/geoutils/Polygon3Compare.hpp', 
    'include/geoutils/Polygon3CompareAxis.hpp', 
    'include/geoutils/FaceCompare.hpp', 
    'include/geoutils/FaceCompareAxis.hpp', 
    'include/geoutils/Polygon3Set.hpp', 
    'include/geoutils/Range.hpp', 
    'include/geoutils/Range3.hpp', 
    'include/geoutils/Rotate.hpp', 
    'include/geoutils/Scale.hpp', 
    'include/geoutils/Scatter.hpp', 
    'include/geoutils/Source.hpp', 
    'include/geoutils/Sphere3.hpp', 
    'include/geoutils/Split.hpp', 
    'include/geoutils/SplitSet.hpp', 
    'include/geoutils/TransformGraph.hpp', 
    'include/geoutils/TransformNode.hpp', 
    'include/geoutils/DeferredTransform.hpp', 
    'include/geoutils/TransformableGroup.hpp', 
    'include/geoutils/TransformableObject.hpp', 
    'include/geoutils/Translate.hpp', 
    'include/geoutils/Unwrap.hpp', 
    'include/geoutils/Vector.hpp', 
    'include/geoutils/Vector2.hpp', 
    'include/geoutils/Vector3.hpp', 
    'include/geoutils/VectorSet.hpp', 
    'include/geoutils/VectorSetSet.hpp', 
    'include/geoutils/FaceData.hpp', 
    'include/geoutils/Vector3Mapping.hpp', 
    'include/geoutils/Vector3MappingSet.hpp', 
    'include/geoutils/Vector4.hpp', 
    'include/geoutils/VectorN.hpp', 
    'include/geoutils/Vertex.hpp', 
    'include/geoutils/Vertex2.hpp', 
    'include/geoutils/Vertex3.hpp', 
    'include/geoutils/Vertex3Set.hpp', 
    'include/geoutils/Voxel.hpp', 
    'include/geoutils/Wrap.hpp', 
    'include/geoutils/WriteSVG.hpp', 
    'include/geoutils/ImageProperties.hpp', 
    'include/geoutils/SVGShapeStyleSource.hpp', 
    'include/geoutils/SVGShapeStyleMap.hpp', 
    'include/geoutils/SVGShapeStyleVectorSource.hpp', 
    'include/geoutils/SVGImageProperties.hpp', 
    'include/geoutils/xml_factories.hpp'
]

geoutilsLibSources = [
    'build/utils.cpp', 
	'build/xmlutils.cpp', 
    'build/Accept3.cpp', 
    'build/AcceptLength3.cpp', 
    'build/AcceptVolume3.cpp', 
    'build/Array.cpp', 
    'build/Batch.cpp', 
    'build/BoundingBox.cpp', 
    'build/BoxBoundsItem.cpp', 
    'build/BoxBoundsItemCompare.cpp', 
    'build/BoxBoundsItemCompareAxis.cpp', 
    'build/BoxBoundsItemCompareDistanceVec3.cpp', 
    'build/BoxBoundsItemCompareDistancePlane3.cpp', 
    'build/Cache.cpp', 
    'build/Camera.cpp', 
    'build/Center.cpp', 
    'build/Clock.cpp', 
    'build/Clone.cpp', 
    'build/Compose3.cpp', 
    'build/Connection.cpp', 
    'build/Duplicate.cpp', 
    'build/Edge.cpp', 
    'build/Explode.cpp', 
    'build/Face.cpp', 
    'build/Flatten.cpp', 
    'build/GeoUtilsError.cpp', 
    'build/Hexagon2.cpp', 
    'build/Interpolator.cpp', 
    'build/ItemSource.cpp', 
    'build/Iterate.cpp', 
    'build/Line3.cpp', 
    'build/LinearInterpolator.cpp', 
    'build/Lookup3.cpp', 
    'build/Matrix.cpp', 
    'build/Matrix2.cpp', 
    'build/Matrix3.cpp', 
    'build/Matrix4.cpp', 
    'build/MatrixMN.cpp', 
    'build/MatrixTransform.cpp', 
    'build/Merge.cpp', 
    'build/Mesh.cpp', 
    'build/Normalize.cpp', 
    'build/Object3.cpp', 
    'build/Shape3.cpp', 
    'build/ParamControl.cpp', 
    'build/Plane3.cpp', 
    'build/Polygon2.cpp', 
    'build/Polygon3.cpp', 
    'build/Polygon3Compare.cpp', 
    'build/Polygon3CompareAxis.cpp', 
    'build/FaceCompare.cpp', 
    'build/FaceCompareAxis.cpp', 
    'build/Polygon3Set.cpp', 
    'build/Range.cpp', 
    'build/Range3.cpp', 
    'build/Rotate.cpp', 
    'build/Scale.cpp', 
    'build/Scatter.cpp', 
    'build/Source.cpp', 
    'build/Sphere3.cpp', 
    'build/Split.cpp', 
    'build/SplitSet.cpp', 
    'build/TransformGraph.cpp', 
    'build/TransformNode.cpp', 
    'build/DeferredTransform.cpp', 
    'build/TransformableGroup.cpp', 
    'build/TransformableObject.cpp', 
    'build/Translate.cpp', 
    'build/Unwrap.cpp', 
    'build/Vector.cpp', 
    'build/Vector2.cpp', 
    'build/Vector3.cpp', 
    'build/VectorSet.cpp', 
    'build/VectorSetSet.cpp', 
    'build/FaceData.cpp', 
    'build/Vector3Mapping.cpp', 
    'build/Vector3MappingSet.cpp', 
    'build/Vector4.cpp', 
    'build/VectorN.cpp', 
    'build/Vertex.cpp', 
    'build/Vertex2.cpp', 
    'build/Vertex3.cpp', 
    'build/Vertex3Set.cpp', 
    'build/Voxel.cpp', 
    'build/Wrap.cpp', 
    'build/WriteSVG.cpp', 
    'build/ImageProperties.cpp', 
    'build/SVGShapeStyleSource.cpp', 
    'build/SVGShapeStyleMap.cpp', 
    'build/SVGShapeStyleVectorSource.cpp', 
    'build/SVGImageProperties.cpp', 
    'build/gslutils.cpp'
]

geoutilsLibClasses = [
    'Accept3', 
    'AcceptLength3', 
    'AcceptVolume3', 
    'Array', 
    'Batch', 
    'BoundingBox', 
    'BoxBoundsItem', 
    'BoxBoundsItemCompare', 
    'BoxBoundsItemCompareAxis', 
    'BoxBoundsItemCompareDistanceVec3', 
    'BoxBoundsItemCompareDistancePlane3', 
    'Cache', 
    'Camera', 
    'Center', 
    'Clock', 
    'Clone', 
    'Compose3', 
    'Connection', 
    'Duplicate', 
    'Edge', 
    'Explode', 
    'Face', 
    'Flatten', 
    'GeoUtilsError', 
    'Hexagon2', 
    'Interpolator', 
    'ItemSource', 
    'Iterate', 
    'Line3', 
    'LinearInterpolator', 
    'Lookup3', 
    'Matrix', 
    'Matrix2', 
    'Matrix3', 
    'Matrix4', 
    'MatrixMN', 
    'MatrixTransform', 
    'Merge', 
    'Mesh', 
    'Normalize', 
    'Object3', 
    'Shape3', 
    'ParamControl', 
    'Plane3', 
    'Polygon2', 
    'Polygon3', 
    'Polygon3Compare', 
    'Polygon3CompareAxis', 
    'FaceCompare', 
    'FaceCompareAxis', 
    'Polygon3Set', 
    'Range', 
    'Range3', 
    'Rotate', 
    'Scale', 
    'Scatter', 
    'Source', 
    'Sphere3', 
    'Split', 
    'SplitSet', 
    'TransformGraph', 
    'TransformNode', 
    'DeferredTransform', 
    'TransformableGroup', 
    'TransformableObject', 
    'Translate', 
    'Unwrap', 
    'Vector', 
    'Vector2', 
    'Vector3', 
    'VectorSet', 
    'VectorSetSet', 
    'FaceData', 
    'Vector3Mapping', 
    'Vector3MappingSet', 
    'Vector4', 
    'VectorN', 
    'Vertex', 
    'Vertex2', 
    'Vertex3', 
    'Vertex3Set', 
    'Voxel', 
    'Wrap', 
    'WriteSVG', 
    'ImageProperties', 
    'SVGShapeStyleSource', 
    'SVGShapeStyleMap', 
    'SVGShapeStyleVectorSource', 
    'SVGImageProperties'
]

geoutilsLibXMLClasses = [
    'Vector', 
    'Vector2', 
    'Vector3', 
    'Vector4', 
    'VectorN', 
    'VectorSet', 
    'VectorSetSet', 
    'Object3',  
    'Matrix',  
    'Matrix2', 
    'Matrix3', 
    'Matrix4', 
    'MatrixMN', 
    'FaceData', 
    'DeferredTransform', 
    'TransformableObject', 
    'Vertex2', 
    'Vertex3', 
    'Vertex3Set', 
    'Face', 
    'Edge', 
    'Mesh', 
    'TransformableGroup', 
    'Polygon3', 
    'Polygon3Set', 
    'Shape3', 
    'Camera'
]

# Altjira/GeoUtils library
altjiraGeoUtilsLibHeaders = [
    'include/geoutils/altjirageoutils.hpp',
    'include/geoutils/imageutils.hpp',
	'include/geoutils/Image.hpp', 
    'include/geoutils/Render.hpp', 
    'include/geoutils/WritePNG.hpp', 
    'include/geoutils/LoadSVG.hpp', 
    'include/geoutils/SVG.hpp', 
    'include/geoutils/ImageItem.hpp', 
    'include/geoutils/ImageSource.hpp', 
    'include/geoutils/ImageLoader.hpp'
]

altjiraGeoUtilsLibSources = [
    'build/imageutils.cpp', 
    'build/Image.cpp', 
    'build/Render.cpp', 
    'build/WritePNG.cpp', 
    'build/LoadSVG.cpp', 
    'build/SVG.cpp', 
    'build/ImageItem.cpp', 
    'build/ImageSource.cpp', 
    'build/ImageLoader.cpp'
]

altjiraGeoUtilsLibClasses = [
    'Image', 
    'Render', 
    'WritePNG', 
    'LoadSVG', 
    'SVG', 
    'ImageItem', 
    'ImageSource', 
    'ImageLoader'
]

altjiraGeoUtilsLibXMLClasses = [
]

# GeoUtils/FBX library
fbxGeoUtilsLibHeaders = [
    'include/geoutils/geoutilsfbx.hpp',
    'include/geoutils/fbxtypes.hpp',
    'include/geoutils/fbxutils.hpp',
    'include/geoutils/fbxutils_private.hpp',
    'include/geoutils/FBXManager.hpp', 
    'include/geoutils/FBXScene.hpp', 
    'include/geoutils/FBXNode.hpp', 
    'include/geoutils/FBXNodeSet.hpp'
]

fbxGeoUtilsLibSources = [
    'build/fbxutils.cpp', 
    'build/FBXManager.cpp', 
    'build/FBXScene.cpp', 
    'build/FBXNode.cpp', 
    'build/FBXNodeSet.cpp'
]

fbxGeoUtilsLibClasses = [
    'FBXManager', 
    'FBXScene', 
    'FBXNode', 
    'FBXNodeSet'
]

fbxGeoUtilsLibXMLClasses = [
]

# GeoUtils/GL library
glGeoUtilsLibHeaders = [
    'include/geoutils/gltypes.hpp', 
    'include/geoutils/Program.hpp'
]

glGeoUtilsLibSources = [
    'build/Program.cpp'
]

glGeoUtilsLibClasses = [
    'Program'
]

glGeoUtilsLibXMLClasses = [
]

