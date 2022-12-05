#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


bool writeFile(string fn, vector<string> content, int y) {
	ofstream fout;
	fout.open(fn.c_str());

	if (fout.fail()) {
		cout << "Failed open file <" << fn << ">." << endl;
		return false;
		// exit(1);
	}

	cout << "Handling <" << fn << ">." << endl;

	int line = content.size(), len;
	for (int i = 0; i < line; i++) {
		int len = content[i].length();
		if (content[i].substr(len-1, 1) == "\n") {
			if (len != y+1) {
				cout << "Length not consistent." << endl;
				fout.close();
				return false;
				// exit(1);
			}
			else {
				fout << content[i];
			}
		}
		else {
			if (len != y) {
				cout << "Length not consistent." << endl;
				fout.close();
				return false;
				// exit(1);
			}
			else {
				fout << content[i] + "\n";
			}
		}
		// fout << content[i];
	}

	fout.close();
	return true;
}


int main() {
	int x, y;
	string sceneName;
	string pathName, fileName;
	string topLine, midLine;
	vector<string> file;
	vector<string> con;

	file.push_back("emptyScene.txt");
	file.push_back("scene1.txt");
	file.push_back("scene2.txt");
	file.push_back("fgColor_scene1.txt");
	file.push_back("fgColor_scene2.txt");
	file.push_back("phyScene.txt");
	file.push_back("trigger.txt");
	file.push_back("editorPhyScene.txt");
	file.push_back("sceneCombined.txt");

	cout << "Input x size: ";
	cin >> x;
	cout << "Input y size: ";
	cin >> y;

	cout << "Input scene name: ";
	cin >> sceneName;
	pathName = "GameScenes/"+sceneName+"/";

	// make line
	// topLine
	topLine = "*";
	midLine = "*";
	for (int i = 1; i < x-1; i++) {
		topLine = topLine + "*";
		midLine = midLine + " ";
	}
	topLine = topLine + "*\n";
	midLine = midLine + "*\n";
	// cout << midLine.length() << endl; //debug

	// assemble lines into files
	con.push_back(topLine);
	for (int i = 1; i < y-1; i++) {
		con.push_back(midLine);
	}
	con.push_back(topLine);

	// write file
	bool success = true;
	for (int i = 0; i < file.size(); i++) {
		fileName = pathName+file[i];
		success *= writeFile(fileName, con, x);
	}
	if (success) {
		cout << "All files successfully written." << endl;
	}

	return 0;
}

