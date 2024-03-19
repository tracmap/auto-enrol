This is based on the [usb-rubber-ducky-mouse](https://github.com/jfedor2/usb-rubber-ducky-mouse) repo. The library is unlikely to be changed but we replace the demo script with ones for our use cases, add actually useful instructions and bundle up things that may be required.

We should keep Knox EMM user passwords external to this repo though they are not particularly sensitive without other information.

The Digistump website recommended using Arduino IDE 1.6.5. I think this is just because it auto installed bundled drivers when adding boards but it doesn't matter as the bundled ones seem broken. If you are using Windows and need to install these drivers and they don't install while adding the Digispark AVR boards: find the package in App Data and install it from there or... download the driver ZIP from the [Digistump Github](https://github.com/digistump/DigistumpArduino/releases) which has been copied here. If they fail to install due to certificate issues, you may need to move the system clock back to match the signing certificate of the drivers (16 August 2014 -> 17 August 2015) while installing them.

# Setup Instructions:
 - Install Arduino IDE.
 - Add the Board Manager URL to Arduino IDE preferences: https://raw.githubusercontent.com/digistump/arduino-boards-index/master/package_digistump_index.json
 - Install the Digistump AVR Boards from Boards Manager.
 - Install drivers on Windows if the wizard doesn't show up. Linux may be using the CONFIG_CDC_ACM driver which should be enabled by default (add yourself to the dialout group).
 - Select Digispark default 16.5 Mhz (in Tools > Board).
 - Add the TrinketHidComboAbsoluteMouse folder to a ZIP file.
 - Add .ZIP Library... in the IDE (Sketch > Include Library) and select your created ZIP.

[Other info including permissions stuff that should be improved before using](https://startingelectronics.org/tutorials/arduino/digispark/digispark-linux-setup/) (just add yourself to the dialout group or similar)...

# Usage Instructions:
 - The Digistump board only exposes the bootloader for 5 seconds upon powering up before running user code after which point you can't program it.
 - Only connect the board after you have pressed upload in the Arduino IDE and it is awaiting your board to be connected in the console.
 - I don't think anything showed up in `/dev` while I was using it in Linux but I did see `Digispark Bootloader` in `Windows Device Manager`.
 - The program is not aware of the keyboard layout.
 - You may have issues if your USB port is loose.
 - Mouse positions are absolute 0 -> 0x7FFF for X and Y no matter the resolution.
