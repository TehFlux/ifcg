/**
 * ==========================================================================
 * Copyright © 2009 Jörn P. Meier
 * All rights reserved.
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * test01.js          Geometry utilities test 01.
 * ==========================================================================
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 *  - Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of the copyright holders nor the names of the 
 *    contributors may be used to endorse or promote products derived from 
 *    this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * ==========================================================================
 */

/**
 * Hexagon.
 *
 * a  -- Base length of hexagon.
 */
Hexagon = Class.create(GeoUtils.Polygon2, {
    
    // Constructor.
    initialize: function($super, a, vertices, edges)
    {
        $super.call(this, vertices, edges);
        if (typeof(a) == 'undefined')
            this.a = 1.0;
        else
            this.a = a;
        this.createVertices();
        this.createEdges();
    }, 
    
    createVertices: function()
    {
        var c = this.a / 4.;
        var b = c * Math.tan(Math.PI / 3.);
        this.vertices = [
            new GeoUtils.Vertex2(-this.a / 4., -b), 
            new GeoUtils.Vertex2(this.a / 4., -b), 
            new GeoUtils.Vertex2(this.a / 2., 0.), 
            new GeoUtils.Vertex2(this.a / 4., b), 
            new GeoUtils.Vertex2(-this.a / 4., b), 
            new GeoUtils.Vertex2(-this.a / 2., 0.)
        ];
    },
    
    toString: function()
    {
        return "Hexagon[" + this.a + ", [" + this.vertices + "], [" 
            + this.edges + "]]";
    }
});

/**
 * Square (3D).
 *
 * a  -- Base length of square.
 */
Square3 = Class.create(GeoUtils.Polygon3, {
    
    // Constructor.
    initialize: function($super, a, vertices, edges)
    {
        $super.call(this, vertices, edges);
        this.a = GeoUtils.defaultArg(a, 1.0);
        this.createVertices();
        this.createEdges();
    }, 
    
    createVertices: function()
    {
        var c = this.a / 2.;
        this.vertices = [
            new GeoUtils.Vertex3(-c, c, 0.), 
            new GeoUtils.Vertex3(-c, -c, 0.), 
            new GeoUtils.Vertex3(c, -c, 0.), 
            new GeoUtils.Vertex3(c, c, 0.)
        ];
    },
    
    toString: function()
    {
        return "Square3[" + this.a + ", [" + this.vertices + "], [" 
            + this.edges + "]]";
    }
});

// Grid widget.
Grid = Class.create({
    
    /**
     * Constructor.
     *
     * x           -- position (X).
     * y           -- position (Y).
     * width       -- width.
     * height      -- height.
     * spacingX    -- Grid spacing (X).
     * spacingY    -- Grid spacing (Y).
     * offsetX     -- Grid offset (X).
     * offsetY     -- Grid offset (Y).
     * lineColor   -- Grid line color.
     * showBorder  -- Draw a border around the grid.
     * title       -- Title to be shown for the grid.
     */
    initialize: function(x, y, width, height, spacingX, spacingY, offsetX, 
        offsetY, lineColor, showBorder, title)
    {
        this.x = GeoUtils.defaultArg(x, 0);
        this.y = GeoUtils.defaultArg(y, 0);
        this.width = GeoUtils.defaultArg(width, 100);
        this.height = GeoUtils.defaultArg(height, 100);
        this.spacingX = GeoUtils.defaultArg(spacingX, 10);
        this.spacingY = GeoUtils.defaultArg(spacingY, 10);
        this.offsetX = GeoUtils.defaultArg(offsetX, 0);
        this.offsetY = GeoUtils.defaultArg(offsetY, 0);
        this.lineColor = GeoUtils.defaultArg(lineColor, '#707070');
        this.showBorder = GeoUtils.defaultArg(showBorder, false);
        this.title = GeoUtils.defaultArg(title, null);
        
        this.setupUI();
    },
    
    // Create the grid lines.
    createGridLines: function()
    {
        var x = this.offsetX + this.spacingX;
        var linesX = [];
        while (x < this.width)
        {
            var l = new Element('div');
            l.setStyle({
                position: 'absolute', 
                left: '' + x + 'px', 
                top: '0px', 
                width: '0px', 
                height: '' + this.getHeight() + 'px', 
                borderLeft: '1px solid ' + this.lineColor
            });
            linesX.push(l);
            x += this.spacingX;
        }
        var y = this.offsetY + this.spacingY;
        var linesY = [];
        while (y < this.width)
        {
            var l = new Element('div');
            l.setStyle({
                position: 'absolute', 
                left: '0px', 
                top: '' + y + 'px', 
                width: '' + this.getWidth() + 'px', 
                height: '0px', 
                borderTop: '1px solid ' + this.lineColor
            });
            linesY.push(l);
            y += this.spacingY;
        }
        return [ linesX, linesY ];
    },
    
    // Setup the user interface.
    setupUI: function()
    {
        this.viewport = new Element('div');
        this.viewport.setStyle({
            position: 'absolute', 
            left: this.getX() + 'px', 
            top: this.getY() + 'px', 
            width: '' + this.getWidth() + 'px', 
            height: '' + this.getHeight() + 'px', 
        });
        if (this.showBorder)
            this.viewport.setStyle({
                border: '1px solid ' + this.lineColor
            });
        var lines = this.createGridLines();
        for (var i = 0; i < lines[0].length; i++)
        {
            var l = lines[0][i];
            this.viewport.insert(l);
        }
        for (var i = 0; i < lines[1].length; i++)
        {
            var l = lines[1][i];
            this.viewport.insert(l);
        }
        if (this.title != null)
        {
            var titleBox = new Element('div');
            titleBox.setStyle({
                position: 'absolute', 
                left: '5px', 
                top: '2px', 
                fontSize: '80%'
            });
            titleBox.insert(this.title);
            this.viewport.insert(titleBox);
        }
    },
    
    // Get viewport element.
    getViewport: function()
    {
        return this.viewport;
    },
    
    /**
     * Set grid position.
     *
     * x  -- X position.
     * y  -- Y position.
     *
     * Set the display offset of the grid viewport relative to its 
     * container.
     */
    setPosition: function(x, y)
    {
        if (GeoUtils.eq2([x0, y0], [this.x, this.y]))
            return;
        this.viewport.setStyle({
            left: '' + x0 + 'px', 
            top: '' + y0 + 'px'
        });
        this.x = x0;
        this.y = y0;
    },
    
    // Get grid position (X).
    getX: function()
    {
        return this.x;
    },
    
    // Get grid position (Y).
    getY: function()
    {
        return this.y;
    },
    
    // Get grid width.
    getWidth: function()
    {
        return this.width;
    },
    
    // Get grid height.
    getHeight: function()
    {
        return this.height;
    },
    
    // Show the grid.
    show: function()
    {
        this.viewport.show();
    },
    
    // Hide the grid.
    hide: function()
    {
        this.viewport.hide();
    }
    
});

