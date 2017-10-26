#pragma once

#include "score.hpp"
#include "volunteer.hpp"
#include "kimchi.hpp"
#include "truck.hpp"
#include "box.hpp"
#include "ofMain.h"
#include "ofxOsc.h"



#define PORT 5001

class ofApp : public ofBaseApp{

public:
    int count;  // the number of donations
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
    void osc208();

    ofFile myTextFile;  // log file

    ofxOscReceiver receiver;
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

    bool isChecked = false;
    
    ofEasyCam cam;

    ofImage background_up;
    ofImage background_down;
    ofImage logo;
    ofImage table;
    ofSoundPlayer drive, back, success;

    Score score;
    Volunteer volunteer[5]={Volunteer(0),Volunteer(1),Volunteer(2),Volunteer(3),Volunteer(4)};
    Truck truck;
    Kimchi kimchi;
    Box box[5];
};
