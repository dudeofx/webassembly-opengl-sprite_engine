# webassembly-opengl-sprite_engine
A simple but capable sprite engine written on WebGL. Features live rotation and scaling. 

Not quite a game engine but its a good solid start. Proof of concept work.

## Quick Start
Run build.sh to compile the example. This will create three files: index.data, index.js and index.wasm.
To see the example run publish all the index.* files (4 total) into a subdirectory in your webserver.

## Developer notes
Things I would have done differently would be to use pointers instead of memory copies when submitting sprites, then I could a quick Z-sort before rendering.

I originally planned to support translucent sprites but I kept running into blending errors. I tried the pre-multiplied alpha technique. That got rid of most of the errors but as you can see on the girl walking, there are still some blending errors arround her hair.