// Box (for use with Grid3).
Box3 = Class.create(GeoUtils.Identifiable, {
    
    /**
     * Constructor.
     *
     * center      -- center (vector).
     * radius      -- radius (vector).
     * lineColor   -- Line color.
     * fillColor   -- Fill color.
     */
    initialize: function($super, center, radius, lineColor, fillColor)
    {
        $super.call(this);
        this.center = GeoUtils.defaultArg(center, [0., 0., 0.]);
        this.radius = GeoUtils.defaultArg(radius, [1., 1., 1.]);
        this.lineColor = GeoUtils.defaultArg(lineColor, '#0000ff');
        this.fillColor = GeoUtils.defaultArg(fillColor, null);
        
        // Rendered center.
        this.rCenter = new GeoUtils.Vertex3();
        // Rendered radius.
        this.rRadius = new GeoUtils.Vertex3();
        // Current viewport transform matrix.
        this.transform = null;
        // Level (used for constructing hierarchies).
        this.level = 0;
        // Parent (used for constructing hierarchies).
        this.parent = 0;
        // Children (used for constructing hierarchies).
        this.children = new GeoUtils.Set();
        
        this.setupUI();
    },
    
    // Setup the user interface.
    setupUI: function()
    {
        var x = -Math.floor(0.5 * this.size) - 1;
        var y = -Math.floor(0.5 * this.size) - 1;
        this.viewportTop = new Element('div');
        this.viewportTop.setStyle({
            position: 'absolute', 
            left: x + 'px', 
            top: y + 'px', 
            width: '1px', 
            height: '1px', 
            border: '1px solid ' + this.lineColor
        });
        if (this.fillColor != null)
            this.viewportTop.setStyle({
                backgroundColor: this.backgroundColor
            });
        this.viewportFront = new Element('div');
        this.viewportFront.setStyle({
            position: 'absolute', 
            left: x + 'px', 
            top: y + 'px', 
            width: '1px', 
            height: '1px', 
            border: '1px solid ' + this.lineColor
        });
        if (this.fillColor != null)
            this.viewportFront.setStyle({
                backgroundColor: this.backgroundColor
            });
        this.viewportRight = new Element('div');
        this.viewportRight.setStyle({
            position: 'absolute', 
            left: x + 'px', 
            top: y + 'px', 
            width: '1px', 
            height: '1px', 
            border: '1px solid ' + this.lineColor
        });
        if (this.fillColor != null)
            this.viewportRight.setStyle({
                backgroundColor: this.backgroundColor
            });
    },
    
    // Get viewport element (top).
    getViewportTop: function()
    {
        return this.viewportTop;
    },
    
    // Get viewport element (top).
    getViewportFront: function()
    {
        return this.viewportFront;
    },
    
    // Get viewport element (top).
    getViewportRight: function()
    {
        return this.viewportRight;
    },
    
    /**
     * Set position.
     * 
     * transform  -- Viewport transform.
     * width      -- Viewport width.
     * height     -- Viewport height.
     * offset     -- Viewport offset.
     * 
     * Set the display offset of the box viewports relative to its 
     * container, using the specified viewport transform. If an optional 
     * viewport height is specified, this will be used to invert the viewport 
     * Y-axis to reflect a right-handed cartesian coordinate system.
     */
    setPosition: function(transform, width, height, offset)
    {
        var w0 = GeoUtils.defaultArg(width, 0);
        var h0 = GeoUtils.defaultArg(height, 0);
        var offset0 = GeoUtils.defaultArg(offset, [0, 0, 0]);
        this.transform = transform;
        // Handle radius vector.
        var v0 = new GeoUtils.Vertex3(this.radius[0], this.radius[1], 
            this.radius[2]);
        this.rRadius = v0.transform(this.transform);
        var rBoxSize = [ 
            Math.round(2 * this.rRadius.x) - 1, 
            Math.round(2 * this.rRadius.y) - 1, 
            Math.round(2 * this.rRadius.z) - 1
        ];
        this.viewportTop.setStyle({
            width: '' + rBoxSize[0] + 'px', 
            height: '' + rBoxSize[1] + 'px'
        });
        this.viewportFront.setStyle({
            width: '' + rBoxSize[0] + 'px', 
            height: '' + rBoxSize[2] + 'px'
        });
        this.viewportRight.setStyle({
            width: '' + rBoxSize[1] + 'px', 
            height: '' + rBoxSize[2] + 'px'
        });
        /* <---- DEBUG ----- //
        GeoUtils.debug('rBoxSize = ' + GeoUtils.vectorToString(rBoxSize), 
            'Box3.setPosition');
        // <---- DEBUG ----- */
        // Handle the box center.
        var v1 = new GeoUtils.Vertex3(this.center[0] - offset0[0], 
            this.center[1] - offset0[1], this.center[2] - offset0[2]);
        this.rCenter = v1.transform(this.transform);
        var x = 0;
        var y = 0;
        x = -Math.floor(this.rRadius.x) + Math.round(this.rCenter.x) 
            + Math.round(0.5 * w0);
        if (h0 == 0)
            y = -Math.floor(this.rRadius.y) + Math.round(this.rCenter.y) 
                + Math.round(0.5 * h0);
        else
            y = -Math.floor(this.rRadius.y) + height 
                - Math.round(this.rCenter.y) - Math.round(0.5 * h0);
        this.viewportTop.setStyle({
            left: '' + x + 'px', 
            top: '' + y + 'px'
        });
        /* <---- DEBUG ----- //
        GeoUtils.debug('Viewport position (top): x = ' + x + ', y = ' + y, 
            'Point.setPosition');
        // <---- DEBUG ----- */
        x = -Math.floor(this.rRadius.x) + Math.round(this.rCenter.x) 
            + Math.round(0.5 * w0);
        if (h0 == 0)
            y = -Math.floor(this.rRadius.z) + Math.round(this.rCenter.z) 
                + Math.round(0.5 * h0);
        else
            y = -Math.floor(this.rRadius.z) + height 
                - Math.round(this.rCenter.z) - Math.round(0.5 * h0);
        this.viewportFront.setStyle({
            left: '' + x + 'px', 
            top: '' + y + 'px'
        });
        /* <---- DEBUG ----- //
        GeoUtils.debug('Viewport position (front): x = ' + x + ', y = ' + y, 
            'Point.setPosition');
        // <---- DEBUG ----- */
        x = -Math.floor(this.rRadius.y) + Math.round(this.rCenter.y) 
            + Math.round(0.5 * w0);
        if (h0 == 0)
            y = -Math.floor(this.rRadius.z) + Math.round(this.rCenter.z) 
                + Math.round(0.5 * h0);
        else
            y = -Math.floor(this.rRadius.z) + height 
                - Math.round(this.rCenter.z) - Math.round(0.5 * h0);
        this.viewportRight.setStyle({
            left: '' + x + 'px', 
            top: '' + y + 'px'
        });
        /* <---- DEBUG ----- //
        GeoUtils.debug('Viewport position (right): x = ' + x + ', y = ' + y, 
            'Point.setPosition');
        // <---- DEBUG ----- */
    },
    
    // Show the point.
    show: function()
    {
        this.viewportTop.show();
        this.viewportFront.show();
        this.viewportRight.show();
    },
    
    // Hide the point.
    hide: function()
    {
        this.viewportTop.hide();
        this.viewportFront.hide();
        this.viewportRight.hide();
    },
    
    // Show highlight
    showHighlight: function()
    {
        this.viewportTop.setStyle({
            border: '1px solid #ffee8d', 
            zIndex: 1000
        });
        this.viewportFront.setStyle({
            border: '1px solid #ffee8d', 
            zIndex: 1000
        });
        this.viewportRight.setStyle({
            border: '1px solid #ffee8d', 
            zIndex: 1000
        });
    },
    
    // Remove highlight
    removeHighlight: function()
    {
        this.viewportTop.setStyle({
            border: '1px solid ' + this.lineColor, 
            zIndex: 0
        });
        this.viewportFront.setStyle({
            border: '1px solid ' + this.lineColor, 
            zIndex: 0
        });
        this.viewportRight.setStyle({
            border: '1px solid ' + this.lineColor, 
            zIndex: 0
        });
    }
    
});

