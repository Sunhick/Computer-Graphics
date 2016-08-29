//
//  shapes.c
//  hw2
//
//  Created by Sunil on 6/12/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include "shapes.h"

extern int rep;
extern unsigned int tex[5];
extern int emission;
extern float shinyvec[1];


/**********************************************************
 * Draw vertex using Polar co-ordinates
 **********************************************************/
void Vertex(double th,double ph)
{
    glColor3f(Cos(th)*Cos(th) , Sin(ph)*Sin(ph) , Sin(th)*Sin(th));
    glNormal3f(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
    glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
}

/**********************************************************
 * Draw sphere using radius R at (x,y,z)
 **********************************************************/
void sphere(double x, double y, double z, double r)
{
    float color[] = {1,.5,.1, 1};
    float Emission[]  = {0.0,0.0,0.1*emission,1.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    
    const int d = 5;
    int th,ph;
    
    glPushMatrix();
    
    glTranslatef(x, y, z);
    glScalef(r, r, r);
    
    //  South pole cap
    glBegin(GL_TRIANGLE_FAN);
    Vertex(0, -90);
    for (th=0; th <= 360; th += d)
    {
        Vertex(th, d-90);
    }
    glEnd();
    
    //  Latitude bands
    for (ph = d-90; ph <= 90-2*d; ph += d)
    {
        glBegin(GL_QUAD_STRIP);
        for (th = 0; th <= 360;th += d)
        {
            Vertex(th, ph);
            Vertex(th, ph+d);
        }
        glEnd();
    }
    
    //  North pole cap
    glBegin(GL_TRIANGLE_FAN);
    Vertex(0, 90);
    for (th = 0; th <= 360; th += d)
    {
        Vertex(th, 90-d);
    }
    glEnd();
    
    glPopMatrix();
}

/**********************************************************
 * Draw cylinder
 **********************************************************/
void Cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;
    
    float color[] = {1,.5,.1, 1};
    float Emission[]  = {0.0,0.0,0.1*emission,1.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    
    glColor3ub(R, G, B);
    glBegin(GL_QUAD_STRIP);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        glNormal3f(x, y, 0);
        const float tc = ( angle / (float)( 2 * PI ) );
        
        glTexCoord2f(rep*tc, 0); glVertex3f(x, y , height);
        glTexCoord2f(rep*tc, 1); glVertex3f(x, y , 0.0);
        
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glVertex3f(radius, 0.0, 0.0);
    glEnd();
    
    glColor3ub(R,G,B);
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,0,1);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        
        glTexCoord2f( rep*0.5f * cos(angle) + 0.5f, rep * 0.5f * sin(angle) + 0.5f );
        glVertex3f(x, y , height);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0,0,-1);
    angle = 0.0;
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        
        glTexCoord2f( -rep*0.5f * cos(angle) + 0.5f, rep * 0.5f * sin(angle) + 0.5f );
        glVertex3f(-x, y , 0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, height);
    glEnd();
}
//
///**********************************************************
// * Draw cylinder
// **********************************************************/
//void Cylinder(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)
//{
//    GLfloat x              = 0.0;
//    GLfloat y              = 0.0;
//    GLfloat angle          = 0.0;
//    GLfloat angle_stepsize = 0.1;
//    
//    float color[] = {1,.5,.1, 1};
//    float Emission[]  = {0.0,0.0,0.1*emission,1.0};
//    
//    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
//    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
//    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
//    
//    
//    glColor3ub(R-40,G-40,B-40);
//    glBegin(GL_QUAD_STRIP);
//    angle = 0.0;
//    while( angle < 2*PI ) {
//        x = radius * cos(angle);
//        y = radius * sin(angle);
//        glNormal3f(x, y, 0);
//        const float tc = ( angle / (float)( 2 * PI ) );
//        
//        glTexCoord2f(rep*tc, 0); glVertex3f(x, y , height);
//        glTexCoord2f(rep*tc, 1); glVertex3f(x, y , 0.0);
//        
//        angle = angle + angle_stepsize;
//    }
//    glVertex3f(radius, 0.0, height);
//    glVertex3f(radius, 0.0, 0.0);
//    glEnd();
//    
//    glColor3ub(R,G,B);
//    glBegin(GL_TRIANGLE_FAN);
//    glNormal3f(0,0,1);
//    angle = 0.0;
//    while( angle < 2*PI ) {
//        x = radius * cos(angle);
//        y = radius * sin(angle);
//        
//        glTexCoord2f( rep*0.5f * cos(angle) + 0.5f, rep * 0.5f * sin(angle) + 0.5f );
//        glVertex3f(x, y , height);
//        angle = angle + angle_stepsize;
//    }
//    glVertex3f(radius, 0.0, height);
//    glEnd();
//    
//    glColor3ub(R-90,G-7,B-66);
//    glBegin(GL_TRIANGLE_FAN);
//    glNormal3f(0,0,-1);
//    angle = 0.0;
//    while( angle < 2*PI ) {
//        x = radius * cos(angle);
//        y = radius * sin(angle);
//        
//        glTexCoord2f( -rep*0.5f * cos(angle) + 0.5f, rep * 0.5f * sin(angle) + 0.5f );
//        glVertex3f(-x, y , 0);
//        angle = angle + angle_stepsize;
//    }
//    glVertex3f(radius, 0.0, height);
//    glEnd();
//}

