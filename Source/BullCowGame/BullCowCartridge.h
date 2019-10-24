// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;

	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	void StartGame();
	void WinGame();
	void EndGame();
	void ProcessGuess(FString Guess);
	// const means that the passed in value will not be manipulated
	bool IsIsogram(FString Word) const;
	TArray<FString> GetValidWords(TArray<FString> Words) const;
};
