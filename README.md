# Snake

[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
[![Powered by raylib](https://img.shields.io/badge/powered_by-raylib-lightgrey.svg)](https://www.raylib.com/)
[![GitHub stars](https://img.shields.io/github/stars/Gitter13/snake?style=social)](https://github.com/Gitter13/snake/stargazers)

A classic Snake game that you probably remember from the early mobile phones! Control a green snake with arrow keys, eat red apples to grow longer, and aim for the highest score shown in the top-left corner. Be careful – colliding with walls or yourself ends the game!

The game is written in C++ using the [raylib](https://www.raylib.com/) library.

## How to play
- **Green snake**: arrow keys ←↑↓→
- **Yellow snake**: keys wasd
###
When one of the snakes dies, the game ends and on the screen you will see who win and in top-left corner the count of apples eaten.<br>
To play another round just press *enter* and to switch between multiplayer and singleplayer press *space*.
## Demo / Screenshots
Examples of Snake gameplay:
<br>
![how the game looks like](screenshot.png)

## Installation & Build

The project requires a **C++ compiler** (e.g., g++, clang, or MSVC) and the **raylib** library.

### Installing raylib
- **Windows**: Download pre-built from https://github.com/raysan5/raylib/releases or use vcpkg: `vcpkg install raylib`
- **Linux**: `sudo apt install libraylib-dev` (Ubuntu/Debian) or your package manager
- **macOS**: `brew install raylib`

### Building the project
```bash
git clone https://github.com/Gitter13/snake.git
cd snake
```
### Compile (examples):
Linux/macOS:
```bash
g++ main.cpp -o snake $(pkg-config --cflags --libs raylib)
./snake
```
Windows (MinGW):
```bash
g++ main.cpp -o snake.exe -lraylib -lopengl32 -lgdi32 -lwinmm
snake.exe
```
