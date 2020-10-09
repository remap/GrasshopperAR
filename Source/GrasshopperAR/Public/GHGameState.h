// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GHGameState.generated.h"

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API AGHGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable, NetMulticast, reliable)
    void Mcast_ServerWillStreamLevel(bool willLoad, const FString& levelName);
    
    UFUNCTION(BlueprintCallable, NetMulticast, reliable)
    void Mcast_ServerDidStreamLevel(bool didLoad, const FString& levelName);
private:
    ULevelStreaming *serverLevelStreaming_;
    bool shouldLoad_;
    FName serverStreamedLevel_;
    
    void serverStreamLevelCounteract();
    
};
