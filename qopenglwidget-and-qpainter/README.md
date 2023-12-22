# Demonstration of QPainter error with QOpenGLWidget

The Qt documentation on QOpenGLWidget states that a QPainter class can be used in conjunction with OpenGL functions inside an implementation of paintGL.

At the beginning of paintGL, the QPainter class is constructed. Any OpenGL calls are then wrapped by QPainter::beginNativePainting and QPainter::endNativePainting.

However, as soon as the QPainter and native painting methods are added, the program crashes with the exception "Access violation reading location 0x0000000000000000."

This project was built with CMake on Windows 11 using Qt6.5.3 and msvc 2019.

Without QPainter, the program draws an archimedean spiral on a gradient background.

The MainWindow contains a single Widget of type SubOGLWidget, which inherits from the base class BasedOGLWidget. The base class inherits from QOpenGLWidget and implements paintGL, resizeGL, and initializeGL. Each of these methods performs operations general to all BasedOGLWidgets, then calls a subclass specific method.

The paintGL of BasedOGLWidget will construct a QPainter class if enabled, draw the background, then call implPaintGL which draws the spiral.

# Build without QPainter

Open the project folder in Visual Studio. Visual Studio will detect the CMakeLists.txt and open the project in CMake mode.

Or

Open a terminal in this directory and run the following commands:
```
mkdir build && cd build
cmake ..
cmake --build .
```

Then run the executable:
```
cd Debug
glpainter_ex.exe
```


# Build the project with QPainter

The steps are the same, but you must add the CMake option "-DWITH_PAINTER=ON"

In Visual Studio, right click the glpainter_ex Project in the Solution Explorer - CMake Targets View, and press "CMake Settings for glpainter_ex". This will create and open a CMakeSettings.json file. Under CMake command arguments, type in -DWITH_PAINTER=ON.

Or

In the terminal, add the option as follows:
``cmake .. -DWITH_PAINTER=ON``