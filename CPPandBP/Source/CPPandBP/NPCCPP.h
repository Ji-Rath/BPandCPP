// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IsInteractable.h"
#include "NPCCPP.generated.h"


UCLASS()
class CPPANDBP_API ANPCCPP : public ACharacter, public IIsInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCPP();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	TArray<FString> NPCText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int> StopPoints;

	UPROPERTY(BlueprintReadOnly)
	bool Talking;

	UPROPERTY(EditAnywhere)
	FString Name;

	UFUNCTION(BlueprintCallable)
	FString GetName();

	UFUNCTION(BlueprintCallable)
	FString GetLine(int TextIndex);

	UFUNCTION(BlueprintCallable)
	bool IsTalking();

	UFUNCTION(BlueprintCallable)
	void SetTalking(bool Talk);

	UFUNCTION(BlueprintCallable)
	int GetLineCount();

};
