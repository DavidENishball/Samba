// Fill out your copyright notice in the Description page of Project Settings.


#include "SambaMontageData.h"

UAnimMontage* FSambaMontageData::ChooseMontage(const AActor* Actor)
{
	// Todo: pick montage contextually from a Library.
	return this->SpecificMontage;
}
