#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


void readFile(string fn, vector<string> &content, int &x, int &y) {
	ifstream fin;
	fin.open(fn.c_str());

	if (fin.fail()) {
		cout << "Failed when open file <";
		cout << fn;
		cout << ">." << endl;
		exit(1);
	}

	string line;
	while (fin >> line) {
		content.push_back(line);
	}

	fin.close();

	x = content[0].length();
	y = content.size();
}


bool writeFile(string fn, vector<string> content) {
	ofstream fout;
	fout.open(fn.c_str());

	if (fout.fail()) {
		cout << "Failed when open file <";
		cout << fn;
		cout << ">." << endl;
		return false;
		// exit(1);
	}

	int lineCount = content.size();
	string line;
	int l;
	for (int i = 0; i < lineCount; i++) {
		line = content[i];
		l = line.length();
		if (line.substr(l-1, 1) == "\n") {
			fout << line;
		}
		else {
			fout << line << endl;
		}
	}
	// return true;

	fout.close();

	return true;
}


void extract(vector<string> n, vector<string> &p, int tlx, int tly, int brx, int bry) {
	int xSize = n[0].length();
	int ySize = n.size();

	if (p.size() != 0) {
		cout << "Vector should be empty." << endl;
		exit(1);
	}

	if (tlx < 0) {
		tlx = 0;
	}
	if (tly < 0) {
		tly = 0;
	}

	if (tlx >= xSize) {
		cout << "Invalid place to start from." << endl;
		exit(1);
	}
	else if (brx > xSize) {
		brx = xSize;
	}

	if (tly >= ySize) {
		cout << "Invalid place to start from." << endl;
		exit(1);
	}
	else if (bry > ySize) {
		bry = ySize;
	}

	if (brx <= tlx) {
		cout << "End should be larger than start." << endl;
		exit(1);
	}
	if (bry <= tly) {
		cout << "End should be larger than start." << endl;
		exit(1);
	}

	string part;
	for (int i = tly; i < bry; i++) {
		part = n[i].substr(tlx, brx-tlx);
		p.push_back(part);
	}
}


void paste(vector<string> &ori, vector<string> cover, int x, int y) {
	int p1x = 0, p1y = 0;
	int p2x = x, p2y = y;
	int p3x, p3y;
	int edx, edy; // end;
	int xSize, ySize, nxSize, nySize;

	xSize = ori[0].length();
	ySize = ori.size();

	nxSize = cover[0].length();
	nySize = cover.size();

	edx = xSize;
	edy = ySize;

	if (x < 0) {
		// p1x = 0;
		p2x = 0;
	}
	else {
		// p1x = 0;
		p2x = x;
	}

	if (y < 0) {
		// p1y = 0;
		p2y = 0;
	}
	else {
		// p1y = 0;
		p2y = y;
	}

	if (x+nxSize > xSize) {
		p3x = xSize;
	}
	else {
		p3x = x+nxSize;
	}
	if (y+nySize > ySize) {
		p3y = ySize;
	}
	else {
		p3y = y+nySize;
	}

	/*
	string line1;
	for (int i = p1y; i < p2y; i++) {
		line1 = ori[i];
		ori[i] = line1;
	}
	*/

	string line2;
	for (int i = p2y; i < p3y; i++) {
		line2 = ori[i].substr(p2x, p3x-p2x);
		line2 = line2 + cover[i-p2y];
		line2 = line2 + ori[i].substr(p3x, edx-p3x);
		ori[i] = line2;
	}

	/*
	string line3;
	for (int i = p3y; i < edy; i++) {
		line3 = ori[i];
		ori[i] = line3;
	}
	*/
}


int main() {
	string scene, file;
	string oriFileName, newFileName;
	int oriXSize, oriYSize;
	int newXSize, newYSize;
	int tlx, tly, brx, bry;
	int xPos, yPos;
	vector<string> oriContent;
	vector<string> newContent;
	vector<string> pstContent;

	// New
	cout << "Input information for the scene to copy from" << endl;
	cout << "Scene name: ";
	cin >> scene;
	cout << "File name: ";
	cin >> file;

	newFileName = "GameScene/"+scene+"/"+file+".txt";
	readFile(newFileName, newContent, newXSize, newYSize);

	cout << "Size on x of this scene is [0-" << newXSize-1 << "]." << endl;
	cout << "Size on y of this scene is [0-" << newYSize-1 << "]." << endl;
	cout << "Input cordinate of the top left corner of things to copy: ";
	cin >> tlx >> tly;
	cout << "Input cordinate of the bottom right corner of things to copy (exclusive): ";
	cin >> brx >> bry;

	extract(newContent, pstContent, tlx, tly, brx, bry);

	// Ori
	cout << "Input information for the scene to be pasted" << endl;
	cout << "Scene name: ";
	cin >> scene;
	cout << "File name: ";
	cin >> file;

	oriFileName = "GameScene/"+scene+"/"+file+".txt";
	readFile(oriFileName, oriContent, oriXSize, oriYSize);
	
	cout << "Size on x of this scene is [0-" << oriXSize-1 << "]." << endl;
	cout << "Size on y of this scene is [0-" << oriYSize-1 << "]." << endl;
	cout << "Input cordinate of top left corner to paste: ";
	cin >> xPos >> yPos;

	paste(oriContent, pstContent, xPos, yPos);

	bool sc;
	sc = writeFile(oriFileName, oriContent);
	if (sc) {
	cout << "Pasted successfully." << endl;
	}

	return 0;
}

