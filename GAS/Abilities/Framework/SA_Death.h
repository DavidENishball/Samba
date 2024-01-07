// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/Framework/SambaGameplayAbility.h"
#include "SA_Death.generated.h"

/**
 * The core Death ability for this project.  If a character is using this, they are considered DEAD.  
 */
UCLASS()
class SAMBA_API USA_Death : public USambaGameplayAbility
{
	GENERATED_BODY()
	public:

	USA_Death(); // Constructor


};


