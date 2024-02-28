#pragma once

#ifndef  _TEXTCLASS_H_
#define _TEXTCLASS_H_

#include "fontclass.h"




class TextClass
{
private:

	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};

	ID3D11Buffer* m_vertexBuffer;
	ID3D11Buffer* m_indexBuffer;
	int m_screenWidth, m_screenHeight, m_maxLength, m_vertexCount, m_indexCount;
	DirectX::XMFLOAT4 m_pixelColor;

	bool InitializeBuffers(ID3D11Device*, ID3D11DeviceContext*, FontClass*, char*, int, int, float, float, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

public:

	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, int, FontClass*, char*, int, int, float, float, float);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();

	bool UpdateText(ID3D11DeviceContext*, FontClass*, char*, int, int, float, float, float);
	DirectX::XMFLOAT4 GetPixelColor();
};


#endif 