#pragma once
#include "MScript.h"
#include "MCollider.h" 
#include "MGameObject.h"

namespace maple {

	class PhantomBlowScript : public Script{

	public:
		PhantomBlowScript();
		~PhantomBlowScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnCollisionEnter(Collider* target) override;
		void OnCollisionStay(class Collider* other) override;
		void OnCollisionExit(Collider* target) override;

		void SetPlayer(GameObject* player) { mPlayer = player; }

	private:
		GameObject* mPlayer;

		bool mbAttackable;


	};


}

