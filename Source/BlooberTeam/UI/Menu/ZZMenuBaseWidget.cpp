// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Menu/ZZMenuBaseWidget.h"

void UZZMenuBaseWidget::ClearDelegates()
{
	OnOpenMenu.Clear();
	OnCloseMenu.Clear();
}