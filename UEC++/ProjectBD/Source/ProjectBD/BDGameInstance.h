// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTBD_API UBDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FString UserID;
	
	
	
	
};
