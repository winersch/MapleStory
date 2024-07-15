#pragma once
#include "CommonInclude.h"
#include "MBoxCollider2D.h"
#include "MCircleCollider2D.h"

namespace maple {

	union CollisionID {
		struct {
			UINT32 left;
			UINT32 right;
		};

		UINT64 id;
	};

	using namespace enums;
	class CollisionManager {
	public:
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);
		static void Clear();

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
		static void ColliderCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);

	private:
		static std::bitset<(UINT)eLayerType::Max> mCollisionLayerMatrix[(UINT)eLayerType::Max];
		static std::unordered_map<UINT64, bool> mCollisionMap;
	};


}


