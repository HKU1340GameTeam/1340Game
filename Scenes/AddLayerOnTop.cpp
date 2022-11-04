// Fri Nov  4 12:08:50 CST 2022
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

vector<string> ReadSceneFromFile(string FileName);
vector<string> AddLayerOnTop(vector<string> layer, vector<string> newLayer);
void WriteSceneToFile(string FileName,vector<string> layer);

int main(int argc, char* argv[]){
	// first arg: first layer; second arg: second layer; third arg: output layer
	// put second layer on top of first layer and output it to output layer
	if(argc != 4){
		cout << "argument number not right" << endl;
		exit(1);
	}

	vector<string> first_layer; 
	vector<string> second_layer;
	vector<string> output_layer;

	first_layer = ReadSceneFromFile(argv[1]);
	second_layer = ReadSceneFromFile(argv[2]);
	output_layer = AddLayerOnTop(first_layer,second_layer);

	WriteSceneToFile(argv[3],output_layer);


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
	int originalLength = line.size();
	layer.push_back(line);
	while(getline(fin,line)){
		layer.push_back(line);
		if(line.size()!=originalLength){
			cout << FileName << "Layer X Size not consistent" << endl;
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
	int layerSize = layer.size();
	for(int i=0;i<layerSize-1;i++){
		fout << layer[i] << endl;
	}
	fout << layer[layerSize-1];
	fout.close();
}

vector<string> AddLayerOnTop(vector<string> layer, vector<string> newLayer){
	int layerXSize = layer[0].size();
	int newLayerXSize = newLayer[0].size();
	int layerYSize = layer.size();
	int newLayerYSize = newLayer.size();
	if(newLayerXSize != layerXSize){
		cout << " LayerXSize not consistent" << endl;
		exit(1);
	}
	if(newLayerYSize != layerYSize){
		cout << " LayerYSize not consistent" << endl;
		exit(1);
	}
	for(int i=0;i<layerYSize;i++){
		for(int j=0;j<layerXSize;j++){
			if(newLayer[i][j]!=' '){
				layer[i][j] = newLayer[i][j];
			}
		}
	}
	return layer;
}
