//
//  main.c
//  hw2
//
//  Created by Sunil on 6/12/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include "main.h"
#include "vector.h"

int axes = 0;  //  Display axes
int th = 16;   //  Azimuth of view angle
int ph = 22;   //  Elevation of view angle
int fov = 50;                  //  Field of view (for perspective)
double asp = 1;                //  Aspect ratio
double dim = 512 * 2;          //  Size of world
enum MODE mode = EXPLORE;  //  Projection mode

int lmove = 1;  // toggle light movement
int rep = 1;
double mspeed = 0.;

unsigned int tex[20];  // textures

// light parameters
int light = 1;      //  Lighting
int distance = 1024;  // Light distance
int smooth = 1;     // Smooth/Flat shading
int emission = 0;   // Emission intensity (%)
int ambient = 30;   // Ambient intensity (%)
int diffuse = 100;  // Diffuse intensity (%)
int specular = 0;   // Specular intensity (%)
int shininess = 0;  // Shininess (power of two)
float shinyvec[1];  // Shininess (value)
int zhlight = 90;   // Light azimuth
float ylight = 5;   // Elevation of light

double zh = 0;  // roatation angle for wings of windmill around y
double speed = 0;

char* text[] = {"Drive", "Explore", "World view"};

//////////////////////////////////////////////////
// Camera position in world view mode
//////////////////////////////////////////////////
struct Point3d camera = {.x = 0, .y = 0, .z = 10};
struct Point3d lookAt = {.x = 0, .y = 0, .z = 10};
struct Point3d upVector = {.x = 0, .y = 1, .z = 0};

//////////////////////////////////////////////////
// Camera position in first person(explore) mode
//////////////////////////////////////////////////
struct Point3d fcamera = {.x = 30, .y = 9, .z = 0};
struct Point3d flookAt = {.x = 0, .y = 0, .z = 0};
struct Point3d fupVector = {.x = 0, .y = 1, .z = 0};

///////////////////////////////////////////////////
// Variables to keep track of the truck direction.
///////////////////////////////////////////////////
struct vector dirVec = {1, 0, 0};
struct vector upVec = {0, 1, 0};
struct vector rightVec = {0, 0, 1};

///////////////////////////////////////
// Variables for drawing broken truck
///////////////////////////////////////
double bx = 0, bz = 0;
double ex = 0, ez = 0;
double tx = 0, tz = 0;
double wx = 0, wz = 0;
double rot = 0;

/**********************************************************
 * Extern functions
 **********************************************************/
extern void DrawTruck();
extern void movingTruck();
extern void DrawWindmill();
extern void DrawHouse();
extern void drawRoad();
extern void DrawApartment();
extern void DrawTrafficSignal();
extern void DrawTree();
extern void DrawWindmillhouse();
extern void BrokenTruck();

void Drawcar();

double tpos[3];
double yaw = 0;

/************************************
 variables to keep track of the objects
 in the scene for collision detection.
 *************************************/
double trees[16][16][4];
double buildings[16][16][4];
double roads[16][16][4];
double signs[16][16][2];

// Keep windmills to low. Too many mills animation
// lead to poor performance.
double mills[5][5][2];
int collided = 0;

double road_width = 14;

////////////////////////////////
// stauts message for the user
////////////////////////////////
char status[20] = "";

/**********************************************************
  Define SDL if sound is required using -DSDL 
  during compilation.
**********************************************************/

#ifdef SDL

#include <SDL/SDL_mixer.h>

Mix_Music* music = NULL;
Mix_Chunk* truck = NULL;
Mix_Chunk* crash = NULL;
Mix_Chunk* screech = NULL;

