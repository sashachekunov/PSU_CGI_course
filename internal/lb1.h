#pragma once

#ifndef LB1_H
#define LB1_H
#define GL_SILENCE_DEPRECATION
#define PI 3.14159

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include<iostream>
#include<cmath>

#include "point2d.h"
#include "utils.h"

using std :: cerr;
using std :: endl;

namespace cgi_lb1
{
    GLuint programID;
    GLuint vBuffer;
    GLuint vertexArray;

    const int N = 1000;
    GLfloat a = -PI, b = PI, c, d;
    GLfloat h = (b - a) / (N - 1);
    point2d graph[N];
  
    GLfloat points[2*N];
    GLfloat nPoints = (double)N;

    double f(double x) 
    {
        return sin(x);
    }

    void lb1_init()
    {
        /* Создать и откомпилировать нашу шейдерную программу */
        programID = LoadShaders
        (
            "/Users/macbook/Google Диск/Документы/Образование/Бакалавриат/Лабораторные работы/Графика/CGI_CHEKUNOV/shaders/vert.vert", 
            "/Users/macbook/Google Диск/Документы/Образование/Бакалавриат/Лабораторные работы/Графика/CGI_CHEKUNOV/shaders/frag.frag" 
        );
    
        /* Вычисление аргументов и значений функции */
        for(int i = 0; i < N; i++) 
        {
            graph[i].x = a + i*h;
            graph[i].y = f(graph[i].x);
        }

        /* Вычисление границ по оси "y" */
        c = graph[0].y;
        d = graph[0].y;
        for(int i = 1; i < N; i++)
        {
            if(graph[i].y < c)
                c = graph[i].y;
            if(graph[i].y > d)
                d = graph[i].y;
        }
    
        /* Вычисление координат для opengl */
        for(int i = 0; i < N; i++) 
        {
            points[2*i] = affine_convert(graph[i].x, a, b, -1, 1);
            points[2*i + 1] = affine_convert(graph[i].y, c, d, -1, 1);
        }

        glGenBuffers(1, &vBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        
        glGenVertexArrays(1, &vertexArray);
        
        glBindVertexArray(vertexArray);
        GLuint vertexLocation(GLuint(glGetAttribLocation(programID, "vertex")));
        glEnableVertexAttribArray(vertexLocation);

        glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
        glVertexAttribPointer(vertexLocation, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0 );
        glBindBuffer(GL_ARRAY_BUFFER, 0);                                                           
        glBindVertexArray(0);
        glUseProgram(programID);
        glBindVertexArray(vertexArray);


        cerr << "- lb1_init" << endl;
    }

    void lb1_destroy()
    {
        cerr << "- lb1_destroy" << endl;
        // /* Освобождаем ресурсы */
        glDeleteBuffers(1, &vBuffer);
        glDeleteVertexArrays(1, &vertexArray);
        glDeleteProgram(programID);
    }

    void lb1(GLFWwindow *window)
    {
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        // cerr << "lb1! " << display_w << ", " << display_h << endl;
        glDrawArrays(GL_LINE_STRIP, 0, nPoints);

        // /* Вычисление координат для opengl */
        // for(int i = 0; i < N; i++) 
        // {
        //     double x, y;
        //     x = affine_convert(graph[i].x, a, b, 0, display_w);
        //     y = affine_convert(graph[i].y, c, d, 0, display_h);
        //     points[2*i] = affine_convert(x, 0, display_w, -1, 1);
        //     points[2*i + 1] = affine_convert(y, 0, display_h, -1, 1);
        // }
        // modify data and update buffer   
        // double t(glfwGetTime());
        // points[0]=cos(t)*0.5;points[1]=sin(t)*0.5;
        // points[2]=cos(t+1.57)*0.5;points[3]=sin(t+1.57)*0.5;
        // points[4]=cos(t+3.14)*0.5;points[5]=sin(t+3.14)*0.5;
        // points[6]=cos(t+4.71)*0.5;points[7]=sin(t+4.71)*0.5;
        // glBindBuffer(GL_ARRAY_BUFFER,vBuffer);
        // glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);
        // glBindBuffer(GL_ARRAY_BUFFER,0);  
    }
}

#endif