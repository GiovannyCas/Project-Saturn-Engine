#pragma once

#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_

#include <DirectXMath.h>






class LightClass
{

private:
    DirectX::XMFLOAT4 m_ambientColor;
	DirectX::XMFLOAT4 m_diffuseColor;
	DirectX::XMFLOAT3 m_direction;

public:

    LightClass();
    LightClass(const LightClass&);
    ~LightClass();

    void SetAmbientColor(float, float, float, float);
    void SetDiffuseColor(float, float, float, float);
    void SetDirection(float, float, float);

    DirectX::XMFLOAT4 GetDiffuseColor();
    DirectX::XMFLOAT3 GetDirection();
    DirectX::XMFLOAT4 GetAmbientColor();

};

#endif 