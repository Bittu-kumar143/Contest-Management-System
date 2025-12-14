#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cstring> //for strcmp

using namespace std;

class person
{
protected:
    char ID[100];
    char password[100];

public:
    static int budget;
    char name[100];
    char gender;

    const char *getID() const
    {
        return ID;
    }

    person()
    {
        cout << "\nEnter the ID : ";
        cin >> ID;
        cout << "Enter the password : ";
        cin >> password;
        cout << "Enter the name : ";
        cin >> name;
        cout << "Enter the gender : ";
        cin >> gender;
    }

    ~person() {}
};

int person::budget = 0;

class admin : public person
{
private:
    static int adminPassword;

public:
    bool checkpassword(int a)
    {
        return (a == adminPassword);
    }
     void write(ofstream &outfile)
    {
        outfile << ID << " " << name << " " << gender << endl;
    }

    void read(ifstream &infile)
    {
        infile >> ID >> name >> gender;
    }
    admin() {}
    ~admin() {}
};

int admin::adminPassword = 22103009;

class organizer : public person
{
public:
    organizer()
    {
        budget += 2000;
    }
    ~organizer() {}
};

class finance : public organizer
{
public:
    static finance *finance_players;

    finance() {}

    finance(int numContestants)
    {
        finance_players = new finance[numContestants];
    }

    void write(ofstream &outfile)
    {
        outfile << ID << " " << name << " " << gender << endl;
    }

    void read(ifstream &infile)
    {
        infile >> ID >> name >> gender;
    }
    ~finance()
    {
        delete[] finance_players;
    }
};

finance *finance::finance_players = nullptr;

class management : public organizer
{
public:
    static management *management_players;

    management() {}

    management(int numContestants)
    {
        management_players = new management[numContestants];
    }

     void write(ofstream &outfile)
    {
        outfile << ID << " " << name << " " << gender << endl;
    }

    void read(ifstream &infile)
    {
        infile >> ID >> name >> gender;
    }

    ~management()
    {
        delete[] management_players;
    }
};

management *management::management_players = nullptr;

class decoration : public organizer
{
public:
    static decoration *decoration_players;

    decoration() {}

    decoration(int numContestants)
    {
        decoration_players = new decoration[numContestants];
    }

     void write(ofstream &outfile)
    {
        outfile << ID << " " << name << " " << gender << endl;
    }

    void read(ifstream &infile)
    {
        infile >> ID >> name >> gender;
    }

    ~decoration()
    {
        delete[] decoration_players;
    }
};

decoration *decoration::decoration_players = nullptr;

class contestant : public person
{
public:
    int age;
    int position;
    int prize_money;

    contestant()
    {
        cout << "Enter the age : ";
        cin >> age;
        budget += 500;
    }

    virtual int calc_score() = 0;
    virtual void get_parameters() = 0;

    void getdata()
    {
        cout << ID << "\t" << name << "\t" << age << "\t";
    }

    virtual void writeToFile(ofstream &outfile)
    {
        outfile << ID << " " << name << " " << age << " ";
    }

    virtual void readFromFile(ifstream &infile)
    {
        infile >> ID >> name >> age;
    }

    ~contestant() {}
};

class coding : public contestant
{
    int rating;
    int no_of_questions_solved;
    float avg_acceptance_rate;
    int avg_time_complexity;
    int avg_space_complexity;

public:
    static coding *coding_players;

    coding(int numContestants)
    {
        coding_players = new coding[numContestants];
    }

    void get_parameters()
    {
        cout << "Enter the coder's ratings : ";
        cin >> rating;
        cout << "Enter the number of questions solved : ";
        cin >> no_of_questions_solved;
        cout << "Enter the average acceptance rate : ";
        cin >> avg_acceptance_rate;
        cout << "Enter the average time complexity (in ms) : ";
        cin >> avg_time_complexity;
        cout << "Enter the average space complexity (in mb) : ";
        cin >> avg_space_complexity;
    }

    int calc_score()
    {
        return no_of_questions_solved * 5 + avg_acceptance_rate * 5 - avg_time_complexity * 2 - avg_space_complexity * 2;
    }

    void writeToFile(ofstream &outfile) override
    {
        contestant::writeToFile(outfile);
        outfile << rating << " " << no_of_questions_solved << " " << avg_acceptance_rate << " "
                << avg_time_complexity << " " << avg_space_complexity << endl;
    }

    void readFromFile(ifstream &infile) override
    {
        contestant::readFromFile(infile);
        infile >> rating >> no_of_questions_solved >> avg_acceptance_rate >> avg_time_complexity >> avg_space_complexity;
    }

