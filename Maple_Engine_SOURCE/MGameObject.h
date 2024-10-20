#pragma once
#include "CommonInclude.h"
#include "MComponent.h"
#include "MScript.h"
#include "MCollider.h"

namespace maple {


	class GameObject : public Entity{
	public:
		enum class eState {
			Active,
			Paused,
			Dead,
			End,
		};

		GameObject();
		~GameObject();


		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		template <typename T>
		T* AddComponent() {
			T* component = GetComponent<T>();
			if (component != nullptr) {
				return component;
			}
			T* comp = new T();
			comp->SetOwner(this);
			comp->Initialize();

			mComponents[(UINT)comp->GetType()] = comp;

			return comp;
		}
		template <typename T>
		T* AddComponent(T* component) {
			mComponents[(UINT)component->GetType()] = component;
			return component;
		}

		template <typename T>
		T* GetComponent() {
			T* component = nullptr;
			for (Component* comp : mComponents) {
				component = dynamic_cast<T*>(comp);
				if (component) {
					break;
				}
			}
			return component;
		}
		eState GetState() const { return mState; }
		void SetActive(bool power) {
			if (power == true) mState = eState::Active;
			if (power == false) mState = eState::Paused;
		}
		void SetDead() { death(); }
		bool IsActive() const { return mState == eState::Active; }
		bool IsDead() const { return mState == eState::Dead; }
		void SetLayerType(eLayerType layerType) { mLayerType = layerType; }
		eLayerType GetLayerType() const { return mLayerType; }
		void DeleteScript();

	private:
		void initializeTransform();
		void death() { mState = eState::Dead; }

	private:
		eState mState;
		std::vector<Component*> mComponents;
		eLayerType mLayerType;
	};

}

