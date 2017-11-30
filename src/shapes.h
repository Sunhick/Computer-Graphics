//
//  shapes.h
//  hw2
//
//  Created by Sunil on 6/12/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#ifndef SRC_SHAPES_H_
#define SRC_SHAPES_H_

#include "./main.h"

#ifdef __cplusplus
extern "C" {
#endif

void Triangle(double red, double green, double blue);
void Rectangle(double red, double green, double blue);
void Cube(double red, double green, double blue);
void CubeTexture(unsigned int sides, unsigned int top);
void CubeTextures(unsigned int front, unsigned int back, unsigned int right,
                  unsigned int left, unsigned int top, unsigned int bottom);

void Vertex(double th, double ph);
void sphere(double x, double y, double z, double r);
void Cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B);
void Cone(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B);

#ifdef __cplusplus
}
#endif

#endif  // SRC_SHAPES_H_
