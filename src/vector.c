//
//  vector.cpp
//  xcode
//
//  Created by Sunil on 6/20/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#include "vector.h"
#include <math.h>

struct vector cross_product(struct vector one, struct vector two){
  double x = one.y*two.z-one.z*two.y;
  double y = one.z*two.x-one.x*two.z;
  double z = one.x*two.y-one.y*two.x;
  return (struct vector){.x = x, .y = y, .z = z};
}

struct vector normalize(struct vector one) {
  double vectorLength = 0;
  vectorLength = sqrt(one.x*one.x+one.y*one.y+one.z*one.z);
  one.x = one.x/vectorLength;
  one.y = one.y/vectorLength;
  one.z = one.z/vectorLength;
  return one;
}
