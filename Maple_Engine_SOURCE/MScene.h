#pragma once
#include "MEntity.h"
#include "MGameObject.h"
#include "MLayer.h"

namespace maple {


	class Scene : public Entity {
		
	public:
		Scene();
		~Scene();
		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();
		virtual void Destroy();

		virtual void OnEnter();
		virtual void OnExit();

		
		void AddGameObject(GameObject* gameObject, const enums::eLayerType type);
		void EraseGameObject(GameObject* gameObj);
		Layer* GetLayer(const enums::eLayerType type) { return mLayers[(UINT)type]; }
		

	private:
		void createLayers();

	private:
		std::vector<Layer*> mLayers;

	};

}


