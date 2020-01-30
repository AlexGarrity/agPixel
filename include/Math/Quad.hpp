#pragma once

#include <cstdint>

// Quad header provides a bunch of quad classes for use in maths functions
// This serves to reduce the size of the maths implementation files and to
// modularise the quads

namespace ag {
namespace Pixel {

// Forward declare for use in narrowing constructors
template <typename T> struct Quad;

template <typename T> struct Quad2;

template <typename T> struct Quad4;

template <typename T> struct Quad8;

template <typename T> struct Quad {
  T a, b, c, d;

  Quad() = default;
  Quad(T a, T b, T c, T d) : a{a}, b{b}, c{c}, d{d} {}
  Quad(T v) : a{v}, b{v}, c{v}, d{v} {}

  Quad(Quad2<T> v);
  Quad(Quad4<T> v);
  Quad(Quad8<T> v);

  T A() { return a; }
  T B() { return b; }
  T C() { return c; }
  T D() { return d; }
};

template <typename T> struct Quad2 {
  Quad<T> a, b;

  Quad2() = default;
  Quad2(T v) : a{v}, b{v} {}

  Quad2(Quad<T> a, Quad<T> b) : a{a}, b{b} {}

  Quad2(Quad4<T> v);
  Quad2(Quad8<T> v);

  inline Quad<T> &qA() { return a; }
  inline Quad<T> &qB() { return b; }
};

template <typename T> struct Quad4 {
  Quad2<T> a, b;

  Quad4() = default;
  Quad4(T v) : a{v}, b{v} {}

  Quad4(Quad<T> a, Quad<T> b, Quad<T> c, Quad<T> d) : a{a, b}, b{c, d} {}
  Quad4(Quad2<T> a, Quad2<T> b) : a{a}, b{b} {}
  
  Quad4(Quad8<T> v);

  inline Quad<T> &qA() { return a.a; }
  inline Quad<T> &qB() { return a.b; }
  inline Quad<T> &qC() { return b.a; }
  inline Quad<T> &qD() { return b.b; }
};

template <typename T> struct Quad8 {
  Quad4<T> a, b;

  Quad8() = default;
  Quad8(T v) : a{v}, b{v} {}

  Quad8(Quad<T> a, Quad<T> b, Quad<T> c, Quad<T> d, Quad<T> e, Quad<T> f,
        Quad<T> g, Quad<T> h)
      : a{{a, b}, {c, d}}, b{{e, f}, {g, h}} {}
  Quad8(Quad2<T> a, Quad2<T> b, Quad2<T> c, Quad2<T> d) : a{a, b}, b{c, d} {}
  Quad8(Quad4<T> a, Quad4<T> b) : a{a}, b{b} {}

  inline Quad<T> &qA() { return a.a.a; }
  inline Quad<T> &qB() { return a.a.b; }
  inline Quad<T> &qC() { return a.b.a; }
  inline Quad<T> &qD() { return a.b.b; }
  inline Quad<T> &qE() { return b.a.b; }
  inline Quad<T> &qF() { return b.a.b; }
  inline Quad<T> &qG() { return b.b.a; }
  inline Quad<T> &qH() { return b.b.b; }
};

// Narrowing constructors
// Quad{8,4,2} to Quad
template <typename T> Quad<T>::Quad(Quad2<T> v) : Quad(v.a) {}
template <typename T> Quad<T>::Quad(Quad4<T> v) : Quad(v.a.a) {}
template <typename T> Quad<T>::Quad(Quad8<T> v) : Quad(v.a.a.a) {}

// Quad{8,4} to Quad2
template <typename T> Quad2<T>::Quad2(Quad4<T> v) : Quad2(v.a) {}
template <typename T> Quad2<T>::Quad2(Quad8<T> v) : Quad2(v.a.a) {}

// Quad8 to Quad4
template <typename T> Quad4<T>::Quad4(Quad8<T> v) : Quad4(v.a) {}

#define BYTE uint8_t
#define SHORT int16_t
#define WORD uint32_t
#define DWORD uint64_t

using BQuad = Quad<BYTE>;
using SQuad = Quad<SHORT>;
using FQuad = Quad<float>;
using DQuad = Quad<double>;

using BQuad2 = Quad2<BYTE>;
using SQuad2 = Quad2<SHORT>;
using FQuad2 = Quad2<float>;

using BQuad4 = Quad4<BYTE>;
using SQuad4 = Quad4<SHORT>;

using BQuad8 = Quad8<BYTE>;

} // namespace Pixel
} // namespace ag