#pragma once

#include "Core.hpp"
#include "Math.hpp"

namespace ag {
namespace Pixel {

struct BQuad2 {
  BQuad a, b;

  BQuad2() = default;
  BQuad2(BQuad a, BQuad b) : a{a}, b{b} {}
};

// SQuad4 contains 4 SQuads, thereby containing 32 bytes or 8 RBGA pixels
// This fills an __m128i
struct SQuad2 {
  SQuad a, b;

  SQuad2() = default;
  SQuad2(SQuad a, SQuad b)
    : a{a}, b{b} {}
};

// SQuad4 contains 4 SQuads, thereby containing 32 bytes or 8 RBGA pixels
// This fills an __m256i
struct SQuad4 {
  SQuad a, b, c, d;

  SQuad4() = default;
  SQuad4(SQuad2 a, SQuad2 b)
  : a{a.a}, b{a.b}, c{b.a}, d{b.b} {}
  SQuad4(SQuad a, SQuad b, SQuad c, SQuad d)
    : a{a}, b{b}, c{c}, d{d} {}
};

// Helper functions to translate BQuads and  SQuads
inline SQuad BQuadToSQuad(BQuad x) {
  return {
    static_cast<int16_t>(x[0]),
    static_cast<int16_t>(x[1]),
    static_cast<int16_t>(x[2]),
    static_cast<int16_t>(x[3])
  };
}

inline BQuad SQuadToBQuad(SQuad x) {
  return {
    static_cast<BYTE>(x[0]),
    static_cast<BYTE>(x[1]),
    static_cast<BYTE>(x[2]),
    static_cast<BYTE>(x[3])
  };
}

// BQuad4 contains four BQuads, thereby containing 16 bytes or 4 RGBA pixels
// This fills half of an __m256i
struct BQuad4 {
  BQuad a, b, c, d;

  BQuad4() = default;
  BQuad4(SQuad4 v) : a{SQuadToBQuad(v.a)}, b{SQuadToBQuad(v.b)}, c{SQuadToBQuad(v.c)}, d{SQuadToBQuad(v.d)} {}
  BQuad4(BQuad2 a, BQuad2 b) : a{a.a}, b{a.b}, c{b.a}, d{b.b} {}
  BQuad4(BQuad a, BQuad b, BQuad c, BQuad d) : a{a}, b{b}, c{c}, d{d} {}
};

// BQuad8 contains eight BQuads, thereby containing 32 bytes or 8 RGBA pixels
// This fills an __m256i
struct BQuad8 {
  BQuad a, b, c, d, e, f, g, h;

  BQuad8() = default;
  BQuad8(SQuad4 a, SQuad4 b) 
      : a{SQuadToBQuad(a.a)}, b{SQuadToBQuad(a.b)}, c{SQuadToBQuad(a.c)}, d{SQuadToBQuad(a.d)},
      e{SQuadToBQuad(b.a)}, f{SQuadToBQuad(b.b)}, g{SQuadToBQuad(b.c)}, h{SQuadToBQuad(b.d)}
       {}
  BQuad8(BQuad4 a, BQuad4 b)
      : a{a.a}, b{a.b}, c{a.c}, d{a.d}, e{b.a}, f{b.b}, g{b.c}, h{b.d} {}
  BQuad8(BQuad2 a, BQuad2 b, BQuad2 c, BQuad2 d)
      : a{a.a}, b{a.b}, c{b.a}, d{b.b}, e{c.a}, f{c.b}, g{d.a}, h{d.b} {}
  BQuad8(BQuad a, BQuad b, BQuad c, BQuad d, BQuad e, BQuad f, BQuad g, BQuad h)
      : a{a}, b{b}, c{c}, d{d}, e{e}, f{f}, g{g}, h{h} {}
};


// FQuad2 contains two FQuads, thereby containing 8 floats or 2 fRGBA pixels
// This fills __m256
struct FQuad2 {
  FQuad a, b;

  FQuad2() = default;
  FQuad2(FQuad a, FQuad b) : a{a}, b{b} {}
};

// Byte operations
BQuad4 Add(BQuad4 a, BQuad4 b);
BQuad4 Mul(BQuad4 a, BQuad4 b);
BQuad4 Sub(BQuad4 a, BQuad4 b);
BQuad4 Div(BQuad4 a, BQuad4 b);

BQuad8 Add(BQuad8 a, BQuad8 b);
BQuad8 Mul(BQuad8 a, BQuad8 b);
BQuad8 Sub(BQuad8 a, BQuad8 b);
BQuad8 Div(BQuad8 a, BQuad8 b);

// Float operations
FQuad2 Add(FQuad2 a, FQuad2 b);
FQuad2 Mul(FQuad2 a, FQuad2 b);
FQuad2 Sub(FQuad2 a, FQuad2 b);
FQuad2 Div(FQuad2 a, FQuad2 b);

} // namespace Pixel
}