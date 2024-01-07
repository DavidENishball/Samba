// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include <GameplayTagContainer.h>
#include "AnimNotifyState_AbilityTargeting.generated.h"

/**
 * Perform targeting based on a given TargetType, for the current animating ability.
 */
UCLASS()
class SAMBA_API UAnimNotifyState_AbilityTargeting : public UAnimNotifyState
{
	GENERATED_BODY()

	protected: 

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
