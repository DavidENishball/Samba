// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_SetSpeed.generated.h"

/**
 * 
 */
UCLASS()
class SAMBA_API UAnimNotify_SetSpeed : public UAnimNotify
{
	GENERATED_BODY()
	public: 


	UPROPERTY(EditAnywhere)
	float NewSpeed;
	protected: 
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
