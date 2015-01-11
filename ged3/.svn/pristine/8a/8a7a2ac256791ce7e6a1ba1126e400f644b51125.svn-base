#include "Maya3DImporter.h"


typedef struct
{
	float x, y, z;
}Vertex;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;

Maya3DImporter::Maya3DImporter(){
}


Maya3DImporter::Maya3DImporter(const Maya3DImporter& other){
}


Maya3DImporter::~Maya3DImporter(){
}

VertexHeader::VertexType* Maya3DImporter::GetVertices(){
	return m_vertices;
}

unsigned long* Maya3DImporter::GetIndices(){
	return m_indices;
}

bool Maya3DImporter::Convert(char* fileName, int& vCount,int& fCount){
	bool result = false;
	int vertexCount, textureCount, normalCount, faceCount;
	char garbage;

	Log::COut("=========================== \nStart reading model");
	
	// Read in the name of the model file.
	GetModelFilename(fileName);

	// Read in the number of vertices, tex coords, normals, and faces so that the data structures can be initialized with the exact sizes needed.
	result = ReadFileCounts(fileName, vertexCount, textureCount, normalCount, faceCount);

	//PUT DATA IN 
	vCount = vertexCount;
	fCount = vertexCount;

	if(!result)
	{
		Log::COut("Fail to import the model");
		return false;
	}

	Log::COut("Vertex Count: " + to_string(vertexCount));
	Log::COut("Texture Count: " +  to_string(textureCount));
	Log::COut("Normal Count: " +  to_string(normalCount));
	Log::COut("Face Count: " +  to_string(faceCount));


	// Now read the data from the file into the data structures and then output it in our model format.
	result = LoadDataStructures(fileName, vertexCount, textureCount, normalCount, faceCount);

	if(!result)
	{
		return false;
	}

	return true;
}

void Maya3DImporter::GetModelFilename(char* filename){
	bool done;
	ifstream fin;

	// Loop until we have a file name.
	done = false;

	// Attempt to open the file.
	fin.open(filename);

	if(fin.good())
	{
		// If the file exists and there are no problems then exit since we have the file name.
		done = true;
	}
	else
	{
		// If the file does not exist or there was an issue opening it then notify the user and repeat the process.
		fin.clear();
		cout << endl;
		cout << "File " << filename << " could not be opened." << endl << endl;
	}

	return;
}

D3DXVECTOR3 CalculateTangent(D3DXVECTOR3 normal)
{
	D3DXVECTOR3 tan1, tan2, tangent;
	D3DXVec3Cross(&tan1, &normal, &D3DXVECTOR3(0,0,1));
	D3DXVec3Cross(&tan2, &normal, &D3DXVECTOR3(0,1,0));

	if( D3DXVec3Length(&tan1) > D3DXVec3Length(&tan2))
		tangent = tan1;
	else
		tangent = tan2;

	D3DXVec3Normalize(&tangent,&tangent);

	return tangent;
}

