// Fri Nov  4 12:08:50 CST 2022
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

vector<string> ReadSceneFromFile(string FileName);
vector<string> DiffLayer(vector<string> layer, vector<string> editorPhyLayer);
void WriteSceneToFile(string FileName,vector<string> layer);
vector<string> WritePlatformToScene(vector<string> layer, vector<string> editorPhyLayer, char platform_look);
vector<string> WritePlatformColorToScene(vector<string> colorLayer, vector<string> editorPhyLayer, char platformColor);

int main(int argc, char* argv[]){
	// first arg: sceneCombined.txt; second arg: editorPhyLayer; third arg: phyLayer; forth arg: platform look; fifth
	// arg: platform storing in this scene; sixth arg: Platform Color; seventh arg: Platform Color File
	if(argc != 8){
		cout << "argument number not right" << endl;
		exit(1);
	}

	vector<string> sceneCombined; 
	vector<string> editorPhyLayer;
	vector<string> platformScene;
	vector<string> phyLayer;

	vector<string> colorScene;

	sceneCombined = ReadSceneFromFile(argv[1]);
	editorPhyLayer = ReadSceneFromFile(argv[2]);
	colorScene = ReadSceneFromFile(argv[7]);
	platformScene = ReadSceneFromFile(argv[5]);

	char platform_look = argv[4][0];
	char platformColor = argv[6][0];

	platformScene = WritePlatformToScene(platformScene,editorPhyLayer,platform_look);

	colorScene = WritePlatformColorToScene(colorScene,editorPhyLayer,platformColor);

	phyLayer = DiffLayer(sceneCombined,editorPhyLayer);

	WriteSceneToFile(argv[5],platformScene);
	WriteSceneToFile(argv[3],phyLayer);
	WriteSceneToFile(argv[7],colorScene);


	return 0;
}

vector<string> WritePlatformColorToScene(vector<string> colorLayer, vector<string> editorPhycolorLayer, char platformColor){
	int colorLayerXSize = colorLayer[0].size();
	int editorPhycolorLayerXSize = editorPhycolorLayer[0].size();
	int colorLayerYSize = colorLayer.size();
	int editorPhycolorLayerYSize = editorPhycolorLayer.size();
	if(editorPhycolorLayerXSize != colorLayerXSize){
		cout << " colorLayerXSize not consistent" << endl;
		exit(1);
	}
	if(editorPhycolorLayerYSize != colorLayerYSize){
		cout << " colorLayerYSize not consistent" << endl;
		exit(1);
	}
	for(int i=0;i<colorLayerYSize;i++){
		for(int j=0;j<colorLayerXSize;j++){
			if(editorPhycolorLayer[i][j]=='p'){
				colorLayer[i][j] = platformColor;
			}
		}
	}
	return colorLayer;
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
	int originalLength = int(line.size());
	layer.push_back(line);
	while(getline(fin,line)){
		layer.push_back(line);
		if(int(line.size())!=originalLength){
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

vector<string> WritePlatformToScene(vector<string> layer, vector<string> editorPhyLayer, char platform_look){
	int layerXSize = layer[0].size();
	int editorPhyLayerXSize = editorPhyLayer[0].size();
	int layerYSize = layer.size();
	int editorPhyLayerYSize = editorPhyLayer.size();
	if(editorPhyLayerXSize != layerXSize){
		cout << " LayerXSize not consistent" << endl;
		exit(1);
	}
	if(editorPhyLayerYSize != layerYSize){
		cout << " LayerYSize not consistent" << endl;
		exit(1);
	}
	for(int i=0;i<layerYSize;i++){
		for(int j=0;j<layerXSize;j++){
			if(editorPhyLayer[i][j]=='p'){
				layer[i][j] = platform_look;
			}
		}
	}
	return layer;
}

vector<string> DiffLayer(vector<string> layer, vector<string> editorPhyLayer){
	int layerXSize = layer[0].size();
	int editorPhyLayerXSize = editorPhyLayer[0].size();
	int layerYSize = layer.size();
	int editorPhyLayerYSize = editorPhyLayer.size();
	if(editorPhyLayerXSize != layerXSize){
		cout << " LayerXSize not consistent" << endl;
		exit(1);
	}
	if(editorPhyLayerYSize != layerYSize){
		cout << " LayerYSize not consistent" << endl;
		exit(1);
	}
	for(int i=0;i<layerYSize;i++){
		for(int j=0;j<layerXSize;j++){
			if(editorPhyLayer[i][j]==layer[i][j] && editorPhyLayer[i][j]!='p'){
				editorPhyLayer[i][j] = ' ';
			}
		}
	}
	return editorPhyLayer;
}
