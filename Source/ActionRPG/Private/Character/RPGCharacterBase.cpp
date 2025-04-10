// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPGCharacterBase.h"

#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "Character/RPGHealthComponent.h"

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


// Called when the game starts or when spawned
void ARPGCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARPGCharacterBase::AddCharacterAbilities()
{
	URPGAbilitySystemComponent* RPG_ASC = CastChecked<URPGAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;

	RPG_ASC->AddCharacterAbilities(StartupAbilities);
	
}

