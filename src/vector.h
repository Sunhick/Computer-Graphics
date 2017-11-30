//
//  vector.h
//  xcode
//
//  Created by Sunil on 6/20/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#ifndef SRC_VECTOR_H_
#define SRC_VECTOR_H_

struct vector {
  double x;
  double y;
  double z;
};

struct vector cross_product(struct vector one, struct vector two);
struct vector normalize(struct vector one);

#endif  // SRC_VECTOR_H_
