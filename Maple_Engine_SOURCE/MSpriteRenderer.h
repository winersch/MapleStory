#pragma once
#include "MEntity.h"
#include "MComponent.h"
#include "MTexture.h"
#include "MMath.h"
#include "MMaterial.h"
#include "MMesh.h"

namespace maple {

	class SpriteRenderer : public Component {
	public:
		SpriteRenderer();
		~SpriteRenderer();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void SetSprite(graphics::Texture* sprite) { mSprite = sprite; }
		graphics::Texture* GetSprite() { return mSprite; }
		void SetMaterial(Material* material) { mMaterial = material; }

	private:
		graphics::Texture* mSprite;
		Material* mMaterial;
		Mesh* mMesh;
	};

}


