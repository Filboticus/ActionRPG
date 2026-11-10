// Fill out your copyright notice in the Description page of Project Settings.



#include "AbilitySystem/Abilities/RPGGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "Player/RPGPlayerControllerBase.h"

URPGGameplayAbility::URPGGameplayAbility(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateNo;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	NetSecurityPolicy = EGameplayAbilityNetSecurityPolicy::ClientOrServer;

	//ActivationPolicy = ELyraAbilityActivationPolicy::OnInputTriggered;
	//ActivationGroup = ELyraAbilityActivationGroup::Independent;
	
	//bLogCancelation = false;

	//ActiveCameraMode = nullptr;
}

URPGAbilitySystemComponent* URPGGameplayAbility::GetRPGAbilitySystemComponentFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<URPGAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent.Get()) : nullptr);
}

ARPGPlayerControllerBase* URPGGameplayAbility::GetRPGPlayerControllerBaseFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ARPGPlayerControllerBase>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

AController* URPGGameplayAbility::GetControllerFromActorInfo() const
{
	if (CurrentActorInfo)
	{
		if (AController* PC = CurrentActorInfo->PlayerController.Get())
		{
			return PC;
		}

		// Look for a player controller or pawn in the owner chain.
		AActor* TestActor = CurrentActorInfo->OwnerActor.Get();

		while (TestActor)
		{
			if (AController* C = Cast<AController>(TestActor))
			{
				return C;
			}

			if (APawn* Pawn = Cast<APawn>(TestActor))
			{
				return Pawn->GetController();
			}

			TestActor = TestActor->GetOwner();
		}
	}

	return nullptr;
} 
