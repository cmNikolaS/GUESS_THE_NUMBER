#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <windows.h>

#include "simpleLibrary.h"
#include "guessTheNumberClass.h"

const std::string MENU_main_file = "MENU_main.txt";
const std::string MENU_playerGuessing_file = "MENU_playerGuessing.txt";
const std::string MENU_botGuessing_file = "MENU_botGuessing.txt";
const std::string websiteLink = "https://youtu.be/dQw4w9WgXcQ?si=aPeCbQAK-WUruYDF";

inline void handleInput(const char input)
{
    if(input == 'o')
    {
        std::string websiteLinkT = "start " + websiteLink;
        system(websiteLinkT.c_str());
    }
    else if(input == 'q')
    {
        exit(0);
    }
}

bool getInput_RestartGame(char &tInput);

void enterBordersAndNumberOfTries(char tInput, rNum_t &lB, rNum_t &hB, rNum_t &nOfTr);

char playGame_PlayerGuessing(rNum_t lB, rNum_t hB, rNum_t numberOfTries);

char playGame_BotGuessing(rNum_t lB, rNum_t hB, rNum_t numberOfTries, char difficulty, rNum_t imaginedNum);

char enterBotDifficulty();

rNum_t enterImaginedNumber(rNum_t lB, rNum_t hB);

int main()
{

    simpleLibrary::setTitle("GUESS THE NUMBER - Made by cmNikolaS");       
    
    char input;

    do
    {
        bool restartGame = false;

        simpleLibrary::clearScreen();
        simpleLibrary::printFile(MENU_main_file);
        do
        {
            input = getch();
            tolower(input);
            handleInput(input);  
        } while (input != '1' && input != '2');

        simpleLibrary::clearScreen();
        bool restartRound = false;
        switch (input)
        {
            case '1':
            {
                do
                {  
                    restartRound = false;
                    simpleLibrary::printFile(MENU_playerGuessing_file);    
                    char tInput;
                    
                    restartGame = getInput_RestartGame(tInput);

                    if(restartGame) { break; }

                    if(tInput != '0')
                    {
                        rNum_t numberOfTries = 10, lB = 1, hB;
                        enterBordersAndNumberOfTries(tInput, lB, hB, numberOfTries);
                        
                        tInput = playGame_PlayerGuessing(lB, hB, numberOfTries);

                        simpleLibrary::clearScreen();

                        if(tInput == '2')
                        {   
                            restartRound = true;
                        }
                        else if(tInput == '3')
                        {
                            restartGame = true;
                        }
                    }
                } while(restartRound);
                break;
            }
            case '2':
            {
                do
                {
                    restartRound = false;
                    simpleLibrary::printFile(MENU_botGuessing_file);    
                    char tInput;
                    restartGame = getInput_RestartGame(tInput);

                    if(restartGame) { break; }

                    if(tInput != '0')
                    {
                        rNum_t numberOfTries = 10, lB = 1, hB, difficulty = tInput, imaginedNumber;
                        enterBordersAndNumberOfTries(tInput, lB, hB, numberOfTries);
                        if(tInput == '4')
                        {
                            difficulty = enterBotDifficulty();
                        }
                        
                        imaginedNumber = enterImaginedNumber(lB, hB);
                        
                        tInput = playGame_BotGuessing(lB, hB, numberOfTries, difficulty, imaginedNumber);

                        simpleLibrary::clearScreen();

                        if(tInput == '2')
                        {   
                            restartRound = true;
                        }
                        else if(tInput == '3')
                        {
                            restartGame = true;
                        }
                    }
                } while (restartRound);
                break;
            }
        }

    } while (true);
    
    simpleLibrary::pause();
    
    return 0;
}

bool getInput_RestartGame(char &tInput)
{   
    bool restartGame = false;
    do
    {
        tInput = getch();
        tolower(tInput);
        if(tInput == '0')
        {
            restartGame = true;
        }
        else
        {
            handleInput(tInput);
        }
    } while (tInput != '1' && tInput != '2'
            && tInput != '3' && tInput != '4' && tInput != '0');

    return restartGame;
}

char playGame_PlayerGuessing(rNum_t lB, rNum_t hB, rNum_t numberOfTries)
{
    char input;
    do
    {
        randomNumber GAME(lB, hB);
        rNum_t imaginedNumber = GAME.getRandomNumber();
        rNum_t playerGuess = 0;
        for(rNum_t i = 0; i < numberOfTries; i++)
        {
            std::cout << i + 1 << ". Guess: "; 
            std::cin >> playerGuess;
            if(playerGuess == imaginedNumber)
            {
                std::cout << std::endl;
                std::cout << "_______________________________________________" << std::endl;
                std::cout << "You guessed it! The number was " << imaginedNumber << std::endl;
                std::cout << "_______________________________________________" << std::endl;
                break;
            }
            else if(playerGuess == (numberOfTries - 1))
            {
                std::cout << std::endl;
                std::cout << "_______________________________________________" << std::endl;
                std::cout << "You didn't guess it! The number was " << imaginedNumber << std::endl;
                std::cout << "_______________________________________________" << std::endl;
            }
            else
            {
                if(playerGuess < imaginedNumber)
                {
                    std::cout << "Imagined number is HIGHER than " << playerGuess << std::endl;
                }
                else if(playerGuess > imaginedNumber)
                {
                    std::cout << "Imagined number is LOWER than " << playerGuess << std::endl;
                }
            }
        }

        do
        {
            std::cout << std::endl;
            std::cout << "            GAME OVER!" << std::endl;
            std::cout << "_______________________________________________" << std::endl;
            std::cout << "1. Play Again This Level" << std::endl;
            std::cout << "2. Player Guessing Number Menu" << std::endl; 
            std::cout << "3. Main Menu" << std::endl;
            input = getch();
            handleInput(input);
        } while(input != '1' && input != '2' && input != '3');
        
    } while(input == '1');

    return input;
}

