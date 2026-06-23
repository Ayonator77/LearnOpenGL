# LearnOpenGL Playground

This repo is set up as a small chapter-by-chapter playground for following
[LearnOpenGL](https://learnopengl.com/).

## Running an Exercise

Build the project with the existing CMake preset:

```powershell
cmake --preset msvc
cmake --build --preset debug
```

Run a specific exercise by passing its id:

```powershell
.\build\msvc\Debug\learnopengl.exe 3
```

List available exercises:

```powershell
.\build\msvc\Debug\learnopengl.exe list
```

If no id is passed, `src/main.cpp` uses `kDefaultExercise`.

## Adding the Next Lesson

1. Add the implementation in a new `src/exerciseN.cpp` file.
2. Declare the function in `src/exercise.h`.
3. Add an entry to `kExercises` in `src/main.cpp`.
4. Put reusable OpenGL setup helpers in `src/common.*` only when multiple
   lessons need them.

