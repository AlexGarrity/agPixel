# libPixel
Lightweight library which provides char, float, and double representation of pixels, for use in
all kinds of applications from image libraries to raytracing.  

## Building
I haven't tested this yet, but these are the instructions for building...

```bash
cmake .
make
make install
```

And that should automagically install it.  
Note that support for vector extensions is off by default, so if you want those you have to do 
some extra configuration.  I have no idea how that part works.  Just use ccmake or cmake-gui.

## Cool Features
The library hase limited support for AVX2.  If you toggle `ENABLE_EXTENSIONS` in CMake, the program
will attempt to build using AVX2 (although it will throw an error if your compiler doesn't support it).  
Using this, you can expect a speedup of ~2x for basic arithmetic operations, based on some limited testing.

## Possible future additions
I would like to include operations that allow you to pass multiple pixels into a single math operation,
leveraging the full power of AVX, but I'm yet to find a nice way to do this due to data width.
A double pixel will use an entire _mm256_mul_pd operation, whereas I can fit two pixels into an _mm256_mul_ps.
I may or may not add them in as specialised functions that only apply to specific pixel types.  

I've considered adding support for SSE, or maybe even MMX, but I don't think these will be happening.  MMX is
too old, and has definitely been superceded by SSE and AVX.  On the other hand, SSE is still updated, but I think
it's being replaced by AVX at this point.  If there's enough (or any) interest in it, I might add it in.