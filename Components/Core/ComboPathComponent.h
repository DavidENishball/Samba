// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "ComboPathComponent.generated.h"

// A component that represents a set of abilities and how they connect.  By default will attempt to grant abilities the character does not already have.  Is also responsible for driving the combo.
// TODO: Swap these around for different weapons.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMBA_API UComboPathComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComboPathComponent();

	// These nodes will always evaluate, before the current combo, and link to the appropriate ability.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combo)
	TArray<TSubclassOf<class UAbilityComboSystemNode>> UniversalNodes;

	// All nodes in this list will be evaluated when their associated ability is active.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combo)
	TArray<TSubclassOf<class UAbilityComboSystemNode>> ComboNodes;

	// TODO: come up with a smarter system than manual inclusion.

protected:

	// Universal Nodes
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	TArray<UAbilityComboSystemNode*> InstantiatedUniversalNodes;

	// Map of the currently executing ability to the appropriate node.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	TMap<FGameplayAbilitySpecHandle, UAbilityComboSystemNode*> AbilityToNodeMap;

	// All nodes created and owned in this combo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
		TArray<UAbilityComboSystemNode*> InstantiatedNodes;

	// The ability that's currently animating, so we don't have to always retrieve it.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	class UGameplayAbility* CurrentAnimatingAbility;


	// The node to use when no other nodes are available.  "Idle".
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	UAbilityComboSystemNode* RootNode;

	// Called when the game starts
	virtual void BeginPlay() override;

	// The Ability System Component
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	class UAbilitySystemComponent* ASC;

	// Abilities granted by this component when preparing for combos.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	TArray<FGameplayAbilitySpecHandle> GrantedAbilities;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
