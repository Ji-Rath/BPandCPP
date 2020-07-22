// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterCPP.h"
#include "DrawDebugHelpers.h"
#include <CPPandBP\IsInteractable.h>
#include <CPPandBP\CarriageCPP.h>

// Sets default values
APlayerCharacterCPP::APlayerCharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	Camera->SetupAttachment(SpringArm);
	SpringArm->SetupAttachment(RootComponent);

	CameraArmLength = 1500.0f;
	SpringArm->TargetArmLength = CameraArmLength;
	SpringArm->bUsePawnControlRotation = true;

	Debug = false;
	ViewedActor = nullptr;
	TalkingTo = nullptr;
	CharacterIndex = 0;
	CurrentLine = 0;
	InventorySize = 5;
	ViewDistance = 500.f;
	Inventory.Init(FSlot(), InventorySize);

}

// Called when the game starts or when spawned
void APlayerCharacterCPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	ViewedActor = InteractInView();
	
	if (Cast<ANPCCPP>(TalkingTo))
	{
		//Stop talking to NPC if out of range
		if (FVector::Distance(TalkingTo->GetActorLocation(), GetActorLocation()) > ViewDistance)
		{
			TalkingTo->SetTalking(false);
			TalkingTo = nullptr;
			CurrentLine = 0;
		}

		//Increment character index if talking to NPC
		CharacterIndex++;
	}

	
}

// Called to bind functionality to input
void APlayerCharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//Check if an actor is interactable
bool APlayerCharacterCPP::CanInteract(AActor* Actor)
{
	//Run interact function from item
	IIsInteractable* InterfaceTest = Cast<IIsInteractable>(Actor);
	if (InterfaceTest)
	{
		return true;
		//InterfaceTest->Execute_Interact(Actor);
	}
	return false;
}

//Add specified item to the inventory or return false if impossible
bool APlayerCharacterCPP::AddToInventory(FItem Item)
{	
	//Add specified item to inventory if empty
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		FSlot* CurrentSlot = &Inventory[i];

		//Add to stack if possible
		if (CurrentSlot->Item.Name == Item.Name)
		{
			CurrentSlot->Amount++;
			return true;
		}

		//Create new stack
		if (CurrentSlot->Amount == 0) 
		{
			CurrentSlot->Amount++;
			CurrentSlot->Item = Item;
			return true;
		}
	};

	return false;
	
	/*Print out inventory
	for (int32 j = 0; j < Inventory.Num(); j++)
	{
		FSlot CurrentSlot = Inventory[j];
		UE_LOG(LogTemp, Log, TEXT("Slot %s - Count %s - Name %s"), *FString::FromInt(j), *FString::FromInt(CurrentSlot.Amount), *CurrentSlot.Item.Name.ToString())
	};
	*/
}

AActor* APlayerCharacterCPP::InteractInView()
{
	//Draw line in front of camera
	FHitResult OutHit;
	FVector CameraAngle = Camera->GetForwardVector() * FVector(1.f, 1.f, 0.f);
	FVector PlayerPos = GetActorLocation() + (CameraAngle * 100);
	FVector InFront = PlayerPos + (ViewDistance * CameraAngle);
	FCollisionQueryParams CollisionParameters;

	bool Result = GetWorld()->LineTraceSingleByChannel(OutHit, PlayerPos, InFront, ECollisionChannel::ECC_WorldStatic , CollisionParameters);

	//Check if interactable
	if (Cast<IIsInteractable>(OutHit.GetActor()))
	{
		if (Debug)
			DrawDebugLine(GetWorld(), PlayerPos, InFront, FColor::Green, false, 1.f);

		//Return interactable object
		return OutHit.GetActor();
	}
	else
	{
		if (Debug)
		{
			if (Result)
				DrawDebugLine(GetWorld(), PlayerPos, InFront, FColor::Yellow, false, 1.f);
			else
				DrawDebugLine(GetWorld(), PlayerPos, InFront, FColor::Red, false, 1.f);
		}
	}

	//Return nullptr if not interactable
	return nullptr;
}

//Called when the player presses the interact button on an NPC
void APlayerCharacterCPP::NPCInteract()
{
	ANPCCPP* NPC = Cast<ANPCCPP>(ViewedActor);

	//Talk to NPC if possible
	if (TalkingTo == nullptr)
	{
		if (NPC != nullptr)
		{
			TalkingTo = NPC;
			TalkingTo->SetTalking(true);
			CharacterIndex = 0;
		}
	}
	else
	{
		CharacterIndex = 0;

		//Increment line or end conversation if no more lines
		if (CurrentLine < (TalkingTo->GetLineCount()-1))
		{
			CurrentLine++;
		}
		else
		{
			TalkingTo->SetTalking(false);
			TalkingTo = nullptr;
			CurrentLine = 0;
		}
	}
}

//General interact function
void APlayerCharacterCPP::Interaction()
{
	if (Cast<ANPCCPP>(ViewedActor) || Cast<ANPCCPP>(TalkingTo))
	{
		NPCInteract();
	}
	if (Cast<AItemCPP>(ViewedActor))
	{
		ItemInteract();
	}
	if (Cast<ACarriageCPP>(ViewedActor))
	{
		VehicleInteract();
	}
}

//Item interaction
void APlayerCharacterCPP::ItemInteract()
{
	AItemCPP* Item = Cast<AItemCPP>(ViewedActor);
	if (Item != nullptr)
	{
		bool Added = AddToInventory(Item->GetItem());
		if (Added)
		{
			Item->Destroy();
			MainGUI->SetInventoryVisibility(true);
		}
	}
}

void APlayerCharacterCPP::VehicleInteract()
{

	APawn* VehiclePawn = Cast<APawn>(ViewedActor);
	ACarriageCPP* Vehicle = Cast<ACarriageCPP>(ViewedActor);
	TeleportTo(Vehicle->PlayerPos->GetComponentLocation(), VehiclePawn->GetActorRotation(), false, true);
	AttachToComponent(Vehicle->PlayerPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	GetController()->Possess(VehiclePawn);
}

