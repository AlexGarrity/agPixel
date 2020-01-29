#include "Math/PackedMathAVX.hpp"

#include "Core.hpp"
#include "Math.hpp"
#include "PackedMath.hpp"

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

inline BQuad4 M256ToBQuad4(__m256i v) {
  return {WordToBQuad(v[0]), WordToBQuad(v[1]), WordToBQuad(v[2]),
          WordToBQuad(v[3])};
}

inline BQuad8 M256ToBQuad8(__m256i v) {
  return {DwordToBQuad2(v[0]), DwordToBQuad2(v[1]), DwordToBQuad2(v[2]),
          DwordToBQuad2(v[3])};
}

inline DWORD SQuadToDword(SQuad v) {
  return (D(v[0]) | (D(v[1]) << 16) | (D(v[2]) << 32) | (D(v[3]) << 48));
}

inline SQuad DwordToSQuad(DWORD v) {
  return {S(v), S(v >> 16), S(v >> 32), S(v >> 48)};
}

// Helper functions to translate BQuad8s and SQuad4s
inline SQuad4 BQuad8UpperToSQuad4(BQuad8 x) {
  return {BQuadToSQuad(x.a), BQuadToSQuad(x.b), BQuadToSQuad(x.c),
          BQuadToSQuad(x.d)};
}

inline SQuad4 BQuad8LowerToSQuad4(BQuad8 x) {
  return {BQuadToSQuad(x.e), BQuadToSQuad(x.f), BQuadToSQuad(x.g),
          BQuadToSQuad(x.h)};
}

inline __m256i BQuad4ToM256(BQuad4 v) {
  return {BQuadToWord(v.a), BQuadToWord(v.b), BQuadToWord(v.c),
          BQuadToWord(v.d)};
}

// Super hacky and I hate it, but it works
inline __m256i BQuad8ToM256(BQuad8 v) {
  return {
      iD(BQuad2ToDword(BQuad2(v.a, v.b))), iD(BQuad2ToDword(BQuad2(v.c, v.d))),
      iD(BQuad2ToDword(BQuad2(v.e, v.f))), iD(BQuad2ToDword(BQuad2(v.g, v.h)))};
}

inline __m256i SQuad4ToM256(SQuad4 v) {
  return {iD(SQuadToDword(v.a)), iD(SQuadToDword(v.b)), iD(SQuadToDword(v.c)),
          iD(SQuadToDword(v.d))};
}

inline SQuad4 M256ToSQuad4(__m256i v) {
  return SQuad4{DwordToSQuad(v[0]), DwordToSQuad(v[1]), DwordToSQuad(v[2]),
                DwordToSQuad(v[3])};
}

inline __m256 FQuad2ToM256(FQuad2 v) {
  return {v.a[0], v.a[1], v.a[2], v.a[3], v.b[0], v.b[1], v.b[2], v.b[3]};
}

FQuad2 M256ToFQuad2(__m256 v) {
  FQuad2 o;
  o.a[0] = v[0];
  o.a[1] = v[1];
  o.a[2] = v[2];
  o.a[3] = v[3];

  o.b[0] = v[4];
  o.b[1] = v[5];
  o.b[2] = v[6];
  o.b[3] = v[7];
  return o;
}

BQuad4 Add(BQuad4 a, BQuad4 b) {
  auto result = _mm256_adds_epu8(BQuad4ToM256(a), BQuad4ToM256(b));
  return M256ToBQuad4(result);
}

BQuad4 Sub(BQuad4 a, BQuad4 b) {
  auto result = _mm256_subs_epu8(BQuad4ToM256(a), BQuad4ToM256(b));
  return M256ToBQuad4(result);
}

BQuad4 Mul(BQuad4 a, BQuad4 b) {
  auto sq1 = SQuad4(BQuadToSQuad(a.a), BQuadToSQuad(a.b), BQuadToSQuad(a.c),
                    BQuadToSQuad(a.d));
  auto sq2 = SQuad4(BQuadToSQuad(b.a), BQuadToSQuad(b.b), BQuadToSQuad(b.c),
                    BQuadToSQuad(b.d));

  auto m1 = SQuad4ToM256(sq1);
  auto m2 = SQuad4ToM256(sq2);

  auto r1 = _mm256_mullo_epi16(m1, m2);

  return M256ToSQuad4(r1);
}

BQuad4 Div(BQuad4 a, BQuad4 b) {
  auto r1 = Div(a.a[0], a.a[1], a.a[2], a.a[3], b.a[0], b.a[1], b.a[2], b.a[3]);
  auto r2 = Div(a.b[0], a.b[1], a.b[2], a.b[3], b.b[0], b.b[1], b.b[2], b.b[3]);
  auto r3 = Div(a.c[0], a.c[1], a.c[2], a.c[3], b.c[0], b.c[1], b.c[2], b.c[3]);
  auto r4 = Div(a.d[0], a.d[1], a.d[2], a.d[3], b.d[0], b.d[1], b.d[2], b.d[3]);
  return {r1, r2, r4, r4};
}

BQuad8 Add(BQuad8 a, BQuad8 b) {
  auto result = _mm256_adds_epu8(BQuad8ToM256(a), BQuad8ToM256(b));
  return M256ToBQuad8(result);
}

BQuad8 Sub(BQuad8 a, BQuad8 b) {
  auto result = _mm256_subs_epu8(BQuad8ToM256(a), BQuad8ToM256(b));
  return M256ToBQuad8(result);
}

BQuad8 Mul(BQuad8 a, BQuad8 b) {
  auto sq1 = BQuad8LowerToSQuad4(a);
  auto sq2 = BQuad8UpperToSQuad4(a);
  auto sq3 = BQuad8LowerToSQuad4(b);
  auto sq4 = BQuad8UpperToSQuad4(b);

  auto m1 = SQuad4ToM256(sq1);
  auto m2 = SQuad4ToM256(sq2);
  auto m3 = SQuad4ToM256(sq3);
  auto m4 = SQuad4ToM256(sq4);

  auto r1 = _mm256_mullo_epi16(m1, m3);
  auto r2 = _mm256_mullo_epi16(m2, m4);

  return {M256ToSQuad4(r1), M256ToSQuad4(r2)};
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
  auto result = _mm256_add_ps(FQuad2ToM256(a), FQuad2ToM256(b));
  return M256ToFQuad2(result);
}

FQuad2 Sub(FQuad2 a, FQuad2 b) {
  auto result = _mm256_sub_ps(FQuad2ToM256(a), FQuad2ToM256(b));
  return M256ToFQuad2(result);
}

FQuad2 Mul(FQuad2 a, FQuad2 b) {
  auto result = _mm256_mul_ps(FQuad2ToM256(a), FQuad2ToM256(b));
  return M256ToFQuad2(result);
}

FQuad2 Div(FQuad2 a, FQuad2 b) {
  auto result = _mm256_div_ps(FQuad2ToM256(a), FQuad2ToM256(b));
  return M256ToFQuad2(result);
}

} // namespace Pixel
} // namespace ag