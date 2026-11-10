// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPGHealthComponent.h"

#include "Net/UnrealNetwork.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/RPGAttributeSet.h"
#include "AbilitySystem/Attributes/RPGHealthSet.h"
#include "Interaction/CombatInterface.h"


// Sets default values for this component's properties
URPGHealthComponent::URPGHealthComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);

	AbilitySystemComponent = nullptr;
	HealthSet = nullptr;
	DeathState = ERPGDeathState::NotDead;
}

void URPGHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(URPGHealthComponent, DeathState);
}

void URPGHealthComponent::InitializeWithAbilitySystem(URPGAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if(AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("RPGHealthComponent: Health component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("RPGHealthComponent: Cannot initialize health component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	HealthSet = AbilitySystemComponent->GetSet<URPGHealthSet>();
	if (!HealthSet)
	{
		UE_LOG(LogTemp, Error, TEXT("RPGHealthComponent: Cannot initialize health component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	// Register to listen for attribute changes.
	HealthSet->OnHealthChanged.AddUObject(this, &ThisClass::HandleHealthChanged);
	HealthSet->OnMaxHealthChanged.AddUObject(this, &ThisClass::HandleMaxHealthChanged);
	HealthSet->OnOutOfHealth.AddUObject(this, &ThisClass::HandleOutOfHealth);

	// TEMP: Reset attributes to default values. Eventually this will be driven by a spreadsheet.
	AbilitySystemComponent->SetNumericAttributeBase(URPGHealthSet::GetHealthAttribute(), HealthSet->GetMaxHealth());
	
	ClearGameplayTags();

	OnHealthChanged.Broadcast(this, HealthSet->GetHealth(), HealthSet->GetHealth(), nullptr);
	OnMaxHealthChanged.Broadcast(this, HealthSet->GetMaxHealth(), HealthSet->GetMaxHealth(), nullptr);
}

void URPGHealthComponent::UninitializeFromAbilitySystem()
{
	ClearGameplayTags();

	if (HealthSet)
	{
		HealthSet->OnHealthChanged.RemoveAll(this);
		HealthSet->OnMaxHealthChanged.RemoveAll(this);
		HealthSet->OnOutOfHealth.RemoveAll(this);
	}

	HealthSet = nullptr;
	AbilitySystemComponent = nullptr;
}

float URPGHealthComponent::GetHealth() const
{
	return (HealthSet ? HealthSet->GetHealth() : 0.0f);
}

float URPGHealthComponent::GetMaxHealth() const
{
	return (HealthSet ? HealthSet->GetMaxHealth() : 0.0f);
}

float URPGHealthComponent::GetHealthNormalized() const
{
	if (HealthSet)
	{
		const float Health = HealthSet->GetHealth();
		const float MaxHealth = HealthSet->GetMaxHealth();
		
		return ((MaxHealth > 0.0f) ? (Health / MaxHealth) : 0.0f);
	}

	return 0.0f;
}

void URPGHealthComponent::StartDeath()
{
	if (DeathState != ERPGDeathState::NotDead)
	{
		return;
	}

	DeathState = ERPGDeathState::DeathStarted;

	if (AbilitySystemComponent)
	{
		//todo: Create RPGGameplayTags class
		//AbilitySystemComponent->SetLooseGameplayTagCount(RPGGameplayTags::Status_Death_Dying, 1);
	}

	AActor* Owner = GetOwner();
	check(Owner);

	OnDeathStarted.Broadcast(Owner);

	Owner->ForceNetUpdate();
}

void URPGHealthComponent::FinishDeath()
{
	if (DeathState != ERPGDeathState::DeathStarted)
	{
		return;
	}

	DeathState = ERPGDeathState::DeathFinished;

	if (AbilitySystemComponent)
	{
		//todo: Create RPGGameplayTags class
		//AbilitySystemComponent->SetLooseGameplayTagCount(RPGGameplayTags::Status_Death_Dead, 1);
	}

	AActor* Owner = GetOwner();
	check(Owner);

	OnDeathFinished.Broadcast(Owner);

	Owner->ForceNetUpdate();
	
}

void URPGHealthComponent::ClearGameplayTags()
{
	if (AbilitySystemComponent)
	{
		//TODO: RPGGameplayTags 
		//AbilitySystemComponent->SetLooseGameplayTagCount(LyraGameplayTags::Status_Death_Dying, 0);
		//AbilitySystemComponent->SetLooseGameplayTagCount(LyraGameplayTags::Status_Death_Dead, 0);
	}
}

void URPGHealthComponent::HandleHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
                                              const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void URPGHealthComponent::HandleMaxHealthChanged(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
	OnMaxHealthChanged.Broadcast(this, OldValue, NewValue, DamageInstigator);
}

void URPGHealthComponent::HandleOutOfHealth(AActor* DamageInstigator, AActor* DamageCauser,
	const FGameplayEffectSpec* DamageEffectSpec, float DamageMagnitude, float OldValue, float NewValue)
{
#if WITH_SERVER_CODE
	
	if (AbilitySystemComponent && DamageEffectSpec)
	{
		AActor* Target = AbilitySystemComponent->GetAvatarActor();
		
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(Target);
		{
			if (CombatInterface)
			{
				CombatInterface->Die();
			}
		}
		UE_LOG(LogTemp, Warning, TEXT("HandleOutofHealth -> Death"))
	}

#endif // #if WITH_SERVER_CODE	
}

void URPGHealthComponent::OnRep_DeathState(ERPGDeathState OldDeathState)
{
	const ERPGDeathState NewDeathState = DeathState;

	// Revert the death state for now since we rely on StartDeath and FinishDeath to change it.
	DeathState = OldDeathState;

	if (OldDeathState > NewDeathState)
	{
		// The server is trying to set us back but we've already predicted past the server state. //todo: LogRPG (Replace LogLrya
		UE_LOG(LogTemp, Warning, TEXT("RPGHealthComponent: Predicted past server death state [%d] -> [%d] for owner [%s]."), (uint8)OldDeathState, (uint8)NewDeathState, *GetNameSafe(GetOwner()));
		return;
	}

	if (OldDeathState == ERPGDeathState::NotDead)
	{
		if (NewDeathState == ERPGDeathState::DeathStarted)
		{
			StartDeath();
		}
		else if (NewDeathState == ERPGDeathState::DeathFinished)
		{
			StartDeath();
			FinishDeath();
		}
		else
		{
			//todo: LogRPG (Replace LogLrya
			UE_LOG(LogTemp, Error, TEXT("RPGHealthComponent: Invalid death transition [%d] -> [%d] for owner [%s]."), (uint8)OldDeathState, (uint8)NewDeathState, *GetNameSafe(GetOwner()));
		}
	}
	else if (OldDeathState == ERPGDeathState::DeathStarted)
	{
		if (NewDeathState == ERPGDeathState::DeathFinished)
		{
			FinishDeath();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("RPGHealthComponent: Invalid death transition [%d] -> [%d] for owner [%s]."), (uint8)OldDeathState, (uint8)NewDeathState, *GetNameSafe(GetOwner()));
		}
	}
	
	ensureMsgf((DeathState == NewDeathState), TEXT("LyraHealthComponent: Death transition failed [%d] -> [%d] for owner [%s]."), (uint8)OldDeathState, (uint8)NewDeathState, *GetNameSafe(GetOwner()));
}
