// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include <GameplayTagContainer.h>
#include "AnimNotifyState_LooseGameplayTag.generated.h"

/**
 * Apply loose gameplay tags for the duration of the notify state.
 */
UCLASS()
class SAMBA_API UAnimNotifyState_LooseGameplayTag : public UAnimNotifyState
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere)
	FGameplayTagContainer Tags;

	protected: 

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
