//////////////////////////////////////////////////////////////////////////////
//
//  Triangles.cpp
//
//////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "LoadShaders.h"
#include "LoadTex.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint  VAOs[NumVAOs];
GLuint  Buffers[NumBuffers];
GLuint  Texture;
GLuint  Time;

const GLuint  NumVertices = 100;

//----------------------------------------------------------------------------
//
// init
//

void
init( void )
{
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    srand((int)time(0));
    GLfloat vertices[NumVertices][2];
    for (int i = 0; i < NumVertices; i++)
    {
        vertices[i][0] = 2.0f * rand() / RAND_MAX - 1;
        vertices[i][1] = 2.0f * rand() / RAND_MAX - 1;
    }

    glCreateBuffers(NumBuffers, Buffers);
    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices),
                         vertices, 0);

    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "triangles.vert" },
        { GL_FRAGMENT_SHADER, "triangles.frag" },
        { GL_NONE, NULL }
    };

    GLuint program = LoadShaders(shaders);
    glUseProgram(program);

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT,
                          GL_FALSE, 0, (void*)(0));
    glEnableVertexAttribArray(vPosition);

    Texture = LoadTex("amazing.png");
    GLuint TextureID = glGetUniformLocation(program, "myTextureSampler");
    glUniform1i(TextureID, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Texture);

    Time = glGetUniformLocation(program, "time");

}

//----------------------------------------------------------------------------
//
// display
//

void
display( void )
{
    
    static const float black[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    static const clock_t time = clock();
    clock_t time_frame = clock();
    float delta_time = (float)((time_frame - time) % 1000);
    
    glUniform1f(Time, delta_time);

    glClearBufferfv(GL_COLOR, 0, black);

    glBindVertexArray( VAOs[Triangles] );
    glPointSize(100);
    glDrawArrays( GL_POINTS, 0, NumVertices );
}

//----------------------------------------------------------------------------
//
// main
//


int
main( int argc, char** argv )
{
    glfwInit();

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    init();

    while (!glfwWindowShouldClose(window))
    {
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}
