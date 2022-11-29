// Layer.h

#ifndef _layer_h
#define _layer_h

#include "common.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Layer{
	public:

	Layer();

	// the layer used in display
	vector<string> layer;
	// the layer storing initial state
	vector<string> originalLayer;

	// the layerName (file name of the layer)
	string LayerName;
	// the length in x direction
	int LayerXSize = 0;
	// the length in y direction
	int LayerYSize = 0;

	// copy originalLayer to layer
	void ResetLayer();
	// print layer to screen, this is used in testing
	void PrintLayer();

	// write a figure to layer
	void WriteObject(vector<vector<char>> pic, int pos_x, int pos_y, int size_x, int size_y);
	void WriteObject(vector<string> pic, int pos_x, int pos_y, int size_x, int size_y);
	// check if the point is out of layer
	bool OutOfLayer(int x,int y);

	// read layer with FileName to originalLayer and layer
	void ReadLayerFromFile(string FileName);
	// cover layer with newLayer(ignoring all the spaces)
	void AddLayerOnTop(Layer newLayer);

	// erase layer (an opposite operation to ReadLayerFromFile)
	void EraseLayer();
	// erase and read new layer
	void ReadNewLayerFromFile(string Filename);
};

#endif
