// No Copyright


#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningBaseCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());

	if (OwningBaseCharacter)
	{
		OwningBaseMovementComponent = OwningBaseCharacter->GetCharacterMovement();
	}
}

void UWarriorCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningBaseCharacter || !OwningBaseMovementComponent)
	{
		return;
	}

	CachedGroundSpeed = OwningBaseCharacter->GetVelocity().Size2D();

	CachedHasAcceleration = OwningBaseMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;

	CachedLocomotionDirection =
		UKismetAnimationLibrary::CalculateDirection(OwningBaseCharacter->GetVelocity(), OwningBaseCharacter->GetActorRotation());
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	GroundSpeed = CachedGroundSpeed;
	bHasAcceleration = CachedHasAcceleration;
	LocomotionDirection = CachedLocomotionDirection;
}
