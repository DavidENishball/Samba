#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayEffectTypes.h"
#include "Debug_GASConfigureComponent.generated.h"

class UGameplayAbility;
class UGameplayEffect;

UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class SAMBA_API UDebug_GASConfigureComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToGrant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayEffect>> EffectsToApply;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> AbilitiesToRemove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer RemoveAbilitiesWithTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> EffectsToRemove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer RemoveEffectsWithTags;

	// Will add these attribute sets if not already present.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<class UAttributeSet>> AttributeSetsToAdd;


	void BeginPlay() override;

	void ApplyChanges();
};

