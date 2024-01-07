// Fill out your copyright notice in the Description page of Project Settings.


#include "SambaMontageStatics.h"
#include <NativeGameplayTags.h>


float USambaMontageStatics::GetDurationForMontageSection(UAnimMontage* Montage, const FName SectionName /*= NAME_None*/)
{
	if (!Montage)
	{
		return 0.f;
	}

	const int32 SectionIndex = Montage->GetSectionIndex(SectionName);

	// Returns the full length if section index is invalid
	return Montage->GetSectionLength(SectionIndex);
}