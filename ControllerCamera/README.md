# Controller Camera

## Objective

By default, many Unreal Engine project templates include a Camera on every Character.

This simple dependentless ActorComponent is designed to spawn a SpringArm and Camera, and then attach itself to an incoming possessed character. Cleanup function included for unposessing as well.

## Usage

1. Add the ControllerCameraComponent to your PlayerController.
2. Listen to the On Possess and On UnPossess Events, and trigger Attach and Detach respectively.

![Blueprint Usage](usage.png)