#pragma once
#include "MGameObject.h"

namespace maple {

	class SceneObject : public GameObject{

	public:
		SceneObject();
		~SceneObject();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:	


	};

}

