
#include "common.h"
#include "Layer.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

Layer::Layer(){
}

void Layer::ResetLayer(){
	for(int i=0;i<LayerYSize;i++){
		layer[i]=originalLayer[i];
	}
}
void Layer::WriteObject(vector<vector<char>> pic, int pos_x, int pos_y, int size_x, int size_y){
	for(int i=0;i<size_y;i++){
		for(int j=0;j<size_x;j++){
			if(!OutOfLayer(pos_x+j,pos_y+i)){
				if(pic[i][j]!=' '){
					layer[pos_y+i][pos_x+j] = pic[i][j];
				}
			}
		}
	}

}
bool Layer::OutOfLayer(int x,int y){
	if(x >= LayerXSize-1 || x <= 0){
		return true;
	}
	if(y >= LayerYSize-1 || y <= 0){
		return true;
	}
	return false;
}

void Layer::ReadLayerFromFile(string FileName){
	LayerName = FileName;
	ifstream fin;
	fin.open(FileName);
	if(LayerYSize != 0){
		cerr << LayerName << " already read a file" << endl;
		exit(1);
	}
	if(fin.fail()){
		cerr << LayerName <<" fail to open file" << endl;
		exit(1);
	}
	string line;
	while(getline(fin,line)){
		if(LayerXSize != 0){
			if(int(line.size()) != LayerXSize){
				cerr << LayerName << " Layer X direction length not consistent" << endl;
				exit(1);
			}
		}
		originalLayer.push_back(line);
		layer.push_back(line);
		LayerXSize = line.size();
	}
	LayerYSize = originalLayer.size();
	fin.close();
}

void Layer::PrintLayer(){
	for(int i=0;i<LayerYSize;i++){
		cout<<layer[i]<<endl;
	}
}

void Layer::AddLayerOnTop(Layer newLayer){
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

void Layer::EraseLayer() {
	LayerXSize = 0;
	LayerYSize = 0;
	LayerName = "";
	layer.clear();
	originalLayer.clear();
}

void Layer::ReadNewLayerFromFile(string Filename) {
	EraseLayer();
	ReadLayerFromFile(Filename);
}

