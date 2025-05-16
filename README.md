# CGMathDemo

This project demonstrates core math concepts foundational to 3D graphics programming, inspired by the **math section** of the book *"Introduction to 3D Game Programming with DirectX 12"* by **Frank Luna**.

## 🎯 Goal

To progressively implement and visualize **all math concepts** covered in the book's math section — including but not limited to vector operations, matrix transforms, coordinate systems, and projection techniques — using OpenGL.

> The current state of the project includes support for 2D and 3D vector math (addition, subtraction, scaling) and visual line rendering in OpenGL. This will grow over time to cover more complex topics.

## 🛠 Technologies Used

- C++17
- OpenGL 3.3 Core
- GLFW (for window creation and input)
- GLEW (OpenGL function loader)
- GLM (math library)
- CMake (cross-platform build system)

## 📂 Project Structure

```
cgmathdemo/
├── include/            # Headers
├── src/
│   ├── main.cpp        # Entry point
│   ├── vector-math/    # Vec2 and Vec3 implementations
│   └── rendering/      # OpenGL rendering logic
├── build/              # CMake build output (not tracked)
└── CMakeLists.txt      # Build configuration
```

## 🧰 Build Instructions

```bash
# Clone the project
git clone https://github.com/yourusername/cgmathdemo.git
cd cgmathdemo

# Create a build directory and generate project
mkdir build && cd build
cmake ..

# Build the executable
make

# Run the application
./cgmathdemo
```

> Ensure `GLFW`, `GLEW`, and `GLM` are installed before building.
