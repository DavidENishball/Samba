// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/Framework/SA_Death.h"
#include "../../TagDefinitions/SambaGameplayTags.h"

USA_Death::USA_Death()
{
	this->ActivationOwnedTags.AddTagFast(TAG_Character_State_Dead);
	this->ActivationOwnedTags.AddTagFast(TAG_Character_State_DisableMovement);
	this->ActivationOwnedTags.AddTagFast(TAG_Character_State_DisableTurning);
	this->ActivationOwnedTags.AddTagFast(TAG_Character_State_IgnoreSweeps);
}
