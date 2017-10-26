//
//  Food.cpp
//  MealSupport
//
//  Created by Heeveloper on 2017. 9. 3..
//
//

#include "Food.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

int Food::cnt = 0;
int SidePlate::cnt = 0;
int Food::counting = 0;
bool Food::isPopup = false;
Food::Food(){
};
static const float INTERVAL = 10;
static float points[5][2] = {{140, 500},{470, 500},{136, 747},{310, 747},{575, 770}};//이걸로 식판에 놓이는 위치
static float sizes[5][2] = {{300,250},{290,250},{200, 200},{260, 180},{300, 200}};
static const string colorStr[] = { "blue", "gray", "green", "red", "yellow" };
void Food::setup(float _x, float _y, string _image, int _index){
    x = _x;
    y = _y;
    index = _index;
    speedX = ofRandom(-2, 2)*2;
    speedY = ofRandom(-2, 2)*2;
    image.load("images/"+_image+".png");
    width = sizes[index][0];
    height = sizes[index][1];
    life = 0;
    timer = 0;
}
void Food::update(){
    if(life == 0){
        if(x < 0 ){
            x = 0;
            speedX *= -1;
        } else if(x + width > 1080){
            x = 1080 - width;
            speedX *= -1;
        }
    
        if(y < 1000 ){
            y = 1000;
            speedY *= -1;
        } else if(y + height> 1900){
            y = 1900 - height;
            speedY *= -1;
        }
    
        x+=speedX;
        y+=speedY;
    }else if(life == 1){
        //  Move in elliptical form
        if(radian <= 2.5 * PI && radian >= -1.5){
            ellipse_x = ellipse_A*cos(radian);
            ellipse_y =ellipse_B*sin(radian);
            track_x = ellipse_x*grad_cos - ellipse_y*grad_sin;
            track_y = ellipse_x*grad_sin + ellipse_y*grad_cos;
            x = mid_x + track_x;
            y = mid_y + track_y;
            if(begin_x<460)
                radian -= 0.03;
            else
                radian += 0.03;
            
            //  When the radian is a turning point (0 or 2*PI)
            if((radian<2*PI && radian+0.03 > 2*PI) || (radian>0 && radian-0.03<0))
                counting++;
            
            speedX2 = (points[index][0]-x)/TOFRONTINTERVAL;
            speedY2 = (points[index][1]-y)/TOFRONTINTERVAL;
        }
        //  Move to the plate
        else{
            x+=speedX2;
            y+=speedY2;
        
            if(points[index][1] >= y){
                y = points[index][1];
                life = 2;
                isPopup = false;
                //counting++;
                if(cnt == 5 && index == 4){
                    cnt++;
                }
            }
        }
    }else if(life == 3){
        x -= INTERVAL;
        if(x<=-1000+(points[index][0]-100)){
            x = -1000+(points[index][0]-100);
            life = 4;
            if(cnt == 7 && index == 4){
                cnt++;
            }
        }
    }
}

void Food::draw(){
    image.draw(x,y,width,height);
}

void Food::slide(){
    life = 3;
}

void Food::toFront(){
    cnt++;
    
    //  Set the values for elliptical moving
    begin_x = x;
    mid_x = (460+x)/2;
    mid_y = (2750+y)/2;
    ellipse_A = sqrt(pow(460-x, 2) + pow(2750-y,2))/2;
    ellipse_B = ellipse_A/2;
    grad_cos = (460-x)/(ellipse_A*2);
    grad_sin = (2750-y)/(ellipse_A*2);
    radian=PI;
    
    life++;
}

//---------------------------------------------

void Plate::setup(string _image){
    x = 100;
    y = 450;
    width = 700;
    height = 500;
    image.load("images/plate_"+_image+".png");
    moving = 0;
    color = _image;
}

void Plate::update(){
    if(moving == 0){
        
    }
    else if(moving == 1){
        x -= INTERVAL;
        if(x<=-1000){
            moving = 2;
            x = -1000;
        }
    }else if(moving == 3){
        x = 100;
        color =colorStr[rand()%5];
        image.load("images/plate_"+color+".png");
        moving = 0;
    }
}

void Plate::draw(){
    image.draw(x,y, width, height);
}

void Plate::slide(){
    moving = 1;
}

//--------------------------------------------

void SidePlate::setup(string _image, int index){
    x=1300;
    y=30+(index*45);
    width = 200;
    height = 40;
    image.load("images/side_"+_image+".png");
    life = 0;
}

void SidePlate::update(){
    if(life == 1){
        x -= INTERVAL;
        if(x<=850){
            x = 850;
            life = 2;
            Food::cnt = 10;
        }
    }
    else if(life == 3){
        x += INTERVAL;
        if(x>=1300){
            x = 1300;
            life = 0;
        }
    }
}

void SidePlate::draw(){
    image.draw(x, y, width, height);
}

void SidePlate::initial(){
    x=1300;
    life = 0;
}

void SidePlate::slide(string _image){
    life = 1;
    
    if(!image.isAllocated()){
        image.allocate(200, 80, OF_IMAGE_COLOR);
    }
    image.load("images/side_"+_image+".png");
}

//--------------------------------------------

void Score::setup(){
    static const string numberStr[] = { "0", "1", "2", "3", "4","5","6","7","8","9"};
    for(int i = 0 ; i < 4; i++){
        for(int j = 0; j < 10; j++){
            number[i][j].load("images/num_"+numberStr[j]+".png");
        }
    }
}

void Score::update(){
    for(int i=0; i<4 ; i++){
        for(int j=0; j<10; j++){
            number[i][j].update();
        }
    }
}

void Score::draw(int food_counting){
    int tmp, strg;
    strg = food_counting;
    int digit = 0;
    do {
        strg /= 10;
        digit++;
    } while (strg>0);
    strg = food_counting;
    
    
    for(int i=0; i<digit; i++){
        tmp=strg/(pow(10,digit-1-i));
        number[i][tmp].draw(540-63-63*(digit-1)+i*126,2750,126,165);
        strg-=tmp*pow(10,digit-1-i);
    }
}

