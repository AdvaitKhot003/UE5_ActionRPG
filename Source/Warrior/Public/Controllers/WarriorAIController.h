// No Copyright

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/Blackboard/BlackboardKey.h"
#include "WarriorAIController.generated.h"

class UAIPerceptionComponent;
class UAISenseConfig_Sight;
struct FAIStimulus;

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorAIController : public AAIController
{
	GENERATED_BODY()

public:
	AWarriorAIController(const FObjectInitializer& ObjectInitializer);
	
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	virtual void OnPossess(APawn* InPawn) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|AIController")
	UAIPerceptionComponent* EnemyAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI|AIController")
	UAISenseConfig_Sight* EnemyAISenseConfig_Sight;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	FBlackboard::FKey TargetActorKey = FBlackboard::InvalidKey;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI|Detour Crowd Avoidance Config")
	bool bShouldEnableDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category = "AI|Detour Crowd Avoidance Config",
		meta = (EditCondition = "bShouldEnableDetourCrowdAvoidance", ClampMin = "1", ClampMax = "4", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category = "AI|Detour Crowd Avoidance Config",
		meta = (EditCondition = "bShouldEnableDetourCrowdAvoidance"))
	float DetourCollisionQueryRange = 600.f;
};
