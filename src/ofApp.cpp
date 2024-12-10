#include "ofApp.h"

#include <string>

enum Character {
  KO0 = 1,
  N0,
  NI0,
  TI0,
  WA0,
};

map<Character, string> fileNames = {{KO0, "ko-0-1"},
                                    {N0, "n-0-2"},
                                    {NI0, "ni-0-3"},
                                    {TI0, "ti-0-4"},
                                    {WA0, "wa-0-5"}};

Character input[] = {KO0, N0, NI0, TI0, WA0};
ofSoundPlayer players[sizeof(input) / sizeof(input[0])];

//--------------------------------------------------------------
void ofApp::setup() {
  for (int i = 0; i < sizeof(input) / sizeof(input[0]); i++) {
    string dirName = "sounds/";
    string fileName = fileNames[Character(i + 1)];
    players[i].load(dirName + fileName + ".mp3");
    players[i].setMultiPlay(false);
  }
}

//--------------------------------------------------------------
int i = 0;
void ofApp::update() {
  if (i == 0 || !players[i - 1].isPlaying()) {
    cout << i << fileNames[Character(i + 1)] << endl;
    players[input[i]].play();
    i++;
    if (i >= sizeof(input) / sizeof(input[0])) {
      i = 0;
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {}

//--------------------------------------------------------------
void ofApp::exit() {}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
