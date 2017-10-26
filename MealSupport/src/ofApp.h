#pragma once

#include "ofMain.h"
#include "Food.hpp"
#include "ofxOsc.h"
#define PORT 5001




class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
 
    
    ofImage background;
    ofImage down;
    Plate front;
    ofEasyCam cam;

    static const int FOOD_COUNT = 5;
    Food food[FOOD_COUNT];
	static const int SIDE_COUNT = 30;
    SidePlate side[SIDE_COUNT];
    Score score;
    
    ofImage popup;
    ofTrueTypeFont message, countMsg;
    ofSoundPlayer eating, back, success;
    
    void osc208();
    
    ofxOscReceiver receiver;
    
    ofFile myTextFile;
    
    float bang;
    int mbangsw;
    int abb;
    int abbco;
    int t;
    
    int frame_r = 0;
    int completeCounter = -1;
    
    bool word_writing = false;
    int c_endIndex = -1;
    int c_index = 0;
    void writingWord();
    bool test=false;
    
    ofImage number[4][10];
    ofImage counting;
    
      
    
};
