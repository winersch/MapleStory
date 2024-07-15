#include "MCollisionManager.h"
#include "MScene.h"
#include "MSceneManager.h"
#include "MGameObject.h"
#include "MCollider.h"
#include "MTransform.h"

namespace maple {
	std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
	std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize() {
		int a = 1;
		int b = a << 1;

	}

	void CollisionManager::Update() {
		Scene* scene = SceneManager::GetActiveScene();
		for (UINT row = 0; row < (UINT)eLayerType::Max; row++) {
			for (UINT col = 0; col < (UINT)eLayerType::Max; col++) {
				if (mCollisionLayerMatrix[row][col] == true) {
					LayerCollision((eLayerType)row, (eLayerType)col);
				}
			}
		}

	}

	void CollisionManager::LateUpdate() {
	}

	void CollisionManager::Render() {
	}

	void CollisionManager::Clear() {
		mCollisionMap.clear();
		mCollisionLayerMatrix->reset();
	}

	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable) {
		int row = 0;
		int col = 0;

		if (left <= right) {
			row = (UINT)left;
			col = (UINT)right;
		} else {
			row = (UINT)right;
			col = (UINT)left;
		}

		mCollisionLayerMatrix[row][col] = enable;

	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right) {
		const std::vector<GameObject*>& leftObjs = SceneManager::GetGameObjects(left);//scene->GetLayer(left)->GetGameObjects();
		const std::vector<GameObject*>& rightObjs = SceneManager::GetGameObjects(right); // scene->GetLayer(right)->GetGameObjects();

		for (GameObject* leftObj : leftObjs) {
			if (leftObj->IsActive() == false)
				continue;
			Collider* leftCol = leftObj->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;

			for (GameObject* rightObj : rightObjs) {
				if (rightObj->IsActive() == false)
					continue;
				Collider* rightCol = rightObj->GetComponent<Collider>();
				if (rightCol == nullptr)
					continue;
				if (leftObj == rightObj)
					continue;

				ColliderCollision(leftCol, rightCol);
			}

		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right) {
		// 두 충돌체 번호로 가져온 ID 확인하여 CollisionID 세팅
		CollisionID id = {};
		id.left = left->GetID();
		id.right = right->GetID();

		// 이전 충돌 정보를 검색한다.
		// 만약에 충돌정보가 없는 상태라면
		// 충돌정보를 생성해준다.

		auto iter = mCollisionMap.find(id.id);
		if (iter == mCollisionMap.end()) {
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		// 충돌 체크를 해준다
		if (Intersect(left, right)) {
			//최초 충돌할??
			if (iter->second == false) {
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);
				iter->second = true;
			} else // 이미 충돌 중
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		} else {
			//충돌을 하지 않은 상태
			if (iter->second == true) {
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}

	}
	bool CollisionManager::Intersect(Collider* left, Collider* right) {
		Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
		Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

		Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
		Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

		// size 1,1 일떄 기본크기가 100픽셀
		Vector2 leftSize = left->GetSize() * 100.0f;
		Vector2 rightSize = right->GetSize() * 100.0f;

		//AABB 충돌
		enums::eColliderType leftType = left->GetColliderType();
		enums::eColliderType rightType = right->GetColliderType();

		if (leftType == enums::eColliderType::Rect2D
			&& rightType == enums::eColliderType::Rect2D) {
			if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
				&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f)) {
				return true;
			}
		}


		if (leftType == enums::eColliderType::Circle2D
			&& rightType == enums::eColliderType::Circle2D) {
			//circle -circle
			Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
			Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);
			float distance = (leftCirclePos - rightCirclePos).Length();
			if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f)) {
				return true;
			}
		}

		if ((leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Rect2D)
			|| (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Circle2D)) {
			// 좌표와 크기 값을 각각 설정
			Vector2 circlePos, rectPos, circleSize, rectSize;

			if (leftType == enums::eColliderType::Circle2D) {
				circlePos = leftPos;
				circleSize = leftSize;
				rectPos = rightPos;
				rectSize = rightSize;
			}
			else {
				circlePos = rightPos;
				circleSize = rightSize;
				rectPos = leftPos;
				rectSize = leftSize;
			}

			// 원의 속성
			Vector2 circleCenter = circlePos + (circleSize / 2.0f);
			float circleRadius = circleSize.x / 2.0f;

			// 사각형의 속성
			Vector2 rectCenter = rectPos;
			Vector2 rectHalfSize = rectSize / 2.0f;

			// 원의 중심에서 사각형의 중심까지의 거리 계산
			float deltaX = circleCenter.x - max(rectCenter.x - rectHalfSize.x, min(circleCenter.x, rectCenter.x + rectHalfSize.x));
			float deltaY = circleCenter.y - max(rectCenter.y - rectHalfSize.y, min(circleCenter.y, rectCenter.y + rectHalfSize.y));

			// 거리가 원의 반지름보다 작거나 같으면 충돌 발생
			if ((deltaX * deltaX + deltaY * deltaY) <= (circleRadius * circleRadius)) {
				return true;
			}

		}


		return false;
	}



}