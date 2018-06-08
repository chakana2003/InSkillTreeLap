// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "ConstructorHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Basic/WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Engine/StaticMesh.h"
#include "TimerManager.h"
#include "Basic/ShootCameraShake.h"
#include "Basic/BulletDamageType.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "Battle/BattlePC.h"
#include "Components/PawnNoiseEmitterComponent.h"
#include "Item/MasterItem.h"
#include "UI/ItemTooltipWidgetBase.h"
#include "Components/TextBlock.h"
#include "Item/ItemDataTableComponent.h"
#include "UI/ItemSlotWidgetBase.h"
#include "UI/InventoryWidgetBase.h"

// Sets default values
ABattleCharacter::ABattleCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ī�޶� �������� ����
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	//������ �� ��ġ ����
	SpringArm->SetRelativeLocation(FVector(0, 30, 70));
	//������ �� ���� ����
	SpringArm->TargetArmLength = 150.0f;

	//ī�޶� ����
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	//���� �޽� ������Ʈ ����
	Weapon = CreateDefaultSubobject<UWeaponComponent>(TEXT("Weapon"));
	//���Ͽ� ���� �ϱ�
	Weapon->SetupAttachment(GetMesh(), TEXT("RHandWeapon"));
	//�⺻ �޽� �̵�
	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -88.0f), FRotator(0, -90, 0));

	//���������� ���� ȸ������ ȸ�� ��Ŵ
	SpringArm->bUsePawnControlRotation = true;

	//�ִϸ��̼��� �ִϸ��̼� �������Ʈ�� ����ϴ°����� ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	//�ִϸ��̼� �������Ʈ Ŭ���� �ε�, �ִ� �������Ʈ�� �ڿ� _C
	static ConstructorHelpers::FClassFinder<UAnimInstance> Anim_Class(TEXT("AnimBlueprint'/Game/Blueprints/Player/Animations/ABP_Male.ABP_Male_C'"));
	if (Anim_Class.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(Anim_Class.Class);
	}

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	GetCharacterMovement()->MaxWalkSpeedCrouched = WalkSpeed;


	NormalSpringArmPosition = SpringArm->GetRelativeTransform().GetLocation();
	CrouchSpringArmPosition = FVector(NormalSpringArmPosition.X, NormalSpringArmPosition.Y, NormalSpringArmPosition.Z - 40);
	ProneSpringArmPosition = FVector(100, NormalSpringArmPosition.Y, NormalSpringArmPosition.Z - 100);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_Explosion(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_MF.P_AssaultRifle_MF'"));
	if (P_Explosion.Succeeded())
	{
		Explosion = P_Explosion.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_HitEffect(TEXT("ParticleSystem'/Game/Effects/P_AssaultRifle_IH.P_AssaultRifle_IH'"));
	if (P_HitEffect.Succeeded())
	{
		HitEffect = P_HitEffect.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> S_Explosion(TEXT("SoundCue'/Game/Sound/Weapons/SMG_Thompson/Cue_Thompson_Shot.Cue_Thompson_Shot'"));
	if (S_Explosion.Succeeded())
	{
		ExplosionSound = S_Explosion.Object;
	}

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_BloodEffect(TEXT("ParticleSystem'/Game/Effects/P_body_bullet_impact.P_body_bullet_impact'"));
	if (P_BloodEffect.Succeeded())
	{
		BloodEffect = P_BloodEffect.Object;
	}


	static ConstructorHelpers::FObjectFinder<UAnimMontage> Anim_Dead(TEXT("AnimMontage'/Game/Male_Grunt/Animations/Death_1_Montage.Death_1_Montage'"));
	if (Anim_Dead.Succeeded())
	{
		DeadAnimation = Anim_Dead.Object;
	}

	Tags.Add(FName(TEXT("Player")));

	NoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
}

// Called when the game starts or when spawned
void ABattleCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHP = MaxHP;

	GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
}

// Called every frame
void ABattleCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogClass, Warning, TEXT("%f"), SpringArm->GetComponentLocation().Z);

	if (bIsSprint && GetCharacterMovement()->Velocity.SizeSquared() == 0)
	{
		bIsSprint = false;
	}

}

// Called to bind functionality to input
void ABattleCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABattleCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABattleCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABattleCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABattleCharacter::MoveForward);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &ABattleCharacter::TryCrouch);
	PlayerInputComponent->BindAction(TEXT("Ironsight"), IE_Pressed, this, &ABattleCharacter::TryIronsight);
	PlayerInputComponent->BindAction(TEXT("Prone"), IE_Pressed, this, &ABattleCharacter::TryProne);

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &ABattleCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &ABattleCharacter::UnSprint);

	PlayerInputComponent->BindAction(TEXT("LookAround"), IE_Pressed, this, &ABattleCharacter::LookAround);
	PlayerInputComponent->BindAction(TEXT("LookAround"), IE_Released, this, &ABattleCharacter::UndoLookAround);


	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ABattleCharacter::StartFire);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ABattleCharacter::StopFire);

	PlayerInputComponent->BindAction(TEXT("ItemGet"), IE_Released, this, &ABattleCharacter::ItemGet);
	PlayerInputComponent->BindAction(TEXT("Inventory"), IE_Released, this, &ABattleCharacter::Inventory);

}

