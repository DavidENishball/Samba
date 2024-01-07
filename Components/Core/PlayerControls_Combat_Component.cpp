// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Core/PlayerControls_Combat_Component.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "GAS/Statics/SambaGameplayStatics.h"
#include "../../../../../../../Plugins/Runtime/GameplayAbilities/Source/GameplayAbilities/Public/AbilitySystemComponent.h"


DEFINE_LOG_CATEGORY(LogControls);


// Sets default values for this component's properties
UPlayerControls_Combat_Component::UPlayerControls_Combat_Component()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerControls_Combat_Component::BeginPlay()
{
	Super::BeginPlay();

	ASC = GetOwner()->FindComponentByClass<UAbilitySystemComponent>();
	if (ASC == nullptr)
	{
		return;
	}

	FGameplayAbilitySpecHandle LightHandle = USambaGameplayStatics::FindOrGrantAbilitySpecHandleByClass(ASC, LightAttackAbility);
	FGameplayAbilitySpecHandle HeavyHandle = USambaGameplayStatics::FindOrGrantAbilitySpecHandleByClass(ASC, HeavyAttackAbility);


	UInputComponent* FoundInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(FoundInputComponent))
	{
		EnhancedInputComponent->BindAction(PrimaryActionInput, ETriggerEvent::Started, this, &UPlayerControls_Combat_Component::HandlePrimaryActionStarted);
		//EnhancedInputComponent->BindAction(PrimaryActionInput, ETriggerEvent::Completed, this, &UPlayerControls_Combat_Component::HandlePrimaryActionCompleted);
		EnhancedInputComponent->BindAction(SecondaryActionInput, ETriggerEvent::Started, this, &UPlayerControls_Combat_Component::DoHeavyAttack);

		//// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//// Moving
		//EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASambaCharacter::Move);

		//// Looking
		//EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASambaCharacter::Look);
	}
	else
	{
		UE_LOG(LogControls, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void UPlayerControls_Combat_Component::HandlePrimaryActionStarted()
{
	
}

//void UPlayerControls_Combat_Component::HandlePrimaryActionCompleted()
//{
//	ASC->TryActivateAbilityByClass(LightAttackAbility);
//}

void UPlayerControls_Combat_Component::DoHeavyAttack()
{
	ASC->TryActivateAbilityByClass(HeavyAttackAbility);
}

