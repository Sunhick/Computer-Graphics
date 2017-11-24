//
//  main.h
//  hw2
//
//  Created by Sunil on 6/12/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#ifndef MAIN_H
#define MAIN_H

#include <CSCIx229.h>

#define PI 3.1415927

/**********************************************************
 * Modes of viewing
 **********************************************************/
enum MODE {
  DRIVE = 0,
  EXPLORE,
  WORLD_VIEW
};

enum DIRECTION {
  LEFT = 0,
  RIGHT,
  FORWARD,
  BACKWARD,
  HALT
};

/**********************************************************
 * point 3d
 **********************************************************/
struct Point3d {
  double x;
  double y;
  double z;
};

/**********************************************************
 * Rotation vector
 **********************************************************/
struct Rotation {
  int pitch;
  int yaw;
  int roll;
};

/**********************************************************
 * Color format
 **********************************************************/
struct Color {
  double red;
  double green;
  double blue;
};

#endif /* MAIN_H */
