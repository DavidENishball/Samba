// Fill out your copyright notice in the Description page of Project Settings.


#include "SambaGameplayTags.h"
#include <NativeGameplayTags.h>

UE_DEFINE_GAMEPLAY_TAG(TAG_Character_State_DisableMovement, "Character.State.DisableMovement")
UE_DEFINE_GAMEPLAY_TAG(TAG_Character_State_DisableTurning, "Character.State.DisableTurning")

// Status
UE_DEFINE_GAMEPLAY_TAG(TAG_Character_State_Dead, "Character.State.Dead");
UE_DEFINE_GAMEPLAY_TAG(TAG_Character_State_IgnoreSweeps, "Character.State.IgnoreSweeps");


// Ability Types
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Type_Action, "Ability.Type.Action")
UE_DEFINE_GAMEPLAY_TAG(TAG_Ability_Type_Death, "Ability.Type.Death")

// Gameplay Events
UE_DEFINE_GAMEPLAY_TAG(TAG_Event_Death, "GameplayEvent.Death")
UE_DEFINE_GAMEPLAY_TAG(TAG_Event_DamageTaken, "GameplayEvent.DamageTaken");

// Core Teams

UE_DEFINE_GAMEPLAY_TAG(TAG_Character_Team_PlayerCharacter, "Character.Team.PlayerCharacter")
UE_DEFINE_GAMEPLAY_TAG(TAG_Character_Team_Hostile, "Character.Team.Hostile")