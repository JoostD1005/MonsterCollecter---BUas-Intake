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

    static	Button button1("assets/button1.png", 1, { 0,0 });
    static Button button2("assets/ball.png", 1, { 0, 130 });
    static Button button3("assets/target.tga", 1, { 0, 230 });
    static Button buttonSell("assets/sellButton.tga", 2, { 368, 480 });
    static Button buttonSell2("assets/sellButton.tga", 2, { 368, 300 });

    static Refiller refiller("assets/food.png", 1, { 100, 400 });


    void Game::Init()
    {

        Refiller* refill1 = new Refiller("assets/food.png", 1, { 100, 470 });
        Refiller* refill2 = new Refiller("assets/water.png", 1, { 148, 470 });
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
        screen->Bar(0, 450, 800, 512, 0x4f2800);
        deltaTime = deltaTime / 1000;

        time = time + deltaTime;
        if (time > 1)
        {
            for (Monster* monster : monsters)
            {
                
                if (monster->GetTimeSinceFood() > 5)
                {
                    monster->Hunger();
                }

                if (monster->GetTimeSinceWater() > 5)
                {
                    monster->Thirst();
                }

                monster->TimeSinceFood();
                monster->TimeSinceWater();
                
                std::cout << monster->GetHunger() << ", " << monster->GetThirst() << "\n";
            }

            time = 0.0f;
            secondsPast++;
            std::cout << secondsPast << "\n";

            cash++;

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

        for (const Monster* monster : monsters)
        {
            if (monster->GetHunger() >= monster->GetStomach() || monster->GetThirst() >= monster->GetHydration())
            {
                //screen->Clear(0xffffff);
                //Shutdown();
            }
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

        if (currentTarget != nullptr && isLeftButtonDown)
        {
            currentTarget->SetPosition({ mousex - (currentTarget->GetSprite()->GetWidth() / 2), mousey - (currentTarget->GetSprite()->GetHeight() / 2) });
        }



        //-----------------------------Reffillers Movement + collision----------------------------------------------------------------------------

        if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
        {
            for (int i = 0; i < refillers.size(); i++)
            {
                if (CheckMouseCollision(refillers[i]->GetCollider()) == true && refillerTarget == nullptr)
                {
                    refillerTarget = refillers[i];
                    break;
                }
            }
        }

        if (refillerTarget != nullptr && isLeftButtonDown)
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
                }

                if (refillerTarget == refillers[1])
                {
                    monster->SetThirst(0);
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------------

        //spawn monster1 if button is clicked

        if (CheckMouseCollision(button1.GetCollider()) == true)
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
        if (CheckMouseCollision(button2.GetCollider()) == true)
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
        if (CheckMouseCollision(button3.GetCollider()) == true)
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
        screen->Print(cashstr.c_str(), 700, 5, 0xffffff);

        std::string monsterstr = std::format("Monsters: {}", monsters.size()); // std::string("Monsters: ").append(std::to_string(monsters.size()));
        screen->Print(monsterstr.c_str(), 700, 20, 0xffffff);

        if (currentTarget != nullptr)
        {
            std::string worthstr = std::format("Worth: {}", currentTarget->GetWorth()); // std::string("Monsters: ").append(std::to_string(monsters.size()));
            screen->Print(worthstr.c_str(), 700, 35, 0xffffff);
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

        button1.Draw(screen);
        button2.Draw(screen);
        button3.Draw(screen);
        

        //--------------------------------------Selling Window-----------------------------------------------------
        if (CheckMouseCollision(buttonSell.GetCollider()) == true && currentTarget != nullptr)
        {
            buttonSell.GetSprite()->SetFrame(1);
            buttonSell.Draw(screen);
            if ((SDL_BUTTON_LMASK) != 0)
            {
                sellWindowcalled = true;
                currentTarget->SetPosition({static_cast<float>( 400 - (currentTarget->GetSprite()->GetWidth() / 2)),static_cast<float>(256 - (currentTarget->GetSprite()->GetHeight() / 2) )});
            }
        }
        else
        {
            buttonSell.GetSprite()->SetFrame(0);
            buttonSell.Draw(screen);
        }



        if (sellWindowcalled)
        {
            m_SellWindow->Draw(screen, 310, 166);
            buttonSell2.Draw(screen);
            
        }

        if (CheckMouseCollision(buttonSell2.GetCollider()) == true)
        {
            buttonSell2.GetSprite()->SetFrame(1);

            if ((buttonPressed & SDL_BUTTON_LMASK) != 0)
            {
                sellWindowcalled = false;
            }
        }
        else
        {
            buttonSell2.GetSprite()->SetFrame(0);
        }

        //------------------------------------------------------------------------------------------------------------

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
            newMonster = new Monster("assets/Slime.tga", 2, 0, 0, 1, 10, 25,25);
        }
        else if (typeOfMonster == 2)
        {
            newMonster = new Monster("assets/Golem.tga", 2, 0, 0, 1, 20, 50, 50);
        }
        else if (typeOfMonster == 3)
        {
            newMonster = new Monster("assets/Slime2.tga", 2, 0, 0, 1, 30, 60, 60);
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








};
