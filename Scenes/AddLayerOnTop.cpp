// Fri Nov  4 12:08:50 CST 2022
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

vector<string> ReadSceneFromFile(string FileName);
vector<string> WriteObject(vector<string> pic, vector<string> layer, int pos_x, int pos_y);

int main(int argc, char* argv[]){
	//  second arg: txtfile of scene; third arg: txtfile storing figure, no \n at end; forth arg: x position; fifth arg:
	// y position; 
	if(argc != 4){
		cout << "argument number not right" << endl;
		exit(1);
	}

	vector<string> first_layer; 
	vector<string> second_layer;
	vector<string> output_layer;

	first_layer = ReadSceneFromFile(argv[1],layer);
	second_layer = ReadSceneFromFile(argv[2],layer);
	output_layer = ReadSceneFromFile(argv[3],layer);


	WriteSceneToFile(argv[1],layer);
	return 0;
}


vector<string> ReadSceneFromFile(string FileName){
	vector<string> layer;
	ifstream fin;
	fin.open(FileName);
	if(fin.fail()){
		cout << FileName <<" fail to open file" << endl;
		exit(1);
	}
	string line;
	getline(fin,line);
	int originalLength = 0;
	while(getline(fin,line)){

		layer.push_back(line);
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
	int layerSize = layer.size();
	for(int i=0;i<layerSize-1;i++){
		fout << layer[i] << endl;
	}
	fout << layer[layerSize-1];
	fout.close();
}

void AddLayerOnTop(Layer layer, Layer newLayer){
	if(newLayer.LayerXSize != LayerXSize){
		cerr << LayerName << " LayerXSize not consistent" << endl;
		exit(1);
	}
	if(newLayer.LayerYSize != LayerYSize){
		cerr << LayerName << " LayerYSize not consistent" << endl;
		exit(1);
	}
	for(int i=0;i<LayerYSize;i++){
		for(int j=0;j<LayerXSize;j++){
			if(newLayer.layer[i][j]!=' '){
				layer[i][j] = newLayer.layer[i][j];
			}
		}
	}
}
