#pragma once
#include "CommonInclude.h"
#include "MGameObject.h"
#include "MObject.h"

namespace maple {

	class SkillObjectPool {


	public:

		SkillObjectPool(int size) : mMaxSkillObjectCount(size) {
			mSkillObjects.reserve(size);
			for (int i = 0; i < size; i++) {
				GameObject* object = object::Instantiate<GameObject>(enums::eLayerType::Effect);
				object->SetActive(false);
				mSkillObjects.push_back(object);
			}
		}
		
		~SkillObjectPool() {
			//for (GameObject* object : mSkillObjects) {
			//	if (object == nullptr) {
			//		continue;
			//	}
			//	delete object;
			//	object = nullptr;
			//}
		}

		GameObject* GetObject() {
			for (auto& obj : mSkillObjects) {
				if (!obj->IsActive()) {
					obj->SetActive(true);
					return obj;
				}
			}
			return nullptr;  // 풀에 사용 가능한 오브젝트가 없으면 nullptr 반환
		}


	private:
		std::vector<GameObject*> mSkillObjects;
		int mMaxSkillObjectCount;

	};

}


