#include <immintrin.h>
#include <stdio.h>

int main() {
  __m256d a{0.1, 0.2, 0.3, 0.4};
  __m256d b{0.4, 0.3, 0.2, 0.1};
  __m256d r = _mm256_add_pd(a, b);
  if (r[0] == r[1] == r[2] == r[3])
    printf("r0: %f\tr1: %f\tr2: %f\tr3: %f\n", r[0], r[1], r[2], r[3]);
  return 0;
  return -1;
}