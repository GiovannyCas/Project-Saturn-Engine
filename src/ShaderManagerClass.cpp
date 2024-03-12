#include "../src/header/ShaderManagerClass.h"



ShaderManagerClass::ShaderManagerClass()
{
    m_TextureShader = 0;
    m_LightShader = 0;
    m_NormalMapShader = 0;
}


ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}


ShaderManagerClass::~ShaderManagerClass()
{
}


bool ShaderManagerClass::Initialize(ID3D11Device* device, HWND hwnd)
{
    bool result;

    // Create and initialize the texture shader object.
     m_TextureShader = new TextureShaderClass;

    result = m_TextureShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the light shader object.
    m_LightShader = new LightShaderClass;

    result = m_LightShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }

    // Create and initialize the normal map shader object.
    m_NormalMapShader = new NormalMapShaderClass;

    result = m_NormalMapShader->Initialize(device, hwnd);
    if (!result)
    {
        return false;
    }
   
    return true;

}

void ShaderManagerClass::Shutdown()
{
   

    // Release the light shader object.
    if (m_LightShader)
    {
        m_LightShader->Shutdown();
        delete m_LightShader;
        m_LightShader = 0;
    }

    // Release the texture shader object.
    if (m_TextureShader)
    {
        m_TextureShader->Shutdown();
        delete m_TextureShader;
        m_TextureShader = 0;
    }

    if (m_NormalMapShader)
    {
        m_NormalMapShader->Shutdown();
        delete m_NormalMapShader ;
        m_NormalMapShader = 0;
    }

    return;
}

bool ShaderManagerClass::RenderTextureShader(ID3D11DeviceContext* deviceContext, int indexCount, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture)
{
    bool result;


    result = m_TextureShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
    if (!result)
    {
        return false;
    }

    return true;
}



bool ShaderManagerClass::RenderLightShader(ID3D11DeviceContext* deviceContext, int indexCount, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture, DirectX::XMFLOAT3 lightDirection, DirectX::XMFLOAT4 ambientColor, DirectX::XMFLOAT4 diffuseColor)
{
    bool result;


    result = m_LightShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, 
        projectionMatrix, texture, lightDirection, ambientColor, diffuseColor);
    if (!result)
    {
        return false;
    }

    return true;
}

bool ShaderManagerClass::RenderNormalMapShader(ID3D11DeviceContext* deviceContext, int indexCount, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* colorTexture, ID3D11ShaderResourceView* normalTexture, DirectX::XMFLOAT3 lightDirection, DirectX::XMFLOAT4 diffuseColor)
{
    bool result;


    result = m_NormalMapShader->Render(deviceContext, indexCount, worldMatrix, viewMatrix, projectionMatrix, colorTexture, normalTexture, lightDirection, diffuseColor);
    if (!result)
    {
        return false;
    }

    return true;
}
