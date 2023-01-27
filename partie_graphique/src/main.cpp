#include <SFML/Graphics.hpp>
#include "main.hpp"
#include "minijeu1.hpp"
#include "minijeu2.hpp"
#include "minijeu3.hpp"

int main()
{   
    const int GAME_SIZE=8;
    Team t1("FRA",100);
    Team t2("BRA",110);
    Team t3("USA",80);
    Team t4("MAR",90);
    Team t5("TUN",75);
    Team t6("ARG",120);
    Team t7("BLG",70);
    Team t8("GER",75);
    vector<Team> teams{t1,t2,t3,t4,t5,t6,t7,t8};

    Game mainGame( teams );

    mainGame.setSize(GAME_SIZE);
    cout <<"Game is of size = " <<teams.size()<< endl;

    cout<< "Starting Game ... " <<endl;

    vector<Team> visibleTeams=mainGame.getTeams();

    // Create the main window
    sf::RenderWindow mainWindow(sf::VideoMode(800, 600), "Main Window");
    mainWindow.setKeyRepeatEnabled(false);

    // Create the second window
    sf::RenderWindow secondWindow(sf::VideoMode(800, 600), "Second Window", sf::Style::Default);
    secondWindow.setPosition(sf::Vector2i(800, 600));

    PFCGame minijeu1(&secondWindow);
    int result1=3;
    minijeu_p minijeu2(&secondWindow);
    minijeu3 minjeu3(&secondWindow);

    sf::Clock clock; // starts the clock

    while (mainWindow.isOpen())
    {
        // Handle events in the main window
        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W){
                mainGame.incrementState();

                if (mainGame.getState()==1)
                    PFCGame minijeu1(&secondWindow);

                else if (mainGame.getState()==2)
                    minijeu_p minijeu2(&secondWindow);
            
                else if (mainGame.getState()==3){
                    minijeu3 minjeu3(&secondWindow);
                }
                playRound(&mainGame);
                
                vector<Team> winners=mainGame.getWinners();
                visibleTeams.insert(visibleTeams.end() , winners.begin(),winners.end());

                // cout<< "visible teams size : "<<visibleTeams.size()<<endl;; 
                // cout<< "winners  size : "<<winners.size()<< endl; 
                mainGame.nextRound();

            }

        }

        // Clear the main window
        mainWindow.clear(sf::Color::White);

        sf::Time elapsed1 = clock.getElapsedTime();
        if (elapsed1.asSeconds() < 1)
        {
            //cout<<"-----WAITING ------------\n";
        }
        else{// Draw to the main window
        mainWindowDraw(&mainWindow, visibleTeams);
        }
        // Display the main window
        mainWindow.display();

        // Handle events in the second window
        while (secondWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || mainGame.getState()==0)
                secondWindow.close();
        }

        // Clear the second window
        //secondWindow.clear(sf::Color::White);

        // Draw to the second window
        if (mainGame.getState()==1){
            //cout << "---------------\n    run state is 1 \n ----------\n";
            minijeu1.run(&secondWindow, &result1);
        }
        else if (mainGame.getState()==2){
            //cout << "---------------\n    run state is 2 \n ----------\n";
            minijeu2.run(&secondWindow);
        }
        else if (mainGame.getState()==3){
            //cout << "---------------\n    run state is 3 \n ----------\n";
            minjeu3.run(&secondWindow);
        } 


        // Display the second window
        //secondWindow.display();
    }

    return 0;
}
