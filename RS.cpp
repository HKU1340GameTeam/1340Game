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


void replace(vector<string> &content, int tlx, int tly, int brx, int bry, char OC, char NC) {
	int x, y;
	x = content[0].length();
	y = content.size();

	for (int line = 0; line < y; line++) {
		if (line >= tly && line < bry) {
			string thisLine = content[line].substr(0, tlx-1);
			string newLineCon;
			for (int p = tlx; p < brx; p++) {
				string K = ""+OC;
				if (thisLine.substr(p, 1) == K) {
					thisLine = thisLine + NC;
				}
				else {
					thisLine = thisLine + thisLine.substr(p, 1);
				}
			}
			thisLine = thisLine + content[line].substr(brx, x-brx);
			content[line] = thisLine;
		}
	}
}


int main() {
	string scene, file;
	string fileName;
	int XSize, YSize;
	vector<string> content;
	int tlx, tly, brx, bry;
	char oldChar, newChar;

	// New
	cout << "-- Input information of the scene --" << endl;
	cout << "Scene name: ";
	cin >> scene;
	cout << "File name: ";
	cin >> file;

	fileName = "GameScene/"+scene+"/"+file+".txt";
	readFile(fileName, content, XSize, YSize);

	cout << "Input x coordinate to start from: ";
	cin >> tlx;
	cout << "Input y coordinate to start from: ";
	cin >> tly;
	cout << "Input x coordinate to end with: ";
	cin >> brx;
	cout << "Input y coordinate to end with: ";
	cin >> bry;

	if (tlx >= XSize || tlx < 0) {
		tlx = 0;
	}
	if (tly >= YSize || tly < 0) {
		tly = 0;
	}
	if (brx <= tlx || brx > XSize) {
		brx = XSize;
	}
	if (bry <= tly || bry > YSize) {
		bry = YSize;
	}

	cout << "Input character to be substituted: ";
	cin >> oldChar;
	cout << "Input character to replace '" << oldChar << "': ";
	cin >> newChar;

	replace(content, tlx, tly, brx, bry, oldChar, newChar);

	bool a = writeFile(fileName, content);

	return 0;
}

