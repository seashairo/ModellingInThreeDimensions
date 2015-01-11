#include "MeshClass.h"

ID3D10Buffer* MeshClass::prevMesh = 0;

MeshClass::MeshClass(){
	m_vertexCount = 0;
	m_indexCount = 0;

	m_internalVertexCount = 0;
	m_internalIndexCount = 0;

	m_internalVertices = 0;
	m_internalIndices = 0;
	m_foliageInstance = 0;

	m_radius = 0;

	m_importer = new Maya3DImporter;

	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_instanceBuffer = 0;
}

MeshClass::MeshClass(const MeshClass& other){
}

MeshClass::~MeshClass(){
}

// Initialize the mesh.
bool MeshClass::Initialize(){
	Log::COut("Initialized mesh.");
	return true;
}

bool MeshClass::InitializeBuffers(ID3D10Device* device){
	InstanceType* instances;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc, instanceBufferDesc;
    D3D10_SUBRESOURCE_DATA vertexData, indexData, instanceData;
	HRESULT result;
	int i;

	m_instanceCount = 1;

	instances = new InstanceType[m_instanceCount];
	if(!instances)
	{
		return false;
	}

	// Set up the description of the vertex buffer.
    vertexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexHeader::VertexType) * GetVertexCount();
    vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = GetVertices();

	// Now finally create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the index buffer.
    indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * GetIndexCount();
    indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = GetIndices();

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Load the instance array with data.
	for (i = 0; i<m_instanceCount; i++)
	{
		instances[i].position = D3DXVECTOR3(0, 0, 0);
	}

	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	instanceBufferDesc.ByteWidth = sizeof(InstanceType) * m_instanceCount;
	instanceBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = 0;
	instanceBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = instances;

	// Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the instance array now that the instance buffer has been created and loaded.
	delete [] instances;
	instances = 0;

	return true;
}


