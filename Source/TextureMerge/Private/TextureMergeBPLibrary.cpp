// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
// 
// Copyright 2015 Heiko Fink, All Rights Reserved.
//
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.
// 
// Description:
// This code implements the blueprint functions that are provided by the TextureMerge Blueprint Function Library.
// 
#include "TextureMergeBPLibrary.h"
#include "TextureMerge.h"
#include "CompositeTexture.h"

UTextureMergeBPLibrary::UTextureMergeBPLibrary(const FObjectInitializer& ObjectInitializer) 
: Super(ObjectInitializer)
{

}

UCompositeTexture* UTextureMergeBPLibrary::Create(UObject* WorldContextObject, const TArray<UTexture2D*>& Layers)
{
	GEngine->ForceGarbageCollection();
	UCompositeTexture* MergedTexture = UCompositeTexture::Create(WorldContextObject, Layers);

	return MergedTexture;
}

UCompositeTexture* UTextureMergeBPLibrary::CreateWithTints(UObject* WorldContextObject, const TArray<UTexture2D*>& Layers, const TArray<FColor>& LayerTints)
{
	GEngine->ForceGarbageCollection();
	UCompositeTexture* MergedTexture = UCompositeTexture::Create(WorldContextObject, Layers, LayerTints);

	return MergedTexture;
}

UCompositeTexture* UTextureMergeBPLibrary::CreateMaterial(UObject* WorldContextObject, UMaterialInterface* ParentMaterial, FName MaterialParamName, const TArray<UTexture2D*>& Layers, UMaterialInterface*& OutputMaterial)
{
	GEngine->ForceGarbageCollection();
	if (ParentMaterial == nullptr)
	{
		const FString DefaultMatPath = "/TextureMerge/Materials/M_DefaultMergeMat.M_DefaultMergeMat";
		TSoftObjectPtr<UMaterial> MatSoftPtr = TSoftObjectPtr<UMaterial>(FSoftObjectPath(DefaultMatPath));
		UObject* LoadObj = UKismetSystemLibrary::LoadAsset_Blocking(MatSoftPtr);
		ParentMaterial = Cast<UMaterialInterface>(LoadObj);
	}
	if (MaterialParamName.IsNone())
	{
		MaterialParamName = "Main";
	}
	if (ParentMaterial == nullptr || Layers.Num() == 0) return nullptr;

	//UMaterialInterface* ParentMat = MaterialClass.Get();
	//if (ParentMat == nullptr)
	//{
	//	ParentMat = MaterialClass.LoadSynchronous();
	//}
	UMaterialInstanceDynamic* DyMat = UMaterialInstanceDynamic::Create(ParentMaterial, WorldContextObject);
	UCompositeTexture* MergedTexture = nullptr;
	if (DyMat)
	{
		MergedTexture = UCompositeTexture::Create(WorldContextObject, Layers);
		if (MergedTexture)
		{
			DyMat->SetTextureParameterValue(MaterialParamName, MergedTexture);
			OutputMaterial = DyMat;
		}
	}
	return MergedTexture;
}

UCompositeTexture* UTextureMergeBPLibrary::UpdateLayer(UCompositeTexture* RenderTarget, UTexture2D* Layer, const int32 Index)
{
	UCompositeTexture* MergedTexture = UCompositeTexture::UpdateLayer(RenderTarget, Layer, Index);

	return MergedTexture;
}

UCompositeTexture* UTextureMergeBPLibrary::UpdateAllLayers(UCompositeTexture* RenderTarget, TArray<UTexture2D*> Layers)
{
	GEngine->ForceGarbageCollection();
	UCompositeTexture* MergedTexture = UCompositeTexture::UpdateAllLayers(RenderTarget, Layers);

	return MergedTexture;
}

UCompositeTexture* UTextureMergeBPLibrary::UpdateTint(UCompositeTexture* RenderTarget, const FColor& Tint, int32 Index)
{
	UCompositeTexture* MergedTexture = UCompositeTexture::UpdateTint(RenderTarget, Tint, Index);

	return MergedTexture;
}

UCompositeTexture* UTextureMergeBPLibrary::UpdateAllTints(UCompositeTexture* RenderTarget, const TArray<FColor>& LayerTints)
{
	GEngine->ForceGarbageCollection();
	UCompositeTexture* MergedTexture = UCompositeTexture::UpdateAllTints(RenderTarget, LayerTints);

	return MergedTexture;
}
