// Fill out your copyright notice in the Description page of Project Settings.


#include "GHBasePlayerController.h"
#include "DDLog.h"
#include <Net/UnrealNetwork.h>
#include <GameFramework/PlayerState.h>

AGHBasePlayerController::AGHBasePlayerController()
: APlayerController()
{
    DLOG_DEBUG("BASE PLAYER CONTROLLER DEFAULT CTOR");
    bReplicates = true;
    isAvatarHidden = false;
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

void AGHBasePlayerController::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGHBasePlayerController, isAvatarHidden);
}

void AGHBasePlayerController::SetIsAvatarHidden(bool hidden)
{
    if (HasAuthority() && hidden ^ isAvatarHidden)
    {
        isAvatarHidden = hidden;
        
        DLOG_DEBUG("do we need to call OnRep_IsAvatarHidden() with AUTHORITY?");
        OnRep_IsAvatarHidden();
    }
}

void AGHBasePlayerController::OnRep_IsAvatarHidden()
{
//    if (!HasAuthority())
    {
        APawn *pawn = GetPawn();
        pawn->GetRootComponent()->SetVisibility(!isAvatarHidden, true);
        OnRepNotify_IsAvatarHidden();
     
        DLOG_DEBUG("Avatar visibility changed for player {}",
                   TCHAR_TO_ANSI(*PlayerState->GetPlayerName()));
    }
}

void AGHBasePlayerController::OnRepNotify_IsAvatarHidden_Implementation()
{
    // nothing here
}

void AGHBasePlayerController::TravelToMap(FString mapName)
{
    DLOG_DEBUG("Seamless ClientTravel to map {}", TCHAR_TO_ANSI(*mapName));
    ClientTravel(mapName, TRAVEL_Relative, true);
}
