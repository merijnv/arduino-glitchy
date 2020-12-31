# arduino-glitchy

Glitchy LED effect for Arduino and the likes.


## The code

This is a simple piece of code to create the effect of a glichy light. It starts up a bit glitchy, then finally starts
and after a while it will go a bit crazy again.

### The sketch

The sketch depends on the `arduino-timer` library to drive the animiation.
A timer is used to call the update function 100 times a second.

In the example I connect two LEDs to two pins and animate them and let them glitch out a bit.


### Glitch.h

The main animating code is here.

There is a central `_data` array that stores the times (in 100ths of a second) when we toggle the LED.


## The story

I am a fan of (https://youtube.com/nerdforge)[Nerdforge] and in (https://www.youtube.com/watch?v=oeir3Pk0KHU)[one of the videos] Martina
and Hansi created a post apocalyptic scene with a light that is a bit glitchy.

They found that light in some random (fysical) shop in the model train section.

Some people, me included, liked the effect and in a comment I said I could maybe recreate the effect in Arduino IDE code.
That comment got upvoted by a few people and now I finally got round to creating something similar.

Feel free to use it as you like!
And if you add neat features, a merge request would be nice.
 
