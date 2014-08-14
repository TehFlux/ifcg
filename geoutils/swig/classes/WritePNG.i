/* ==========================================================================
 * GeoUtils - Ionflux' Geometry Library
 * Copyright © 2009-2013 Jörn P. Meier
 * mail@ionflux.org
 * --------------------------------------------------------------------------
 * WritePNG.i                      Transform node: Write PNG (interface).
 * =========================================================================
 * 
 * This file is part of GeoUtils - Ionflux' Geometry Library.
 * 
 * GeoUtils - Ionflux' Geometry Library is free software; you can 
 * redistribute it and/or modify it under the terms of the GNU General 
 * Public License as published by the Free Software Foundation; either 
 * version 2 of the License, or (at your option) any later version.
 * 
 * GeoUtils - Ionflux' Geometry Library is distributed in the hope that it 
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied 
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with GeoUtils - Ionflux' Geometry Library; if not, write to the Free 
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 
 * 02111-1307 USA
 * 
 * ========================================================================== */
%{
#include "geoutils/WritePNG.hpp"
%}

namespace Ionflux
{

namespace GeoUtils
{

namespace TransformNodes
{

class WritePNGClassInfo
: public Ionflux::ObjectBase::IFClassInfo
{
    public:
        WritePNGClassInfo();
        virtual ~WritePNGClassInfo();
};

class WritePNG
: public Ionflux::GeoUtils::TransformNodes::TransformNode
{
    public:
		static const unsigned int INPUT_FIRST;
		static const unsigned int OUTPUT_COMPOSITE;
        
        WritePNG();
		WritePNG(const Ionflux::GeoUtils::TransformNodes::WritePNG& other);
        WritePNG(const std::string& initFileName, Ionflux::GeoUtils::AxisID
        initAxis = Ionflux::GeoUtils::AXIS_Z, bool initClosePath = true, 
        const Ionflux::GeoUtils::SVGShapeStyleVector* initStyles = 0, 
        unsigned int initWidth = 1000, unsigned int initHeight = 1000, 
        unsigned int initOriginX = 0, unsigned int initOriginY = 0, const 
        Ionflux::Altjira::Color& initBackgroundColor = 
        Ionflux::Altjira::Color::TRANSPARENT, const 
        Ionflux::ObjectBase::IFObjectID& nodeID = "");
        virtual ~WritePNG();
        virtual std::string getString() const;
        virtual void addStyles(const 
        Ionflux::GeoUtils::SVGShapeStyleVector& newStyles);
		virtual Ionflux::GeoUtils::TransformNodes::WritePNG* copy() const;
		static Ionflux::GeoUtils::TransformNodes::WritePNG* 
		upcast(Ionflux::ObjectBase::IFObject* other);
		static Ionflux::GeoUtils::TransformNodes::WritePNG* 
		create(Ionflux::ObjectBase::IFObject* parentObject = 0);
		virtual unsigned int getMemSize() const;
        virtual void setFileName(const std::string& newFileName);
        virtual std::string getFileName() const;        
        virtual unsigned int getNumStyles() const;
        virtual Ionflux::GeoUtils::SVGShapeStyle* getStyle(unsigned int 
        elementIndex = 0) const;
		virtual int findStyle(Ionflux::GeoUtils::SVGShapeStyle* needle, unsigned 
		int occurence = 1) const;
        virtual std::vector<Ionflux::GeoUtils::SVGShapeStyle*>& 
        getStyles();
        virtual void addStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        addElement);        
        virtual void removeStyle(Ionflux::GeoUtils::SVGShapeStyle* 
        removeElement);
		virtual void removeStyleIndex(unsigned int removeIndex);
		virtual void clearStyles();
        virtual void setAxis(Ionflux::GeoUtils::AxisID newAxis);
        virtual Ionflux::GeoUtils::AxisID getAxis() const;
        virtual void setClosePath(bool newClosePath);
        virtual bool getClosePath() const;
        virtual void setWidth(unsigned int newWidth);
        virtual unsigned int getWidth() const;
        virtual void setHeight(unsigned int newHeight);
        virtual unsigned int getHeight() const;
        virtual void setOriginX(unsigned int newOriginX);
        virtual unsigned int getOriginX() const;
        virtual void setOriginY(unsigned int newOriginY);
        virtual unsigned int getOriginY() const;
        virtual void setBackgroundColor(const Ionflux::Altjira::Color& 
        newBackgroundColor);
        virtual Ionflux::Altjira::Color getBackgroundColor() const;
};

}

}

}
