
#include "IE_PCH.h"
#include "EventAnimController.h"
#include "AnimInstance.h"
#include "AnimationController.h"
#include "ECS/Components/AnimationComponent/EventAnimPlaySetting.h"

namespace inceptionengine
{
	EventAnimController::EventAnimController(std::reference_wrapper<AnimationController> animationController)
		:mAnimationController(animationController)
	{

	}

	EventAnimController::~EventAnimController() = default;

	void EventAnimController::PlayEventAnimation(EventAnimPlaySetting const& setting)
	{
		if (mEventAnimBlender.IsBlending()) return;

		if (mAnimInstance != nullptr)
		{
			std::vector<Matrix4x4f> currentPose = mAnimInstance->Sample(mRunningTime);
			mAnimInstance->Interrupt();
			mAnimInstance = std::make_unique<AnimInstance>(setting);
			std::vector<Matrix4x4f> blendToPose = mAnimInstance->Sample(0.0f);
			mEventAnimBlender.StartBlending(currentPose, blendToPose, setting.blendInDuration);
		}
		else
		{
			mAnimInstance = std::make_unique<AnimInstance>(setting);
		}

		
		mRunningTime = 0.0f;
		mAnimInstance->Start();
	}

	bool EventAnimController::IsPlayingAnimation() const
	{
		return mAnimInstance != nullptr;
	}
	void EventAnimController::Update(float dt)
	{
		if (mAnimInstance != nullptr)
		{
			if (mEventAnimBlender.IsBlending())
			{
				auto blendedPose = mEventAnimBlender.Blend(dt);
				if (blendedPose.has_value())
				{
					mCurrentPose = blendedPose.value();
				}
				else
				{
					//stop blending
				}
			}
			else
			{
				float currentAnimSpeend = mAnimInstance->QueryAnimSpeed(mRunningTime / mAnimInstance->GetDuration());
				mRunningTime += dt * currentAnimSpeend;
				if (mRunningTime > mAnimInstance->GetDuration())
				{
					//stop animation
					mAnimInstance->End();
					mRunningTime = 0.0f;
					mAnimationController.get().EventAnimFinish(mAnimInstance->GetBlendOutDuration());
					mAnimInstance = nullptr;
					
				}
				else
				{
					mAnimInstance->Notify(mRunningTime);
					mCurrentPose = mAnimInstance->Sample(mRunningTime);
				}
			}
		}
	}
	std::vector<Matrix4x4f> const& EventAnimController::GetCurrentPose() const
	{
		return mCurrentPose;
	}
	bool EventAnimController::IsBlending() const
	{
		return mEventAnimBlender.IsBlending();
	}
	float EventAnimController::GetCurrentEventAnimTime() const
	{
		if (mRunningTime == 0.0f) return -1.0f;
		else return mRunningTime;
	}
	float EventAnimController::GetCurrentEventAnimDuration() const
	{
		assert(mAnimInstance != nullptr);
		return mAnimInstance->GetDuration();
	}
	void EventAnimController::InsertAnimSpeedRange(float startRatio, float endRatio, float playSpeed)
	{
		assert(mAnimInstance != nullptr);
		AnimSpeedRange range;
		range.startRatio = startRatio;
		range.endRatio = endRatio;
		range.playSpeed = playSpeed;
		mAnimInstance->InsertAnimSpeedRange(range);
	}
}


