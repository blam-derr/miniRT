*This project was created as part of the 42 curriculum by jode-cas and fbenini-*

# 🎨 miniRT - 42 Project

> **"My first RayTracer with MiniLibX"**
> A simplified rendering engine developed in C to explore the world of Ray Tracing and the implementation of mathematical and physical formulas.

---

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

---

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