#pragma once

#ifndef LB3_H
#define LB3_H
#define GL_SILENCE_DEPRECATION
#define PI 3.14159

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<iostream>
#include<cmath>

#include "point3d.h"
#include "utils.h"

using std :: cerr;
using std :: endl;

namespace cgi_lb3
{
    GLuint VertexArrayID;
    GLuint programID;
    GLuint MatrixID;
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 MVP;
    GLuint vertexbuffer;

    const GLuint N = 50;
    GLfloat a = -PI, b = PI, c = -PI, d = PI, e, f;
    GLfloat h_x = (b - a) / (N - 1.);
    GLfloat h_y = (d - c) / (N - 1.);
    point3d graph[N*N];
	GLfloat g_vertex_buffer_data[12*(N - 1)*(N - 1)];


    GLfloat func(GLfloat x, GLfloat y)
    {
        // return exp(x)*y;
        return sin(x)*cos(y);
    }

    void lb3_init()
    {
        cerr << "- lb3_init" << endl;
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
            {
                graph[i*N + j].x = a + i*h_x;
                graph[i*N + j].y = c + j*h_y;
                graph[i*N + j].z = func(graph[i*N + j].x, graph[i*N + j].y);
            }
        }
        // for(int i = 0; i < N; ++i)
        // {
        //     for(int j = 0; j < N; ++j)
        //     {
        //         cerr << "(" << graph[i*N + j].x << "," <<
        //             graph[i*N + j].y << "), ";
        //     }
        //     cerr << endl;
        // }
        /* Вычисление границ по оси "z" */
        e = graph[0].z;
        f = graph[0].z;
        for(int i = 1; i < N*N; i++)
        {
            if(graph[i].z < e)
                e = graph[i].z;
            if(graph[i].z > f)
                f = graph[i].z;
        }
        // cerr << e << endl;
        // cerr << f << endl;
        for(int i = 0; i < N - 1; ++i)
        {
            for(int j = 0; j < N - 1; ++j)
            {
                // cerr << "(" << graph[i*N + j + 1].x << "," <<
                //     graph[i*N + j + 1].y << "), ";

                // cerr << "(" << graph[i*N + j].x << "," <<
                //     graph[i*N + j].y << "), ";

                // cerr << "(" << graph[(i + 1)*N + j].x << "," <<
                //     graph[(i + 1)*N + j].y << "), ";

                // cerr << "(" << graph[(i + 1)*N + j + 1].x << "," <<
                //     graph[(i + 1)*N + j + 1].y << ")\n";

                g_vertex_buffer_data[12*(i*(N - 1) + j) + 0] = affine_convert(graph[i*N + j + 1].x, a, b, -1, 1);
                g_vertex_buffer_data[12*(i*(N - 1) + j) + 1] = affine_convert(graph[i*N + j + 1].y, c, d, -1, 1);
                g_vertex_buffer_data[12*(i*(N - 1) + j) + 2] = affine_convert(graph[i*N + j + 1].z, e, f, -1, 1);

                g_vertex_buffer_data[12*(i*(N - 1) + j) + 3] = affine_convert(graph[i*N + j].x, a, b, -1, 1);
                g_vertex_buffer_data[12*(i*(N - 1) + j) + 4] = affine_convert(graph[i*N + j].y, c, d, -1, 1);
                g_vertex_buffer_data[12*(i*(N - 1) + j) + 5] = affine_convert(graph[i*N + j].z, e, f, -1, 1);

                g_vertex_buffer_data[12*(i*(N - 1) + j) + 6] = affine_convert(graph[(i + 1)*N + j].x, a, b, -1, 1);
                g_vertex_buffer_data[12*(i*(N - 1) + j) + 7] = affine_convert(graph[(i + 1)*N + j].y, c, d, -1, 1);
                g_vertex_buffer_data[12*(i*(N - 1) + j) + 8] = affine_convert(graph[(i + 1)*N + j].z, e, f, -1, 1);

                g_vertex_buffer_data[12*(i*(N - 1) + j) + 9]  = affine_convert(graph[(i + 1)*N + j + 1].x, a, b, -1, 1);
                g_vertex_buffer_data[12*(i*(N - 1) + j) + 10] = affine_convert(graph[(i + 1)*N + j + 1].y, c, d, -1, 1);
                g_vertex_buffer_data[12*(i*(N - 1) + j) + 11] = affine_convert(graph[(i + 1)*N + j + 1].z, e, f, -1, 1);
                // graph[i*10 + j + 1];
                // graph[i*10 + j];
                // graph[(i + 1)*10 + j];
                // graph[(i + 1)*10 + j + 1];
            }
        }

        // 12*(N - 1)*(N - 1)
        // for(int i = 0; i < 12*(N - 1)*(N - 1); ++i)
        // {
        //     cerr << g_vertex_buffer_data[i] << endl;
        // }

        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);	// Create and compile our GLSL program from the shaders

        programID = LoadShaders("../shaders/3d.vert", "../shaders/3d.frag");

        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(programID, "MVP");

        // Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        Projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
        // Or, for an ortho camera :
        //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
        
        // Camera matrix
        // View       = glm::lookAt(
        //                             glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
        //                             glm::vec3(0,0,0), // and looks at the origin
        //                             glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        //                     );
        View = glm::lookAt(glm::vec3(0.0, -5.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        // Model matrix : an identity matrix (model will be at the origin)

        Model = glm::mat4(1.0f);

        // Our ModelViewProjection : multiplication of our 3 matrices
        MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    }

    void lb3_destroy()
    {
        cerr << "- lb3_destroy" << endl;
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteVertexArrays(1, &VertexArrayID);
        glDeleteProgram(programID);
    }

    void lb3(GLFWwindow *window)
    {
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

		/* Clear the screen */
		// glClear( GL_COLOR_BUFFER_BIT );

       	glUseProgram(programID);

        Projection = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 100.0f);
        Model = glm::rotate(glm::mat4(1.0f), glm::radians(((float)glfwGetTime()*1000.0f) / 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw
		glDrawArrays(GL_LINES, 0, 12*(N - 1)*(N - 1)); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
    }
}

#endif