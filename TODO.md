# TODOs
- Don't render mandie on the UI thread!
  - Blows up if MandelbrotRenderer gets deleted whilst rendering and before we try to copy to the screen!
  - Refactor the SDL custom event code so it _doesn't_ suck.
