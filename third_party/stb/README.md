
# stb_image

Vendored copy of `stb_image.h`, a single-file public domain image loader by Sean Barrett.

- **Source:** https://github.com/nothings/stb
- **Commit:** 2c980bb59875b0d32144a71867fbdebb2f77cd20
- **Version:** 2.30
- **License:** MIT (alternative A in the file). The file offers a choice between MIT and Public Domain (Unlicense). The full license text is at the end of `stb_image.h`.

## Usage in Pixelarium

Used later by `ImageLoader` to read image dimensions and channel count without decoding the full image. The implementation is enabled in exactly one translation unit (`ImageLoader.cpp`) via `STB_IMAGE_IMPLEMENTATION`.

## Notes

- The file is kept unmodified, so it can be compared against the commit above.
- To update, replace the file from a newer commit and update the commit and version here.
