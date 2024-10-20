#pragma once

namespace maple::enums {

	enum class eComponentType {
		Transform,
		Collider,
		Rigidbody,
		SpriteRenderer,
		Animator,
		SkillManager,
		Script,
		Camera,
		AudioListener,
		AudioSource,
		End,
	};

	enum class eLayerType {
		None,
		BackGround,
		Object,
		NPC,
		Floor,
		Monster,
		Player,
		Effect,
		Particle,
		UI,
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