void init_sdl() {
    printf("sdl init\n");
    if (Mix_OpenAudio(4410, AUDIO_S16SYS, 1, 4096))
        Fatal("Cannot initialize audio\n");
    
    music = Mix_LoadMUS("sounds/truck.wav");
    if (!music) Fatal("cannot load ./sounds/truck.wav");
    
    crash = Mix_LoadWAV("sounds/smash.wav");
    if (!music) Fatal("cannot load ./sounds/smash.wav");
    
    screech = Mix_LoadWAV("sounds/squeal.wav");
    if (!music) Fatal("cannot load ./sounds/squeal.wav");
    
    Mix_PlayMusic(music, -1);
    Mix_PauseMusic();
}

void free_sdl() {
    Mix_FreeMusic(music);
    Mix_FreeChunk(crash);
    
    Mix_CloseAudio();
}

void stop_chunk(int value) {
    printf("stopping crashing sound");
    Mix_PauseMusic();
    Mix_HaltMusic();
    
    Mix_PlayMusic(music, -1);
    Mix_PauseMusic();
}

#endif

void data_init() {
    tpos[0] = 0;
    tpos[1] = 2;
    tpos[2] = 4;
    
    double x, z, rot, r;
    for (int i = 0; i < 16; i++) {
        z = 512 - (64 * i);
        for (int j = 0; j < 16; j++) {
            x = -512 + (64 * j);
            
            rot = j % 2 == 0 ? 90 : -90;
            r = x + 5;
            trees[i][j][0] = r;
            r = z - 5;
            trees[i][j][1] = r;
            trees[i][j][2] = rot;
            r = (rand()*rand()) % 3;
            trees[i][j][3] = r+1;
            
            rot = (rand()  * rand()) % 360;
            r = x + 20;
            buildings[i][j][0] = r;
            r = z - 20;
            buildings[i][j][1] = r;
            buildings[i][j][2] = rot;
            
            r = (rand()*rand()) % 3;
            buildings[i][j][3] = r + 1;
            
            signs[i][j][0] = x + 64 - road_width;
            signs[i][j][1] = z - 64 + road_width;
        }
    }
    
    // wind mills
    for (int i = 0; i < 5; i++) {
        z = 512 - (64 * i);
        for (int j = 0; j < 5; j++) {
            x = -512 + (64 * j);
            r = x + 10;
            mills[i][j][0] = r;
            r = z - 30;
            mills[i][j][1] = r;
        }
    }
}

void key(unsigned char ch, int x, int y);

void Exit(unsigned char ch, int x, int y) {
    if (ch == 27) {
        exit(0);
    } else if (ch == '0') {
        // Reset everything
        axes = 0;
        th = ph = 0;
        fov = 55;
        tpos[0] = 0;
        tpos[1] = 2;
        tpos[2] = 3;
        collided = 0;
        yaw = 0;
        bx = bz = ex = ez = tx = tz = wx = wz = rot = 0.;
        glutKeyboardFunc(key);
    }
}

