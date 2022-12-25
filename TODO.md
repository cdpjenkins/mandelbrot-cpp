# TODOs

- freeing obj that wasn't malloc-ed on exit:
  - I bet it's because there are now two instances of SDLContext whereas there should only be one :-/
  - Something something std::move something...
  - Or only instantiate one...
  ```
  mandelbrot(16797,0x1050f8580) malloc: *** error for object 0x148008000: pointer being freed was not allocated
  mandelbrot(16797,0x1050f8580) malloc: *** set a breakpoint in malloc_error_break to debug
  Abort trap: 6
  ```
- Split up SDLContext
  - SDL stuff stays
  - Application class that owns config, mandie etc
- Re=initialise Mandie when window is resized
  - Also re-init the aspect ration shizzle
- Command line params for:
  - Initial coords
  - Initial zoom
