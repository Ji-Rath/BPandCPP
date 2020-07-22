// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGUICPP.generated.h"

/**
 * 
 */
UCLASS()
class CPPANDBP_API UMainGUICPP : public UUserWidget
{
	GENERATED_BODY()
	

public:

	//Allow functions to be implemented in BP but be used in CPP
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetInventoryVisibility(bool Visible);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ToggleInventoryVisibility();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	bool ToggleMenuVisibility();
};