void look_for_collision() {
    
    if (collided) {
        // no need to check for anymore collision
        // truck is already broken
        return;
    }
    
    double truckX = tpos[0];
    //double truckY = tpos[1];
    double truckZ = tpos[2];
    
    // Collision with min or max of x-axis
    if (truckX < -512 || truckX > 512) {
        printf("outside of x\n");
        strcpy(status, "Outside of world");
        collided = 1;
        mspeed = 0;
#ifdef SDL
        Mix_PlayChannel(-1, crash, 0);
        Mix_PauseMusic();
        mspeed = 0;
#endif
        return;
    }
    // Collision with min or max of z-axis
    if (truckZ < -512 || truckZ > 512) {
        printf("outside of z\n");
        strcpy(status, "Outside of world");
        collided = 1;
        mspeed = 0;
#ifdef SDL
        Mix_PlayChannel(-1, crash, 0);
        Mix_PauseMusic();
        mspeed = 0;
#endif
        return;
    }
    
    int offroad = 0;
    
    // bounds for the roads
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if ((roads[i][j][0] <= truckX && roads[i][j][1] >= truckZ &&
                 roads[i][j][2] >= truckX && roads[i][j][3] <= truckZ)) {
                offroad = 1;
                break;
            }
        }
    }
    
    if (offroad) {
        printf("you are heading offroad...[%f, %f]\n", tpos[0], tpos[2]);
        strcpy(status, "Off road");
    } else {
        printf("you are heading onroad...[%f, %f]\n", tpos[0], tpos[2]);
        strcpy(status, "On road");
    }
    
    double x, z;
    int i, j;
    const double HOUSE_TOL = 5;
    const double APT_TOL = 9.5;
    const double TREE_TOL = 1.7;
    
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++) {
            x = trees[i][j][0];
            z = trees[i][j][1];
            if (truckX <= (x + TREE_TOL) && truckX >= (x - TREE_TOL)) {
                if (truckZ <= (z + TREE_TOL) && truckZ >= (z - TREE_TOL)) {
                    printf("collision by tree\n");
                    strcpy(status, "Hit a tree");
                    collided = 1;
                    mspeed = 0;
#ifdef SDL
                    Mix_PlayChannel(-1, crash, 0);
                    Mix_PauseMusic();
                    mspeed = 0;
#endif
                    break;
                }
            }
        }
    
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++) {
            x = buildings[i][j][0];
            z = buildings[i][j][1];
            double tol = HOUSE_TOL;
            if ((i+j) % 2) tol = APT_TOL;
            if (truckX <= (x + tol) && truckX >= (x - tol)) {
                if (truckZ <= (z + tol) && truckZ >= (z - tol)) {
                    if ((i+j) % 2) {
                        printf("collision by a Apartment\n");
                        strcpy(status, "Hit a Apartment");
                    }
                    else {
                        printf("collision by a house\n");
                        strcpy(status, "Hit a house");
                    }
                    collided = 1;
                    mspeed = 0;
#ifdef SDL
                    Mix_PlayChannel(-1, crash, 0);
                    Mix_PauseMusic();
                    mspeed = 0;
#endif
                    break;
                }
            }
        }
    
    const double SIGN_TOL = 1.2;
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 16; j++) {
            x = signs[i][j][0];
            z = signs[i][j][1];
            if (truckX <= (x + SIGN_TOL) && truckX >= (x - SIGN_TOL)) {
                if ((truckZ <= (z + SIGN_TOL) && truckZ >= (z - SIGN_TOL))) {
                    printf("collision by a traffic sign\n");
                    strcpy(status, "Hit a traffic sign");
                    collided = 1;
                    mspeed = 0;
#ifdef SDL
                    Mix_PlayChannel(-1, crash, 0);
                    Mix_PauseMusic();
                    mspeed = 0;
#endif
                    break;
                }
            }
        }
    }
    
#ifdef SDL
    
    if (collided) {
        printf("register for timer func\n");
        glutTimerFunc(500, stop_chunk, 0);
        glutKeyboardFunc(Exit);
    }
    
#endif
}