/**
 * Create Box3 from GeoUtils.BoundingBox.
 *
 * bBox       -- GeoUtils.BoundingBox.
 * recursive  -- Recursive flag.
 * level      -- Hierarchy level (used for building box hierarchies 
 *                recursively).
 * 
 * Create a Box3 from a GeoUtils.BoundingBox. If the optional recursive flag 
 * is set to true, create a hierarchy of boxes.
 */
Box3.createFromBoundingBox = function(bBox, recursive, level)
{
    var r0 = GeoUtils.defaultArg(recursive, false);
    var l0 = GeoUtils.defaultArg(level, 0);
    var b0 = new Box3(GeoUtils.copyVector(bBox.center), 
        GeoUtils.copyVector(bBox.rVec));
    b0.level = l0;
    if (r0 && (bBox.items.getNumEntries() > 0))
    {
        var e0 = bBox.items.getEntries();
        for (var i = 0; i < e0.length; i++)
        {
            var it = e0[i];
            if (!GeoUtils.isUndefined(it.boundingBoxType))
            {
                var cb0 = Box3.createFromBoundingBox(it, true, l0 + 1);
                cb0.parent = b0;
                cb0.level = b0.level + 1;
                b0.children.add(cb0);
            }
        }
    }
    return b0;
}

// Point (for use with Grid3).
Point3 = Class.create(GeoUtils.BoxBoundsItem, {
    
    /**
     * Constructor.
     *
     * x           -- position (X).
     * y           -- position (Y).
     * z           -- position (Z).
     * color       -- Point color.
     * size        -- Size of the rendered result.
     */
    initialize: function($super, x, y, z, color, size)
    {
        this.x = GeoUtils.defaultArg(x, 0);
        this.y = GeoUtils.defaultArg(y, 0);
        this.z = GeoUtils.defaultArg(z, 0);
        $super.call(this, [ this.x, this.y, this.z ]);
        this.color = GeoUtils.defaultArg(color, '#ff0000');
        this.size = GeoUtils.defaultArg(size, 3);
        
        // Rendered position.
        this.rPos = new GeoUtils.Vertex3();
        // Current viewport transform matrix.
        this.transform = null;
        
        this.setupUI();
    },
    
    // Setup the user interface.
    setupUI: function()
    {
        var x = -Math.floor(0.5 * this.size);
        var y = -Math.floor(0.5 * this.size);
        this.viewportTop = new Element('div');
        this.viewportTop.setStyle({
            position: 'absolute', 
            left: x + 'px', 
            top: y + 'px', 
            width: '' + this.size + 'px', 
            height: '' + this.size + 'px', 
            backgroundColor: this.color
        });
        this.viewportFront = new Element('div');
        this.viewportFront.setStyle({
            position: 'absolute', 
            left: x + 'px', 
            top: y + 'px', 
            width: '' + this.size + 'px', 
            height: '' + this.size + 'px', 
            backgroundColor: this.color
        });
        this.viewportRight = new Element('div');
        this.viewportRight.setStyle({
            position: 'absolute', 
            left: x + 'px', 
            top: y + 'px', 
            width: '' + this.size + 'px', 
            height: '' + this.size + 'px', 
            backgroundColor: this.color
        });
    },
    
    // Get viewport element (top).
    getViewportTop: function()
    {
        return this.viewportTop;
    },
    
    // Get viewport element (top).
    getViewportFront: function()
    {
        return this.viewportFront;
    },
    
    // Get viewport element (top).
    getViewportRight: function()
    {
        return this.viewportRight;
    },
    
    /**
     * Set Point position.
     * 
     * transform  -- Viewport transform.
     * width      -- Viewport width.
     * height     -- Viewport height.
     * offset     -- Viewport offset.
     * 
     * Set the display offset of the point viewports relative to its 
     * container, using the specified viewport transform. If an optional 
     * viewport height is specified, this will be used to invert the viewport 
     * Y-axis to reflect a right-handed cartesian coordinate system.
     */
    setPosition: function(transform, width, height, offset)
    {
        var w0 = GeoUtils.defaultArg(width, 0);
        var h0 = GeoUtils.defaultArg(height, 0);
        var offset0 = GeoUtils.defaultArg(offset, [0, 0, 0]);
        this.transform = transform;
        var v0 = new GeoUtils.Vertex3(this.x - offset0[0], 
            this.y - offset0[1], this.z - offset0[2]);
        this.rPos = v0.transform(this.transform);
        var x = 0;
        var y = 0;
        x = -Math.floor(0.5 * this.size) + Math.round(this.rPos.x) 
            + Math.round(0.5 * w0);
        if (h0 == 0)
            y = -Math.floor(0.5 * this.size) + Math.round(this.rPos.y) 
                + Math.round(0.5 * h0);
        else
            y = -Math.floor(0.5 * this.size) + height 
                - Math.round(this.rPos.y) - Math.round(0.5 * h0);
        this.viewportTop.setStyle({
            left: '' + x + 'px', 
            top: '' + y + 'px'
        });
        /* <---- DEBUG ----- //
        GeoUtils.debug('Viewport position (top): x = ' + x + ', y = ' + y, 
            'Point.setPosition');
        // <---- DEBUG ----- */
        x = -Math.floor(0.5 * this.size) + Math.round(this.rPos.x) 
            + Math.round(0.5 * w0);
        if (h0 == 0)
            y = -Math.floor(0.5 * this.size) + Math.round(this.rPos.z) 
                + Math.round(0.5 * h0);
        else
            y = -Math.floor(0.5 * this.size) + height 
                - Math.round(this.rPos.z) - Math.round(0.5 * h0);
        this.viewportFront.setStyle({
            left: '' + x + 'px', 
            top: '' + y + 'px'
        });
        /* <---- DEBUG ----- //
        GeoUtils.debug('Viewport position (front): x = ' + x + ', y = ' + y, 
            'Point.setPosition');
        // <---- DEBUG ----- */
        x = -Math.floor(0.5 * this.size) + Math.round(this.rPos.y) 
            + Math.round(0.5 * w0);
        if (h0 == 0)
            y = -Math.floor(0.5 * this.size) + Math.round(this.rPos.z) 
                + Math.round(0.5 * h0);
        else
            y = -Math.floor(0.5 * this.size) + height 
                - Math.round(this.rPos.z) - Math.round(0.5 * h0);
        this.viewportRight.setStyle({
            left: '' + x + 'px', 
            top: '' + y + 'px'
        });
        /* <---- DEBUG ----- //
        GeoUtils.debug('Viewport position (right): x = ' + x + ', y = ' + y, 
            'Point.setPosition');
        // <---- DEBUG ----- */
    },
    
    // Show the point.
    show: function()
    {
        this.viewportTop.show();
        this.viewportFront.show();
        this.viewportRight.show();
    },
    
    // Hide the point.
    hide: function()
    {
        this.viewportTop.hide();
        this.viewportFront.hide();
        this.viewportRight.hide();
    },
    
    // Show highlight
    showHighlight: function()
    {
        this.viewportTop.setStyle({
            backgroundColor: '#ffee8d', 
            zIndex: 1000
        });
        this.viewportFront.setStyle({
            backgroundColor: '#ffee8d', 
            zIndex: 1000
        });
        this.viewportRight.setStyle({
            backgroundColor: '#ffee8d', 
            zIndex: 1000
        });
    },
    
    // Remove highlight
    removeHighlight: function()
    {
        this.viewportTop.setStyle({
            backgroundColor: this.color, 
            zIndex: 0
        });
        this.viewportFront.setStyle({
            backgroundColor: this.color, 
            zIndex: 0
        });
        this.viewportRight.setStyle({
            backgroundColor: this.color, 
            zIndex: 0
        });
    }
    
});