    coding() {}
    ~coding() {}
};

class chess : public contestant
{
    int no_of_games_won_with_white;
    int no_of_games_won_with_black;
    int draws;

public:
    static chess *chess_players;

    chess(int numContestants)
    {
        chess_players = new chess[numContestants];
    }

    int calc_score()
    {
        return no_of_games_won_with_black * 3 + no_of_games_won_with_white * 2 + draws;
    }

    void get_parameters()
    {
        cout << "Enter the number of games won with white : ";
        cin >> no_of_games_won_with_white;
        cout << "Enter the number of games won with black : ";
        cin >> no_of_games_won_with_black;
        cout << "Enter the number of games drawn : ";
        cin >> draws;
    }

    void writeToFile(ofstream &outfile) override
    {
        contestant::writeToFile(outfile);
        outfile << no_of_games_won_with_white << " " << no_of_games_won_with_black << " " << draws << endl;
    }

    void readFromFile(ifstream &infile) override
    {
        contestant::readFromFile(infile);
        infile >> no_of_games_won_with_white >> no_of_games_won_with_black >> draws;
    }

    chess() {}
    ~chess() {}
};

class debate : public contestant
{
    int victories_as_PM;
    int victories_as_DPM;
    int victories_as_whip;
    int victories_as_LO;
    int victories_as_DLO;
    int victories_as_O_whip;
    int total_games_played;

public:
    static debate *debate_players;

    // const char* getID() const{
    //     return ID;
    // }

    debate(int numContestants)
    {
        debate_players = new debate[numContestants];
    }

    void get_parameters()
    {
        cout << "Enter the number of victories as PM : ";
        cin >> victories_as_PM;
        cout << "Enter the number of victories as DPM : ";
        cin >> victories_as_DPM;
        cout << "Enter the number of victories as whip : ";
        cin >> victories_as_whip;
        cout << "Enter the number of victories as LO : ";
        cin >> victories_as_LO;
        cout << "Enter the number of victories as DLO : ";
        cin >> victories_as_DLO;
        cout << "Enter the number of victories as O-Whip : ";
        cin >> victories_as_O_whip;
        cout << "Enter the total number of games played by the player : ";
        cin >> total_games_played;
    }

    int calc_score()
    {
        return victories_as_LO * 7 + victories_as_DLO * 5 + victories_as_DPM * 4 + victories_as_PM * 6 +
               victories_as_whip * 2 + victories_as_O_whip * 3 + total_games_played;
    }

    void writeToFile(ofstream &outfile) override
    {
        contestant::writeToFile(outfile);
        outfile << victories_as_PM << " " << victories_as_DPM << " " << victories_as_whip << " "
                << victories_as_LO << " " << victories_as_DLO << " " << victories_as_O_whip << " "
                << total_games_played << endl;
    }

    void readFromFile(ifstream &infile) override
    {
        contestant::readFromFile(infile);
        infile >> victories_as_PM >> victories_as_DPM >> victories_as_whip >> victories_as_LO >> victories_as_DLO >> victories_as_O_whip >> total_games_played;
    }

    debate() {}
    ~debate() {}
};

void prize_money(int budg)
{
    float prize_money = budg / 3;
    cout << "\nPrize allocated for 1st place holder : " << prize_money * 0.5712;
    cout << "\nPrize allocated for 2nd place holder : " << prize_money * 0.2856;
    cout << "\nPrize allocated for 3rd place holder : " << prize_money * 0.1428;
    cout << "\nExpenditure on event organization : " << float(budg / 3);
    float salaries = budg / 3;
    cout << "\nAmount granted to organizers team : " << salaries * 0.7;
    cout << "\nAmount granted to admins team : " << salaries * 0.3;
}

template <typename t>
void sort(int scores[], t players[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (scores[j] > scores[j + 1])
            {
                int temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
                t v = players[j];
                players[j] = players[j + 1];
                players[j + 1] = v;
            }
        }
    }
}

template <class T>
void save(T *team, int numMembers, const char *fileName)
{
    ofstream outfile(fileName, ios::out | ios::trunc);

    for (int i = 0; i < numMembers; ++i)
    {
        team[i].write(outfile);
    }

    outfile.close();
}

template <class T>
void read(T *team, int numMembers, const char *fileName)
{
    ifstream infile(fileName);

    for (int i = 0; i < numMembers; ++i)
    {
        team[i].read(infile);
    }

    infile.close();
}

template <typename T>
void storeContestantDataToFile(T *contestants, int numContestants, const char *fileName)
{
    ofstream outfile(fileName, ios::out | ios::ate); // Open file in truncation mode

    for (int i = 0; i < numContestants; ++i)
    {
        contestants[i].writeToFile(outfile);
    }

    outfile.close();
}

