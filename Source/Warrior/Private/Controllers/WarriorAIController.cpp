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

void AWarriorAIController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* CrowdFollowingComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		/** const FString Message = FString::Printf(TEXT("PathFollowingComponent Class: %s"), *CrowdFollowingComp->GetClass()->GetName());
		Debug::Print(Message, FColor::Green); **/

		CrowdFollowingComp->SetCrowdSimulationState(bShouldEnableDetourCrowdAvoidance?
			ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourCrowdAvoidanceQuality)
		{
			case 1: CrowdFollowingComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);		break;
			case 2: CrowdFollowingComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);	break;
			case 3: CrowdFollowingComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);		break;
			case 4: CrowdFollowingComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);		break;
			default:																				break;
		}

		CrowdFollowingComp->SetAvoidanceGroup(1);
		CrowdFollowingComp->SetGroupsToAvoid(0xFF);
		CrowdFollowingComp->SetCrowdCollisionQueryRange(DetourCollisionQueryRange);
	}
}

ETeamAttitude::Type AWarriorAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	
	if (!PawnToCheck)
	{
		return ETeamAttitude::Neutral;
	}

	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());

	if (!OtherTeamAgent)
	{
		return ETeamAttitude::Neutral;
	}

	return (OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())? ETeamAttitude::Hostile : ETeamAttitude::Friendly;
}

void AWarriorAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
		{
			if (Stimulus.WasSuccessfullySensed() && Actor)
			{
				Debug::Print(FString::Printf(TEXT("Sensed=%d | Strength=%.2f | Age=%.2f"),
					Stimulus.WasSuccessfullySensed(), Stimulus.Strength, Stimulus.GetAge()), FColor::Yellow);
				
				BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
			}
		}
	}
}