void MeshClass::ShutdownBuffers(){
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	// Release the instance buffer.
	if(m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	return;
}

void MeshClass::RenderBuffers(ID3D10Device* device){
	if(MeshClass::prevMesh == m_vertexBuffer){
		return;
	}
	MeshClass::prevMesh = m_vertexBuffer;

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D10Buffer* bufferPointers[2];

	// Set vertex buffer stride and offset.
    strides[0] = sizeof(VertexHeader::VertexType);
	strides[1] = 0; 

	offsets[0] = 0;
	offsets[1] = 0;
	
	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;	
	bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	device->IASetVertexBuffers(0, 2, bufferPointers, strides, offsets);

    // Set the index buffer to active in the input assembler so it can be rendered.
    device->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
    device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

// Release the mesh.
void MeshClass::Shutdown(){
	m_internalVertices = 0;
	m_internalIndices = 0;

	m_importer = 0;
}

// Return the mesh's vertices.
VertexHeader::VertexType* MeshClass::GetVertices(){
	return &m_vertices[0];
}

VertexHeader::VertexType* MeshClass::GetVertexData(){
	return m_internalVertices;
}

// Return the mesh's indices.
unsigned long* MeshClass::GetIndices(){
	return &m_indices[0];
}

// How many vertices the mesh has.
int MeshClass::GetVertexCount(){
	return m_vertexCount;
}

// How many indices the mesh has.
int MeshClass::GetIndexCount(){
	return m_indexCount;
}

// radius of the mesh
float MeshClass::GetRadius(){
	return m_radius;
} 

#pragma region Primitives
// Set the mesh to a plane rectangular plane. 
//The entity using this plane will need to set the scale, rotation, and position correctly.

void MeshClass::SetInternalPlane(){
	// Set vertex and index counts.
	// There are 4 corners, and 6 indices to link them.
	m_internalVertexCount = 6;
	m_internalIndexCount = 6;

	// Create the vertex and index arrays.
	m_internalVertices = new VertexHeader::VertexType[m_internalVertexCount];
	m_internalIndices = new unsigned long[m_internalIndexCount];
	
	// Set the position of the vertices.
	m_internalVertices[5].position = D3DXVECTOR3( -1.0f, 1.0f, 0.0f); // top left
	m_internalVertices[4].position = D3DXVECTOR3( -1.0f,  -1.0f, 0.0f); // top right
	m_internalVertices[3].position = D3DXVECTOR3( 1.0f, -1.0f, 0.0f); // bottom left
	m_internalVertices[2].position = D3DXVECTOR3( 1.0f,  -1.0f, 0.0f); // top right
	m_internalVertices[1].position = D3DXVECTOR3( 1.0f, 1.0f, 0.0f); // bottom left
	m_internalVertices[0].position = D3DXVECTOR3(-1.0f,  1.0f, 0.0f); // bottom right

	// Set the texture coordinates
	m_internalVertices[5].texture = D3DXVECTOR2(0, 0);// top left
	m_internalVertices[4].texture = D3DXVECTOR2(0, 1);// top right
	m_internalVertices[3].texture = D3DXVECTOR2(1, 1);// bottom left
	m_internalVertices[2].texture = D3DXVECTOR2(1, 1);// top right
	m_internalVertices[1].texture = D3DXVECTOR2(1, 0);// bottom left
	m_internalVertices[0].texture = D3DXVECTOR2(0, 0);// bottom right


	m_internalVertices[5].normal = D3DXVECTOR3( 0,0,1); // top left
	m_internalVertices[4].normal = D3DXVECTOR3( 0,0,1); // top right
	m_internalVertices[3].normal = D3DXVECTOR3( 0,0,1); // bottom left
	m_internalVertices[2].normal = D3DXVECTOR3( 0,0,1); // top right
	m_internalVertices[1].normal = D3DXVECTOR3( 0,0,1); // bottom left
	m_internalVertices[0].normal = D3DXVECTOR3( 0,0,1); // bottom right

	m_internalVertices[5].tangent = D3DXVECTOR3( 0,-1,0); // top left
	m_internalVertices[4].tangent = D3DXVECTOR3( 0,-1,0); // top right
	m_internalVertices[3].tangent = D3DXVECTOR3( 0,-1,0); // bottom left
	m_internalVertices[2].tangent = D3DXVECTOR3( 0,-1,0); // top right
	m_internalVertices[1].tangent = D3DXVECTOR3( 0,-1,0); // bottom left
	m_internalVertices[0].tangent = D3DXVECTOR3( 0,-1,0); // bottom right

	for(int i = 0; i < m_internalVertexCount; i++){
		m_internalIndices[i] = i;
	}	

	Log::COut("Plane created.");
}

// Set the mesh to a cube with set size, centred around (0,0,0).
void MeshClass::SetInternalCube(float length){

	// Set the vertex and index counts.
	// 8 vertices are required for a cube, but to make texturing work we need
	// an extra 8. The first 8 are used for the sides, second 8 are used for the top.
	m_internalVertexCount = 36;
	m_internalIndexCount = 36;

	// Create blank arrays of vertices and indices.
	m_internalVertices = new VertexHeader::VertexType[m_internalVertexCount];
	m_internalIndices = new unsigned long[m_internalIndexCount];

	// Set the positions of the vertices.
	// Vertices for the sides.
	m_internalVertices[0].position = D3DXVECTOR3(-length/2,  length/2, -length/2);
	m_internalVertices[1].position = D3DXVECTOR3( length/2,  length/2, -length/2);
	m_internalVertices[2].position = D3DXVECTOR3(-length/2, -length/2, -length/2);
	m_internalVertices[3].position = D3DXVECTOR3(-length/2, -length/2, -length/2);
	m_internalVertices[4].position = D3DXVECTOR3( length/2,  length/2, -length/2);
	m_internalVertices[5].position = D3DXVECTOR3( length/2, -length/2, -length/2);

	// Right
	m_internalVertices[6].position = D3DXVECTOR3( length/2,  length/2, -length/2);
	m_internalVertices[7].position = D3DXVECTOR3( length/2,  length/2,  length/2);
	m_internalVertices[8].position = D3DXVECTOR3( length/2, -length/2, -length/2);
	m_internalVertices[9].position = D3DXVECTOR3( length/2, -length/2, -length/2);
	m_internalVertices[10].position = D3DXVECTOR3( length/2,  length/2,  length/2);
	m_internalVertices[11].position = D3DXVECTOR3( length/2, -length/2,  length/2);

	// Back
	m_internalVertices[12].position = D3DXVECTOR3( length/2,  length/2,  length/2);
	m_internalVertices[13].position = D3DXVECTOR3(-length/2,  length/2,  length/2);
	m_internalVertices[14].position = D3DXVECTOR3( length/2, -length/2,  length/2);
	m_internalVertices[15].position = D3DXVECTOR3( length/2, -length/2,  length/2);
	m_internalVertices[16].position = D3DXVECTOR3(-length/2,  length/2,  length/2);
	m_internalVertices[17].position = D3DXVECTOR3(-length/2, -length/2,  length/2);

	// Left
	m_internalVertices[18].position = D3DXVECTOR3(-length/2,  length/2,  length/2);
	m_internalVertices[19].position = D3DXVECTOR3(-length/2,  length/2, -length/2);
	m_internalVertices[20].position = D3DXVECTOR3(-length/2, -length/2,  length/2);
	m_internalVertices[21].position = D3DXVECTOR3(-length/2, -length/2,  length/2);
	m_internalVertices[22].position = D3DXVECTOR3(-length/2,  length/2, -length/2);
	m_internalVertices[23].position = D3DXVECTOR3(-length/2, -length/2, -length/2);

	// Top
	m_internalVertices[24].position = D3DXVECTOR3(-length/2,  length/2,  length/2);
	m_internalVertices[25].position = D3DXVECTOR3( length/2,  length/2,  length/2);
	m_internalVertices[26].position = D3DXVECTOR3(-length/2,  length/2, -length/2);
	m_internalVertices[27].position = D3DXVECTOR3(-length/2,  length/2, -length/2);
	m_internalVertices[28].position = D3DXVECTOR3( length/2,  length/2,  length/2);
	m_internalVertices[29].position = D3DXVECTOR3( length/2,  length/2, -length/2);

	// Bottom
	m_internalVertices[30].position = D3DXVECTOR3(-length/2, -length/2, -length/2);
	m_internalVertices[31].position = D3DXVECTOR3( length/2, -length/2, -length/2);
	m_internalVertices[32].position = D3DXVECTOR3(-length/2, -length/2,  length/2);
	m_internalVertices[33].position = D3DXVECTOR3(-length/2, -length/2,  length/2);
	m_internalVertices[34].position = D3DXVECTOR3( length/2, -length/2, -length/2);
	m_internalVertices[35].position = D3DXVECTOR3( length/2, -length/2,  length/2);

	// Set the texture position for each vertex.
	m_internalVertices[0].texture = D3DXVECTOR2(0, 0);
	m_internalVertices[1].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[2].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[3].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[4].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[5].texture = D3DXVECTOR2(1, 1);
						  
	// Right			  
	m_internalVertices[6].texture =  D3DXVECTOR2(0, 0);
	m_internalVertices[7].texture =  D3DXVECTOR2(0, 1);
	m_internalVertices[8].texture =  D3DXVECTOR2(1, 0);
	m_internalVertices[9].texture =  D3DXVECTOR2(1, 0);
	m_internalVertices[10].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[11].texture = D3DXVECTOR2(1, 1);
						   
	// Back				   
	m_internalVertices[12].texture = D3DXVECTOR2(0, 0);
	m_internalVertices[13].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[14].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[15].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[16].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[17].texture = D3DXVECTOR2(1, 1);
						   
	// Left				   
	m_internalVertices[18].texture = D3DXVECTOR2(0, 0);
	m_internalVertices[19].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[20].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[21].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[22].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[23].texture = D3DXVECTOR2(1, 1);
						   
	// Top				   
	m_internalVertices[24].texture = D3DXVECTOR2(0, 0);
	m_internalVertices[25].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[26].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[27].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[28].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[29].texture = D3DXVECTOR2(1, 1);
						   
	// Bottom			   
	m_internalVertices[30].texture = D3DXVECTOR2(0, 0);
	m_internalVertices[31].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[32].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[33].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[34].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[35].texture = D3DXVECTOR2(1, 1);

	// Normals
	m_internalVertices[0].normal = D3DXVECTOR3(0, 0, -1);
	m_internalVertices[1].normal = D3DXVECTOR3(0, 0, -1);
	m_internalVertices[2].normal = D3DXVECTOR3(0, 0, -1);
	m_internalVertices[3].normal = D3DXVECTOR3(0, 0, -1);
	m_internalVertices[4].normal = D3DXVECTOR3(0, 0, -1);
	m_internalVertices[5].normal = D3DXVECTOR3(0, 0, -1);

	// Right
	m_internalVertices[6].normal = D3DXVECTOR3( 1, 0, 0);
	m_internalVertices[7].normal = D3DXVECTOR3( 1, 0, 0);
	m_internalVertices[8].normal = D3DXVECTOR3( 1, 0, 0);
	m_internalVertices[9].normal = D3DXVECTOR3( 1, 0, 0);
	m_internalVertices[10].normal = D3DXVECTOR3(1, 0, 0);
	m_internalVertices[11].normal = D3DXVECTOR3(1, 0, 0);

	// Back
	m_internalVertices[12].normal = D3DXVECTOR3(0, 0, 1);
	m_internalVertices[13].normal = D3DXVECTOR3(0, 0, 1);
	m_internalVertices[14].normal = D3DXVECTOR3(0, 0, 1);
	m_internalVertices[15].normal = D3DXVECTOR3(0, 0, 1);
	m_internalVertices[16].normal = D3DXVECTOR3(0, 0, 1);
	m_internalVertices[17].normal = D3DXVECTOR3(0, 0, 1);

	// Left
	m_internalVertices[18].normal = D3DXVECTOR3(-1, 0, 0);
	m_internalVertices[19].normal = D3DXVECTOR3(-1, 0, 0);
	m_internalVertices[20].normal = D3DXVECTOR3(-1, 0, 0);
	m_internalVertices[21].normal = D3DXVECTOR3(-1, 0, 0);
	m_internalVertices[22].normal = D3DXVECTOR3(-1, 0, 0);
	m_internalVertices[23].normal = D3DXVECTOR3(-1, 0, 0);

	// Top
	m_internalVertices[24].normal = D3DXVECTOR3(0, 1, 0);
	m_internalVertices[25].normal = D3DXVECTOR3(0, 1, 0);
	m_internalVertices[26].normal = D3DXVECTOR3(0, 1, 0);
	m_internalVertices[27].normal = D3DXVECTOR3(0, 1, 0);
	m_internalVertices[28].normal = D3DXVECTOR3(0, 1, 0);
	m_internalVertices[29].normal = D3DXVECTOR3(0, 1, 0);

	// Bottom
	m_internalVertices[30].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[31].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[32].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[33].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[34].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[35].normal = D3DXVECTOR3(0, -1, 0);


	// TANGENT

	// Set the indices.
	for(int i = 0; i < 36; i++){
		CalculateTangentBinormal
			(m_internalVertices[i].normal, 
			m_internalVertices[i].tangent,
			m_internalVertices[i].binormal);
		m_internalIndices[i] = i;
	}	

	Log::COut("Cube created with length " + std::to_string(length) + " around origin (0,0,0)");
}

void MeshClass::SetInternalPyramid(){

	// Set the vertex and index counts.
	// 8 vertices are required for a cube, but to make texturing work we need
	// an extra 8. The first 8 are used for the sides, second 8 are used for the top.
	m_internalVertexCount = 18;
	m_internalIndexCount = 18;

	// Create blank arrays of vertices and indices.
	m_internalVertices = new VertexHeader::VertexType[m_internalVertexCount];
	m_internalIndices = new unsigned long[m_internalIndexCount];

	// base
	m_internalVertices[0].position = D3DXVECTOR3(-0.5, 0, 0.5 );
	m_internalVertices[1].position = D3DXVECTOR3( 0.5, 0, 0.5 );
	m_internalVertices[2].position = D3DXVECTOR3( 0.5, 0, -0.5 );
	m_internalVertices[3].position = D3DXVECTOR3( 0.5, 0, -0.5 );
	m_internalVertices[4].position = D3DXVECTOR3(-0.5, 0, -0.5 );
	m_internalVertices[5].position = D3DXVECTOR3(-0.5, 0, 0.5 );

	//right
	m_internalVertices[6].position = D3DXVECTOR3(0, 1, 0 );
	m_internalVertices[7].position = D3DXVECTOR3( 0.5, 0, 0.5 );
	m_internalVertices[8].position = D3DXVECTOR3( 0.5, 0, -0.5 );

	//front
	m_internalVertices[9].position = D3DXVECTOR3(0, 1, 0 );
	m_internalVertices[10].position = D3DXVECTOR3( 0.5, 0, -0.5 );
	m_internalVertices[11].position = D3DXVECTOR3( -0.5, 0, -0.5 );

	//left
	m_internalVertices[12].position = D3DXVECTOR3(0, 1, 0 );
	m_internalVertices[13].position = D3DXVECTOR3( -0.5, 0, -0.5 );
	m_internalVertices[14].position = D3DXVECTOR3( -0.5, 0, 0.5 );

	//back
	m_internalVertices[15].position = D3DXVECTOR3(0, 1, 0 );
	m_internalVertices[16].position = D3DXVECTOR3( -0.5, 0, 0.5 );
	m_internalVertices[17].position = D3DXVECTOR3( 0.5, 0, 0.5 );

	// Set the texture position for each vertex.					   
	// Bottom			   
	m_internalVertices[0].texture = D3DXVECTOR2(0, 1);
	m_internalVertices[1].texture = D3DXVECTOR2(1, 1);
	m_internalVertices[2].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[3].texture = D3DXVECTOR2(1, 0);
	m_internalVertices[4].texture = D3DXVECTOR2(0, 0);
	m_internalVertices[5].texture = D3DXVECTOR2(0, 1);

	//right
	m_internalVertices[6].texture = D3DXVECTOR2(.5, .5);
	m_internalVertices[7].texture = D3DXVECTOR2( 1, 0);
	m_internalVertices[8].texture = D3DXVECTOR2( 1, 1);

	//front
	m_internalVertices[9].texture = D3DXVECTOR2(.5, .5);
	m_internalVertices[10].texture = D3DXVECTOR2( 1, 1);
	m_internalVertices[11].texture = D3DXVECTOR2( 0, 1);

	//left
	m_internalVertices[12].texture = D3DXVECTOR2(.5, .5);
	m_internalVertices[13].texture = D3DXVECTOR2( 0, 1);
	m_internalVertices[14].texture = D3DXVECTOR2( 0, 0);

	//back
	m_internalVertices[15].texture = D3DXVECTOR2(.5, .5);
	m_internalVertices[16].texture = D3DXVECTOR2( 0, 0);
	m_internalVertices[17].texture = D3DXVECTOR2( 1, 0);

	// Normals

	// Bottom
	m_internalVertices[0].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[1].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[2].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[3].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[4].normal = D3DXVECTOR3(0, -1, 0);
	m_internalVertices[5].normal = D3DXVECTOR3(0, -1, 0);

	//right
	m_internalVertices[6].normal = D3DXVECTOR3(1, 0.5, 0 );
	m_internalVertices[7].normal = D3DXVECTOR3(1, 0.5, 0 );
	m_internalVertices[8].normal = D3DXVECTOR3(1, 0.5, 0 );

	//front
	m_internalVertices[9]. normal = D3DXVECTOR3(0, .5, -1 );
	m_internalVertices[10].normal = D3DXVECTOR3(0, .5, -1 );
	m_internalVertices[11].normal = D3DXVECTOR3(0, .5, -1 );
						   
	//left				   
	m_internalVertices[12].normal = D3DXVECTOR3(-1, 0.5, 0 );
	m_internalVertices[13].normal = D3DXVECTOR3(-1, 0.5, 0 );
	m_internalVertices[14].normal = D3DXVECTOR3(-1, 0.5, 0 );
						   
	//back				   
	m_internalVertices[15].normal = D3DXVECTOR3(0, .5, 1 );
	m_internalVertices[16].normal = D3DXVECTOR3(0, .5, 1 );
	m_internalVertices[17].normal = D3DXVECTOR3(0, .5, 1 );
	
	//CalculateModelVectors();
	// TANGENT

	// Set the indices.
	for(int i = 0; i < m_internalVertexCount; i++){
		CalculateTangentBinormal
			(m_internalVertices[i].normal, 
			m_internalVertices[i].tangent,
			m_internalVertices[i].binormal);
		m_internalIndices[i] = i;
	}	

	Log::COut("Pyramid created around origin (0,0,0)");
}


void MeshClass::SetInternalCuboid(float xLength, float yLength, float zLength){
	SetInternalCube(1.0f);

	for(int i = 0; i < m_internalVertexCount; i++)
	{
		m_internalVertices[i].position.x = m_internalVertices[i].position.x * xLength;
		m_internalVertices[i].position.y = m_internalVertices[i].position.y * yLength;
		m_internalVertices[i].position.z = m_internalVertices[i].position.z * zLength;
	}

	Log::COut("Cuboid created with size (" + 
		std::to_string(xLength) + ", " +
		std::to_string(yLength) + ", " +
		std::to_string(zLength) + ") around origin (0,0,0)");

}

// Sets internal mesh to be a sphere
void MeshClass::SetInternalSphere(int latLines, int longLines){
	m_internalVertexCount = ((latLines - 2) * longLines) + 2;
	int faceCount = ((latLines - 3) * (longLines)*2) + (longLines*2);
	m_internalIndexCount = faceCount*3;

	// Create blank arrays of vertices and indices.
	m_internalVertices = new VertexHeader::VertexType[m_internalVertexCount];
	m_internalIndices = new unsigned long[m_internalIndexCount];

	float yaw = 0.0f;
	float pitch = 0.0f;

	//set the initial vertex

	D3DXVECTOR3 curPos = D3DXVECTOR3(0, 0, 1);

	m_internalVertices[0].position.x = 0;
	m_internalVertices[0].position.y = 0;
	m_internalVertices[0].position.z = 1;

	m_internalVertices[0].texture.x =
				0.5f + 
				((atan2f(m_internalVertices[0].normal.z, 
				m_internalVertices[0].normal.x)) / (D3DX_PI * 2));

			m_internalVertices[0].texture.y =
				0.5 -
				((asin(m_internalVertices[0].normal.y))/(D3DX_PI));


	D3DXMATRIX rotX, rotY, rotZ;

	//loop to set the rest of the vertices

	for(int i = 0; i < latLines - 2; ++i)
	{
		pitch = (i+1) * (D3DX_PI/(latLines-1));
		D3DXMatrixRotationX(&rotX, pitch);

		for(int j = 0; j < longLines; ++j)
		{
			yaw = j * (D3DX_PI * 2/(longLines));
			D3DXMatrixRotationZ(&rotY, yaw);

			//rotates to draw next line

			D3DXVECTOR3 tVect = D3DXVECTOR3(0, 0, 1);
			D3DXMATRIX comRot;
			D3DXMatrixMultiply(&comRot, &rotX, &rotY);
			D3DXVec3TransformNormal(&curPos, &tVect, &comRot);
			D3DXVec3Normalize(&curPos, &curPos);

			m_internalVertices[i*longLines+j+1].position.x = curPos.x;
			m_internalVertices[i*longLines+j+1].position.y = curPos.y;
			m_internalVertices[i*longLines+j+1].position.z = curPos.z;

			m_internalVertices[i*longLines+j+1].normal.x = curPos.x;
			m_internalVertices[i*longLines+j+1].normal.y = curPos.y;
			m_internalVertices[i*longLines+j+1].normal.z = curPos.z;

			m_internalVertices[i*longLines+j+1].texture.x =
				0.5f + 
				((atan2f(m_internalVertices[i*longLines+j+1].normal.z, 
				m_internalVertices[i*longLines+j+1].normal.x)) / (D3DX_PI * 2));

			m_internalVertices[i*longLines+j+1].texture.y =
				0.5 -
				((asin(m_internalVertices[i*longLines+j+1].normal.y))/(D3DX_PI));


		}
	}


	//sets the final vertex

	m_internalVertices[m_internalVertexCount-1].position.x = 0;
	m_internalVertices[m_internalVertexCount-1].position.y = 0;
	m_internalVertices[m_internalVertexCount-1].position.z = -1;

	m_internalVertices[m_internalVertexCount-1].texture.x =
				0.5f + 
				((atan2f(m_internalVertices[m_internalVertexCount-1].normal.z, 
				m_internalVertices[m_internalVertexCount-1].normal.x)) / (D3DX_PI * 2));

			m_internalVertices[m_internalVertexCount-1].texture.y =
				0.5 -
				((asin(m_internalVertices[m_internalVertexCount-1].normal.y))/(D3DX_PI));


	// Indices drawn in groups
	int k = 0;
	for(int l = 0; l < longLines - 1;  ++l)
	{
		m_internalIndices[k] = 0;
		m_internalIndices[k+1] = l+1;
		m_internalIndices[k+2] = l+2;
		k+=3;
	}

	m_internalIndices[k] = 0;
	m_internalIndices[k+1] = longLines;
	m_internalIndices[k+2] = 1;
	k+=3;

	for(int i = 0; i < latLines - 3; ++i)
	{
		for(int j = 0; j < longLines - 1; ++j)
		{
			m_internalIndices[k] = i * longLines + j + 1;
			m_internalIndices[k+1] = i * longLines + j + 2;
			m_internalIndices[k+2] = (i+1) * longLines + j + 1;

			m_internalIndices[k+3] = (i+1) * longLines + j + 1;
			m_internalIndices[k+4] = i * longLines + j + 2;
			m_internalIndices[k+5] = (i+1) * longLines + j + 2;

			k += 6;
		}

		m_internalIndices[k]   = (i*longLines)+longLines;
		m_internalIndices[k+1] = (i*longLines)+1;
		m_internalIndices[k+2] = ((i+1)*longLines)+longLines;

		m_internalIndices[k+3] = ((i+1)*longLines)+longLines;
		m_internalIndices[k+4] = (i*longLines)+1;
		m_internalIndices[k+5] = ((i+1)*longLines)+1;

		k += 6;
	}

	for(int l = 0; l < longLines-1; ++l)
	{
		m_internalIndices[k] = m_internalVertexCount-1;
		m_internalIndices[k+1] = (m_internalVertexCount-1)-(l+1);
		m_internalIndices[k+2] = (m_internalVertexCount-1)-(l+2);
		k += 3;
	}

	m_internalIndices[k] = m_internalVertexCount - 1;
	m_internalIndices[k+1] = (m_internalVertexCount-1)-(longLines);
	m_internalIndices[k+2] = m_internalVertexCount - 2;

	int x;
	for(int i = 0; i < m_internalVertexCount; i++)
	{
		if(m_internalVertices[i].position.x == 0 &&
		   m_internalVertices[i].position.y == 0 &&
		   m_internalVertices[i].position.z == -1)
		{
				x = i;
				break;
		}
	}

	for(int i = 0; i < m_internalIndexCount; i+=3)
	{
		if(m_internalIndices[i] != 0 && m_internalIndices[i] != x)
		{
			m_internalIndices[i] = m_internalIndices[i] ^ m_internalIndices[i+2];
			m_internalIndices[i+2] = m_internalIndices[i] ^ m_internalIndices[i+2];
			m_internalIndices[i] = m_internalIndices[i] ^ m_internalIndices[i+2];
		}
	}
}
#pragma endregion

#pragma region Add Meshes

// Adds the internal vertices and indices from the arrays to the vectors
void MeshClass::AddInternalMesh(){
	// Add the vertices
	for(int i = 0; i < m_internalVertexCount; i++)
	{
		m_vertices.push_back(m_internalVertices[i]);
	}

	// Add the indices
	for(int i = 0; i < m_internalIndexCount; i++)
	{
		m_indices.push_back(m_internalIndices[i] + m_vertexCount);
	}

	// Update the vertex and index counts
	m_vertexCount += m_internalVertexCount;
	m_indexCount += m_internalIndexCount;

	CalculateRadius();
}

void MeshClass::AddInternalTransformedMesh(
	float xRot, float yRot, float zRot, 
	float xScale, float yScale, float zScale, 
	float xOfs, float yOfs, float zOfs){

	// Build the rotation matrix
	D3DXMATRIX t_rotation;
	D3DXMatrixRotationYawPitchRoll(&t_rotation,
		D3DXToRadian(yRot), 
		D3DXToRadian(xRot), 
		D3DXToRadian(zRot));

	// The reason for using the extra matrices here is that I couldn't use *= or += on the points
	// for some reason.
	// Build the scaling matrix
	D3DXMATRIX t_scale;
	D3DXMatrixScaling(&t_scale, xScale, yScale, zScale);

	// Build the translation matrix
	D3DXMATRIX t_translate;
	D3DXMatrixTranslation(&t_translate, xOfs, yOfs, zOfs);

	// Build the trasformation matrix
	D3DXMATRIX t_transform;
	D3DXMatrixMultiply(&t_transform, &t_scale, &t_rotation);
	D3DXMatrixMultiply(&t_transform, &t_transform, &t_translate);

	// Add the vertices
	for(int i = 0; i < m_internalVertexCount; i++)
	{
		m_vertices.push_back(m_internalVertices[i]);

		// Apply rotation to position
		D3DXVec3TransformCoord(&m_vertices.back().position, &m_vertices.back().position, 
			&t_transform);
		// Apply rotation to normals
		D3DXVec3TransformCoord(&m_vertices.back().normal, &m_vertices.back().normal, 
			&t_transform);
	}

	// Add the indices
	for(int i = 0; i < m_internalIndexCount; i++)
	{
		m_indices.push_back(m_internalIndices[i] + m_vertexCount);
	}

	// Update the vertex and index counts
	m_vertexCount += m_internalVertexCount;
	m_indexCount += m_internalIndexCount;

	CalculateRadius();
}

// Add an external mesh to this one
void MeshClass::AddExternalMesh(MeshClass& other){
	// Add the vertices
	for(int i = 0; i < other.GetVertexCount(); i++)
	{
		m_vertices.push_back(other.GetVertices()[i]);
	}

	// Add the indices
	for(int i = 0; i < other.GetIndexCount(); i++)
	{
		m_indices.push_back(other.GetIndices()[i] + m_vertexCount);
	}

	// Update the vertex and index counts
	m_vertexCount += other.GetVertexCount();
	m_indexCount += other.GetIndexCount();

	CalculateRadius();
}

// Add an external mesh to this one with a transformation
void MeshClass::AddExternalTransformedMesh(MeshClass& other, 
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs){

	// Build the rotation matrix
	D3DXMATRIX t_rotation;
	D3DXMatrixRotationYawPitchRoll(&t_rotation,
		D3DXToRadian(yRot), 
		D3DXToRadian(xRot), 
		D3DXToRadian(zRot));

	// The reason for using the extra matrices here is that I couldn't use *= or += on the points
	// for some reason.
	// Build the scaling matrix
	D3DXMATRIX t_scale;
	D3DXMatrixScaling(&t_scale, xScale, yScale, zScale);

	// Build the translation matrix
	D3DXMATRIX t_translate;
	D3DXMatrixTranslation(&t_translate, xOfs, yOfs, zOfs);

	// Build the trasformation matrix
	D3DXMATRIX t_transform;
	D3DXMatrixMultiply(&t_transform, &t_scale, &t_rotation);
	D3DXMatrixMultiply(&t_transform, &t_transform, &t_translate);

	// Add the vertices
	for(int i = 0; i < other.GetVertexCount(); i++)
	{
		m_vertices.push_back(other.GetVertices()[i]);

		// Apply rotation to position
		D3DXVec3TransformCoord(&m_vertices.back().position, &m_vertices.back().position, 
			&t_transform);
		// Apply rotation to normals
		D3DXVec3TransformCoord(&m_vertices.back().normal, &m_vertices.back().normal, 
			&t_transform);
	}

	// Add the indices
	for(int i = 0; i < other.GetIndexCount(); i++)
	{
		m_indices.push_back(other.GetIndices()[i] + m_vertexCount);
	}

	// Update the vertex and index counts
	m_vertexCount += other.GetVertexCount();
	m_indexCount += other.GetIndexCount();

	CalculateRadius();
}

// Adds plane around origin
void MeshClass::AddPlane(){
	SetInternalPlane();
	AddInternalMesh();
}

// Adds cube around origin
void MeshClass::AddCube(float length){
	SetInternalCube(length);
	AddInternalMesh();
}

// Adds cube around origin
void MeshClass::AddPyramid(){
	SetInternalPyramid();
	AddInternalMesh();
}

// Adds cuboid around origin
void MeshClass::AddCuboid(float xLength, float yLength, float zLength){
	SetInternalCuboid(xLength, yLength, zLength);
	AddInternalMesh();
}

// Adds sphere around origin
void MeshClass::AddSphere(int latLines, int longLines){
	SetInternalSphere(latLines, longLines);
	AddInternalMesh();
}
// Add terrain around origin
void MeshClass::AddTerrain(int terrainWidth, int terrainHeight, unsigned char* bitmapImage, float heightFactor){
	SetInternalTerrain(terrainWidth, terrainHeight, bitmapImage, heightFactor);
	AddInternalMesh();
}

void MeshClass::AddWater(int waterSize){
	SetInternalWater(waterSize);
	AddInternalMesh();
}

void MeshClass::AddFoliage(int foliagecount){
	SetInternalFoliage(foliagecount);
	AddInternalMesh();
}

// Adds a mesh from passed in data
void MeshClass::AddCustom(VertexHeader::VertexType* verticesIn, unsigned long* indicesIn, 
		int vertexCountIn, int indexCountIn){

	// Add the vertices
	for(int i = 0; i < vertexCountIn; i++)
	{
		m_vertices.push_back(verticesIn[i]);
	}

	// Add the indices
	for(int i = 0; i  <indexCountIn; i++)
	{
		m_indices.push_back(indicesIn[i] + m_vertexCount);
	}

	// Update the vertex and index counts
	m_vertexCount += vertexCountIn;
	m_indexCount += indexCountIn;
}

// Adds plane with given transformation
void MeshClass::AddPlane(float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs){
	SetInternalPlane();
	AddInternalTransformedMesh(xRot, yRot, zRot, 
		xScale, yScale, zScale, 
		xOfs, yOfs, zOfs);
}

// Adds cube with given transformation
void MeshClass::AddCube(float length,
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs){
	SetInternalCube(length);
	AddInternalTransformedMesh(xRot, yRot, zRot, 
		xScale, yScale, zScale, 
		xOfs, yOfs, zOfs);
}

// Adds cuboid with given transformation
void MeshClass::AddCuboid(float xLength, float yLength, float zLength,
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs){
	SetInternalCuboid(xLength, yLength, zLength);
	AddInternalTransformedMesh(xRot, yRot, zRot, 
		xScale, yScale, zScale, 
		xOfs, yOfs, zOfs);
}

// Adds a mesh from passed in data with a transformation
void MeshClass::AddCustom(VertexHeader::VertexType* verticesIn, unsigned long* indicesIn, 
		int vertexCountIn, int indexCountIn, float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs){

	// Build the rotation matrix
	D3DXMATRIX t_rotation;
	D3DXMatrixRotationYawPitchRoll(&t_rotation,
		D3DXToRadian(yRot), 
		D3DXToRadian(xRot), 
		D3DXToRadian(zRot));

	// The reason for using the extra matrices here is that I couldn't use *= or += on the points
	// for some reason.
	// Build the scaling matrix
	D3DXMATRIX t_scale;
	D3DXMatrixScaling(&t_scale, xScale, yScale, zScale);

	// Build the translation matrix
	D3DXMATRIX t_translate;
	D3DXMatrixTranslation(&t_translate, xOfs, yOfs, zOfs);

	// Build the trasformation matrix
	D3DXMATRIX t_transform;
	D3DXMatrixMultiply(&t_transform, &t_scale, &t_rotation);
	D3DXMatrixMultiply(&t_transform, &t_transform, &t_translate);

	// Add the vertices
	for(int i = 0; i < vertexCountIn; i++)
	{
		m_vertices.push_back(verticesIn[i]);

		// Apply rotation to position
		D3DXVec3TransformCoord(&m_vertices.back().position, &m_vertices.back().position, 
			&t_transform);
		// Apply rotation to normals
		D3DXVec3TransformCoord(&m_vertices.back().normal, &m_vertices.back().normal, 
			&t_transform);
	}

	// Add the indices
	for(int i = 0; i  <indexCountIn; i++)
	{
		m_indices.push_back(indicesIn[i] + m_vertexCount);
	}

	// Update the vertex and index counts
	m_vertexCount += vertexCountIn;
	m_indexCount += indexCountIn;
}

// Adds cube with given transformation
void MeshClass::AddSphere(int latLines, int longLines,
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs){
	SetInternalSphere(latLines, longLines);
	AddInternalTransformedMesh(xRot, yRot, zRot, 
		xScale, yScale, zScale, 
		xOfs, yOfs, zOfs);
}
#pragma endregion

#pragma region Model Import

// Loads a model from file into the internal buffer.
 void MeshClass::SetInternalModel(char* fileName)
 {
	m_importer->Convert(fileName, m_internalVertexCount, m_internalIndexCount);
	m_internalVertices = m_importer->GetVertices();
	m_internalIndices = m_importer->GetIndices();
 }

 // Adds a model from file to (0,0,0)
void MeshClass::AddModel(char* fileName){
	SetInternalModel(fileName);
	AddInternalMesh();
}
	
// Adds a model from file, with a transformation.
void MeshClass::AddModel(char* fileName, 
		float xRot, float yRot, float zRot, 
		float xScale, float yScale, float zScale, 
		float xOfs, float yOfs, float zOfs){

	SetInternalModel(fileName);
	AddInternalTransformedMesh(xRot, yRot, zRot, 
		xScale, yScale, zScale, 
		xOfs, yOfs, zOfs);
}

#pragma endregion

#pragma region Transformation

 // Applies scaling, rotation, and translation to a mesh.
 void MeshClass::TransformMesh(float xRot, float yRot, float zRot,
	 float xScale, float yScale, float zScale,
	 float xOfs, float yOfs, float zOfs){
		 ScaleMesh(xScale, yScale, zScale);
		 RotateMesh(xRot, yRot, zRot);
		 TranslateMesh(xOfs, yOfs, zOfs);
		
		 Log::COut("Transformed mesh successfully.");
 }

 // Translates a mesh by a given offset.
 // Since meshes are created around the origin, this will allow them to appear to "orbit"
 // when the entity using them has a rotate speed.

void MeshClass::TranslateMesh(float xOfs, float yOfs, float zOfs){
	for (vector<VertexHeader::VertexType>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
    {
		i->position.x += xOfs;
		i->position.y += yOfs;
		i->position.z += zOfs;
    }

	Log::COut("Translated mesh by (" + 
		std::to_string(xOfs) + ", " +
		std::to_string(yOfs) + ", " +
		std::to_string(zOfs) + ").");

	CalculateRadius();
}

// Scales a mesh by a given amount.
void MeshClass::ScaleMesh(float xScale, float yScale, float zScale){
	for (vector<VertexHeader::VertexType>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
    {
		i->position.x *= xScale;
		i->position.y *= yScale;
		i->position.z *= zScale;
    }

	Log::COut("Scaled mesh by (" + 
		std::to_string(xScale) + ", " +
		std::to_string(yScale) + ", " +
		std::to_string(zScale) + ").");

	if(xScale == yScale == zScale){
		m_radius *= xScale;
	}else{
		CalculateRadius();
	}
}

// Rotates a mesh by a given amount (in degrees).
void MeshClass::RotateMesh(float xRot, float yRot, float zRot){
	// Create a vector to store the position
	D3DXVECTOR3 t_position(0, 0, 0);
	// Create a rotation matrix for x, y, and z
	D3DXMATRIX t_rotation;
	D3DXMatrixRotationYawPitchRoll(&t_rotation,
		D3DXToRadian(yRot), 
		D3DXToRadian(xRot), 
		D3DXToRadian(zRot));

	// Apply the transform
	for (vector<VertexHeader::VertexType>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
    {
		// Apply rotation to position
		D3DXVec3TransformCoord(&i->position, &i->position, &t_rotation);

		// Apply rotation to the normals
		D3DXVec3TransformCoord(&i->normal, &i->normal, &t_rotation);
    }

	Log::COut("Rotated mesh by " + 
		std::to_string(xRot) + " degrees around the X-axis, " +
		std::to_string(yRot) + " degrees around the Y-axis, and " +
		std::to_string(zRot) + " degrees around the Z-axis.");

	CalculateRadius();
}
#pragma endregion

#pragma region Terrain
bool MeshClass::SetInternalTerrain(int terrainWidth, int terrainHeight, unsigned char* bitmapImage, float heightFactor)
{
	
	unsigned char height;
	int index, index1,  index2,  index3,  index4;
	float tu, tv;
	m_TerrainWidth = terrainWidth;
	m_TerrainHeight = terrainHeight;
	// Create the structure to hold the height map data.
	m_heightMap = new D3DXVECTOR3*[terrainHeight];
	
	for (int i=0; i<terrainHeight; i++)
	{
		m_heightMap[i] = new D3DXVECTOR3[terrainWidth];
	}
	m_texValues = new D3DXVECTOR2[terrainWidth * terrainHeight];
	//UV value calculations
	int repeat = 16;	//Has to be powers of 2 eg 2^3 or 2^456
	int incrementCount, uCount = 0, vCount = 0;
	float incrementValue, u = 0.0f, v = 1.0f;

	// Calculate how much to increment the texture coordinates by.
	incrementValue = (float)repeat / (float)terrainWidth;

	// Calculate how many times to repeat the texture.
	incrementCount = terrainWidth / repeat;

	int k = 0;

	
	

	for (int j=0; j<terrainHeight; j++)
	{
		for (int i=0; i<terrainWidth; i++)
		{
			//Height values
			height = bitmapImage[k];
			index = terrainHeight * j + i;

			m_heightMap[i][j].x = (float)i;
			m_heightMap[i][j].y = (float)height/heightFactor;
			m_heightMap[i][j].z = (float)j;

			k+=3;

			//UV values
			m_texValues[index].x = u;
			m_texValues[index].y = v;

			u += incrementValue;
			uCount++;

			if (uCount == incrementCount)
			{
				u = 0.0f;
				uCount = 0;
			}
		}

		v -= incrementValue;
		vCount++;

		if (vCount == incrementCount)
		{
			v = 1.0f;
			vCount = 0;
		}
	}

	delete[] bitmapImage;
	bitmapImage = 0;

	m_internalVertexCount = (m_TerrainHeight-1) * (m_TerrainWidth-1) * 6;
	m_internalIndexCount = m_internalVertexCount;

	m_internalVertices = new VertexHeader::VertexType[m_internalVertexCount];
	m_internalIndices = new unsigned long[m_internalIndexCount];

	index = 0;
	u = 0;
	v= 0;
	CalculateTerrainNormals();

	for (int j=0; j<m_TerrainHeight-1; j++)
	{
		for (int i=0; i<m_TerrainWidth-1; i++)
		{
			int index1 = (m_TerrainHeight * j) + i;          // Bottom left.
			int index2 = (m_TerrainHeight * j) + (i+1);      // Bottom right.
			int index3 = (m_TerrainHeight * (j+1)) + i;      // Upper left.
			int index4 = (m_TerrainHeight * (j+1)) + (i+1);  // Upper right.

			//Upper Left
			v = m_texValues[index3].y;
			if (v==1.0f) v = 0.0f;

			m_internalVertices[index].position = m_heightMap[i][j+1];
			m_internalVertices[index].texture = D3DXVECTOR2(m_texValues[index3].x, v);
			m_internalVertices[index].normal = normalValues[index3];
			m_internalIndices[index] = index;
			index++;


			// Upper right.
			u = m_texValues[index4].x;
			v = m_texValues[index4].y;

			// Modify the texture coordinates to cover the top and right edge.
			if(u == 0.0f) { u = 1.0f; }
			if(v == 1.0f) { v = 0.0f; }

			m_internalVertices[index].position = m_heightMap[i+1][j+1];
			m_internalVertices[index].texture = D3DXVECTOR2(u, v);
			m_internalVertices[index].normal = normalValues[index4];
			m_internalIndices[index] = index;
			index++;

			// Bottom left.
			m_internalVertices[index].position = m_heightMap[i][j];
			m_internalVertices[index].texture = m_texValues[index1];
			m_internalVertices[index].normal = normalValues[index1];
			m_internalIndices[index] = index;
			index++;

			// Bottom left.
			m_internalVertices[index].position = m_heightMap[i][j];
			m_internalVertices[index].texture = m_texValues[index1];
			m_internalVertices[index].normal = normalValues[index1];
			m_internalIndices[index] = index;
			index++;

			// Upper right.
			u = m_texValues[index4].x;
			v = m_texValues[index4].y;

			// Modify the texture coordinates to cover the top and right edge.
			if(u == 0.0f) { u = 1.0f; }
			if(v == 1.0f) { v = 0.0f; }

			m_internalVertices[index].position = m_heightMap[i+1][j+1];
			m_internalVertices[index].texture = D3DXVECTOR2(u, v);
			m_internalVertices[index].normal = normalValues[index4];
			m_internalIndices[index] = index;
			index++;

			// Bottom right.
			u = m_texValues[index2].x;

			// Modify the texture coordinates to cover the right edge.
			if(u == 0.0f) { u = 1.0f; }

			m_internalVertices[index].position = m_heightMap[i+1][j];
			m_internalVertices[index].texture = D3DXVECTOR2(u, m_texValues[index2].y);
			m_internalVertices[index].normal = normalValues[index2];
			m_internalIndices[index] = index;
			index++;
		}
	}

	return true;
}

void MeshClass::CalculateTerrainNormals()
{
	int i, j, index1, index2, index3, index, count;
	float vertex1[3], vertex2[3], vertex3[3], vector1[3], vector2[3], sum[3], length;

	D3DXVECTOR3* normals = new D3DXVECTOR3[(m_TerrainHeight-1) * (m_TerrainWidth-1)];
	normalValues = new D3DXVECTOR3[m_TerrainHeight*m_TerrainWidth];
	// Go through all the faces in the mesh and calculate their normals.
	for(j=0; j<(m_TerrainHeight-1); j++)
	{
		for(i=0; i<(m_TerrainWidth-1); i++)
		{
			index1 = (j * m_TerrainHeight) + i;
			index2 = (j * m_TerrainHeight) + (i+1);
			index3 = ((j+1) * m_TerrainHeight) + i;

			// Get three vertices from the face.
			vertex1[0] = m_heightMap[i][j].x;
			vertex1[1] = m_heightMap[i][j].y;
			vertex1[2] = m_heightMap[i][j].z;
		
			vertex2[0] = m_heightMap[i+1][j].x;
			vertex2[1] = m_heightMap[i+1][j].y;
			vertex2[2] = m_heightMap[i+1][j].z;
		
			vertex3[0] = m_heightMap[i][j+1].x;
			vertex3[1] = m_heightMap[i][j+1].y;
			vertex3[2] = m_heightMap[i][j+1].z;

			// Calculate the two vectors for this face.
			vector1[0] = vertex1[0] - vertex3[0];
			vector1[1] = vertex1[1] - vertex3[1];
			vector1[2] = vertex1[2] - vertex3[2];
			vector2[0] = vertex3[0] - vertex2[0];
			vector2[1] = vertex3[1] - vertex2[1];
			vector2[2] = vertex3[2] - vertex2[2];

			index = (j * (m_TerrainHeight-1)) + i;

			// Calculate the cross product of those two vectors to get the un-normalized value for this face normal.
			normals[index].x = (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
			normals[index].y = (vector1[2] * vector2[0]) - (vector1[0] * vector2[2]);
			normals[index].z = (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
		}
	}

	// Now go through all the vertices and take an average of each face normal 	
	// that the vertex touches to get the averaged normal for that vertex.
	for(j=0; j<m_TerrainHeight; j++)
	{
		for(i=0; i<m_TerrainWidth; i++)
		{
			// Initialize the sum.
			sum[0] = 0.0f;
			sum[1] = 0.0f;
			sum[2] = 0.0f;

			// Initialize the count.
			count = 0;

			// Bottom left face.
			if(((i-1) >= 0) && ((j-1) >= 0))
			{
				index = ((j-1) * (m_TerrainHeight-1)) + (i-1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Bottom right face.
			if((i < (m_TerrainWidth-1)) && ((j-1) >= 0))
			{
				index = ((j-1) * (m_TerrainHeight-1)) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Upper left face.
			if(((i-1) >= 0) && (j < (m_TerrainHeight-1)))
			{
				index = (j * (m_TerrainHeight-1)) + (i-1);

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}

			// Upper right face.
			if((i < (m_TerrainWidth-1)) && (j < (m_TerrainHeight-1)))
			{
				index = (j * (m_TerrainHeight-1)) + i;

				sum[0] += normals[index].x;
				sum[1] += normals[index].y;
				sum[2] += normals[index].z;
				count++;
			}
			
			// Take the average of the faces touching this vertex.
			sum[0] = (sum[0] / (float)count);
			sum[1] = (sum[1] / (float)count);
			sum[2] = (sum[2] / (float)count);

			// Calculate the length of this normal.
			length = sqrt((sum[0] * sum[0]) + (sum[1] * sum[1]) + (sum[2] * sum[2]));
			
			// Get an index to the vertex location in the height map array.
			index = (j * m_TerrainHeight) + i;

			// Normalize the final shared normal for this vertex and store it in the height map array.
			normalValues[index].x = (sum[0] / length);
			normalValues[index].y = (sum[1] / length);
			normalValues[index].z = (sum[2] / length);

			m_internalVertices[index].normal.x = (sum[0] / length);
			m_internalVertices[index].normal.y = (sum[1] / length);
			m_internalVertices[index].normal.z = (sum[2] / length);
		}
	}

	// Release the temporary normals.
	delete [] normals;
	normals = 0;
}

void MeshClass::ShutdownHeightMap()
{
	if(m_heightMap)
	{
		delete [] m_heightMap;
		m_heightMap = 0;
	}

	return;
}

#pragma engregion
#pragma region foliage
void MeshClass::SetInternalFoliage(int foliagecount)
{
	m_vertexCount = 7;
	m_internalVertices = new VertexHeader::VertexType[m_internalVertexCount];

	m_internalVertices[0].position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // Bottom left.
	m_internalVertices[0].texture = D3DXVECTOR2(0.0f, 1.0f);

	m_internalVertices[1].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top left.
	m_internalVertices[1].texture = D3DXVECTOR2(0.0f, 0.0f);

	m_internalVertices[2].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);  // Bottom right.
	m_internalVertices[2].texture = D3DXVECTOR2(1.0f, 1.0f);

	m_internalVertices[3].position = D3DXVECTOR3(1.0f, 0.0f, 0.0f);  // Bottom right.
	m_internalVertices[3].texture = D3DXVECTOR2(1.0f, 1.0f);

	m_internalVertices[4].position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Top left.
	m_internalVertices[4].texture = D3DXVECTOR2(0.0f, 0.0f);

	m_internalVertices[5].position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);  // Top right.
	m_internalVertices[5].texture = D3DXVECTOR2(1.0f, 0.0f);
}
#pragma endregion

#pragma region Water
void MeshClass::SetInternalWater(int waterSize)
{
	m_internalVertexCount = 6;
	m_internalIndexCount = m_internalVertexCount;

	m_internalVertices = new VertexHeader::VertexType[m_internalVertexCount];
	m_internalIndices = new unsigned long[m_internalIndexCount];

	// Load the vertex array with data.
	m_internalVertices[0].position = D3DXVECTOR3(0.0f, 20.0f, waterSize);  // Top left.
	m_internalVertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	m_internalIndices[0] = 0;

	m_internalVertices[1].position = D3DXVECTOR3(255.0f, 20.0f, waterSize);  // Top right.
    m_internalVertices[1].texture = D3DXVECTOR2(1.0f, 0.0f);
	m_internalIndices[1] = 1;

	m_internalVertices[2].position = D3DXVECTOR3(0.0f, 20.0f, 0.0f);  // Bottom left.
	m_internalVertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);
	m_internalIndices[2] = 2;
	
	m_internalVertices[3].position = D3DXVECTOR3(0.0f, 20.0f, 0.0f);  // Bottom left.
	m_internalVertices[3].texture = D3DXVECTOR2(0.0f, 1.0f);
	m_internalIndices[3] = 3;

    m_internalVertices[4].position = D3DXVECTOR3(waterSize, 20.0f, waterSize);  // Top right.
	m_internalVertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);
	m_internalIndices[4] = 4;

	m_internalVertices[5].position = D3DXVECTOR3(waterSize, 20.0f, 0.0f);  // Bottom right.
	m_internalVertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);
	m_internalIndices[5] = 5;
}

#pragma endregion




void MeshClass::CalculateRadius(){
	float t_radius = 0;
	for (vector<VertexHeader::VertexType>::iterator i = m_vertices.begin(); i != m_vertices.end(); i++)
    {
		t_radius = D3DXVec3Length(&i->position);
		if(t_radius > m_radius) m_radius = t_radius;
    }

}

//Only work for Maya Model because of its format.
// 3 Vertices in a row forms a face.
void MeshClass::CalculateModelVectors(){

	int faceCount, i, index;
	VertexHeader::VertexType vertex1, vertex2, vertex3;
	D3DXVECTOR3 tangent, normal, binormal;

	// Go through all the faces and calculate the the tangent, binormal, and normal vectors.
	for(index=0; index<m_internalIndexCount; index += 3)
	{
		// Get the three vertices for this face from the model.
		vertex1 = m_internalVertices[m_internalIndices[index]];		
		
		vertex2 = m_internalVertices[m_internalIndices[index + 1]];	

		vertex3 = m_internalVertices[m_internalIndices[index + 2]];
		

		// Calculate the tangent and binormal of that face.
		CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, normal);

		if(m_internalVertices[m_internalIndices[index]].normal.x < -1000)
			m_internalVertices[m_internalIndices[index]].normal = normal;

		if(m_internalVertices[m_internalIndices[index]].tangent.x < -1000)
			m_internalVertices[m_internalIndices[index]].tangent = tangent;

		if(m_internalVertices[m_internalIndices[index+ 1]].normal.x < -1000)
			m_internalVertices[m_internalIndices[index + 1]].normal = normal;
		if(m_internalVertices[m_internalIndices[index + 1]].tangent.x < -1000)
			m_internalVertices[m_internalIndices[index + 1]].tangent = tangent;

		if(m_internalVertices[m_internalIndices[index+ 2]].normal.x < -1000)
			m_internalVertices[m_internalIndices[index + 2]].normal = normal;
		if(m_internalVertices[m_internalIndices[index + 2]].tangent.x < -1000)
			m_internalVertices[m_internalIndices[index + 2]].tangent = tangent;

	}
	
	return;
}

void MeshClass::CalculateTangentBinormal(VertexHeader::VertexType vertex1,VertexHeader::VertexType vertex2, VertexHeader::VertexType vertex3,
											D3DXVECTOR3& tangent, D3DXVECTOR3& normal){

	D3DXVECTOR3 sub1, sub2;
	D3DXVec3Subtract(&sub1, &vertex2.position, &vertex1.position);
	D3DXVec3Subtract(&sub2, &vertex3.position, &vertex1.position);

	D3DXVec3Cross(&normal, &sub1, &sub2);
	D3DXVec3Normalize(&normal,&normal);

	D3DXVECTOR3 tan1, tan2;
	D3DXVec3Cross(&tan1, &normal, &D3DXVECTOR3(0,0,1));
	D3DXVec3Cross(&tan2, &normal, &D3DXVECTOR3(0,1,0));

	if( D3DXVec3Length(&tan1) > D3DXVec3Length(&tan2))
		tangent = tan1;
	else
		tangent = tan2;

	D3DXVec3Normalize(&tangent,&tangent);

	return;
}

void MeshClass::CalculateTangentBinormal(D3DXVECTOR3& normal, D3DXVECTOR3& tangent, D3DXVECTOR3& binormal){
	D3DXVECTOR3 tan1, tan2;
	D3DXVec3Cross(&tan1, &normal, &D3DXVECTOR3(0,0,1));
	D3DXVec3Cross(&tan2, &normal, &D3DXVECTOR3(0,1,0));

	if( D3DXVec3Length(&tan1) > D3DXVec3Length(&tan2))
		tangent = tan1;
	else
		tangent = tan2;

	D3DXVec3Normalize(&tangent,&tangent);
	D3DXVec3Cross(&binormal, &normal, &tangent);
	D3DXVec3Normalize(&binormal,&binormal);

	return;
}

void MeshClass::CalculateNormal(D3DXVECTOR3 tangent, D3DXVECTOR3 binormal, D3DXVECTOR3& normal){
	float length;

	// Calculate the cross product of the tangent and binormal which will give the normal vector.
	normal.x = (tangent.y * binormal.z) - (tangent.z * binormal.y);
	normal.y = (tangent.z * binormal.x) - (tangent.x * binormal.z);
	normal.z = (tangent.x * binormal.y) - (tangent.y * binormal.x);

	// Calculate the length of the normal.
	length = sqrt((normal.x * normal.x) + (normal.y * normal.y) + (normal.z * normal.z));

	// Normalize the normal.
	normal.x = normal.x / length;
	normal.y = normal.y / length;
	normal.z = normal.z / length;

	return;
}

void MeshClass::AddSkybox(){
	SetInternalSkybox();
	AddInternalMesh();
}
// Set the mesh to a cube with set size, centred around (0,0,0).
void MeshClass::SetInternalSkybox(){
	float length = 50;
	// Set the vertex and index counts.
	// 8 vertices are required for a cube, but to make texturing work we need
	// an extra 8. The first 8 are used for the sides, second 8 are used for the top.
	m_internalVertexCount = 8;
	m_internalIndexCount = 36;

	// Create blank arrays of vertices and indices.
	m_internalVertices = new VertexHeader::VertexType[m_internalVertexCount];
	m_internalIndices = new unsigned long[m_internalIndexCount];

	// Set the positions of the vertices.
	// Vertices for the sides.
	m_internalVertices[0].position = D3DXVECTOR3(-length/2,  length/2, length/2); // Left, top, front
	m_internalVertices[1].position = D3DXVECTOR3( -length/2,  -length/2, length/2); // Right, top, front
	m_internalVertices[2].position = D3DXVECTOR3(length/2, -length/2, length/2); // Left, bottom, front
	m_internalVertices[3].position = D3DXVECTOR3( length/2, length/2, length/2); // Right, bottom, front
	m_internalVertices[4].position = D3DXVECTOR3(-length/2,  length/2,  -length/2); // Left, top, back
	m_internalVertices[5].position = D3DXVECTOR3( -length/2,  -length/2,  -length/2); // Right, top, back
	m_internalVertices[6].position = D3DXVECTOR3(length/2, -length/2,  -length/2); // Left, bottom, back
	m_internalVertices[7].position = D3DXVECTOR3( length/2, length/2,  -length/2); // Right, bottom, back

	// Set the indices.
	// Front face.
	m_internalIndices[0] = 0;	m_internalIndices[1] = 3;	m_internalIndices[2] = 2;
	m_internalIndices[3] = 2;	m_internalIndices[4] = 1;	m_internalIndices[5] = 0;

	// Top face.
	m_internalIndices[6] = 0;	m_internalIndices[7] = 4;	m_internalIndices[8] = 7;
	m_internalIndices[9] = 7;	m_internalIndices[10] = 3;	m_internalIndices[11] = 0;

	// Back face.
	m_internalIndices[12] = 4;	m_internalIndices[13] = 5;	m_internalIndices[14] = 6;
	m_internalIndices[15] = 6;	m_internalIndices[16] = 7;	m_internalIndices[17] = 4;

	// Left face.
	m_internalIndices[18] = 4;	m_internalIndices[19] = 0;	m_internalIndices[20] = 1;
	m_internalIndices[21] = 1;	m_internalIndices[22] = 5;	m_internalIndices[23] = 4;

	// Right face.
	m_internalIndices[24] = 7;	m_internalIndices[25] = 6;	m_internalIndices[26] = 2;
	m_internalIndices[27] = 2;	m_internalIndices[28] = 3;	m_internalIndices[29] = 7;

	// Bottom face.
	m_internalIndices[30] = 1;	m_internalIndices[31] = 2;	m_internalIndices[32] = 6;
	m_internalIndices[33] = 6;	m_internalIndices[34] = 5;	m_internalIndices[35] = 1;

	Log::COut("Cube created with length " + std::to_string(length) + " around origin (0,0,0)");
}

bool MeshClass::GenerateFoliagePositions(int m_foliageCount)
{
	int i;
	float red, green;

	m_foliageArray = new FoliageType[m_foliageCount];
	if(!m_foliageArray)
	{
		return false;
	}

	//Seed the random generator.
	srand((int)time(NULL));

	//Set random positions and random colors for each piece of foliage
	// Set random positions and random colors for each piece of foliage.
	for(i=0; i<m_foliageCount; i++)
	{
		m_foliageArray[i].x = ((float)rand() / (float)(RAND_MAX)) * 9.0f - 4.5f;
		m_foliageArray[i].z = ((float)rand() / (float)(RAND_MAX)) * 9.0f - 4.5f;

		red = ((float)rand() / (float)(RAND_MAX)) * 1.0f;
		green = ((float)rand() / (float)(RAND_MAX)) * 1.0f;

		m_foliageArray[i].r = red + 1.0f;
		m_foliageArray[i].g = green + 0.5f;
		m_foliageArray[i].b = 0.0f;
	}

	return true;
}