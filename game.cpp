#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include "Monster.hpp"
#include <vector>
#include <algorithm>
#include <SDL.h>
#include "AABBCollider.hpp"
#include "Button.hpp"
#include "Refiller.hpp"
#include <string>
#include <format>
#include <Windows.h>
#include "ParticleSystem.hpp"


namespace Tmpl8
{
    Surface tiles("assets/background.png");

    static char map[9][51] = {
     "ba ca da ca ba ca da ba da ba ba ca da ba ca da",
     "ba da ba ba ca da ba ca da ca ba ca da ba ca da",
     "da ba ca ca ca da ba ba da ca ba da ba da ca ca",
     "ba ca da ca ba ca da ba da ba ba ca da ba ca da",
     "ba da ba ba ca da ba ca da ca ba ca da ba ca da",
     "da ba ca ca ca da ba ba da ca ba da ba da ca ca",
     "ba ca da ca ba ca da ba da ba ba ca da ba ca da",
     "ba da ba ba ca da ba ca da ca ba ca da ba ca da",
     "da ba ca ca ca da ba ba da ca ba da ba da ca ca"
    };

    void Game::Init()
    {

        Refiller* refill1 = new Refiller("assets/food.png", 1, { 200, 472 });
        Refiller* refill2 = new Refiller("assets/water.png", 1, { 247, 472 });
        refillers.push_back(refill1);
        refillers.push_back(refill2);
#if _DEBUG
        for (int i = 0; i < 128; i++)
        {
            Label* gridLabel = new Label("", i, i, 0x0, 1);
            gridLabels.push_back(gridLabel);
        }
#endif
    }



    void Game::Shutdown()
    {
        for (Monster* monster : monsters)
        {
            delete monster;
        }

        for (Refiller* refiller : refillers)
        {
            delete refiller;
        }
        
#if _DEBUG
        for (Label* gridLabel : gridLabels)
        {
            delete gridLabel;
        }
#endif
        
        monsters.clear();
        refillers.clear();

        screen->Clear(0x00ff00);
    }


    void Game::Tick(float deltaTime)
    {
        //-----Time Past--------------------------------------------------------
        switch (state)
        {
        case State::startScreen :
            StartScreen(deltaTime);
            break;
        case State::game :
            GameScreen(deltaTime);
            break;
        case State::gameOver :
            GameOverScreen(deltaTime);
            break;
        case State::helpScreen :
            HelpScreen(deltaTime);
            break;
        }

        prevButtonState = buttonState;
    }

    void Game::StartScreen(float deltaTime)
    {
        screen->Clear(0);
        startScreen.Draw(screen);
        playButton.Draw(screen);
        helpButton.Draw(screen);
        exitButton.Draw(screen);

        if (CheckButtonClicked(playButton))
        {
            Reset();
            state = State::game;
        }
        
        if (CheckButtonClicked(helpButton))
        {
            state = State::helpScreen;
        }

        if (CheckButtonClicked(exitButton))
        {
            exit(0);
        }

    }

