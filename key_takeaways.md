- linmath mat4x4_mul_vec4 function modifies the result vector passed in while reading from the input vector.
    - so, don't pass in the same vector for the result and the input, it will corrupt the data.


- in order to debug, click on the cmake extension icon on the left side-bar
    - configure the compiler (I'm using GCC 11.4.0)
    - from the project root, clean cmake `rm -rf build/CMakeCache.txt build/CMakeFiles`
    - from the project root, run `cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=TRUE -S . -B build -G "Unix Makefiles"`
    - not sure if this is necessary, I had issues with getting the debugger to work when I just built normally using `cmake ..` in the build directory. I'm not sure why those above commands fixed the issue, it just seems like it would be the same thing as removing the build directory and re-running cmake, but that didn't work when I tried it...
- vs code's cmake:Reconfigure shortcut option uses Ninja by default which causes issues if you're using makefiles with cmake.