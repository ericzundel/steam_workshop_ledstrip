# steam_workshop_ledstrip

Eric Z. Ayers <ericzundel@gmail.com>

This project is designed for a 45 minute workshop for 8th grade (13 year old) students at Charles R. Drew Charter School in Atlanta, Georgia USA. If you find this useful in your environment, I would love to hear from you!

The goals of the workshop were:

- To develop enthusiasm among rising high school students
for engineering.
- To get some hands on experience wiring up components
- To get some experience changing a computer program.


- [Student handout](https://docs.google.com/document/d/1-PyozopYgN8l7mBLquPVMcDZ8zSOU5BLg8CazD3vZFc)
- [Assistant handout](https://docs.google.com/document/d/1tJRgG4w04AegT61keKJJrY-u8prtBeywJORsqLRg49g)

## Environment

We made use of laptops with the Arduino IDE installed.  We used Arduino Nano hardware and a NeoPixel LED strip clone.  The strip was driven at 5V and has a single pin for data.  I cut a strip of 5-20 pixels for each  laptop and pre-soldered breadboard wires onto the Neopixels.

## Usage
This directory should be copied into the 'libraries' directory that the Arduino IDE uses so that the headerfile and example file are ready for students to use.

Our environment uses windows laptops and a network with Microsoft OneDrive configured.  I used the instructor account and copied the files in this project to $HOME/OneDrive/Arduino/libraries/steam_workshop_ledstrip

## Philosopy

This is not meant to be an exercise in learning how a computer language works, understanding hardware, or using a canonical computer language.  The workshop was designed so that students could experience success in programming hardware a short time frame. To that end, the example works out of the box. I also used macros to create shortcuts to make additional coding simpler and more forgiving.  Also, I wanted to give enough depth to the exercise so that eager students would not get bored, so there are multiple goodies commented out in the file for students to explore.  At the advice of a student helper, I gave the students the experience of wiring the LED strip to the Arduino in each workshop (even though it was time consuming) to give the students hands on experience.

To inspire students, I tacked up a 100 led strand to the front of the classroom with all of the logic uncommented and turned it on once we finished wiring up the hardware.

In March 2022 I ran this workshop four times with 15-20 students in each workshop and every student got their light strip to work.

## Notes on the code

### steam_workshop_ledstrip.h

This header file is used to create some shortcuts to programming the led strip using the Adafruit_NeoPixel library.

If you are familiar with C++, you might cringe upon reading this header file. As an old C programmer, I made heavy use of the macro pre-processor.  The file mostly consists of static function declarations and macro declarations that pollute the global namespace. I also made it so that using either all upper case or all lower case would work, and planted semicolons in the macros so that a missing semicolon wouldn't trigger a syntax error.

### workshop_example.ino

This is the example program that students used in the workshop.  

In this file, workshop participants could define new colors and experiment with pre-programmed effects. In the verbal instruction, I explained what a comment was and how to define one color and uncomment one effect, then let students explore.
