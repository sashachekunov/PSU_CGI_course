#pragma once

#ifndef LB2_H
#define LB2_H
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

namespace cgi_lb2
{
    GLuint programID;
    GLuint vBuffer;
    GLuint vertexArray;

    const int N = 1000;
    GLfloat a = -PI, b = PI, c, d;
    GLfloat h = (b - a) / (N - 1.);
    point2d graph[N];
  
    GLfloat points[2*N];
    GLfloat nPoints = (double)N;

    // Точки и параметры буквы A
    GLfloat s = 2./20.;
    GLfloat h1 = 2./10.;
    GLfloat h2 = h1/2.;
    GLfloat A[10];
    GLfloat APoints = 5.;
    // Точка относительно которой происходит вращение
    GLfloat c_x = 0, c_y = 0;

    // Переменные для определения нужно ли вращаться
    bool is_left = false;
    bool is_right = false;

    // Функция-траектория
    GLfloat f(GLfloat x) 
    {
        return x*x*x*x*x*x;
    }

    void lb2_init()
    {
        /* Создать и откомпилировать  шейдерную программу */
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
            points[2*i] = affine_convert(graph[i].x, a, b, -1.+h1, 1.-h1);
            points[2*i + 1] = affine_convert(graph[i].y, c, d, -1.+h1, 1.-h1);
        }

        // A[10] = {-1.,-1., -1+s/2,-1+h1, -1+s,-1, s*(h1 - h2)/(2*h1)-1+s/2,-1+h2, s*h2/(2*h1)-1,-1+h2};
        A[0] = -1;
        A[1] = -1;
        A[2] = -1+s/2;
        A[3] = -1+h1;
        A[4] = -1+s;
        A[5] = -1;
        A[6] = s*(h1 - h2)/(2*h1)-1+s/2;
        A[7] = -1+h2;
        A[8] = s*h2/(2*h1)-1;
        A[9] = -1+h2;

        // Перевод координат вершин A для вписания в прямоугольник
        for(int i = 0; i < 5; i++) 
        {
            A[2*i] = affine_convert(A[2*i], -1., 1., -1.+h1, 1.-h1);
            A[2*i + 1] = affine_convert(A[2*i + 1], -1., 1., -1.+h1, 1.-h1);
        }

        // Вычисление смещенния по y, для параллельного переноса в начало графика
        GLfloat delta_y, tmp, angle;
        delta_y = affine_convert(f(a), c,d, -1., 1.) - affine_convert(A[1], -1., 1., -1., 1.);
        for(int i = 0; i < 5; i++) 
        {
            A[2*i + 1] += delta_y;
        }
        // Обратное преобразование координат
        for(int i = 0; i < 5; i++) 
        {
            A[2*i + 1] = affine_convert(A[2*i + 1], -1., 1., -1.+h1, 1.-h1);
        }

        // Поворот на угол наклона, при котором буква правильно располагается на кривой графика
        if(f(a) > f(affine_convert(-1+h1+s, -1+h1, 1-h1, a,b)))
            while(affine_convert(A[5], -1+h1, 1-h1, c,d) > f(affine_convert(A[4], -1+h1, 1-h1, a, b)))
                for(int i = 0; i < 5; i++)
                    affine_rotate(A[2*i], A[2*i + 1], affine_convert(a, a, b, -1+h1, 1-h1), affine_convert(f(a), c, d, -1+h1, 1-h1), -1);
        else
            while(affine_convert(A[5], -1+h1, 1-h1, c,d) < f(affine_convert(A[4], -1+h1, 1-h1, a, b)))
                for(int i = 0; i < 5; i++)
                    affine_rotate(A[2*i], A[2*i + 1], affine_convert(a, a, b, -1+h1, 1-h1), affine_convert(f(a), c, d, -1+h1, 1-h1), 1);

        c_x = A[0];
        c_y = A[1];

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

        cerr << "- lb2_init" << endl;
    }

    void lb2_destroy()
    {
        cerr << "- lb2_destroy" << endl;
        // /* Освобождаем ресурсы */
        glDeleteBuffers(1, &vBuffer);
        glDeleteVertexArrays(1, &vertexArray);
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
    }

    void lb2(GLFWwindow *window)
    {
        glfwSetKeyCallback(window, key_callback);

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        // gldraw
        glDrawArrays(GL_LINE_STRIP, 0, nPoints);

        glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(A), A, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // gldraw
        glDrawArrays(GL_LINE_STRIP, 0, APoints);

        /* Вычисление координат для opengl */
        if(is_left)
        {
            // Проверки 3-х вершин на пересечение с графиком
            if(affine_convert(A[1], -1+h1,1-h1, c,d) < f(affine_convert(A[0], -1+h1,1-h1, a,b)))
            {
                for(int i = 0; i < 5; i++)
                    affine_rotate(A[2*i], A[2*i+1], c_x, c_y, -1);
                c_x = A[0];
                c_y = A[1];
            }
            if(affine_convert(A[3], -1+h1,1-h1, c,d) < f(affine_convert(A[2], -1+h1,1-h1, a,b)))
            {
                for(int i = 0; i < 5; i++)
                    affine_rotate(A[2*i], A[2*i+1], c_x, c_y, -1);
                c_x = A[2];
                c_y = A[3];
            }
            if(affine_convert(A[5], -1+h1,1-h1, c,d) < f(affine_convert(A[4], -1+h1,1-h1, a,b)))
            {
                for(int i = 0; i < 5; i++)
                    affine_rotate(A[2*i], A[2*i+1], c_x, c_y, -1);
                c_x = A[4];
                c_y = A[5];
            }

            // Поворот против часовой стрелки
            for(int i = 0; i < 5; i++) 
                affine_rotate(A[2*i], A[2*i+1], c_x, c_y, 1);
        }
        if(is_right)
        {
            // Проверки 3-х вершин на пересечение с графиком
            if(affine_convert(A[1], -1+h1,1-h1, c,d) < f(affine_convert(A[0], -1+h1,1-h1, a,b)))
            {
                for(int i = 0; i < 5; i++)
                    affine_rotate(A[2*i], A[2*i+1], c_x, c_y, 1);
                c_x = A[0];
                c_y = A[1];
            }
            if(affine_convert(A[3], -1+h1,1-h1, c,d) < f(affine_convert(A[2], -1+h1,1-h1, a,b)))
            {
                for(int i = 0; i < 5; i++)
                    affine_rotate(A[2*i], A[2*i+1], c_x, c_y, 1);
                c_x = A[2];
                c_y = A[3];
            }
            if(affine_convert(A[5], -1+h1,1-h1, c,d) < f(affine_convert(A[4], -1+h1,1-h1, a,b)))
            {
                for(int i = 0; i < 5; i++)
                    affine_rotate(A[2*i], A[2*i+1], c_x, c_y, 1);
                c_x = A[4];
                c_y = A[5];
            }

            // Поворот по часовой стрелке
            for(int i = 0; i < 5; i++)
                affine_rotate(A[2*i], A[2*i+1], c_x, c_y, -1);
        }

        glBindBuffer(GL_ARRAY_BUFFER, vBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

#endif