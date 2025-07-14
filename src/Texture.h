#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>

class Texture
{
public:
	Texture() {};
	~Texture();

	void LoadFile(const char* file);
	void Set();

private:
	ID3D11Texture2D* texture = nullptr;
	ID3D11ShaderResourceView* textureView = nullptr;
	ID3D11SamplerState* samplerState = nullptr;
};

class MultiTexture
{
public:
	MultiTexture() {};
	~MultiTexture();

	void LoadFile(const char* f1, const char* f2);
	void Set();

private:
	ID3D11Texture2D* texture1 = nullptr;
	ID3D11ShaderResourceView* textureView1 = nullptr;

	ID3D11Texture2D* texture2 = nullptr;
	ID3D11ShaderResourceView* textureView2 = nullptr;

	ID3D11SamplerState* samplerState = nullptr;
};

#endif // !TEXTURE_H
