// Copyright Advait Khot

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorBaseWeapon.generated.h"

class UBoxComponent;

UCLASS()
class WARRIOR_API AWarriorBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWarriorBaseWeapon();

	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }

protected:
	/** Begin Weapon Components **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;
	/** End Weapon Components **/
};
