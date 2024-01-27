#include "../src/header/ModelClass.h"


ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	m_Texture = 0;
}

ModelClass::ModelClass(const ModelClass& other)
{

}

ModelClass::~ModelClass()
{

}

bool ModelClass::Initialize(ID3D11Device* device)
{
	bool result;

	//Initialize the vertex and index buffers.
	result = InitializeBuffers(device);

	if (!result)
	{
		return false;
	}

	return true;

}

bool ModelClass::InitializeWithTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename) 
{
	bool result;

	//Initialize the vertex and index buffers.
	result = InitializeBuffers(device);

	if (!result)
	{
		return false;
	}

	//Load the texture for this model.
	result = LoadTexture(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}


	return true;
}

void ModelClass::Shutdown()
{

	//release the model texture.
	ReleaseTexure();

	//Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	//Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}

int ModelClass::GetIndexCount()
{
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device)
{
	
	VertexTextureType* vertices;
	
	unsigned long* indices;
	D3D11_BUFFER_DESC verteBufferDesc;
	D3D11_BUFFER_DESC indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData;
	D3D11_SUBRESOURCE_DATA indexData;
	HRESULT result;

	//Set the numbers of vertices in the vertex array.
	m_vertexCount = 3;

	//Set the numbers of indices in the index array.
	m_indexCount = 3;

	//Create the vertex array.
	vertices = new VertexTextureType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	//Create the index array.
	indices = new unsigned long[m_indexCount];

	if (!indices)
	{
		return false;
	}

	//////Trinagle//////

	// Load the vertex array with data.
	////Color type
	//	vertices[0].position = DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
	//	vertices[0].color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	//	vertices[1].position = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
	//	vertices[1].color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

	//	vertices[2].position = DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
	//	vertices[2].color = DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	
	//Texture type
		vertices[0].position = DirectX::XMFLOAT3(-1.0f, -1.0f, 0.0f);  // Bottom left.
		vertices[0].texture = DirectX::XMFLOAT2(0.0f, 1.0f);

		vertices[1].position = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);  // Top middle.
		vertices[1].texture = DirectX::XMFLOAT2(0.5f, 0.0f);

		vertices[2].position = DirectX::XMFLOAT3(1.0f, -1.0f, 0.0f);  // Bottom right.
		vertices[2].texture = DirectX::XMFLOAT2(1.0f, 1.0f);

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.


	//Set up the description of the static vertex buffers.
	verteBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	verteBufferDesc.ByteWidth = sizeof(VertexTextureType) * m_vertexCount;
	verteBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	verteBufferDesc.CPUAccessFlags = 0;
	verteBufferDesc.MiscFlags = 0;
	verteBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	//Now create the vertex buffer.
	result = device->CreateBuffer(&verteBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}


	//Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	//Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	//Createthe index Buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//Release the arrrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;

}

void ModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	//Set vertex buffer stride and offset.
	stride = sizeof(VertexTextureType);
	offset = 0;

	//Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool ModelClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;


	//Create and Initialize the texture object.
	m_Texture = new TextureClass;
	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;

}

void ModelClass::ReleaseTexure()
{
	//Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

