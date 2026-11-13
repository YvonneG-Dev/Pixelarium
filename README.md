# Pixelarium

Pixelarium is a desktop image viewer built with C++20 and Qt 6. It provides a simple interface for opening and viewing images, with basic image metadata displayed alongside the preview.

## Screenshot

<img width="729" height="499" alt="image" src="https://github.com/user-attachments/assets/d362134c-3752-4ef6-9a5a-0193f2619cb1" />

<img width="729" height="499" alt="image" src="https://github.com/user-attachments/assets/96bdc474-a240-43e4-8921-073ac6cc2a18" />

## Features

* Open images using a file dialog
* Display images while preserving their aspect ratio
* Show image filenames and dimensions
* Switch between light and dark mode

## Technology Stack

* C++20
* Qt 6
* Qt Quick / QML
* CMake

## Architecture

Pixelarium uses an MVVM-inspired architecture.

* **Model**: `ImageInfo` stores image metadata, including the filename and dimensions.
* **ViewModel**: `ImageViewModel` exposes image metadata to the UI through Qt properties and signals.
* **View**: `Main.qml` defines the user interface using Qt Quick and QML.

This separation keeps the presentation layer distinct from the image metadata handling and builds on architectural concepts familiar from my iOS development experience.

## Unit Tests

Pixelarium includes unit tests written with GoogleTest 1.14.0.

GoogleTest is included locally in the repository under `tests/googletest`, so no external download is required during CMake configuration.

The current unit tests cover the `ImageLoader`:

- An empty file path returns an error.
- A non-existent file returns an error.
- A valid PNG image is successfully inspected and its metadata is returned.

The tests are registered with CTest and can be executed from the project root:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Roadmap

- [x] Open an image and show its name and dimensions
- [x] Strict C++20 build setup
- [x] Error handling when an image cannot be loaded
- [x] Separate image loading from the ViewModel
- [x] Initial unit tests for ImageLoader using GoogleTest
- [ ] Unit tests and continuous integration
- [ ] More metadata (file size, format, color depth) and a histogram
- [ ] Image processing with OpenCV (e.g. edge detection)

## Project Status

Pixelarium is a personal learning project under active development. It currently supports image viewing and metadata display, while serving as a practical exploration of modern C++, Qt Quick, and the integration of C++ with QML.

---

**Note**

This is a personal portfolio project. While contributions via pull requests are not currently accepted, feedback and suggestions via GitHub Issues are welcome.
