#pragma once

#ifndef LB5_H
#define LB5_H
#define GL_SILENCE_DEPRECATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include<iostream>

using std :: cerr;
using std :: endl;

namespace cgi_lb5
{
    GLuint VertexArrayID;
    GLuint programID;
    GLuint MatrixID;
    GLuint EVID;
    glm::mat4 Projection;
    glm::mat4 View;
    glm::mat4 Model;
    glm::mat4 MVP;
    GLuint vertexbuffer;

    glm::mat4 T;

    const GLuint N = 14;
    GLfloat a = -PI, b = PI, c = -PI, d = PI, e, f;
    GLfloat h_x = (b - a) / (N - 1.);
    GLfloat h_y = (d - c) / (N - 1.);
    point3d graph[N*N];

    GLuint texture_id;

    bool is_top_visible = true;
    bool is_low_visible = true;
    bool is_gr1_visible = true;
    bool is_gr2_visible = true;
    bool is_gr3_visible = true;
    bool is_gr4_visible = true;
    bool is_gr5_visible = true;
    bool is_gr6_visible = true;

    bool is_left = false;
    bool is_right = false;
    bool is_top = false;
    bool is_bottom = false;

	GLfloat top_vertex[18*3] = 
    {
        -1.0f, 0.0f, 1.0f,
        -sinf(30*PI/180), cosf(30*PI/180), 1.0f,
        0.0f, 0.0f, 1.0f,

        -sinf(30*PI/180), cosf(30*PI/180), 1.0f,
        sinf(30*PI/180), cosf(30*PI/180), 1.0f,
        0.0f, 0.0f, 1.0f,
        
        sinf(30*PI/180), cosf(30*PI/180), 1.0f,
        1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        sinf(30*PI/180), -cosf(30*PI/180), 1.0f,
        0.0f, 0.0f, 1.0f,
        
        sinf(30*PI/180), -cosf(30*PI/180), 1.0f,
        -sinf(30*PI/180), -cosf(30*PI/180), 1.0f,
        0.0f, 0.0f, 1.0f,

        -sinf(30*PI/180), -cosf(30*PI/180), 1.0f,
        -1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    };

	GLfloat low_vertex[18*3] = 
    {
        -1.0f, 0.0f, -1.0f,
        -sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        0.0f, 0.0f, -1.0f,

        -sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        0.0f, 0.0f, -1.0f,
        
        sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        1.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, -1.0f,
        sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        0.0f, 0.0f, -1.0f,
        
        sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        -sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        0.0f, 0.0f, -1.0f,

        -sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        -1.0f, 0.0f, -1.0f,
        0.0f, 0.0f, -1.0f
    };

	GLfloat gr1[6*3] = 
    {
        -1.0f, 0.0f, 1.0f,
        -sinf(30*PI/180), cosf(30*PI/180), 1.0f,
        -sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        -sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        -1.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, 1.0f
    };

	GLfloat gr2[6*3] = 
    {
        -sinf(30*PI/180), cosf(30*PI/180), 1.0f,
        sinf(30*PI/180), cosf(30*PI/180), 1.0f,
        sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        -sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        -sinf(30*PI/180), cosf(30*PI/180), 1.0f
    };

	GLfloat gr3[6*3] = 
    {
        sinf(30*PI/180), cosf(30*PI/180), 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, -1.0f,
        1.0f, 0.0f, -1.0f,
        sinf(30*PI/180), cosf(30*PI/180), -1.0f,
        sinf(30*PI/180), cosf(30*PI/180), 1.0f
    };

	GLfloat gr4[6*3] = 
    {
        1.0f, 0.0f, 1.0f,
        sinf(30*PI/180), -cosf(30*PI/180), 1.0f,
        sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        1.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 1.0f
    };

