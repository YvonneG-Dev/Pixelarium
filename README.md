## Pixelarium

Pixelarium is a desktop image viewer built with C++20 and Qt 6. It provides a simple interface for opening and viewing images, with basic image metadata displayed alongside the preview.

## Screenshot

<img width="701" height="512" alt="image" src="https://github.com/user-attachments/assets/40400733-8986-4354-bffb-0ceecc785b16" />

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

## Project Status

Pixelarium is a personal learning project under active development. It currently supports image viewing and metadata display, while serving as a practical exploration of modern C++, Qt Quick, and the integration of C++ with QML.

---

**Note**

This is a personal portfolio project. While contributions via pull requests are not currently accepted, feedback and suggestions via GitHub Issues are welcome.
