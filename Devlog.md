# Devlog

This readme will be used to log the process of developing the Space Puzzle Matrix. This log should hopefully make our design choices clear and our development process transparent.

## 10/16/25

Today we designed the block diagram for the puzzle matrix, outlining the main components of the system and what connections need to be made to the main board:

![The Space Puzzle Matrix block diagram.](block_diagram.svg)

<!-- Note: For those with access, this is the link to the diagram on draw.io: https://drive.google.com/file/d/1CoTKAC93WJClgrDPM8iDVgEEN2oWHCxh/view?usp=sharing -->

## 11/13/25

We missed a couple of entries, but we are making good progress. We have soldered jumper wires to our button pcb neopixels and are ready to start experimenting with them in `experimental/neopixels/neopixels.ino`. We're going to test addressing them as a matrix using [Adafruit's Neomatrix Library](https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library). Since the final prototype will be on esp32 and this is being tested on an Arduino Nano, this won't be a direct representation of how we interface with them, but it will give us some experience working with them.

We are also working on writing some sample game in C, such as Simon Says, which we will integrate with the button matrix once that is configured.

## 11/19/25

We started interfacing with a sequence of our prototype neopixels. We got them connected in series and began playing around with the Neopixel library in `experimental/neopixels/neopixels.ino`. We got some interesting patterns and behavior to appear and will begin interfacing our neopixels with Brian's simple Simon Says program soon.