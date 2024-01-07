// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "SambaAbilityTask.generated.h"

/**
 * An ability task that can be derived in blueprint.  Contains many helpful functions.
 */
UCLASS(Blueprintable, editinlinenew)
class SAMBA_API USambaAbilityTask : public UAbilityTask
{
	GENERATED_BODY()
	public:

	UPROPERTY(VisibleInstanceOnly)
	UObject* TaskSource;

	UFUNCTION(BlueprintCallable)
	UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION(BlueprintCallable)
	UGameplayAbility* GetAbility() const;

	UFUNCTION(BlueprintCallable)
	AActor* GetAvatarActorBP() const;

	void InitTask_Public(IGameplayTaskOwnerInterface& InTaskOwner, uint8 InPriority);

	protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Activate_BP();

	virtual void Activate() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDestroy_BP(bool bInOwnerFinished);

	virtual void OnDestroy(bool bInOwnerFinished) override;


	UFUNCTION(BlueprintImplementableEvent)
	void TickTask_BP(float DeltaTime);

	virtual void TickTask(float DeltaTime) override;
};
