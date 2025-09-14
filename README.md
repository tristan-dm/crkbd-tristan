# Tristan's keyboard layout for Corne 4.1

This repository contains the qmk firmware config for my personal Corne
4.1 keyboard layout.

## Compilation

```bash
qmk compile -kb crkbd/rev4_1/standard -km tristan
```

## Flashing

To flash the keyboard, each half needs to be connected and flashed separately.
It is important to ensure that they are not connected during the flashing and 
that their connection is only separated when neither half is powered.

- For the right half, hold the p button down while plugging in the USB cable.
- For the left half, hold the q button down while plugging in the USB cable.

Run the following commands once you have each half in bootloader mode:

```bash
lsblk  # Identify the correct device (e.g., /dev/sdX)
mkdir -p ~/rp2040
sudo mount /dev/sdX1 ~/rp2040
sudo cp crkbd_rev4_1_standard_tristan.uf2 ~/rp2040/
sudo umount ~/rp2040
```
