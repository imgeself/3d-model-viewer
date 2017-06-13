# Summary
I wanted to make basic OpenGL renderer with cover of all core basics(Drawing, Shaders, Texture, Camera, Lights, etc). 
3d model viewing software great fit for this goal. I started with Gtk+ widgets but I get weird issues and I moved to the QT widgets. 
And I used Assimp library for 3d model loading. I tried to abstract gui and render engine from start. And that help me a lot when I switched from Gtk+ to QT widgets.
For more information and comments I wrote [blog] (Turkish) about this app

# Instructions
- App is simple. You can open 3d model on menu bar. Model loading may take a time depending your model. 
[![image](https://i.hizliresim.com/qW4Z4Q.png)](https://hizliresim.com/qW4Z4Q)

- Left Click and drag for rotate model horizontally.
- Middle Click and drag for rotate model vertically.
- Right Click and drag for move camera.
- Scroll Mouse Wheel for move camera forward and backward.
- Click window in menubar and click settings for opening settings panel. You can make light adjustments in here.
- App supports diffuse and specular maps. But textures must be in same folder as 3d model.
[![image](https://i.hizliresim.com/gWkJkb.png)](https://hizliresim.com/gWkJkb)

- Click edit and enable wireframe 
[![image](https://i.hizliresim.com/Mv6362.png)](https://hizliresim.com/Mv6362)

# Requirements
- QT5 for widgets and build system(qmake).
- GLM-0.9.5 for mathmatics.
- [GLEW-2.0] for OpenGL functions.
- [stb_image] for image loading.
- [Assimp-3.3.1] for 3d model loading.

[blog]: https://havadabirseyvar.wordpress.com/2017/06/13/opengl-ve-rendering/
[GLEW-2.0]: https://github.com/nigels-com/glew
[stb_image]: https://github.com/nothings/stb/blob/master/stb_image.h
[Assimp-3.3.1]: https://github.com/assimp/assimp
