// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemCPP.h"

// Sets default values
AItemCPP::AItemCPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Item = FItem();

}

// Called when the game starts or when spawned
void AItemCPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AItemCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemCPP::Interact_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("Interacted function ran from item!"))
}

FItem AItemCPP::GetItem()
{
	return Item;
}

FName AItemCPP::GetName()
{
	return Item.Name;
}

FName AItemCPP::GetDescription()
{
	return Item.Description;
}

