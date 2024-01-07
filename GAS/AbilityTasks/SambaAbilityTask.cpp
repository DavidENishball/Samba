// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/SambaAbilityTask.h"

UAbilitySystemComponent* USambaAbilityTask::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

UGameplayAbility* USambaAbilityTask::GetAbility() const
{
	return this->Ability;
}

AActor* USambaAbilityTask::GetAvatarActorBP() const
{
	return GetAvatarActor();
}

void USambaAbilityTask::InitTask_Public(IGameplayTaskOwnerInterface& InTaskOwner, uint8 InPriority)
{
	InitTask(InTaskOwner, InPriority);
}

void USambaAbilityTask::Activate()
{
	Activate_BP();
	Super::Activate();
}

void USambaAbilityTask::OnDestroy(bool bInOwnerFinished)
{
	OnDestroy_BP(bInOwnerFinished);
	Super::OnDestroy(bInOwnerFinished);
}

void USambaAbilityTask::TickTask(float DeltaTime)
{
	TickTask_BP(DeltaTime);
	Super::TickTask(DeltaTime);
}
