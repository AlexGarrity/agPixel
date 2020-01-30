# agPixel
***Note - this library is currently undergoing some changes and will be separated into two components in the near future.  agPixel will remain for image manipulation, but a new library (likely agSIMD) will be absorbing the maths functions.***

Lightweight library which provides char, float, and double representation of pixels, for use in all kinds of applications from image libraries to raytracing.  
It also provides a set of math functions for operating on pixels, including packed maths with optional vector extension support.  

## Building
Building should be pretty simple, you can just run this:

```bash
cmake .
make
make install
```

Or, what I'd recommend is using `ccmake` or `cmake-gui`.  These will allow you to configure the project to cater your needs.
I'd also recommend creating a build folder.  To do this, it's just:

```bash
mkdir build
cd build
cmake-gui -S .. -B .
make
make install
```

And that should automagically install it.  
Note that support for vector extensions is off by default, but you can most likely turn it on and it'll be fine.
If your CPU doesn't support the extensions, the compiler will throw an error at you.  Just disable extensions in cmake.

## Features
The library has support for AVX2 and SSE2.  If you toggle `ENABLE_EXTENSIONS` in CMake, the program will first detect which extensions are available, then attempt to build using them.  This allows the math functions to utilise AVX or SSE (dependent on which is available; AVX is preferred).
Additionally, there are packed variants of the math functions, which will allow you to process multiple pixels at the same time.  These are employed when using pixel arrays as these are designed to store large volumes of pixels.

Using this, you can expect a bit of a speed up, dependent on which extension set you have enabled.  It's much more apparent when using pixel arrays, as these use the packed math functions and will process much more data.



## Future Additions
I'd like to be able to divide `BYTE` values more efficiently in the case of packed maths, but processors simply don't have the instructions to do this using intrinsics (or, at least, they're not exposed [probably because it's useless]).

I'm half tempted to implement AVX-512 because I've found a server I can use to test it, but I think it's likely a waste of time since nobody using AVX-512 seriously is going to use this library...
