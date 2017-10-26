//
//  score.hpp
//  Kimchi
//
//  Created by  Heejun Lee on 9/14/17.
//
//

#ifndef score_hpp
#define score_hpp

#include <stdio.h>
#include "ofMain.h"

class Score{
public:
    static const int SCORE_WIDTH = 120;
    static const int SCORE_HEIGHT = 270;
    static const int fixed_y = 1920*2 - 300;
    static const int floating_y = 20;
    static bool checked;
    int pos_x, pos_y;
    int dir;
    int score_count;
    int score_state;  // 0:default 1:checked(move up) 2:checked(move down)
    ofImage number[4][10];
    void setup();
    void update();
    void draw();
};

#endif /* score_hpp */
