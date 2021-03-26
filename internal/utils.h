#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

GLfloat affine_convert(GLfloat x, GLfloat a, GLfloat b, GLfloat a_, GLfloat b_)
{
    return (x - a)*(b_ - a_)/(b - a) + a_;
}

void affine_rotate(GLfloat &x, GLfloat &y, GLfloat c_x, GLfloat c_y, GLfloat angle)
{
    GLfloat x_ = x;
    x = (x_ - c_x)*cos(angle*PI/180) - (y - c_y)*sin(angle*PI/180) + c_x;
    y = (x_ - c_x)*sin(angle*PI/180) + (y - c_y)*cos(angle*PI/180) + c_y;
}

#endif