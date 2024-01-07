// Fill out your copyright notice in the Description page of Project Settings.


#include "Interfaces/InputBindingsInterface.h"

// Add default functionality here for any IInputBindingsInterface functions that are not pure virtual.

TSet<UInputAction*> IInputBindingsInterface::GetInputActions_Implementation() const
{
	return TSet<UInputAction*>();
}
