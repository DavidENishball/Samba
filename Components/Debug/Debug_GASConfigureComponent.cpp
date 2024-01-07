#include "Components/Debug/Debug_GASConfigureComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffect.h"
#include "Abilities/GameplayAbility.h"
#include "Runtime/GameplayTags/Classes/GameplayTagContainer.h"
#include "AbilitySystemInterface.h"



void UDebug_GASConfigureComponent::BeginPlay()
{
	Super::BeginPlay();
	ApplyChanges();
}

void UDebug_GASConfigureComponent::ApplyChanges()
{
	
	UAbilitySystemComponent* ASC = nullptr;

	IAbilitySystemInterface* AsInterface = Cast<IAbilitySystemInterface>(GetOwner());

	if (AsInterface)
	{
		ASC = AsInterface->GetAbilitySystemComponent();
	}

	if (ASC == nullptr)
	{
		// Search manually for the ASC.
		ASC = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
	}


	if (ASC == nullptr)
	{
		UActorComponent* NewComponent = GetOwner()->AddComponentByClass(UAbilitySystemComponent::StaticClass(), false, FTransform(), false);
		GetOwner()->AddInstanceComponent(NewComponent);
		ASC = Cast<UAbilitySystemComponent>(NewComponent);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("UDebug_GASConfigureComponent::ApplyChanges - Added a default ASC to Actor %s"), *(GetOwner()->GetName())));
	}

	// Start with attribute sets first.
	for (TSubclassOf<UAttributeSet> IteratedSetClass : AttributeSetsToAdd)
	{
		if (ASC->GetAttributeSet(IteratedSetClass) == nullptr)
		{
			UAttributeSet* NewSet = NewObject<UAttributeSet>(ASC->GetOwner(), IteratedSetClass);
			ASC->AddAttributeSetSubobject(NewSet);
		}
	}

	// Removal first, then add. 
	TArray<FGameplayAbilitySpecHandle> AllSpecs;
	ASC->GetAllAbilities(AllSpecs);

	for (const FGameplayAbilitySpecHandle& IteratedSpecHandle : AllSpecs)
	{
		FGameplayAbilitySpec* SpecPointer = ASC->FindAbilitySpecFromHandle(IteratedSpecHandle);
		if (SpecPointer == nullptr)
		{
			continue;
		}
		// Remove by tag.
		if (SpecPointer->Ability->AbilityTags.HasAny(RemoveAbilitiesWithTags))
		{
			ASC->ClearAbility(IteratedSpecHandle);
			continue;
		}

		// Remove by class.
		if (AbilitiesToRemove.Contains(SpecPointer->Ability->GetClass()))
		{
			ASC->ClearAbility(IteratedSpecHandle);
			continue;
		}
	}

	TArray<FActiveGameplayEffectHandle> AllActiveEffects = ASC->GetActiveEffects(FGameplayEffectQuery());

	for (const FActiveGameplayEffectHandle& IteratedHandle : AllActiveEffects)
	{
		const FActiveGameplayEffect* EffectPointer = ASC->GetActiveGameplayEffect(IteratedHandle);
		if (EffectPointer == nullptr)
		{
			continue;
		}
		if (EffectPointer->Spec.Def->GetAssetTags().HasAny(RemoveEffectsWithTags))
		{
			ASC->RemoveActiveGameplayEffect(IteratedHandle);
			continue;
		}

		if (EffectsToRemove.Contains(EffectPointer->Spec.Def->GetClass()))
		{
			ASC->RemoveActiveGameplayEffect(IteratedHandle);
			continue;
		}
	}

	// Add desired.
	// Ability
	for (TSubclassOf<UGameplayAbility>& IteratedAbilityClass : AbilitiesToGrant)
	{
		ASC->K2_GiveAbility(IteratedAbilityClass);
	}
	// Effect
	for (TSubclassOf<UGameplayEffect> IteratedGameplayEffect : EffectsToApply)
	{
		ASC->BP_ApplyGameplayEffectToSelf(IteratedGameplayEffect, 1.0f, ASC->MakeEffectContext());
	}

	// Don't bother caching.
}
