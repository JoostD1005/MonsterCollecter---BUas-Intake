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


namespace Tmpl8
{

    static	Button button1("assets/Slime.tga", 2, { 700, 80 });
    static Button button2("assets/Golem.tga", 2, { 700, 208 });
    static Button button3("assets/Slime2.tga", 2, { 700, 336 });

    static Button buttonSell("assets/sellButton.tga", 2, { 368, 472 });
    static Button buttonSell2("assets/sellButton.tga", 2, { 368, 300 });

    static Button buttonBuy("assets/buyButton.tga", 2, { 636, 472 });
    static Button backButton1("assets/backButton.tga", 2, { 755, 52 });

    static Button playAgainButton("assets/playAgainButton.tga", 2, { 150, 350 });


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




    void Game::Tick(float deltaTime)
    {
        //-----Time Past--------------------------------------------------------

        screen->Clear(0);
        screen->Bar(0, 450, 800, 512, 0xD9A066);
        screen->Bar(0, 450, 800, 465, 0x8F563B);
        deltaTime = deltaTime / 1000;

        time = time + deltaTime;
        
            if (freeze == false)
            {
                for (Monster* monster : monsters)
                {
                    monster->SetTimeSinceFood(time);
                    monster->SetTimeSinceWater(time);

                    if (monster->GetTimeSinceFood() > 2)
                    {
                        monster->Hunger(time);
                    }

                    if (monster->GetTimeSinceWater() > 2)
                    {
                        monster->Thirst(time);
                    }


                    std::cout << monster->GetHunger() << ", " << monster->GetThirst() << "\n";

                }

                if (time > 1)
                {
                    cash++;
                    time = 0.0f;

                    secondsPast++;
                    std::cout << secondsPast << "\n";
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
            currentTarget->SetPosition({ mousex - (currentTarget->GetSprite()->GetWidth() / 2), mousey - (currentTarget->GetSprite()->GetHeight() / 2) });
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

        if (CheckMouseCollision(button1.GetCollider()) == true && freeze == false)
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
        if (CheckMouseCollision(button2.GetCollider()) == true && freeze == false)
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
        if (CheckMouseCollision(button3.GetCollider()) == true && freeze == false)
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

        //-------------------------------------------Text------------------------------------------------------------------------

        std::string cashstr = std::format("Cash: {}", cash); // std::string("Cash: ").append(std::to_string(cash));
        screen->Print(cashstr.c_str(), 5, 5, 0xffffff, 2);

        std::string monsterstr = std::format("Monsters: {}", monsters.size()); // std::string("Monsters: ").append(std::to_string(monsters.size()));
        screen->Print(monsterstr.c_str(), 5, 20, 0xffffff, 2);

        if (currentTarget != nullptr)
        {
            std::string worthstr = std::format("Worth: {}", currentTarget->GetWorth()); // std::string("Monsters: ").append(std::to_string(monsters.size()));
            screen->Print(worthstr.c_str(), 5, 35, 0xffffff, 2);
        }

        if (lastTarget != nullptr)
        {
            std::string worthstr = std::format("Worth last Target: {}", lastTarget->GetWorth()); // std::string("Monsters: ").append(std::to_string(monsters.size()));
            screen->Print(worthstr.c_str(), 5, 60, 0xffffff, 2);
        }

        //-------------------------------------------Drawing------------------------------------------------------------------------

        for (const Monster* monster : monsters)
        {
            monster->Draw(screen);
            screen->Box(monster->GetCollider(), 0x00ff00);
        }

        for (const Refiller* refiller : refillers)
        {
            refiller->Draw(screen);
            screen->Box(refiller->GetCollider(), 0x00ff00);
        }

       
        
        

        //--------------------------------------Selling Window-----------------------------------------------------
        if (CheckMouseCollision(buttonSell.GetCollider()) == true && currentTarget != nullptr && freeze == false)
        {
            buttonSell.GetSprite()->SetFrame(1);
            buttonSell.Draw(screen);
            if ((SDL_BUTTON_LMASK) != 0)
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



        if (sellWindowCalled)
        {
            m_SellWindow->Draw(screen, 310, 166);
            buttonSell2.Draw(screen);
            
            freeze = true;

            if (currentTarget == nullptr && lastTarget != nullptr)
            {
                lastTarget->Draw(screen);
            }

        }

        if (CheckMouseCollision(buttonSell2.GetCollider()) == true)
        {
            buttonSell2.GetSprite()->SetFrame(1);

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
            buttonSell2.GetSprite()->SetFrame(0);
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


        if (buyWindowCalled)
        {
            m_BuyWindow->Draw(screen, 670, 35);
            backButton1.Draw(screen);
            button1.Draw(screen);
            button2.Draw(screen);
            button3.Draw(screen);

            screen->Print("cost: 10", 700, 144, 0x000000);
            screen->Print("cost: 20", 700, 272, 0x000000);
            screen->Print("cost: 30", 700, 400, 0x000000);
        }


        if (CheckMouseCollision(backButton1.GetCollider()) == true)
        {
            backButton1.GetSprite()->SetFrame(1);

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                buyWindowCalled = false;
            }
        }
        else
        {
            backButton1.GetSprite()->SetFrame(0);
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

            std::string monsterstr = std::format("you Collected {} Monsters!", monsters.size());
            screen->Print(monsterstr.c_str(), (ScreenWidth - 500) / 2, ((ScreenHeight - 25) / 2) + 50, 0xffffff, 4);

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
            newMonster = new Monster("assets/Slime.tga", 2, 0, 0, 1, 10, 5, 5, 10);
        }
        else if (typeOfMonster == 2)
        {
            newMonster = new Monster("assets/Golem.tga", 2, 0, 0, 1, 20, 50, 50, 20);
        }
        else if (typeOfMonster == 3)
        {
            newMonster = new Monster("assets/Slime2.tga", 2, 0, 0, 1, 30, 60, 60, 30);
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


};
