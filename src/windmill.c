//
//  windmill.c
//  hw2
//
//  Created by Sunil on 6/12/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "shapes.h"

extern unsigned int tex[20];
extern double zh;

/**********************************************************
 * Draw wings
 **********************************************************/
void wings()
{
  // supporting pole for wings
  glPushMatrix();
  glRotated(180,1,0,0);
  glScaled(.3,.3,3);
  Cylinder(1,.5,255,255,255);
  glPopMatrix();
    
  glBindTexture(GL_TEXTURE_2D, tex[9]);
    
  // 1st wing
  //cube(0,0,0, 2,.4,0.9, 0, 1,0,0);
  glPushMatrix();
  glRotated(zh, 0,0,1);
  glScaled(.4,4,.2);
  Cube(1,1,1);
  glPopMatrix();
    
  // 2nd wing
  glPushMatrix();
  glRotated(zh + 90, 0,0,1);
  glScaled(.4, 4, .2);
  Cube(1,1,1);
  glPopMatrix();
}

/**********************************************************
 * Draw windmill
 **********************************************************/
void DrawWindmill()
{
  glBindTexture(GL_TEXTURE_2D, tex[8]);
    
  // draw the base
  glPushMatrix();
  glRotated(90,1,0,0);
  glScaled(2, 2, 2);
  Cylinder(1,.5,255, 255, 255);
  glPopMatrix();
    
  // draw the pole
  glPushMatrix();
  glRotated(-90,1,0,0);
  glScaled(.5, .5, 15);
  Cylinder(1,.5,255,255,255);
  glPopMatrix();
    
  // windmill holder
  glPushMatrix();
  sphere(.1, 7.9, 0, .5);
  glPopMatrix();
    
  // wings
  glPushMatrix();
  glTranslated(0,8,2);
  wings();
  glPopMatrix();
    
  ErrCheck("DrawWindmill");
}

///**********************************************************
// * Draw wings
// **********************************************************/
//void wings()
//{
//    // supporting pole for wings
//    glPushMatrix();
//    glRotated(180,1,0,0);
//    glScaled(.3,.3,3);
//    Cylinder(1,.5,255,255,255);
//    glPopMatrix();
// 
//    glBindTexture(GL_TEXTURE_2D, tex[9]);
//    
//    // 1st wing
//    //cube(0,0,0, 2,.4,0.9, 0, 1,0,0);
//    glPushMatrix();
//    glRotated(zh, 0,0,1);
//    glScaled(.4,4,.2);
//    Cube(1,1,1);
//    glPopMatrix();
//    
//    // 2nd wing
//    glPushMatrix();
//    glRotated(zh + 90, 0,0,1);
//    glScaled(.4, 4, .2);
//    Cube(1,1,1);
//    glPopMatrix();
//}
//
///**********************************************************
// * Draw windmill
// **********************************************************/
//void DrawWindmill() 
//{
//    glBindTexture(GL_TEXTURE_2D, tex[8]);
//    
//    // draw the base
//    glPushMatrix();
//    glRotated(90,1,0,0);
//    glScaled(2, 2, 2);
//    Cylinder(1,.5,255, 255, 255);
//    glPopMatrix();
//    
//    // draw the pole
//    glPushMatrix();
//    glRotated(-90,1,0,0);
//    glScaled(.5, .5, 15);
//    Cylinder(1,.5,255,255,255);
//    glPopMatrix();
//
//    // windmill holder
//    glPushMatrix();
//    sphere(.1, 7.9, 0, .5);
//    glPopMatrix();
//
//    // wings
//    glPushMatrix();
//    glTranslated(0,8,2);
//    wings();
//    glPopMatrix();
//    
//    ErrCheck("DrawWindmill");
//}

