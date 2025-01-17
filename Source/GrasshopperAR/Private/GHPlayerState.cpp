// Fill out your copyright notice in the Description page of Project Settings.


#include "GHPlayerState.h"
#include "DDLog.h"
#include <Net/UnrealNetwork.h>
#include <GameFramework/PlayerState.h>

AGHPlayerState::AGHPlayerState()
: APlayerState()
{
    DLOG_TRACE("AGHPlayerState::AGHPlayerState()");
    init();
}


AGHPlayerState::AGHPlayerState(const FObjectInitializer& ObjectInitializer)
{
    DLOG_TRACE("AGHPlayerState::AGHPlayerState(const FObjectInitializer&)");
    init();
}

AGHPlayerState::~AGHPlayerState()
{
    DLOG_TRACE("AGHPlayerState::~AGHPlayerState()");
}

void AGHPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AGHPlayerState, isAvatarHidden);
    DOREPLIFETIME(AGHPlayerState, isGameActive);
}

void AGHPlayerState::SetIsAvatarVisibility(bool hidden)
{
    if ( hidden ^ isAvatarHidden)
    {
        isAvatarHidden = hidden;
        OnRep_IsAvatarHidden();
    }
}

void AGHPlayerState::SetIsGameActive(bool isActive)
{
    if (HasAuthority() && isActive ^ isGameActive)
    {
        isGameActive = isActive;
        OnRep_IsGameActive();
    }
}

void AGHPlayerState::OnRep_IsAvatarHidden()
{
    APawn *pawn = GetPawn();

   if (pawn)
    {
        pawn->GetRootComponent()->SetVisibility(!isAvatarHidden, true);
        OnRepNotify_IsAvatarHidden();

        DLOG_DEBUG("Avatar visibility changed for player {}",
            TCHAR_TO_ANSI(*GetPlayerName()));
    }
}

void AGHPlayerState::OnRepNotify_IsAvatarHidden_Implementation()
{
    // nothing here
}

void AGHPlayerState::OnRep_IsGameActive()
{
    OnRepNotify_IsGameActive();
}

void AGHPlayerState::OnRepNotify_IsGameActive_Implementation()
{
    // nothing here
}

void
AGHPlayerState::SetPlayerName(const FString &S)
{
    Super::SetPlayerName(S);
}

FString
AGHPlayerState::GetPlayerNameCustom() const
{
    return Super::GetPlayerNameCustom();
}

void
AGHPlayerState::init()
{
    bUseCustomPlayerNames = true;
    isAvatarHidden = false;
}

void
AGHPlayerState::OnRep_PlayerName()
{
    Super::OnRep_PlayerName();
    OnRepNotify_PlayerName();
}

