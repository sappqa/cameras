- linmath mat4x4_mul_vec4 function modifies the result vector passed in while reading from the input vector.
    - so, don't pass in the same vector for the result and the input, it will corrupt the data.


- arcball camera bugs:
    - camera distance was getting closer and closer to the cube and eventually the camera would get stuck, rotation looked like diagonal wobbling/rolling.
        - this was fixed by normalizing _orientation after applying the mouse drag rotation to it in arcball_camera_rotate.
        - dragging left then dragging right would rotate left first, then when dragging right, would still rotate left, then eventually start rotating right
            - originally I wanted to keep the original mouse down point the same and only update it on left click, but since the rotation axis is determined by the cross
            product of the start and current mouse point projected onto the sphere, even though I was moving the mouse to the right, the current position was still to the left of where I started on mouse down, so the cross product didn't change the axis of rotation.
    - cross product order matters. when using a linear algebra library, you should test which parameter order it is using. But with that said, mathematically, the cross product uses the right hand rule, that is always the same regardless of your coordinate system. Right vs left handed coordinate system is a separate thing.
    - be careful whether your scene is using a right or left handed coordinate system, eg: if your camera base position before any orientation/rotation applied is <0,0,-10> and the camera target is the origin, you will run into issues if you're mapping ndc to a unit sphere and using positive z. You would be mapping to the wrong hemisphere and it will mess with how you compute your rotation axis.
    - when using a linear algebra library, write tests to check whether the rotation calls are rotating cw/ccw.

- Rule of thumb: in a right handed coordinate system, +z points towards you. In a left handed coordinate system, +z points away from you, into the screen.

- in order to debug, click on the cmake extension icon on the left side-bar
    - configure the compiler (I'm using GCC 11.4.0)
    - from the project root, clean cmake `rm -rf build/CMakeCache.txt build/CMakeFiles`
    - from the project root, run `cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -S . -B build -G "Unix Makefiles"`
    - not sure if this is necessary, I had issues with getting the debugger to work when I just built normally using `cmake ..` in the build directory. I'm not sure why those above commands fixed the issue, it just seems like it would be the same thing as removing the build directory and re-running cmake, but that didn't work when I tried it...
- vs code's cmake:Reconfigure shortcut option uses Ninja by default which causes issues if you're using makefiles with cmake.