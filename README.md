# stb-cut
Utility for cut images on satellite's Raspberry Pi, based on stb_image lib. Developed for work on satellite's Raspberry Pi

## Setup

### Clone repo
```shell
$ git clone git@github.com:zdrvzbl/stb-cut.git
```

### Install dependencies

Build dependencies:
```shell
$ sudo apt install build-essential cmake
```
Cross-compiling toolchain if you need: https://github.com/zdrvzbl/rpi-crosscompile-template#setup

### Configure

```shell
$ cmake --preset <linux-default | linux-arm> .

```
### Build

```shell
$ cmake --build <build/default | build/rpi>
```

### Install

```shell
$ cmake --install <build/default | build/rpi>
```

CMake install command copies binary and script to `~/bin` or `{projectDir}/rpi-install/bin` in depend of chosen preset

## Usage

The `-s` and `-d` options specify the paths to the source image and the result. `-q` option sets quality of output image in percents. Cutting area coords are non-option parameters and take place after all options and `--` delimeter

```shell
stb-cut -s image_in.jpg -d image_out.jpg -q 90 -- 25 25 75 75
```


## Structure

- `stb_{name}` - [stb_image](https://github.com/nothings/stb.git) headers
- `main.cpp` - CLI program
- `scripts/cut.sh` - Script for cutting pieces from photos on satellite's RPi

## TODO
- cutted photo to archive
- make cut.sh silent