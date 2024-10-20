#pragma once
#include "MComponent.h"
#include "MGameObject.h"

namespace maple {

	class BackGroundObject : public GameObject{

	public:
		BackGroundObject();
		~BackGroundObject();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetRatio(float x, float y) { rx = x; ry = y; }
		void SetOriginPos(Vector3 pos) { mOriginPos = pos; }


	private:
		float rx;
		float ry;
		Vector3 mOriginPos;

	};


}

