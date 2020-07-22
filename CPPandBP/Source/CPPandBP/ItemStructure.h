// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemStructure.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Description;

	FItem()
	{
		Name = FName(TEXT("NoName"));
		Description = FName(TEXT("N/A"));
	};
};

USTRUCT(BlueprintType)
struct FSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FItem Item;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Amount;

	FSlot()
	{
		Item = FItem();
		Amount = 0;
	}
};
