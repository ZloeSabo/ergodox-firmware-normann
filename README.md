# ergodox-firmware-normann

This is the [Ergodox EZ](https://ergodox-ez.com/) firmware. It requires [QMK Firmware](https://github.com/qmk/qmk_firmware) to compile.


* 1st layer - Norman layout
* 2st layer - Mouse
* 3st layer - QWERTY layout

### Prerequisites for building

* Docker
* Git
* Around 550 MB for qmk_firmware (downloaded to the current directory)

### Building

```bash
make -j5
```

If everything went correctly, the firmware would be in the `release` folder.

### Flashing

The easiest way is to use the [Teensy Loader](https://www.pjrc.com/teensy/loader.html). Simply follow the instructions they provide.

### TODOs

* [ ] Stop attempts to recreate `qmk_firmware/keyboards/ergodox_ez/keymaps/zloesabo` on every build
* [ ] Add missing keys to QWERTY layout
* [ ] Tap dance for the functional keys
* [X] Flashing instructions