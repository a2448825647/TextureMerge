#pragma once
#include "Engine.h"
#include "TextureMergeBPLibrary.generated.h"

UCLASS()
class UTextureMergeBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintCallable, Category = "Texture Merge", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "Create", Keywords = "Create composed texture"))
		static UCompositeTexture* Create(UObject* WorldContextObject, const TArray<UTexture2D*>& Layers);
	UFUNCTION(BlueprintCallable, Category = "Texture Merge", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "CreateWithTints", Keywords = "Create composed texture with tints"))
		static UCompositeTexture* CreateWithTints(UObject* WorldContextObject, const TArray<UTexture2D*>& Layers, const TArray<FColor>& LayerTints);
	UFUNCTION(BlueprintCallable, Category = "Texture Merge", meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject", DisplayName = "CreateMaterial", Keywords = "Create composed texture and material with tints"))
		static UCompositeTexture* CreateMaterial(UObject* WorldContextObject, UMaterialInterface* ParentMaterial, FName MaterialParamName, const TArray<UTexture2D*>& Layers, UMaterialInterface*& OutputMaterial);


	UFUNCTION(BlueprintCallable, Category = "Texture Merge", meta = (DisplayName = "UpdateLayer", Keywords = "Update single layer"))
		static UCompositeTexture* UpdateLayer(UCompositeTexture* RenderTarget, UTexture2D* Layer, const int32 Index);
	UFUNCTION(BlueprintCallable, Category = "Texture Merge", meta = (DisplayName = "UpdateAllLayers", Keywords = "Update all layers"))
		static UCompositeTexture* UpdateAllLayers(UCompositeTexture* RenderTarget, TArray<UTexture2D*> Layers);

	UFUNCTION(BlueprintCallable, Category = "Texture Merge", meta = (DisplayName = "UpdateTint", Keywords = "Update single tint layer"))
		static UCompositeTexture* UpdateTint(UCompositeTexture* RenderTarget, const FColor& Tint, int32 Index);
	UFUNCTION(BlueprintCallable, Category = "Texture Merge", meta = (DisplayName = "UpdateAllTints", Keywords = "Update all tint layers"))
		static UCompositeTexture* UpdateAllTints(UCompositeTexture* RenderTarget, const TArray<FColor>& LayerTints);

};
