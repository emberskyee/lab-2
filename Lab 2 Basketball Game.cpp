#include <iostream>
#include <string>
using namespace std;

class player {
private:
    string name;
    int shotsTaken;
    int shotsMade;
    int passesAttempted;
    int passesMade;

public:
    player(const std::string& playerName) : name(playerName), shotsTaken(0), shotsMade(0), passesAttempted(0), passesMade(0) {}
    // Getters for private variables
    string getName() {
        return name;
    }
    int getShotsTaken() {
        return shotsTaken;
    }
    int getShotsMade() {
        return shotsMade;
    }
    int getPassesAttempted() {
        return passesAttempted;
    }
    int getPassesMade() {
        return passesMade;
    }

    //Setters for private variables 
    void setShotsTaken() {
        shotsTaken++;
    }
    void setShotsMade() {
        shotsMade++;
    }
    void setPassesAttempted() {
        passesAttempted++;
    }
    void setPassesMade() {
        passesMade++;
    }

    bool passBall(player& currentPlayer) {
        int passesAttempted = currentPlayer.getPassesAttempted();
        int passesMade = currentPlayer.getPassesMade();

        int passChance = rand() % 100 + 1;
        double passPercentage = static_cast<double>(passesMade) / static_cast<double>(passesAttempted);

        if (passChance > (passPercentage + 50)) {
            currentPlayer.setPassesAttempted();
            cout << "Pass unsuccessful.\n" << endl;
            return false;
        }
        else {
            currentPlayer.setPassesMade();
            cout << "Pass successful.\n" << endl;
            return true;
        }
    }

    int takeShot(player& currentPlayer) {
        int shotsTaken = currentPlayer.getShotsTaken();
        int shotsMade = currentPlayer.getShotsMade();
        double shootingPercentage;
        int points;
        cout << "Choose number of points to attempt: 1, 2, 3\n";
        cin >> points;
        int shotChance;

        if (shotsTaken == 0) {
            shootingPercentage = 0;
        }
        else {
            shootingPercentage = (static_cast<double>(shotsMade) / static_cast<double>(shotsTaken))*100;
        }

        if (points == 1) {
            shotChance = (rand() % 70 + 1);
        }
        else if (points == 2) {
            shotChance = (rand() % 100 + 1);
        }
        else if (points == 3) {
            shotChance = (rand() % 125 + 1);
        }
        else {
            cout << "Invalid number of points.\n\n";
        }

        cout << "Shot Chance: " << shotChance << " Shooting percentage: " << shootingPercentage << "\n" << endl;

        if (shotChance < (shootingPercentage + 50)) {
            cout << "Shot successful.\n" << endl;
            currentPlayer.setShotsMade();
            currentPlayer.setShotsTaken();
            return points;
        }
        else {
            currentPlayer.setShotsTaken();
            cout << "Shot unsuccessful.\n" << endl;
            return 0;
        }
    }
};

int OpposingTeamPossesion(int& opponentscore) {
    cout << "***********************************************\n";
    while (true) {
        cout << "Opposing team attempting shot...\n\n";
        bool shotMade = (rand() % 100) < 60;

        if (shotMade) {
            cout << "Opposing team made the shot! (2 Points) It's Your ball!\n";
            cout << "***********************************************\n";
            opponentscore += 2;
            return false;
        }
        else {
            cout << "Opposing team missed the shot!\n\n" << "Opposing team attempting rebound...\n\n";
            bool rebound = (rand() % 100) < 50;
            if (rebound) {
                cout << "Opposing team made the rebound!\n\n";
            }
            else {
                cout << "Opposing team missed the rebound... Its your ball!\n";
                cout << "***********************************************\n";
                return false;
            }
        }
    }
    return opponentscore;
}

player &pickplayer(player playernames[5]) {
    int randomnumber = (rand() % 5);
    return playernames[randomnumber];
    
}

