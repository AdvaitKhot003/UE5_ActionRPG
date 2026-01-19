// No Copyright


#include "Controllers/WarriorAIController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "WarriorDebugHelper.h"

AWarriorAIController::AWarriorAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if (UCrowdFollowingComponent* CrowdFollowingComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		const FString Message = FString::Printf(TEXT("PathFollowingComponent: %s"), *CrowdFollowingComp->GetClass()->GetName());
		Debug::Print(Message, FColor::Green);
	}
	
	EnemyAISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemyAISenseConfig_Sight");
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	EnemyAISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	EnemyAISenseConfig_Sight->SightRadius = 5000.f;
	EnemyAISenseConfig_Sight->LoseSightRadius = 5500.f;
	EnemyAISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	EnemyAIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyAIPerceptionComponent");
	EnemyAIPerceptionComponent->ConfigureSense(*EnemyAISenseConfig_Sight);
	EnemyAIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
	EnemyAIPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &AWarriorAIController::OnEnemyPerceptionUpdated);
}

void AWarriorAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	
	if (!PawnToCheck)
	{
		return ETeamAttitude::Neutral;
	}

	const IGenericTeamAgentInterface* OtherTeamAgent =
		Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

	if (!OtherTeamAgent)
	{
		return ETeamAttitude::Neutral;
	}

	return (OtherTeamAgent->GetGenericTeamId() == GetGenericTeamId())
		? ETeamAttitude::Friendly
		: ETeamAttitude::Hostile;
}

void AWarriorAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed() && Actor)
	{
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}
