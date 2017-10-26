//
//  kimchi.cpp
//  Kimchi
//
//  Created by  Heejun Lee on 9/14/17.
//
//

#include "kimchi.hpp"
#include "truck.hpp"

void Kimchi::setup(){
    for(int i=0; i<KIMCHI_NUM-1; i++){
        img[i].load("images/kimchi_" + std::to_string(i) + ".png");
    }
    
    curKimchi = img[0];
    width = 130;
    height = 180;
    state = 0;
    isMoving = 0;
    pos_x = 474;
    pos_y = 2270;
    frameCnt=0;
    delay=0;
    volState=0;
}

void Kimchi::update(){
    switch(isMoving){
        case 0:
            break;
        case 1:
            frameCnt++;
            pos_y+=3;
            if(frameCnt%3==0)
                height-=1;
            if(frameCnt%7==0)
                width-=1,pos_x++;
            if(pos_y>=yOfState[state]){
                this->isMoving++;
            }
            break;
        case 2:
            delay++;
            if(delay==90){
                state++;
            }
            else if(delay==INTERVAL*2){
                this->isMoving=0;
                this->volState++;
                delay=0;
                if(state==4){
                    width=158;
                    height=110;
                    isLast=true;
                }
            }
            break;
    }
}

void Kimchi::draw(){
    curKimchi=img[state];
    curKimchi.draw(pos_x, pos_y, width, height);
}

void Kimchi::init(){
    
    curKimchi = img[0];
    width = 130;
    height = 180;
    state = 0;
    isMoving = 0;
    pos_x = 474;
    pos_y = 2300;
    frameCnt=0;
    delay=0;
    volState=0;
    isLast=false;
}

