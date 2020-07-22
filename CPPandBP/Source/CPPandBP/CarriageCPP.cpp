// Fill out your copyright notice in the Description page of Project Settings.


#include "CarriageCPP.h"

ACarriageCPP::ACarriageCPP()
{
	PlayerPos = CreateDefaultSubobject<USceneComponent>(TEXT("Player Position"));
	PlayerPos->SetupAttachment(RootComponent);
}

