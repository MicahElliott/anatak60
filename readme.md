# Anatak60 Keyboard Layout

This is an upside-down variant of Katana60.

![Anatak60](anatak1.png?raw=true "Anatak60")

## Usage

```
git clone https://github.com/qmk/qmk_firmware ~/src
cd ~/src/qmk_firmware/keyboards/rominronin/katana60/rev2/keymaps
git clone https://github.com/micahelliott/anatak60
cd ~/src/qmk_firmware
qmk flash -kb rominronin/katana60/rev2 -km anatak60
```

## About

I needed a symmetric staggered keyboard that would aid with
same-finger utilization (SFU).

## Acquiring, Setup

1. Order a [Katana60 board from Candykeys](https://candykeys.com/product/katana60-pcb-V2).
1. You can’t get the plate, but it’s not actuall needed.
1. Solder switches of your choosing (better if PCB-mountable since no plate).
1. Put on some caps.
1. Set up [QMK firmware](https://github.com/qmk/qmk_firmware).

## Caveats

- This layout will undergo some tweaks.
- The keymap.c file is upside-down and backwards, could maybe do some
  work to fix that.
