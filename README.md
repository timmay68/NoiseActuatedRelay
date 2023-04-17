# NoiseActuatedRelay
Micrphone monitors room noise, if noise threshold is exceeded a relay is actuated.


Objective is to later the noise threshold using a rotary encoder.
I have managed to achieve this by placing the //encoder  //end encoder contecnt into the loop function, but I a told it is better coding to place it in an ISR.
When I do this, it does not work.
I have tested the encoder for left, right and sw and it works fine.
I spent hours trying to understand why it wont work.

The rotary code I have used is not essential, if there is more efficient code thats fine.

To the user, the encoder is basically adjusting the mic sensitivity.

Second point; I also dont fully understand how I mapped the encoder to the thresholdLevel, I am not sure what command told it to adjust it, it just worked.

"NoiseActuatedRelay.ino" is file I am trying to fix
