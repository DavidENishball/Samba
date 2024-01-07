// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Core/TeamComponent.h"
#include <GenericTeamAgentInterface.h>

// Sets default values for this component's properties
UTeamComponent::UTeamComponent()
{

}

ETeamAttitude::Type UTeamComponent::GetAttitude(const AActor* OtherActor) const
{
	if (MainTeam == FGameplayTag::EmptyTag)
	{
		return ETeamAttitude::Neutral;
	}

	if (OtherActor == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	// TODO: define teams as a tag or an asset?

	UTeamComponent* OtherTeamComponent = OtherActor->FindComponentByClass<UTeamComponent>();
	if (OtherTeamComponent == nullptr)
	{
		return ETeamAttitude::Neutral;
	}

	if (OtherTeamComponent->MainTeam == this->MainTeam)
	{
		return ETeamAttitude::Friendly;
	}

	return ETeamAttitude::Hostile;
}


