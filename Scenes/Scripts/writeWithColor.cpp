// Fri Nov  4 12:08:50 CST 2022
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

vector<string> ReadSceneFromFile(string FileName,vector<string> layer);
void WriteSceneToFile(string FileName,vector<string> layer);
vector<string> WriteObject(vector<string> pic, vector<string> layer, int pos_x, int pos_y);
vector<string> WriteColor(vector<string> pic,char colorCode);
vector<string> ReadFigureFromFile(string FileName,vector<string> layer);

int main(int argc, char* argv[]){
	//  second arg: txtfile of scene; third arg: txtfile storing figure, no \n at end; forth arg: x position; fifth arg:
	// y position; sixth arg: color file; seventh arg: color code
	if(argc != 7){
		cout << "argument number not right" << endl;
		exit(1);
	}

	vector<string> layer;
	vector<string> figure;
	vector<string> colorFigure;
	vector<string> colorLayer;

	int x = atoi(argv[3]);
	int y = atoi(argv[4]);
	char colorCode = argv[6][0];

	layer = ReadSceneFromFile(argv[1],layer);
	figure = ReadFigureFromFile(argv[2],figure);
	colorFigure = WriteColor(figure,colorCode);
	colorLayer = ReadSceneFromFile(argv[5],colorLayer);
	if(colorLayer.size()!=layer.size()){
		cout << "Layer sizes not consistent" << endl;
		exit(1);
	}

	layer = WriteObject(figure, layer, x, y);
	colorLayer = WriteObject(colorFigure, colorLayer, x, y);

	WriteSceneToFile(argv[1],layer);
	WriteSceneToFile(argv[5],colorLayer);
	return 0;
}
vector<string> ReadFigureFromFile(string FileName,vector<string> layer){
	ifstream fin;
	fin.open(FileName);
	if(fin.fail()){
		cout << FileName <<" fail to open file" << endl;
		exit(1);
	}
	string line;
	while(getline(fin,line)){
		layer.push_back(line);
	}
	fin.close();
	return layer;
}
vector<string> WriteColor(vector<string> pic,char colorCode){
	for(int i=0;i<int(pic.size());i++){
		for(int j=0;j<int(pic[i].size());j++){
			if(pic[i][j]!=' '){
				pic[i][j]=colorCode;
			}
		}
	}
	return pic;
}

vector<string> WriteObject(vector<string> pic, vector<string> layer, int pos_x, int pos_y){
	for(int i=0;i<int(pic.size());i++){
		for(int j=0;j<int(pic[i].size())-1;j++){
			if(((pos_y+i)>0 && (pos_y+i)<int(layer.size())) && ((pos_x+j)>0 && (pos_x+j)<int(layer[pos_y+i].size()))){
				if(pic[i][j]!=' '){
					layer[pos_y+i][pos_x+j] = pic[i][j];
				}
			}
			else{
				break;
			}
		}
	}
	return layer;

}

vector<string> ReadSceneFromFile(string FileName,vector<string> layer){
	ifstream fin;
	fin.open(FileName);
	if(fin.fail()){
		cout << FileName <<" fail to open file" << endl;
		exit(1);
	}
	string line;
	getline(fin,line);
	int originalLength = line.size();
	layer.push_back(line);
	while(getline(fin,line)){
		layer.push_back(line);
		if(int(line.size())!=originalLength){
			cout << "Layer X direction not consistent" << endl;
			exit(1);
		}
	}
	fin.close();
	return layer;
}

void WriteSceneToFile(string FileName,vector<string> layer){
	ofstream fout;
	fout.open(FileName);
	if(fout.fail()){
		cout << FileName <<" fail to open file" << endl;
		exit(1);
	}
	string line;
	int layerSize = int(layer.size());
	for(int i=0;i<layerSize-1;i++){
		fout << layer[i] << endl;
	}
	fout << layer[layerSize-1];
	fout.close();
}

