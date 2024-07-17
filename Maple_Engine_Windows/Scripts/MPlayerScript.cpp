#include "MPlayerScript.h"
#include "MComponent.h"
#include "MTime.h"
#include "MTransform.h"
#include "MInput.h"
#include "MGameObject.h"
#include "MResources.h"
#include "MObject.h"
#include "..\\Maple_Engine_Windows\\Contents\\MCat.h"
#include "MRigidbody.h"
#include "MUIManager.h"

namespace maple {

	PlayerScript::PlayerScript()
		:mState(eState::Idle)
		, mAnimator(nullptr){
	}

	PlayerScript::~PlayerScript() {
	}

	void PlayerScript::Initialize() {
		
	}

	void PlayerScript::Update() {
		//if (mAnimator == nullptr) {
		//	mAnimator = GetOwner()->GetComponent<Animator>();
		//}
		//switch (mState) {
		//	case PlayerScript::eState::Idle:
		//		idle();
		//		break;
		//	case PlayerScript::eState::Walk:
		//		move();
		//		break;
		//	case PlayerScript::eState::Sleep:
		//		break;
		//	case PlayerScript::eState::GiveWater:
		//		giveWater();
		//		break;
		//	case PlayerScript::eState::Attack:
		//		break;
		//	default:
		//		break;
		//}

		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();
		//COLORREF color = mPixelMap->GetPixel(pos.x, pos.y + 50);

		//Rigidbody* playerRb = GetOwner()->GetComponent<Rigidbody>();
		//if (color == RGB(255, 0, 0)) {
		//	playerRb->SetGround(true);

		//	pos.y -= 1;
		//	tr->SetPosition(pos);
		//} else {
		//	playerRb->SetGround(false);
		//}

	}

	void PlayerScript::LateUpdate() {
	}

	void PlayerScript::Render() {
	}

	void PlayerScript::AttackEffect() {
		//Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
		//CatScript* catSrc = cat->AddComponent<CatScript>();

		//catSrc->SetPlayer(GetOwner());

		//graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
		//Animator* catAnimator = cat->AddComponent<Animator>();
		//catAnimator->CreateAnimation(L"DownWalk", catTex
		//	, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"RightWalk", catTex
		//	, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"UpWalk", catTex
		//	, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"LeftWalk", catTex
		//	, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"SitDown", catTex
		//	, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"Grooming", catTex
		//	, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//catAnimator->CreateAnimation(L"LayDown", catTex
		//	, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

		//catAnimator->PlayAnimation(L"SitDown", false);

		//Transform* tr = GetOwner()->GetComponent<Transform>();

		//cat->GetComponent<Transform>()->SetPosition(tr->GetPosition());
		//cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));

		//Vector2 mousePos = Input::GetMousePosition();
		//catSrc->mDest = mousePos;

	}

	void PlayerScript::OnCollisionEnter(Collider* other) {
		float ny = rand() % 672;
		float nx = rand() % 486;
		//other->GetOwner()->GetComponent<Transform>()->SetPosition(Vector2(nx, ny));
	}

	void PlayerScript::OnCollisionStay(Collider* other) {
		float ny = rand() % 672;
		float nx = rand() % 486;
		//other->GetOwner()->GetComponent<Transform>()->SetPosition(Vector2(nx, ny));

	}

	void PlayerScript::OnCollisionExit(Collider* other) {

	}

