#include <immintrin.h>

int main() {
    __m128d a {0.1, 0.2};
    __m128d b {0.4, 0.3};
    __m128d r = _mm_add_pd(a, b);
    if (r[0] == r[1])
        return 0;
    return -1;
}