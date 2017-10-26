//
//  volunteer.cpp
//  Kimchi
//
//  Created by  Heejun Lee on 9/13/17.
//
//

#include "volunteer.hpp"

Volunteer::Volunteer(int i){
    switch(i){
        case 0:
            pos_x=135;
            pos_y=3840-1191-480;
            width=400;
            height=600;
            idx=0;
            break;
        case 1:
            pos_x=542;
            pos_y=3840-1033-480;
            width=380;
            height=570;
            idx=1;
            break;
        case 2:
            pos_x=207;
            pos_y=3840-890-480;
            width=360;
            height=540;
            idx=2;
            break;
        case 3:
            pos_x=519;
            pos_y=3840-745-380;
            width=340;
            height=510;
            idx=3;
            break;
        case 4:
            pos_x=244;
            pos_y=3840-745-380;;
            width=340;
            height=510;
            idx=4;
            break;
    }
}
void Volunteer::setup(){
    img.load("images/vol_1.png");
    img2.load("images/vol_2.png");
    img3.load("images/vol_3.png");
    switch(getIdx()){
        case 0:
            img.mirror(false, true);
            img2.mirror(false, true);
            img3.mirror(false, true);
            break;
        case 2:
            img.mirror(false, true);
            img2.mirror(false, true);
            img3.mirror(false, true);
            break;
        case 4:
            img.mirror(false, true);
            img2.mirror(false, true);
            img3.mirror(false, true);
            break;
    }
    delay=0;
    vol=img3;
}

void Volunteer::update(){
    delay++;
    if(delay==20){
        vol=img;
    } /*else if(delay==60){
        vol=img2;
    }*/
    else if(delay==120){
        vol=img3;
        delay=0;
    }
}

void Volunteer::draw(){
    vol.draw(pos_x, pos_y, width, height);
}
