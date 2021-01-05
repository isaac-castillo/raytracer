This is a raytracer built in CPP.

To use you must have the FreeImage library. 

You can get it from https://freeimage.sourceforge.io/

Make sure that FreeImage is in the system library path! (Else you will get linker issues)

Then do the following:

`cmake .`

`make`

Running:

`./raytracer scenes/scene0.test`

Or, to test:

`./raytracer_test`
