--DESCRIPTION--

This is an interfaced ray tracer engine on MAC OSX Platform (we may support linux platforms later);

Supports:

- lights : ambient, point, parrallel, light box;
- shadows;
- soft shadows with light box;
- refraction;
- reflection;
- transparency;
- 12 shapes (sphere, plane, cone, cylinder, cube, triangle, disk, torus, mobius, hollow cube, hyperboloid, paraboloid);
- perlin noise;
- post-process effects (sepia, black & white, cartoon, pastel, etc);
- anaglyph 3D;
- Clustering;
- XML Parser;
- XML File saver;
- Bitmap saver;
- User Interface;

--DEPENDENCIES--

Latest CUDA Toolkit
SDL2
LibXML2

* You could simply use brew to install dependencies (except CUDA Toolkit) : brew install sdl2, brew install libxml2.

--INSTALLATION--

Compile the project using 'make' command.

To execute the program : './bin/rt' .

--MEDIA--

https://youtu.be/ylTecs2UYDA

--AUTHORS--

Antoine Anzieu
aanzieu@student.42.fr

Stefan VILAU
svilau@student.42.fr

Xavier Pouzenc
xpouzenc@student.42.fr

Hugo Weber
huweber@student.42.fr
