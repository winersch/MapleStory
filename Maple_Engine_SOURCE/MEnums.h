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
		Tile,
		Animal,
		Player,
		Floor,
		Particle,

		Max = 16,
	};

	enum class eResourceType {
		Texture,
		AudioClip,
		Animation,
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