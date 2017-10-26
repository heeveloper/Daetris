//
//  Food.hpp
//  MealSupport
//
//  Created by Heeveloper on 2017. 9. 3..
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"

class Food {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void setup(float _x, float _y, string _image, int _index);	// setup method, use this to setup your object's initial state
    void update();  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    void toFront();
    void goAround();
    void slide();
    static int cnt;
    static bool isPopup;
    static int counting;
    int life;//randomly moving 0, to front 1, stop 2
    Food();  // constructor - used to initialize an object, if no properties are passed the program sets them to the default value
private: // place private functions or variables declarations here
    // variables
    int index;
    float x;        // position
    float y;
    float width;
    float height;
    float speedY;   // speed and direction
    float speedX;
    float speedY2;   // speed and direction
    float speedX2;
    // used in goAround()
    float radian;
    float begin_x;
    float mid_x;
    float mid_y;
    float grad_cos;
    float grad_sin;
    float ellipse_x;
    float ellipse_y;
    float ellipse_A;
    float ellipse_B;
    float track_x;
    float track_y;
    ofImage image;  // color using ofColor type
    const static int TOFRONTINTERVAL = 85;
    float timer;
}; // don't forget the semicolon!


class Plate{
public:
    void setup(string _image);
    void update();  // update method, used to refresh your objects properties
    void draw();
    void slide();
    string color;
    int moving;       //init 0, moving 1, invisible 2
    
private:
    float x;        // position
    float y;
    float width;
    float height;
    ofImage image;
};

class SidePlate{
public:
    void setup(string _image, int index);
    void update();  // update method, used to refresh your objects properties
    void draw();
    void slide(string _image);
    void initial();
    static int cnt;
    ofImage image;
    
private:
    int life;        //nothing 0, move 1, stop 2;
    float x;        // position
    float y;
    float width;
    float height;

};

class Score{
public:
    void setup();
    void update();
    void draw(int food_counting);
    ofImage number[4][10];
    
private:
    int state;
};
