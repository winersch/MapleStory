#include "MFlashJump.h"

namespace maple {

	FlashJump::FlashJump()
		: mDelay(0.0f), mCoolDown(0.0f) {
	}

	FlashJump::~FlashJump() {
	}

	void FlashJump::Initialize() {
	}

	void FlashJump::Update() {
		if (!mbIsJumping) {
			mbIsJumping = true;
		}
	}

	void FlashJump::LateUpdate() {
	}

	void FlashJump::Render() {
	}

}

