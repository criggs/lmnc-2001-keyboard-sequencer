# lmnc-2001-keyboard-sequencer

Module: https://www.lookmumnocomputer.com/2001keyboardsequencer
Original code: https://www.lookmumnocomputer.com/s/2001_KEYBOARD_SEQUENCER-22.ino

This is a modified version of the sequencer code for the LMNC 2001 Keyboard Sequencer.

If using an older sequencer module, the 10-20M common capacitor trace will need to be cut and sent to ground (before the cut the trace is connected to 5V).

This version adds an arpeggiator so you can hold down multiple pads at the same time.

You might need to adjust the values in threshold array at the top.

I also reduce the threshold when 3 or more fingers are detected, as i saw the input value decrease with each finger but you milage may vary. I still have some experimentation to do to see if this is specific to my module.
