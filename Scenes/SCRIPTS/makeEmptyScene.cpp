// Sat Nov  5 11:10:47 CST 2022
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

string makeCeil(int width,string edge);
string makeInter(int width,string edge);
void WriteSceneToFile(string FileName,vector<string> layer);

int main(int argc, char* argv[]){
	if(argc!=4){
		cout << "argc: " << argc << endl;
		cout << "Usage: scene_width scene_height FileName" << endl;
		exit(1);
	}
	int scene_width=atoi(argv[1]);
	int scene_height=atoi(argv[2]);
	vector<string> layer;
	string edgeChar = "*";
	string ceil = makeCeil(scene_width,edgeChar);
	string inter = makeInter(scene_width,edgeChar);
	layer.push_back(ceil);
	for(int i=1;i<scene_height-1;i++){
		layer.push_back(inter);
	}
	layer.push_back(ceil);
	WriteSceneToFile(argv[3],layer);

	return 0;
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

string makeInter(int width,string edge){
	string ceil= edge;
	for(int i=1;i<width-1;i++){
		ceil+=" ";
	}
	ceil+=edge;
	return ceil;
}
string makeCeil(int width,string edge){
	string ceil= edge;
	for(int i=0;i<width-1;i++){
		ceil=edge+ceil;
	}
	return ceil;
}