void draw_sky() {
    glPushMatrix();
    
    glColor3f(1, 1, 1);
    
    // back
    glBindTexture(GL_TEXTURE_2D, tex[17]);
    glNormal3f(0, 0, 1);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(-512, 0, -512);
    glTexCoord2d(0, 1); glVertex3f(-512, 512 / 2, -512);
    glTexCoord2d(1, 1); glVertex3f(512, 512 / 2, -512);
    glTexCoord2d(1, 0); glVertex3f(512, 0, -512);
    glEnd();
    
    // right
    glBindTexture(GL_TEXTURE_2D, tex[17]);
    glNormal3f(-1, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(512, 0, -512);
    glTexCoord2d(0, 1); glVertex3f(512, 512 / 2, -512);
    glTexCoord2d(1, 1); glVertex3f(512, 512 / 2, 512);
    glTexCoord2d(1, 0); glVertex3f(512, 0, 512);
    glEnd();
    
    // left
    glBindTexture(GL_TEXTURE_2D, tex[17]);
    glNormal3f(1, 0, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(-512, 0, 512);
    glTexCoord2d(0, 1); glVertex3f(-512, 512 / 2, 512);
    glTexCoord2d(1, 1); glVertex3f(-512, 512 / 2, -512);
    glTexCoord2d(1, 0); glVertex3f(-512, 0, -512);
    glEnd();
    
    // top
    glBindTexture(GL_TEXTURE_2D, tex[17]);
    glNormal3f(0, -1, 0);
    glBegin(GL_QUADS);
    glTexCoord2d(0, 0); glVertex3f(-512, 512 / 2, -512);
    glTexCoord2d(0, 1); glVertex3f(512, 512 / 2, -512);
    glTexCoord2d(1, 1); glVertex3f(512, 512 / 2, 512);
    glTexCoord2d(1, 0); glVertex3f(-512, 512 / 2, 512);
    glEnd();
    
    // front
    glBindTexture(GL_TEXTURE_2D, tex[17]);
    glNormal3f(0, 0, -1);
    glBegin(GL_QUADS);
    glTexCoord2f(0., 0.); glVertex3f(-512, 0, 512);
    glTexCoord2f(0., 1.); glVertex3f(-512, 512 / 2, 512);
    glTexCoord2f(1., 1.); glVertex3f(512, 512 / 2, 512);
    glTexCoord2f(1., 0.); glVertex3f(512, 0, 512);
    glEnd();
    
    glPopMatrix();
}

void draw_land() {
    draw_sky();
    
    glPushMatrix();
    
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    
    int x = 0, z = 0;
    
    for (int i = 0; i < 16; i++) {
        z = 512 - (64 * i);
        for (int j = 0; j < 16; j++) {
            x = -512 + (64 * j);
            
            roads[i][j][0] = x;
            roads[i][j][1] = z;
            roads[i][j][2] = x + 64 - road_width;
            roads[i][j][3] = z - 64 + road_width;
            
            // lawn
            glBindTexture(GL_TEXTURE_2D, tex[5]);
            glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);
            glTexCoord2f(0, 0);
            glVertex3d(x, 0, z);
            glTexCoord2f(2, 0);
            glVertex3d(x + 64 - road_width, 0, z);
            glTexCoord2f(2, 2);
            glVertex3d(x + 64 - road_width, 0, z - 64 + road_width);
            glTexCoord2f(0, 2);
            glVertex3d(x, 0, z - 64 + road_width);
            glEnd();
            
            // horizantal roads
            glBindTexture(GL_TEXTURE_2D, tex[3]);
            glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);
            glTexCoord2f(0, 0);
            glVertex3d(x, 0, z - 64 + road_width);
            glTexCoord2f(1, 0);
            glVertex3d(x, 0, z - 64);
            glTexCoord2f(1, 1);
            glVertex3d(x + 64, 0, z - 64);
            glTexCoord2f(0, 1);
            glVertex3d(x + 64, 0, z - 64 + road_width);
            glEnd();
            
            // vertical roads
            glBindTexture(GL_TEXTURE_2D, tex[4]);
            glBegin(GL_QUADS);
            glNormal3f(0, 1, 0);
            glTexCoord2f(0, 0);
            glVertex3d(x + 64 - road_width, 0, z);
            glTexCoord2f(1, 0);
            glVertex3d(x + 64 - road_width, 0, z - 64 + road_width);
            glTexCoord2f(1, 1);
            glVertex3d(x + 64, 0, z - 64 + road_width);
            glTexCoord2f(0, 1);
            glVertex3d(x + 64, 0, z);
            glEnd();
        }
    }
    
    glPopMatrix();
}

