// Fri Nov  4 12:08:50 CST 2022
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

vector<string> ReadSceneFromFile(string FileName,vector<string> layer);
void WriteSceneToFile(string FileName,vector<string> layer);
vector<string> WriteObject(vector<string> pic, vector<string> layer, int pos_x, int pos_y);

int main(int argc, char* argv[]){
	//  second arg: txtfile of scene; third arg: txtfile storing figure, no \n at end; forth arg: x position; fifth arg:
	// y position; 
	if(argc != 5){
		cout << "argument number not right" << endl;
		exit(1);
	}

	vector<string> layer;
	vector<string> figure;

	int x = atoi(argv[3]);
	int y = atoi(argv[4]);

	layer = ReadSceneFromFile(argv[1],layer);
	figure = ReadSceneFromFile(argv[2],figure);

	layer = WriteObject(figure, layer, x, y);

	WriteSceneToFile(argv[1],layer);
	return 0;
}

vector<string> WriteObject(vector<string> pic, vector<string> layer, int pos_x, int pos_y){
	for(int i=0;i<pic.size();i++){
		for(int j=0;j<pic[i].size()-1;j++){
			if(((pos_y+i)>0 && (pos_y+i)<layer.size()) && ((pos_x+j)>0 && (pos_x+j)<layer[pos_y+i].size())){
				layer[pos_y+i][pos_x+j] = pic[i][j];
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

