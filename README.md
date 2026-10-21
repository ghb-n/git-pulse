# git-pulse 🚀

A blazing-fast, modern C++ local workspace manager and Git status scanner designed for Linux and Wayland environments.

## Features

- **Lightning-Fast Scanning**: Recursively crawls directories using `std::filesystem` to find local Git repos in milliseconds.
- **Status Tracking**: Instantly identifies uncommitted changes, staged files, and ahead/behind commit counts.
- **Modern C++**: Built with RAII, smart pointers, and zero bloat.

## Building from Source

```bash
mkdir build && cd build
cmake ..
make
```
