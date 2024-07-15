#pragma once
#include "MEntity.h"
#include "MComponent.h"

namespace maple {

	using namespace math;

	class Transform : public Component {

	public:
		Transform();
		~Transform();

		void Initialize() override;
		void Update()  override;
		void LateUpdate()  override;
		void Render(HDC hdc)  override;

		void SetPosition(Vector2 pos) { mPosition.x = pos.x; mPosition.y = pos.y; }
		Vector2 GetPosition() { return mPosition; }
		float GetRotation() { return mRotation; }
		Vector2 GetScale() { return mScale; }
		void SetRotation(float rotation) { mRotation = rotation; }
		void SetScale(Vector2 scale) { mScale = scale; }

	private:
		Vector2 mPosition;
		Vector2 mScale;
		float mRotation;

	};

}

