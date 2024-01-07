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

	UFUNCTION(BlueprintCallable)
	static FRotator GetFlatRotation(FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	static void FlattenRotationInPlace(FRotator& Rotation);

	UFUNCTION(BlueprintCallable)
	static FTransform GetFlatTransform(FTransform Transform);

	UFUNCTION(BlueprintCallable)
	static void FlattenTransformInPlace(FTransform& Transform);

	UFUNCTION(BlueprintCallable)
	static void FlattenActorTransform(AActor* Actor);

	UFUNCTION(BlueprintCallable)
	static FVector GetStandingLocation(AActor* InActor, FVector FloorLocation);

	UFUNCTION(BlueprintCallable)
	static FVector GetActorBaseLocation(AActor* InActor);
};