# file_signature
A console program for generating the signature of the specified file.

# Usage
```shell
file_signature input_file output_file block_size
```
## Requirements
* C++17
* Boost 1.78.0
* GTest 1.13.0
* CMake 3.5

## Build

```shell
cmake -S ./ -B build_dir -D CMAKE_BUILD_TYPE=Release
cmake --build build_dir
```

## Location
* `file_signature` will be in the `build_dir`
* `test` will be in the `build_dir/test`
