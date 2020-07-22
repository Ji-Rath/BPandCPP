// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IsInteractable.h"
#include "ItemStructure.h"
#include "ItemCPP.generated.h"

UCLASS()
class CPPANDBP_API AItemCPP : public AActor , public IIsInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemCPP();

	UPROPERTY(EditAnywhere, Category = "Item")
	FItem Item;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation() override;

	UFUNCTION(BlueprintCallable, Category = "Item")
	FItem GetItem();

	UFUNCTION(BlueprintCallable, Category = "Item")
	FName GetName();

	UFUNCTION(BlueprintCallable, Category = "Item")
	FName GetDescription();
};
