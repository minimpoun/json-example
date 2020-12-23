// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "JsonExampleGameModeBase.generated.h"

USTRUCT()
struct FExampleStruct
{
	GENERATED_BODY()

public:

	FExampleStruct(){}

	FExampleStruct(FString InMyString, int32 InMyInt, bool InMyBool)
		: MyString(InMyString)
		, MyInt(InMyInt)
		, MyBool(InMyBool)
	{}

	UPROPERTY()
	FString MyString;

	UPROPERTY()
	int32 MyInt;

	UPROPERTY()
	bool MyBool;
};

USTRUCT()
struct FArrayStruct
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString Prop;

};

USTRUCT()
struct FContainerStruct
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FArrayStruct> StructArray;
};

/**
 * 
 */
UCLASS()
class JSONEXAMPLE_API AJsonExampleGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable)
	FString K2_ToString();

	UFUNCTION(BlueprintCallable)
	void TestFunctions();

	FString ContainerStructToString(const FContainerStruct& InStruct);
	FContainerStruct StringToContainerStruct(const FString& InString);

	template<typename ContentType>
	FString FromStruct(const ContentType& Struct)
	{
		FString Out;
		if (!FJsonObjectConverter::UStructToJsonObjectString(Struct, Out))
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to convert a struct into a string"));
			return TEXT("ERROR");
		}

		return Out;
	}

	template<typename ContentType>
	ContentType ToStruct(const FString& FromString)
	{
		if (!FromString.IsEmpty())
		{
			ContentType Out;
			if (!FJsonObjectConverter::JsonObjectStringToUStruct(FromString, &Out, 0, 0))
			{
				UE_LOG(LogTemp, Warning, TEXT("Failed to convert %s to a USTRUCT. Make sure the struct contains the required properties"), *FromString);
				return Out;
			}

			return Out;
		}

		UE_LOG(LogTemp, Warning, TEXT("The FromString was empty"));
		return ContentType();
	}

private:

	UPROPERTY()
	FString StructString;

	FTimerHandle Callback_TimerHandle;

	UFUNCTION()
	void Callback();
};
