//
//  kimchi.hpp
//  Kimchi
//
//  Created by  Heejun Lee on 9/14/17.
//
//

#ifndef kimchi_hpp
#define kimchi_hpp

#include <stdio.h>
#include "ofMain.h"

class Kimchi{
public:
    int num;    // The index of Kimchi
    int yOfState[4]={2350, 2506, 2650,  2880};    // The position y of each kimchi states
    int xOfLoad[5];     // The position x of each load on truck
    ofImage img[5], curKimchi;
    int pos_x, pos_y;
    int width, height;
    int speed_x, speed_y;   // The distance ratio from the position of last state(3) kimchi to the its position on the truck
    static const int INTERVAL = 60;
    static const int KIMCHI_NUM = 5;
    int isMoving;   // 0: wait 1: on moving 2: arrived
    int state;  //0: 1: 2: 3:
    int volState;
    int frameCnt, delay;
    bool isLast=false;
    void setup();
    void update();
    void draw();
    void init();
};

#endif /* kimchi_hpp */
