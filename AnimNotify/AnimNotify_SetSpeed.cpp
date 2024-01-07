// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SetSpeed.h"
#include "GameFramework/MovementComponent.h"

void UAnimNotify_SetSpeed::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		UMovementComponent* MovementComp = MeshComp->GetOwner()->FindComponentByClass<UMovementComponent>();
		if (MovementComp == nullptr)
		{
			return;
		}

		if (NewSpeed == 0)
		{
			MovementComp->Velocity == FVector::ZeroVector;
		}
		else
		{
			MovementComp->Velocity = (MovementComp->Velocity.GetSafeNormal() * NewSpeed);
		}
	}
}
