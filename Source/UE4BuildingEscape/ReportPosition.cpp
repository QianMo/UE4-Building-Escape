// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4BuildingEscape.h"
#include "ReportPosition.h"


// Sets default values for this component's properties
UReportPosition::UReportPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UReportPosition::BeginPlay()
{
	Super::BeginPlay();

	//�ҵ���������
	FString objectName = GetOwner( )->GetName( );
	//�ҵ������λ��
	FString ObjectPos = GetOwner( )->GetTransform( ).GetLocation( ).ToString();
	//log����
	UE_LOG(LogTemp, Warning, TEXT(" %s is at %s"),*objectName , *ObjectPos);
	
}


// Called every frame
void UReportPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