void draw_scene() {
    draw_land();
    
    int i = 0, j = 0;
    // Draw the trees in the scene
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++) {
            glPushMatrix();
            glTranslatef(trees[i][j][0], 4, trees[i][j][1]);
            glRotatef(trees[i][j][2], 0, 1, 0);
            double s = trees[i][j][3];
            s = s == 0? 1 : fabs(s);
            glScalef(.5, s, .5);
            DrawTree();
            glPopMatrix();
        }
    
    // Draw the houses in the scene
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++) {
            glPushMatrix();
            double c = (i*j)/(16);
            glColor3f(1, c/2, i*c/3);
            if ((i+j) % 2) {
                glTranslatef(buildings[i][j][0], 5, buildings[i][j][1]);
                glRotatef(buildings[i][j][2], 0, 1, 0);
                double s = buildings[i][j][3];
                glScalef(2, s==0? 1:fabs(s), 2);
                
                DrawApartment();
            }
            else {
                glTranslatef(buildings[i][j][0], 2, buildings[i][j][1]);
                glRotatef(buildings[i][j][2], 0, 1, 0);
                double s = buildings[i][j][3];
                glScalef(1.5, s==0? 1:fabs(s), 1.5);
                DrawHouse();
            }
            
            glPopMatrix();
        }
    
    for (i = 0; i < 16; i++)
        for (j = 0; j < 16; j++) {
            glPushMatrix();
            glTranslatef(signs[i][j][0], -2, signs[i][j][1]);
            glRotatef(-90, 0, 1, 0);
            DrawTrafficSignal();
            glPopMatrix();
        }
    
    glPushMatrix();
    glTranslated(15, 1, 20);
    glRotated(-125, 0, 1, 0);
    DrawWindmill();
    glPopMatrix();
    
    if (mode == DRIVE) {
        look_for_collision();
    }
    
    Drawcar();
}

/**********************************************************
 *  Draw Axes
 **********************************************************/
void DrawAxes() {
    const double len = dim;  //  Length of axes
    
    //  Draw axes
    glBegin(GL_LINES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(len, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, len, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, len);
    glEnd();
    //  Label axes
    glRasterPos3d(len, 0.0, 0.0);
    Print("X");
    glRasterPos3d(0.0, len, 0.0);
    Print("Y");
    glRasterPos3d(0.0, 0.0, len);
    Print("Z");
}

/**********************************************************
 *  setup view
 **********************************************************/
void SetupView() {
    if (mode == WORLD_VIEW){
        camera = (struct Point3d){
            .x = -2 * dim * Sin(th) * Cos(ph),
            .y = +2 * dim * Sin(ph),
            .z = +2*dim*Cos(th)*Cos(ph)
        };
        
        gluLookAt(camera.x, camera.y, camera.z, 0, 2, 0, 0, Cos(ph), 0);
    }
    // First person view
    else if(mode == EXPLORE){
        // Recalculate where the camera is looking
        flookAt.x = -2 * dim * Sin(th) * Cos(ph);
        flookAt.y = -2 * dim * Sin(ph);
        flookAt.z = -2 * dim * Cos(th) * Cos(ph);
        
        // Orient the scene so it imitates first person movement
        gluLookAt(fcamera.x, fcamera.y, fcamera.z,
                  flookAt.x + fcamera.x, flookAt.y + fcamera.y, flookAt.z + fcamera.z, fupVector.x, fupVector.y, fupVector.z);
    }
    else if (mode == DRIVE) {
        double behindX = 3 * 10 * dirVec.x;
        double behindY = 3 * 10 * dirVec.y;
        double behindZ = 3 * 10 * dirVec.z;
        
        double heightX = 3 * 3 * upVec.x;
        double heightY = 3 * 3 * upVec.y;
        double heightZ = 3 * 3 * upVec.z;
        
        // keep the camera behind the truck while in drive mode
        gluLookAt(tpos[0] - behindX + heightX, tpos[1] - behindY + heightY,  tpos[2] - behindZ + heightZ, tpos[0], tpos[1], tpos[2], upVec.x, upVec.y, upVec.z);
        
    }
}

//static void ball(double x, double y, double z, double r) {
//    //  Save transformation
//    glPushMatrix();
//    //  Offset, scale and rotate
//    glTranslated(x, y, z);
//    glScaled(r, r, r);
//    //  White ball
//    glColor3f(1, 1, 1);
//    glutSolidSphere(1.0, 16, 16);
//    //  Undo transofrmations
//    glPopMatrix();
//}

void setupLight() {
    if (light) {
        //  Translate intensity to color vectors
        float Ambient[] = {0.01 * ambient, 0.01 * ambient, 0.01 * ambient, 1.0};
        float Diffuse[] = {0.01 * diffuse, 0.01 * diffuse, 0.01 * diffuse, 1.0};
        float Specular[] = {0.01 * specular, 0.01 * specular, 0.01 * specular, 1.0};
        //  Light position
        //float Position[]  = {-distance*Cos(zh),ylight,distance*Sin(zh), 1.0};
        float Position[] = {0, 128, 0, 1.0};
        //  Draw light position as ball (still no lighting here)
        //ball(Position[0], Position[1], Position[2], 2);
        
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, Ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, Diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, Specular);
        glLightfv(GL_LIGHT0, GL_POSITION, Position);
    } else
        glDisable(GL_LIGHTING);
}