void ABattleCharacter::ItemGet()
{
	AMasterItem* PickupItem = GetClosestItem();
	if (PickupItem && !PickupItem->IsPendingKill())
	{
		RemovePickupItemList(PickupItem);
		ABattlePC* PC = Cast<ABattlePC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PC)
		{
			UItemSlotWidgetBase* Slot = PC->InventoryWidget->GetSameIDSlot(PickupItem->ItemIndex);
			if (Slot)
			{
				Slot->AddItemCount(PickupItem->ItemCount);
				PickupItem->Destroy();
				ViewItemTooltip();
			}
			else
			{
				UItemSlotWidgetBase* Slot = PC->InventoryWidget->GetEmptySlot();
				if (Slot)
				{
					Slot->SetItem(PickupItem->ItemIndex);
					PickupItem->Destroy();
					ViewItemTooltip();
				}
				else
				{
					UE_LOG(LogClass, Warning, TEXT("Inventory full."))
				}
			}
		}
	}
}

void ABattleCharacter::Inventory()
{
	ABattlePC* PC = Cast<ABattlePC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC)
	{
		PC->ToggleInventory();
	}
}

AMasterItem* ABattleCharacter::GetClosestItem()
{
	AMasterItem* ClosestItem = nullptr;
	float Min = 9999999999.9f;

	for (auto Item : CanPickupList)
	{
		float Distance = FVector::Distance(Item->GetActorLocation(), GetActorLocation());
		if (Min > Distance)
		{
			Min = Distance;
			ClosestItem = Item;
		}
	}

	return ClosestItem;
}

void ABattleCharacter::TryIronsight()
{
	if (bIsSprint)
	{
		return;
	}

	bIsIronsight = bIsIronsight ? false : true;

	if (!bIsIronsight)
	{
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	}
}


void ABattleCharacter::TryCrouch()
{
	if (bIsProning) //���帮�� �߿��� ���� ��ȭ �ȵ�
	{
		return;
	}

	if (CanCrouch() && !bIsSprint && !bIsProne) //��������
	{
		Crouch();
	}
	else if (bIsProne) //��� �ٴҶ�
	{
		bIsProne = false;
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void ABattleCharacter::Turn(float Value)
{
	if (Value != 0.0)
	{
		AddControllerYawInput(Value);
	}
}

void ABattleCharacter::LookUp(float Value)
{
	if (Value != 0.0)
	{
		AddControllerPitchInput(-Value);
	}
}

void ABattleCharacter::MoveRight(float Value)
{
	if (Value != 0.0 && !bIsSprint && !bIsProning)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void ABattleCharacter::MoveForward(float Value)
{
	if (Value != 0.0 && !bIsProning)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

FRotator ABattleCharacter::GetAimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}

void ABattleCharacter::Sprint()
{
	if (!bIsCrouched && !bIsIronsight && !bIsProne && !bIsProning &&
		!bIsFire && GetCharacterMovement()->Velocity.Size() > 0)
	{
		bIsSprint = true;
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}
}

void ABattleCharacter::UnSprint()
{
	if (bIsSprint)
	{
		bIsSprint = false;
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
	}
}

void ABattleCharacter::LookAround()
{
	if (!bIsIronsight)
	{
		bUseControllerRotationYaw = false;
	}

}

void ABattleCharacter::UndoLookAround()
{
	bUseControllerRotationYaw = true;
}

void ABattleCharacter::TryProne()
{
	if (bIsProning)
	{
		return;
	}

	if (!bIsSprint && !bIsProne)
	{
		bIsProne = true;
		UnCrouch();
		GetCharacterMovement()->MaxWalkSpeed = ProneSpeed;
	}
	else if (bIsProne)
	{
		bIsProne = false;
		GetCharacterMovement()->MaxWalkSpeed = JogSpeed;
		UnCrouch();
	}
}

void ABattleCharacter::StartFire()
{
	if (!bIsSprint && !bIsProning)
	{
		bIsFire = true;
		OnShot();
	}
}

void ABattleCharacter::StopFire()
{
	bIsFire = false;
	//GetWorldTimerManager().ClearTimer(ShootTimeHandle);
}

void ABattleCharacter::OnShot()
{
	if (!bIsFire)
	{
		return;
	}

	FVector CameraLocation;
	FRotator CameraRotation;

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPlayerViewPoint(CameraLocation, CameraRotation);

	int SizeX;
	int SizeY;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(SizeX, SizeY);

	FVector WorldLocation;
	FVector WorldDirection;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectScreenPositionToWorld(SizeX / 2, SizeY / 2, WorldLocation, WorldDirection);

	FVector TraceStart = CameraLocation;
	FVector TraceEnd = CameraLocation + (WorldDirection * 80000.0f);

	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	TArray<AActor*> IgnoreObjects;
	FHitResult OutHit;

	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_PhysicsBody));
	IgnoreObjects.Add(this);


	//���� ���� ����
	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
		TraceStart,
		TraceEnd,
		ObjectTypes,
		false,
		IgnoreObjects,
		EDrawDebugTrace::None,
		OutHit,
		true,
		FLinearColor::Blue,
		FLinearColor::Red,
		5.0f);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, Weapon->GetSocketTransform(TEXT("MuzzleFlash")));

	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, Weapon->GetSocketTransform(TEXT("MuzzleFlash")).GetLocation());

	if (Result)
	{
		TraceStart = Weapon->GetSocketTransform(TEXT("MuzzleFlash")).GetLocation();
		FVector Dir = OutHit.Location - TraceStart;
		TraceEnd = TraceStart + (Dir * 2.0f);

		bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(),
			TraceStart,
			TraceEnd,
			ObjectTypes,
			false,
			IgnoreObjects,
			EDrawDebugTrace::None,
			OutHit,
			true,
			FLinearColor::Green,
			FLinearColor::Green,
			5.0f);
		if (Result)
		{
			//UGameplayStatics::ApplyDamage(OutHit.GetActor(),
			//	0.0f,
			//	UGameplayStatics::GetPlayerController(GetWorld(), 0),
			//	this,
			//	UBulletDamageType::StaticClass()
			//);

			//UGameplayStatics::ApplyRadialDamage(GetWorld(),
			//	30.0f,
			//	OutHit.ImpactPoint,
			//	300.0f,
			//	UBulletDamageType::StaticClass(),
			//	IgnoreObjects,
			//	this,
			//	UGameplayStatics::GetPlayerController(GetWorld(), 0),
			//	false);

			UGameplayStatics::ApplyPointDamage(OutHit.GetActor(),
				30.0f,
				TraceEnd - TraceStart,
				OutHit,
				UGameplayStatics::GetPlayerController(GetWorld(), 0),
				this,
				UBulletDamageType::StaticClass()
			);

			APawn* Pawn = Cast<APawn>(OutHit.GetActor());
			if (Pawn)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BloodEffect, OutHit.Location, FRotator::ZeroRotator);
			}
			else
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, OutHit.Location, FRotator::ZeroRotator);
			}

			NoiseEmitter->MakeNoise(this, 1.0f, OutHit.Location);
			NoiseEmitter->NoiseLifetime = 0.2f;
		}
	}

	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->PlayCameraShake(UShootCameraShake::StaticClass());

	FRotator CurrentRotation = GetControlRotation();
	CurrentRotation.Pitch += 1.0f;
	CurrentRotation.Yaw += FMath::RandRange(-0.5f, 0.5f);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->SetControlRotation(CurrentRotation);

	if (bIsFire)
	{
		GetWorldTimerManager().SetTimer(ShootTimeHandle, this, &ABattleCharacter::OnShot, 0.2f);
	}
}

float ABattleCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	if (CurrentHP <= 0)
	{
		return 0;
	}

	if (DamageEvent.IsOfType(FRadialDamageEvent::ClassID))
	{
		FRadialDamageEvent* RadialDamageEvent = (FRadialDamageEvent*)(&DamageEvent);
	}
	else if (DamageEvent.IsOfType(FPointDamageEvent::ClassID))
	{
		FPointDamageEvent* PointDamageEvent = (FPointDamageEvent*)(&DamageEvent);

		if (PointDamageEvent->HitInfo.BoneName.Compare(FName(TEXT("head"))) == 0)
		{
			UE_LOG(LogClass, Warning, TEXT("Head Shot"));
			CurrentHP = 0;
		}
		else
		{
			UE_LOG(LogClass, Warning, TEXT("Shot"));
			CurrentHP -= DamageAmount;
		}
	}
	else if (DamageEvent.IsOfType(FDamageEvent::ClassID))
	{
		CurrentHP -= DamageAmount;
	}

	if (CurrentHP <= 0)
	{
		CurrentHP = 0;
		//GetMesh()->SetSimulatePhysics(true);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		DisableInput(Cast<ABattlePC>(GetController()));

		PlayAnimMontage(DeadAnimation);
	}

	//Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return DamageAmount;
}

void ABattleCharacter::AddPickupItemList(AMasterItem * Item)
{
	if (Item && !Item->IsPendingKill())
	{
		CanPickupList.Add(Item);
	}

	ViewItemTooltip();
}

void ABattleCharacter::RemovePickupItemList(AMasterItem * Item)
{
	if (Item)
	{
		CanPickupList.Remove(Item);
	}

	ViewItemTooltip();
}

void ABattleCharacter::ViewItemTooltip()
{
	ABattlePC* PC = Cast<ABattlePC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		return;
	}

	if (CanPickupList.Num() == 0)
	{
		UE_LOG(LogClass, Warning, TEXT("ViewToopTip"));

		PC->ItemTooltip->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	//�� ����� ������ ��������
	AMasterItem* ClosestItem = GetClosestItem();
	if (ClosestItem)
	{
		PC->ItemTooltip->ItemName->SetText(FText::FromString(ClosestItem->ItemDataTable->GetItemData(ClosestItem->ItemIndex).ItemName));
		PC->ItemTooltip->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PC->ItemTooltip->SetVisibility(ESlateVisibility::Collapsed);
	}
}
