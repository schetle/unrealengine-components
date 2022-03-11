/*
Copyright (c) 2022 Ryan Shetley

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "ControllerCameraComponent.h"

// Sets default values for this component's properties
UControllerCameraComponent::UControllerCameraComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UControllerCameraComponent::Attach(APawn* Pawn, APlayerController* PlayerController)
{
	ensure(!actor);  // If we're calling Attach and already have an actor, then we haven't been using this correctly.
	
	// We'll detach things, just in case things haven't been cleaned up before.
	Detach();
	
	actor = Pawn;
	
	springArmComponent = CreateSpringArm(Pawn);
	cameraComponent = CreateCamera(Pawn, springArmComponent);

	PlayerController->SetViewTarget(Pawn);
}

void UControllerCameraComponent::Detach()
{
	if (cameraComponent)
	{
		cameraComponent->DestroyComponent();
		cameraComponent = nullptr;
	}

	if (springArmComponent)
	{
		springArmComponent->DestroyComponent();
		springArmComponent = nullptr;
	}
	
	actor = nullptr;
}

USpringArmComponent* UControllerCameraComponent::CreateSpringArm(APawn* pawn)
{
	USpringArmComponent* newSpringArm = Cast<USpringArmComponent>(pawn->AddComponentByClass(USpringArmComponent::StaticClass(), false, FTransform(), false));
	verify(newSpringArm);
	newSpringArm->TargetArmLength = SpringArmLength;
	newSpringArm->bUsePawnControlRotation = bUsePawnControlRotation;
	
	newSpringArm->AttachToComponent(pawn->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	return newSpringArm;
}

UCameraComponent* UControllerCameraComponent::CreateCamera(APawn* pawn, USpringArmComponent* springArm)
{
	UCameraComponent* newCamera = Cast<UCameraComponent>(pawn->AddComponentByClass(UCameraComponent::StaticClass(), false, FTransform(), false));
	verify(newCamera);
	newCamera->AttachToComponent(springArm, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	return newCamera;
}

