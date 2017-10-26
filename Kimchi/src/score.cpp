//
//  score.cpp
//  Kimchi
//
//  Created by  Heejun Lee on 9/14/17.
//
//

#include "score.hpp"
#include <cstdlib>

void Score::setup(){
    static const string numberStr[] = { "0", "1", "2", "3", "4","5","6","7","8","9"};
    for(int i = 0 ; i < 4; i++){
        for(int j = 0; j < 10; j++){
            number[i][j].load("images/num_" + numberStr[j] + ".png");
        }
    }
    pos_y = fixed_y;
    score_count = 0;
    score_state = 0;
    dir = 1;
    checked = false;
}

void Score::update(){
    if(checked){
        // Update the count
        if(score_state == 1){
            pos_y+=3;
            if(pos_y > 1920*2 + 10){
                score_count++;
                score_state = 2;
            }
        }
        else{
            pos_y-=3;
            if(pos_y <= fixed_y){
                pos_y = fixed_y;
                score_state = 0;
                checked = false;
            }
        }
    }
    else{
        // Floating in the air
        if(pos_y == fixed_y + floating_y)
            dir = -2;
        else if(pos_y == fixed_y - floating_y)
            dir = 2;
        
        if(dir % 2 == 0){
            dir = dir / 2;
            pos_y += dir;
        }
        else if(dir < 0 ){
            dir--;
        }
        else{
            dir++;
        }
    }
}

void Score::draw(){
    int num, digit=0, tmp = score_count;
    do{
        tmp /= 10;
        digit++;
    }while(tmp>0);
    tmp = score_count;
    
    // 100
    if(digit==3){
        for(int i=0;i<digit;i++){
            num = tmp/pow(10, digit-i-1);
            tmp -= num*pow(10, digit-i-1);
            number[i][num].draw(400+i*130, pos_y, SCORE_WIDTH, SCORE_HEIGHT);
        }
    }
    // 10
    else if(digit==2){
        for(int i=0;i<digit;i++){
            num = tmp/pow(10, digit-i-1);
            tmp -= num*pow(10, digit-i-1);
            number[i][num].draw(450+i*130, pos_y, SCORE_WIDTH, SCORE_HEIGHT);
        }
    }
    // 1
    else{
        num = tmp;
        number[0][num].draw(520, pos_y, SCORE_WIDTH, SCORE_HEIGHT);
    }
}
