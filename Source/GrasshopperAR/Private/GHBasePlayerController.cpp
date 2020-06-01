// Fill out your copyright notice in the Description page of Project Settings.


#include "GHBasePlayerController.h"
#include "DDLog.h"
#include "GameFramework/GameStateBase.h"

AGHBasePlayerController::AGHBasePlayerController()
: APlayerController()
{
    DLOG_DEBUG("BASE PLAYER CONTROLLER DEFAULT CTOR");
    bReplicates = true;
}

AGHBasePlayerController::AGHBasePlayerController(const FObjectInitializer& ObjectInitializer)
: APlayerController(ObjectInitializer)
{
    DLOG_DEBUG("BASE PLAYER CONTROLLER CTOR");
}

AGHBasePlayerController::~AGHBasePlayerController()
{
    DLOG_DEBUG("PLAYER CONTROLLER DTOR AGHBasePlayerController::~AGHBasePlayerController()");
}

AGHPlayerState* AGHBasePlayerController::getPlayerState()
{
    return Cast<AGHPlayerState>(GetPawn()->GetPlayerState());
}

void
AGHBasePlayerController::SetNewPlayerName(FString name)
{
    if (!name.IsEmpty())
    {
        ServerSetPlayerName(getPlayerState()->GetPlayerName(),
                            name.Mid(0,15));
    }
}

void
AGHBasePlayerController::ServerSetPlayerName_Implementation(const FString& currentName, const FString& newName)
{
    for (auto& playerState : GetWorld()->GetGameState()->PlayerArray)
    {
        if (playerState->GetPlayerName().Equals(currentName))
        {
            playerState->SetPlayerName(newName);
            break;
        }
    }
}
