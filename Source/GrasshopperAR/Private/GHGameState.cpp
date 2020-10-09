// Fill out your copyright notice in the Description page of Project Settings.


#include "GHGameState.h"
#include "DDLog.h"
#include "GHGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"

void
AGHGameState::Mcast_ServerWillStreamLevel_Implementation(bool willLoad, const FString& levelName)
{
    if (GetNetMode() == NM_Client)
    {
        UGHGameInstance *ghGameInstance = Cast<UGHGameInstance>(GetWorld()->GetGameInstance());
        
        if (ghGameInstance->isLevelLoaded(levelName)^willLoad)
        {
            DLOG_TRACE("server will stream {} level {}. will counteract",
                       willLoad, TCHAR_TO_ANSI(*levelName));
            
            serverLevelStreaming_ = UGameplayStatics::GetStreamingLevel(this, FName(levelName));
            
            shouldLoad_ = !willLoad;
            serverStreamedLevel_ = FName(levelName);
            
            // NOTE: callbacks below don't work
            // if server loads level -- need to unload
            if (willLoad)
                serverLevelStreaming_->OnLevelLoaded.AddDynamic(this, &AGHGameState::serverStreamLevelCounteract);
            else // else -- need to load
                serverLevelStreaming_->OnLevelUnloaded.AddDynamic(this, &AGHGameState::serverStreamLevelCounteract);
        }
        else
            serverLevelStreaming_ = nullptr;
    }
}

void
AGHGameState::Mcast_ServerDidStreamLevel_Implementation(bool didLoad, const FString& levelName)
{
    if (GetNetMode() == NM_Client && serverLevelStreaming_)
        serverStreamLevelCounteract();
}

void
AGHGameState::serverStreamLevelCounteract()
{
    UWorld *wrld = GetWorld();
    FLatentActionInfo LatentInfo;
    
    if (shouldLoad_)
    {
        DLOG_TRACE("loading level {}", TCHAR_TO_ANSI(*serverStreamedLevel_.ToString()));
        
        UGameplayStatics::LoadStreamLevel(wrld, serverStreamedLevel_, true, false, LatentInfo);
        serverLevelStreaming_->OnLevelUnloaded.RemoveAll(this);
    }
    else
    {
        DLOG_TRACE("unloading level {}", TCHAR_TO_ANSI(*serverStreamedLevel_.ToString()));
                   
        UGameplayStatics::UnloadStreamLevel(wrld, serverStreamedLevel_, LatentInfo, false);
        serverLevelStreaming_->OnLevelLoaded.RemoveAll(this);
    }
    
    serverLevelStreaming_ = nullptr;
}
