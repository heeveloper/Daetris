#include "ofApp.h"
#include <ctime> //for logging

int x = -1500, y = 500, z=1000;
time_t rawtime;
bool Box::isStart = false;
bool Score::checked = false;

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
        if (abbco > 200) {
            abb = 0; abbco = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::setup(){
    cam = ofEasyCam();
    // Here you set up a object of classes (such as load(), setup(),..
    
    std::cout << "\n ";
    std::cout << " > 위에 화면 보기 (1)\n";
    std::cout << " > 아래 화면 보기 (2)\n";
    std::cout << " > 입력 : ";
    std::cin  >> t;
    
    receiver.setup(PORT);
    bang = 0;
    ofHideCursor();
    
    background_up.load("images/background_up.png");
    background_down.load("images/background_down.jpg");
    logo.load("images/logo.png");
    table.load("images/table.png");
    
    back.load("sounds/back.mp3");
    drive.load("sounds/drive.mp3");
    success.load("sounds/success.mp3");
    
    back.setLoop(true);
    back.play();
    back.setVolume(0.7f);
    count=0;
    score.setup();
    truck.setup();
    kimchi.setup();
    for(int i=0;i<5;i++){
        volunteer[i].setup();
    }
    for(int i=0;i<5;i++){
        box[i].setup(i, 435, 2880, 158, 110);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    osc208();
    if (bang != 0 && abb == 0 &&completeCounter==-1) {
        success.play();
        abb = 1;
        if (word_writing)return;
        if (c_index <= c_endIndex)return;
        test = true;
        
        count++;
        cout << "click!" << endl;
        
        // Log the check-time in the ~/bin/data/log.txt
        time(&rawtime);
        myTextFile.open("log.txt", ofFile::Append);
        myTextFile << ctime(&rawtime);
        myTextFile.close();
        Score::checked = true;
        score.score_state = 1;
        kimchi.isMoving ++;
    }
    score.update();
    truck.update();
    kimchi.update();
    if(kimchi.isMoving==2){
        if(kimchi.volState==3){
            volunteer[kimchi.volState].update();
            volunteer[kimchi.volState+1].update();
        } else{
            volunteer[kimchi.volState].update();
        }
        
    }
    if(kimchi.isLast){
        box[Box::box_cnt].setState(1);   // Go on the truck
        kimchi.init();
    }
    for(int i=0;i<5;i++){
        box[i].update();
        if(truck.truck_state==2&&truck.isArrived==true){
            Box::box_cnt=0;
            box[Box::box_cnt].isStart=false;
            box[i].init();
        }
    }
    if(Box::box_cnt == 5){
        truck.truck_state = 1;
        box[Box::box_cnt-1].isStart = true;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    cam.setPosition(ofVec3f(x, y, z));  // x, y, z (240,1920,4000)
    ofRotateZ(90);
    background_up.draw(0, 1920);
    background_down.draw(0,0,1080, 1920);
    table.draw(350,3840-1769);
    logo.draw(0,1920+25,1080,151);
    truck.draw();
    score.draw();
    for(int i=0;i<5;i++)
        box[i].draw();
    if(kimchi.isMoving == 0){
        for(int i=4;i>=0;i--)
            volunteer[i].draw();
        kimchi.draw();
    }
    else{
        kimchi.draw();
        for(int i=4;i>=0;i--)
            volunteer[i].draw();
    }
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 119 || key == 119 - 'a') {
        cout << 1 << endl;
        y++;
    }
    else if (key == 97 || key == 97 - 'a') {
        cout <<2 << endl;
        
        x--;
    }
    else if (key == 115 || key == 115 - 'a') {
        cout << 3 << endl;
        
        y--;
    }
    else if (key == 100 || key == 100 - 'a') {
        cout << 4 << endl;
        
        x++;
    }
    else if (key == 113 || key == 113 - 'a') {
        cout << 5 << endl;
        
        z--;
    }
    else if (key == 101 || key == 101 - 'a') {
        cout << 6 << endl;
        
        z++;
    }}

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
void ofApp::mouseReleased(int x, int y, int button){
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
