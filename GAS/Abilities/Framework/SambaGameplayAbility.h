// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SambaGameplayAbility.generated.h"

class UTargetType;

/**
 * Base class for any ability relevant to Project Samba
 */
UCLASS(abstract)
class SAMBA_API USambaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bActivateAbilityOnGranted;


	void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;



protected:

};
