#pragma once
#include "MScript.h"
#include "MTransform.h"

namespace maple {

	class CameraScript : public Script {
	public:
		CameraScript();
		~CameraScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};


}

