#include "ofApp.h"
#include <ctime>
int x = -1500, y = 500, z=1000;
time_t rawtime;

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
//---------------------------------------------------------------------------------------------------------
int getIndex(string color) {
	if (color.compare("blue") == 0) return 0;
	else if (color.compare("gray") == 0)return 1;
	else if (color.compare("green") == 0)return 2;
	else if (color.compare("red") == 0)return 3;
	else if (color.compare("yellow") == 0)return 4;
}

//--------------------------------------------------------------
void ofApp::setup(){
    background.load("images/background.jpg");
    down.load("images/down.jpg");
    srand((unsigned int)time(NULL));
    static const char * colorStr[] = { "blue", "gray", "green", "red", "yellow" };
    front.setup(colorStr[rand()%5]);
    cam = ofEasyCam();
    static const char * foodStr[] = { "rice", "soup", "apple", "egg", "chicken" };
        for(int i = 0; i < FOOD_COUNT; i++){
        food[i].setup(250, 2500, foodStr[i], i);
    }
    for(int i = 0; i < SIDE_COUNT; i++){
        side[i].setup(front.color, i);
    }
    
    score.setup();
    // The below code is lefted for the number used in the popup message
    static const string numberStr[] = { "0", "1", "2", "3", "4","5","6","7","8","9"};
    for(int i = 0 ; i < 4; i++){
        for(int j = 0; j < 10; j++){
            number[i][j].load("images/num_"+numberStr[j]+".png");
        }
    }
    
    counting.load("images/counting.png");
    popup.load("images/alarm.png");
    message.load("fonts/NanumSquareR.ttf", 35);
    countMsg.load("fonts/NanumSquareB.ttf", 110);
    back.load("sounds/ground.mp3");
    success.load("sounds/success.mp3");
    eating.load("sounds/eating.mp3");
    back.setLoop(true);
    back.play();
    
	std::cout << "\n ";
	std::cout << " > 위에 화면 보기 (1)\n";
	std::cout << " > 아래 화면 보기 (2)\n";
	std::cout << " > 입력 : ";
	std::cin  >> t;
	std::cout << " > Frame  rate (max for 0)\n";
	std::cout << " > 입력 :";
	std::cin  >> frame_r;
    
    receiver.setup(PORT);
    bang = 0;
    ofHideCursor();
}

//--------------------------------------------------------------
void ofApp::update(){
    osc208();
    if (bang != 0 && abb == 0 &&completeCounter==-1) {
        abb = 1;
        if (word_writing)return;
        if (c_index <= c_endIndex)return;
        test = true;
		
        // Log the check-time in the ~/bin/data/log.txt
        time(&rawtime);
        myTextFile.open("log.txt", ofFile::Append);
        myTextFile << ctime(&rawtime);
        myTextFile.close();
        
		food[Food::cnt].toFront();
		Food::isPopup = true;
		success.play();
    }
    
    counting.update();
    front.update();
    for(int i = 0; i < FOOD_COUNT; i++){
        food[i].update();
    }
    
    for(int i = 0; i < SIDE_COUNT; i++){
        side[i].update();
    }
    
    score.update();
    
    if(Food::cnt == 6){
        front.slide();
        for(int i = 0; i < 5; i++){
            food[i].slide();
        }
        Food::cnt = 7;
        eating.play();
    }else if(Food::cnt == 8){
        side[SidePlate::cnt++].slide(front.color);
        Food::cnt = 9;
    }else if(Food::cnt == 10){
        if(SidePlate::cnt == SIDE_COUNT){
            for(int i = 0; i<SIDE_COUNT; i++){
                side[i].initial();
            }
			SidePlate::cnt = 0;
        }
        front.moving = 3;
        for(int i = 0; i < FOOD_COUNT; i++){
            food[i].life = 0;
        }
        Food::cnt = 0;
    }
 
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    cam.setPosition(ofVec3f(240, 1920, 4000));  // x, y, z (240,1920,4000)
    //ofRotateZ(90);
    background.draw(0,0,1080,1920);
    down.draw(0,1920);
    front.draw();
    
    for(int i = 0; i < FOOD_COUNT; i++){
        food[i].draw();
    }
    for(int i = 0; i < SIDE_COUNT; i++){
        side[i].draw();
    }

    score.draw(Food::counting);
    
    if(Food::isPopup){
        popup.draw(240,1600,600, 300);
        counting.draw(460, 1740, 300, 30);
        
        int tmp, strg;
        int digit=(Food::counting/5+1)/10+1;
        strg=Food::counting/5+1;
        
        for(int i=0; i<digit; i++){
            tmp=strg/(pow(10,digit-1-i));
            number[i][tmp].draw(400+i*30,1740,30,30);
            strg-=tmp*pow(10,digit-1-i);
        }
    }
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 119) {
		y++;
	}
	else if (key == 97) {
		x--;
	}
	else if (key == 115) {
		y--;
	}
	else if (key == 100) {
		x++;
	}
	else if (key == 113) {
		z--;
	}
	else if (key == 101) {
		z++;
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


