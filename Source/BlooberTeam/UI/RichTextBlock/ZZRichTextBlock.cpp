// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RichTextBlock/ZZRichTextBlock.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateStyle.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Components/PanelWidget.h"
#include "Components/RichTextBlockDecorator.h"
#include "RenderingThread.h"
#include "Widgets/SWidget.h"
#include "UObject/Object.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Interface/ZZUIInterface.h"
#include "UI/Buttons/ZZButtonBaseWidget.h"


template< class ObjectType >
struct FDeferredDeletor : public FDeferredCleanupInterface
{
public:
	FDeferredDeletor(ObjectType* InInnerObjectToDelete)
		: InnerObjectToDelete(InInnerObjectToDelete)
	{
	}

	virtual ~FDeferredDeletor()
	{
		delete InnerObjectToDelete;
	}

private:
	ObjectType* InnerObjectToDelete;
};

template< class ObjectType >
FORCEINLINE TSharedPtr< ObjectType > MakeShareableDeferredCleanup(ObjectType* InObject)
{
	return MakeShareable(InObject, [](ObjectType* ObjectToDelete) { BeginCleanup(new FDeferredDeletor<ObjectType>(ObjectToDelete)); });
}

void UZZRichTextBlock::UpdateStyleData()
{
	if (IsDesignTime())
	{
		InstanceDecorators.Reset();
	}

	if (!StyleInstance.IsValid())
	{
		InternalRebuildStyleInstance();

		for (TSubclassOf<URichTextBlockDecorator> DecoratorClass : DecoratorClasses)
		{
			if (UClass* ResolvedClass = DecoratorClass.Get())
			{
				if (!ResolvedClass->HasAnyClassFlags(CLASS_Abstract))
				{
					URichTextBlockDecorator* Decorator = NewObject<URichTextBlockDecorator>(this, ResolvedClass);
					InstanceDecorators.Add(Decorator);
				}
			}
		}
	}
}
void UZZRichTextBlock::SetTextStyleSet(const FTextStylePicker& InTextStyleBlock)
{
	if (InTextStyleBlock != StylePicker)
	{
		StylePicker = InTextStyleBlock;
		InternalRebuildStyleInstance();
		if (MyRichTextBlock.IsValid())
		{
			MyRichTextBlock->SetDecoratorStyleSet(StyleInstance.Get());
			MyRichTextBlock->SetTextStyle(DefaultTextStyle);
		}
	}
}
void UZZRichTextBlock::InternalRebuildStyleInstance()
{
	StyleInstance = MakeShareableDeferredCleanup(new FSlateStyleSet(TEXT("RichTextStyle")));
	StylePicker.GetStyles(DefaultTextStyle, StyleInstance);
}