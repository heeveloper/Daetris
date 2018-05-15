#include "ofApp.h"

void ofApp::osc208() {
    bang = 0;
    while (receiver.hasWaitingMessages()) {
        
        ofxOscMessage m;
        receiver.getNextMessage(&m);
        
        for (int i = 0; i < m.getNumArgs(); i++) {
            if (m.getArgType(i) == OFXOSC_TYPE_FLOAT) {
                bang = m.getArgAsFloat(0);
            }
        }
    }
    
    if (mbangsw == 1) {
        bang = 1;
    }
    
    if (abb == 1) {
        abbco += 1;
        if (abbco > 300) {
            abb = 0; abbco = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    // tag receiver setting and initialize the signal.
    receiver.setup(PORT);
    abb = 0;
    bang = 0;
    // hide cursor.
    ofHideCursor();
    
    flag = FLAG_NORM;
    opacity = 255;
    
    // setup camera
    cam = ofEasyCam();
    cam_x = SCREEN_X;
    cam_y = SCREEN_Y;
    cam_z = SCREEN_Z;
    
    // setup score image
    for (int i = 0; i <= 9; i++) {
        number[i].load("img/" + to_string(i) + ".png");
        number[i].resize(275, 370);
    }
    
    // setup background
    background_text_img.load("img/background_text_img.png");
    background_poster_img.load("img/background_poster_img.png");
    
    // setup videos
    background_video.load("video/background_video.mp4");
    background_video.setLoopState(OF_LOOP_NORMAL);
    background_video.play();
    
    // setup bgm
    bgm.load("music/bgm.mp3");
    bgm.setLoop(OF_LOOP_NORMAL);
    bgm.play();
    
    // open log file and counting.
    ifstream is;
    is.open(ofToDataPath("tag_counter.txt").c_str());
    string str;
    getline(is, str);
    tag_counter = atoi(str.c_str());
    std::cout << tag_counter;
    is.close();
}

//--------------------------------------------------------------
void ofApp::update(){
    osc208();
    curr_time = time(NULL);
    curr_tm = localtime(&curr_time);
    
    // Tag occured
    if (bang != 0 && abb == 0) {
        abb = 1;
        flag = FLAG_DOWN;
        
        // Log the check-time in the ~/bin/data/log.txt
        time(&rawTime);
        logFile.open("log.txt", ofFile::Append);
        logFile << ctime(&rawTime);
        logFile.close();
        
        ofstream of;
        of.open(ofToDataPath("tag_counter.txt").c_str());
        of << tag_counter;
        of.close();
    }
    
    if(flag == FLAG_NORM){
    
    }
    else if(flag == FLAG_DOWN){
        num_h -= 8;
        num_w -= 3;
        opacity -= 6;
        if(num_w < 10 || num_h < 10){
            flag = FLAG_UP;
            tag_counter++;
        }
    }
    else{
        num_h += 8;
        num_w += 3;
        opacity += 6;
        if(num_h >= NUM_H - 10){
            num_h = NUM_H;
            num_w = NUM_W;
            flag = FLAG_NORM;
            opacity  = 255;
        }
    }
    
    //Decrease bgm volume from 20:00 to 08:00
    if (curr_tm->tm_hour >= 20 || curr_tm->tm_hour < 8)
        bgm.setVolume(0.3f);
    
    background_video.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    cam.setPosition(ofVec3f(2500, 620, 1600));  // Debug mode
    cam.setPosition(ofVec3f(cam_x, cam_y, cam_z));
    
    ofSetHexColor(0xffffff);
    ofRotateZ(-90);
    ofTranslate(-1080 + tx, 0 + ty, 0);
    
    ///// Bottom Screen /////////////////
    background_video.draw(0, 0, 1080, 1920);
    background_text_img.draw(0, 0, 1080, 1920);
    
    
    ///// Top Screen ////////////////////
    background_poster_img.draw(0, 1920, 1080, 1920);
    
    //ofEnableAlphaBlending();
    ofSetColor(255, 255, 255, opacity);
    number[tag_counter % 10].draw(648, 1920 + 1110, num_w, num_h);
    if (tag_counter >= 10) {
        number[(tag_counter / 10) % 10].draw(383, 1920 + 1110, num_w, num_h);
    }
    if (tag_counter >= 100) {
        number[(tag_counter / 100) % 10].draw(141, 1920 + 1110, num_w, num_h);
    }
    //ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == OF_KEY_UP) {
        tx += 40;
    }
    if (key == OF_KEY_DOWN) {
        tx -= (40);
    }
    if (key == OF_KEY_RIGHT) {
        ty += 40;
    }
    if (key == OF_KEY_LEFT) {
        ty -= 40;
    }
    
    if (key == 119) {
        cam_y++;
    }
    else if (key == 97) {
        cam_x--;
    }
    else if (key == 115) {
        cam_y--;
    }
    else if (key == 100) {
        cam_x++;
    }
    else if (key == 113) {
        cam_z--;
    }
    else if (key == 101) {
        cam_z++;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mbangsw = 1;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    mbangsw = 0;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
