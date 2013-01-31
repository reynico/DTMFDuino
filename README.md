DTMFDuino receives DTMF tones through a MT8870 integrated circuit who converts the analog audio of tones to a binary code understandable by the microcontroller. The 
microcontroller runs Arduino bootloader and converts the received codes to actions (turn on and off some outputs), also the system has the option to know the current state 
of each output.


First Release Candidate?
------------------------
I think this version can be easily a Release Candidate of the project. I've added a simple timer who counts seconds between the sent digits. If there is a timeout greater than 3 seconds, the array is reseted to 0 to do all the stuff again, this is very important because if you make a mistake when sending digits the system goes in a weird state because the counter was 'moved' one or more places. To avoid this, I reset the counter when the timeout reachs 3 secs.

Features
--------

DTMFDuino allows to manage up to 10 digital-two-state outputs. The workflow of commands are:
First char: *, to initialize parsing.
Second char: 0,1 or 2: 0 disables an output, 1 enables it and 2 checks the state (off/on)
Third char: The number of the output.

So, to power up the second output you need to send: *12. To power off it, *02 and to check if it's on or off: *22.

To-Do
-----
There is too much work to do, but this beta is also very functional.

I need to remove some bugs in the Arduino code to improve the reliability of the system, as you can see, the commands to control the outputs are a three character code, so I'm using a simple counter to count the three characters before send the data to the controller. At this moment I need to add some particular cases when the code is misspelled or is erroneous.

At the electronics part I think is all good, but maybe it needs some improvements.


