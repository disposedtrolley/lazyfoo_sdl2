# Lazy Foo SDL2

Following the [SDL tutorials](https://lazyfoo.net/tutorials/SDL/) from Lazy Foo.

## Development

### Prerequisites

- Clang 12
- CMake 3.19

```shell
# Compilation
BUILD_FOLDER=build
C=clang CXX=clang++ cmake -B "$BUILD_FOLDER" -S . -G "Unix Makefiles"
cd "$BUILD_FOLDER" && make

# Execution
./lazyfoo_sdl2
```