    void Game::GameScreen(float deltaTime)
    {

        screen->Clear(0);
        deltaTime = deltaTime / 1000;

        time = time + deltaTime;

        if (freeze == false)
        {
            for (Monster* monster : monsters)
            {
                monster->TimeSinceFood(deltaTime);
                monster->TimeSinceWater(deltaTime);
                monster->Evolution();
                monster->GetWorth();


                if (monster->GetTimeSinceFood() > 2.0f)
                {
                    monster->Hunger(deltaTime);
                }

                if (monster->GetTimeSinceWater() > 2.0f)
                {
                    monster->Thirst(deltaTime);
                }


              //  std::cout << monster->GetTileIndex() << "\n";

                if (time >= 1)
                {
                    monster->TimeSinceSpawn();
                }

                if (monster->GetTileIndex() != monster->GetNextTileIndex())
                {
                    monster->Move(deltaTime);
                }
                else 
                {
                    monster->SetState(AnimState::Idle);
                }


                moveTime += deltaTime;
                if (monster->GetTileIndex() == monster->GetNextTileIndex() && moveTime > 1.0f)
                {
                    monster->GetMonsterAI().NextTile(monsters, monster);
                    moveTime = 0.0f;
                }

            }

            if (time > 1.0f && !monsters.empty())
            {
                cash++;
            }

            if (time > 1)
            {
                time = 0.0f;

                secondsPast++;
                //std::cout << secondsPast << "\n";
                for (Monster* monster : monsters)
                {
                    monster->TimeSinceSpawn();
                }
            }


        }

        frameTime = frameTime + deltaTime;
        if (frameTime > 0.10f)
        {
            for (Monster* monster : monsters)
            {
                monster->DoAnimation(deltaTime);
            }
            frameTime = 0.0f;
        }


        const int buttonPressed = buttonState & ~prevButtonState;
        int buttonReleased = ~buttonState & prevButtonState;

        //---------------------------------------Monster Movements With Mouse + collision------------------------------------------------
        if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
        {
            for (int i = 0; i < monsters.size(); i++)
            {
                if (CheckMouseCollision(monsters[i]->GetCollider()) == true && currentTarget == nullptr)
                {
                    currentTarget = monsters[i];
                    break;
                }
            }
        }

        if (currentTarget != nullptr && isLeftButtonDown && freeze == false)
        {
            int row = mousey / 50;
            int col = mousex / 50;
            int tileIndex = row * 16 + col;
            
            if (tileIndex <= 127)
            {
                currentTarget->SetPosition(tileIndex);
                currentTarget->SetNextTileIndex(tileIndex);
            }
            
            if(tileIndex > 127)
            {
                currentTarget->SetPosition(127 - (16 - (tileIndex % 16)));
                currentTarget->SetNextTileIndex(127 - (16 - (tileIndex % 16)));
            }
        }



        //-----------------------------Reffillers Movement + collision----------------------------------------------------------------------------

        if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
        {
            for (int i = 0; i < refillers.size(); i++)
            {
                if (CheckMouseCollision(refillers[i]->GetCollider()) == true)
                {
                    refillerTarget = refillers[i];
                    break;
                }
            }
        }

        if (refillerTarget != nullptr && isLeftButtonDown && freeze == false)
        {
            refillerTarget->SetPos({ mousex - (refillerTarget->GetSprite()->GetWidth() / 2), mousey - (refillerTarget->GetSprite()->GetHeight() / 2) });
        }

        if (refillerTarget == nullptr)
        {
            for (Refiller* refiller : refillers)
            {
                refiller->SetPos(refiller->GetOriginalPos());
            }
        }

        for (Monster* monster : monsters)
        {
            monster->UpdateParticles(deltaTime);

            if (CheckMouseCollision(monster->GetCollider()) == true && refillerTarget != nullptr)
            {
                if (refillerTarget == refillers[0])
                {
                    monster->SetHunger(0);
                    monster->SetTimeSinceFood(0);
                }

                if (refillerTarget == refillers[1])
                {
                    monster->SetThirst(0);
                    monster->SetTimeSinceWater(0);
                }
            }
        }



        //-------------------------------------------Drawing------------------------------------------------------------------------

        for (int y = 0; y < 9; y++) // tilemap --> from the 3DGep Website.
            for (int x = 0; x < 16; x++)
            {
                int tx = map[y][x * 3] - 'a';
                int ty = map[y][x * 3 + 1] - 'a';
                DrawTile(tx, ty, screen, x * 50, y * 50);
            }

        screen->Bar(0, 450, 800, 512, 0xD9A066);
        screen->Bar(0, 450, 800, 465, 0x8F563B);
        screen->Box(199, 471, 233, 505, 0x0);
        screen->Box(246 , 471, 280, 505, 0x0);

        for (const Monster* monster : monsters)
        {
            monster->Draw(screen);
        }

        for (const Refiller* refiller : refillers)
        {
            refiller->Draw(screen);
        }

        ///////////////////////////////drawing debug stuff////////////////////////////////////////////////////////////
#if _DEBUG
        for (int i = 0; i < monsters.size(); i++)
        {
            screen->Box(monsters[i]->GetCollider(), 0x00ff00); // colliderbox for monsters
            if (i < refillers.size())
            {
                screen->Box(refillers[i]->GetCollider(), 0x00ff00); // colliderbox for refillers
            }

            Label monsterNumber = Label("M  ", monsters[i]->GetNextTileIndex(), monsters[i]->GetPosition(), 0xffffff, 1); // prints next tile above monster
            if (monsters[i]->GetPosition().x > 0 && monsters[i]->GetPosition().y > 0)
            {
                monsterNumber.Print(screen);
            }
        }

        xText.SetValue(mousex);
        yText.SetValue(mousey);

        xText.Print(screen);
        yText.Print(screen);

        screen->Line(mousex, 0, mousex, 511, 0xff0000);
        screen->Line(0, mousey, 799, mousey, 0xff0000);

        for (Label* gridLabel : gridLabels)
        {
            gridLabel->Print(screen); //prints the number of the tile above the tile
        }

        if (lastTarget != nullptr) // print worth of lastTarget
        {
            Label worthLastText = Label("Worth last", lastTarget->GetWorth(), { 5, 35 }, 0xffffff, 2);
            worthLastText.Print(screen);
        }

#endif


        //-------------------------------------------Text------------------------------------------------------------------------

        cashText.SetValue(cash);
        cashText.Print(screen);

        monsterText.SetValue(monsters.size());
        monsterText.Print(screen);

        if (currentTarget != nullptr) // print worth of currentTarget
        {
            Label worthText = Label("Monster Worth", currentTarget->GetWorth(), { 5, 35 }, 0x0, 2);
            worthText.Print(screen);
        }

        //--------------------------------------Selling Window-----------------------------------------------------
        if (CheckMouseCollision(buttonSell.GetCollider()) == true && currentTarget != nullptr && freeze == false) // draw button on screen
        {
            buttonSell.GetSprite()->SetFrame(1);  
            if ((SDL_BUTTON_LMASK) != 0) // check if pressed
            {
                sellWindowCalled = true;
                currentTarget->SetPosition({ static_cast<float>(400 - (currentTarget->GetSprite()->GetWidth() / 2)),static_cast<float>(200 - (currentTarget->GetSprite()->GetHeight() / 2)) });
            }
        }
        else
        {
            buttonSell.GetSprite()->SetFrame(0);
        }
        buttonSell.Draw(screen);


        if (sellWindowCalled) // checks if sell window is called and draws it on the screen.
        {
            m_SellWindow.Draw(screen);
            freeze = true;

            if (lastTarget != nullptr) // print worth and level of lastTarget
            {
                screen->Print(std::format("level: {}", lastTarget->GetEvoStage()), 350, 260, 0x0, 2);
                screen->Print(std::format("Worth: {}", lastTarget->GetWorth()), 350, 280, 0x0, 2);
            }

            if (currentTarget == nullptr && lastTarget != nullptr)
            {
                lastTarget->Draw(screen);
            }

        }

        if (CheckButtonClicked(m_SellWindow.GetBackButton()) && sellWindowCalled) // function to back out of selling
        {
            sellWindowCalled = false;
            time = 0.0f;
            freeze = false;
        }

        if (CheckButtonClicked(m_SellWindow.GetSellButton()) && sellWindowCalled) // collision logic for sellButton 2
        {
            Sell();
            sellWindowCalled = false;
            time = 0.0f;
            freeze = false;
        }


        //-------------------------Buy Window----------------------------------------------------

        if (CheckButtonClicked(buttonBuy) && freeze == false)
        {
                buyWindowCalled = true;
        }

        buttonBuy.Draw(screen);


        if (buyWindowCalled) // checks if buy window is called and draws the window
        {
            m_BuyWindow.Draw(screen);
            if (cash < costMonster1)  m_BuyWindow.GetLock1().Draw(screen);
            if (cash < costMonster2)  m_BuyWindow.GetLock2().Draw(screen);
            if (cash < costMonster3)  m_BuyWindow.GetLock3().Draw(screen);

        }


        //spawn monster1 if button is clicked
        if (CheckButtonClicked(m_BuyWindow.GetMonsterButton1())&& buyWindowCalled && freeze == false)
        {
            if (cash >= costMonster1)
            {
                CreateMonster(1);
                cash = cash - costMonster1;
            }
        }

        //spawn monster2 if button is clicked
        if (CheckButtonClicked(m_BuyWindow.GetMonsterButton2()) && buyWindowCalled && freeze == false)
        {
            if (cash >= costMonster2)
            {
                CreateMonster(2);
                cash = cash - costMonster2;
            }
        }

        //spawn monster3 if button is clicked
        if (CheckButtonClicked(m_BuyWindow.GetMonsterButton3()) && buyWindowCalled && freeze == false)
        {
            if (cash >= costMonster3)
            {
                CreateMonster(3);
                cash = cash - costMonster3;
            }
        }

        if (CheckButtonClicked(m_BuyWindow.GetBackButton()))
        {
                buyWindowCalled = false;
        }


        //---------------exit Window---------------------------------------------------------------------
        if (CheckButtonClicked(buttonExit) && freeze == false)
        {
           exitWindowCalled = true;
        }

        buttonExit.Draw(screen);

        if (exitWindowCalled)
        {
            m_ExitWindow.Draw(screen);
        }

        if (CheckButtonClicked(m_ExitWindow.GetExitButton()) && exitWindowCalled)
        {

            state = State::startScreen;
        }

        if (CheckButtonClicked(m_ExitWindow.GetBackButton()))
        {
            exitWindowCalled = false;
        }


        //------------------check if monster Died---------------------------------------------------------
        for (Monster* monster : monsters)
        {
            if (monster->GetHunger() >= monster->GetStomach() || monster->GetThirst() >= monster->GetHydration())
            {
                monster->Dies();

                screen->Print("A Monster Died...", (ScreenWidth - 340) / 2 + 1, (ScreenHeight - 20) / 2 + 1, 0x000000, 4);
                screen->Print("A Monster Died...", (ScreenWidth - 340) / 2, (ScreenHeight - 20) / 2, 0xffffff, 4);

                freeze = true;
            }
        }

        //-------------------------------Game Over Screen--------------------------------------------------------------
        if (time >= 3 && sellWindowCalled == false)
        {
            state = State::gameOver;
        }
    }

   
    void Game::GameOverScreen(float deltaTime)
    {
        blankScreen.Draw(screen);
        screen->Print("Game Over", (ScreenWidth - 270) / 2, (ScreenHeight - 30) / 2, 0x0, 5);
        screen->Print(std::format("You Collected {} Monsters!", monsters.size()),(ScreenWidth - 625) / 2, (ScreenHeight - 25) / 2 + 50 , 0x0, 4);

        playAgainButton.Draw(screen);

        if (CheckButtonClicked(playAgainButton))
        {
            Reset();
            state = State::startScreen;
        }

    }

