#include "MAudioListener.h"
#include "MTransform.h"
#include "MFmod.h"
#include "MGameObject.h"


namespace maple {


	AudioListener::AudioListener()
		: Component(eComponentType::AudioListener) {
	}

	AudioListener::~AudioListener() {
	}

	void AudioListener::Initialize() {
	}

	void AudioListener::Update() {
	}

	void AudioListener::LateUpdate() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		Fmod::Set3DListenerAttributes(&pos);
	}

	void AudioListener::Render(HDC hdc) {
	}


}
