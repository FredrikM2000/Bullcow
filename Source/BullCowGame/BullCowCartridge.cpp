// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    // *********Only write code under this line *************

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordList.txt");
    FFileHelper::LoadFileToStringArray(Words, *WordListPath);


    SetupGame();
    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The number of valid words is %i"), GetValidWords(Words).Num());
    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord);//Debug line

    TArray<FString> ValidWords = GetValidWords(Words);

 
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome"));

    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives"), Lives);
    PrintLine(TEXT("Type your guess and\npress enter to continue..."));
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("\nPress enter to play again"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You won"));
        EndGame();
        return;
    }

    //Check if right number of characters
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long"), HiddenWord.Len());
        PrintLine(TEXT("Guess again, you have %i lives"), Lives);
        return;
    }

    if (!IsIsogram(Guess)) {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }

    PrintLine(TEXT("Lost a life!"));
    --Lives;

    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);

        EndGame();
        return;
    }

    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}


bool UBullCowCartridge::IsIsogram(FString word) const
{
    for (int32 Index = 0; Index < word.Len() - 1; Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < word.Len(); Comparison++)
        {
            if (word[Index] == word[Comparison])
                return false;
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;

    for (FString Word : WordList) {
        if (Word.Len() >= 4 && Word.Len() <= 8 && IsIsogram(Word))
        {
            ValidWords.Emplace(Word);
        }
    }


    //for (int32 i = 0; i < WordList.Num(); i++)
    //{
    //    if (WordList[i].Len() >= 4 && WordList[i].Len() <= 8 && IsIsogram(WordList[i]))
    //    {
    //        ValidWords.Emplace(WordList[i]);
    //    }
    //}
    return ValidWords;
}
