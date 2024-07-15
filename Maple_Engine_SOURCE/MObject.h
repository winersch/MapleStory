#pragma once
#include "MLayer.h"
#include "MGameObject.h"
#include "MScene.h"
#include "MSceneManager.h"
#include "MComponent.h"
#include "MTransform.h"

namespace maple::object {

	template <typename T>
	static T* Instantiate(enums::eLayerType type) {
		T* gameObject = new T();
		gameObject->SetLayerType(type);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		return gameObject;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, math::Vector2 position) {
		T* gameObject = new T();
		gameObject->SetLayerType(type);
		Scene* activeScene = SceneManager::GetActiveScene();
		Layer* layer = activeScene->GetLayer(type);
		layer->AddGameObject(gameObject);

		Transform* tr = gameObject->GetComponent<Transform>();
		tr->SetPosition(position);

		return gameObject;
	}
	
	static void DontDestroyOnLoad(GameObject* gameObject) {
		Scene* activeScene = SceneManager::GetActiveScene();
		// 현재씬에서 게임오브젝트를 지워준다.
		activeScene->EraseGameObject(gameObject);

		// 해당 게임오브젝트를 -> DontDestroy씬으로 넣어준다.
		Scene* dontDestroyOnLoad = SceneManager::GetDontDestroyOnLoad();
		dontDestroyOnLoad->AddGameObject(gameObject, gameObject->GetLayerType());

	}
	//static void Destroy(GameObject* obj) {
	//	obj->death();
	//}

}