/**********************************************************
 *  Render the 3d scene
 **********************************************************/
void RenderScene() {
    glShadeModel(GL_SMOOTH);
    
    //  OpenGL should normalize normal vectors
    glEnable(GL_NORMALIZE);
    
    // enable cull facing for performance
    //   #warning "Cull face disabled! Fix triangles and rectangles"
    // glEnable(GL_CULL_FACE);
    
    setupLight();
    
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    draw_scene();
    
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
    glColor3f(1, 1, 1);
    if (axes) {
        DrawAxes();
    }
}

/**********************************************************
 *  Display params on the scene for debug
 **********************************************************/
void DisplayParams() {
    //  Display parameters
    glWindowPos2i(5, 5);
    Print("Angle=%d,%d  Dim=%.1f FOV=%d Mode=%s Light=%s", th, ph, dim, fov,
          text[mode], light ? "On" : "Off");
    if (mode == DRIVE) {
        glWindowPos2i(5, 25);
        Print("X = %.2f Z = %.2f", tpos[0], tpos[2]);
    }
    
    glWindowPos2i(5, 45);
    glColor3f(1, 0, 0);
    Print("%s", status);
}

/**********************************************************
 *  OpenGL (GLUT) calls this routine to display the scene
 **********************************************************/
void display() {
    glPushMatrix();
    
    //  Erase the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //  Enable Z-buffering in OpenGL
    glEnable(GL_DEPTH_TEST);
    
    // enable cull face for optimization
    // glEnable(GL_CULL_FACE);
    
    //  Undo previous transformations
    glLoadIdentity();
    
    SetupView();
    
    RenderScene();
    
    DisplayParams();
    
    // Check for any errors that have occurred
    ErrCheck("display");
    
    //  Render the scene and make it visible
    glFlush();
    glutSwapBuffers();
    
    glPopMatrix();
}

/**********************************************************
 *  GLUT calls this routine when an arrow key is pressed
 **********************************************************/