    void Game::HelpScreen(float deltaTime)
    {
        blankScreen.Draw(screen);
        returnButton.Draw(screen);
        screen->Print("Press PLAY to start.", 40, 20, 0x0, 2);
        screen->Print("open the buy menu to buy new monsters.", 40, 40, 0x0, 2);
        screen->Print("drag a monster over the sell button to open the sell menu.", 40, 60, 0x0, 2);
        screen->Print("feed and water your monsters to keep them alive.", 40, 80, 0x0, 2);
        screen->Print("keep them long enough to see them evolve.", 40, 100, 0x0, 2);
        screen->Print("Collect as many Monsters as possible!", 40, 120, 0x0, 2);

        if (CheckButtonClicked(returnButton))
        {
                state = State::startScreen;
        }

    }

    void Game::MouseUp(int button)
    {
        // Reset button when released.
        buttonState ^= SDL_BUTTON(button);


        switch (button)
        {
        case SDL_BUTTON_LEFT:
            isLeftButtonDown = false;
            if (currentTarget != nullptr)
            {
                lastTarget = currentTarget;
            }
            currentTarget = nullptr;
            refillerTarget = nullptr;
            break;
        case SDL_BUTTON_RIGHT:
            isRightButtonDown = false;
            break;
        }
    }

    void Game::MouseDown(int button)
    {
        // Set the bit for the pressed button.
        buttonState |= SDL_BUTTON(button);


        switch (button)
        {
        case SDL_BUTTON_LEFT:
            isLeftButtonDown = true;
            break;
        case SDL_BUTTON_RIGHT:
            isRightButtonDown = true;
            break;
        }
    }