void enterBordersAndNumberOfTries(char tInput, rNum_t &lB, rNum_t &hB, rNum_t &nOfTr)
{
    lB = 1;
    nOfTr = 10;
    if(tInput == '1')
    {
        hB = 100;
    }
    else if(tInput == '2')
    {
        hB = 500;
    }
    else if(tInput == '3')
    {
        hB = 1000;
    }
    else if(tInput == '4')
    {
        do
        {
            simpleLibrary::clearScreen();
            std::cout << "Enter the LOWER border of the range (1 - 50000): ";
            std::cin >> lB;
        } while (lB < 1 || lB > 50000);
        
        do
        {
            simpleLibrary::clearScreen();
            std::cout << "Lower Border: " << lB << std::endl;
            std::cout << "Enter the HIGHER border of the range (" << lB << " - 50000): ";
            std::cin >> hB;
        } while (hB < lB || hB > 50000);

        do
        {
            simpleLibrary::clearScreen();
            std::cout << "Lower Border: " << lB << std::endl;
            std::cout << "Higher Border: " << hB << std::endl;
            std::cout << "Enter the number of tries (1 - 15): ";
            std::cin >> nOfTr;
        } while (nOfTr < 1 || nOfTr > 15);
        simpleLibrary::clearScreen();
    }
}

char playGame_BotGuessing(rNum_t lB, rNum_t hB, rNum_t numberOfTries, char difficulty, rNum_t imaginedNum)
{
    char input;
    
    do
    {    
        randomNumber GAME(lB, hB);
        rNum_t botGuessing;
        for(int i = 0; i < numberOfTries; i++)
        {
            if(difficulty == '1' || i % 2 == 0)
            {
                botGuessing = GAME.getRandomNumber();
            }
            else
            {
                botGuessing = (lB + hB / 2);
            } 
            std::cout << "BOT: Guessing number: " << botGuessing << std::endl;
            Sleep(690);
            if(numberOfTries == (i + 1))
            {
                std::cout << "PLAYER: YOU RUN OUT OF TRIES" << std::endl;
                std::cout << "__________________________________" << std::endl;
                std::cout << "Imagined Number Was " << imaginedNum << std::endl;
                break;
            }
            else
            {
                if(botGuessing == imaginedNum)
                {
                    std::cout << "PLAYER: Thats Right! You Guessed It!" << std::endl;
                }
                else if(botGuessing < imaginedNum)
                {
                    GAME.changeLowerBorder(botGuessing + 1);
                    std::cout << "PLAYER: Imagined Number is BIGGER Than " << botGuessing  << '!' << std::endl;
                }
                else if(botGuessing > imaginedNum)
                {
                    GAME.changeHigherBorder(botGuessing - 1);
                    std::cout << "PLAYER: Imagined Number is SMALLER Than " << botGuessing << '!' << std::endl;
                }
            }
        }
        do
        {
            std::cout << std::endl;
            std::cout << "            GAME OVER!" << std::endl;
            std::cout << "_______________________________________________" << std::endl;
            std::cout << "1. Play Again This Level" << std::endl;
            std::cout << "2. Bot Guessing Number Menu" << std::endl; 
            std::cout << "3. Main Menu" << std::endl;
            input = getch();
            handleInput(input);
            simpleLibrary::clearScreen();
        } while(input != '1' && input != '2' && input != '3');

    } while (input == '1');

    return input;   
}

char enterBotDifficulty()
{
    char difficulty;
    std::cout << std::endl;
    std::cout << "Enter Bot Difficulty" << std::endl;
    std::cout << "_________________________________" << std::endl;
    std::cout << "1. Noob(Easy)\n";
    std::cout << "2. Average(Medium)\n";
    std::cout << "3. Pro(Hard)\n";
    std::cout << "4. Random\n";
    do
    {
        difficulty = getch();
        handleInput(difficulty);
    } while(difficulty != '1' && difficulty != '2' && difficulty != '3'
    && difficulty != '4');
    if(difficulty == '4')
    {
        randomNumber diff(1, 3);
        difficulty = char(diff.getRandomNumber() + 48);
    }
    return difficulty;
    simpleLibrary::clearScreen();
}

rNum_t enterImaginedNumber(rNum_t lB, rNum_t hB)
{
    rNum_t imaginedNumber;
    do
    {
        std::cout << "Imagine Number Between " << lB << " and " << hB << std::endl;
        std::cout << "_____________________________________________________" << std::endl;
        std::cin >> imaginedNumber;
    } while(imaginedNumber < lB || imaginedNumber > hB);
    return imaginedNumber;
}