//
//  vector.h
//  xcode
//
//  Created by Sunil on 6/20/16.
//  Copyright © 2016 Sunil. All rights reserved.
//

#ifndef vector_h
#define vector_h

struct vector{
  double x;
  double y;
  double z;
};

struct vector cross_product(struct vector one, struct vector two);
struct vector normalize(struct vector one);


#endif /* vector_h */
