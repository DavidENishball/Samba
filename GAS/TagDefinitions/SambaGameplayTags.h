// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

// Controls
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_State_DisableMovement);

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_State_DisableTurning);



// Status.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_State_Dead);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_State_IgnoreSweeps);  // Ignore any Gameplay Effect Volumes outright.

// Ability Types

// Action: Any ability that affects montage.  Usually initiated by player.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Type_Action);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_Type_Death);


// Ability blocking.

UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Ability_State_BlockNormal);


// Gameplay Events
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Event_Death);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Event_DamageTaken);

// Core Teams.
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Team_PlayerCharacter);
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Team_Hostile);