template <typename T>
void readContestantDataFromFile(T *contestants, int numContestants, const char *fileName)
{
    ifstream infile(fileName);

    for (int i = 0; i < numContestants; ++i)
    {
        contestants[i].readFromFile(infile);
    }

    infile.close();
}

template <typename T>
void saveDataToFile(T *contestants, int numContestants, const char *fileName)
{
    ofstream outfile(fileName);

    for (int i = 0; i < numContestants; ++i)
    {
        contestants[i].writeToFile(outfile);
        outfile << endl; // Add a newline after each contestant's data
    }

    outfile.close();
}

template <typename T>
void modifyContestantDataByID(T *contestants, int numContestants, const char *fileName)
{
    cout << "Enter the ID of the contestant you want to modify: ";
    char targetID[100];
    cin >> targetID;

    int index = -1;
    for (int i = 0; i < numContestants; ++i)
    {
        if (strcmp(contestants[i].getID(), targetID) == 0)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Contestant with ID " << targetID << " not found.\n";
        return;
    }

    cout << "\nEnter new age for contestant " << targetID << ": ";
    cin >> contestants[index].age;

    // Open the file for writing
    ofstream outfile(fileName);

    // Write updated data to the file
    for (int i = 0; i < numContestants; ++i)
    {
        contestants[i].writeToFile(outfile);
        outfile << endl; // Add a newline after each contestant's data
    }

    // Close the file
    outfile.close();

    cout << "Contestant data modified and saved to file.\n";
}

template <typename T>
void createLeaderboardFile(const char *fileName, T *players, vector<int> &scores)
{
    ofstream outfile(fileName, ios::out | ios::ate); // Open file in truncation mode
    if (!outfile.is_open())
    {
        cout << "Error opening file for writing!\n";
        return;
    }

    for (int i = 0; i < scores.size(); ++i)
    {
        scores[i] = players[i].calc_score();
        players[i].writeToFile(outfile);
        outfile << scores[i] << "\n";
    }

    outfile.close();
}

template <typename T>
void readLeaderboardFile(const char *fileName, T *players, vector<int> &scores)
{
    ifstream infile(fileName); // Open file in default mode (no truncation)
    if (!infile.is_open())
    {
        cout << "Error opening file for reading!\n";
        return;
    }

    for (int i = 0; i < scores.size(); ++i)
    {
        players[i].readFromFile(infile);
        infile >> scores[i];
        infile.ignore();
    }

    infile.close();
}

template <typename T>
void displayLeaderboard(T *players, vector<int> &scores)
{
    cout << "Leaderboard:\n";
    cout << "ID\tName\tAge\tScore\n";

    for (int i = static_cast<int>(scores.size()) - 1; i >= 0; --i)
    {
        players[i].getdata();
        cout << scores[i] << "\n";
    }
}

