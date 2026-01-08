[README.md](https://github.com/user-attachments/files/24485535/README.md)
# **3D Graphics Engine (OpenGL/C++)**

A modular, Object-Oriented 3D game engine built from the ground up using C++, OpenGL, FreeGLUT, and GLM. This project implements a full graphics pipeline including hierarchical modeling, custom camera controls, the Phong lighting model, and 2D texture mapping.



### **Key Features**



#### Architecture

* **OOP Singleton Engine:** Wraps procedural GLUT C-callbacks into a clean C++ class.
* **Hierarchical Transform System:** Base *GameObject* class managing local space (Translation -> Rotation -> Scale).
* **Vertex Array Rendering:** High-performance drawing using *glDrawArrays* and *glDrawElements.*



#### Graphics Pipeline

* **Phong Lighting Model:** Real-time calculation of Ambient, Diffuse, and Specular light components.
* **Shading Modes:** Support for both Flat and Smooth (Gouraud) shading algorithms.
* **Texture Mapping:** 2D bitmap application with *stb\_image*, supporting various filtering and wrapping modes.
* **Projection Systems:** Instant switching between Perspective (field of view) and Orthographic (parallel) views.



#### Observer \& Interaction

* **Custom Camera:** Observer class utilizing *lookAt* logic for 3D navigation.
* **Input Mapping:** Integration of standard ASCII keys and Special Arrow keys for player movement.



#### Technical Stack

* **Graphics API:** OpenGL (Compatibility Profile).
* **Windowing/Events:** FreeGLUT.
* **Mathematics:** GLM (OpenGL Mathematics).
* **Image Loading:** stb\_image header-only library.







