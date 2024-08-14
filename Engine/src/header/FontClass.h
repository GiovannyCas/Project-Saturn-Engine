#pragma once
#ifndef _FONTCLASS_H_
#define _FONTCLASS_H_


#include <directxmath.h>
#include <fstream>

#include "textureclass.h"

class FontClass
{

private:

    struct FontType
    {
        float left, right;
        int size;
    };

    struct VertexType
    {
        DirectX::XMFLOAT3 position;
        DirectX::XMFLOAT2 texture;
    };

    FontType* m_Font;
    TextureClass* m_Texture;
    float m_fontHeight;
    int m_spaceSize;

    bool LoadFontData(char*);
    void ReleaseFontData();
    bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
    void ReleaseTexture();

public:
    FontClass();
    FontClass(const FontClass&);
    ~FontClass();

    bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int);
    void Shutdown();

    ID3D11ShaderResourceView* GetTexture();

    void BuildVertexArray(void*, char*, float, float);
    int GetSentencePixelLength(char*);
    int GetFontHeight();

};

#endif _FONTCLASS_H_

