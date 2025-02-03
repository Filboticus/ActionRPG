// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RPGEnemy.h"

#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AbilitySystem/RPGAttributeSet.h"
#include "ActionRPG/ActionRPG.h"

ARPGEnemy::ARPGEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal); 
	
	AttributeSet = CreateDefaultSubobject<URPGAttributeSet>("AttributeSet");
}

void ARPGEnemy::BeginPlay()
{
	Super::BeginPlay();

	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ARPGEnemy::HighlightActor()
{
	bHighlighted = true;

	// Highlight Character
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_YELLOW); // CUSTOM_DEPTH_YELLOW defined in ActionRPG.h

	// Highlight Weapon
	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_YELLOW);
	
	
}

void ARPGEnemy::UnHighlightActor()
{
	bHighlighted = false;

	// Unhighlight Character
	GetMesh()->SetRenderCustomDepth(false);

	// Unhighlight Weapon
	Weapon->SetRenderCustomDepth(false);
}


