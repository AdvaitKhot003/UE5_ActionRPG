// No Copyright


#include "Widgets/WarriorWidgetBase.h"
#include "Interfaces/PawnUIInterface.h"

void UWarriorWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	APawn* OwningPawn = GetOwningPlayerPawn();
	check(OwningPawn);

	if (const IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningPawn))
	{
		UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent();

		checkf(HeroUIComponent,
			TEXT("Actor %s implements IPawnUIInterface but returned null HeroUIComponent"),
			*OwningPawn->GetActorNameOrLabel());

		BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
	}
}

void UWarriorWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if (const IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent();

		checkf(EnemyUIComponent,
			TEXT("Actor %s implements IPawnUIInterface but returned null EnemyUIComponent"),
			*OwningEnemyActor->GetActorNameOrLabel());

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
	}
}
