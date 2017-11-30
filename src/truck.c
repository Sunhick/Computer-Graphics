//
//  truck.c
//  hw2
//
//  Created by Sunil on 6/12/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#include <stdio.h>

#include <math.h>
#include <stdlib.h>

#include "./shapes.h"
#include "CSCIx229.h"

extern double zh;
extern double speed;
extern unsigned int tex[20];
extern double bx, bz;
extern double ex, ez;
extern double tx, tz;
extern double wx, wz;
extern double rot;

double fall_apart = .2;

void drawRoad() {
  // center long road
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[3]);
  glScaled(5, .2, 25);
  Cube(1, 1, 1);
  glPopMatrix();

  // left road
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[4]);
  glTranslated(-15, 0, 0);
  glScaled(10, .2, 5);
  Cube(1, 1, 1);
  glPopMatrix();

  // right road
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[4]);
  glTranslated(15, 0, 0);
  glScaled(10, .2, 5);
  Cube(1, 1, 1);
  glPopMatrix();

  // bottom left grass
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[5]);
  glTranslated(-15, 0, 15);
  glScaled(10, .2, 10);
  Cube(1, 1, 1);
  glPopMatrix();

  // bottom right
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[5]);
  glTranslated(15, 0, 15);
  glScaled(10, .2, 10);
  Cube(1, 1, 1);
  glPopMatrix();

  // top left
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[5]);
  glTranslated(-15, 0, -15);
  glScaled(10, .2, 10);
  Cube(1, 1, 1);
  glPopMatrix();

  // top left
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[5]);
  glTranslated(15, 0, -15);
  glScaled(10, .2, 10);
  Cube(1, 1, 1);
  glPopMatrix();
}

/**********************************************************
 * Draw tires
 **********************************************************/
void tires() {
  // front tires
  glPushMatrix();
  glTranslated(1, -.4, -.8);
  glScaled(1, 1, 1);
  Cylinder(.5, .2, 155, 160, 130);  // left
  glPopMatrix();

  glPushMatrix();
  glTranslated(1, -.4, .6);
  glScaled(1, 1, 1);
  Cylinder(.5, .2, 155, 160, 130);  // right
  glPopMatrix();

  // rear
  glPushMatrix();
  glTranslated(-1, -.4, .6);
  glScaled(1, 1, 1);
  Cylinder(.5, .2, 155, 160, 130);  // left
  glPopMatrix();

  glPushMatrix();
  glTranslated(-1, -.4, -.8);
  glScaled(1, 1, 1);
  Cylinder(.5, .2, 155, 160, 130);  // right
  glPopMatrix();
}

/**********************************************************
 * Draw head lights
 **********************************************************/
void headlights() {
  // front lights
  glPushMatrix();
  glTranslated(2, -.1, -.5);
  glRotated(90, 0, 1, 0);
  glScaled(.4, .4, .4);
  Cylinder(.5, .2, 155, 160, 130);  // left
  glPopMatrix();

  glPushMatrix();
  glTranslated(2, -.1, .5);
  glRotated(90, 0, 1, 0);
  glScaled(.4, .4, .4);
  Cylinder(.5, .2, 155, 160, 130);  // right
  glPopMatrix();
}

/**********************************************************
 * Draw truck
 **********************************************************/
void DrawTruck() {
  // base
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[15]);
  glScaled(2, 0.4, 0.9);
  Cube(1, .6, .4);
  glPopMatrix();

  // engine
  glPushMatrix();
  glColor3f(0.9, .6, 0);
  // glBindTexture(GL_TEXTURE_2D, tex[2]);
  glTranslated(1.6, 1.4, 0);
  glScaled(.4, 1, .9);
  // Cube(0.9, .6, 0);
  CubeTextures(tex[16], tex[16], tex[2], tex[2], tex[16], tex[16]);
  glPopMatrix();

  // tank
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[0]);
  glTranslated(-1.9, .9, 0);
  glRotated(90, 0, 1, 0);
  glScaled(1, 1, 3.1);
  Cylinder(1, 1, 255, 160, 100);
  glPopMatrix();

  // tires
  glBindTexture(GL_TEXTURE_2D, tex[1]);
  tires();

  // head lights
  headlights();
}

void DrawTrafficSignal() {
  // draw the pole
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[9]);
  glRotated(-90, 1, 0, 0);
  glScaled(.2, .2, 15);
  Cylinder(1, .5, 255, 255, 255);
  glPopMatrix();

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[8]);
  glTranslated(0, 7.3, 0);
  glRotated(-90, 0, 1, 0);
  glScaled(.2, .2, 15);
  Cylinder(1, .5, 255, 255, 255);
  glPopMatrix();

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[12]);
  glColor3f(1, 1, 1);
  glTranslated(-7, 7.3, 0);
  glScaled(2, .5, .5);
  CubeTextures(tex[12], tex[12], tex[16], tex[16], tex[16], tex[16]);
  glPopMatrix();

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[8]);
  glTranslated(0, 7.3, 0);
  glRotated(180, 0, 1, 0);
  glScaled(.2, .2, 15);
  Cylinder(1, .5, 255, 255, 255);
  glPopMatrix();

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[12]);
  glColor3f(1, 1, 1);
  glTranslated(0, 7.3, -7);
  glRotated(90, 0, 1, 0);
  glScaled(2, .5, .5);
  CubeTextures(tex[12], tex[12], tex[16], tex[16], tex[16], tex[16]);
  glPopMatrix();
}

void BrokenTruck() {
  if (bx <= 5) {
    // bx = bz = ex = ez = tx = tz = 0.;
    //        bx = bz += fall_apart;
    //        ex = ez -= fall_apart;
    //        tx = tz += fall_apart;
    //        wx = wz += fall_apart;

    bx += fall_apart;
    bz += fall_apart;
    ex = ez -= fall_apart;
    tx -= fall_apart;
    tz += 2 * fall_apart;
    wx = wz += fall_apart;
    rot += 10;
  }

  // base
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[3]);
  glTranslatef(bx, 0, bz);
  glRotated(rot, 1, 1, 1);
  glScaled(2, 0.4, 0.9);
  Cube(1, 0, 0);
  glPopMatrix();

  // engine
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[2]);
  glTranslatef(ex, 0, ez);
  glTranslated(1.6, 1.4, 0);
  glRotated(rot, 1, 1, 1);
  glScaled(.4, 1, .9);
  Cube(0.9, .6, 0);
  glPopMatrix();

  // tank
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, tex[0]);
  glTranslatef(tx, 0, tz);
  glTranslated(-1.9, .9, 0);
  glRotated(90, 0, 1, 0);
  glRotated(rot, 1, 1, 1);
  glScaled(1, 1, 3.1);
  Cylinder(1, 1, 255, 160, 100);
  glPopMatrix();

  // tires
  glBindTexture(GL_TEXTURE_2D, tex[1]);
  glTranslated(wx, 2, wz);
  glRotated(rot, 1, 1, 1);
  tires();

  // head lights
  headlights();
}
