#pragma once

// Floating point represetations of pixels
// More CPU intensive to use, but also more accurate
// Suited for applications such as ray tracing

namespace Pixel {

// fRGB is the simplest way to represent a pixel, using only red, green, and
// blue
class fRGB {
 protected:
  float _r;
  float _g;
  float _b;

 public:
  fRGB(float r, float g, float b);
  fRGB();

  float R() const;
  float& R();
  unsigned uR() const;

  float G() const;
  float& G();
  unsigned uG() const;

  float B() const;
  float& B();
  unsigned uB() const;

 public:
  void operator+=(fRGB& other);
  void operator-=(fRGB& other);

  virtual void operator+=(float value);

  virtual void operator-=(float value);

  virtual void operator*=(float value);

  virtual void operator/=(float value);
};

// fRGBA is an extension of fRGB, adding support for alpha
class fRGBA : public fRGB {
 protected:
  float _a;

 public:
  fRGBA(float r, float g, float b, float a);
  fRGBA();

  float A() const;
  float& A();
  unsigned uA() const;

 public:
  void operator+=(fRGBA& other);
  void operator-=(fRGBA& other);
  void operator+=(float value) override;
  void operator-=(float value) override;
  void operator*=(float value) override;
  void operator/=(float value) override;
};

};  // namespace Pixel