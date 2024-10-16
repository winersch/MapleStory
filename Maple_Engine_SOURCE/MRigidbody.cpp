#include "MRigidbody.h"
#include "MTime.h"
#include "MTransform.h"
#include "MGameObject.h"

namespace maple {


	Rigidbody::Rigidbody() 
		: Component(enums::eComponentType::Rigidbody)
		, mbGround(false)
		, mMass(1.0f)
		, mFriction(1000.0f)
		, mForce(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mLimitedVelocity(Vector2(2000.0f, 1000.0f))
		, mGravity(Vector2(0.0f, -700.0f))
		, mAccelation(Vector2::Zero)
	{
	}

	Rigidbody::~Rigidbody() {
	}

	void Rigidbody::Initialize() {
	}

	void Rigidbody::Update() {
		// f(힘) = m(질량) x a(가속도)
		// a = f / m;
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더한다.
		mVelocity += mAccelation * Time::DeltaTime();

		if (mbGround) {
			// 땅위에 있을때
			Vector2 gravity = mGravity;
			gravity.Normalize();

			float dot = mVelocity.Dot(gravity);
			mVelocity -= gravity * dot;
		} else {
			// 공중에 있을때
			mVelocity += mGravity * Time::DeltaTime();
		}
		//최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = mVelocity.Dot(gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitedVelocity.y < gravity.Length()) {
			gravity.Normalize();
			gravity *= mLimitedVelocity.y;
		}

		if (mLimitedVelocity.x < sideVelocity.Length()) {
			sideVelocity.Normalize();
			sideVelocity *= mLimitedVelocity.x;
		}
		mVelocity = gravity + sideVelocity;
		if (mVelocity != Vector2::Zero && mbGround) {
			// 수평 속도만 고려
			Vector2 horizontalVelocity = mVelocity;
			horizontalVelocity.y = 0;  // y축 성분은 무시

			// 마찰력 계산
			Vector2 friction = -horizontalVelocity;
			friction.Normalize();
			friction *= mFriction * mMass * Time::DeltaTime();

			// 마찰력이 속도보다 크면 속도를 0으로 설정
			if (horizontalVelocity.Length() <= friction.Length()) {
				horizontalVelocity = Vector2::Zero;
			}
			else {
				horizontalVelocity += friction;
			}

			// y축 속도는 유지하고 x축 속도만 업데이트
			mVelocity.x = horizontalVelocity.x;
		}

		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos = pos + mVelocity * Time::DeltaTime();
		tr->SetPosition(pos);

		mForce = Vector2::Zero;
	}

	void Rigidbody::LateUpdate() {
	}

	void Rigidbody::Render() {
	}

}

