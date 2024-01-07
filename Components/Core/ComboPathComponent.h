// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "ComboPathComponent.generated.h"

// A component that represents a set of abilities and how they connect.  By default will attempt to grant abilities the character does not already have.  Is also responsible for driving the combo.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMBA_API UComboPathComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComboPathComponent();

	// Root of the graph.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Combo)
	TArray<TSubclassOf<class UAbilityComboSystemNode>> ComboNodes;

	// TODO: come up with a smarter system than manual inclusion.

protected:
	// Map of the currently executing ability to the appropriate node.
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	TMap<FGameplayAbilitySpecHandle, UAbilityComboSystemNode*> AbilityToNodeMap;

	// All nodes created and owned in this combo;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
		TArray<UAbilityComboSystemNode*> InstantiatedNodes;

	// The node to use when no other nodes are available.  "Idle".
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	class UGameplayAbility* CurrentAnimatingAbility;


	// The node to use when no other nodes are available.  "Idle".
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	UAbilityComboSystemNode* RootNode;

	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = Combo)
	class UAbilitySystemComponent* ASC;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
