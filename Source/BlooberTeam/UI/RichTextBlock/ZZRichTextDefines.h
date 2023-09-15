// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateStyle.h"
#include "Engine/DataTable.h"
#include "ZZRichTextDefines.generated.h"

USTRUCT(Blueprintable)
struct FTextStylesData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Appearance)
	TMap<FName, FTextBlockStyle> AdditionalStyles;

	UPROPERTY(EditAnywhere, Category = Appearance)
	FTextBlockStyle DefaultTextStyle;
};

USTRUCT(BlueprintType)
struct FTextStylePicker
{
	GENERATED_USTRUCT_BODY()

public:
	FTextStylePicker() : DataTable(nullptr)
	{ 
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TextStyle)
	UDataTable* DataTable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TextStyle)
	FName RowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TextStyle)
	FName RowDefault;

	bool IsNull() const
	{
		return DataTable == nullptr && RowName.IsNone();
	}

	bool GetStyles(FTextBlockStyle& DefaultStyle, TSharedPtr<class FSlateStyleSet> InStyleInstance)
	{
		if (!DataTable)
		{
			return false;
		}

		FTextStylesData* OutStyle = DataTable->FindRow<FTextStylesData>(RowName, FString("UZZRichTextBlock::RebuildStyleInstance"));
		if (!OutStyle)
		{
			return false;
		}
		if (RowDefault.IsNone())
		{
			DefaultStyle = OutStyle->DefaultTextStyle;
		}
		else if (OutStyle->AdditionalStyles.Contains(RowDefault))
		{
			DefaultStyle = *OutStyle->AdditionalStyles.Find(RowDefault);
		}
		else
		{
			DefaultStyle = OutStyle->DefaultTextStyle;
		}
		if (!OutStyle)
		{
			return false;
		}
		for (TPair<FName, FTextBlockStyle> Style : OutStyle->AdditionalStyles)
		{
			InStyleInstance->Set(Style.Key, Style.Value);
		}
		return true;
	}
	bool operator==(FTextStylePicker const& Other) const;
	bool operator!=(FTextStylePicker const& Other) const;
};