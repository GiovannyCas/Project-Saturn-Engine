#pragma once

#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


#include <d3d11.h>
#include <DirectXMath.h>


#include "TextureClass.h"



class ModelClass
{
private:

	struct VertexColorType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT4 color;
		

	};

	struct VertexTextureType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;

	};

	int m_vertexCount, m_indexCount;
	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;

	TextureClass* m_Texture;

	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexure();

public:

	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D11Device*);
	bool InitializeWithTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	ID3D11ShaderResourceView* GetTexture();

};

#endif 