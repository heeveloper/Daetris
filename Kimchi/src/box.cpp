//
//  box.cpp
//  kimchi
//
//  Created by 정구열 on 2017. 10. 2..
//

#include "box.hpp"

int Box::box_cnt=0;
const int Box::DESTINATION_X[5]={199,199+158,199+316,199+79,199+237}, Box::DESTINATION_Y[5]={3840-666,3840-666,3840-666,3840-556,3840-556};

void Box::setup(int idx, int pos_x, int pos_y, int width, int height){
    this->index = idx;
    boxImg.load("images/box.png");
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->vel_x = (DESTINATION_X[idx] - this->pos_x) / 50;
    this->vel_y = (DESTINATION_Y[idx] - this->pos_y) / 50;
    this->width = width;
    this->height = height;
}

void Box::update(){
    // Go with the truck
    if(state == 2 && box_cnt == 5 && isStart){
        pos_x += 5;
        if(pos_x >= 1800){
            state=0;
        }
    }
    // Default
    if(state == 0){
        
    }
    // Go on the truck
    else if(state == 1){
        pos_x += vel_x;
        pos_y += vel_y;
        if(pos_y > DESTINATION_Y[index]){
            pos_x = DESTINATION_X[index];
            pos_y = DESTINATION_Y[index];
            state = 2;
            box_cnt++;
        }
    }
}
void Box::init(){
    this->pos_x = 435;
    this->pos_y = 2880;
    this->width = 158;
    this->height = 110;
    this->state = 0;
    this->isStart = false;
}

void Box::draw(){
    if(state == 1 || state == 2)
        boxImg.draw(pos_x, pos_y, width, height);
}