int main()
{
    debate *debate_players = nullptr;
    chess *chess_players = nullptr;
    coding *coding_players = nullptr;
    finance *finance_team = nullptr;
    management *management_team = nullptr;
    decoration *decoration_team = nullptr;
    admin *admin_team = nullptr;

    int cp, cc, dc, ft, mt, dt, bt;
label:

    cout << "\n1. Set data\n2. Get Data\n3. Modify data\n4. Start contests\n5. EXIT: ";
    int menu1;
    cin >> menu1;

    if (menu1 == 1)
    {
        cout << "Enter your class: ";
        char c;
        cin >> c;

        if (c == 'A' || c == 'a')
        {
            int pass;
            cout << "\nVerification\nEnter the password(Enter 0 to go back): ";
            cin >> pass;

            int k = 3;
            while (k > 0)
            {
                if (pass == 0)
                    goto label;

                if (admin_team->checkpassword(pass))
                    break;
                else
                {
                    k--;
                    cout << "Invalid password!, attempts left: " << k;
                }

                if (k == 0)
                    return 0;

                cout << "Enter again(Enter 0 to go back): ";
                cin >> pass;
            }

            if (k <= 0)
            {
                cout << "\nSystem locked!";
                return 0;
            }
            else
            {
                int go_back_flag;
                cout << "\nCAUTION: The above procedure requires full engagement and cannot be stopped in between. Wish to continue?(1/0): ";
                cin >> go_back_flag;

                if (go_back_flag == 0)
                    goto label;
                cout << "\nINDEX -\n1. Set contestants data\n2. Set Organizers data\n3. Set Administrators data\n";

                cout << "Setting contestants data: \n";

                cout << "Coding contestants: ";
                cout << "\nEnter the number of contestants: ";
                cin >> cp;
                coding_players = new coding[cp];

                cout << "Chess contestants: ";
                cout << "\nEnter the number of contestants: ";
                cin >> cc;
                chess_players = new chess[cc];

                cout << "Debate contestants: ";
                cout << "\nEnter the number of contestants: ";
                cin >> dc;
                debate_players = new debate[dc];

                cout << "Setting organizers data: ";

                cout << "\nFinance team: ";
                cout << "\nEnter the number of finance team members: ";
                cin >> ft;
                finance_team = new finance[ft];

                cout << "\nManagement team: ";
                cout << "\nEnter the number of management team members: ";
                cin >> mt;
                management_team = new management[mt];

                cout << "\nDecoration team: ";
                cout << "\nEnter the number of decoration team members: ";
                cin >> dt;
                decoration_team = new decoration[dt];

                cout << "\nSetting administrators data: ";

                cout << "\nB class administrators data: ";
                cout << "\nEnter the number of B-class administrators: ";
                cin >> bt;
                admin_team= new admin[bt];
                cout << "\nData added successfully!\n";
                goto label;
            }
        }
        else if (c == 'B' || c == 'b')
        {
            cout << "\nClass B admins cannot set the data!\n";
            goto label;
        }
    }
    else if (menu1 == 2)
    {
        // Display coding contestant data
        saveDataToFile(coding_players, cp, "coding_contestant_data.txt");
        readContestantDataFromFile(coding_players, cp, "coding_contestant_data.txt");
        for (int i = 0; i < cp; ++i)
        {
            cout << "\nCoding Contestant " << i + 1 << " Data:\n";
            coding_players[i].getdata();
        }

        // Display chess contestant data
        saveDataToFile(chess_players, cc, "chess_contestant_data.txt");
        readContestantDataFromFile(chess_players, cc, "chess_contestant_data.txt");
        for (int i = 0; i < cc; ++i)
        {
            cout << "\nChess Contestant " << i + 1 << " Data:\n";
            chess_players[i].getdata();
        }

        // Display debate contestant data
        saveDataToFile(debate_players, dc, "debate_contestant_data.txt");
        readContestantDataFromFile(debate_players, dc, "debate_contestant_data.txt");
        for (int i = 0; i < dc; ++i)
        {
            cout << "\nDebate Contestant " << i + 1 << " Data:\n";
            debate_players[i].getdata();
        }

        save(finance_team, ft, "finance_data.txt");
        // Read finance team data from file
        read(finance_team, ft, "finance_data.txt");
        // Display finance team data
        cout << "\nFinance Team Data:\n";
        for (int i = 0; i < ft; ++i)
        {
            cout << "ID: " << finance_team[i].getID() << ", Name: " << finance_team[i].name << ", Gender: " << finance_team[i].gender << endl;
        }

        save(management_team, mt, "management_data.txt");
        // Read management team data from file
        read(management_team, mt, "management_data.txt");
        // Display management team data
        cout << "\nManagement Team Data:\n";
        for (int i = 0; i < mt; ++i)
        {
            cout << "ID: " << management_team[i].getID() << ", Name: " << management_team[i].name << ", Gender: " << management_team[i].gender << endl;
        }

         save(decoration_team, dt, "decoration_data.txt");
        // Read decoration team data from file
        read(decoration_team, dt, "decoration_data.txt");
        // Display decoration team data
        cout << "\ndecoration Team Data:\n";
        for (int i = 0; i < dt; ++i)
        {
            cout << "ID: " << decoration_team[i].getID() << ", Name: " << decoration_team[i].name << ", Gender: " << decoration_team[i].gender << endl;
        }

         save(admin_team, bt, "admin_data.txt");
        // Read admin team data from file
        read(admin_team, bt, "admin_data.txt");
        // Display admin team data
        cout << "\nadmin Team Data:\n";
        for (int i = 0; i < bt; ++i)
        {
            cout << "ID: " << admin_team[i].getID() << ", Name: " << admin_team[i].name << ", Gender: " << admin_team[i].gender << endl;
        }



        goto label;
    }
    else if (menu1 == 3)
    {
        int menu2;
        cout << "\nSearch in - \n1.Debating contestants database\n2.Coding contestants database\n3.Chess contestants database : ";
        cin >> menu2;
        if (menu2 == 1)
        {
            cout << "Debate ------->>>>>>>" << endl;
            modifyContestantDataByID(debate_players, dc, "debate_contestant_data.txt");
        }
        else if (menu2 == 2)
        {
            cout << "Coding ------->>>>>>>" << endl;
            modifyContestantDataByID(coding_players, cp, "coding_contestant_data.txt");
        }
        else if (menu2 == 3)
        {
            cout << "chess ------->>>>>>>" << endl;
            modifyContestantDataByID(chess_players, cc, "chess_contestant_data.txt");
        }
        goto label;
    }
    else if (menu1 == 4)
    {
        cout << "The Coding contest begins!";
        for (int i = 0; i < cp; ++i)
        {
            cout << "\nEnter data for Coding Contestant " << i + 1 << ":\n";
            coding_players[i].get_parameters();
        }

        // Store coding contestant data to file
        saveDataToFile(coding_players, cp, "coding_contestant_data.txt");

        cout << "The Chess contest begins!";
        for (int i = 0; i < cc; ++i)
        {
            cout << "\nEnter data for Chess Contestant " << i + 1 << ":\n";
            chess_players[i].get_parameters();
        }

        // Store chess contestant data to file
        saveDataToFile(chess_players, cc, "chess_contestant_data.txt");

        cout << "The Debate contest begins!";
        for (int i = 0; i < dc; ++i)
        {
            cout << "\nEnter data for Debate Contestant " << i + 1 << ":\n";
            debate_players[i].get_parameters();
        }

        // Store debate contestant data to file
        saveDataToFile(debate_players, dc, "debate_contestant_data.txt");

        cout << "\nContest is over!\n";

        int end;
        vector<int> chess_scores(cc);
        vector<int> coding_scores(cp);
        vector<int> debate_scores(dc);

        for (int i = 0; i < dc; i++)
        {
            debate_scores[i] = debate_players[i].calc_score();
        }

        for (int i = 0; i < cp; i++)
        {
            coding_scores[i] = coding_players[i].calc_score();
        }

        for (int i = 0; i < cc; i++)
        {
            chess_scores[i] = chess_players[i].calc_score();
        }

        // Sort coding contestants
        sort(coding_scores.data(), coding_players, cp);

        // Sort chess contestants
        sort(chess_scores.data(), chess_players, cc);

        // Sort debate contestants
        sort(debate_scores.data(), debate_players, dc);

        createLeaderboardFile("debate_leaderboard.txt", debate_players, debate_scores);
        readLeaderboardFile("debate_leaderboard.txt", debate_players, debate_scores);

        createLeaderboardFile("coding_leaderboard.txt", coding_players, coding_scores);
        readLeaderboardFile("coding_leaderboard.txt", coding_players, coding_scores);

        createLeaderboardFile("chess_leaderboard.txt", chess_players, chess_scores);
        readLeaderboardFile("chess_leaderboard.txt", chess_players, chess_scores);

        while (1)
        {
            cout << "\n1. Leaderboard\n2. Declare winners\n3. Payroll\n4. Exit";
            cin >> end;

            if (end == 1)
            {

                if (cc > 0)
                {
                    cout << "chess-------" << endl;
                    displayLeaderboard(chess_players, chess_scores);
                }

                if (cp > 0)
                {
                    cout << "coding-------" << endl;
                    displayLeaderboard(coding_players, coding_scores);
                }

                if (dc > 0)
                {
                    cout << "debate-------" << endl;
                    displayLeaderboard(debate_players, debate_scores);
                }
            }
            else if (end == 2)
            {
                if (cp > 0)
                {
                    cout << "Coding - \n";
                    cout << "ID\tName\tAge\tScore\n";
                    for (int i = cp - 1; i >= max(cp - 4, 0); i--)
                    {
                        coding_players[i].getdata();
                        cout << coding_scores[i] << "\n";
                    }
                }

                if (cc > 0)
                    cout << "Chess - \n";
                cout << "ID\tName\tAge\tScore\n";
                for (int i = cc - 1; i >= max(cc - 4, 0); i--)
                {
                    chess_players[i].getdata();
                    cout << chess_scores[i] << "\n";
                }


                if (dc > 0)
                {
                    cout << "Debate - \n";
                    cout << "ID\tName\tAge\tScore\n";
                    for (int i = dc - 1; i >= max(dc - 4, 0); i--)
                    {
                        debate_players[i].getdata();
                        cout << debate_scores[i] << "\n";
                    }
                }
            }
            else if (end == 3)
            {
                prize_money(person::budget);
                cout << "\n";
            }
            else if (end == 4)
            {
                break;
            }
        }
    }
    else if (menu1 == 5)
    {
        return 0;
    }

    // Free allocated memory
    delete[] coding_players;
    delete[] chess_players;
    delete[] debate_players;
    delete[] finance_team;
    delete[] management_team;
    delete[] decoration_team;
    delete[] admin_team;

   return 0;
}