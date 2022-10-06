#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(30);

	ofBackground(0);
	ofSetLineWidth(3.5);

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->mesh.clear();

	auto radius = 15;
	for (int x = -300; x <= 300; x += 60) {

		for (int y = -300; y <= 300; y += 60) {

			int deg = ofMap(ofNoise(x * 0.0035, y * 0.0035, ofGetFrameNum() * 0.0005), 0, 1, 0, 720);
			int deg_param = deg % 90;
			deg = deg / 90 * 90;
			if (deg_param > 85) {

				deg += ofMap(deg_param, 85, 90, 0, 90);
			}

			int start_index = this->mesh.getNumVertices();
			for (int circle_deg = 0; circle_deg < 360; circle_deg += 2) {

				this->mesh.addVertex(glm::vec3(x + radius * cos(circle_deg * DEG_TO_RAD), y + radius * sin(circle_deg * DEG_TO_RAD), 0));
				if (circle_deg > 0) {

					this->mesh.addIndex(this->mesh.getNumVertices() - 1);
					this->mesh.addIndex(this->mesh.getNumVertices() - 2);
				}
			}

			this->mesh.addIndex(this->mesh.getNumVertices() - 1);
			this->mesh.addIndex(start_index);

			this->mesh.addVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), y + radius * sin(deg * DEG_TO_RAD), 0));
			this->mesh.addVertex(glm::vec3(x + radius * 2 * cos(deg * DEG_TO_RAD), y + radius * 2 * sin(deg * DEG_TO_RAD), 0));

			this->mesh.addIndex(this->mesh.getNumVertices() - 1);
			this->mesh.addIndex(this->mesh.getNumVertices() - 2);

			this->mesh.addVertex(glm::vec3(x + radius * cos((deg + 180) * DEG_TO_RAD), y + radius * sin((deg + 180) * DEG_TO_RAD), 0));
			this->mesh.addVertex(glm::vec3(x + radius * 2 * cos((deg + 180) * DEG_TO_RAD), y + radius * 2 * sin((deg + 180) * DEG_TO_RAD), 0));

			this->mesh.addIndex(this->mesh.getNumVertices() - 1);
			this->mesh.addIndex(this->mesh.getNumVertices() - 2);
		}
	}

	ofColor color;
	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		color.setHsb(ofMap(ofNoise(this->mesh.getVertex(i) * 0.0035), 0, 1, 180, 255), 200, 255);
		this->mesh.addColor(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	this->mesh.drawWireframe();
	
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}