void special(int key, int x, int y) {
    const int FACTOR = 1;
    
    switch (key) {
        case GLUT_KEY_RIGHT:
            //  Right arrow key - increase angle
            th -= FACTOR;
            break;
        case GLUT_KEY_LEFT:
            //  Left arrow key - decrease angle
            th += FACTOR;
            break;
        case GLUT_KEY_UP:
            //  Up arrow key - increase elevation
            ph -= FACTOR;
            break;
        case GLUT_KEY_DOWN:
            //  Down arrow key - decrease elevation
            ph += FACTOR;
            break;
        case GLUT_KEY_PAGE_UP:
            //  PageUp key - increase dim
            dim += 0.1;
            break;
        case GLUT_KEY_PAGE_DOWN:
            //  PageDown key - decrease dim
            dim -= 0.1;
            break;
        case GLUT_KEY_F3:
            distance += 1;
            break;
        case GLUT_KEY_F4:
            distance -= 1;
            break;
        default:
            break;
    }
    
    //  Keep angles to +/-360 degrees
    //  Keep angles to +/-360 degrees
    th %= 360;
    ph %= 360;
    
    // Reproject
    Project(fov, asp, dim);
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/**********************************************************
 * On Idle of openGL
 **********************************************************/
void idle() {
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    zh = fmod(90 * t, 360);
    speed += 1.5;
    glutPostRedisplay();
}

double old_yaw = 0;

/**********************************************************
 *  GLUT calls this routine when a key is pressed
 **********************************************************/
void key(unsigned char ch, int x, int y) {
    switch (ch) {
        case 27:
            exit(0);
            
        case '0':
            // Reset everything
            axes = 0;
            th = ph = 0;
            fov = 55;
            tpos[0] = 0;
            tpos[1] = 2;
            tpos[2] = 3;
            collided = 0;
            yaw = 0;
            bx = bz = ex = ez = tx = tz = wx = wz = rot = 0.;
            break;
            
        case 32: // space (disk brake)
            mspeed = 0;
#ifdef SDL
            if (Mix_PlayingMusic()) {
                Mix_PauseMusic();
            }
#endif
            break;
            
        case 'd':
            yaw -= 2.5;
#ifdef SDL
            if (fabs(yaw - old_yaw) >= 20 && fabs(mspeed) > 1) {
                old_yaw = yaw;
                Mix_PlayChannel(-1, screech, 0);
                //Mix_PauseMusic();
            }
#endif
            break;
        case 'a':
            yaw += 2.5;
#ifdef SDL
            if (fabs(yaw - old_yaw) >= 20 && fabs(mspeed) > 1) {
                old_yaw = yaw;
                Mix_PlayChannel(-1, screech, 0);
            }
#endif
            break;
            
        case 'w':
            mspeed += .1;
#ifdef SDL
            Mix_ResumeMusic();
            printf("playing music...\n");
#endif
            break;
        case 'z':
            mspeed -= .1;
#ifdef SDL
            if (!mspeed) Mix_PauseMusic();
#endif
            break;
            
        case 'A':
            //  Toggle axes
            axes = 1 - axes;
            break;
            
        case 'X':
            //  Reset view angle
            // Look down x-axis
            th = -90;
            ph = 0;
            camera.x = 2 * dim;
            camera.z = 0;
            break;
            
        case 'Y':
            // Look down y-axis
            th = 0;
            ph = 90;
            break;
            
        case 'Z':
            // Look down z-axis
            th = ph = 0;
            camera.x = 0;
            camera.z = 2 * dim;
            break;
            
        case '-':
            //  Change field of view angle
            if (fov > 1) fov--;
            break;
            
        case '+':
            //  Change field of view angle
            if (fov < 200) fov++;
            break;
            
        case 'f':
            if (mode == EXPLORE){
                // Move forward in the scene
                fcamera.x += flookAt.x * .001;
                fcamera.z += flookAt.z * .001;
            }
            break;
            
        case 'b':
            if (mode == EXPLORE) {
                // Move backward in the scene
                fcamera.x -= flookAt.x * .001;
                fcamera.z -= flookAt.z * .001;
            }
            break;
            
        case 'm':
            //  Switch display mode
            mode = (mode + 1) % 2;
            break;
            
        case '[':
            //  Light elevation
            ylight -= 10;
            break;
            
        case ']':
            ylight += 10;
            break;
            
        case 's':
            light = 1 - light;
            break;
            
        case 'l':
            lmove = 1 - lmove;
            glutIdleFunc(lmove ? idle : NULL);
            break;
            
        default:
            break;
    }
    
    // Reproject
    Project(fov, asp, dim);
    
    //  Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

void determine_vectors() {
    dirVec.x = Cos(yaw);
    dirVec.z = -Sin(yaw);
    dirVec = normalize(dirVec);
    
    rightVec = cross_product(dirVec, upVec);
    rightVec = normalize(rightVec);
}

void timer(int value) {
    tpos[0] += dirVec.x * mspeed;
    tpos[1] += dirVec.y * mspeed;
    tpos[2] += dirVec.z * mspeed;
    
    // turnleftright();
    determine_vectors();
    
    glutTimerFunc(value, timer, 100);
    glutPostRedisplay();
}

/**********************************************************
 *  GLUT calls this routine when the window is resized
 **********************************************************/
void reshape(int width, int height) {
    //  Ratio of the width to the height of the window
    asp = (height > 0) ? (double)width / height : 1;
    //  Set the viewport to the entire window
    glViewport(0, 0, width, height);
    //  Set projection
    Project(fov, asp, dim);
}

void Drawcar() {
    double mat[16];
    mat[0] = dirVec.x;
    mat[4] = upVec.x;
    mat[8] = rightVec.x;
    
    mat[12] = 0;
    mat[1] = dirVec.y;
    mat[5] = upVec.y;
    mat[9] = rightVec.y;
    
    mat[13] = 0;
    mat[2] = dirVec.z;
    mat[6] = upVec.z;
    mat[10] = rightVec.z;
    
    mat[14] = 0;
    mat[3] = 0;
    mat[7] = 0;
    
    mat[11] = 0;
    mat[15] = 1;
    
    // center right truck
    glPushMatrix();
    glTranslated(tpos[0], 1, tpos[2]);
    
    glMultMatrixd(mat);
    
    if (!collided) DrawTruck();
    else BrokenTruck();
    
    //    DrawTruck();
    glPopMatrix();
}

/**********************************************************
 *  Start up GLUT and tell it what to do
 **********************************************************/
int main(int argc, char* argv[]) {
#ifdef SDL
    init_sdl();
#endif
    
    data_init();
    
    //  Initialize GLUT
    glutInit(&argc, argv);
    
    //  Request double buffered, true color window with Z buffering at 600x600
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    //glutInitWindowSize(800, 800);
    
    glutCreateWindow("Sunil");
    glutFullScreen();
    
    //  Set callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    
    tex[0] = LoadTexBMP("img/tank.bmp");
    tex[1] = LoadTexBMP("img/tyre.bmp");
    tex[2] = LoadTexBMP("img/front.bmp");
    tex[3] = LoadTexBMP("img/hroad.bmp");
    tex[4] = LoadTexBMP("img/vroad.bmp");
    tex[5] = LoadTexBMP("img/grass.bmp");
    tex[6] = LoadTexBMP("img/apartment.bmp");
    tex[7] = LoadTexBMP("img/aptroof.bmp");
    tex[8] = LoadTexBMP("img/wood.bmp");
    tex[9] = LoadTexBMP("img/blades.bmp");
    tex[10] = LoadTexBMP("img/house.bmp");
    tex[11] = LoadTexBMP("img/roof.bmp");
    tex[12] = LoadTexBMP("img/traffic.bmp");
    tex[13] = LoadTexBMP("img/tree.bmp");
    tex[14] = LoadTexBMP("img/bark.bmp");
    tex[15] = LoadTexBMP("img/base.bmp");
    tex[16] = LoadTexBMP("img/truck-door.bmp");
    tex[17] = LoadTexBMP("img/fsky.bmp");
    tex[18] = LoadTexBMP("img/tsky.bmp");
    
    ErrCheck("Main");
    glutTimerFunc(0, timer, 100);
    //  Pass control to GLUT so it can interact with the user
    glutMainLoop();
    
#ifdef SDL
    
    free_sdl();
    
#endif
    
    return 0;
}
