// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GHPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GRASSHOPPERAR_API AGHPlayerState : public APlayerState
{
    AGHPlayerState();
    AGHPlayerState(const FObjectInitializer& ObjectInitializer);
    ~AGHPlayerState();
    
	GENERATED_BODY()
	
public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_IsAvatarHidden)
    bool isAvatarHidden;
    
    UFUNCTION(BlueprintCallable)
    void SetIsAvatarVisibility(bool isHidden);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnRepNotify_IsAvatarHidden();
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, ReplicatedUsing=OnRep_IsGameActive)
    bool isGameActive;
    
    UFUNCTION(BlueprintCallable)
    void SetIsGameActive(bool isActive);
    
    UFUNCTION(BlueprintNativeEvent)
    void OnRepNotify_IsGameActive();

    UFUNCTION(BlueprintCallable)
    void SetPlayerName(const FString & S) override;
    
    FString GetPlayerNameCustom() const override;
    
    void OnRep_PlayerName() override;
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnRepNotify_PlayerName();
    
private:

    void init();
    
    UFUNCTION()
    void OnRep_IsAvatarHidden();
    
    UFUNCTION()
    void OnRep_IsGameActive();
    
    FString playerName_;
};
