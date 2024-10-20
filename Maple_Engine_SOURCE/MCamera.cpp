#include "MCamera.h"
#include "MGameObject.h"
#include "MTransform.h"
#include "MApplication.h"

extern maple::Application application;

namespace maple {
	Matrix Camera::ViewMatrix = Matrix::Identity;
	Matrix Camera::ProjectionMatrix = Matrix::Identity;

	Camera::Camera()
		: Component(enums::eComponentType::Camera)
		, mProjectionType(eProjectionType::Perspective)
		, mViewMatrix(Matrix::Identity)
		, mProjectionMatrix(Matrix::Identity)
		, mAspectRatio(0.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(1.0f)
		
	{

	}

	Camera::~Camera() {

	}

	void Camera::Initialize() {
		
	}

	void Camera::Update() {

		
	}

	void Camera::LateUpdate() {
		CreateViewMatrix();
		CreateProjectionMatrix(mProjectionType);

		ViewMatrix = mViewMatrix;
		ProjectionMatrix = mProjectionMatrix;
	}

	void Camera::Render() {

	}

	void Camera::CreateViewMatrix() {
		Transform* tr = GetOwner()->GetComponent<Transform>();

		const Vector3 pos = tr->GetPosition();
		const Vector3 up = tr->Up();
		const Vector3 forward = tr->Foward();

		mViewMatrix = Matrix::CreateLookToLH(pos, forward, up);
	}

	void Camera::CreateProjectionMatrix(eProjectionType type) {
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float width = (winRect.right - winRect.left);
		float height = (winRect.bottom - winRect.top);

		// 디버깅 시 화면 크기가 0이 되는 것을 방지
		if (width <= 0 || height <= 0) {
			width = 1.0f;
			height = 1.0f;
		}
		mAspectRatio = width / height;
		
		switch (type) {
			case eProjectionType::Perspective:
				mProjectionMatrix = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
				break;
			case eProjectionType::Orthographic:
				mProjectionMatrix = Matrix::CreateOrthographicLH(width , height , mNear, mFar);
				break;
		}
	}

	Vector3 Camera::GetLeftTopPosition() const {
		if (mProjectionType == eProjectionType::Orthographic) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			const Vector3 camPosition = tr->GetPosition();

			RECT winRect;
			GetClientRect(application.GetHwnd(), &winRect);
			float width = (winRect.right - winRect.left);
			float height = (winRect.bottom - winRect.top);
			Vector3 leftTop = camPosition + Vector3(-width / 2.0f, height / 2.0f, 0.0f);
			return leftTop;
		}
		else if (mProjectionType == eProjectionType::Perspective) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			const Vector3 camPosition = tr->GetPosition();
			const Vector3 forward = tr->Foward();
			const Vector3 up = tr->Up();
			const Vector3 right = tr->Right();

			float tanFov = tanf(XM_2PI / 6.0f / 2.0f); // FOV / 2의 탄젠트 값
			float halfHeight = mNear * tanFov;
			float halfWidth = halfHeight * mAspectRatio;

			Vector3 nearCenter = camPosition + forward * mNear;
			Vector3 leftTop = nearCenter + up * halfHeight - right * halfWidth;
			return leftTop;
		}

		return Vector3::Zero;
	}

	// 마우스 좌표를 월드 좌표계로 변환하는 함수
	Vector3 Camera::ScreenToWorld(const Vector2& mousePos) const {
		RECT winRect;
		GetClientRect(application.GetHwnd(), &winRect);
		float screenWidth = (winRect.right - winRect.left);
		float screenHeight = (winRect.bottom - winRect.top);

		// Orthographic 투영에서의 좌표 변환
		if (mProjectionType == eProjectionType::Orthographic) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 camPosition = tr->GetPosition();

			// 화면 좌표를 월드 좌표로 변환 (비율 기반)
			float worldX = camPosition.x + (mousePos.x / screenWidth) * screenWidth - screenWidth / 2.0f;
			float worldY = camPosition.y - (mousePos.y / screenHeight) * screenHeight + screenHeight / 2.0f;

			return Vector3(worldX, worldY, camPosition.z);
		}
		// Perspective 투영에서의 좌표 변환
		else if (mProjectionType == eProjectionType::Perspective) {
			Transform* tr = GetOwner()->GetComponent<Transform>();
			Vector3 camPosition = tr->GetPosition();
			Vector3 forward = tr->Foward();
			Vector3 up = tr->Up();
			Vector3 right = tr->Right();

			// FOV를 사용해 근평면에서의 좌상단 좌표 계산
			float tanFov = tanf(XM_2PI / 6.0f / 2.0f);
			float halfHeight = mNear * tanFov;
			float halfWidth = halfHeight * mAspectRatio;

			Vector3 nearCenter = camPosition + forward * mNear;
			Vector3 leftTop = nearCenter + up * halfHeight - right * halfWidth;

			// 마우스 좌표를 비율로 변환하여 월드 좌표 계산
			float worldX = leftTop.x + (mousePos.x / screenWidth) * 2.0f * halfWidth;
			float worldY = leftTop.y - (mousePos.y / screenHeight) * 2.0f * halfHeight;

			return Vector3(worldX, worldY, nearCenter.z);
		}

		return Vector3::Zero;
	}
}