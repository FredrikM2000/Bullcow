// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    // *********Only write code under this line *************

    SetupGame();

    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord);//Debug line
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

    //const TCHAR HW[] = TEXT("plums");
    ////const TCHAR HW[] = {TEXT('c'), TEXT('a'), TEXT('k'), TEXT('e') ,TEXT('s'), TEXT('\n') };
    //PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
    //PrintLine(TEXT("The 4yh character of the hidden word is: %c"), HW[3]);//print m

    //int32 i = 0;
    //while (i < 10)
    //{
    //    PrintLine(TEXT("%i"), i);
    //    i++;
    //}

    //for (int32 i = 0; i < 10; i++)
    //{
    //    PrintLine(TEXT("%i"), i);
    //}
    //int32 i = 0;
    //do
    //{
    //    PrintLine(TEXT("%i"), i);
    //    i++;
    //} while (i < 10);
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

    if(!IsIsogram(Guess))
        PrintLine(TEXT("No repeating letters, guess again"));

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
    //for (int i = 0; i < word.Len(); i++)
    //{
    //    for (int j = 0; j < word.Len(); j++)
    //    {
    //        if (word[i] == word[j])
    //            return false;
    //    }
    //}
    //return true;

    for (int32 i = 0; i < HiddenWord.Len(); i++)
    {
        PrintLine(TEXT("%c"), HiddenWord[i]);
    }

    for (int32 i = 0; i < word.Len(); i++)
    {
        PrintLine(TEXT("%c"), word[i]);
    }



    return true;
}