	void PlayerScript::idle() {
		//if (Input::GetKey(eKeyCode::LButton) || Input::GetKey(eKeyCode::Space)) {
		//	Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
		//	CatScript* catSrc = cat->AddComponent<CatScript>();

		//	catSrc->SetPlayer(GetOwner());

		//	graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"Cat");
		//	Animator* catAnimator = cat->AddComponent<Animator>();
		//	catAnimator->CreateAnimation(L"DownWalk", catTex
		//		, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//	catAnimator->CreateAnimation(L"RightWalk", catTex
		//		, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//	catAnimator->CreateAnimation(L"UpWalk", catTex
		//		, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//	catAnimator->CreateAnimation(L"LeftWalk", catTex
		//		, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//	catAnimator->CreateAnimation(L"SitDown", catTex
		//		, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//	catAnimator->CreateAnimation(L"Grooming", catTex
		//		, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		//	catAnimator->CreateAnimation(L"LayDown", catTex
		//		, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);

		//	catAnimator->PlayAnimation(L"SitDown", false);

		//	Transform* tr = GetOwner()->GetComponent<Transform>();

		//	cat->GetComponent<Transform>()->SetPosition(tr->GetPosition() /*+ Vector2(100.0f, 0.0f)*/);
		//	cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));


		//	Vector2 mousePos = Input::GetMousePosition();
		//	catSrc->mDest = mousePos;


		//	/*		mState = PlayerScript::eState::GiveWater;
		//			mAnimator->PlayAnimation(L"FrontGiveWater", false);
		//			Vector2 mousePos = Input::GetMousePosition();*/

		//	
		//}
		//Transform* tr = GetOwner()->GetComponent<Transform>();
		//Vector3 pos = tr->GetPosition();
		//Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		//float speed = 3.0f;

		//if (Input::GetKey(eKeyCode::D)) {
		//	//pos.x += 100.0f * Time::DeltaTime() * speed;
		//	rb->AddForce(Vector2(200.0f, 0.0f));
		//}
		//if (Input::GetKey(eKeyCode::A)) {
		//	//pos.x -= 100.0f * Time::DeltaTime() * speed;
		//	rb->AddForce(Vector2(-200.0f, 0.0f));
		//}
		//if (Input::GetKey(eKeyCode::S)) {
		//	//pos.y += 100.0f * Time::DeltaTime() * speed;
		//	rb->AddForce(Vector2(0.0f, 200.0f));
		//}
		//if (Input::GetKey(eKeyCode::W)) {
		//	//pos.y -= 100.0f * Time::DeltaTime() * speed;
		//	//rb->AddForce(Vector2(0.0f, -200.0f));
		//	if (rb->GetGround()) {
		//		Vector2 velocity = rb->GetVelocity();
		//		velocity.y = -500.0f;
		//		rb->SetVelocity(velocity);
		//		rb->SetGround(false);
		//	}
		//}
		//if (Input::GetKeyDown(eKeyCode::I)) {
		//	UIManager::Push(eUIType::HpBar);
		//	//UIManager::Push(eUIType::Button);

		//}

		//if (Input::GetKeyDown(eKeyCode::O)) {
		//	UIManager::Pop(eUIType::HpBar);

		//}
		//
		////tr->SetPosition(pos);
	}

	void PlayerScript::move() {
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		Rigidbody* rb = GetOwner()->GetComponent<Rigidbody>();

		if (Input::GetKey(eKeyCode::Right)) {
			//pos.x += 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Left)) {
			//pos.x -= 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(-200.0f, 0.0f));
		}
		if (Input::GetKey(eKeyCode::Up)) {
			//pos.y -= 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(0.0f, 200.0f));
		}
		if (Input::GetKey(eKeyCode::Down)){
			//pos.y += 100.0f * Time::DeltaTime();
			rb->AddForce(Vector2(0.0f, 200.0f));
		}

		//tr->SetPosition(pos);

		if (Input::GetKeyUp(eKeyCode::D) || Input::GetKeyUp(eKeyCode::A)
			|| Input::GetKeyUp(eKeyCode::W) || Input::GetKeyUp(eKeyCode::S)) {
			mState = PlayerScript::eState::Idle;
			mAnimator->PlayAnimation(L"SitDown", false);
		}
	}
	void PlayerScript::giveWater() {
		if (mAnimator->IsCompleted()) {
			mState = eState::Idle;
			mAnimator->PlayAnimation(L"Idle", false);
		}
	}



}