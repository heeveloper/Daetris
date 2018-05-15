#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofVideoPlayer.h"
#include <iostream>
#include <fstream>
#define PORT    5001
#define FLAG_DOWN  0
#define FLAG_UP    1
#define FLAG_NORM  2
#define SCREEN_X   1500
#define SCREEN_Y   500
#define SCREEN_Z   1000

const int VIDEO_W = 800;
const int VIDEO_H = 1000;
const int NUM_W = 246;
const int NUM_H = 357;

class ofApp : public ofBaseApp {
    
public:
    /* Tag signal
     */
    float bang;
    int mbangsw;
    int abb;
    int abbco;
    int completeCounter = -1;
    int tx = 0;
    int ty = 0;
    int num_w = 246, num_h = 357;
    int flag;
    int opacity;
    int cam_x, cam_y, cam_z;
    
    // Camera for debugging.
    ofEasyCam cam;
    
    // Tag count
    int tag_counter;
    
    // Log file.
    ofFile logFile;
    
    // background video.
    ofVideoPlayer background_video;
    
    // background music.
    ofSoundPlayer bgm;
    
    // background image
    ofImage background_poster_img;
    ofImage background_text_img;
    
    ofxOscReceiver receiver;
    
    time_t rawTime;
    time_t curr_time;
    struct tm *curr_tm;
    
    ofImage number[10];
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void osc208();
    
};
