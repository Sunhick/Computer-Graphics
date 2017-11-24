//
//  house.c
//  hw2
//
//  Created by Sunil on 6/12/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#include "shapes.h"

extern unsigned int tex[20];

/**********************************************************
 *  Draw house
 **********************************************************/
void DrawHouse()
{
  // draw body of the house
  glPushMatrix();
  glScaled(2.5, 1.5, 3.5);
  CubeTexture(tex[10], tex[10]);
  glPopMatrix();
    
  glBindTexture(GL_TEXTURE_2D, tex[10]);
  // roof front and back
  glPushMatrix();
  glTranslated(0, 1.5, 3.5);
  glScaled(2.5, 1.5, 1);
  Triangle(.1, .3, .1);
  glPopMatrix();
    
    
  glPushMatrix();
  glTranslated(0, 1.5, -3.5);
  glRotated(180,0,1,0);
  glScaled(2.5, 1.5, 1);
  Triangle(.1, .3 ,.1);
  glPopMatrix();
    
  // roof sides
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[11]);
  //glTranslated(2.5, 1.5, 3.5);
  glTranslated(-2.5, 1.5, -3.5);
  glRotated(-90,0,1,0);
  glRotated(-60, 1,0,0);
  glScaled(3.5*2, 1.5*2, 1);
  Rectangle(.8, .3, .4);
  glPopMatrix();
    
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[11]);
  glTranslated(2.5, 1.5, 3.5);
  glRotated(90,0,1,0);
  glRotated(-60, 1,0,0);
  glScaled(3.5*2, 1.5*2, 1);
  Rectangle(.8, .3, .4);
  glPopMatrix();
    
  ErrCheck("DrawHouse");
}

void DrawApartment()
{
  glPushMatrix();
  glColor3f(1, 1, 1);
  glScaled(3, 5, 5);
  CubeTexture(tex[6], tex[7]);
  glPopMatrix();
    
  ErrCheck("DrawApartment");
}

void DrawTree()
{
  glPushMatrix();
  glRotated(-90, 1, 0, 0);
  glBindTexture(GL_TEXTURE_2D, tex[13]);
  for (int i = 0; i < 3; i++) {
    Cone(4, 10, 255, 255, 255);
    glTranslated(0, 0, 3);
  }
  glPopMatrix();
    
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[14]);
  glRotated(90, 1, 0, 0);
  Cylinder(1, 5, 255, 255, 255);
  glPopMatrix();
}
