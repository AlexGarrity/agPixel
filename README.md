# libPixel
Tiny library which provides char and float representation of pixels.  
I made this because I fancied making an image library, but then I realised that pixels are really fun.  
So now it's a pixel library instead.  

## Building
I've only tested this on Ubuntu, and I have little (no) experiene with CMake, so I have no idea if this will work.  
I'm pretty sure it doesn't work on Windows (yet).  

But, otherwise, just this in the root directory...
```bash
cmake .
make
make install
```

And that should automagically install it.  

## Coming Soon
*I make no promises, you can see the commit history in my other projects*
- HSL representations of pixels
- More operator overloads
- Built-in pixel array type for representing images
- Some other things that might be useful for pixels (that I need to research)