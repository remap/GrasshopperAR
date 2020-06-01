// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GHPlayerState.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "GHBasePlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToggleMasterUiDelegate);

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API AGHBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    AGHBasePlayerController();
    AGHBasePlayerController(const FObjectInitializer& ObjectInitializer);
    ~AGHBasePlayerController();
    
    UPROPERTY(EditAnywhere)
    TSubclassOf<APawn> ghPawnClass;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    APlayerStart *playerStart;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> enteredGameLevels;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> lobbyLevels;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> startTags;
    
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FToggleMasterUiDelegate OnToggleMasterUiDelegate;
    
    UFUNCTION(BlueprintCallable)
    AGHPlayerState* getPlayerState();
    
    UPROPERTY(EditAnywhere)
    FString PlayerName;
    
    // exists lobby levels and loads specified game level
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void enterGameLevel();
    
    // unloads game levels and loads lobby levels
    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
    void exitGameLevel();
    
    UFUNCTION(BlueprintCallable)
    void SetNewPlayerName(FString name);
    
    UFUNCTION(Server, Reliable, BlueprintCallable)
    void ServerSetPlayerName(const FString& currentName,
                             const FString& newName);
};
