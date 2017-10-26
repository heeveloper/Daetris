//
//  truck.cpp
//  Kimchi
//
//  Created by  Heejun Lee on 9/19/17.
//
//

#include "truck.hpp"

void Truck::setup(){
    img.load("images/truck.png");
    smoke.load("images/smoke.png");
    smoke_2.load("images/smoke_2.png");
    pos_x = fixed_x;
    smoke_pos_x = smoke_fixed_x;
    smoke_pos_y = smoke_fixed_y;
    frame_cnt = 0;
    isArrived = false;
}

void Truck::update(){
    if(truck_state == 0){
        
    }
    
    else if(truck_state == 1){  // move right and come back automatically
        pos_x += 5;
        frame_cnt++;
        if(frame_cnt%3==0)
            smoke_pos_x-=2;
        if(pos_x-250>smoke_pos_x){
            smoke.clear();
            smoke_2.clear();
            smoke_init(pos_x-135, smoke_fixed_y);
            frame_cnt=0;
        }
        if(pos_x >= 1200){
            truck_state = 2;
            pos_x = -1000;
            isArrived = true;
            smoke.clear();
            smoke_2.clear();
            smoke_init(pos_x-135, smoke_fixed_y);
        }
    }
    else if(truck_state == 2){   // come back
        pos_x += 5;
        frame_cnt++;
        
        if(frame_cnt%3==0)
            smoke_pos_x-=2;
        
        if(pos_x-250>smoke_pos_x){
            smoke.clear();
            smoke_2.clear();
            smoke_init(pos_x-135, smoke_fixed_y);
            frame_cnt=0;
        }
        
        if(pos_x >= fixed_x){
            pos_x = fixed_x;
            truck_state = 0;
            isArrived = false;
        }
    }
}

void Truck::draw(){
    img.draw(pos_x, fixed_y, TRUCK_WIDTH, TRUCK_HEIGHT);
    if(truck_state == 1 || truck_state == 2){
        smoke.draw(smoke_pos_x,smoke_pos_y);
        smoke_2.draw(smoke_pos_x+90,smoke_pos_y+103);
    }
}

void Truck::smoke_init(int x, int y){
    smoke.load("images/smoke.png");
    smoke_2.load("images/smoke_2.png");
    smoke_pos_x = x;
    smoke_pos_y = y;
}
