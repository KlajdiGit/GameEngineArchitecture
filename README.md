# Game Engine Architecture

## Overview
This project is a C++ game engine designed to simulate the core systems used in real‑time applications. Its primary purpose is to demonstrate how an engine can manage diverse data types, apply logic to graphical elements, and coordinate multiple subsystems to deliver a smooth experience.

The engine processes external assets such as 2D textures and audio files to render graphics, play sounds, and control gameplay behavior. Its architecture is built around modular components such as Input, Audio, Physics, Data, Graphics, and File Management cores, allowing each subsystem to operate independently while keeping the overall structure easy to maintain and debug. Design patterns are applied throughout to support efficient memory usage, scalable data handling, and a clean separation of concerns.

## Features
Each module is designed with scalability and maintainability in mind, using design patterns, custom data structures, and efficient memory strategies to ensure a good performance that meets real-time requirements. The architecture emphasizes clean separation of responsibilities, allowing the engine to load assets, process input, update game logic, simulate physics, and render frames in a coordinated and extensible pipeline. Together, these systems demonstrate how a modern engine manages complex data flow while keeping debugging and feature expansion straightforward.

- **Memory Management**  
Implements structured allocation and deallocation strategies using design patterns such as singletons, controllers, object pooling and resource managers. Ensures predictable memory usage, reduces fragmentation, and centralizes ownership of engine‑level resources.
- **State Machines**  
  Provides hierarchical and modular state machine logic for both global game states and per‑entity behavior. Enables clean transitions, isolated logic blocks, and easy debugging of state‑driven systems.
- **Physics Core**  
  Handles object movement, velocity updates, collision detection, and basic physical interactions. Integrated directly into the update loop to ensure consistent simulation timing and deterministic behavior across frames.
- **Audio Management**  
  Dedicated subsystem for loading, caching, and playing sound effects triggered efficiently to sync with the AI characters for a proper experience. This project supports only WAV files and with if we try to use other file types, the engine will communicate to the user that it cannot support that file type.
- **Input Management**  
  Unified interface for keyboard, mouse, and Xbox controller input. Abstracts device differences into a consistent API, enabling gameplay logic to react to input events without worrying about hardware‑specific details.
- **Graphics Core**  
  A 2D rendering pipeline built on OpenGL, supporting textures, sprite sheets, animations, transformations, and batching. Includes utilities for rendering TGA images, fonts, and layered visual elements. Designed to efficiently draw multiple objects per frame while keeping GPU calls minimal.
- **Data Management**  
Structured asset loading system capable of reading textures, audio files, binary resources, and serialized data. Centralizes asset access through controllers to reduce duplication, improve debugging, and maintain clean resource lifecycles.

## Technologies Used
Technologies used in this project:
- **OpenGL**: Rendering pipeline for 2D graphics
- **GLM**: Math library for vectors, matrices and transformations
- **SDL**: Input handling, window management and controller support

## Installation
Feel free to clone the repository by using the Code button or by downloading the zip file and open the solution in Visual Studio 2022

## Important
Make sure to run the project in x64 mode. The engine does not support x86 builds.

