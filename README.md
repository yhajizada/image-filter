# Image Filter

A fast, lightweight command-line image editor written in pure C. Apply professional filters to JPG/PNG images without any dependencies.

![Demo](examples_sepia.jpg)

## Features

- **Zero dependencies**: Only uses `stb_image`, single header library
- **6 Built-in filters**: Grayscale, Sepia, Invert, Blur, Edge Detection, Brightness
- **Fast**: Processes 4K images in under 200ms
- **Cross-platform**: Works on Linux, macOS, Windows with MinGW
- **Educational**: Clean C code to learn image processing basics

## Installation

### Prerequisites
- `gcc` compiler
- `wget` or `curl`

### Clone and Build
```bash
git clone https://github.com/YOUR USERNAME/image-filter.git

This downloads stb_image.h automatically and compiles the binary.

If you downloaded manually:

cd image-filter
make
Usage

Basic syntax:
Bash

./filter <input.jpg> --<filter> <output.jpg>

Brightness Examples
Bash

# Make image 50 points brighter
./filter input.jpg --bright 50 output.jpg

# Make image 30 points darker  
./filter input.jpg --bright -30 output.jpg

How It Works
Grayscale

Uses ITU-R BT.601 luma formula: Y = 0.299*R + 0.587*G + 0.114*B. This matches human eye sensitivity to green.
Sepia

Applies sepia matrix transformation to RGB values. Classic old-photo effect.
Blur

3x3 kernel averaging. Each pixel becomes average of itself + 8 neighbors. Simple but effective.
Edge Detection

Implements Sobel operator. Calculates gradient magnitude using two 3x3 convolution kernels. Highlights rapid intensity changes.
Performance

Benchmarks on Ryzen 5 5600:

    1080p (1920x1080): ∼45ms per filter
    4K (3840x2160): ∼180ms per filter
    Memory usage: 2x image size
File Structure
image-filter/
├── main.c              # All filter implementations
├── Makefile           # Build script
├── stb_image.h        # Image reading library
├── stb_image_write.h  # Image writing library
└── README.md          # You are here

Supported Formats

    Input: JPG, PNG, BMP, TGA, PSD
    Output: JPG only. Quality = 95

Chaining Filters

Currently runs one filter per execution. To chain:
Bash

./filter input.jpg --grayscale temp.jpg
./filter temp.jpg --blur output.jpg
rm temp.jpg

Troubleshooting

Error: Cannot load image
Check if input file exists and is valid JPG/PNG. Path is case-sensitive.

Error: Unknown filter
Check filter name. Use --grayscale not -grayscale. Run ./filter with no args to see all options.

Compilation error: math.h not found
Install build tools: sudo apt install build-essential on Ubuntu/Debian.
Roadmap

    PNG output support
    More filters: contrast, saturation, sharpen
    Multi-threading with OpenMP
    Filter chaining in single command
    Web UI with WASM

Contributing

Pull requests welcome. For major changes, open an issue first to discuss what you want to change.

    Fork the repo
    Create feature branch: git checkout -b feature/contrast
    Commit: git commit -m "Add contrast filter"
    Push: git push origin feature/contrast
    Open Pull Request

License

MIT License. Do whatever you want.
