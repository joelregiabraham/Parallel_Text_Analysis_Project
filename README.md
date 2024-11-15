# Parallel Text Analysis Project

## Project Description
This is a parallel computing project that performs word counting analysis on a large text file using C++ and Boost libraries, demonstrating parallel processing techniques.

## Prerequisites

### Software Requirements
- Visual Studio 2022
- Boost C++ Libraries (version 1.86.0)
- 7-Zip (optional, but recommended for extraction)

### Hardware Requirements
- 64-bit Windows system
- Minimum 8GB RAM recommended
- Multi-core processor

## Boost Library Setup

### Download Boost
1. Visit the official Boost website: https://www.boost.org/users/download/
2. Download the latest Boost library (used version: 1.86.0)
3. Extract the downloaded .7z file to a convenient location

### Building Boost Libraries

#### Using Command Prompt
1. Open Developer Command Prompt for VS 2022
2. Navigate to Boost root directory
3. Run bootstrap configuration:  .\bootstrap.bat
4. Build Boost Thread Library:  b2.exe --with-thread --toolset=msvc-14.3 address-model=64 link=static runtime-link=shared threading=multi


### Visual Studio Configuration

#### Include Directories
1. Right-click project in Solution Explorer
2. Select "Properties"
3. Go to C/C++ > General > Additional Include Directories
4. Add Boost root directory path (e.g., `E:\boost_1_86_0`)

#### Library Directories
1. In the same Properties window
2. Go to Linker > General > Additional Library Directories
3. Add Boost library stage path (e.g., `E:\boost_1_86_0\stage\lib`)

## Project Setup

### Required Files
- `main.cpp`
- `word_counter.h`
- `word_counter.cpp`
- `Hamlet.txt` (input text file)

### Compilation Notes
- Ensure project is set to x64 configuration
- Use Visual Studio 2022 with C++17 or later standard

## Troubleshooting

### Common Issues
1. **Linker Errors**: 
- Verify Boost library paths
- Confirm library files exist in specified directory
- Ensure matching architecture (64-bit)

2. **Runtime Errors**:
- Check `Hamlet.txt` file location
- Verify file permissions


   
