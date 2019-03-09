#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	ofSetColor(39);
	int len = 300;
	int log = 15;
	float noise_seed_x = ofRandom(1000);
	float noise_seed_y = ofRandom(1000);
	vector<glm::vec3> locations;
	for (int x = len * -0.5; x <= len * 0.5; x += len) {

		for (int y = len * -0.5; y <= len * 0.5; y += len) {

			for (int z = len * -0.5; z <= len * 0.5; z += len) {

				ofBeginShape();
				for (int i = 0; i < log; i++) {

					auto location = glm::vec3(x, y, z);
					auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + i) * 0.008), 0, 1, -PI, PI), glm::vec3(1, 0, 0));
					auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + i) * 0.008), 0, 1, -PI, PI), glm::vec3(0, 1, 0));
					location = glm::vec4(location, 0) * rotation_x * rotation_y;

					ofVertex(location);

					if (i == log - 1) { 
					
						ofFill();
						ofDrawSphere(location, 8); 
						locations.push_back(location);
						ofNoFill();
					}
				}
				ofEndShape();
			}
		}
	}

	ofSetColor(139);
	ofDrawLine(locations[0], locations[1]);
	ofDrawLine(locations[2], locations[3]);
	ofDrawLine(locations[4], locations[5]);
	ofDrawLine(locations[6], locations[7]);

	ofDrawLine(locations[0], locations[2]);
	ofDrawLine(locations[1], locations[3]);
	ofDrawLine(locations[4], locations[6]);
	ofDrawLine(locations[5], locations[7]);

	ofDrawLine(locations[0], locations[4]);
	ofDrawLine(locations[1], locations[5]);
	ofDrawLine(locations[2], locations[6]);
	ofDrawLine(locations[3], locations[7]);

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}