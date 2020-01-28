# agPixel
Lightweight library which provides char, float, and double representation of pixels, for use in all kinds of applications from image libraries to raytracing.  

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
The library has limited support for AVX2 and SSE2.  If you toggle `ENABLE_EXTENSIONS` in CMake, the program
will first detect which extensions are available, then attempt to build using them.
Using this, you can expect a bit of a speed up, dependent on which extension set you have enabled.  It's much more apparent when using pixel arrays.

Additionally, there are packed variants of the math functions, which will allow you to process multiple pixels
at the same time.  These are employed when using pixel arrays as these are designed to store large volumes of pixels.

## Future Additions
I would like to find some way to multiply BYTEs more efficiently.  At the moment, the packed variants of `Mul` and `Div`
just run the code for a regular `Mul` or `Div` several times in a row.  Whilst this is theoretically still more efficient
as the processor is already in AVX mode, I feel it could be better optimised.  AVX-512 would help, but only by allowing
me to ram more 32-bit values into one operation.  And I'd have to borrow a server to test that.