bool Maya3DImporter::ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount){
	ifstream fin;
	char input;

	// Initialize the counts.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// Open the file.
	fin.open(filename);

	// Check if it was successful in opening the file.
	if(fin.fail() == true)
	{
		return false;
	}

	// Read from the file and continue to read until the end of the file is reached.
	fin.get(input);
	while(!fin.eof())
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if(input == 'v')
		{
			fin.get(input);
			if(input == ' ') { vertexCount++; }
			if(input == 't') { textureCount++; }
			if(input == 'n') { normalCount++; }
		}

		// If the line starts with 'f' then increment the face count.
		if(input == 'f')
		{
			fin.get(input);
			if(input == ' ') { faceCount++; }
		}
		
		// Otherwise read in the remainder of the line.
		while(input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();

	return true;
}


bool Maya3DImporter::LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount){
	Log::COut("Processing.....");
	Vertex *vertices, *texcoords, *normals;
	FaceType *faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;

	// Initialize the four data structures.
	vertices = new Vertex[vertexCount];
	if(!vertices)
	{
		return false;
	}

	texcoords = new Vertex[textureCount];
	if(!texcoords)
	{
		return false;
	}

	normals = new Vertex[normalCount];
	if(!normals)
	{
		return false;
	}

	faces = new FaceType[faceCount];
	if(!faces)
	{
		return false;
	}

	// Initialize the indexes.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// Open the file.
	fin.open(filename);

	// Check if it was successful in opening the file.
	if(fin.fail() == true)
	{
		return false;
	}

	// Read in the vertices, texture coordinates, and normals into the data structures.
	// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
	fin.get(input);
	while(!fin.eof())
	{
		if(input == 'v')
		{
			fin.get(input);

			// Read in the vertices.
			if(input == ' ') 
			{ 
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				// Invert the Z vertex to change to left hand system.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++; 
			}

			// Read in the texture uv coordinates.
			if(input == 't') 
			{ 
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				// Invert the V texture coordinates to left hand system.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++; 
			}

			// Read in the normals.
			if(input == 'n') 
			{ 
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				// Invert the Z normal to change to left hand system.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++; 
			}
		}

		// Read in the faces.
		if(input == 'f') 
		{
			fin.get(input);
			if(input == ' ')
			{
				// Read the face data in backwards to convert it to a left hand system from right hand system.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// Read in the remainder of the line.
		while(input != '\n')
		{
			fin.get(input);
		}

		// Start reading the beginning of the next line.
		fin.get(input);
	}

	// Close the file.
	fin.close();

	//==FROM HERE==//
	int indexCount = 0;

	//Set array length
	m_vertices = new VertexHeader::VertexType[faceCount*3];
	m_indices = new unsigned long[faceCount*3];

	// Now loop through all the faces and output the three vertices for each face.
	for(int i=0; i<faceIndex; i++)
	{
		
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;
		
		m_indices[indexCount] = indexCount;

		//Vertex
		m_vertices[indexCount].position.x = vertices[vIndex].x;
		m_vertices[indexCount].position.y = vertices[vIndex].y;
		m_vertices[indexCount].position.z = vertices[vIndex].z;

		//Textyre
		m_vertices[indexCount].texture.x = texcoords[tIndex].x;
		m_vertices[indexCount].texture.y = texcoords[tIndex].y;

		//Normal
		m_vertices[indexCount].normal.x = normals[nIndex].x;
		m_vertices[indexCount].normal.y = normals[nIndex].y;
		m_vertices[indexCount].normal.z = normals[nIndex].z;

		//Tangent
		m_vertices[indexCount].tangent = CalculateTangent(m_vertices[indexCount].normal);
		D3DXVec3Cross(&m_vertices[indexCount].binormal, 
			&m_vertices[indexCount].normal,
			&m_vertices[indexCount].tangent);
			 


		//increase index
		indexCount++; 

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		m_indices[indexCount] = indexCount;

		//Vertex
		m_vertices[indexCount].position.x = vertices[vIndex].x;
		m_vertices[indexCount].position.y = vertices[vIndex].y;
		m_vertices[indexCount].position.z = vertices[vIndex].z;

		//Textyre
		m_vertices[indexCount].texture.x = texcoords[tIndex].x;
		m_vertices[indexCount].texture.y = texcoords[tIndex].y;

		//Normal
		m_vertices[indexCount].normal.x = normals[nIndex].x;
		m_vertices[indexCount].normal.y = normals[nIndex].y;
		m_vertices[indexCount].normal.z = normals[nIndex].z;
		//Tangent
		m_vertices[indexCount].tangent = CalculateTangent(m_vertices[indexCount].normal);
		//biNormal
		D3DXVec3Cross(&m_vertices[indexCount].binormal, 
			&m_vertices[indexCount].normal,
			&m_vertices[indexCount].tangent);
		//increase index
		indexCount++; 

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		//Index
		m_indices[indexCount] = indexCount;

		//Vertex
		m_vertices[indexCount].position.x = vertices[vIndex].x;
		m_vertices[indexCount].position.y = vertices[vIndex].y;
		m_vertices[indexCount].position.z = vertices[vIndex].z;

		//Textyre
		m_vertices[indexCount].texture.x = texcoords[tIndex].x;
		m_vertices[indexCount].texture.y = texcoords[tIndex].y;

		//Normal
		m_vertices[indexCount].normal.x = normals[nIndex].x;
		m_vertices[indexCount].normal.y = normals[nIndex].y;
		m_vertices[indexCount].normal.z = normals[nIndex].z;
		//Tangent
		m_vertices[indexCount].tangent = CalculateTangent(m_vertices[indexCount].normal);
		//BiNormal
		D3DXVec3Cross(&m_vertices[indexCount].binormal, 
			&m_vertices[indexCount].normal,
			&m_vertices[indexCount].tangent);
		//increase index
		indexCount++; 
	}

	// Release the four data structures.
	if(vertices)
	{
		delete [] vertices;
		vertices = 0;
	}
	if(texcoords)
	{
		delete [] texcoords;
		texcoords = 0;
	}
	if(normals)
	{
		delete [] normals;
		normals = 0;
	}
	if(faces)
	{
		delete [] faces;
		faces = 0;
	}

	Log::COut("Model loaded !!");
	return true;
}