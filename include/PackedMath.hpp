#pragma once

#include "Core.hpp"
#include "Math.hpp"

namespace Pixel {

struct BQuad2 {
  BQuad a, b;

  BQuad2() = default;
  BQuad2(BQuad a, BQuad b) : a{a}, b{b} {}
};

// BQuad4 contains four BQuads, thereby containing 16 bytes or 4 RGBA pixels
// This fills half of an __m256i
struct BQuad4 {
  BQuad a, b, c, d;

  BQuad4() = default;
  BQuad4(BQuad2 a, BQuad2 b) : a{a.a}, b{a.b}, c{b.a}, d{b.b} {}
  BQuad4(BQuad a, BQuad b, BQuad c, BQuad d) : a{a}, b{b}, c{c}, d{d} {}
};

// BQuad8 contains eight BQuads, thereby containing 16 bytes or 8 RGBA pixels
// This fills an __m256i
struct BQuad8 {
  BQuad a, b, c, d, e, f, g, h;

  BQuad8() = default;
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