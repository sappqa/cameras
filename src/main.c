#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "common.h"
// #include "render_window.h"

int main(int argc, char** argv) {
    #ifdef USE_ARCBALL_CAMERA
    printf("USING ARCBALL\n");
    #else
    printf("not using arcball\n");
    #endif
    // render_window();
    exit(0);
    
}