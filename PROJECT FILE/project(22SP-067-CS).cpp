#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

class MoodJournal {
private:
    string date;
    int moodScore;
    string userNote;

public:
    void addNewEntry() {
        cout << "\n\t=========================================" << endl;
        cout << "\t* NEW JOURNAL ENTRY            *" << endl;
        cout << "\t=========================================" << endl;
        
        cout << "\n\t[+] Enter Today's Date (DD-MM-YYYY): ";
        cin >> date;
        
        cout << "\n\tHow are you feeling today? \n" << endl;
        cout << "\t  [5] \x03  Super Happy / Excited" << endl; // \x03 se heart symbol banta hai
        cout << "\t  [4] \x01  Good / Relaxed" << endl;        // \x01 se smile symbol banta hai
        cout << "\t  [3] o_o Normal / Okay" << endl;
        cout << "\t  [2] -_- Low / Stressed" << endl;
        cout << "\t  [1] ;_; Very Sad / Lonely" << endl;
        cout << "\n\t[+] Enter Score (1-5): ";
        cin >> moodScore;
        
        while(moodScore < 1 || moodScore > 5) {
            cout << "\t[!] Invalid choice! Please enter between 1 and 5: ";
            cin >> moodScore;
        }

        cout << "\n\t[+] Write a short note about your day:\n\t> ";
        cin.ignore();
        getline(cin, userNote);

        saveToFile();
        analyzeMoodText(userNote);
    }

    void saveToFile() {
        ofstream outFile("journal_database.txt", ios::app); 
        
        if (outFile.is_open()) {
            outFile << date << " | " << moodScore << " | " << userNote << endl;
            outFile.close();
            cout << "\n\t>> [SUCCESS] Saved securely to database!" << endl;
        } else {
            cout << "\n\t>> [ERROR] Connection to file failed!" << endl;
        }
    }

    void analyzeMoodText(string text) {
        cout << "\n\t-----------------------------------------" << endl;
        cout << "\t* COGNITIVE REFLECTION          *" << endl;
        cout << "\t-----------------------------------------" << endl;

        if (text.find("stressed") != string::npos || text.find("tension") != string::npos || text.find("tired") != string::npos) {
            cout << "\t[CBT Advice]: It looks like you're carrying stress." << endl;
            cout << "\tRecommendation: Inhale for 4s, hold for 7s, exhale for 8s." << endl;
        }
        else if (text.find("sad") != string::npos || text.find("lonely") != string::npos || text.find("failed") != string::npos) {
            cout << "\t[CBT Advice]: One bad day doesn't mean a bad life." << endl;
            cout << "\tRecommendation: Write down 3 small things you are grateful for." << endl;
        }
        else if (text.find("happy") != string::npos || text.find("great") != string::npos || text.find("won") != string::npos) {
            cout << "\t[System]: Wonderful! Your positive energy is amazing." << endl;
            cout << "\tRecommendation: Capture what made today special & celebrate it!" << endl;
        }
        else {
            cout << "\t[System]: Self-reflection is a great step for your mind." << endl;
        }
        cout << "\t=========================================" << endl;
    }

    void viewJournalHistory() {
        ifstream inFile("journal_database.txt");
        string line;
        double totalScore = 0;
        int entryCount = 0;

        cout << "\n\t=========================================" << endl;
        cout << "\t* JOURNAL HISTORY             *" << endl;
        cout << "\t=========================================" << endl;

        if (!inFile.is_open()) {
            cout << "\t[i] No history found yet. Write your first entry!" << endl;
            return;
        }

        cout << "\n\tDATE       | SCORE | THOUGHTS" << endl;
        cout << "\t-----------------------------------------" << endl;

        while (getline(inFile, line)) {
            cout << "\t" << line << endl;
            
            size_t firstPipe = line.find('|');
            if (firstPipe != string::npos) {
                char scoreChar = line[firstPipe + 2];
                int score = scoreChar - '0';
                totalScore += score;
                entryCount++;
            }
        }
        inFile.close();

        cout << "\t-----------------------------------------" << endl;
        if (entryCount > 0) {
            double average = totalScore / entryCount;
            cout << "\tTotal Entries Tracked: " << entryCount << endl;
            cout << "\tAverage Well-being Score: " << average << " / 5.0" << endl;
            
            cout << "\tOverall Mood Status: ";
            if (average >= 4.0) cout << "Excellent & Stable!" << endl;
            else if (average >= 3.0) cout << "Doing Okay. Balanced." << endl;
            else cout << "Heavy week. Please take some rest." << endl;
        } else {
            cout << "\tNo valid entries to calculate average." << endl;
        }
        cout << "\t=========================================" << endl;
    }
};

int main() {
    MoodJournal myJournal;
    int choice;

    do {
        // ASCII Art Logo for attractive look
        cout << "\n\t  _  _                 _     _                               _ " << endl;
        cout << "\t | |/ | ___  ___  ____| |   | | ___  _   _  ____ ____  ____ | |" << endl;
        cout << "\t | ' / / _ \\/ _ \\/ _  | |   | |/ _ \\| | | |/ ___/  _ \\/ _  || |" << endl;
        cout << "\t | . \\|  __/ /_/ / /| | |___| | /_/ | |_| | |   | / | / /| || |" << endl;
        cout << "\t |_|\\_\\\\___|\\___/\\_||_|_____|_|\\___/ \\____|_|   |_| |_\\_||_||_|" << endl;
        
        cout << "\n\t=========================================" << endl;
        cout << "\t* MENTAL WELL-BEING JOURNAL       *" << endl;
        cout << "\t=========================================" << endl;
        cout << "\t  [1] Add Today's Mood & Thoughts" << endl;
        cout << "\t  [2] View Journal History & Analytics" << endl;
        cout << "\t  [3] Exit System" << endl;
        cout << "\t-----------------------------------------" << endl;
        cout << "\t[+] Enter choice (1-3): ";
        cin >> choice;

        switch(choice) {
            case 1:
                myJournal.addNewEntry();
                break;
            case 2:
                myJournal.viewJournalHistory();
                break;
            case 3:
                cout << "\n\t>> Thank you for journaling. Take care of your mind! Goodbye. \x03" << endl;
                break;
            default:
                cout << "\n\t[!] Invalid selection! Try again." << endl;
        }
    } while(choice != 3);

    return 0;
}

