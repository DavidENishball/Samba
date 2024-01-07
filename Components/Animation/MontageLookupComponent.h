// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <GameplayTagContainer.h>
#include <GameplayEffectTypes.h>
#include "MontageLookupComponent.generated.h"

class UAnimMontage;
// A component that lets a character play montages contextually based on tags, so that the specific montage can be skeleton-appropriate.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMBA_API UMontageLookupComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMontageLookupComponent();

	UPROPERTY(EditAnywhere)
	TMap<FGameplayTag, class UAnimMontageSelector*> MontageSelectorMap;

protected:
	
	void BeginPlay();

	USkeletalMeshComponent* CachedSkeletalMesh;

public:	
	UFUNCTION(BlueprintCallable)
	UAnimMontage* LookupMontage(const FGameplayTag& Tag, const FGameplayEffectContextHandle& ContextHandle) const;


	// Actor Component interface Begin
	virtual void InitializeComponent() override;
	// Actor Component interface End

};
