#include "JsonExampleGameModeBase.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "Serialization/JsonReader.h"
#include "Dom/JsonObject.h"

FString AJsonExampleGameModeBase::K2_ToString()
{
	return FromStruct<FExampleStruct>(FExampleStruct("Test string", 42, true));
}

void AJsonExampleGameModeBase::TestFunctions()
{
	FExampleStruct MyStruct("this is my struct", 43, true);
	if (GEngine)
	{
		StructString = FromStruct<FExampleStruct>(MyStruct);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, StructString);
		GetWorld()->GetTimerManager().SetTimer(Callback_TimerHandle, this, &ThisClass::Callback, 15.f, false);
	}
}

FString AJsonExampleGameModeBase::ContainerStructToString(const FContainerStruct& InStruct)
{
	return "";
}

FContainerStruct AJsonExampleGameModeBase::StringToContainerStruct(const FString& InString)
{
	TArray<FContainerStruct> StructData;
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(InString);
	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> ObjArray = JsonObject->GetArrayField("StructArray");
		FJsonObjectConverter::JsonArrayToUStruct(ObjArray, &StructData, 0, 0);
	}

	return StructData[0];
}

void AJsonExampleGameModeBase::Callback()
{
	if (GEngine)
	{
		FExampleStruct MyStruct("different string", 21, false);
		MyStruct = ToStruct<FExampleStruct>(StructString);
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, MyStruct.MyString);
	}
}
