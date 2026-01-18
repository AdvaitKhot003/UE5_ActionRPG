// No Copyright


#include "Controllers/WarriorHeroController.h"

void AWarriorHeroController::BeginPlay()
{
	Super::BeginPlay();

	HeroTeamId = FGenericTeamId(0);
}

FGenericTeamId AWarriorHeroController::GetGenericTeamId() const
{
	return HeroTeamId;
}
