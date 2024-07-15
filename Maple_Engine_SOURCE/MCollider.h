#pragma once
#include "MComponent.h"

namespace maple {


	class Collider : public Component{

	public:
		Collider(eColliderType type);
		~Collider();

		void Initialize();
		void Update();
		void LateUpdate();
		void Render();

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		Vector2 GetOffset() const { return mOffset; }
		UINT32 GetID() const { return mID; }
		Vector2 GetSize() const { return mSize; }
		eColliderType GetColliderType() const { return mType; }
		void SetOffset(Vector2 offset) { mOffset = offset; }
		void SetSize(Vector2 size) { mSize = size; }

	private:
		static UINT CollisionID;

		UINT32 mID;
		Vector2 mOffset;
		Vector2 mSize;
		eColliderType mType;

	};

}


