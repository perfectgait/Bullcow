// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    Isograms = GetValidWords(Words);

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

void UBullCowCartridge::ProcessGuess(const FString& Guess)
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

    FBullCowCount Count = GetBullCows(Guess);

    PrintLine(TEXT("You have %i Bulls and %i Cows"), Count.Bulls, Count.Cows);
    PrintLine(TEXT("Uh oh, only %i lives left!"), Lives);
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
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

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList)
    {
        if (Word.Len() >= 4
            && Word.Len() <= 8
            && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }

    return ValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if (Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;

            continue;
        }

        for (int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows++;

                break;
            }
        }
    }

    return Count;
}

void UBullCowCartridge::StartGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num() - 1)];
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