#pragma once
#include "MUIBase.h"
#include "MTexture.h"
#include "MGameObject.h"
#include "CommonInclude.h"

namespace maple {

	class UIHUD : public UIBase{
	public:
		UIHUD();
		~UIHUD();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender() override;
		virtual void OnClear() override;

	private:
		graphics::Texture* mTexture;
		std::vector<GameObject*> mUIs;

	};


}

