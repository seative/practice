#include <immintrin.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <random>
#include <vector>

#include "print.h"
#include "simd_print.h"

#define _MM_SHUFFLER(x, y, z, w) _MM_SHUFFLE(w, z, y, x)

int main() {
  // {
  //   double x = 3.8;
  //   double y = 1.4;
  //   __m128d m = _mm_setr_pd(x, y);
  //   __m128d two = _mm_set1_pd(2.0);
  //   m = _mm_mul_pd(m, two);
  //   print(m);
  // }
  // float f = 1;
  // int i = *(int*)&f;
  // print(as_hex(i));
  // {
  //   __m128 m = _mm_setr_ps(1.5, -2.5, 3.5, -4.5);
  //   print(m);
  //   // __m128i mi = _mm_castps_si128(m);
  //   __m128i mi = _mm_cvtps_epi32(m);
  //   print(mi);
  // }
  // {
  //   float x = 3.8f;
  //   float y = 3.3f;
  //   float z = 1.4f;
  //   float w = -5.3f;

  //   __m128 m = _mm_setr_ps(x, y, z, w);
  //   __m128 two = _mm_set1_ps(2.0f);
  //   m = _mm_mul_ps(m, two);
  //   print(m);
  // }
  // {
  //   __m128i m = _mm_setr_epi32(1, 2, 3, 4);
  //   __m128i two = _mm_set1_epi32(2);
  //   m = _mm_mullo_epi32(m, two);
  //   print(m);
  // }
  // {
  //   __m128i m = _mm_setr_epi16(1, 2, 3, 4, 5, 6, 7, 8);
  //   __m128i two = _mm_set1_epi16(2);
  //   m = _mm_mullo_epi16(m, two);
  //   print(m);
  // }
  // {
  //   __m128i m = _mm_setr_epi32(1, 2, 3, 4);
  //   m = _mm_shuffle_epi32(m, _MM_SHUFFLER(0, 1, 2, 3));
  //   print(m);
  //   __m128 m2 = _mm_setr_ps(1.5, -2.5, 3.5, -4.5);
  //   m2 = _mm_castsi128_ps(_mm_shuffle_epi32(_mm_castps_si128(m2),
  //   0b00011011)); print(m2); m2 = _mm_shuffle_ps(m2, m2, _MM_SHUFFLER(0, 1,
  //   2, 3)); print(m2);
  // }
  // {
  //   __m128 m = _mm_setr_ps(1, 2, 3, 4);
  //   __m128 n = _mm_shuffle_ps(m, m, _MM_SHUFFLER(1, 0, 3, 2));
  //   m = _mm_add_ps(m, n);
  //   print(m);
  //   n = _mm_shuffle_ps(m, m, _MM_SHUFFLER(2, 3, 0, 1));
  //   m = _mm_add_ss(m, n);
  //   // float x = _mm_cvtss_f32(m);
  //   // addps(m,n) ={m[0]+n[0],m[1]+n[1],m[2]+n[2],m[3]+n[3]}
  //   // addss(m,n) ={m[0]+n[0],m[1],m[2],m[3]}
  //   print(m);
  //   print(_mm_cvtss_f32(m));
  //   print(m[0]);
  //   print(_mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLER(1, 0, 0, 0))));
  // }
  {
    float a[4] = {1, 2, 3, 4};
    __m128 m = _mm_load1_ps(&a[0]);
    print(m);
    float b[4];
    _mm_storeu_ps(b, m);
    print(b);
  }
}