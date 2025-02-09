// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/RPGAttributeSet.h"


#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

URPGAttributeSet::URPGAttributeSet()
{
}

URPGAbilitySystemComponent* URPGAttributeSet::GetRPGAbilitySystemComponent() const
{
	return Cast<URPGAbilitySystemComponent>(GetOwningAbilitySystemComponent());
}

void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);
}



void URPGAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source - causer of the effect, Target = target of the effect (owner of "this" Attribute Set)

	// ASC = Ability System Component
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC =  Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);

		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}
