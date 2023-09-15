// Fill out your copyright notice in the Description page of Project Settings.

#include "TextStylePicker/ZZTextStylePicker.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "Engine/DataTable.h"
#include "UI/RichTextBlock/ZZRichTextDefines.h"
#include "PropertyEditorModule.h"
#include "PropertyCustomizationHelpers.h"
#include "IPropertyTypeCustomization.h"

#define LOCTEXT_NAMESPACE "TextStylePicker"

TSharedRef<IPropertyTypeCustomization> FZZTextStylePicker::MakeInstance()
{
    return MakeShareable(new FZZTextStylePicker());
}

void FZZTextStylePicker::CustomizeHeader(TSharedRef<IPropertyHandle> InStructPropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& StructCustomizationUtils)
{

    DataTablePropertyHandle = InStructPropertyHandle->GetChildHandle("DataTable");
    RowNamePropertyHandle = InStructPropertyHandle->GetChildHandle("RowName");
    RowDefaultPropertyHandle = InStructPropertyHandle->GetChildHandle("RowDefault");

    if (DataTablePropertyHandle)
    {
        FSimpleDelegate OnDataTableChanged;
        OnDataTableChanged.BindLambda([=] {
            if (RowNamePropertyHandle.IsValid() && RowNamePropertyHandle->IsValidHandle())
            {
                RowNamePropertyHandle->SetValue(FName(""));
            }
            if (RowDefaultPropertyHandle.IsValid() && RowDefaultPropertyHandle->IsValidHandle())
            {
                RowDefaultPropertyHandle->SetValue(FName(""));
            }
        });
        DataTablePropertyHandle->SetOnPropertyValueChanged(OnDataTableChanged);
    }

    FPropertyComboBoxArgs ComboArgsRowNames(RowNamePropertyHandle,
    FOnGetPropertyComboBoxStrings::CreateSP(this, &FZZTextStylePicker::OnGetRowStrings),
    FOnGetPropertyComboBoxValue::CreateSP(this, &FZZTextStylePicker::OnGetRowValueString));


    FPropertyComboBoxArgs ComboArgsDefault(RowDefaultPropertyHandle,
        FOnGetPropertyComboBoxStrings::CreateSP(this, &FZZTextStylePicker::OnGetRowStringsDefaults),
        FOnGetPropertyComboBoxValue::CreateSP(this, &FZZTextStylePicker::OnGetRowValueStringDefaults));
    

    StructPropertyHandle = InStructPropertyHandle;
    HeaderRow
    .NameContent()
    [
        InStructPropertyHandle->CreatePropertyNameWidget(FText::GetEmpty(), FText::GetEmpty(), false)
    ]
    .ValueContent().MinDesiredWidth(500)
    [        
        SNew(SVerticalBox)
        + SVerticalBox::Slot()
        .Padding(0.0f, 10.0f, 0.0f, 0.0f)
        [
            SNew(STextBlock)
            .Text(LOCTEXT("DataTable", "Data Style"))
        ]
        + SVerticalBox::Slot()
        .Padding(0.0f, 2.0f)
        [
            SNew(SObjectPropertyEntryBox)
            .PropertyHandle(DataTablePropertyHandle)
            .AllowedClass(UDataTable::StaticClass())
        ]
        +SVerticalBox::Slot()
        .Padding(0.0f, 8.0f, 0.0, 0.0f)
        .AutoHeight()
        [
            SNew(SHorizontalBox)
            +SHorizontalBox::Slot()
            [            
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(STextBlock)
                    .Text(LOCTEXT("BaseStyle", "Base style:"))
                ]
                + SVerticalBox::Slot()
                 .Padding(0.0f, 4.0f, 0.0f, 0.0f)
                 .AutoHeight()
                [
                    PropertyCustomizationHelpers::MakePropertyComboBox(ComboArgsRowNames)
                ]

            ]
            + SHorizontalBox::Slot()
            [
                SNew(SVerticalBox)
                + SVerticalBox::Slot()
                .AutoHeight()
                [
                    SNew(STextBlock)
                    .Text(LOCTEXT("DefaultStyle", "Default style:"))
                ]
                + SVerticalBox::Slot()
                .Padding(0.0f, 4.0f, 0.0f, 0.0f)
                .AutoHeight()
                [
                    PropertyCustomizationHelpers::MakePropertyComboBox(ComboArgsDefault)
                ]
            ]
       ]        
    ];
}
void FZZTextStylePicker::CustomizeChildren(TSharedRef<IPropertyHandle> InStructPropertyHandle, class IDetailChildrenBuilder& StructBuilder, IPropertyTypeCustomizationUtils & StructCustomizationUtils)
{
}


