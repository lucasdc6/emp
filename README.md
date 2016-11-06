# emp
A file packager.
This file format is implemented for learning purposes.

## About the format
The header of all files has:
 - Magic: an ASCII code with the characters "EMP"
 - Version: a byte with the short version of the program who packed the file
 - Entries: an unsigned int with the quantity of files packaged (limit of 4294967295 files)
 - Reserved: two field reserved to future functionality

 All the packed files also has an own header with:
 - Size: the size in bytes stored in a unsigned int
 - Date of last modification: the date in epoch
 - Reserved: two field reserved to future functionality
 - Path: the path of the file
 
## Future
I look in the future to add functionality to compress (in .gz format).

## Installing

### Prerequisites
- [Git](https://git-scm.com/)
- [Make](https://www.gnu.org/software/make/)
- [GCC](https://www.gnu.org/software/gcc/)
- [Zlib.h](http://www.zlib.net/)

### Steaps:
```
  $ git clone https://github.com/lucasdc6/emp.git
  $ ./dependences
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
