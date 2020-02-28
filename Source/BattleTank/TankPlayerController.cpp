// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));  
    }

        UE_LOG(LogTemp, Warning, TEXT("PlayerController possessing: %s"), *(ControlledTank->GetName()));
}

// Tick
    // Super

    void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if(!GetControlledTank()) { return; }

    FVector HitLocation; // OUT Parameter
    if(GetSightRayHitLocation(HitLocation)) // Has Side effect, it is going to line trace
    {
        // TODO Tell controlled tank to aim at this point
        // UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString()); 
    }
}
    // Get world location of linetrace through crosshair, ture if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const
{
    // Find the cross hair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);    
    FVector2D ScreenLocation = FVector2D
    (ViewportSizeX * CrossHairXLocation, ViewportSizeY *CrossHairYLocation); 

    // "De-Project" the screen position of the crosshair to a wolrd direction
    // Line trace along that look direction, and see what we hit (up to max range) 

    FVector LookDirection;

    //GetLookDirection(ScreenLocation, LookDirection);

    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
        // //Line trace
        // GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const 
{ FVector CameraWorldLocation; // To be discarded

return DeprojectScreenPositionToWorld
( ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection ); 

}