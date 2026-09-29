# RGB ↔ HLS ↔ CMYK Color Converter

A **WPF desktop application built with C# and .NET 8** for interactive color manipulation and conversion between the **RGB, HLS, and CMYK** color models.

The project was developed as part of a **Computer Graphics** laboratory course.

## Features

* Work with three color models:

  * **RGB** — Red, Green, Blue
  * **HLS** — Hue, Lightness, Saturation
  * **CMYK** — Cyan, Magenta, Yellow, Key (Black)
* Automatic synchronization between all color models.
* Manual value input through text fields.
* Interactive value adjustment using sliders.
* Real-time color preview.
* Color selection through the Windows system color picker.
* Multiple RGB → CMYK separation algorithms:

  * **Naive**
  * **UCR** — Under Color Removal
  * **GCR** — Gray Component Replacement
* Adjustable UCR and GCR strength.
* Separate, WPF-independent project for color conversion logic.
* Automated checks for mathematical color conversions.

## Architecture

The project separates the mathematical logic from the user interface:

```text
src/
├── lab1.Core/              # Color conversion logic
│   └── Models/
│       ├── HlsConverter.cs
│       ├── CmykConverter.cs
│       └── ColorMathTests.cs
│
└── lab1/                   # WPF application
    ├── MainWindow.xaml
    ├── MainWindow.xaml.cs
    │
    └── ViewModels/
        ├── MainViewModel.cs
        └── RelayCommand.cs
```

### `lab1.Core`

Contains the core mathematical logic independently of WPF:

* RGB ↔ HLS conversion
* RGB ↔ CMYK conversion
* Naive, UCR, and GCR color separation
* Mathematical conversion tests

The core project has no dependency on the WPF UI, making the conversion algorithms easier to test, reuse, and extend.

### `lab1`

The main WPF application.

The UI follows the **MVVM (Model–View–ViewModel)** pattern:

* `MainWindow.xaml` — user interface
* `MainViewModel` — application state and UI interaction logic
* `RelayCommand` — commands for user actions

Property synchronization is implemented using **`INotifyPropertyChanged`** and WPF data binding.

When a color component is changed, the ViewModel recalculates the corresponding representations and notifies the UI:

```text
User Input
    │
    ▼
MainViewModel
    │
    ├──► RGB ↔ HLS
    │
    └──► RGB ↔ CMYK
            │
            ▼
      PropertyChanged
            │
            ▼
        WPF Binding
            │
            ▼
        Updated UI
```

The ViewModel also prevents recursive updates when multiple color models are synchronized.

## Color Conversion

### RGB ↔ HLS

The application supports conversion between RGB and HLS, including calculation of:

* Hue
* Lightness
* Saturation

Both conversion directions are implemented.

### RGB → CMYK

RGB-to-CMYK conversion supports several color separation methods.

#### Naive

A basic conversion from RGB to CMYK without additional gray component removal.

#### UCR

**Under Color Removal** reduces the amount of CMY in darker areas and transfers part of the neutral component to the black channel.

#### GCR

**Gray Component Replacement** replaces the gray component of CMY with the black channel over a wider range.

Both UCR and GCR provide an adjustable strength parameter, allowing different CMYK representations of the same RGB color to be explored.

## Testing

The mathematical conversion logic is tested independently of the WPF interface.

Tests are located in:

```text
lab1.Core/Models/ColorMathTests.cs
```

The tests cover:

* RGB ↔ HLS conversions
* RGB ↔ CMYK conversions
* Round-trip conversions
* Boundary values
* Different CMYK separation algorithms

Keeping the conversion logic separate from the UI makes it possible to verify the mathematical part of the application independently.

## Requirements

* Windows
* [.NET 8 SDK](https://dotnet.microsoft.com/download/dotnet/8.0)
* Visual Studio 2022+ with the **.NET desktop development** workload

## Getting Started

### Visual Studio

1. Clone the repository.
2. Open `lab1.sln`.
3. Set `lab1` as the startup project.
4. Run the application with **F5**.

### Command Line

```bash
cd src/lab1
dotnet run
```

The executable is generated at:

```text
src/lab1/bin/Debug/net8.0-windows/lab1.exe
```

## Project Structure

```text
rgb_hls_cmyk_converter_lab1/
│
├── src/
│   ├── lab1.Core/
│   │   └── Models/
│   │       ├── HlsConverter.cs
│   │       ├── CmykConverter.cs
│   │       └── ColorMathTests.cs
│   │
│   └── lab1/
│       ├── MainWindow.xaml
│       ├── MainWindow.xaml.cs
│       └── ViewModels/
│           ├── MainViewModel.cs
│           └── RelayCommand.cs
│
├── lab1.sln
├── report_lab1.docx
└── README.md
```

## Technologies

* **C#**
* **.NET 8**
* **WPF**
* **MVVM**
* **Data Binding**
* **INotifyPropertyChanged**
* **RGB / HLS / CMYK**
* **UCR / GCR**

