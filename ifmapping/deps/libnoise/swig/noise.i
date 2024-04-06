/*
    This file is part of pynoise

    pynoise is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    pynoise is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with pynoise; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

%define DOCSTRING
"libnoise - Python interface"
%enddef

%module(docstring=DOCSTRING) noise
%{
#include <stdlib.h>
#include <noise.h>
#include "noiseutils.h"
%}

%feature("autodoc","1");

%include "std_string.i"

namespace noise {
  namespace module {
    class Module {
      public:
        Module(int sourceModuleCount);
        ~Module();
        virtual double GetValue(double x, double y, double z) const = 0;
        virtual int GetSourceModuleCount() const;
	virtual void SetSourceModule (int index, const Module& sourceModule);
    };
    
    class Abs : public Module {
      public:
        Abs();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };
    
    class Add : public Module {
      public:
        Add ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };
    
    class Billow: public Module
    {
      public:
        Billow ();
        double GetFrequency () const;
        double GetLacunarity () const;
        noise::NoiseQuality GetNoiseQuality () const;
        int GetOctaveCount () const;
        double GetPersistence () const;
        int GetSeed () const;
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetFrequency (double frequency);
        void SetLacunarity (double lacunarity);
        void SetNoiseQuality (noise::NoiseQuality noiseQuality);
        void SetOctaveCount (int octaveCount);
        void SetPersistence (double persistence);
        void SetSeed (int seed);
        
        %pythoncode %{
          frequency = property(GetFrequency, SetFrequency)
          lacunarity = property(GetLacunarity, SetLacunarity)
          octaveCount = property(GetOctaveCount, SetOctaveCount)
          persistence = property(GetPersistence, SetPersistence)
          quality = property(GetNoiseQuality, SetNoiseQuality)
          seed = property(GetSeed, SetSeed);          
        %}
    };
    
    class Blend: public Module
    {
      public:
        Blend ();
        const Module& GetControlModule () const;
        virtual int GetSourceModuleCount () const;
	    virtual double GetValue (double x, double y, double z) const;
        void SetControlModule (const Module& controlModule);
    };

    class Checkerboard: public Module
    {
      public:
        Checkerboard ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };
    
    class Clamp: public Module
    {
      public:
        Clamp ();
        double GetLowerBound () const;
        virtual int GetSourceModuleCount () const;
        double GetUpperBound () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetBounds (double lowerBound, double upperBound);
        
        %pythoncode %{
          lowerbound = property(GetLowerBound)
          upperbound = property(GetUpperBound)
        %}
    };
    
    class Cache: public Module
    {
      public:
        Cache ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        virtual void SetSourceModule (int index, const Module& sourceModule);
    };
    
    class Const: public Module
    {
      public:
        Const ();
        double GetConstValue () const;
        virtual int GetSourceModuleCount () const;        
        virtual double GetValue (double x, double y, double z) const;
        void SetConstValue (double constValue);
        
        %pythoncode %{
          value = property(GetConstValue, SetConstValue)
        %}
    };
    
    struct ControlPoint
    {
      double inputValue;
      double outputValue;
    };
    
    class Curve: public Module
    {
      public:
        Curve ();
        ~Curve ();
        void AddControlPoint (double inputValue, double outputValue);
        void ClearAllControlPoints ();
        const ControlPoint* GetControlPointArray () const;
        int GetControlPointCount () const;
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };  
    
    class Cylinders: public Module
    {
      public:
        Cylinders ();
        double GetFrequency () const;
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetFrequency (double frequency);
        
        %pythoncode %{
          frequency = property(GetFrequency, SetFrequency)
        %}
    };
    
    class Displace: public Module
    {
      public:
        Displace ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        const Module& GetXDisplaceModule () const;
        const Module& GetYDisplaceModule () const;
        const Module& GetZDisplaceModule () const;
        void SetDisplaceModules (const Module& xDisplaceModule, 
                                 const Module& yDisplaceModule, const Module& zDisplaceModule);
        void SetXDisplaceModule (const Module& xDisplaceModule);
        void SetYDisplaceModule (const Module& yDisplaceModule);
        void SetZDisplaceModule (const Module& zDisplaceModule);
    };    

    class Exponent: public Module
    {
      public:
        Exponent ();
        double GetExponent () const;
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetExponent (double exponent);
        
        %pythoncode %{
          exponent = property(GetExponent, SetExponent)
        %}
    };

    class Invert: public Module
    {
      public:
        Invert ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };    
    
    class Max: public Module
    {
      public:
        Max ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };
    
    class Min: public Module
    {
      public:
        Min ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };
    
    class Multiply: public Module
    {
      public:
        Multiply ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };       

    class Perlin: public Module {
      public:
        Perlin();
        double GetFrequency() const;
        double GetLacunarity() const;
        int GetOctaveCount() const;
        double GetPersistence() const;
        int GetSeed() const;
        virtual int GetSourceModuleCount() const;
        virtual double GetValue(double x, double y, double z) const;
        void SetFrequency(double frequency);
        void SetLacunarity(double lacunarity);
        void SetOctaveCount(int octaveCount);
        void SetPersistence(double persistence);
        void SetSeed(int seed);

        %pythoncode %{
          frequency = property(GetFrequency, SetFrequency)
          lacunarity = property(GetLacunarity, SetLacunarity)
          octaveCount = property(GetOctaveCount, SetOctaveCount)
          persistence = property(GetPersistence, SetPersistence)
          seed = property(GetSeed, SetSeed);
        %}
    };
    
    class Power: public Module
    {
      public:
        Power ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
    };
    
    class RidgedMulti: public Module
    {
      public:
        RidgedMulti ();
        double GetFrequency () const;
        double GetLacunarity () const;
        noise::NoiseQuality GetNoiseQuality () const;
        int GetOctaveCount () const;
        int GetSeed () const;
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetFrequency (double frequency);
        void SetLacunarity (double lacunarity);
        void SetNoiseQuality (noise::NoiseQuality noiseQuality);
        void SetOctaveCount (int octaveCount);
        void SetSeed (int seed);
        
        %pythoncode %{
          frequency = property(GetFrequency, SetFrequency)
          lacunarity = property(GetLacunarity, SetLacunarity)
          quality = property(GetNoiseQuality, SetNoiseQuality)          
          octaveCount = property(GetOctaveCount, SetOctaveCount)
          seed = property(GetSeed, SetSeed);
        %}
    };
    
    class RotatePoint: public Module
    {
      public:
        RotatePoint ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        double GetXAngle () const;
        double GetYAngle () const;
        double GetZAngle () const;
        void SetAngles (double xAngle, double yAngle, double zAngle);
        void SetXAngle (double xAngle);
        void SetYAngle (double yAngle);
        void SetZAngle (double zAngle);
        
        %pythoncode %{
          xangle = property(GetXAngle, SetXAngle)
          yangle = property(GetYAngle, SetYAngle)
          zangle = property(GetZAngle, SetZAngle)
        %}
    };    
    
    class ScaleBias: public Module
    {
      public:
        ScaleBias ();
        double GetBias () const;
        double GetScale () const;
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetBias (double bias);
        void SetScale (double scale);
        
        %pythoncode %{
          bias = property(GetBias, SetBias)
          scale = property(GetScale, SetScale)
        %}
    };
    
    class ScalePoint: public Module
    {
      public:
        ScalePoint ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        double GetXScale () const;
        double GetYScale () const;
        double GetZScale () const;
        void SetScale (double scale);
        void SetScale (double xScale, double yScale, double zScale);
        void SetXScale (double xScale);
        void SetYScale (double yScale);
        void SetZScale (double zScale);
        
        %pythoncode %{
          xscale = property(GetXScale, SetXScale)
          yscale = property(GetYScale, SetYScale)
          zscale = property(GetZScale, SetZScale)
        %}
    };    
    
    class Select: public Module
    {
      public:
        Select ();
        const Module& GetControlModule () const;
        double GetEdgeFalloff () const;
        double GetLowerBound () const;
        virtual int GetSourceModuleCount () const;
        double GetUpperBound () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetBounds (double lowerBound, double upperBound);
        void SetControlModule (const Module& controlModule);
        void SetEdgeFalloff (double edgeFalloff);
        
        %pythoncode %{
          edgefalloff = property(GetEdgeFalloff, SetEdgeFalloff)
          lowerbound = property(GetLowerBound)
          upperbound = property(GetUpperBound)
        %}
    };
    
    class Spheres: public Module
    {
      public:
        Spheres ();
        double GetFrequency () const;
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetFrequency (double frequency);
        
        %pythoncode %{
          frequency = property(GetFrequency, SetFrequency)
        %}
    };
    
    class Terrace: public Module
    {
	    public:
	      Terrace ();
	      ~Terrace ();
	      void AddControlPoint (double value);
	      void ClearAllControlPoints ();
	      const double* GetControlPointArray () const;
	      int GetControlPointCount () const;
    	  virtual int GetSourceModuleCount () const;
	      void InvertTerraces (bool invert = true);
          bool IsTerracesInverted () const;
    	  virtual double GetValue (double x, double y, double z) const;
          void MakeControlPoints (int controlPointCount);
    };    
    
    class TranslatePoint: public Module
    {
      public:
        TranslatePoint ();
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        double GetXTranslation () const;
        double GetYTranslation () const;
        double GetZTranslation () const;
        void SetTranslation (double translation);
        void SetTranslation (double xTranslation, double yTranslation, double zTranslation);
        void SetXTranslation (double xTranslation);
        void SetYTranslation (double yTranslation);
        void SetZTranslation (double zTranslation);
        
        %pythoncode   %{
          xtrans = property(GetXTranslation, SetXTranslation)
          ytrans = property(GetYTranslation, SetYTranslation)
          ztrans = property(GetZTranslation, SetZTranslation)
        %}
    };
    
    class Turbulence: public Module
    {
      public:
        Turbulence ();
        double GetFrequency () const;
        double GetPower () const;
        int GetRoughnessCount () const;
        int GetSeed () const;
        virtual int GetSourceModuleCount () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetFrequency (double frequency);
        void SetPower (double power);
        void SetRoughness (int roughness);
        void SetSeed (int seed);
        
        %pythoncode %{
          power = property(GetPower, SetPower)
          frequency = property(GetFrequency, SetFrequency)
          roughness = property(GetRoughnessCount, SetRoughness)
          seed = property(GetSeed, SetSeed)
        %}
    };    
    
    class Voronoi: public Module
    {
      public:
        Voronoi ();
        void EnableDistance (bool enable = true);
        double GetDisplacement () const;
        double GetFrequency () const;
        virtual int GetSourceModuleCount () const;
        int GetSeed () const;
        bool IsDistanceEnabled () const;
        virtual double GetValue (double x, double y, double z) const;
        void SetDisplacement (double displacement);
        void SetFrequency (double frequency);
        void SetSeed (int seed);
        
        %pythoncode %{
          displacement = property(GetDisplacement, SetDisplacement)
          frequency = property(GetFrequency, SetFrequency)
          seed = property(GetSeed, SetSeed)
          distanceEnabled = property(IsDistanceEnabled, EnableDistance)
        %}
    };    
    
  }; // end of namespace module
}; // end of namespace noise

%typemap(in) noise::uint8 = unsigned int;

namespace noise {

namespace utils {

class Color {
  public:
    Color(noise::uint8 r, noise::uint8 g, noise::uint8 b, noise::uint8 a);
    noise::uint red;
    noise::uint green;
    noise::uint blue;
    noise::uint alpha;
};

class NoiseMap {
  public:
    NoiseMap();
    NoiseMap(int width, int height);
    NoiseMap(const NoiseMap &rhs);
    ~NoiseMap();
    void Clear(float value);
    float GetBorderValue() const;
    int GetHeight() const;
    int GetMemUsed() const;
    int GetStride() const;
    float GetValue(int x, int y) const;
    int GetWidth() const;
    void ReclaimMem();
    void SetBorderValue(float borderValue);
    void SetSize(int width, int height);
    void SetValue(int x, int y, float value);
    void TakeOwnership(NoiseMap &source);

    %pythoncode %{
      borderValue = property(GetBorderValue, SetBorderValue);
      height = property(GetHeight)
      memUsed = property(GetMemUsed)
      stride = property(GetStride)
      width = property(GetWidth)
    %}
};

class NoiseMapBuilder {
  public:
    NoiseMapBuilder();
    virtual void Build() = 0;
    double GetDestHeight() const;
    double GetDestWidth() const;
    void SetDestNoiseMap( NoiseMap &destNoiseMap);
    void SetSourceModule( noise::module::Module &sourceModule);
    void SetDestSize(int destWidth, int destHeight);

    %pythoncode %{
      destHeight = property(GetDestHeight)
      destWidth = property(GetDestWidth)
    %}
};

class NoiseMapBuilderCylinder: public NoiseMapBuilder {
  public:
    NoiseMapBuilderCylinder();
    virtual void Build();
    double GetLowerAngleBound() const;
    double GetLowerHeightBound() const;
    double GetUpperAngleBound() const;
    double GetUpperHeightBound() const;
    void SetBounds(double lowerAngleBound, double upperAngleBound,
                    double lowerHeightBound, double upperHeightBound);
                    
    %pythoncode %{
      lowerAngleBound = property(GetLowerAngleBound)
      lowerHeightBound = property(GetLowerHeightBound)
      upperAngleBound = property(GetUpperAngleBound)
      upperHeightBound = property(GetUpperHeightBound)
    %}
};

class NoiseMapBuilderPlane: public NoiseMapBuilder {
  public:
    NoiseMapBuilderPlane();
    virtual void Build();
    void EnableSeamless(bool enable = true);
    double GetLowerXBound() const;
    double GetLowerZBound() const;
    double GetUpperXBound() const;
    double GetUpperZBound() const;
    bool IsSeamlessEnabled() const;
    void SetBounds(double lowerXBound, double upperXBound, 
                    double lowerZBound, double upperZBound);

    %pythoncode %{
      lowerXBound = property(GetLowerXBound)
      lowerZBound = property(GetLowerZBound)
      upperXBound = property(GetUpperXBound)
      upperZBound = property(GetUpperZBound)
      seamless = property(IsSeamlessEnabled, EnableSeamless)
    %}
};

class NoiseMapBuilderSphere: public NoiseMapBuilder {
  public:
    NoiseMapBuilderSphere();
    virtual void Build();
    double GetEastLonBound() const;
    double GetNorthLatBound() const;
    double GetSouthLatBound() const;
    double GetWestLonBound() const;
    void SetBounds(double southLatBound, double northLatBound,
                    double westLonBound, double eastLonBound);
};

class Image {
  public:
    Image();
    Image(int width, int height);
    Image(const Image &rhs);
    void Clear(const Color &value);
    Color GetBorderValue() const;
    int GetHeight() const;
    int GetStride() const;
    int GetWidth() const;
    void ReclaimMem();
    void SetBorderValue(const Color &borderValue);
    void SetSize(int width, int height);
    void SetValue(int x, int y, const Color &value);

    %pythoncode %{
      borderValue = property(GetBorderValue, SetBorderValue)
      height = property(GetHeight)
      stride = property(GetStride)
      width = property(GetWidth)
    %}
};

class RendererImage {
  public:
    RendererImage();
    void AddGradientPoint(double gradientPost, const Color &gradientColor);
    void BuildGrayscaleGradient();
    void BuildTerrainGradient();
    void ClearGradient();
    void EnableLight(bool enable = true);
    void EnableWrap(bool enable = true);
    double GetLightAzimuth() const;
    double GetLightBrightness() const;
    Color GetLightColor() const;
    double GetLightContrast() const;
    double GetLightElev() const;
    double GetLightIntensity() const;
    bool IsLightEnabled() const;
    bool IsWrapEnabled() const;
    void Render();
    void SetBackgroundImage(const Image &backgroundImage);
    void SetDestImage(Image &destImage);
    void SetLightAzimuth(double lightAzimuth);
    void SetLightBrightness(double lightBrightness);
    void SetLightColor(const Color &lightColor);
    void SetLightContrast(double lightContrast);
    void SetLightElev(double lightElev);
    void SetLightIntensity(double lightIntensity);
    void SetSourceNoiseMap(const NoiseMap &sourceNoiseMap);

    %pythoncode %{
      light = property(IsLightEnabled, EnableLight)
      wrap = property(IsWrapEnabled, EnableWrap)
      lightAzimuth = property(GetLightAzimuth, SetLightAzimuth)
      lightBrightness = property(GetLightBrightness, SetLightBrightness)
      lightColor = property(GetLightColor, SetLightColor)
      lightContrast = property(GetLightContrast, SetLightContrast)
      lightElev = property(GetLightElev, SetLightElev)
      lightIntensity = property(GetLightIntensity, SetLightIntensity)
    %}
};

class RendererNormalMap {
  public:
    RendererNormalMap();
    void EnableWrap(bool enable = true);
    double GetBumpHeight() const;
    bool IsWrapEnabled() const;
    void Render();
    void SetBumpHeight( double bumpHeight);
    void SetDestImage(Image &destImage);
    void SetSourceNoiseMap(const NoiseMap &sourceNoiseMap);
};  

class WriterBMP {
  public:
    WriterBMP();
    std::string GetDestFilename() const;
    void SetDestFilename(const std::string &filename);
    void SetSourceImage(Image &sourceImage);
    void WriteDestFile();
};

}

}
