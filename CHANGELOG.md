# Change Log
All notable changes to this project will be documented in this file.

## [Unreleased]
### Added
- compress function (not functional)
- silent mode
- magic is recognized by file command (__only tested in linux__)
 
### Changed
- makefile now add the magic configuration in /etc/magic
- changed the file associated by the stderr in silent mode

### Fixed
- The file_exist function now admit more than 10 repetitions

## 0.2 - 2016-08-29
### Added
- The program create the file "ERRORS[yyyy-mm-dd-H:M:S]" with the last error (in silent mode)

### Changed
- The error messages printed in the stderr

### Fixed
- Errors in the packed and unpacked function

## 0.1 - 2016-08-02
### Added
- Man pages
- function packaging directory
- README.md
