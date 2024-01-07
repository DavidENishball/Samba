// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Core/ComboPathComponent.h"
#include "AbilityComboSystemNode.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/InputComponent.h"
#include "../../../../../../../Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"

// Sets default values for this component's properties
UComboPathComponent::UComboPathComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UComboPathComponent::BeginPlay()
{
	Super::BeginPlay();  // Never forget this.

	ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());

	if (!ensure(ASC))
	{
		return;
	}

	// Starting with the root node, aquire all abilities referenced and index.

	TSet < TSubclassOf<UAbilityComboSystemNode>> UniqueSet;

	TSet<UInputAction*> ActionsToBind;

	for (TSubclassOf<UAbilityComboSystemNode> IteratedNodeClass : ComboNodes)
	{
		if (!ensure(IteratedNodeClass))
		{
			continue;
		}

		if (!ensure(UniqueSet.Contains(IteratedNodeClass) == false))
		{
			// Prevent duplicate nodes
			continue;
		}

		UAbilityComboSystemNode* NewNode = NewObject<UAbilityComboSystemNode>(this, IteratedNodeClass);

		InstantiatedNodes.Add(NewNode);

		if (NewNode->Ability != nullptr)
		{
			// Grant ability.
			FGameplayAbilitySpec* ExistingSpec = ASC->FindAbilitySpecFromClass(NewNode->Ability);

			if (ExistingSpec == nullptr)
			{
				FGameplayAbilitySpecHandle NewHandle = ASC->K2_GiveAbility(NewNode->Ability); // TODO: Input ID?
				AbilityToNodeMap.Add(NewHandle, NewNode);
			}
			if (ExistingSpec != nullptr)
			{
				// We already have a spec for this ability.
				AbilityToNodeMap.Add(ExistingSpec->Handle, NewNode);
			}			
		}
		else
		{
			// TODO: Root.
			AbilityToNodeMap.Add(FGameplayAbilitySpecHandle(), NewNode);
			RootNode = NewNode;
		}

		// Get input bindings.
		ActionsToBind.Append(IInputBindingsInterface::Execute_GetInputActions(NewNode));

		// Add linked abilities;

		for (const FAbilityComboSystemLink& IteratedLink : NewNode->Links)
		{
			TSubclassOf<UGameplayAbility> LinkedAbilityClass = IteratedLink.LinkedAbility;
			if (!ensureAlways(LinkedAbilityClass != nullptr))
			{
				continue;
			}
			// Grant the ability if we don't have it.
			FGameplayAbilitySpecHandle UnusedHandle = ASC->K2_GiveAbility(LinkedAbilityClass); // TODO : cache this?  Maybe for abilities that are explicitly granted by this component.
		}
	}

	// Bind required actions so we can check their state at any time.
	UEnhancedInputComponent* FoundInputComponent = GetOwner()->FindComponentByClass<UEnhancedInputComponent>();
	if (FoundInputComponent)
	{
		for (UInputAction* IteratedAction : ActionsToBind)
		{
			FoundInputComponent->BindActionValue(IteratedAction);
		}
	}
}


// Called every frame
void UComboPathComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// Get currently animating ability.
	// Get appropriate node.
	// Do we have a valid link?  If so, try activate.

	// TODO: Check if we've changed abilities in a way that doesn't follow a link.  That means we've broken the combo.
	// Can use this to do things like add links that persist down-stream.  Nested combos.

	FGameplayAbilitySpecHandle CurrentAbilityHandle; 

	CurrentAnimatingAbility = ASC->GetAnimatingAbility();
	if (CurrentAnimatingAbility != nullptr)
	{
		CurrentAbilityHandle = CurrentAnimatingAbility->GetCurrentAbilitySpecHandle();
	}

	if (AbilityToNodeMap.Contains(CurrentAbilityHandle))
	{
		UAbilityComboSystemNode* BestNode = AbilityToNodeMap[CurrentAbilityHandle];
		if (BestNode == nullptr)
		{
			// Default to root.
			BestNode = RootNode;
		}

		if (BestNode != nullptr)
		{
			FGameplayTagContainer TempContainer;
			FAbilityComboSystemLink BestLink = BestNode->GetBestLink(CurrentAbilityHandle, ASC->AbilityActorInfo.Get(), &TempContainer, &TempContainer, &TempContainer); //  !!!!!!MAJOR TODO: How do I get all the actor info I need?

			if (FGameplayAbilitySpec* FoundSpec = ASC->FindAbilitySpecFromClass(BestLink.LinkedAbility))
			{
				ASC->TryActivateAbility(FoundSpec->Handle);
			}
		}
	}
}

