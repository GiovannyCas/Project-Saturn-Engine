#pragma once

#include <d3d11.h>
#include <directxmath.h>
#include <fstream>


class SkyDomeClass
{
private:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VertexType
	{
		DirectX::XMFLOAT3 position;
	};
	
	ModelType* m_model;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
	DirectX::XMFLOAT4 m_apexColor, m_centerColor;

	bool LoadSkyDomeModel(char*);
	void ReleaseSkyDomeModel();

	bool InitializeBuffers(ID3D11Device*);
	void ReleaseBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	

public:
	SkyDomeClass();

	~SkyDomeClass() = default;

	bool Initialize(ID3D11Device*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	DirectX::XMFLOAT4 GetApexColor();
	DirectX::XMFLOAT4 GetCenterColor();

};
