//g++ -o raw -I /usr/include/GL -lGL -lX11 raw_opengl_window.c -DGL_GLEXT_PROTOTYPES

#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <unistd.h>
#include <iostream>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define GLX_CONTEXT_MAJOR_VERSION_ARB       0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB       0x2092

typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const int*);

int main (int argc, char ** argv)
{
    Display *display = XOpenDisplay(0);

    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = NULL;

    const char *extensions = glXQueryExtensionsString(display, DefaultScreen(display));
    std::cout << extensions << std::endl;

    static int visual_attribs[] =
    {
        GLX_RENDER_TYPE, GLX_RGBA_BIT,
        GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_DOUBLEBUFFER, true,
        GLX_RED_SIZE, 1,
        GLX_GREEN_SIZE, 1,
        GLX_BLUE_SIZE, 1,
        None
     };

    std::cout << "Getting framebuffer config" << std::endl;
    int fbcount;
    GLXFBConfig *fbc = glXChooseFBConfig(display, DefaultScreen(display), visual_attribs, &fbcount);
    if (!fbc)
    {
        std::cout << "Failed to retrieve a framebuffer config" << std::endl;
        return 1;
    }

    std::cout << "Getting XVisualInfo" << std::endl;
    XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[0]);

    XSetWindowAttributes swa;
    std::cout << "Creating colormap" << std::endl;
    swa.colormap = XCreateColormap(display, RootWindow(display, vi->screen), vi->visual, AllocNone);
    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;

    std::cout << "Creating window" << std::endl;
    Window win = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0, 100, 100, 0, vi->depth, InputOutput, vi->visual, CWBorderPixel|CWColormap|CWEventMask, &swa);
    if (!win)
    {
        std::cout << "Failed to create window." << std::endl;
        return 1;
    }

    std::cout << "Mapping window" << std::endl;
    XMapWindow(display, win);

    // Create an oldstyle context first, to get the correct function pointer for glXCreateContextAttribsARB
    GLXContext ctx_old = glXCreateContext(display, vi, 0, GL_TRUE);
    glXCreateContextAttribsARB =  (glXCreateContextAttribsARBProc)glXGetProcAddress((const GLubyte*)"glXCreateContextAttribsARB");
    glXMakeCurrent(display, 0, 0);
    glXDestroyContext(display, ctx_old);

    if (glXCreateContextAttribsARB == NULL)
    {
        std::cout << "glXCreateContextAttribsARB entry point not found. Aborting." << std::endl;
        return false;
    }

    static int context_attribs[] =
    {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 3,
        None
    };

    std::cout << "Creating context" << std::endl;
    GLXContext ctx = glXCreateContextAttribsARB(display, fbc[0], NULL, true, context_attribs);
    if (!ctx)
    {
        std::cout << "Failed to create GL3 context." << std::endl;
        return 1;
    }

    std::cout << "Making context current" << std::endl;
    glXMakeCurrent(display, win, ctx);

        glClearColor (0, 0.5, 1, 1);
        glClear (GL_COLOR_BUFFER_BIT);
        glXSwapBuffers (display, win);

        sleep(1);

        glClearColor (1, 0.5, 0, 1);
        glClear (GL_COLOR_BUFFER_BIT);
        glXSwapBuffers (display, win);


GLuint VertexArrayID;
glGenVertexArrays(1, &VertexArrayID);
glBindVertexArray(VertexArrayID);

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
   -1.0f, -1.0f, 0.0f,
   1.0f, -1.0f, 0.0f,
   0.0f,  1.0f, 0.0f,
};

// This will identify our vertex buffer
GLuint vertexbuffer;

// Generate 1 buffer, put the resulting identifier in vertexbuffer
glGenBuffers(1, &vertexbuffer);

// The following commands will talk about our 'vertexbuffer' buffer
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

// Give our vertices to OpenGL.
glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
// 1rst attribute buffer : vertices
glEnableVertexAttribArray(0);
glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
glVertexAttribPointer(
   0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
   3,                  // size
   GL_FLOAT,           // type
   GL_FALSE,           // normalized?
   0,                  // stride
   (void*)0            // array buffer offset
);

// Draw the triangle !
glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

glDisableVertexAttribArray(0);

glXSwapBuffers (display, win);


        sleep(10);

    ctx = glXGetCurrentContext();
    glXMakeCurrent(display, 0, 0);
    glXDestroyContext(display, ctx);
}