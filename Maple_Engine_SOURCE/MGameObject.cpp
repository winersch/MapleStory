#pragma once 
#include "MGameObject.h"
#include "CommonInclude.h"
#include "MInput.h"
#include "MTime.h"
#include "MTransform.h"

namespace maple {
	
	
	GameObject::GameObject()
		:mState(eState::Active)
		,mLayerType(eLayerType::None)
	{

		mComponents.resize((UINT)enums::eComponentType::End);

		initializeTransform();

	}

	GameObject::~GameObject() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				continue;
			}
			delete comp;
			comp = nullptr;
		}
	}

	
	void GameObject::Initialize() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				continue;
			}
			comp->Initialize();
		}
	}

	void GameObject::Update() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				continue;
			}
			comp->Update();
		}
	}
	
	void GameObject::LateUpdate() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				continue;
			}
			comp->LateUpdate();
		}
	}
	void GameObject::Render() {
		for (Component* comp : mComponents) {
			if (comp == nullptr) {
				continue;
			}
			comp->Render();
		}
	}
	void GameObject::initializeTransform() {
		AddComponent<Transform>();
	}

	void GameObject::DeleteScript() {
		delete mComponents[(UINT)enums::eComponentType::Script];
		mComponents[(UINT)enums::eComponentType::Script] = nullptr;
	}
}

