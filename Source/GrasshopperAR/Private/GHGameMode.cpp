// Fill out your copyright notice in the Description page of Project Settings.


#include "GHGameMode.h"
#include "DDLog.h"
#include "DDHelpers.h"
#include "GHBasePlayerController.h"

#include <InputCoreTypes.h>
#include <Kismet/GameplayStatics.h>

AGHGameMode::AGHGameMode(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
    PlayerControllerClass = AGHBasePlayerController::StaticClass();
}

APlayerController*
AGHGameMode::SpawnPlayerController(ENetRole InRemoteRole, const FString & Options)
{
    DLOG_TRACE("spawn options {}", TCHAR_TO_ANSI(*Options));
    FString platform = UGameplayStatics::GetPlatformName();
    APlayerController *controller;
    
    if (platform.Equals(TEXT("Android")) ||
        platform.Equals(TEXT("IOS")))
    {
        controller = SpawnPlayerControllerCommon(InRemoteRole, FVector(), FRotator(), arPlayerController);
    }
    else
    {
        controller = SpawnPlayerControllerCommon(InRemoteRole, FVector(), FRotator(), vrPlayerController);
    }
    
    return controller;
}

UClass*
AGHGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    AGHBasePlayerController *ghPlayerController = Cast<AGHBasePlayerController>(InController);
    
    if (ghPlayerController)
    {
        return ghPlayerController->ghPawnClass;
    }
    else
        DLOG_ERROR("couldn't get a pawn class from player controller obbject");
    
    return NULL;
}
