#include "MTransform.h"
#include "MGraphics.h"
#include "MCamera.h"
#include "MConstantBuffer.h"
#include "MRenderer.h"

namespace maple {



	Transform::Transform()
		: Component(enums::eComponentType::Transform)
		, mWorldMatrix(Matrix::Identity)
		, mScale(Vector3::One)
		, mRotation(Vector3::Zero)
		, mPosition(Vector3::Zero)
		, mbRenderPos(false)
		, mRenderPos(Vector3::Zero)
		, mParent(nullptr)
	{
	}

	Transform::~Transform() {
	}

	void Transform::Initialize() {
	}

	void Transform::Update() {
	}

	void Transform::LateUpdate() {
		Matrix scale = Matrix::CreateScale(mScale.x, mScale.y, mScale.z);
		Matrix rotation = Matrix::CreateRotationX(math::Radian(mRotation.x));
		rotation *= Matrix::CreateRotationY(math::Radian(mRotation.y));
		rotation *= Matrix::CreateRotationZ(math::Radian(mRotation.z));
		Matrix translation;
		if (mbRenderPos) {
			translation = Matrix::CreateTranslation(mRenderPos);
		}
		else {
			translation = Matrix::CreateTranslation(mPosition);
		}

		mWorldMatrix = scale * rotation * translation;

		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);
		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
	}

	void Transform::Render() {
	}

	void Transform::Bind() {
		graphics::TransformCB cbData = {};
		cbData.world = GetWorldMatrix();
		cbData.view = Camera::GetGpuViewMatrix();
		cbData.projection = Camera::GetGpuProjectionMatrix();

		graphics::ConstantBuffer* cb = renderer::constantBuffers[CBSLOT_TRANSFORM];

		cb->SetData(&cbData);
		cb->Bind(eShaderStage::All);
	}

}