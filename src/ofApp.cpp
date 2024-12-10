#include "ofApp.h"

#include <string>

// 全ての顔に整数連番のidを付与
enum Character {
  KO0 = 1,
  N0,
  NI0,
  TI0,
  WA0,
};

// 各idに紐づくファイル名を設定
map<Character, string> fileNames = {
    {KO0, "ko_1"}, {N0, "N_1"}, {NI0, "ni_1"}, {TI0, "ti_1"}, {WA0, "wa_1"}};

// 読み上げる文章を設定
Character input[] = {KO0, N0, NI0, TI0, WA0};

ofSoundPlayer players[WA0];
//--------------------------------------------------------------
// 起動時に一度呼ばれる
// 音声ファイルをロード
void ofApp::setup() {
  for (int i = 0; i < WA0; i++) {
    string dirName = "sounds/";
    string fileName = fileNames[Character(i + 1)];
    players[i].load(dirName + fileName + ".wav");
    players[i].setMultiPlay(false);
  }
}

int i = 0;
//--------------------------------------------------------------
// 起動中繰り返し呼ばれる
void ofApp::update() {
  if (i == 0 || !players[input[i - 1] - 1].isPlaying()) {
    // 最後の文字までいったら最初に戻る
    if (i >= sizeof(input) / sizeof(input[0])) {
      i = 0;
    }
    players[input[i] - 1].play();
    i++;
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
