// Copyright Big Time Studios Ltd. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <GenericTeamAgentInterface.h>
#include "../EffectPackage.h"
#include "GameplayEffectsVolume.generated.h"

struct FHitResult;
class UPrimitiveComponent;
class UAbilitySystemComponent;
struct FGameplayTag;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FVolumeAppliedEffectsDelegate, AGameplayEffectsVolume*, SourceActor, const TArray<FActiveGameplayEffectHandle>&, EffectResults);

/**
 * A volume(s) created by a particular ASC.  Applies gameplay effects to anyone that enters.
 */
UCLASS(Abstract, BlueprintType, Blueprintable)
class SAMBA_API AGameplayEffectsVolume : public AActor  //  TODO: public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	AGameplayEffectsVolume();

	UFUNCTION(BlueprintCallable)
	AActor* GetAvatarActor() const;

	UFUNCTION(BlueprintCallable)
	void Activate();

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta = (ExposeOnSpawn))
	UGameplayAbility* OwnerAbility;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, meta= (ExposeOnSpawn))
	UAbilitySystemComponent* OwnerComponent;

	UFUNCTION(BlueprintCallable)
	void SetDebugDraw(bool On);

protected:

	// If true, do not start tracking targets until Activate is called manually.
	UPROPERTY(BlueprintReadWrite, meta= (ExposeOnSpawn))
	bool bActivateManually = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsActive = false;

public:

	UFUNCTION(BlueprintCallable)
	void SetDuration(float Duration);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetVolumeSize(FVector NewSize);
	virtual void SetVolumeSize_Implementation(FVector NewSize);

	UFUNCTION()
	virtual void DurationExpired();

	// Cues
	// A persistent cue that triggers when the volume spawns and lasts until it is destroyed.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag CueOnSpawn;

	// An instant cue when the volume spawns.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag InstantCueOnSpawn;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FGameplayCueParameters CachedCueOnSpawnParameters;

	// Instant cue when the volume expires
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FGameplayTag CueOnExpire;

	
	
	// Volumes
	UFUNCTION(BlueprintCallable, Category = "Volume")
	TArray<UPrimitiveComponent*> GetVolumeComponents() const {return VolumeComponents;}

	UFUNCTION(BlueprintCallable, Category = "Volume")
	TSet<AActor*> GetAllActorsWithinVolumes() const;

	UFUNCTION(BlueprintCallable, Category = "Volume")
	bool IsActorWithinAnyVolume(const AActor* ArgActor) const;

	UFUNCTION(BlueprintCallable, Category = "Volume")
	TArray<UPrimitiveComponent*> GetVolumesIntersectingActor(const AActor* ArgActor) const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	TSet<TEnumAsByte<ETeamAttitude::Type>> AttitudesToTarget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Volume")
	bool bIgnoreAvatar;

	// Effects and targeting.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	bool bIgnoreDeadTargets;

	// These effects will be applied from the owner to the target.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter", meta = (ExposeOnSpawn))
	TArray<FEffectPackage> EffectPackagesAppliedOnEnter;

	// If no gameplay packages are applied on creation, use these instead.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter", meta = (ExposeOnSpawn))
	TArray<FEffectPackage> DefaultEffectPackagesAppliedOnEnter;

	// These effects will be applied from the owner to the target.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter", meta = (ExposeOnSpawn))
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffectsAppliedOnEnter; 
	
	// If no gameplay effects are applied on creation, use these instead.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	TArray<TSubclassOf<UGameplayEffect>> DefaultGameplayEffectsAppliedOnEnter; 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	int MaximumActivationsForEnter;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Effects On Enter")
	int TotalEnterActivations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	bool bDestroyAfterMaximumActivations;

	// If true Enter effects will be applied on any targets that were within the volume when it was spawned.
	// If false they must exit the volumes first.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	bool bApplyEnterEffectsOnTargetsWithinVolumeOnSpawn;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	FGameplayTag CueOnMaximumActivation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	FGameplayTag CueOnActivation;

	// If true, target will only get affected while inside the area.  Used for infinite effects.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	bool bRemoveEnterEffectsOnExit;

	// If true, a single target can be affected only once by the Enter effects.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Effects On Enter")
	bool bTargetsEnterOnlyOnce;

	// Cache the effects in this form so they can be removed later.
	TMultiMap<AActor*,FActiveGameplayEffectHandle> ActorToCachedEnterEffectsMap;

	UFUNCTION(BlueprintCallable)
	void QuickInstantCue(FGameplayTag CueTag);

	UPROPERTY(BlueprintAssignable)
	FVolumeAppliedEffectsDelegate OnAnyEnterEffectsApplied;

	// TODO: on any targets enter.

	// TODO: On any targets exit.


protected:

	// Which primitive components are to be used for the collision tests.  Configured per subclass (because we might attach primitives that aren't for collision, like visuals.
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<UPrimitiveComponent*> VolumeComponents;

	// We've overlapped something!
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void HandleAnyPrimitiveEntered(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	virtual void HandleAnyPrimitiveEntered_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Something stopped overlapping us.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void HandleAnyPrimitiveExited(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void HandleAnyPrimitiveExited_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void RemoveAllActiveEffectsWhenVolumeIsDestroyed();

	void Destroyed() override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<FActiveGameplayEffectHandle> TryApplyEnterEffects(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION(BlueprintCallable)
	//virtual TArray<AActor*> FilterPeriodicTargets(TArray<AActor*> PossibleTargets) const;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AActor*> FilterEnterTargets(TArray<AActor*> PossibleTargets) const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