    void Game::MouseMove(int x, int y)
    {
        mousex = static_cast<float>(x);
        mousey = static_cast<float>(y);

        currentMousePos = { mousex, mousey };
    }



    bool Game::CheckButtonClicked(Button button)
    {
        const int buttonPressed = buttonState & ~prevButtonState;
        int buttonReleased = ~buttonState & prevButtonState;

        if (CheckMouseCollision(button.GetCollider()))
        {
            button.GetSprite()->SetFrame(1);

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                return true;
            }
        }
        else
        {
            button.GetSprite()->SetFrame(0);
        }
            return false;
    }

    bool Game::CheckMouseCollision(const AABBCollider& object)
    {

        Tmpl8::vec2 objectPosition = object.GetPosition();
        Tmpl8::vec2 mousePosition = GetMousePosition();

        int objectWidth = object.GetWidth();
        int objectHeight = object.GetHeight();

        if ((mousePosition.x > objectPosition.x) && (mousePosition.x < (objectPosition.x + objectWidth)))
        {
            if ((mousePosition.y > objectPosition.y) && (mousePosition.y < (objectPosition.y + objectHeight)))
            {
                return true;
            }
        }

        return false;
    }

    Monster* Game::CreateMonster(int typeOfMonster)
    {

        Monster* newMonster = nullptr;

        if (typeOfMonster == 1)
        {
            newMonster = new Monster("assets/slimeIdle.tga", 2, 0, 0, 1, costMonster1, 10, 10, 20);
            newMonster->SetMovingAnimation("assets/slimeJumping.tga", 5);
            newMonster->SetMovingAnimFrames(5);
        }
        else if (typeOfMonster == 2)
        {
            newMonster = new Monster("assets/GolemIdle.tga", 2, 0, 0, 1, costMonster2, 17, 17, 60);
            newMonster->SetMovingAnimation("assets/golemWalking.tga", 5);
            newMonster->SetMovingAnimFrames(5);
        }
        else if (typeOfMonster == 3)
        {
            newMonster = new Monster("assets/mushroomIdle.tga", 2, 0, 0, 1, costMonster3, 30, 30, 100);
            newMonster->SetMovingAnimation("assets/mushroomJumping.tga", 5);
            newMonster->SetMovingAnimFrames(5);
        }
        else
        {
            std::cout << "This is not a valid option.";
        }

        if (newMonster != nullptr)
        {
            newMonster->SetPosition({401,201});
            newMonster->SetNextTileIndex(72);// sets position of new monster to tileIndex 72.
            monsters.push_back(newMonster);
        }

        return newMonster;

    }


    void Game::Sell()
    {
        if (lastTarget != nullptr)
        {
            cash = cash + lastTarget->GetWorth();
        }

        std::vector<Monster*>::iterator posInVector;

        
        posInVector = std::find(monsters.begin(), monsters.end(), lastTarget);

        if (posInVector != monsters.end())
        monsters.erase(posInVector);

        delete lastTarget;
        lastTarget = nullptr;
    }

    void Game::Reset()
    {
        monsters.clear();
        cash = 100;
        time = 0.0f;
        frameTime = 0.0f;
        secondsPast = 0;
        freeze = false;
        sellWindowCalled = false;
        buyWindowCalled = false;
        exitWindowCalled = false;

    }

    void Game::DrawTile(int tx, int ty, Surface* screen, int x, int y) // big inspo from 3dGep.Com fast Track part 11:tiles
    {
        Pixel* src = tiles.GetBuffer() + tx * 50 + (ty * 50) * 200;
        Pixel* dst = screen->GetBuffer() + x + y * 800;

        for (int i = 0; i < 50; i++, src += 200, dst += 800)
        {
            for (int j = 0; j < 50; j++)
            {
                dst[j] = src[j];
            }
        }
    }

};
