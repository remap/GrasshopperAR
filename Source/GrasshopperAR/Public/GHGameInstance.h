// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GHGameInstance.generated.h"

UENUM()
enum ConnectionStatus
{
  Disconnected  UMETA(DisplayName = "Disconnected"),
  Connecting    UMETA(DisplayName = "Connecting"),
  Connected     UMETA(DisplayName = "Connected"),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameInstanceConnectionStatusUpdate, ConnectionStatus, oldStatus, ConnectionStatus, newStatus);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameInstancePlayerStateUpdate, bool, oldIsActive, bool, newIsActive);
/**
 * Custom implementation for Game Instance class
 */
UCLASS()
class GRASSHOPPERAR_API UGHGameInstance : public UGameInstance
{
    GENERATED_BODY()
public:
    UGHGameInstance();
    UGHGameInstance(const FObjectInitializer& ObjectInitializer);
    ~UGHGameInstance();
    
    void setNetworkVersionOverride();
    bool HandleOpenCommand(const TCHAR * Cmd,
                           FOutputDevice & Ar,
                           UWorld * InWorld) override;
    void LoadComplete(const float LoadTime,
                      const FString & MapName) override;
    
    UFUNCTION(BlueprintCallable)
    FString getCodeVersion() const;
    
    UFUNCTION(BlueprintCallable)
    FString getBranchName() const;
    
    UFUNCTION(BlueprintCallable)
    ConnectionStatus getConnectionStatus() const;
    
    UFUNCTION(BlueprintCallable)
    void setConnectionStatus(ConnectionStatus status);
    
    UPROPERTY(BlueprintAssignable)
    FGameInstanceConnectionStatusUpdate OnConnectionStatusUpdated;
    
    UPROPERTY(BlueprintAssignable)
    FGameInstancePlayerStateUpdate OnPlayerStateUpdated;

    UFUNCTION(BlueprintCallable)
    void notifyPlayerStateUpdate(bool oldIsActive, bool newIsActive);
    
private:
    static uint32 getNetworkVersionGrasshopper();
    ConnectionStatus connectionStatus_;
	
    void updateConnectionStatus(ConnectionStatus newStatus);
};
