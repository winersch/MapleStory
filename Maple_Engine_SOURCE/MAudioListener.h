#pragma once
#include "MComponent.h"

namespace maple {

	class AudioListener : public Component{

	public:
		AudioListener();
		~AudioListener();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	};

}

