#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "Layer.h"
#include "Player.h"
#include "Scene.h"

using namespace std;


void Scene::setName(string sn) { sceneName = sn; }

void Scene::readTrigger() {
	trigger.clear();
	// wrong place
	// tp.clear();
	// tpX.clear();
	// tpY.clear();

	string filename = "Scenes/"+sceneName+"/trigger.txt";
	ifstream fin;
	fin.open(filename.c_str());

	if (fin.fail()) {
		//cout << "failed when opening file <" << fn << ">;" << endl;
		cerr << "failed when opening file <" << filename << ">." << endl;
		// throw "Failed open file."; // need
		exit(1);
	}

	string ln;
	while (getline(fin, ln)) {
		// need check size?
		if (sizeX != 0 && (int)ln.size() != sizeX) {
			cerr << filename << " length not consistent" << endl;
			//throw "X not consistent.";
			exit(1);
		}
		trigger.push_back(ln);
	}

	fin.close();

	if ((int)trigger.size() != sizeY) {cerr << "trigger.txt (y) size not consistent." << endl;}
}


void Scene::loadNewScene(Layer &l0, Layer &l1, Layer &l2, Layer &fgColor, Layer &l1Color, Layer &l2Color, Layer &phy)  {
	string folderName;

	if (sceneName == "") {
		cerr << "No scene name given!" << endl;
		exit(1);
	}
	folderName = "Scenes/"+sceneName+"/";

	// Need to reset layer to empty
	l0.ReadNewLayerFromFile(folderName+"emptyScene.txt");
	l1.ReadNewLayerFromFile(folderName+"scene1.txt");
	l2.ReadNewLayerFromFile(folderName+"scene2.txt");
	fgColor.ReadNewLayerFromFile(folderName+"emptyScene.txt");
	l1Color.ReadNewLayerFromFile(folderName+"fgColor_scene1.txt");
	l2Color.ReadNewLayerFromFile(folderName+"fgColor_scene2.txt");
	phy.ReadNewLayerFromFile(folderName+"phyScene.txt");

	sizeX = l0.LayerXSize;
	sizeY = l0.LayerYSize;

	readTrigger();

	ifstream fin;
	fin.open(folderName+"triggerMap.txt");
	if (fin.fail()) {
		cerr << "Cannot load scene <" << sceneName << ">; Reason: failed opening file.";
		// throw "Cannot open file.";
		exit(1);
	}

	/*
	string info;
	fin >> info;

	string layerNames[7];
	string fileName;
	for (int i = 0; i < 7; i++) {
		fin >> fileName;
		layerNames[i] = fileName;
	}
	fin >> layerFilename;
	fg.ReadLayerFromFile(layerNames[0].c_str());
	l1.ReadLayerFromFile(layerNames[1].c_str());
	l2.ReadLayerFromFile(layerNames[2].c_str());
	fgColor.ReadLayerFromFile(layerNames[3].c_str());
	l1Color.ReadLayerFromFile(layerNames[4].c_str());
	l2Color.ReadLayerFromFile(layerNames[5].c_str());
	phy.ReadLayerFromFile(layerNames[6].c_str());
	*/

	tp.clear();
	tpX.clear();
	tpY.clear();

	string ln;
	while (getline(fin, ln)) {
		istringstream iss(ln);
		char c;
		string n;
		int x, y;
		iss >> c >> n >> x >> y;
		tp[c] = n;
		// cout << tp[c] << endl;
		tpX[c] = x;
		tpY[c] = y;
		// cout << n << x << y << endl;
	}

	fin.close();
}


bool Scene::switchScene(Player &p) {
	// char loc = trigger[p.position.y][p.position.x];
	char loc = trigger[p.int_y_pos][p.int_x_pos];
	if (loc == ' ' || loc == '*') { return false; }
	else {
		if (tp.count(loc) > 0) {
			setName(tp[loc]);
			// Need?
			p.position.x = tpX[loc];
			p.position.y = tpY[loc];
			// Mistake: to change any property of a para, need &
			p.int_x_pos = tpX[loc];
			p.int_y_pos = tpY[loc];
			return true;
		}
	}
	return false;
}


void Scene::resetLayer(Layer &l0, Layer &l1, Layer &l2, Layer &fgc, Layer &l1c, Layer &l2c, Player p) {
	l0.ResetLayer();
	l1.ResetLayer();
	l2.ResetLayer();
	fgc.ResetLayer();
	l1c.ResetLayer();
	l2c.ResetLayer();

	l1.WriteObject(p.figure, p.int_x_pos, p.int_y_pos, 3, 3);
	l1c.WriteObject(p.figure_fg_color, p.int_x_pos, p.int_y_pos, 3, 3);

	fgc.AddLayerOnTop(l1c);
	fgc.AddLayerOnTop(l2c);
	l0.AddLayerOnTop(l1);
	l0.AddLayerOnTop(l2);

}



