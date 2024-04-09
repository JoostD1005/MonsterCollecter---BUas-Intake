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


namespace Tmpl8
{
    Surface tiles("assets/background.tga");



    void Game::Init()
    {

        Refiller* refill1 = new Refiller("assets/food.png", 1, { 100, 472 });
        Refiller* refill2 = new Refiller("assets/water.png", 1, { 147, 472 });
        refillers.push_back(refill1);
        refillers.push_back(refill2);
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

        monsters.clear();

        screen->Clear(0x00ff00);
    }


    static char map[9][51] = {
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
        "aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa aa",
    };



    void Game::Tick(float deltaTime)
    {
        //-----Time Past--------------------------------------------------------

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


                    std::cout << monster->GetTileIndex() << "\n";

                }

                if (time > 1)
                {
                    cash++;
                    time = 0.0f;

                    secondsPast++;
                    std::cout << secondsPast << "\n";

                    for (Monster* monster : monsters)
                    {
                        monster->TimeSinceSpawn();
                        monster->Move(monsters);
                    }
                }
            

        }

        frameTime = frameTime + deltaTime;
        if (frameTime > 0.25f)
        {
            for (Monster* monster : monsters)
            {
                int i = 0;
                if (monster->GetSprite()->GetFrame() < monster->GetNumFrames() - 1)
                {
                    monster->GetSprite()->SetFrame(i + 1);
                }
                else if (monster->GetSprite()->GetFrame() == monster->GetNumFrames() - 1)
                {
                    monster->GetSprite()->SetFrame(0);
                }
            }

            frameTime = 0.0f;
        }

       

        //===============Checking Collisions===========================================================

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
            float snapX = roundf(mousex / 50) * 50;
            float snapY = roundf(mousey / 50) * 50;
            
            currentTarget->SetPosition({ snapX - (currentTarget->GetSprite()->GetWidth() / 2), snapY - (currentTarget->GetSprite()->GetHeight() / 2) });
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

        //--------------------------------------------------------------------------------------------------------------------

        //spawn monster1 if button is clicked

        if (CheckMouseCollision(m_BuyWindow.GetMonsterButton1().GetCollider()) == true && buyWindowCalled == true && freeze == false)
        {
            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                if (cash > 10)
                {
                    CreateMonster(1);
                    std::cout << "\n" << monsters.size() << "\n";
                    cash = cash - 10;
                }
            }

        }


        //spawn monster2 if button is clicked
        if (CheckMouseCollision(m_BuyWindow.GetMonsterButton2().GetCollider()) == true && buyWindowCalled == true && freeze == false)
        {

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                if (cash > 20)
                {
                    CreateMonster(2);
                    cash = cash - 20;
                }
            }
        }


        //spawn monster3 if button is clicked
        if (CheckMouseCollision(m_BuyWindow.GetMonsterButton3().GetCollider()) == true && buyWindowCalled == true && freeze == false)
        {

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                if (cash > 30)
                {
                    CreateMonster(3);
                    cash = cash - 30;
                }
            }
        }



        prevButtonState = buttonState;

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

        for (const Monster* monster : monsters)
        {
            monster->Draw(screen);
            screen->Box(monster->GetCollider(), 0x00ff00); // colliderbox 
        }

        for (int i = 0; i < monsters.size(); i++)
        {
            Label monsterNumber = Label("M", i, monsters[i]->GetPosition(), 0xffffff, 1);
            monsterNumber.Print(screen);
        }

        for (const Refiller* refiller : refillers)
        {
            refiller->Draw(screen);
            screen->Box(refiller->GetCollider(), 0x00ff00); // colliderbox
        }

     
        //-------------------------------------------Text------------------------------------------------------------------------

        cashText.SetValue(cash);
        cashText.Print(screen);

        monsterText.SetValue(monsters.size());
        monsterText.Print(screen);

        if (currentTarget != nullptr) // print worth of currentTarget
        {
            Label worthText = Label("Worth", currentTarget->GetWorth(), { 5, 35 }, 0xffffff, 2);
            worthText.Print(screen);
        }

        if (lastTarget != nullptr) // print worth of lastTarget
        {
            Label worthLastText = Label("Worth last", lastTarget->GetWorth(), { 5, 35 }, 0xffffff, 2);
            worthLastText.Print(screen);
        }

        xText.SetValue(mousex);
        yText.SetValue(mousey);

        xText.Print(screen);
        yText.Print(screen);

        //--------------------------------------Selling Window-----------------------------------------------------
        if (CheckMouseCollision(buttonSell.GetCollider()) == true && currentTarget != nullptr && freeze == false) // draw button on screen
        {
            buttonSell.GetSprite()->SetFrame(1);
            buttonSell.Draw(screen);
            if ((SDL_BUTTON_LMASK) != 0) // check if pressed
            {
                sellWindowCalled = true;
                currentTarget->SetPosition({ static_cast<float>(400 - (currentTarget->GetSprite()->GetWidth() / 2)),static_cast<float>(220 - (currentTarget->GetSprite()->GetHeight() / 2)) });
            }
        }
        else
        {
            buttonSell.GetSprite()->SetFrame(0);
            buttonSell.Draw(screen);
        }



        if (sellWindowCalled) // checks if sell window is called and draws it on the screen.
        {
            m_SellWindow.Draw(screen);
        

            if (lastTarget != nullptr) // print worth of lastTarget
            {
                screen->Print(std::format("Worth: {}", lastTarget->GetWorth()), 350, 280, 0xffffff, 2);
            }
            
            freeze = true;

            if (currentTarget == nullptr && lastTarget != nullptr)
            {
                lastTarget->Draw(screen);
            }

        }

        if (CheckMouseCollision(m_SellWindow.GetBackButton().GetCollider()) == true) // function to back out of selling
        {
            m_SellWindow.GetBackButton().GetSprite()->SetFrame(1);

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                sellWindowCalled = false;
                freeze = false;
            }
        }
        else
        {
            m_SellWindow.GetBackButton().GetSprite()->SetFrame(0);
        }

        if (CheckMouseCollision(m_SellWindow.GetSellButton().GetCollider()) == true) // collision logic for sellButton 2
        {
            m_SellWindow.GetSellButton().GetSprite()->SetFrame(1);

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                Sell();
                sellWindowCalled = false;
                freeze = false;
                time = 0.0f;
            }
        }
        else
        {
            m_SellWindow.GetSellButton().GetSprite()->SetFrame(0);
        }

        //------------------------------------------------------------------------------------------------------------
        
        
        //-------------------------Buy Window----------------------------------------------------

        if (CheckMouseCollision(buttonBuy.GetCollider()) == true && freeze == false)
        {
            buttonBuy.GetSprite()->SetFrame(1);
            buttonBuy.Draw(screen);
            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                buyWindowCalled = true;
            }
        }
        else
        {
            buttonBuy.GetSprite()->SetFrame(0);
            buttonBuy.Draw(screen);
        }


        if (buyWindowCalled) // checks if buy window is called and draws the window
        {
            m_BuyWindow.Draw(screen);
        }


        if (CheckMouseCollision(m_BuyWindow.GetBackButton().GetCollider()) == true)
        {
            m_BuyWindow.GetBackButton().GetSprite()->SetFrame(1);

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                buyWindowCalled = false;
            }
        }
        else
        {
            m_BuyWindow.GetBackButton().GetSprite()->SetFrame(0);
        }
     
        //------------------------------------------------------------------------------------------------
        //================================================================================================

        //------------------check if monster Died---------------------------------------------------------
        for (const Monster* monster : monsters)
        {
            if (monster->GetHunger() >= monster->GetStomach() || monster->GetThirst() >= monster->GetHydration())
            {
                screen->Print("A Monster Died...", (ScreenWidth - 340) / 2 + 1, (ScreenHeight - 20) / 2 + 1, 0x000000, 4);
                screen->Print("A Monster Died...", (ScreenWidth - 340) / 2, (ScreenHeight - 20) / 2, 0xffffff, 4);

                freeze = true;
               
              
            }
        }

        //-------------------------------Game Over Screen--------------------------------------------------------------
        if (time >= 3 && sellWindowCalled == false)
        {
            screen->Clear(0);
            screen->Print("Game Over", (ScreenWidth - 225) / 2, (ScreenHeight - 25) / 2, 0xffffff, 5);
            gameOverMonsterText.SetValue(monsters.size());
            gameOverMonsterText.Print(screen);

            playAgainButton.Draw(screen);

        }

        if (CheckMouseCollision(playAgainButton.GetCollider()) == true)
        {
            playAgainButton.GetSprite()->SetFrame(1);

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                Reset();
            }
        }
        else
        {
            playAgainButton.GetSprite()->SetFrame(0);
        }
        //---------------------------------------------------------------------------------------

        screen->Line(mousex, 0, mousex, 511, 0xff0000);
        screen->Line(0, mousey, 799, mousey, 0xff0000);
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
            newMonster = new Monster("assets/Slime.tga", 2, 0, 0, 1, 10, 5, 5, 10, 10);
        }
        else if (typeOfMonster == 2)
        {
            newMonster = new Monster("assets/Golem.tga", 2, 0, 0, 1, 20, 50, 50, 20, 20);
        }
        else if (typeOfMonster == 3)
        {
            newMonster = new Monster("assets/Slime2.tga", 2, 0, 0, 1, 30, 60, 60, 30, 30);
        }
        else
        {
            std::cout << "This is not a valid option.";
        }

        if (newMonster != nullptr)
        {
            // Place the new monster in the center of the screen.
            newMonster->SetPosition({ ScreenWidth / 2.0f, ScreenHeight / 2.0f });
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
        cash = 500;
        time = 0.0f;
        frameTime = 0.0f;
        secondsPast = 0;
        freeze = false;
        sellWindowCalled = false;
        buyWindowCalled = false;

    }

    void Game::DrawTile(int tx, int ty, Surface* screen, int x, int y)
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
