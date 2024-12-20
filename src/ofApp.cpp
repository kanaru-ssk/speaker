#include "ofApp.h"

#include <string>

// 全ての顔に整数連番のidを付与
enum Character {
  KO0,
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
const int INPUT_SIZE = sizeof(input) / sizeof(input[0]);

ofImage images[2];
ofSoundPlayer players[2];

const float FADE_POINT = 0.1;

float crossFade(float volume) {
  if (volume < FADE_POINT) {
    return 2 * volume;
  } else if (volume > 1 - FADE_POINT) {
    return -2 * volume + 2;
  }
  return 1;
}

int getNextPlayer(int playing) {
  // playing = 0 -> next = 1
  // playing = 1 -> next = 0
  return 1 - playing;
}

void loadFile(int index, ofImage *image, ofSoundPlayer *player) {
  // 画像ファイルをロード
  string imageDirName = "images/";
  image->load(imageDirName + fileNames[input[index]] + ".png");

  // 音声ファイルをロード
  string soundDirName = "sounds/";
  player->load(soundDirName + fileNames[input[index]] + ".wav");
}

int current = 0;
int playing = 0;

//--------------------------------------------------------------
// 起動時に一度呼ばれる
void ofApp::setup() {
  // 画像ファイルをロード
  string imageDirName = "images/";
  loadFile(current, &images[playing], &players[playing]);
  loadFile(current + 1, &images[getNextPlayer(playing)],
           &players[getNextPlayer(playing)]);
  players[playing].play();
}

//--------------------------------------------------------------
// 起動中繰り返し呼ばれる
void ofApp::update() {
  int next = current + 1;
  if (next >= INPUT_SIZE) {
    next = 0;
  }

  for (int i = 0; i < 2; i++) {
    if (players[i].getPosition() == 1) {
      loadFile(next, &images[i], &players[i]);
    }
  }

  if (!players[getNextPlayer(playing)].isPlaying() &&
      players[playing].getPosition() >= 1 - FADE_POINT) {
    current++;
    // 最後の文字までいったら最初に戻る
    if (current >= INPUT_SIZE) {
      current = 0;
    }
    playing = getNextPlayer(playing);

    players[playing].play();
  }
  players[playing].setVolume(crossFade(players[playing].getPosition()));
  players[getNextPlayer(playing)].setVolume(
      crossFade(players[getNextPlayer(playing)].getPosition()));
}

//--------------------------------------------------------------
void ofApp::draw() {
  int next = current + 1;
  if (next >= INPUT_SIZE) {
    next = 0;
  }
  ofSetColor(255, 255);
  images[getNextPlayer(playing)].draw(0, 0, ofGetWidth(), ofGetHeight());
  ofSetColor(255, 255 * (1.5 - players[playing].getPosition()));
  images[playing].draw(0, 0, ofGetWidth(), ofGetHeight());
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
