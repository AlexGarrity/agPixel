#include "Math/PackedMathSSE.hpp"

#include "Core.hpp"
#include "Math.hpp"
#include "PackedMath.hpp"
#include <emmintrin.h>

namespace ag {
namespace Pixel {

/*
    Indexes are in bytes, rather than bits

    __mm256i packing for uint8_ts:
        | QUAD1 | QUAD2 | QUAD3 | QUAD4 | QUAD5 | QUAD6 | QUAD7 | QUAD8 |
        | 00-03 | 04-07 | 08-11 | 12-15 | 16-19 | 20-23 | 24-27 | 28-31 |

    __mm256 packing for floats:
        | QUAD1 | QUAD2 |
        | 00-15 | 16-32 |

*/

#define B(x) static_cast<BYTE>(x)
#define S(x) static_cast<int16_t>(x)
#define W(x) static_cast<WORD>(x)
#define D(x) static_cast<DWORD>(x)
#define iD(x) static_cast<int64_t>(x)

inline WORD BQuadToWord(BQuad v) {
  return (W(v[0]) | W(v[1]) << 8 | W(v[2]) << 16 | W(v[3]) << 24);
}

inline BQuad WordToBQuad(WORD v) {
  return {B(v), B(v >> 8), B(v >> 16), B(v >> 24)};
}

inline DWORD BQuad2ToDword(BQuad2 v) {
  return (DWORD(v.a[0]) | DWORD(v.a[1]) << 8 | DWORD(v.a[2]) << 16 |
          DWORD(v.a[3]) << 24 | DWORD(v.a[0]) << 32 | DWORD(v.a[1]) << 40 |
          DWORD(v.a[2]) << 48 | DWORD(v.a[3]) << 56);
}

inline BQuad2 DwordToBQuad2(DWORD v) {
  return {WordToBQuad(v), WordToBQuad(v << 32)};
}

inline DWORD SQuadToDword(SQuad v) {
  return (D(v[0]) | (D(v[1]) << 16) | (D(v[2]) << 32) | (D(v[3]) << 48));
}

inline SQuad DwordToSQuad(DWORD v) {
  return {S(v), S(v >> 16), S(v >> 32), S(v >> 48)};
}

inline BQuad4 M128ToBQuad4(__m128i v) {
  return {WordToBQuad(v[0]), WordToBQuad(v[1]), WordToBQuad(v[2]),
          WordToBQuad(v[3])};
}

__m128i BQuad4ToM128(BQuad4 v) {
  __m128i out;
  out[0] = D(BQuadToWord(v.a)) | D(BQuadToWord(v.b)) << 32;
  out[1] = D(BQuadToWord(v.c)) | D(BQuadToWord(v.d)) << 32;
  return out;
}

inline __m128i SQuad2ToM128(SQuad2 v) {
  return {
      iD(SQuadToDword(v.a)),
      iD(SQuadToDword(v.b)),
  };
}

inline SQuad2 M128ToSQuad2(__m128i v) {
  return {DwordToSQuad(v[0]), DwordToSQuad(v[1])};
}

__m128 FQuadToM128(FQuad v) { return {v[0], v[1], v[2], v[3]}; }

FQuad M128ToFQuad(__m128 v) { return {v[0], v[1], v[2], v[3]}; }

BQuad4 Add(BQuad4 a, BQuad4 b) {
  auto result = _mm_adds_epu8(BQuad4ToM128(a), BQuad4ToM128(b));
  return M128ToBQuad4(result);
}

BQuad4 Sub(BQuad4 a, BQuad4 b) {
  auto result = _mm_subs_epu8(BQuad4ToM128(a), BQuad4ToM128(b));
  return M128ToBQuad4(result);
}

BQuad4 Mul(BQuad4 a, BQuad4 b) {
  auto s1 = SQuad2(BQuadToSQuad(a.a), BQuadToSQuad(a.b));
  auto s2 = SQuad2(BQuadToSQuad(a.c), BQuadToSQuad(a.d));
  auto s3 = SQuad2(BQuadToSQuad(b.a), BQuadToSQuad(b.b));
  auto s4 = SQuad2(BQuadToSQuad(b.c), BQuadToSQuad(b.d));

  auto m1 = SQuad2ToM128(s1);
  auto m2 = SQuad2ToM128(s2);
  auto m3 = SQuad2ToM128(s3);
  auto m4 = SQuad2ToM128(s4);

  auto r1 = _mm_mullo_epi16(m1, m3);
  auto r2 = _mm_mullo_epi16(m2, m4);

  auto rs1 = M128ToSQuad2(r1);
  auto rs2 = M128ToSQuad2(r2);

  return {SQuadToBQuad(rs1.a), SQuadToBQuad(rs1.b), SQuadToBQuad(rs2.a),
          SQuadToBQuad(rs2.b)};
}

BQuad4 Div(BQuad4 a, BQuad4 b) {
  auto r1 = Div(a.a[0], a.a[1], a.a[2], a.a[3], b.a[0], b.a[1], b.a[2], b.a[3]);
  auto r2 = Div(a.b[0], a.b[1], a.b[2], a.b[3], b.b[0], b.b[1], b.b[2], b.b[3]);
  auto r3 = Div(a.c[0], a.c[1], a.c[2], a.c[3], b.c[0], b.c[1], b.c[2], b.c[3]);
  auto r4 = Div(a.d[0], a.d[1], a.d[2], a.d[3], b.d[0], b.d[1], b.d[2], b.d[3]);
  return {r1, r2, r4, r4};
}

BQuad8 Add(BQuad8 a, BQuad8 b) {
  BQuad4 aa{a.a, a.b, a.c, a.d};
  BQuad4 ab{a.e, a.f, a.g, a.h};
  BQuad4 ba{b.a, b.b, b.c, b.d};
  BQuad4 bb{b.e, b.f, b.g, b.h};

  auto r1 = _mm_adds_epu8(BQuad4ToM128(aa), BQuad4ToM128(ba));
  auto r2 = _mm_adds_epu8(BQuad4ToM128(ba), BQuad4ToM128(bb));
  return {M128ToBQuad4(r1), M128ToBQuad4(r2)};
}

BQuad8 Sub(BQuad8 a, BQuad8 b) {
  BQuad4 aa{a.a, a.b, a.c, a.d};
  BQuad4 ab{a.e, a.f, a.g, a.h};
  BQuad4 ba{b.a, b.b, b.c, b.d};
  BQuad4 bb{b.e, b.f, b.g, b.h};

  auto r1 = _mm_subs_epu8(BQuad4ToM128(aa), BQuad4ToM128(ba));
  auto r2 = _mm_subs_epu8(BQuad4ToM128(ba), BQuad4ToM128(bb));
  return {M128ToBQuad4(r1), M128ToBQuad4(r2)};
}

BQuad8 Mul(BQuad8 a, BQuad8 b) {
  auto b1 = BQuad4(a.a, a.b, a.c, a.d);
  auto b2 = BQuad4(a.e, a.f, a.g, a.h);
  auto b3 = BQuad4(b.a, b.b, b.c, b.d);
  auto b4 = BQuad4(b.e, b.f, b.g, b.h);

  auto r1 = Mul(b1, b3);
  auto r2 = Mul(b2, b4);

  return {r1, r2};
}

BQuad8 Div(BQuad8 a, BQuad8 b) {
  auto r1 = Div(a.a[0], a.a[1], a.a[2], a.a[3], b.a[0], b.a[1], b.a[2], b.a[3]);
  auto r2 = Div(a.b[0], a.b[1], a.b[2], a.b[3], b.b[0], b.b[1], b.b[2], b.b[3]);
  auto r3 = Div(a.c[0], a.c[1], a.c[2], a.c[3], b.c[0], b.c[1], b.c[2], b.c[3]);
  auto r4 = Div(a.d[0], a.d[1], a.d[2], a.d[3], b.d[0], b.d[1], b.d[2], b.d[3]);
  auto r5 = Div(a.e[0], a.e[1], a.e[2], a.e[3], b.e[0], b.e[1], b.e[2], b.e[3]);
  auto r6 = Div(a.f[0], a.f[1], a.f[2], a.f[3], b.f[0], b.f[1], b.f[2], b.f[3]);
  auto r7 = Div(a.g[0], a.g[1], a.g[2], a.g[3], b.g[0], b.g[1], b.g[2], b.g[3]);
  auto r8 = Div(a.h[0], a.h[1], a.h[2], a.h[3], b.h[0], b.h[1], b.h[2], b.h[3]);
  return {r1, r2, r4, r4, r5, r6, r7, r8};
}

FQuad2 Add(FQuad2 a, FQuad2 b) {
  auto r1 = _mm_add_ps(FQuadToM128(a.a), FQuadToM128(b.a));
  auto r2 = _mm_add_ps(FQuadToM128(a.b), FQuadToM128(b.b));
  return {M128ToFQuad(r1), M128ToFQuad(r2)};
}

FQuad2 Sub(FQuad2 a, FQuad2 b) {
  auto r1 = _mm_sub_ps(FQuadToM128(a.a), FQuadToM128(b.a));
  auto r2 = _mm_sub_ps(FQuadToM128(a.b), FQuadToM128(b.b));
  return {M128ToFQuad(r1), M128ToFQuad(r2)};
}

FQuad2 Mul(FQuad2 a, FQuad2 b) {
  auto r1 = _mm_mul_ps(FQuadToM128(a.a), FQuadToM128(b.a));
  auto r2 = _mm_mul_ps(FQuadToM128(a.b), FQuadToM128(b.b));
  return {M128ToFQuad(r1), M128ToFQuad(r2)};
}

FQuad2 Div(FQuad2 a, FQuad2 b) {
  auto r1 = _mm_div_ps(FQuadToM128(a.a), FQuadToM128(b.a));
  auto r2 = _mm_div_ps(FQuadToM128(a.b), FQuadToM128(b.b));
  return {M128ToFQuad(r1), M128ToFQuad(r2)};
}

} // namespace Pixel
} // namespace ag