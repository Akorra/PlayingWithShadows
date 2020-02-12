# Playing with Shadows
## XCode setup
### Brew Install
    - glm;
    - glew;
    - glfw;
    - sdl2;
    - assimp;

### Build Settings
  - Add to "Header Search Paths" the following paths:
    - "/usr/local/include";
    - "/usr/local/Cellar/glm/0.9.9.5/include";

### Build Phases
  - Add to "Link Binary With Libraries":
    - "OpenGL.framework";
    - "/usr/local/Cellar/glew/2.1.0_1/lib/libGLEW.2.1.0.dylib";
    - "/usr/local/Cellar/glfw/3.3.2/lib/libGLFW.3.3.dylib";
    - "/usr/local/Cellar/sdl2/2.0.10/lib/libSDL2-2.0.0.dylib";
    - "/usr/local/Cellar/assimp/5.0.1/lib/libassimp.5.0.0.dylib";

  if you cant find the /usr directory on your MAC press "command"+"shift"+"G" and enter "/usr"
