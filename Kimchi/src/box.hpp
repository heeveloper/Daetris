//
//  box.hpp
//  kimchi
//
//  Created by 정구열 on 2017. 10. 2..
//

#ifndef box_hpp
#define box_hpp

#include "ofMain.h"
#include <stdio.h>

class Box{
private:
    int index;
    int state; // 0 : stop, 1: go on the truck, 2: go with the truck
public:
    int pos_x, pos_y;
    int vel_x, vel_y;
    int width, height;
    static bool isStart;
    static int box_cnt;
    const static int DESTINATION_X[5], DESTINATION_Y[5];
    
    //int getIndex(){return index;};
    //void setIndex(int idx){this->index=idx;};
    void setState(int idx){this->state = idx;};
    void update();
    void draw();
    void init();
    void setup(int idx, int pos_x, int pos_y, int width, int height);
    
    ofImage boxImg;
};
#endif /* box_hpp */