// Orthographic 3D Grid widget.
Grid3 = Class.create({
    
    /**
     * Constructor.
     *
     * x           -- position (X).
     * y           -- position (Y).
     * gridWidth   -- width (per grid).
     * gridHeight  -- heigh (per grid).
     * spacingX    -- Grid spacing (X).
     * spacingY    -- Grid spacing (Y).
     * offsetX     -- Grid offset (X).
     * offsetY     -- Grid offset (Y).
     * lineColor   -- Grid line color.
     * transform   -- Viewport transform matrix.
     * centerX     -- Center offset (X).
     * centerY     -- Center offset (Y).
     * centerZ     -- Center offset (Z).
     */
    initialize: function(x, y, width, height, spacingX, spacingY, offsetX, 
        offsetY, lineColor, transform, centerX, centerY, centerZ)
    {
        this.x = GeoUtils.defaultArg(x, 0);
        this.y = GeoUtils.defaultArg(y, 0);
        this.gridWidth = GeoUtils.defaultArg(width, 100);
        this.gridHeight = GeoUtils.defaultArg(height, 100);
        this.spacingX = GeoUtils.defaultArg(spacingX, 10);
        this.spacingY = GeoUtils.defaultArg(spacingY, 10);
        this.offsetX = GeoUtils.defaultArg(offsetX, 0);
        this.offsetY = GeoUtils.defaultArg(offsetY, 0);
        this.lineColor = GeoUtils.defaultArg(lineColor, '#707070');
        this.transform = GeoUtils.defaultArg(transform, GeoUtils.unit3x3());
        this.centerX = GeoUtils.defaultArg(centerX, 0);
        this.centerY = GeoUtils.defaultArg(centerY, 0);
        this.centerZ = GeoUtils.defaultArg(centerZ, 0);
        
        // Objects which are shown on the grid.
        this.objects = new Hash();
        
        this.setupUI();
    },
    
    // Create the grids.
    createGrids: function()
    {
        var x = 0;
        var step = this.gridWidth + this.spacingX + 2;
        this.gridTop = new Grid(x, 0, this.gridWidth, this.gridHeight, 
            this.spacingX, this.spacingY, this.offsetX, this.offsetY, 
            '#707070', true, 'top (XY)');
        x += step;
        this.gridFront = new Grid(x, 0, this.gridWidth, this.gridHeight, 
            this.spacingX, this.spacingY, this.offsetX, this.offsetY, 
            '#707070', true, 'front (XZ)');
        x += step;
        this.gridLeft = new Grid(x, 0, this.gridWidth, this.gridHeight, 
            this.spacingX, this.spacingY, this.offsetX, this.offsetY, 
            '#707070', true, 'right (YZ)');
    },
    
    // Setup the user interface.
    setupUI: function()
    {
        this.width = 3 * (this.gridWidth + 2) + 2 * this.spacingX;
        this.height = this.gridHeight + 2;
        this.viewport = new Element('div');
        this.viewport.setStyle({
            position: 'absolute', 
            left: this.getX() + 'px', 
            top: this.getY() + 'px', 
            width: '' + this.getWidth() + 'px', 
            height: '' + this.getHeight() + 'px', 
        });
        this.createGrids();
        this.viewport.insert(this.gridTop.getViewport());
        this.viewport.insert(this.gridFront.getViewport());
        this.viewport.insert(this.gridLeft.getViewport());
    },
    
    /**
     * Add object.
     *
     * obj        -- Object.
     * recursive  -- Add child objects recursively.
     * 
     * Add an object (and optionally all of its child objects recursively) to 
     * the grid.
     */
    addObject: function(obj, recursive)
    {
        var r0 = GeoUtils.defaultArg(recursive, false);
        obj.setPosition(this.transform, this.gridWidth, this.gridHeight, 
            [ this.centerX, this.centerY, this.centerZ ]);
        this.gridTop.getViewport().insert(obj.getViewportTop());
        this.gridFront.getViewport().insert(obj.getViewportFront());
        this.gridLeft.getViewport().insert(obj.getViewportRight());
        this.objects.set(obj.uniqueID, obj);
        if (r0)
        {
            var e0 = obj.children.getEntries();
            for (var i = 0; i < e0.length; i++)
                this.addObject(e0[i], true);
        }
    },
    
    /**
     * Show highlight for an object.
     * 
     * uniqueID  -- Unique ID for the object for which a highlight should be 
     *              shown.
     */
    showHighlight: function(uniqueID)
    {
        var obj = this.objects.get(uniqueID);
        obj.showHighlight();
    },
    
    /**
     * Remove highlight for an object.
     * 
     * uniqueID  -- Unique ID for the object for which a highlight should be 
     *              removed.
     */
    removeHighlight: function(uniqueID)
    {
        var obj = this.objects.get(uniqueID);
        obj.removeHighlight();
    },
    
    // Get viewport element.
    getViewport: function()
    {
        return this.viewport;
    },
    
    /**
     * Set grid position.
     * 
     * x  -- X position.
     * y  -- Y position.
     * 
     * Set the display offset of the grid viewport relative to its 
     * container.
     */
    setPosition: function(x, y)
    {
        if (GeoUtils.eq2([x0, y0], [this.x, this.y]))
            return;
        this.viewport.setStyle({
            left: '' + x0 + 'px', 
            top: '' + y0 + 'px'
        });
        this.x = x0;
        this.y = y0;
    },
    
    // Get grid position (X).
    getX: function()
    {
        return this.x;
    },
    
    // Get grid position (Y).
    getY: function()
    {
        return this.y;
    },
    
    // Get grid width.
    getWidth: function()
    {
        return this.width;
    },
    
    // Get grid height.
    getHeight: function()
    {
        return this.height;
    },
    
    // Show the grid.
    show: function()
    {
        this.viewport.show();
    },
    
    // Hide the grid.
    hide: function()
    {
        this.viewport.hide();
    }
    
});

