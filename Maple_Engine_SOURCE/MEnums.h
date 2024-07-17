#pragma once

namespace maple::enums {

	enum class eComponentType {
		Transform,
		Collider,
		Rigidbody,
		Script,
		SpriteRenderer,
		Animator,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType {
		None,
		BackGround,
		Player,
		Floor,
		Particle,

		Max = 16,
	};

	enum class eResourceType {
		Texture,
		Mesh,
		Material,
		Animation,
		AudioClip,
		Shader,
		Prefab,
		End,
	};

	enum class eColliderType {
		Circle2D,
		Rect2D,
		End,
	};

	enum class eUIType {
		HpBar,
		Button,
		End,
	};
}