# Airport OpenGL Simulation

A 2D airport runway simulation built with C and OpenGL (GLUT), featuring an animated plane that takes off and lands, a fully modeled airport building with a control tower, and a set of dynamic visual effects.

## Features

- **Plane animation**: takeoff and landing sequence with acceleration, wheel retraction/deployment, and looping flight cycles
- **Airport building**: main terminal with windows, entrance, control tower, and an "AIRPORT" sign
- **Runway**: lane markings and edge lights
- **Effects Module** (by Joory):
  - Animated clouds drifting across the sky
  - Day/night cycle with automatic and manual toggling
  - Blinking runway edge lights
  - Waving flags near the runway
  - Rotating radar dish on a tower

## Controls

| Key | Action |
|-----|--------|
| `↑` Arrow Up | Increase plane speed |
| `↓` Arrow Down | Decrease plane speed |
| `Space` | Take off (once at max speed) |
| `N` | Manually toggle day/night mode |
| `R` | Reset the simulation |
| `Esc` | Exit the program |

## Requirements

This project uses the **OpenGL** and **GLUT** libraries. Make sure they're installed before compiling.

## How to Compile & Run

**Windows (MinGW):**
```bash
gcc airport_simulation_joory_v5.c -o airport_sim -lglut32 -lglu32 -lopengl32
airport_sim.exe
```

**Linux:**
```bash
gcc airport_simulation_joory_v5.c -o airport_sim -lglut -lGLU -lGL
./airport_sim
```

**macOS:**
```bash
gcc airport_simulation_joory_v5.c -o airport_sim -framework OpenGL -framework GLUT
./airport_sim
```

## Project Structure

This was a collaborative team project, with each member owning a specific module:

- **Sky & Effects Module** — Joory (clouds, day/night cycle, runway lights, flags, radar)
- **Runway Module**
- **Airport Building Module**
- **Plane Module**
- **Animation Module**
- **Keyboard Input Module**

## License

This project was created for academic purposes.
