// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameplayTagContainer.h>
#include <GenericTeamAgentInterface.h>
#include "TeamComponent.generated.h"

/// <summary>
///  Indicates this character is on a team.
/// </summary>
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMBA_API UTeamComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTeamComponent();

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TMap<AActor*, ETeamAttitude> OtherActorToAttitudeOverrideMap;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//TMap<FGameplayTag, ETeamAttitude> TeamTagToAttitudeOverrideMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Categories = "Character.Team"))
	FGameplayTag MainTeam;

	ETeamAttitude::Type GetAttitude(const AActor* OtherActor) const;		
};
