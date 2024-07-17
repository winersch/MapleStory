#pragma once
#include "MResource.h"
#include "MTexture.h"
#include "MShader.h"



namespace maple
{
	class Material : public Resource {
	public:

		struct Data //Texture names
		{
			std::wstring albedo; //diffuse
		};

		Material();
		virtual ~Material();

		virtual HRESULT Save(const std::wstring& path) override;
		virtual HRESULT Load(const std::wstring& path) override;

		void Bind();
		void BindShader();
		void BindTextures();

		void SetShader(graphics::Shader* shader) { mShader = shader; }
		void SetAlbedoTexture(graphics::Texture* texture) { mAlbedoTexture = texture; mData.albedo = texture->GetName(); }

	private:
		graphics::eRenderingMode mMode;
		Material::Data mData;

		//Texture* mTexture;
		graphics::Texture* mAlbedoTexture;
		graphics::Shader* mShader;
	};
}

