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
    };
    int getShotsTaken() {
        return shotsTaken;
    };
    int getShotsMade() {
        return shotsMade;
    };
    int getPassesAttempted() {
        return passesAttempted;
    };
    int getPassesMade() {
        return passesMade;
    };

    //Setters for private variables 
    void setShotsTaken(int a) {
        shotsTaken += a;
    };
    void setShotsMade(int a) {
        shotsMade += a;
    };
    void setPassesAttempted(int a) {
        passesAttempted += 1;
    };
    void setPassesMade(int a) {
        passesMade += 1;
    }

    bool passBall(player currentPlayer) {
        int passesAttempted = currentPlayer.getPassesAttempted();
        int passesMade = currentPlayer.getPassesMade();

        int passChance = rand() % 100 + 1;
        double passPercentage = static_cast<double>(passesMade) / static_cast<double>(passesAttempted);

        if (passChance > (passPercentage + 50)) {
            currentPlayer.setPassesAttempted(1);
            cout << "Pass unsuccessful." << endl;
            return false;
        }
        else {
            currentPlayer.setPassesMade(1);
            cout << "Pass successful." << endl;
            return true;
        }
    }

    int takeShot(player currentPlayer) {
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
            shootingPercentage = static_cast<double>(shotsMade) / static_cast<double>(shotsTaken);
        }

        if (points == 1) {
            shotChance = rand() % 70 + 1;
        }
        else if (points == 2) {
            shotChance = rand() % 100 + 1;
        }
        else if (points == 3) {
            shotChance = rand() % 125 + 1;
        }
        else {
            cout << "Invalid number of points.\n";
        }

        cout << "Random number generated: " << shotChance << " Shooting percentage: " << shootingPercentage << endl;

        if (shotChance < (shootingPercentage + 50)) {
            cout << "Shot successful.\n";
            currentPlayer.setShotsMade(1);
            return points;
        }
        else {
            currentPlayer.setShotsTaken(1);
            cout << "Shot unsuccessful.\n";
        }
    }
};

int OpposingTeamPossesion(int opponentscore) {
    cout << "***********************************************\n";
    while (true) {
        bool shotMade = (rand() % 100) < 60;

        if (shotMade) {
            cout << "Opposing team made the shot! (2 Points)\n";
            opponentscore += 2;
        }
        else {
            bool rebound = (rand() % 100) < 50;
            if (rebound) {
                cout << "Opposing team made the rebound!\n";
            }
            else {
                cout << "Opposing team missed the rebound... Its your ball!\n";
                return false;
            }
        }
    }
    cout << "***********************************************\n";
    return opponentscore;
}

player pickplayer(player playernames[5]) {
    int randomnumber = (rand() % 5) + 1;
    player playerName = playernames[randomnumber - 1];
    return playerName;
}

int main() {
    player playernames[5] = { player("P1"),player("P2"),player("P3"),player("P4"),player("P5") };
    player opposingTeam(player("opposing"));
    int score1 = 0;
    int score2 = 0;
    int team1possessions = 0;
    int team2possessions = 0;
    player currentPlayer = pickplayer(playernames);
    while (team1possessions < 30 && team2possessions < 30) {
        // Asks the user to choose an option, moves to what they chose
        cout << "Choose an Action:\n 1. Shoot \n 2. Pass \n 3. See Player Stats \n 4. See score\n";
        int choice;
        cin >> choice;

        //shoot
        if (choice == 1) {
            int shotPoints = currentPlayer.takeShot(currentPlayer);
            score1 += shotPoints;
            if (shotPoints == 0) {
                bool chance = rand() % 100 < 50;
                if (not chance) {
                    team1possessions += 1;
                    currentPlayer = opposingTeam;
                    score2 = OpposingTeamPossesion(score2);
                    team2possessions += 1;
                    currentPlayer = pickplayer(playernames);
                }
            }

        }
        //pass
        else if (choice == 2) {
            int passedTo;
            cout << "Choose a player to pass the ball to: 1, 2, 3, 4, 5\n";
            cin >> passedTo;
            bool pass = currentPlayer.passBall(currentPlayer);
            if (pass) {
                currentPlayer = playernames[passedTo - 1];
                cout << "Current player in possession: " << currentPlayer.getName() << "\n";
            }
            else {
                currentPlayer = opposingTeam;
                score2 = OpposingTeamPossesion(score2);
                team2possessions += 1;
                currentPlayer = pickplayer(playernames);
            }
        }
        //print stats
        else if (choice == 3) {
            cout << "*****************************************\n";
            cout << "Player Name: " << currentPlayer.getName() << "\n";
            cout << "Shots Taken: " << currentPlayer.getShotsTaken() << "\n";
            cout << "Shots Made: " << currentPlayer.getShotsMade() << "\n";
            cout << "Passes Attempted: " << currentPlayer.getPassesAttempted() << "\n";
            cout << "Passes Made: " << currentPlayer.getPassesMade() << "\n";
            cout << "******************************************\n";
        }
        //print score
        else if (choice == 4) {
            cout << "Current score: " << score1 << "  -  " << score2 << endl;
        }
    }
}

