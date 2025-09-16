<h1 align="center"> 
	miniRT
</h1>

<p align="center">
	<img src="https://img.shields.io/badge/Language-C-blue?style=flat-square"/>
	<img src="https://img.shields.io/badge/Graphics-MiniLibX-orange?style=flat-square"/>
	<img src="https://img.shields.io/badge/Project-miniRT-green?style=flat-square"/>
</p>

**miniRT** is a **computer graphics** project developed in C, implementing a **mini ray tracer** capable of rendering 3D scenes from simple descriptions. It’s a key project at 42 that introduces the fundamentals of graphics programming, ray tracing mathematics, and how to represent 3D objects in a 2D image.

## › Features
- 🌍 Render 3D scenes using **basic ray tracing**
- 💡 Support for **ambient** and **point lights**
- 🔷 Supported objects: **spheres, planes, cylinders**
- 🖼️ Image rendering in a window using **MiniLibX**
- 🖱️ User interaction (window closing, event handling)
- 📜 Scene parsing from **.rt files**
- 🎨 Color, vector, and normal handling
- 🛑 Error handling and robust parsing

## › Project Overview
<p align="center">
	<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/d/d0/Ray_trace_diagram.svg/512px-Ray_trace_diagram.svg.png" alt="Ray Tracing" width="300"/>
</p>

In this simulation:
- A **ray** is cast from the camera through each pixel of the screen.
- **Intersections** with scene objects are calculated.
- An **illumination model** is applied to determine the final color.
- The result is a **rendered image** in real time.
## › .rt Scene Files

The scene is described in a `.rt` file, with elements such as:
- **A**: ambient light  
- **C**: camera  
- **L**: point light  
- **sp**: sphere  
- **pl**: plane  
- **cy**: cylinder  

```Example:
A 0.2 255,255,255
C 0,0,0 0,0,1 70
L 10,0,0 0.7 255,255,255
sp 0,0,20 20 255,0,0
pl 0,0,0 0,1,0 255,255,255
cy 50,0,20 0,1,0 14.2 21.42 10,0,255
```
## 📫 Contact

Feel free to reach out or check out more of my work:

[<img src="https://img.shields.io/badge/LinkedIn-0077B5?style=flat-square&logo=linkedin&logoColor=white"/>](https://www.linkedin.com/in/aitor-guinea-961635348/)  
[<img src="https://img.shields.io/badge/GitHub-aguinea1-black?style=flat-square&logo=github"/>](https://github.com/aguinea1)  
[<img src="https://img.shields.io/badge/Email-guineaitor36@gmail.com-red?style=flat-square&logo=gmail&logoColor=white"/>](mailto:guineaitor36@gmail.com)

