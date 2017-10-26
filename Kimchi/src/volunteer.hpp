//
//  volunteer.hpp
//  Kimchi
//
//  Created by  Heejun Lee on 9/13/17.
//
//

#ifndef volunteer_hpp
#define volunteer_hpp

#include <stdio.h>
#include "ofMain.h"



class Volunteer{
private:
    int idx;
public:
    Volunteer(int i);
    ofImage img,img2,img3;
    ofImage vol;
    int pos_x, pos_y;
    int width;
    int height;
    int delay;
    void setup();
    void update();
    void draw();
    int getIdx(){return idx;};
};

#endif /* volunteer_hpp */
