# TODOs

## Now

## Backlog
- Refactoring
  - Pull SDL stuff into the App class and call it SDLApp
  - Probably still need an SDLContext though, but give it a more focussed set of responsibilities
- Headless mode?
- Use futures rather than using threads directly
- Nicer colours
  - Cubic interpolation over some pre-chosen nice colours?
- Render Mandie on the graphics card!
- Trackpad gestures

## Icebox
- Don't render mandie on the UI thread!
  - Basically I don't know how to effectively do concurrency in modern C++ yet
