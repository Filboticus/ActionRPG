// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPGCharacterBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffect.h"

#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "Character/RPGHealthComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ARPGCharacterBase::ARPGCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Weapon_Left = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon_Left");
	Weapon_Left->SetupAttachment(GetMesh(), FName("WeaponHandSocket_Left"));
	Weapon_Left->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	HealthComponent = CreateDefaultSubobject<URPGHealthComponent>(TEXT("HealthComponent"));
}

URPGAbilitySystemComponent* ARPGCharacterBase::GetRPGAbilitySystemComponent() const
{
	return Cast<URPGAbilitySystemComponent>(GetAbilitySystemComponent());
}

UAbilitySystemComponent* ARPGCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARPGCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	Weapon_Left->SetSimulatePhysics(true);
	Weapon_Left->SetEnableGravity(true);
	Weapon_Left->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Set bDead to true
	bDead = true;
}

void ARPGCharacterBase::Die()
{
	// Detach Weapons
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	Weapon_Left->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));

	
}


// Called when the game starts or when spawned
void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	//TODO: Turn into Gameplay Abilities
	//ApplyHealthRegenToSelf(HealthRegenGameplayEffectClass);
	//ApplyPowerRegenToSelf(PowerRegenGameplayEffectClass);
	//ApplyEnduranceRegenToSelf(EnduranceRegenGameplayEffectClass);
}

void ARPGCharacterBase::ApplyHealthRegenToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC || !GameplayEffectClass)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void ARPGCharacterBase::ApplyPowerRegenToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC || !GameplayEffectClass)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void ARPGCharacterBase::ApplyEnduranceRegenToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC || !GameplayEffectClass)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle EffectSpecHandle = ASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);

	ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

void ARPGCharacterBase::AddCharacterAbilities()
{
	URPGAbilitySystemComponent* RPG_ASC = CastChecked<URPGAbilitySystemComponent>(AbilitySystemComponent);

	if (!HasAuthority()) return;
	
	RPG_ASC->AddCharacterAbilities(StartUpAbilities);
}

