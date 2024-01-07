// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../../../../../../../Source/Runtime/GameplayTags/Classes/GameplayTagContainer.h"
#include "PlayerControls_Combat_Component.generated.h"

class UInputAction;
class UAbilitySystemComponent;
class UGameplayAbility;
DECLARE_LOG_CATEGORY_EXTERN(LogControls, Log, All);


USTRUCT(BlueprintType)
struct FButtonHistoryStruct
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	float PressedTime;

	UPROPERTY(BlueprintReadOnly)
	float ReleasedTime;

	bool IsButtonDown() const
	{
		return PressedTime > ReleasedTime;
	}
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMBA_API UPlayerControls_Combat_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerControls_Combat_Component();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TSubclassOf<UGameplayAbility> LightAttackAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TSubclassOf<UGameplayAbility> HeavyAttackAbility;
	// TODO: Bind Action and Ability into a single struct?


protected:

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TMap<FGameplayTag, FButtonHistoryStruct> InputTagToButtonHistoryMap;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	UAbilitySystemComponent* ASC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PrimaryActionInput;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SecondaryActionInput;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category=Combat)
	virtual void HandlePrimaryActionStarted();

	UFUNCTION(BlueprintCallable, Category=Combat)
	virtual void DoHeavyAttack();		
};
