#pragma once
#include "MCollider.h"
#include "MMath.h"


namespace maple {

	class BoxCollider2D : public Collider{

	public:
		BoxCollider2D();
		~BoxCollider2D();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:

	};



}
