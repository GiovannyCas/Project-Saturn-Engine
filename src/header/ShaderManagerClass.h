#pragma once
#ifndef _SHADERMANAGERCLASS_H_
#define _SHADERMANAGERCLASS_H_


#include "textureshaderclass.h"
#include "lightshaderclass.h"
#include "NormalMapShaderClass.h"




class ShaderManagerClass
{

private:
    TextureShaderClass* m_TextureShader;
    LightShaderClass* m_LightShader;
    NormalMapShaderClass* m_NormalMapShader;
   

public:
    ShaderManagerClass();
    ShaderManagerClass(const ShaderManagerClass&);
    ~ShaderManagerClass();

    bool Initialize(ID3D11Device*, HWND);
    void Shutdown();

    bool RenderTextureShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*);
    bool RenderLightShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*, DirectX::XMFLOAT3, DirectX::XMFLOAT4, DirectX::XMFLOAT4);
    bool RenderNormalMapShader(ID3D11DeviceContext*, int, DirectX::XMMATRIX, DirectX::XMMATRIX, DirectX::XMMATRIX, ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, DirectX::XMFLOAT3, DirectX::XMFLOAT4);
};
#endif
