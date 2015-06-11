#ifndef IONFLUX_VOLGFX_NODEINTERSECTIONPROCESSOR
#define IONFLUX_VOLGFX_NODEINTERSECTIONPROCESSOR
/* ==========================================================================
 * IFVG - Ionflux' Volumetric Graphics Library
 * Copyright © 2014 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * NodeIntersectionProcessor.hpp   Node intersection processor (header).
 * ========================================================================== */

#include "ifvg/types.hpp"
#include "ifvg/constants.hpp"
#include "ifvg/Node.hpp"
#include "ifvg/ChainableNodeProcessor.hpp"

namespace Ionflux
{

namespace VolGfx
{

class Context;

/// Class information for class NodeIntersectionProcessor.
class NodeIntersectionProcessorClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
	public:
		/// Constructor.
		NodeIntersectionProcessorClassInfo();
		/// Destructor.
		virtual ~NodeIntersectionProcessorClassInfo();
};

/** Node intersection processor.
 * \ingroup ifvg
 *
 * A node processor for ray/node intersections. This processor can be used 
 * to set a data type and voxel class on nodes that are intersected by a 
 * ray. By default, the node intersection processor will only process leaf 
 * nodes and throw an exception if a node is passed in that is not a leaf 
 * node. This behavior can be changed by setting the \c leafStatus 
 * property. Depending on the configuration, this processor can cast ray 
 * votes for interior/exterior classification of nodes, identify boundary 
 * nodes and calculate and fix the wall thickness of connected sequences of
 * 'filled' nodes along a ray.
 */
class NodeIntersectionProcessor
: public Ionflux::VolGfx::ChainableNodeProcessor
{
	private:
		
	protected:
		/// Updated node intersections.
		Ionflux::VolGfx::NodeIntersectionVector updatedIntersections;
		/// Vector of intersections.
		std::vector<Ionflux::VolGfx::NodeIntersection> intersections;
		/// Voxel tree context.
		Ionflux::VolGfx::Context* context;
		/// node data type for ray hits.
		Ionflux::VolGfx::NodeDataType hitDataType;
		/// voxel class mask for ray hits.
		Ionflux::VolGfx::VoxelClassID voxelClassHit;
		/// leaf status flag.
		Ionflux::VolGfx::LeafStatusID leafStatus;
		/// Ray.
		Ionflux::GeoUtils::Line3* ray;
		/// boundary data enable flag.
		bool enableBoundaryData;
		/// target depth for inserting node intersections.
		int targetDepth;
		/// fill nodes that are created for new intersections.
		bool fillNewIntersections;
		/// prune empty nodes that are created for new intersections.
		bool pruneEmptyNewIntersections;
		/// enable inside/outside/boundary classification.
		bool enableIOB;
		/// mark nodes with zero intersections as outside (ray-stabbing).
		bool enableRayStabbing;
		/// enable wall thickness calculation.
		bool enableWallThickness;
		/// voxel class for 'filled' voxels.
		Ionflux::VolGfx::VoxelClassID voxelClassFilled;
		/// voxel class for 'inside' voxels.
		Ionflux::VolGfx::VoxelClassID voxelClassInside;
		/// voxel class for 'outside' voxels.
		Ionflux::VolGfx::VoxelClassID voxelClassOutside;
		/// voxel class for 'boundary' voxels.
		Ionflux::VolGfx::VoxelClassID voxelClassBoundary;
		/// Tolerance for comparisons.
		double tolerance;
		/// Ray axis.
		Ionflux::GeoUtils::AxisID rayAxis;
		/// Minimum wall thickness.
		unsigned int minWallThickness;
		/// Fill 'inside' nodes only when fixing the minimum wall thickness.
		bool fillInsideOnly;
		/// Maximum number of passes for fixing wall thickness.
		unsigned int maxNumWallThicknessPasses;
		
		/** Update node intersections.
		 *
		 * Update the current sequence of node intersections from the updated 
		 * sequence of node intersections.
		 *
		 * \param reverse reverse the order of intersections.
		 */
		virtual void updateIntersections(bool reverse = false);
		
		/** Process node implementation.
		 *
		 * Process a node implementation. \c userData is expected to contain a
		 * pointer to a NodeIntersection data record for \c nodeImpl.
		 *
		 * \param nodeImpl Node implementation.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID 
		processImpl(Ionflux::VolGfx::NodeImpl* nodeImpl, void* userData = 0);
		
		/** Process node intersections (inside/outside/boundary).
		 *
		 * Process node intersections from a vector.
		 *
		 * \param intersections0 node intersections.
		 * \param state current state.
		 * \param numIntersections0 current number of intersections.
		 * \param processingFlags processing flags.
		 * \param wallThickness current wall thickness.
		 * \param maxWallThickness current maximum wall thickness.
		 */
		virtual void processIntersectionsIOB(const 
		Ionflux::VolGfx::NodeIntersectionVector& intersections0, 
		Ionflux::VolGfx::VoxelClassID& state, unsigned int& numIntersections0, 
		Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
		unsigned int* wallThickness = 0, unsigned int* maxWallThickness = 0);
		
		/** Insert and process node intersections (inside/outside/boundary).
		 *
		 * Create new node intersections by inserting a node at the near or 
		 * far intersection point for the specified intersections and process 
		 * the new intersections recursively.
		 *
		 * \param intersection0 node intersection.
		 * \param createNear Create node for near intersection.
		 * \param createFar Create node for far intersection.
		 * \param state current state.
		 * \param numIntersections0 current number of intersections.
		 * \param processingFlags processing flags.
		 * \param wallThickness current wall thickness.
		 * \param maxWallThickness current maximum wall thickness.
		 */
		virtual void createAndProcessIntersectionsIOB(const 
		Ionflux::VolGfx::NodeIntersection& intersection0, bool createNear, bool 
		createFar, Ionflux::VolGfx::VoxelClassID& state, unsigned int& 
		numIntersections0, Ionflux::VolGfx::NodeIntersectionProcessingFlags 
		processingFlags, unsigned int* wallThickness = 0, unsigned int* 
		maxWallThickness = 0);
		
		/** Process inside/outside/boundary data step.
		 *
		 * Process a single step of the inside/outside/boundary data 
		 * iteration. This function is used by setIOBData() and should not be 
		 * called directly.
		 *
		 * \param intersection0 node intersection data.
		 * \param state current state.
		 * \param numIntersections0 current number of intersections.
		 * \param processingFlags processing flags.
		 * \param wallThickness current wall thickness.
		 * \param maxWallThickness current maximum wall thickness.
		 */
		virtual void processIOBStep(const Ionflux::VolGfx::NodeIntersection& 
		intersection0, Ionflux::VolGfx::VoxelClassID& state, unsigned int& 
		numIntersections0, Ionflux::VolGfx::NodeIntersectionProcessingFlags 
		processingFlags, unsigned int* wallThickness = 0, unsigned int* 
		maxWallThickness = 0);
		
		/** Process node intersections (wall thickness).
		 *
		 * Process node intersections from a vector. This function assigns 
		 * wall thickness values to nodes intersected by the ray. The function
		 * will also fix the minimum wall thickness of sequences of filled 
		 * nodes if \c minWallThickness is greater than zero.
		 *
		 * \param intersections0 node intersections.
		 * \param state current state.
		 * \param processingFlags processing flags.
		 * \param wallThickness current wall thickness.
		 * \param maxWallThickness current maximum wall thickness.
		 * \param minWallThickness0 minimum wall thickness.
		 * \param maxNumFillNodes maximum number of nodes to be filled per 
		 * component and direction.
		 * \param insideOnly only fill nodes that are classified as 'inside'.
		 * \param numThinComponents number of components that have a wall 
		 * thickness below the minimum.
		 * \param numNodesFilled number of nodes filled for the current component
		 * and direction.
		 */
		virtual void processIntersectionsWallThickness(const 
		Ionflux::VolGfx::NodeIntersectionVector& intersections0, 
		Ionflux::VolGfx::VoxelClassID& state, 
		Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
		unsigned int& wallThickness, unsigned int& maxWallThickness, unsigned int
		minWallThickness0 = 0, unsigned int maxNumFillNodes = 0, bool insideOnly 
		= true, unsigned int* numThinComponents = 0, unsigned int* numNodesFilled
		= 0);
		
		/** Insert and process node intersections (wall thickness).
		 *
		 * Create new node intersections by inserting a node at the near or 
		 * far intersection point for the specified intersections and process 
		 * the new intersections recursively.
		 *
		 * \param intersection0 node intersection.
		 * \param createNear Create node for near intersection.
		 * \param createFar Create node for far intersection.
		 * \param state current state.
		 * \param processingFlags processing flags.
		 * \param wallThickness current wall thickness.
		 * \param maxWallThickness current maximum wall thickness.
		 * \param minWallThickness0 minimum wall thickness.
		 * \param maxNumFillNodes maximum number of nodes to be filled per 
		 * component and direction.
		 * \param insideOnly only fill nodes that are classified as 'inside'.
		 * \param numThinComponents number of components that have a wall 
		 * thickness below the minimum.
		 * \param numNodesFilled number of nodes filled for the current component
		 * and direction.
		 */
		virtual void createAndProcessIntersectionsWallThickness(const 
		Ionflux::VolGfx::NodeIntersection& intersection0, bool createNear, bool 
		createFar, Ionflux::VolGfx::VoxelClassID& state, 
		Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
		unsigned int& wallThickness, unsigned int& maxWallThickness, unsigned int
		minWallThickness0 = 0, unsigned int maxNumFillNodes = 0, bool insideOnly 
		= true, unsigned int* numThinComponents = 0, unsigned int* numNodesFilled
		= 0);
		
		/** Process wall thickness step.
		 *
		 * Process a single step of the wall thickness iteration. If \c 
		 * minWallThickness is greater than zero, the function will attempt to
		 * fill nodes at the target depth level to increase the wall 
		 * thickness, according to the specified constraints. If \c 
		 * maxNumFillNodes is greater than zero, this value specifies the 
		 * maximum number of nodes filled per component and direction to 
		 * increase the wall thickness. If \c insideOnly is set to \c true, 
		 * only nodes that are classified as 'inside' will be filled. This 
		 * function is used by processWallThickness() and should not be called
		 * directly.
		 *
		 * \param intersection0 node intersection data.
		 * \param state current state.
		 * \param processingFlags processing flags.
		 * \param wallThickness current wall thickness.
		 * \param maxWallThickness current maximum wall thickness.
		 * \param minWallThickness0 minimum wall thickness.
		 * \param maxNumFillNodes maximum number of nodes to be filled per 
		 * component and direction.
		 * \param insideOnly only fill nodes that are classified as 'inside'.
		 * \param numThinComponents number of components that have a wall 
		 * thickness below the minimum.
		 * \param numNodesFilled number of nodes filled for the current component
		 * and direction.
		 */
		virtual void processWallThicknessStep(const 
		Ionflux::VolGfx::NodeIntersection& intersection0, 
		Ionflux::VolGfx::VoxelClassID& state, 
		Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
		unsigned int& wallThickness, unsigned int& maxWallThickness, unsigned int
		minWallThickness0 = 0, unsigned int maxNumFillNodes = 0, bool insideOnly 
		= true, unsigned int* numThinComponents = 0, unsigned int* numNodesFilled
		= 0);
		
		/** Process node intersections (boundary).
		 *
		 * Process node intersections from a vector.
		 *
		 * \param intersections0 node intersections.
		 * \param state current state.
		 * \param processingFlags processing flags.
		 * \param colorIndex color index.
		 */
		virtual void processIntersectionsBoundary(const 
		Ionflux::VolGfx::NodeIntersectionVector& intersections0, 
		Ionflux::VolGfx::VoxelClassID& state, 
		Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
		Ionflux::VolGfx::ColorIndex* colorIndex = 0);
		
		/** Insert and process node intersections (boundary).
		 *
		 * Create new node intersections by inserting a node at the near or 
		 * far intersection point for the specified intersections and process 
		 * the new intersections recursively.
		 *
		 * \param intersection0 node intersection.
		 * \param createNear Create node for near intersection.
		 * \param createFar Create node for far intersection.
		 * \param state current state.
		 * \param processingFlags processing flags.
		 * \param colorIndex color index.
		 */
		virtual void createAndProcessIntersectionsBoundary(const 
		Ionflux::VolGfx::NodeIntersection& intersection0, bool createNear, bool 
		createFar, Ionflux::VolGfx::VoxelClassID& state, 
		Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
		Ionflux::VolGfx::ColorIndex* colorIndex = 0);
		
		/** Process boundary step.
		 *
		 * Process a single step of the boundary iteration.
		 *
		 * \param intersection0 node intersection data.
		 * \param state current state.
		 * \param processingFlags processing flags.
		 * \param colorIndex color index.
		 */
		virtual void processBoundaryStep(const Ionflux::VolGfx::NodeIntersection&
		intersection0, Ionflux::VolGfx::VoxelClassID& state, 
		Ionflux::VolGfx::NodeIntersectionProcessingFlags processingFlags, 
		Ionflux::VolGfx::ColorIndex* colorIndex = 0);
		
		/** Set ray axis.
		 *
		 * Set new value of ray axis.
		 *
		 * \param newRayAxis New value of ray axis.
		 */
		virtual void setRayAxis(Ionflux::GeoUtils::AxisID newRayAxis);
		
	public:
		/// Class information instance.
		static const NodeIntersectionProcessorClassInfo nodeIntersectionProcessorClassInfo;
		/// Class information.
		static const Ionflux::ObjectBase::IFClassInfo* CLASS_INFO;
		
		/** Constructor.
		 *
		 * Construct new NodeIntersectionProcessor object.
		 */
		NodeIntersectionProcessor();
		
		/** Constructor.
		 *
		 * Construct new NodeIntersectionProcessor object.
		 *
		 * \param other Other object.
		 */
		NodeIntersectionProcessor(const Ionflux::VolGfx::NodeIntersectionProcessor& other);
		
		/** Constructor.
		 *
		 * Construct new NodeIntersectionProcessor object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initHitDataType node data type for ray hits.
		 * \param initVoxelClassHit voxel class for ray hits.
		 * \param initLeafStatus leaf status.
		 * \param initRay Ray.
		 * \param initEnableBoundaryData enable boundary data flag.
		 * \param initTargetDepth target depth.
		 * \param initFillNewIntersections fill nodes that are created for new 
		 * intersections.
		 * \param initPruneEmptyNewIntersections prune empty nodes that are 
		 * created for new intersections.
		 * \param initEnableIOB Enable inside/outside/boundary classification.
		 * \param initEnableRayStabbing mark nodes with zero intersections as 
		 * outside (ray-stabbing).
		 * \param initEnableWallThickness enable wall thickness calculation.
		 * \param initVoxelClassFilled voxel class for 'filled' voxels.
		 * \param initVoxelClassInside voxel class for 'inside' voxels.
		 * \param initVoxelClassOutside voxel class for 'outside' voxels.
		 * \param initVoxelClassBoundary voxel class for 'boundary' voxels.
		 * \param initTolerance tolerance for comparisons.
		 * \param initMinWallThickness Minimum wall thickness.
		 * \param initFillInsideOnly Fill 'inside' nodes only when fixing the 
		 * minimum wall thickness.
		 * \param initMaxNumWallThicknessPasses Maximum number of passes for 
		 * fixing wall thickness.
		 */
		NodeIntersectionProcessor(Ionflux::VolGfx::Context* initContext, 
		Ionflux::VolGfx::NodeDataType initHitDataType = Node::DATA_TYPE_UNKNOWN, 
		Ionflux::VolGfx::VoxelClassID initVoxelClassHit = VOXEL_CLASS_UNDEFINED, 
		Ionflux::VolGfx::LeafStatusID initLeafStatus = NODE_LEAF, 
		Ionflux::GeoUtils::Line3* initRay = 0, bool initEnableBoundaryData = 
		false, int initTargetDepth = DEPTH_UNSPECIFIED, bool 
		initFillNewIntersections = true, bool initPruneEmptyNewIntersections = 
		false, bool initEnableIOB = true, bool initEnableRayStabbing = false, 
		bool initEnableWallThickness = false, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassFilled = VOXEL_CLASS_FILLED, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassInside = VOXEL_CLASS_INSIDE, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassOutside = VOXEL_CLASS_OUTSIDE, 
		Ionflux::VolGfx::VoxelClassID initVoxelClassBoundary = 
		VOXEL_CLASS_BOUNDARY, double initTolerance = DEFAULT_TOLERANCE, unsigned 
		int initMinWallThickness = 0, bool initFillInsideOnly = true, unsigned 
		int initMaxNumWallThicknessPasses = 0);
		
		/** Destructor.
		 *
		 * Destruct NodeIntersectionProcessor object.
		 */
		virtual ~NodeIntersectionProcessor();
		
		/** Clear.
		 *
		 * Clear state of the node intersection processor.
		 */
		virtual void clear();
		
		/** Begin processing.
		 *
		 * Start processing of a new batch of intersections (e.g. for a ray). 
		 * By default, this clears the current set of intersections.
		 */
		virtual void begin();
		
		/** Finish processing.
		 *
		 * Finish processing of a batch of intersections (e.g. for a ray). By 
		 * default, this sets the inside/outside/boundary data on the 
		 * intersections. If \c minWallThickness is not equal to zero, this 
		 * function will also invoke the wall thickness calculation and fixing
		 * stage.
		 */
		virtual void finish();
		
		/** Process intersection.
		 *
		 * Apply the filter to a node implementation. This should be 
		 * overridden by derived classes.
		 *
		 * \param newIntersection Node intersection.
		 * \param userData User data.
		 *
		 * \return result.
		 */
		virtual Ionflux::VolGfx::NodeProcessingResultID processIntersection(const
		Ionflux::VolGfx::NodeIntersection& newIntersection, void* userData = 0);
		
		/** Set inside/outside/boundary data.
		 *
		 * Set inside/outside/boundary data for the current set of 
		 * intersections. This calculates the number of surface intersections 
		 * each node in the intersection set and updates the interection and 
		 * vote counts accordingly. A data record of type VoxelDataIOB will be
		 * attached to each node contained in the intersection set, unless it 
		 * already has data of that type attached. Existing voxel classes that
		 * are attached to the nodes will be merged into to the new data 
		 * records.
		 * 
		 * See Nooruddin, Turk (2003) "Simplification and repair of polygonal 
		 * models using volumetric techniques" for details on the 
		 * inside/outside calculation.
		 *
		 * \param processingFlags processing flags.
		 */
		virtual void setIOBData(Ionflux::VolGfx::NodeIntersectionProcessingFlags*
		processingFlags = 0);
		
		/** Process wall thickness.
		 *
		 * Assign wall thickness values to nodes intersected by the ray. The 
		 * function will also fix the minimum wall thickness of sequences of 
		 * filled nodes if \c minWallThickness is greater than zero.
		 *
		 * \param processingFlags processing flags.
		 */
		virtual void 
		processWallThickness(Ionflux::VolGfx::NodeIntersectionProcessingFlags* 
		processingFlags = 0);
		
		/** Process boundary.
		 *
		 * Mark boundary nodes intersected by the ray.
		 *
		 * \param processingFlags processing flags.
		 */
		virtual void 
		processBoundary(Ionflux::VolGfx::NodeIntersectionProcessingFlags* 
		processingFlags = 0);
		
		/** Create node intersections.
		 *
		 * Create node intersections at the target depth level for the 
		 * specified node intersection.
		 *
		 * \param intersection0 Node intersection.
		 * \param newIntersections Where to store the node intersections for the 
		 * subdivided node.
		 * \param createNear Create node for near intersection.
		 * \param createFar Create node for far intersection.
		 *
		 * \return Number of new intersections created.
		 */
		virtual unsigned int createIntersections(const 
		Ionflux::VolGfx::NodeIntersection& intersection0, 
		Ionflux::VolGfx::NodeIntersectionVector& newIntersections, bool 
		createNear = false, bool createFar = false);
		
		/** Get string representation of value.
		 *
		 * Get a string representation of the value of the object.
		 *
		 * \return String representation.
		 */
		virtual std::string getValueString() const;
		
		/** Get node implementation inside/outside/boundary data record.
		 *
		 * Get the inside/outside/boundary (IOB) data record for the specified
		 * node intersection. If the node implementation does not have an IOB 
		 * record and it cannot be created, an exception will be thrown.
		 *
		 * \param intersection0 Node intersection.
		 *
		 * \return Inside/outside/boundary data record.
		 */
		static Ionflux::VolGfx::VoxelDataIOB* getIOBData(const 
		Ionflux::VolGfx::NodeIntersection& intersection0);
		
		/** Assignment operator.
		 *
		 * Assign an object.
		 *
		 * \param other Other object.
		 *
		 * \return The object itself.
		 */
		virtual Ionflux::VolGfx::NodeIntersectionProcessor& operator=(const 
		Ionflux::VolGfx::NodeIntersectionProcessor& other);
		
		/** Copy.
		 *
		 * Create a copy of the object.
		 *
		 * \return Newly allocated copy of the object.
		 */
		virtual Ionflux::VolGfx::NodeIntersectionProcessor* copy() const;
		
		/** Upcast.
		 *
		 * Cast an IFObject to the most specific type.
		 *
		 * \param other Other object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		static Ionflux::VolGfx::NodeIntersectionProcessor* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		
		/** Create instance.
		 *
		 * Create a new instance of the class. If the optional parent object 
		 * is specified, a local reference for the new object will be added 
		 * to the parent object.
		 *
		 * \param parentObject Parent object.
		 *
		 * \return Pointer to the new instance.
		 */
		static Ionflux::VolGfx::NodeIntersectionProcessor* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
        
		/** Create instance.
		 *
		 * Create a new NodeIntersectionProcessor object.
		 *
		 * \param initContext Voxel tree context.
		 * \param initHitDataType node data type for ray hits.
		 * \param initVoxelClassHit voxel class for ray hits.
		 * \param initLeafStatus leaf status.
		 * \param initRay Ray.
		 * \param initEnableBoundaryData enable boundary data flag.
		 * \param initTargetDepth target depth.
		 * \param initFillNewIntersections fill nodes that are created for new 
		 * intersections.
		 * \param initPruneEmptyNewIntersections prune empty nodes that are 
		 * created for new intersections.
		 * \param initEnableIOB Enable inside/outside/boundary classification.
		 * \param initEnableRayStabbing mark nodes with zero intersections as 
		 * outside (ray-stabbing).
		 * \param initEnableWallThickness enable wall thickness calculation.
		 * \param initVoxelClassFilled voxel class for 'filled' voxels.
		 * \param initVoxelClassInside voxel class for 'inside' voxels.
		 * \param initVoxelClassOutside voxel class for 'outside' voxels.
		 * \param initVoxelClassBoundary voxel class for 'boundary' voxels.
		 * \param initTolerance tolerance for comparisons.
		 * \param initMinWallThickness Minimum wall thickness.
		 * \param initFillInsideOnly Fill 'inside' nodes only when fixing the 
		 * minimum wall thickness.
		 * \param initMaxNumWallThicknessPasses Maximum number of passes for 
		 * fixing wall thickness.
		 * \param parentObject Parent object.
		 */
		static Ionflux::VolGfx::NodeIntersectionProcessor* 
		create(Ionflux::VolGfx::Context* initContext, 
		Ionflux::VolGfx::NodeDataType initHitDataType = Node::DATA_TYPE_UNKNOWN, 
		Ionflux::VolGfx::VoxelClassID initVoxelClassHit = VOXEL_CLASS_UNDEFINED, 
		Ionflux::VolGfx::LeafStatusID initLeafStatus = NODE_LEAF, 
		Ionflux::GeoUtils::Line3* initRay = 0, bool initEnableBoundaryData = 
		false, int initTargetDepth = DEPTH_UNSPECIFIED, bool 
		initFillNewIntersections = true, bool initPruneEmptyNewIntersections = 
		false, bool initEnableIOB = true, bool initEnableRayStabbing = false, 
		bool initEnableWallThickness = false, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassFilled = VOXEL_CLASS_FILLED, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassInside = VOXEL_CLASS_INSIDE, Ionflux::VolGfx::VoxelClassID 
		initVoxelClassOutside = VOXEL_CLASS_OUTSIDE, 
		Ionflux::VolGfx::VoxelClassID initVoxelClassBoundary = 
		VOXEL_CLASS_BOUNDARY, double initTolerance = DEFAULT_TOLERANCE, unsigned 
		int initMinWallThickness = 0, bool initFillInsideOnly = true, unsigned 
		int initMaxNumWallThicknessPasses = 0, Ionflux::ObjectBase::IFObject* 
		parentObject = 0);
		
		/** Get allocated size in memory.
		 *
		 * Get the allocated size in memory for the object.
		 *
		 * \return The more specific object, or 0 if the cast failed.
		 */
		virtual unsigned int getMemSize() const;
		
		/** Get number of intersections.
		 *
		 * \return Number of intersections.
		 */
		virtual unsigned int getNumIntersections() const;
		
		/** Get intersection.
		 *
		 * Get the intersection at the specified index.
		 *
		 * \param elementIndex Element index.
		 *
		 * \return Intersection at specified index.
		 */
		virtual Ionflux::VolGfx::NodeIntersection getIntersection(unsigned int 
		elementIndex = 0) const;
		
		/** Find intersection.
		 *
		 * Find the specified occurence of a intersection.
		 *
		 * \param needle Intersection to be found.
		 * \param occurence Number of the occurence to be found.
		 *
		 * \return Index of the intersection, or -1 if the intersection cannot be
		 * found.
		 */
		virtual int findIntersection(const Ionflux::VolGfx::NodeIntersection& 
		needle, unsigned int occurence = 1) const;
        
		/** Get vector of intersections.
		 *
		 * \return vector of intersections.
		 */
		virtual std::vector<Ionflux::VolGfx::NodeIntersection>& 
		getIntersections();
		
		/** Add intersection.
		 *
		 * Add a intersection.
		 *
		 * \param addElement Intersection to be added.
		 */
		virtual void addIntersection(const Ionflux::VolGfx::NodeIntersection& 
		addElement);
		
		/** Create intersection.
		 *
		 * Create a new intersection which is managed by the intersection set.
		 *
		 * \return New intersection.
		 */
		virtual const Ionflux::VolGfx::NodeIntersection& addIntersection();
		
		/** Add intersections.
		 *
		 * Add intersections from a intersection vector.
		 *
		 * \param newIntersections intersections.
		 */
		virtual void addIntersections(const 
		std::vector<Ionflux::VolGfx::NodeIntersection>& newIntersections);
		
		/** Add intersections.
		 *
		 * Add intersections from a intersection set.
		 *
		 * \param newIntersections intersections.
		 */
		virtual void addIntersections(Ionflux::VolGfx::NodeIntersectionProcessor*
		newIntersections);
		
		/** Remove intersection.
		 *
		 * Remove a intersection.
		 *
		 * \param removeElement Intersection to be removed.
		 */
		virtual void removeIntersection(const Ionflux::VolGfx::NodeIntersection& 
		removeElement);
		
		/** Remove intersection.
		 *
		 * Remove a intersection.
		 *
		 * \param removeIndex Intersection to be removed.
		 */
		virtual void removeIntersectionIndex(unsigned int removeIndex);
		
		/** Clear intersections.
		 *
		 * Clear all intersections.
		 */
		virtual void clearIntersections();
		
		/** Get voxel tree context.
		 *
		 * \return Current value of voxel tree context.
		 */
		virtual Ionflux::VolGfx::Context* getContext() const;
		
		/** Set voxel tree context.
		 *
		 * Set new value of voxel tree context.
		 *
		 * \param newContext New value of voxel tree context.
		 */
		virtual void setContext(Ionflux::VolGfx::Context* newContext);
		
		/** Get node data type for ray hits.
		 *
		 * \return Current value of node data type for ray hits.
		 */
		virtual Ionflux::VolGfx::NodeDataType getHitDataType() const;
		
		/** Set node data type for ray hits.
		 *
		 * Set new value of node data type for ray hits.
		 *
		 * \param newHitDataType New value of node data type for ray hits.
		 */
		virtual void setHitDataType(Ionflux::VolGfx::NodeDataType 
		newHitDataType);
		
		/** Get voxel class mask for ray hits.
		 *
		 * \return Current value of voxel class mask for ray hits.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClassHit() const;
		
		/** Set voxel class mask for ray hits.
		 *
		 * Set new value of voxel class mask for ray hits.
		 *
		 * \param newVoxelClassHit New value of voxel class mask for ray hits.
		 */
		virtual void setVoxelClassHit(Ionflux::VolGfx::VoxelClassID 
		newVoxelClassHit);
		
		/** Get leaf status flag.
		 *
		 * \return Current value of leaf status flag.
		 */
		virtual Ionflux::VolGfx::LeafStatusID getLeafStatus() const;
		
		/** Set leaf status flag.
		 *
		 * Set new value of leaf status flag.
		 *
		 * \param newLeafStatus New value of leaf status flag.
		 */
		virtual void setLeafStatus(Ionflux::VolGfx::LeafStatusID newLeafStatus);
		
		/** Get ray.
		 *
		 * \return Current value of ray.
		 */
		virtual Ionflux::GeoUtils::Line3* getRay() const;
		
		/** Set ray.
		 *
		 * Set new value of ray.
		 *
		 * \param newRay New value of ray.
		 */
		virtual void setRay(Ionflux::GeoUtils::Line3* newRay);
		
		/** Get boundary data enable flag.
		 *
		 * \return Current value of boundary data enable flag.
		 */
		virtual bool getEnableBoundaryData() const;
		
		/** Set boundary data enable flag.
		 *
		 * Set new value of boundary data enable flag.
		 *
		 * \param newEnableBoundaryData New value of boundary data enable flag.
		 */
		virtual void setEnableBoundaryData(bool newEnableBoundaryData);
		
		/** Get target depth for inserting node intersections.
		 *
		 * \return Current value of target depth for inserting node 
		 * intersections.
		 */
		virtual int getTargetDepth() const;
		
		/** Set target depth for inserting node intersections.
		 *
		 * Set new value of target depth for inserting node intersections.
		 *
		 * \param newTargetDepth New value of target depth for inserting node 
		 * intersections.
		 */
		virtual void setTargetDepth(int newTargetDepth);
		
		/** Get fill nodes that are created for new intersections.
		 *
		 * \return Current value of fill nodes that are created for new 
		 * intersections.
		 */
		virtual bool getFillNewIntersections() const;
		
		/** Set fill nodes that are created for new intersections.
		 *
		 * Set new value of fill nodes that are created for new intersections.
		 *
		 * \param newFillNewIntersections New value of fill nodes that are 
		 * created for new intersections.
		 */
		virtual void setFillNewIntersections(bool newFillNewIntersections);
		
		/** Get prune empty nodes that are created for new intersections.
		 *
		 * \return Current value of prune empty nodes that are created for new 
		 * intersections.
		 */
		virtual bool getPruneEmptyNewIntersections() const;
		
		/** Set prune empty nodes that are created for new intersections.
		 *
		 * Set new value of prune empty nodes that are created for new intersections.
		 *
		 * \param newPruneEmptyNewIntersections New value of prune empty nodes 
		 * that are created for new intersections.
		 */
		virtual void setPruneEmptyNewIntersections(bool 
		newPruneEmptyNewIntersections);
		
		/** Get enable inside/outside/boundary classification.
		 *
		 * \return Current value of enable inside/outside/boundary 
		 * classification.
		 */
		virtual bool getEnableIOB() const;
		
		/** Set enable inside/outside/boundary classification.
		 *
		 * Set new value of enable inside/outside/boundary classification.
		 *
		 * \param newEnableIOB New value of enable inside/outside/boundary 
		 * classification.
		 */
		virtual void setEnableIOB(bool newEnableIOB);
		
		/** Get mark nodes with zero intersections as outside (ray-stabbing).
		 *
		 * \return Current value of mark nodes with zero intersections as outside
		 * (ray-stabbing).
		 */
		virtual bool getEnableRayStabbing() const;
		
		/** Set mark nodes with zero intersections as outside (ray-stabbing).
		 *
		 * Set new value of mark nodes with zero intersections as outside (ray-stabbing).
		 *
		 * \param newEnableRayStabbing New value of mark nodes with zero 
		 * intersections as outside (ray-stabbing).
		 */
		virtual void setEnableRayStabbing(bool newEnableRayStabbing);
		
		/** Get enable wall thickness calculation.
		 *
		 * \return Current value of enable wall thickness calculation.
		 */
		virtual bool getEnableWallThickness() const;
		
		/** Set enable wall thickness calculation.
		 *
		 * Set new value of enable wall thickness calculation.
		 *
		 * \param newEnableWallThickness New value of enable wall thickness 
		 * calculation.
		 */
		virtual void setEnableWallThickness(bool newEnableWallThickness);
		
		/** Get voxel class for 'filled' voxels.
		 *
		 * \return Current value of voxel class for 'filled' voxels.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClassFilled() const;
		
		/** Set voxel class for 'filled' voxels.
		 *
		 * Set new value of voxel class for 'filled' voxels.
		 *
		 * \param newVoxelClassFilled New value of voxel class for 'filled' 
		 * voxels.
		 */
		virtual void setVoxelClassFilled(Ionflux::VolGfx::VoxelClassID 
		newVoxelClassFilled);
		
		/** Get voxel class for 'inside' voxels.
		 *
		 * \return Current value of voxel class for 'inside' voxels.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClassInside() const;
		
		/** Set voxel class for 'inside' voxels.
		 *
		 * Set new value of voxel class for 'inside' voxels.
		 *
		 * \param newVoxelClassInside New value of voxel class for 'inside' 
		 * voxels.
		 */
		virtual void setVoxelClassInside(Ionflux::VolGfx::VoxelClassID 
		newVoxelClassInside);
		
		/** Get voxel class for 'outside' voxels.
		 *
		 * \return Current value of voxel class for 'outside' voxels.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClassOutside() const;
		
		/** Set voxel class for 'outside' voxels.
		 *
		 * Set new value of voxel class for 'outside' voxels.
		 *
		 * \param newVoxelClassOutside New value of voxel class for 'outside' 
		 * voxels.
		 */
		virtual void setVoxelClassOutside(Ionflux::VolGfx::VoxelClassID 
		newVoxelClassOutside);
		
		/** Get voxel class for 'boundary' voxels.
		 *
		 * \return Current value of voxel class for 'boundary' voxels.
		 */
		virtual Ionflux::VolGfx::VoxelClassID getVoxelClassBoundary() const;
		
		/** Set voxel class for 'boundary' voxels.
		 *
		 * Set new value of voxel class for 'boundary' voxels.
		 *
		 * \param newVoxelClassBoundary New value of voxel class for 'boundary' 
		 * voxels.
		 */
		virtual void setVoxelClassBoundary(Ionflux::VolGfx::VoxelClassID 
		newVoxelClassBoundary);
		
		/** Get tolerance for comparisons.
		 *
		 * \return Current value of tolerance for comparisons.
		 */
		virtual double getTolerance() const;
		
		/** Set tolerance for comparisons.
		 *
		 * Set new value of tolerance for comparisons.
		 *
		 * \param newTolerance New value of tolerance for comparisons.
		 */
		virtual void setTolerance(double newTolerance);
		
		/** Get ray axis.
		 *
		 * \return Current value of ray axis.
		 */
		virtual Ionflux::GeoUtils::AxisID getRayAxis() const;
		
		/** Get minimum wall thickness.
		 *
		 * \return Current value of minimum wall thickness.
		 */
		virtual unsigned int getMinWallThickness() const;
		
		/** Set minimum wall thickness.
		 *
		 * Set new value of minimum wall thickness.
		 *
		 * \param newMinWallThickness New value of minimum wall thickness.
		 */
		virtual void setMinWallThickness(unsigned int newMinWallThickness);
		
		/** Get fill 'inside' nodes only when fixing the minimum wall thickness.
		 *
		 * \return Current value of fill 'inside' nodes only when fixing the 
		 * minimum wall thickness.
		 */
		virtual bool getFillInsideOnly() const;
		
		/** Set fill 'inside' nodes only when fixing the minimum wall thickness.
		 *
		 * Set new value of fill 'inside' nodes only when fixing the minimum wall thickness.
		 *
		 * \param newFillInsideOnly New value of fill 'inside' nodes only when 
		 * fixing the minimum wall thickness.
		 */
		virtual void setFillInsideOnly(bool newFillInsideOnly);
		
		/** Get maximum number of passes for fixing wall thickness.
		 *
		 * \return Current value of maximum number of passes for fixing wall 
		 * thickness.
		 */
		virtual unsigned int getMaxNumWallThicknessPasses() const;
		
		/** Set maximum number of passes for fixing wall thickness.
		 *
		 * Set new value of maximum number of passes for fixing wall thickness.
		 *
		 * \param newMaxNumWallThicknessPasses New value of maximum number of 
		 * passes for fixing wall thickness.
		 */
		virtual void setMaxNumWallThicknessPasses(unsigned int 
		newMaxNumWallThicknessPasses);
};

}

}

/** \file NodeIntersectionProcessor.hpp
 * \brief Node intersection processor (header).
 */
#endif
