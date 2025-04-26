// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RPGCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "RPGEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONRPG_API ARPGEnemy : public ARPGCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	ARPGEnemy();
	
	/**  Begin Enemy Interface */
	virtual void HighlightActor() override;
	
	virtual void UnHighlightActor() override;
	
	/**  End Enemy Interface */

	//** Combat Interface */
	virtual int32 GetLevel() override;
	
	/** End Combat Interface */
	
	UPROPERTY(BlueprintReadOnly)
	bool bHighlighted = false;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Character Class Defaults")
	int32 Level = 1;
};
