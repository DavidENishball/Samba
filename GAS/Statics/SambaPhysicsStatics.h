// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "SambaPhysicsStatics.generated.h"
// Statics related to transforms, rays, and colliders.


UCLASS()
class SAMBA_API USambaPhysicsStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FRotator GetFlatRotation(FRotator Rotation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void FlattenRotationInPlace(FRotator& Rotation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FTransform GetFlatTransform(FTransform Transform);

	UFUNCTION(BlueprintCallable)
	static void FlattenTransformInPlace(FTransform& Transform);

	UFUNCTION(BlueprintCallable)
	static void FlattenActorTransform(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector GetStandingLocation(const AActor* InActor, FVector FloorLocation);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FVector GetActorBaseLocation(const AActor* InActor);
};