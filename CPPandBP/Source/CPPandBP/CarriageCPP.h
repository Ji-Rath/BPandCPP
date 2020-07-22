// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "IsInteractable.h"
#include "CarriageCPP.generated.h"

/**
 * 
 */
UCLASS()
class CPPANDBP_API ACarriageCPP : public AWheeledVehicle, public IIsInteractable
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	USceneComponent* PlayerPos;

	ACarriageCPP();
};
