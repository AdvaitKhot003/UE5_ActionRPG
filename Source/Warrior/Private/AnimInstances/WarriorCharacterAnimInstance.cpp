// Copyright Advait Khot


#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningBaseCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());

	if (OwningBaseCharacter)
	{
		OwningBaseMovementComponent = OwningBaseCharacter->GetCharacterMovement();
	}
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningBaseCharacter || !OwningBaseMovementComponent)
	{
		return;
	}
	
	GroundSpeed = OwningBaseCharacter->GetVelocity().Size2D();

	bHasAcceleration = OwningBaseMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
