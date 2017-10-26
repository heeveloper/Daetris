//
//  truck.hpp
//  Kimchi
//
//  Created by  Heejun Lee on 9/19/17.
//
//

#ifndef truck_hpp
#define truck_hpp

#include <stdio.h>
#include "ofMain.h"

class Truck{
public:
    ofImage img;
    ofImage smoke;
    ofImage smoke_2;

    static const int fixed_x = 181, fixed_y = 3940-950;
    static const int smoke_fixed_x = 45, smoke_fixed_y = 3041;
    static const int TRUCK_WIDTH = 739;
    static const int TRUCK_HEIGHT = 328;
    int pos_x;
    int smoke_pos_x, smoke_pos_y;
    int frame_cnt;
    
    bool isArrived;
    int truck_state;    // 0:default 1:go right 2:come back
    //static int load_count;     // The number of loads
    
    void setup();
    void update();
    void draw();
    void smoke_init(int x, int y);
};

#endif /* truck_hpp */
