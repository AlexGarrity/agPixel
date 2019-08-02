# libPixel
Tiny library which provides char, float, and double representation of pixels.  
I made this because I fancied making an image library, but then I realised that pixels are really fun.  
So now it's a pixel library instead.  

## Building
I've only tested this on Ubuntu, and I have little experience with CMake, but it seems to work.  
I should note that I use CMake GUI because I don't fancy doing it CLI.  
I'm pretty sure it doesn't work on Windows (yet).  

But, otherwise, just this in the root directory...
```bash
cmake .
make
make install
```

And that should automagically install it.  

## Cool Features
The library hase limited support for AVX2.  If you toggle `ENABLE_EXTENSIONS` in CMake, the program
will attempt to build using AVX2 (although it will throw an error if your compiler doesn't support it).  
Using this, you can expect a speedup of ~2x for basic arithmetic operations, based on some limited testing.

## Coming Soon
*I make no promises, you can see the commit history in my other projects*
- HSL representations of pixels
- More operator overloads
- Built-in pixel array type for representing images
- Some other things that might be useful for pixels (that I need to research)