int main() {
    player playernames[5] = { player("Lebron"),player("MJ"),player("Kobe"),player("Steph"),player("Jokic") };
    player opposingTeam(player("opposing"));
    int score1 = 0;
    int score2 = 0;
    int team1possessions = 0;
    int team2possessions = 0;
    int gamelength = 30;
    player* currentPlayer = &pickplayer(playernames);
    cout << "*****************************************\n" << "New game has been started.\n"<< endl; 

    while (team1possessions < gamelength && team2possessions < gamelength) {
        // Asks the user to choose an option, moves to what they chose
        cout << currentPlayer->getName() << " currently has the ball.\n\n";
        cout << "Choose an Action:\n 1. Shoot \n 2. Pass \n 3. See Player Stats \n 4. See score\n";
        int choice;
        cin >> choice;

        //shoot
        if (choice == 1) {
            int shotPoints = currentPlayer->takeShot(*currentPlayer);
            score1 += shotPoints;
            if (shotPoints == 0) {
                bool rebound = (rand() % 100) < 50;
                if (!(rebound)) {
                    team1possessions += 1;
                    currentPlayer = &opposingTeam;
                    cout << "You lost possession of the ball!\n";
                    score2 += OpposingTeamPossesion(score2);
                    team2possessions += 1;
                    cout << "Possesions Remaining: User - "<< (gamelength-team1possessions) << " Opponent - " << (gamelength -team2possessions) << "\n";
                    cout << "*****************************************\n";
                    currentPlayer = &pickplayer(playernames);
                }
                else{
                    cout << "You made the rebound! Choose next action. \n\n";
                }
            }
            else{
                team1possessions += 1;
                currentPlayer = &opposingTeam;
                score2 += OpposingTeamPossesion(score2);
                team2possessions += 1;
                cout << "Possesions Remaining: User - "<< (gamelength-team1possessions) << " Opponent - " << (gamelength -team2possessions) << "\n";
                cout << "*****************************************\n";
                currentPlayer = &pickplayer(playernames);
            }
            

        }
        //pass
        else if (choice == 2) {
            int passedTo;
            cout << "Choose a player to pass the ball to: 1. Lebron , 2. MJ , 3. Kobe, 4, Steph , 5. Jokic\n";
            cin >> passedTo;
            bool pass = currentPlayer->passBall(*currentPlayer);
            if (pass) {
                currentPlayer = &playernames[passedTo - 1];
            
            }
            else {
                cout << "You lost the ball!\n";
                currentPlayer = &opposingTeam;
                score2 += OpposingTeamPossesion(score2);
                team1possessions +=1;
                team2possessions += 1;
                cout << "Possesions Remaining: User - "<< (gamelength-team1possessions) << " Opponent - " << (gamelength -team2possessions) << "\n";
                cout << "*****************************************\n";
                currentPlayer = &pickplayer(playernames);
                cout << "Current player in possession of the ball: " << currentPlayer->getName() << endl;
            }
        }
        //print stats
        else if (choice == 3) {
            cout << "*****************************************\n";
            cout << "Player Name: " << currentPlayer->getName() << "\n";
            cout << "Shots Taken: " << currentPlayer->getShotsTaken() << "\n";
            cout << "Shots Made: " << currentPlayer->getShotsMade() << "\n";
            cout << "Passes Attempted: " << currentPlayer->getPassesAttempted() << "\n";
            cout << "Passes Made: " << currentPlayer->getPassesMade() << "\n";
            cout << "******************************************\n";
        }
        //print score
        else if (choice == 4) {
            cout << "Current score: " << score1 << "  -  " << score2 << "\n\n";
        }
    }
    string winner;
    if (score1 > score2) {
        winner = "Player's team!";
    }
    else {
        winner = "Opposing team!";
    }
    cout << "Game over!\n" << "Winner: " << winner << endl;
    cout << "The final score was: " << score1 << " - " << score2 << endl;
}
