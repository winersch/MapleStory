#include "MLayer.h"

namespace maple {

	Layer::Layer()
		: mGameObjects{}
	{

	}

	Layer::~Layer() {
		for (auto* gameobj : mGameObjects) {
			if (gameobj == nullptr) {
				continue;
			}

			delete gameobj;
			gameobj = nullptr;
		}
	}

	void Layer::Initialize() {
		for (GameObject* gameobj : mGameObjects) {
			if (gameobj == nullptr) {
				continue;
			}
			gameobj->Initialize();
		}

	}

	void Layer::Update() {
		for (GameObject* gameobj : mGameObjects) {
			if (gameobj == nullptr) {
				continue;
			}
			GameObject::eState state = gameobj->GetState();
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) {
				continue;
			}

			gameobj->Update();
		}

	}

	void Layer::LateUpdate() {
		for (GameObject* gameobj : mGameObjects) {
			if (gameobj == nullptr) {
				continue;
			}
			GameObject::eState state = gameobj->GetState();
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) {
				continue;
			}

			gameobj->LateUpdate();
		}
	}

	void Layer::Render() {
		for (GameObject* gameobj : mGameObjects) {
			if (gameobj == nullptr) {
				continue;
			}
			GameObject::eState state = gameobj->GetState();
			if (state == GameObject::eState::Paused || state == GameObject::eState::Dead) {
				continue;
			}

			gameobj->Render();
		}
	}

	void Layer::Destroy() {

		std::vector<GameObject*> deleteObjects = {};
		findDeadGameObjects(deleteObjects);
		eraseDeadGameObject();
		deleteGameObjects(deleteObjects);
	}

	void Layer::AddGameObject(GameObject* gameobject) {
		if (gameobject == nullptr) {
			return;
		}
		mGameObjects.push_back(gameobject);
	}
	void Layer::EraseGameObject(GameObject* eraseGameObj) {
		// std::erase() iter넣어줘서 해당 이터레이와 같은 객체 삭제
		std::erase_if(mGameObjects,
			[=](GameObject* gameObj) {
				return gameObj == eraseGameObj;
			});
	}

	void Layer::findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs) {
		for (GameObject* gameObj : mGameObjects) {
			GameObject::eState active = gameObj->GetState();
			if (active == GameObject::eState::Dead)
				gameObjs.push_back(gameObj);
		}
	}

	void Layer::deleteGameObjects(std::vector<GameObject*> deleteObjs) {
		for (GameObject* obj : deleteObjs) {
			delete obj;
			obj = nullptr;
		}
	}

	void Layer::eraseDeadGameObject() {
		std::erase_if(mGameObjects,
			[](GameObject* gameObj) {
				return (gameObj)->IsDead();
			});
	}

}