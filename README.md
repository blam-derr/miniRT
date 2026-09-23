*This project was created as part of the 42 curriculum by fbenini- and jode-cas*

# 🎨 miniRT - 42 Project

> **"My first RayTracer with MiniLibX"**
> A simplified rendering engine developed in C to explore the world of Ray Tracing and the implementation of mathematical and physical formulas.

---
[![Norminette](https://github.com/blam-derr/miniRT/actions/workflows/norminette.yml/badge.svg?branch=main&event=push)](https://github.com/blam-derr/miniRT/actions/workflows/norminette.yml)

## 🚀 Description

**miniRT** is a 3D image rendering software that uses the **Ray Tracing** technique. Developed entirely in **C**, the main goal of this project is to implement the fundamentals of computer graphics and optical physics, allowing the generation of scenes with simple geometric shapes, lighting systems, and camera projections.

Unlike traditional rasterization, Ray Tracing simulates the physical path of light to produce a higher degree of visual realism, including shadows and diffuse lighting.

### 🛠️ Key Technologies and Concepts
* **C Language** (Following the 42 Norm)
* **MiniLibX:** A simple graphics library for window management and pixel rendering.
* **Analytical Geometry:** Ray-object intersections (spheres, planes, and cylinders).
* **Basic Optics:** Ambient and diffuse lighting (Lambertian reflectance).
* **File Management:** Robust parsing of `.rt` configuration files.

---

## ⚙️ Implemented Features

### 🔹 Mandatory Part
- [x] **Primitive Rendering:** Support for planes, spheres, and cylinders.
- [x] **Camera:** Free positioning, orientation via vectors, and adjustable FOV.
- [x] **Lighting:** Ambient light and point lights with hard shadows.
- [x] **Interface:** Window management and event handling (ESC and window close button).
- [x] **Parsing:** Strict validation of `.rt` scene files.

### 🔹 Bonus Part

- [x] **Multi-spot light:** Support for multiple light spots in a single scene.
- [x] **Texture and color disruption:** Texture rendering for meshes.
- [x] **.obj mesh support:** Parsing and rendering of objects in the wavefront file format.
- [x] **Specular reflection:** Recursive reflection, resulting in a mirror like surface.

## 🛠️ Instructions

### **Prerequisites**
The project depends on **MiniLibX** and the math library `math.h` (`-lm`).

```bash
# Clone the repository
git clone git@github.com:blam-derr/miniRT.git

# Enter the directory
cd miniRT

# Compile the project
make

# Run the program with an example scene
./miniRT scenes/mandatory_scene.rt

## 📚 Resources

Learning resources that helped us while doing this project

- [Moller-Trumbore Intersection algorhitm page on wikipedia](https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm)
- [Acceleration Structures and BVH on Scratchapixel](https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-acceleration-structure//bounding-volume-hierarchy-BVH-part1.html)
- [Ray Tracing in One Weekend](https://raytracing.github.io/)
- [pbrt.org](https://pbr-book.org/4ed/contents)
