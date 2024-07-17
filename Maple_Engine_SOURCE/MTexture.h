#pragma once
#include <DirectXTex.h>
#include <DirectXTex.inl>
//#include <DirectxTexEXR.h>

#include "MResource.h"
#include "MGraphicDevice_DX11.h"

namespace maple::graphics {

	class Texture : public Resource{

	public:
		Texture();
		~Texture();

		virtual HRESULT Save(const std::wstring& path) override;
		virtual HRESULT Load(const std::wstring& path) override;

		void Bind(eShaderStage stage, UINT startSlot);

	private:
		ScratchImage mImage;

		D3D11_TEXTURE2D_DESC mDesc;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;

	};


}


