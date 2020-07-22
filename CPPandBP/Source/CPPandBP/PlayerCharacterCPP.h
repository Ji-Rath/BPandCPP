// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ItemStructure.h"
#include "ItemCPP.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <CPPandBP\NPCCPP.h>
#include <MainGUICPP.h>
#include "PlayerCharacterCPP.generated.h"



UCLASS()
class CPPANDBP_API APlayerCharacterCPP : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacterCPP();

	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	TArray<FSlot> Inventory;

	UPROPERTY(BlueprintReadWrite)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UMainGUICPP* MainGUI;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	int32 InventorySize;

	UPROPERTY(BlueprintReadOnly, Category = "NPC")
	ANPCCPP* TalkingTo;

	UPROPERTY(BlueprintReadOnly, Category = "Interact")
	AActor* ViewedActor;

	UPROPERTY(BlueprintReadOnly, Category = "NPC")
	int CurrentLine;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	float ViewDistance;

	UPROPERTY(BlueprintReadOnly, Category = "NPC")
	int CharacterIndex;

	UPROPERTY(EditAnywhere, Category = "Camera")
	float CameraArmLength;

	UPROPERTY(BlueprintReadWrite, Category = "Debug")
	bool Debug;

	UFUNCTION(BlueprintCallable)
	bool CanInteract(AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddToInventory(FItem Item);

	UFUNCTION(BlueprintCallable, Category = "Interact")
	AActor* InteractInView();

	UFUNCTION(BlueprintCallable, Category = "NPC")
	void NPCInteract();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void Interaction();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void ItemInteract();

	UFUNCTION(BlueprintCallable, Category = "Interact")
	void VehicleInteract();
};
