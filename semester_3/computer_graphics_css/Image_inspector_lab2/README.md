# Image Inspector

A **WPF desktop application built with C# and .NET 8** for scanning image files and displaying technical information about their formats, dimensions, color depth, resolution, and compression.

The project was developed as part of a **Computer Graphics** laboratory course.

## Features

- Scan images from a selected folder.
- Recursive scanning of subfolders.
- Multithreaded image processing.
- Support for:
  - **BMP**
  - **PNG**
  - **JPEG**
  - **GIF**
  - **TIFF**
  - **PCX**
- Automatic image format detection.
- Display:
  - Image dimensions
  - Color depth
  - Resolution
  - Compression
  - File size
- Image preview.
- Animated GIF preview.
- File name filtering.
- Progress tracking and scan cancellation.
- Export scan results to CSV.
- Drag & drop folder support.

## Architecture

The application is logically divided into three layers:

```text
Core / Business Logic Layer
        │
        ▼
Data / Parsing Layer
```

### Core / Business Logic Layer

Responsible for:

- Folder scanning
- Multithreaded file processing
- Progress tracking
- Scan cancellation
- Filtering results

The scanning logic is currently implemented in `MainWindow.xaml.cs`.

### Data / Parsing Layer

`Parser.cs` contains the binary parsing logic for supported image formats.

It detects the format from the file header and extracts technical information without loading the entire file.

Supported formats:

- BMP
- PNG
- JPEG
- GIF
- TIFF
- PCX

## Image Parsing

The application reads image headers and extracts format-specific information such as:

- Width and height
- Color depth
- Resolution
- Compression method
- Palette information when available

Binary values can be read using both little-endian and big-endian byte order.

## Multithreading

Image files are processed in parallel using the **Task Parallel Library**.

```text
Selected Folder
      │
      ▼
Find Image Files
      │
      ▼
Parallel Processing
      │
      ▼
Parse Image Headers
      │
      ▼
Display Results
```

`CancellationToken` is used to stop an active scan.

## Project Structure

```text
ImageInspector/
│
├── MainWindow.xaml
├── MainWindow.xaml.cs
├── Parser.cs
├── App.xaml
├── App.xaml.cs
└── ImageInspector.csproj
```

## Technologies

- **C#**
- **.NET 8**
- **WPF**
- **XAML**
- **Task Parallel Library**
- **Multithreading**
- **Binary file parsing**
- **BMP / PNG / JPEG / GIF / TIFF / PCX**