	GLfloat gr5[6*3] = 
    {
        sinf(30*PI/180), -cosf(30*PI/180), 1.0f,
        -sinf(30*PI/180), -cosf(30*PI/180), 1.0f,
        -sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        -sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        sinf(30*PI/180), -cosf(30*PI/180), 1.0f
    };

	GLfloat gr6[6*3] = 
    {
        -sinf(30*PI/180), -cosf(30*PI/180), 1.0f,
        -1.0f, 0.0f, 1.0f,
        -1.0f, 0.0f, -1.0f,
        -1.0f, 0.0f, -1.0f,
        -sinf(30*PI/180), -cosf(30*PI/180), -1.0f,
        -sinf(30*PI/180), -cosf(30*PI/180), 1.0f
    };


    GLfloat V[4][8] = 
    {
        {
            0.0f, 0.0f, -433.0f, 0.0f, 433.0f, 433.0f, 0.0f, -433.0f
        },
        {
            0.0f, 0.0f, 250.0f, 500.0f, 250.0f, -250.0f, -500.0f, -250.0f
        },
        {
            433.0f, -433.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
        },
        {
            -433.0f, -433.0f, -433.0f, -433.0f, -433.0f, -433.0f, -433.0f, -433.0f
        }
    };

    GLfloat VT[4][8], EV[8];
    GLfloat E[4] = {0.0f, 5.0f, -2.0f, 0.0f};
    // int E_ = 1;

    void lb5_init()
    {
        cerr << "- lb4_init" << endl;


	    // // Create our datapoints, store it as bytes
        // #define N 256
        // GLbyte graph[N][N];

        // for (int i = 0; i < N; i++) {
        //     for (int j = 0; j < N; j++) {
        //         float x = (i - N / 2) / (N / 2.0);
        //         float y = (j - N / 2) / (N / 2.0);
        //         float d = hypotf(x, y) * 4.0;
        //         float z = (1 - d * d) * expf(d * d / -2.0);

        //         graph[i][j] = roundf(z * 127 + 128);
        //     }
        // }

        // /* Upload the texture with our datapoints */
        // glActiveTexture(GL_TEXTURE0);
        // glGenTextures(1, &texture_id);
        // glBindTexture(GL_TEXTURE_2D, texture_id);
        // glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, N, N, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, graph);


        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);	// Create and compile our GLSL program from the shaders

        programID = LoadShaders("../shaders/lb5.vert", "../shaders/lb5.frag");

        // Get a handle for our "MVP" uniform
        MatrixID = glGetUniformLocation(programID, "MVP");
        // EVID = glGetUniformLocation(programID, "E_");
        Projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
        View = glm::lookAt(glm::vec3(0.0, -5.0, 2.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
        Model = glm::mat4(1.0f);
        MVP = Projection * View * Model;

        T = glm::inverse(MVP);

        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 8; ++j)
            {
                VT[i][j] = 0;
                for(int k = 0; k < 4; ++k)
                {
                    VT[i][j] += T[i][k]*V[k][j];
                }
                // cerr << VT[i][j] << " ";
            }
            // cerr << "\n";
        }

        for(int j = 0; j < 8; ++j)
        {
            EV[j] = 0;
            for(int k = 0; k < 4; ++k)
            {
                EV[j] += E[k]*VT[k][j];
                // EV[j] += E[k]*V[k][j];
            }
            // cerr << EV[j] << ' ';
        }
        // cerr << "\n";

        if(EV[0] >= 0)
            is_top_visible = true;
        else
            is_top_visible = false;
        if(EV[1] >= 0)
            is_low_visible = true;
        else
            is_low_visible = false;
        if(EV[2] >= 0)
            is_gr1_visible = true;
        else
            is_gr1_visible = false;
        if(EV[3] >= 0)
            is_gr2_visible = true;
        else
            is_gr2_visible = false;
        if(EV[4] >= 0)
            is_gr3_visible = true;
        else
            is_gr3_visible = false;
        if(EV[5] >= 0)
            is_gr4_visible = true;
        else
            is_gr4_visible = false;
        if(EV[6] >= 0)
            is_gr5_visible = true;
        else
            is_gr5_visible = false;
        if(EV[7] >= 0)
            is_gr6_visible = true;
        else
            is_gr6_visible = false;

