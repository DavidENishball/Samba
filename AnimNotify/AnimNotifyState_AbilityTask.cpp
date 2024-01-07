// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotifyState_AbilityTask.h"


void UAnimNotifyState_AbilityTask::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		UAbilitySystemComponent* ASC = MeshComp->GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
		if (ASC == nullptr)
		{
			return;
		}

		UGameplayAbility* AnimatingAbilityInstance = ASC->GetAnimatingAbility();

		if (AnimatingAbilityInstance)
		{
			UE_LOG(LogTemp, Log, TEXT("Current animating ability is: %s"), *AnimatingAbilityInstance->GetName());

			// TODO: Clone the task.
			UAbilityTask* TaskClone = DuplicateObject<UAbilityTask>(TaskInstance, AnimatingAbilityInstance);
			if (TaskClone)
			{
				if (USambaAbilityTask* SambaTask = Cast<USambaAbilityTask>(TaskClone))
				{
					SambaTask->TaskSource = this;

					MeshToActiveTaskMap.Add(MeshComp, SambaTask);

					SambaTask->InitTask_Public(*AnimatingAbilityInstance, AnimatingAbilityInstance->GetGameplayTaskDefaultPriority());
					SambaTask->ReadyForActivation();
				}
				// How do I push it?

				//TaskClone->InitTask(*AnimatingAbilityInstance, AnimatingAbilityInstance->GetGameplayTaskDefaultPriority());

				//UAbilityTask::DebugRecordAbilityTaskCreatedByAbility(AnimatingAbilityInstance);
				
			}
		}

	}
}

void UAnimNotifyState_AbilityTask::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		UAbilitySystemComponent* ASC = MeshComp->GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
		if (ASC == nullptr)
		{
			return;
		}
		UGameplayAbility* AnimatingAbilityInstance = ASC->GetAnimatingAbility();
		if (AnimatingAbilityInstance != nullptr)
		{
			UAbilityTask* FoundTask;

			if (MeshToActiveTaskMap.RemoveAndCopyValue(MeshComp, FoundTask))
			{
				FoundTask->EndTask();
			}
		}
	}
}