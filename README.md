# emp
[![License: GPL v3](https://img.shields.io/badge/License-GPL%20v3-blue.svg)](http://www.gnu.org/licenses/gpl-3.0)
[![License: Zlib](https://img.shields.io/badge/License-Zlib-lightgrey.svg)](https://opensource.org/licenses/Zlib)
[![Version: v0.2](https://img.shields.io/badge/Version-v0.2-blue.svg)](https://github.com/lucasdc6/emp/releases/tag/v0.2)

A file packager.

## Future
I look in the future to add functionality to compress (in .gz format).

## Installing

[![download 64 bit: 13.4kb](https://img.shields.io/badge/download 64 bit-13.4 kb-red.svg)](https://github.com/lucasdc6/emp/releases/download/v0.2/emp0.2_amd64.deb)
[![download 32 bit: 13.8kb](https://img.shields.io/badge/download 32 bit-13.8 kb-red.svg)](https://github.com/lucasdc6/emp/releases/download/v0.2/emp0.2_i386.deb)

### Prerequisites
- [Make](https://www.gnu.org/software/make/)
- [GCC](https://www.gnu.org/software/gcc/)
- [Zlib.h](http://www.zlib.net/)

### Steaps:

####with Git:

```
  $ git clone https://github.com/lucasdc6/emp.git
  $ make
  $ make install
```
You may need to give sudo permissions.

####Manually:

1- download compressed in [tar](https://github.com/lucasdc6/emp/archive/v0.2.tar.gz) or [zip](https://github.com/lucasdc6/emp/archive/v0.2.zip)

2- In the main directory:

```
  $ make
  $ make install
```
You may need to give sudo permissions.

## Uninstalling

### Steaps
```
  $ make uninstall
```
You may need to give sudo permissions.
