#include "ofApp.h"

#include <string>

// 全ての顔に整数連番のidを付与
enum Character {
  KO0 = 1,
  N0,
  NI0,
  TI0,
  WA0,
  LAST,
};

// 各idに紐づくファイル名を設定
map<Character, string> fileNames = {
    {KO0, "ko_1"}, {N0, "N_1"}, {NI0, "ni_1"}, {TI0, "ti_1"}, {WA0, "wa_1"}};

// 読み上げる文章を設定
Character input[] = {KO0, N0, NI0, TI0, WA0};
const int INPUT_SIZE = sizeof(input) / sizeof(input[0]);

ofImage images[LAST];
ofSoundPlayer players[LAST];
int current = 0;

const float FADE_POINT = 0.1;

float crossFade(float volume) {
  if (volume < FADE_POINT) {
    return 2 * volume;
  } else if (volume > 1 - FADE_POINT) {
    return -2 * volume + 2;
  }
  return 1;
}

//--------------------------------------------------------------
// 起動時に一度呼ばれる
void ofApp::setup() {
  for (int i = 0; i < LAST; i++) {
    string fileName = fileNames[Character(i + 1)];

    // 画像ファイルをロード
    string imageDirName = "images/";
    images[i].load(imageDirName + fileName + ".png");

    // 音声ファイルをロード
    string soundDirName = "sounds/";
    players[i].load(soundDirName + fileName + ".wav");
    players[i].setMultiPlay(false);
  }

  players[input[current] - 1].play();
}

//--------------------------------------------------------------
// 起動中繰り返し呼ばれる
void ofApp::update() {
  int next = current + 1;
  if (next >= INPUT_SIZE) {
    next = 0;
  }
  if (!players[input[next] - 1].isPlaying() &&
      players[input[current] - 1].getPosition() >= 1 - FADE_POINT) {
    current++;
    // 最後の文字までいったら最初に戻る
    if (current >= INPUT_SIZE) {
      current = 0;
    }
    players[input[current] - 1].play();
  }
  players[input[current] - 1].setVolume(
      crossFade(players[input[current] - 1].getPosition()));
  players[input[next] - 1].setVolume(
      crossFade(players[input[next] - 1].getPosition()));
}

//--------------------------------------------------------------
void ofApp::draw() {
  int next = current + 1;
  if (next >= INPUT_SIZE) {
    next = 0;
  }
  ofSetColor(255, 255);
  images[input[next] - 1].draw(0, 0, ofGetWidth(), ofGetHeight());
  ofSetColor(255, 255 * (1.5 - players[input[current] - 1].getPosition()));
  images[input[current] - 1].draw(0, 0, ofGetWidth(), ofGetHeight());
}

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
