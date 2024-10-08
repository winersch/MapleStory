#include "MTexture.h"
#include "MApplication.h"
#include "MResources.h"

// 해당 전역변수가 존재함을 알리는 키워드
extern maple::Application application;

namespace maple::graphics {

	Texture::Texture()
		: Resource(enums::eResourceType::Texture)
		, mDesc{}
		
	{

	}

	Texture::~Texture() {
	}

	HRESULT Texture::Save(const std::wstring& path) {
		return E_NOTIMPL;
	}

	HRESULT Texture::Load(const std::wstring& path) {
		std::wstring ext
			= path.substr(path.find_last_of(L".") + 1);
		if (ext == L".dds" || ext == L".DDS") {
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (ext == L".tga" || ext == L".TGA") {
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		HRESULT hr = CreateShaderResourceView
		(
			graphics::GetDevice()->GetID3D11Device().Get()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mSRV.GetAddressOf()
		);

		auto metadata = mImage.GetMetadata();
		if (metadata.format == DXGI_FORMAT_R8G8B8A8_UNORM || metadata.format == DXGI_FORMAT_B8G8R8A8_UNORM) {
			metadata.format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // 또는 DXGI_FORMAT_B8G8R8A8_UNORM_SRGB
		}

		if (hr == S_FALSE)
			assert(false/*"Textrue load fail!!"*/);

		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());


		return S_OK;
	}

	void Texture::Bind(eShaderStage stage, UINT startSlot) {
		graphics::GetDevice()->SetShaderResource(stage, startSlot, mSRV.GetAddressOf());
	}

}