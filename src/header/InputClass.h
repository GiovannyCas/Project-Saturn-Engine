#pragma once

#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_





class InputClass
{

private:
	bool m_keys[256];


public:
	InputClass();
	InputClass(const InputClass& other);
	~InputClass();

	void Initialize();

	void KeyDown(unsigned int input);
	void KeyUp(unsigned int input);

	bool IsKeyDown(unsigned int key);

};

#endif 