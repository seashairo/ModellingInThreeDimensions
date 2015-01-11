////////////////////////////////////////////////////////////////////////////////
// Filename: Maya3DImporter.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _Maya3DImporter_
#define _Maya3DImporter_

#include <iostream>
#include <fstream>
#include "Log.h"
#include "VertexHeader.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: Maya3DImporter
////////////////////////////////////////////////////////////////////////////////
class Maya3DImporter
{
public:
	Maya3DImporter();
	Maya3DImporter(const Maya3DImporter&);
	~Maya3DImporter();

	bool Convert(char* fileName, int& vCount, int& fCount);
	VertexHeader::VertexType* GetVertices();
	unsigned long* GetIndices();
private:
	void GetModelFilename(char* filename);
	bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount);
	bool LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount);
	VertexHeader::VertexType* m_vertices;
	unsigned long* m_indices;
};

#endif