void FZZTextStylePicker::OnGetRowStrings(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems)
{
    if (!DataTablePropertyHandle.IsValid() || !DataTablePropertyHandle->IsValidHandle())
    {
        return;
    }
    UObject* SourceDataTable = nullptr;
    const FPropertyAccess::Result TableResult = DataTablePropertyHandle->GetValue(SourceDataTable);
    if (TableResult != FPropertyAccess::Result::Success)
    {
        return;
    }
    UDataTable* DataTable = Cast<UDataTable>(SourceDataTable);
    if (!DataTable)
    {
        return;
    }
    TArray<FName> AllRowsStyles;
    for (TMap<FName, uint8*>::TConstIterator Iterator(DataTable->GetRowMap()); Iterator; ++Iterator)
    {
        AllRowsStyles.Add(Iterator.Key());
    }
    for (const FName& RowName : AllRowsStyles)
    {
        OutStrings.Add(MakeShared<FString>(RowName.ToString()));
        OutRestrictedItems.Add(false);
    }

}
FString FZZTextStylePicker::OnGetRowValueString() const
{
    if (!RowNamePropertyHandle.IsValid() || !RowNamePropertyHandle->IsValidHandle())
    {
        return FString();
    }

    FName RowNameValue;
    const FPropertyAccess::Result RowResult = RowNamePropertyHandle->GetValue(RowNameValue);

    if (RowResult == FPropertyAccess::Result::Success)
    {
        if (RowNameValue.IsNone())
        {
            return FString("None");
        }
        return RowNameValue.ToString();
    }
    else 
    {
        //Multiple / Fail
        return FString("None");
    }
}
void FZZTextStylePicker::OnGetRowStringsDefaults(TArray< TSharedPtr<FString> >& OutStrings, TArray<TSharedPtr<SToolTip>>& OutToolTips, TArray<bool>& OutRestrictedItems)
{
    if (!DataTablePropertyHandle.IsValid() || !DataTablePropertyHandle->IsValidHandle())
    {
        return;
    }
    if (!RowNamePropertyHandle.IsValid() || !RowNamePropertyHandle->IsValidHandle())
    {
        return;
    }

    UObject* SourceDataTable = nullptr;
    const FPropertyAccess::Result TableResult = DataTablePropertyHandle->GetValue(SourceDataTable);
    if (TableResult != FPropertyAccess::Result::Success)
    {
        return;
    }
    UDataTable* DataTable = Cast<UDataTable>(SourceDataTable);
    if (!DataTable)
    {
        return;
    }
    FName RowNameMain = FName(OnGetRowValueString());
    if (RowNameMain.IsNone())
    {
        return;
    }
    FTextStylesData* StyleRow = DataTable->FindRow<FTextStylesData>(RowNameMain, FString("FZZTextStylePicker::OnGetRowStringsDefaults"));

    TArray<FName> AllRowsStyles;
    StyleRow->AdditionalStyles.GenerateKeyArray(AllRowsStyles);

    OutStrings.Add(MakeShared<FString>("None"));
    OutRestrictedItems.Add(false);

    for (const FName& RowName : AllRowsStyles)
    {
        OutStrings.Add(MakeShared<FString>(RowName.ToString()));
        OutRestrictedItems.Add(false);
    }
}
FString FZZTextStylePicker::OnGetRowValueStringDefaults() const
{
    if (!RowNamePropertyHandle.IsValid() || !RowNamePropertyHandle->IsValidHandle())
    {
        return FString("Default");
    }
    if (!RowDefaultPropertyHandle.IsValid() || !RowDefaultPropertyHandle->IsValidHandle())
    {
        return FString("Default");
    }

    FName RowNameValue;
    const FPropertyAccess::Result RowResult = RowDefaultPropertyHandle->GetValue(RowNameValue);

    if (RowResult == FPropertyAccess::Result::Success)
    {
        if (RowNameValue.IsNone())
        {
            return FString("None");
        }
        return RowNameValue.ToString();
    }
    else
    {
        //Multiple / Fail
        return FString("None");
    }
}
#undef LOCTEXT_NAMESPACE