struct Point3d Normalize(struct Point3d p)
{
    double length = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
    p.x /= length;
    p.y /= length;
    p.z /= length;
    return p;
}

struct Point3d computeNormal(struct Point3d p1, struct Point3d p2, struct Point3d center)
{
    p1.x = p1.x - center.x;
    p1.y = p1.y - center.y;
    p1.z = p1.z - center.z;
    
    p2.x = p2.x - center.x;
    p2.y = p2.y - center.y;
    p2.z = p2.z - center.z;
    
    return Normalize((struct Point3d) {
        .x = p1.y * p2.z - p1.z * p2.y,
        .y = -p1.x * p2.z + p1.z * p2.x,
        .z = p1.x * p2.y - p1.y * p2.x
    });
}

/**********************************************************
 * Draw cone
 **********************************************************/
void Cone(GLfloat radius, GLfloat height, GLubyte R, GLubyte G, GLubyte B)
{
    GLfloat x              = 0.0;
    GLfloat y              = 0.0;
    GLfloat angle          = 0.0;
    GLfloat angle_stepsize = 0.1;
    
    float color[] = {1,.5,.1, 1};
    float Emission[]  = {0.0,0.0,0.1*emission,1.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    
    glColor3ub(R-40,G-40,B-40);
    angle = 0.0;
    glBegin(GL_TRIANGLES);
    while( angle < 2*PI ) {
        x = radius * cos(angle);
        y = radius * sin(angle);
        
        float x1 = radius * cos(angle + angle_stepsize);
        float y1 = radius * sin(angle + angle_stepsize);
        
        struct Point3d p1 = {.x = x, .y = y, .z = 0};
        struct Point3d p2 = {.x = x1, .y = y1, .z = 0};
        struct Point3d center = {.x = 0, .y = 0, .z = height};
        struct Point3d normal = computeNormal(p1, p2, center);
        
        glNormal3f(normal.x, normal.y, normal.z);
        
        glTexCoord2f(0, 0); glVertex3d(0, 0, height);
        glTexCoord2f(1, 0); glVertex3d(x, y, 0);
        glTexCoord2f(1, 1); glVertex3d(x1, y1, 0);
    
        angle = angle + angle_stepsize;
    }
    
    glEnd();
    
    glColor3ub(R,G,B);
    angle = 0.0;
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    while( angle < 2*PI ) {

        x = radius * cos(angle);
        y = radius * sin(angle);
        
        glTexCoord2f( rep*0.5f * cos(angle) + 0.5f, rep * 0.5f * sin(angle) + 0.5f );
        glVertex3f(x, y , 0);
        angle = angle + angle_stepsize;
    }
    glVertex3f(radius, 0.0, 0);
    glEnd();
}


/**********************************************************
 *  Draw Cube
 **********************************************************/
void Cube(double red, double green, double blue)
{
    float color[] = {.9,.1,.4, 1};
    float Emission[]  = {0.0,0.0,0.1*emission,1.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    
    //  Cube
    glColor3f(red, green, blue);
    //  Front
    glBegin(GL_QUADS);
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    glEnd();
    //  Back
    glBegin(GL_QUADS);
    glNormal3f( 0, 0,-1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
    glEnd();
    //  Right
    glBegin(GL_QUADS);
    glNormal3f(+1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
    glEnd();
    //  Left
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    glEnd();
    //  Top
    glBegin(GL_QUADS);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    glEnd();
    //  Bottom
    glBegin(GL_QUADS);
    glNormal3f( 0,-1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
    glEnd();
}

/**********************************************************
 * Triangle
 **********************************************************/
void Triangle(double red, double green, double blue)
{
    glPushMatrix();
    
    float color[] = {1,.5,.1, 1};
    float Emission[]  = {0.0,0.0,0.1*emission,1.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    
    glBegin(GL_TRIANGLES);
    glColor3f(red, green, blue);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(-1, 0, 0);
    glTexCoord2f(0, 1); glVertex3f(1, 0, 0);
    glTexCoord2f(.5, .5); glVertex3f(0, 1, 0);
    glEnd();
    
    glPopMatrix();
}

/**********************************************************
 * Draw rectangle
 **********************************************************/
void Rectangle(double red, double green, double blue)
{
    glPushMatrix();
    
    float color[] = {1,.5,.1, 1};
    float Emission[]  = {0.0,0.0,0.1*emission,1.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    
    glNormal3f(0, 0, 1);
    glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
    glTexCoord2f(1, 0); glVertex3f(1, 0, 0);
    glTexCoord2f(1, 1); glVertex3f(1, 1, 0);
    glTexCoord2f(0, 1); glVertex3f(0, 1, 0);
    glEnd();
    
    glPopMatrix();
}


void CubeTextures(unsigned int front,
                 unsigned int back,
                 unsigned int right,
                 unsigned int left,
                 unsigned int top,
                 unsigned int bottom)
{
    float color[] = {1,.5,.1, 1};
    float Emission[]  = {0.0,0.0,0.1*emission,1.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shinyvec);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,color);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
    
    int rep = 1;
    //  Cube
    //glColor3f(1, 1, 1);
    //glColor3f(.5, .1, .1);
    
    //  Front
    glBindTexture(GL_TEXTURE_2D, front);
    glBegin(GL_QUADS);
    glNormal3f( 0, 0, 1);
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(rep,0); glVertex3f(+1,-1, 1);
    glTexCoord2f(rep,rep); glVertex3f(+1,+1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    glEnd();
    
    //  Back
    glBindTexture(GL_TEXTURE_2D, back);
    glBegin(GL_QUADS);
    glNormal3f( 0, 0,-1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(rep,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(rep,rep); glVertex3f(-1,+1,-1);
    glTexCoord2f(0,rep); glVertex3f(+1,+1,-1);
    glEnd();
    
    //  Right
    glBindTexture(GL_TEXTURE_2D, right);
    glBegin(GL_QUADS);
    glNormal3f(+1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,rep); glVertex3f(+1,+1,+1);
    glEnd();
    
    //  Left
    glBindTexture(GL_TEXTURE_2D, left);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(rep,0); glVertex3f(-1,-1,+1);
    glTexCoord2f(rep,rep); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,rep); glVertex3f(-1,+1,-1);
    glEnd();
    
    //  Top
    glBindTexture(GL_TEXTURE_2D, top);
    glBegin(GL_QUADS);
    glNormal3f( 0,+1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(rep,0); glVertex3f(+1,+1,+1);
    glTexCoord2f(rep,rep); glVertex3f(+1,+1,-1);
    glTexCoord2f(0,rep); glVertex3f(-1,+1,-1);
    glEnd();
    
    //  Bottom
    glBindTexture(GL_TEXTURE_2D, bottom);
    glBegin(GL_QUADS);
    glNormal3f( 0,-1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(rep,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(rep,rep); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,rep); glVertex3f(-1,-1,+1);
    glEnd();
}

void CubeTexture(unsigned int sides, unsigned int top)
{
    CubeTextures(sides, sides, sides, sides, top, sides);
}