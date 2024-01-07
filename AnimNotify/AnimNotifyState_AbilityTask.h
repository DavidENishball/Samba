// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AnimNotifyState_AbilityTask.generated.h"

class UAbilityTask;

/**
 * Start an Ability task on the current animating ability.
 */
UCLASS()
class SAMBA_API UAnimNotifyState_AbilityTask : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Instanced)
	UAbilityTask* TaskInstance;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

protected:
	UPROPERTY(VisibleAnywhere)
	TMap<USkeletalMeshComponent*, UAbilityTask*> MeshToActiveTaskMap;
};
