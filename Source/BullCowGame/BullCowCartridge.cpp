// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include <string>

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    StartGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();

    // If the game is over, start the game again
    if (bGameOver)
    {
        StartGame();

        return;
    }

    ProcessGuess(Input);
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        WinGame();

        return;
    }

    // If the user input length doesn't match the hidden word length, let the user try again for free.
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Try again, the hidden word is %i characters long but your word was %i characters long"), HiddenWord.Len(), Guess.Len());

        return;
    }

    // If the user input isn't an isogram, let the user try again for free.
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("Try again, the hidden word is an isogram but your word isn't"));

        return;
    }

    --Lives;

    if (Lives <= 0)
    {
        EndGame();

        return;
    }

    PrintLine(TEXT("Uh oh, only %i lives left!"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for (int32 Index = 0; Index < Word.Len() - 1; Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

void UBullCowCartridge::StartGame()
{
    HiddenWord = TEXT("dork");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word, you have %i lives!"), HiddenWord.Len(), Lives);
    PrintLine(TEXT("Type in your guess and then hit Enter"));
}

void UBullCowCartridge::WinGame()
{
    PrintLine(TEXT("You won, way to go!  Press enter to play again"));

    bGameOver = true;
}

void UBullCowCartridge::EndGame()
{
    PrintLine(TEXT("Game over, the actual word was %s.  Press enter to play again"), *HiddenWord);

    bGameOver = true;
}