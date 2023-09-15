// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RichTextBlock/ZZRichTextDefines.h"

// Add default functionality here for any IZZRichTextDefines functions that are not pure virtual.
bool FTextStylePicker::operator==(FTextStylePicker const& Other) const
{
	return DataTable == Other.DataTable && RowName == Other.RowName && RowDefault == Other.RowDefault;
}

bool FTextStylePicker::operator != (FTextStylePicker const& Other) const
{
	return DataTable != Other.DataTable || RowName != Other.RowName || RowDefault != Other.RowDefault;
}