// Test 01 class.
Test01 = Class.create({
    
    initialize: function()
    {
        this.infoBox = new Element('div', { 'id' : 'infoBox' });
        this.infoBox.addClassName('infoBox');
        this.debugBox = new Element('div', { 'id' : 'debug' });
        this.debugBox.addClassName('debugBox');
    },
    
    setup: function()
    {
        var main = $('main');
        $('noJS').replace(this.infoBox);
        main.insert(this.debugBox);
        GeoUtils.debug('Hello!', 'Test01.setup', 'guDebugItemEmp');
        // Tolerance test.
        GeoUtils.debug('Tolerance test.', 'Test01.setup', 
            'guDebugItemEmp');
        var tr0 = GeoUtils.lt(0, 1);
        var tr1 = GeoUtils.lt(0, 1, 1);
        GeoUtils.assert('0 < 1 (default tolerance): ' + tr0, 
            'Test01.setup', tr0);
        GeoUtils.assert('0 < 1 (tolerance = 1): ' + tr1, 
            'Test01.setup', !tr1);
        // Vertex in poly test.
        GeoUtils.debug('Vertex in poly test.', 'Test01.setup', 
            'guDebugItemEmp');
        var foo = GeoUtils.Vertex2.createFromSeq([1., 0.]);
        var hex = new Hexagon(40., [ new GeoUtils.Vertex2(-1., 0.), 
            new GeoUtils.Vertex2(1., 0.), new GeoUtils.Vertex2(0., 1.5) ]);
        GeoUtils.debug('Created vertex: ' + foo, 'Test01.setup');
        GeoUtils.debug('Created hexagon: ' + hex, 'Test01.setup');
        var verts = [
            [ new GeoUtils.Vertex2(0., 0.), true ], 
            [ new GeoUtils.Vertex2(10., 10.), true ], 
            [ new GeoUtils.Vertex2(100., 100.), false ]
        ];
        for (var i = 0; i < verts.length; i++)
        {
            var v = verts[i][0];
            tr0 = hex.checkVertex(v);
            GeoUtils.assert('Vertex in hexagon: ' + v + ": " + tr0, 
                'Test01.setup', tr0 == verts[i][1]);
        }
        // 3D polygon test.
        GeoUtils.debug('3D polygon test.', 'Test01.setup', 'guDebugItemEmp');
        var sq = new Square3();
        GeoUtils.debug('Created square: ' + sq, 'Test01.setup');
        GeoUtils.debug('Square barycenter: [' + sq.getBarycenter() + ']', 
            'Test01.setup');
        var plane0 = sq.getPlane();
        GeoUtils.debug('Square plane: ' + plane0, 'Test01.setup');
        var ts0 = plane0.getTangentBase();
        GeoUtils.debug('Plane normal: [' + plane0.getNormal() + ']', 
            'Test01.setup');
        GeoUtils.debug('Plane tangent space matrix: [[' + ts0[0] + '], [' 
            + ts0[1] + '], [' + ts0[2] + ']]', 'Test01.setup');
        var plane1 = GeoUtils.Plane3.createFromNormal();
        GeoUtils.debug('Plane from normal: ' + plane1, 'Test01.setup');
        // Matrix equation solver test.
        GeoUtils.debug('Matrix equation solver test.', 'Test01.setup', 
            'guDebugItemEmp');
        var m0 = [
            [ 1. , -2. ], 
            [ 4. ,  1. ]
        ];
        var v0 = [ 2., -1. ];
        tr0 = GeoUtils.solve2x2(m0, v0);
        GeoUtils.assert('S = [ 0., -1. ]:  ' + GeoUtils.vectorToString(tr0), 
            'Test01.setup', GeoUtils.eq2(tr0, [ 0., -1. ]));
        var m1 = [
            [ 3., 1., -6. ], 
            [ 2., 8., -1. ], 
            [ 5., 6., -3. ]
        ];
        var v1 = [ -1., 11., 0. ];
        tr0 = GeoUtils.solve3x3(m1, v1)
        GeoUtils.assert('S = [ -3., 2., -1. ]:  ' 
            + GeoUtils.vectorToString(tr0), 'Test01.setup', 
            GeoUtils.eq3(tr0, [ -3., 2., -1. ]));
        var m1Inv = GeoUtils.invert3x3(m1);
        GeoUtils.debug('m1_inv: ' + GeoUtils.matrixToString(m1Inv), 
            'Test01.setup');
        var r0 = GeoUtils.mult3x3(m1, m1Inv);
        GeoUtils.assert('m1 * m1_inv: ' + GeoUtils.matrixToString(r0), 
            'Test01.setup', GeoUtils.matrixEq(r0, GeoUtils.unit3x3()));
        // Range test.
        GeoUtils.debug('Range test.', 'Test01.setup', 'guDebugItemEmp');
        var ranges = [
            new GeoUtils.Range(-1.1, 1.1), 
            new GeoUtils.Range(-1.1, 0.), 
            new GeoUtils.Range(-2, 2), 
            new GeoUtils.Range(0., 1.), 
            new GeoUtils.Range(3., 5.)
        ];
        for (var i = 0; i < ranges.length; i++)
            for (var j = 0; j < ranges.length; j++)
            {
                var rx0 = ranges[i];
                var rx1 = ranges[j];
                GeoUtils.debug('Range comparison (' + rx0 + ', ' + rx1 
                    + '): '+ GeoUtils.rangeCompToString(rx0.compare(rx1)), 
                    'Test01.setup');
            }
        ranges = [
            GeoUtils.Range3.createFromVectors(
                [ -1., 1. ], [ -1., 1. ], [ -1., 1.]), 
            GeoUtils.Range3.createFromVectors(
                [ -2., 2. ], [ -2., 2. ], [ -2., 2.]), 
            GeoUtils.Range3.createFromVectors(
                [ -2., 2. ], [ -2., 2. ], [ -1.5, 1.5 ]), 
            GeoUtils.Range3.createFromVectors(
                [ 3., 5. ], [ 3., 5. ], [ 3., 5. ]), 
            GeoUtils.Range3.createFromVectors(
                [ 1.5, 3. ], [ 4., 5. ], [ 4., 5. ]) 
        ];
        for (var i = 0; i < ranges.length; i++)
            for (var j = 0; j < ranges.length; j++)
            {
                var rx0 = ranges[i];
                var rx1 = ranges[j];
                GeoUtils.debug('Range comparison (' + rx0 + ', ' + rx1 
                    + '): '+ GeoUtils.rangeCompToString(rx0.compare(rx1)), 
                    'Test01.setup');
            }
        // BoxBoundsItem test.
        GeoUtils.debug('BoxBoundsItem test.', 'Test01.setup', 
            'guDebugItemEmp');
        var bb = [
            new GeoUtils.BoxBoundsItem([ 0., 0., 0. ], 
                [ 1., 1., 1. ], 'bb0'), 
            new GeoUtils.BoxBoundsItem([ 3.1, 3.1, 0. ], 
                [ 2., 2., 2. ], 'bb1'), 
            new GeoUtils.BoxBoundsItem([ -1., -1., 0. ], 
                [ 1., 1., 1. ], 'bb2')
        ];
        for (var i = 0; i < bb.length; i++)
            for (var j = 0; j < bb.length; j++)
            {
                var bbx0 = bb[i];
                var bbx1 = bb[j];
                GeoUtils.debug('BoxBoundsItem comparison (' + bbx0 + ', ' 
                    + bbx1 + '): ' + GeoUtils.rangeCompToString(
                        bbx0.compare(bbx1)), 'Test01.setup');
                var cr = bbx0.compare3(bbx1);
                GeoUtils.debug('Per axis results: ' 
                    + GeoUtils.rangeCompToString(cr[0]) + ', '
                    + GeoUtils.rangeCompToString(cr[1]) + ', '
                    + GeoUtils.rangeCompToString(cr[2]), 'Test01.setup');
            }
        // UID test.
        GeoUtils.debug('UID test.', 'Test01.setup', 'guDebugItemEmp');
        for (var i = 0; i < 10; i++)
            GeoUtils.debug(GeoUtils.getUID(), 'Test01.setup');
        // Set test.
        GeoUtils.debug('Set test.', 'Test01.setup', 'guDebugItemEmp');
        var s0 = new GeoUtils.Set();
        var s1 = new GeoUtils.Set();
        var bb0 = new GeoUtils.BoundingBox([ 0., 0., 0. ], 
            [ 1., 1., 1. ], 'bb0');
        var bb1 = new GeoUtils.BoundingBox([ 1., 0., 0. ], 
            [ 1., 1., 1. ], 'bb1');
        var bb2 = new GeoUtils.BoundingBox([ 2., 0., 0. ], 
            [ 1., 1., 1. ], 'bb2');
        s0.add(bb0);
        s0.add(bb1);
        s1.add(bb2);
        GeoUtils.debug('s0.getNumEntries = ' + s0.getNumEntries(), 
            'Test01.setup');
        tr0 = s0.contains(bb0);
        GeoUtils.assert('s0.contains(bb0) = ' + tr0, 'Test01.setup', tr0);
        tr0 = s0.contains(bb1);
        GeoUtils.assert('s0.contains(bb1) = ' + tr0, 'Test01.setup', tr0);
        tr0 = s0.contains(bb2);
        GeoUtils.assert('s0.contains(bb2) = ' + tr0, 'Test01.setup', !tr0);
        var tok = false;
        var e0 = '<no error>';
        try {
            s0.add(5);
        } catch (e)
        {
            e0 = e;
            tok = true;
        }
        GeoUtils.assert('Trying to add non-identifiable object: ' + e0, 
            'Test01.setup', tok);
        GeoUtils.debug('s1 = ' + s1 + ' (numEntries = ' 
            + s1.getNumEntries() + ')', 'Test01.setup');
        s0.update(s1);
        GeoUtils.debug('s0 = ' + s0 + ' (numEntries = ' 
            + s0.getNumEntries() + ')', 'Test01.setup');
        tr0 = s0.contains(bb2);
        GeoUtils.assert('s0.contains(bb2) = ' + tr0, 'Test01.setup', tr0);
        var x0 = s0.pop();
        GeoUtils.debug('s0.pop() = ' + x0 + ' (numEntries = ' 
            + s0.getNumEntries() + ')', 'Test01.setup');
        x0 = s0.pop();
        GeoUtils.debug('s0.pop() = ' + x0 + ' (numEntries = ' 
            + s0.getNumEntries() + ')', 'Test01.setup');
        x0 = s0.pop();
        GeoUtils.debug('s0.pop() = ' + x0 + ' (numEntries = ' 
            + s0.getNumEntries() + ')', 'Test01.setup');
        // Bounding box test: Basic container features.
        GeoUtils.debug('Bounding box test: Basic container features.', 
            'Test01.setup', 'guDebugItemEmp');
        bb0 = new GeoUtils.BoundingBox([ 0., 0., 0. ], 
            [ 1., 1., 1. ], 'bb0');
        bb1 = new GeoUtils.BoundingBox([ 1., 0., 0. ], 
            [ 1., 1., 1. ], 'bb1');
        bb2 = new GeoUtils.BoundingBox([ 5., 0., 0. ], 
            [ 1., 1., 1. ], 'bb2');
        bb3 = new GeoUtils.BoundingBox([ 0., 0., 0. ], 
            [ 0., 0., 0. ], 'bb3');
        bb3.addItem(bb0);
        GeoUtils.debug('bb3 = ' + bb3, 'Test01.setup');
        GeoUtils.debug('Number of items in bounding box (bb3): ' 
            + bb3.items.getNumEntries(), 'Test01.setup');
        tr0 = bb3.addItem(bb2, 3.7);
        GeoUtils.assert('Testing addItem() with maxRadius.', 'Test01.setup', 
            !tr0);
        tr0 = bb3.removeItem(bb0);
        GeoUtils.assert('Testing removeItem().', 'Test01.setup', tr0);
        s0 = new GeoUtils.Set();
        s0.add(bb0);
        s0.add(bb1);
        s0.add(bb2);
        tr0 = bb3.addItems(s0);
        GeoUtils.assert('Testing addItems().', 'Test01.setup', 
            (tr0.getNumEntries() == 0) && (bb3.items.getNumEntries() == 3));
        bb3.clear();
        tr0 = bb3.addItems(s0, 2);
        GeoUtils.assert('Testing addItems() with maxItems.', 'Test01.setup', 
            (tr0.getNumEntries() == 1) && (bb3.items.getNumEntries() == 2));
        bb3.clear();
        tr0 = bb3.addItems(s0, 0, 3.7);
        GeoUtils.assert('Testing addItems() with maxRadius.', 'Test01.setup', 
            (tr0.getNumEntries() == 1) && (bb3.items.getNumEntries() == 2));
        bb3.clear();
        tr0 = bb3.takeItems(s0);
        GeoUtils.assert('Testing takeItems().', 'Test01.setup', 
            (tr0 == 3) && (bb3.items.getNumEntries() == 3) 
                && (s0.getNumEntries() == 0));
        s0.add(bb0);
        s0.add(bb1);
        s0.add(bb2);
        bb3.clear();
        tr0 = bb3.takeItems(s0, 2);
        GeoUtils.assert('Testing takeItems() with maxItems.', 'Test01.setup', 
            (tr0 == 2) && (bb3.items.getNumEntries() == 2) 
                && (s0.getNumEntries() == 1));
        s0.add(bb0);
        s0.add(bb1);
        s0.add(bb2);
        bb3.clear();
        tr0 = bb3.takeItems(s0, 0, 3.7);
        GeoUtils.assert('Testing takeItems() with maxRadius.', 'Test01.setup', 
            (tr0 == 2) && (bb3.items.getNumEntries() == 2) 
                && (s0.getNumEntries() == 1));
        // Bounding box test: Splitting.
        GeoUtils.debug('Bounding box test: Splitting.', 
            'Test01.setup', 'guDebugItemEmp');
        bb0 = new GeoUtils.BoundingBox();
        var bbi = [
            new GeoUtils.BoxBoundsItem([ -1., 1., -1. ], 
                [ 0., 0., 0. ], 'bbi0'), 
            new GeoUtils.BoxBoundsItem([ -1., -1., -1. ], 
                [ 0., 0., 0. ], 'bbi1'), 
            new GeoUtils.BoxBoundsItem([ 1., -1., -1. ], 
                [ 0., 0., 0. ], 'bbi2'),
            new GeoUtils.BoxBoundsItem([ 1., 1., -1. ], 
                [ 0., 0., 0. ], 'bbi3'),
            new GeoUtils.BoxBoundsItem([ -1., 1., 1. ], 
                [ 0., 0., 0. ], 'bbi4'), 
            new GeoUtils.BoxBoundsItem([ -1., -1., 1. ], 
                [ 0., 0., 0. ], 'bbi5'), 
            new GeoUtils.BoxBoundsItem([ 1., -1., 1. ], 
                [ 0., 0., 0. ], 'bbi6'),
            new GeoUtils.BoxBoundsItem([ 1., 1., 1. ], 
                [ 0., 0., 0. ], 'bbi7')
        ];
        var splits = GeoUtils.Split.createSplits(GeoUtils.AXIS_X);
        for (var i = 0; i < bbi.length; i++)
            if (!bb0.addItem(bbi[i]))
                throw new Error("[Test01.setup] Could not add BoxBoundsItem "
                    + "to BoundingBox!");
        tr0 = bb0.splitTest(splits[0]);
        GeoUtils.assert('Testing splitTest() with a single split.', 
            'Test01.setup', (tr0.length == 2) 
                && (tr0[0].getNumEntries() == 4) 
                && (tr0[1].getNumEntries() == 4));
        bbi = [
            new GeoUtils.BoxBoundsItem([ -1., 0., 0. ], 
                [ 0., 0., 0. ], 'bbi0'), 
            new GeoUtils.BoxBoundsItem([ -0.5, 0., 0. ], 
                [ 0., 0., 0. ], 'bbi1'), 
            new GeoUtils.BoxBoundsItem([ 0.5, 0., 0. ], 
                [ 0., 0., 0. ], 'bbi2'), 
            new GeoUtils.BoxBoundsItem([ 1., 0., 0. ], 
                [ 0., 0., 0. ], 'bbi3')
        ];
        bb0.clear();
        for (var i = 0; i < bbi.length; i++)
            if (!bb0.addItem(bbi[i]))
                throw new Error("[Test01.setup] Could not add BoxBoundsItem "
                    + "to BoundingBox!");
        var splits = GeoUtils.Split.createSplits(GeoUtils.AXIS_X, 3);
        tr0 = bb0.getBestSplit(splits);
        GeoUtils.assert('Testing getBestSplit() with 3 splits.', 
            'Test01.setup', tr0.s == 0.5);
        var gridSize = 300;
        var spaceSize = 2;
        var gridBox0 = new Element('div');
        gridBox0.setStyle({
            position: 'relative', 
            width: '' + (3 * gridSize + 40 + 6) + 'px', 
            height: '' + (gridSize + 2) + 'px', 
            margin: '20px'
        });
        var vt0 = GeoUtils.scale3x3(
            gridSize / spaceSize, 
            gridSize / spaceSize, 
            gridSize / spaceSize
        );
        this.grid0 = new Grid3(0, 0, gridSize, gridSize, 
            gridSize / 10, gridSize / 10, 0, 0, 
            '#707070', vt0);
        gridBox0.insert(this.grid0.getViewport());
        var points0 = [
            new Point3(0.607415641887, 0.718705489141, -0.225119709644, "#a43217"),
            new Point3(0.875825333637, -0.0573853653933, 0.202470894686, "#86a197"),
            new Point3(0.0622396542542, 0.833795337589, -0.594071825809, "#07a54d"),
            new Point3(0.0978927338215, -0.938852215553, -0.978846042241, "#634463"),
            new Point3(0.0728408015356, -0.00997117308592, 0.775148271791, "#09dd02"),
            new Point3(-0.698258593952, -0.548446195445, -0.938418659592, "#321253"),
            new Point3(-0.963365750832, -0.300554008166, -0.00954516618162, "#7fe16b"),
            new Point3(-0.23397952826, -0.632782192171, 0.314228963344, "#4cf202"),
            new Point3(-0.0362186111467, -0.881106809054, 0.196295037355, "#f120e0"),
            new Point3(-0.494240109345, -0.637551388716, -0.504403922825, "#69f493"),
            new Point3(0.567796144827, 0.891323063435, 0.646969860611, "#bea9a2"),
            new Point3(0.398703185601, 0.221126849291, 0.563951443381, "#953923"),
            new Point3(-0.230592732479, 0.207860506282, 0.550936374027, "#4edac9"),
            new Point3(-0.0203087267027, 0.828140936686, -0.0113749638823, "#d206c5"),
            new Point3(-0.12589991174, 0.39163333572, -0.967737855772, "#3de43f"),
            new Point3(-0.896956271477, 0.501435268487, 0.881099725261, "#e3366c"),
            new Point3(0.919674754078, 0.768222708852, -0.325443420918, "#c6fbc7"),
            new Point3(0.96884639734, -0.111784368895, 0.708906705091, "#7250b0"),
            new Point3(0.993587035364, -0.974822676713, -0.562923045724, "#fbea81"),
            new Point3(0.116054844554, -0.423830262697, -0.321361680489, "#862a95"),
            new Point3(1., 1., 1., "#ff0000"),
            new Point3(-1., -1., -1., "#00ff00")
        ];
        bb0 = new GeoUtils.BoundingBox();
        for (var i = 0; i < points0.length; i++)
        {
            var p = points0[i];
            this.grid0.addObject(p);
            bb0.addItem(p);
        }
        GeoUtils.debug('Creating splits...', 'Test01.setup');
        var splits0 = GeoUtils.Split.createSplits(GeoUtils.AXIS_X, 3);
        var splits1 = GeoUtils.Split.createSplits(GeoUtils.AXIS_Y, 3);
        var splits2 = GeoUtils.Split.createSplits(GeoUtils.AXIS_Z, 3);
        var splits = [];
        for (var i = 0; i < splits0.length; i++)
            splits.push(splits0[i]);
        for (var i = 0; i < splits1.length; i++)
            splits.push(splits1[i]);
        for (var i = 0; i < splits2.length; i++)
            splits.push(splits2[i]);
        bb0.split(splits, true, 4);
        var box0 = Box3.createFromBoundingBox(bb0, true);
        this.grid0.addObject(box0, true);
        var e0 = box0.children.getEntries();
        for (var i = 0; i < e0.length; i++)
            this.grid0.addObject(e0[i]);
        $('debug').insert(gridBox0);
        var keys0 = this.grid0.objects.keys();
        var objBox = new Element('div');
        objBox.setStyle({
            border: "1px solid #007000", 
            padding: "2px", 
            margin: "20px", 
            backgroundColor: "#96a2a5"
        });
        for (var i = 0; i < keys0.length; i++)
        {
            var k = keys0[i];
            var hlItem = '<span class="objField" onmouseover="'
                + 'javascript:test01.grid0.showHighlight(\'' + k + '\');" '
                + 'onmouseout="javascript:test01.grid0.removeHighlight(\'' + k 
                + '\');">[' + k + ']</span> ';
            objBox.insert(hlItem);
        }
        $('debug').insert(objBox);
        GeoUtils.debug('bb0: center = ' + GeoUtils.vectorToString(bb0.center) 
             + ', radius = ' + GeoUtils.vectorToString(bb0.rVec), 
            'Test01.setup');
    }
    
});

var test01 = new Test01();

Event.observe(document, 'dom:loaded', 
    test01.setup.bindAsEventListener(test01));

