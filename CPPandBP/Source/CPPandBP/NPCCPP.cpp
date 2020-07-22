// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCPP.h"

// Sets default values
ANPCCPP::ANPCCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Talking = false;
	Name = TEXT("");
	NPCText.Init(TEXT(""), 1);
	StopPoints.Init(-1, 1);
}

// Called when the game starts or when spawned
void ANPCCPP::BeginPlay()
{
	Super::BeginPlay(); 
}

// Called every frame
void ANPCCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANPCCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FString ANPCCPP::GetName()
{
	return Name;
}

FString ANPCCPP::GetLine(int TextIndex)
{
	if (TextIndex < (GetLineCount()))
	{
		return NPCText[TextIndex];
	}

	//UE_LOG(LogTemp, Log, TEXT("Index Check: %s, Max Index: %s"), *FString::FromInt(TextIndex), *FString::FromInt(GetLineCount()))

	return "Error!";
}

bool ANPCCPP::IsTalking()
{
	return Talking;
}

void ANPCCPP::SetTalking(bool Talk)
{
	Talking = Talk;
}

int ANPCCPP::GetLineCount()
{
	return NPCText.Num();
}