        glGenBuffers(1, &vertexbuffer);
    }

    void lb5_destroy()
    {
        cerr << "- lb4_destroy" << endl;
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteVertexArrays(1, &VertexArrayID);
        glDeleteProgram(programID);
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
            is_left = true;
        if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
            is_right = true;
        if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE)
            is_left = false;
        if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE)
            is_right = false;
        if (key == GLFW_KEY_UP && action == GLFW_PRESS)
            is_top = true;
        if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
            is_bottom = true;
        if (key == GLFW_KEY_UP && action == GLFW_RELEASE)
            is_top = false;
        if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE)
            is_bottom = false;
    }

    void lb5(GLFWwindow *window)
    {
        glfwSetKeyCallback(window, key_callback);
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

       	glUseProgram(programID);

        Projection = glm::perspective(glm::radians(45.0f), (float)display_w / (float)display_h, 0.1f, 100.0f);
        if(is_right)
            Model = glm::rotate(Model, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        if(is_left)
            Model = glm::rotate(Model, glm::radians(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
        if(is_top)
            Model = glm::rotate(Model, glm::radians(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        if(is_bottom)
            Model = glm::rotate(Model, glm::radians(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	    MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around


        /* Динамические вычисления */
        T = glm::inverse(MVP);

        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 8; ++j)
            {
                VT[i][j] = 0;
                for(int k = 0; k < 4; ++k)
                {
                    VT[i][j] += T[i][k]*V[k][j];
                }
                // cerr << VT[i][j] << " ";
            }
            // cerr << "\n";
        }
        for(int j = 0; j < 8; ++j)
        {
            EV[j] = 0;
            for(int k = 0; k < 4; ++k)
            {
                EV[j] += E[k]*VT[k][j];
            }
            // cerr << EV[j] << ' ';
        }
        // cerr << "\n";

        if(EV[0] >= 0)
            is_top_visible = true;
        else
            is_top_visible = false;
        if(EV[1] >= 0)
            is_low_visible = true;
        else
            is_low_visible = false;
        if(EV[2] >= 0)
            is_gr1_visible = true;
        else
            is_gr1_visible = false;
        if(EV[3] >= 0)
            is_gr2_visible = true;
        else
            is_gr2_visible = false;
        if(EV[4] >= 0)
            is_gr3_visible = true;
        else
            is_gr3_visible = false;
        if(EV[5] >= 0)
            is_gr4_visible = true;
        else
            is_gr4_visible = false;
        if(EV[6] >= 0)
            is_gr5_visible = true;
        else
            is_gr5_visible = false;
        if(EV[7] >= 0)
            is_gr6_visible = true;
        else
            is_gr6_visible = false;


		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
		// glUniform1f(EVID, EV[0]);

        // glUniform1i(EVID, E_);


		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);

        if(is_top_visible)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(top_vertex), top_vertex, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3*18);
        }
        if(is_low_visible)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(low_vertex), low_vertex, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3*18);
        }
        if(is_gr1_visible)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(gr1), gr1, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3*6);
        }
        if(is_gr2_visible)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(gr2), gr2, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3*6);
        }
        if(is_gr3_visible)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(gr3), gr3, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3*6);
        }
        if(is_gr4_visible)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(gr4), gr4, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3*6);
        }
        if(is_gr5_visible)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(gr5), gr5, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3*6);
        }
        if(is_gr6_visible)
        {
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(gr6), gr6, GL_DYNAMIC_DRAW);
            glDrawArrays(GL_TRIANGLES, 0, 3*6);
        }

		glDisableVertexAttribArray(0);
    }
}
#endif