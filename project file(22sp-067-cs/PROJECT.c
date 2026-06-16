#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MoodJournal {
    char date[20];
    int moodScore;
    char userNote[200];
};

void addNewEntry() {
    struct MoodJournal journal;
    printf("\n\t=========================================");
    printf("\n\t* NEW JOURNAL ENTRY                     *");
    printf("\n\t=========================================\n");
    
    printf("\n\t[+] Enter Today's Date (DD-MM-YYYY): ");
    scanf("%s", journal.date);
    
    printf("\n\tHow are you feeling today? \n\n");
    printf("\t  [5] Super Happy / Excited\n");
    printf("\t  [4] Good / Relaxed\n");
    printf("\t  [3] o_o Normal / Okay\n");
    printf("\t  [2] -_- Low / Stressed\n");
    printf("\t  [1] ;_; Very Sad / Lonely\n");
    printf("\n\t[+] Enter Score (1-5): ");
    scanf("%d", &journal.moodScore);
    
    while(journal.moodScore < 1 || journal.moodScore > 5) {
        printf("\t[!] Invalid choice! Please enter between 1 and 5: ");
        scanf("%d", &journal.moodScore);
    }

    printf("\n\t[+] Write a short note about your day:\n\t> ");
    getchar(); 
    fgets(journal.userNote, sizeof(journal.userNote), stdin);
    journal.userNote[strcspn(journal.userNote, "\n")] = 0; 

    FILE *outFile = fopen("journal_database.txt", "a");
    if (outFile != NULL) {
        fprintf(outFile, "%s | %d | %s\n", journal.date, journal.moodScore, journal.userNote);
        fclose(outFile);
        printf("\n\t>> [SUCCESS] Saved securely to database!\n");
    } else {
        printf("\n\t>> [ERROR] Connection to file failed!\n");
    }

    printf("\n\t-----------------------------------------");
    printf("\n\t* COGNITIVE REFLECTION                  *");
    printf("\n\t-----------------------------------------\n");

    if (strstr(journal.userNote, "stressed") != NULL || strstr(journal.userNote, "tension") != NULL || strstr(journal.userNote, "tired") != NULL) {
        printf("\t[CBT Advice]: It looks like you're carrying stress.\n");
        printf("\tRecommendation: Inhale for 4s, hold for 7s, exhale for 8s.\n");
    }
    else if (strstr(journal.userNote, "sad") != NULL || strstr(journal.userNote, "lonely") != NULL || strstr(journal.userNote, "failed") != NULL) {
        printf("\t[CBT Advice]: One bad day doesn't mean a bad life.\n");
        printf("\tRecommendation: Write down 3 small things you are grateful for.\n");
    }
    else if (strstr(journal.userNote, "happy") != NULL || strstr(journal.userNote, "great") != NULL || strstr(journal.userNote, "won") != NULL) {
        printf("\t[System]: Wonderful! Your positive energy is amazing.\n");
        printf("\tRecommendation: Capture what made today special & celebrate it!\n");
    }
    else {
        printf("\t[System]: Self-reflection is a great step for your mind.\n");
    }
    printf("\t=========================================\n");
}

void viewJournalHistory() {
    FILE *inFile = fopen("journal_database.txt", "r");
    char line[300];
    double totalScore = 0;
    int entryCount = 0;

    printf("\n\t=========================================");
    printf("\n\t* JOURNAL HISTORY                       *");
    printf("\n\t=========================================\n");

    if (inFile == NULL) {
        printf("\t[i] No history found yet. Write your first entry!\n");
        return;
    }

    printf("\n\tDATE       | SCORE | THOUGHTS\n");
    printf("\t-----------------------------------------\n");

    while (fgets(line, sizeof(line), inFile)) {
        printf("\t%s", line);
        
        char *firstPipe = strchr(line, '|');
        if (firstPipe != NULL) {
            char scoreChar = *(firstPipe + 2);
            int score = scoreChar - '0';
            totalScore += score;
            entryCount++;
        }
    }
    fclose(inFile);

    printf("\t-----------------------------------------\n");
    if (entryCount > 0) {
        double average = totalScore / entryCount;
        printf("\tTotal Entries Tracked: %d\n", entryCount);
        printf("\tAverage Well-being Score: %.1f / 5.0\n", average);
        
        printf("\tOverall Mood Status: ");
        if (average >= 4.0) printf("Excellent & Stable!\n");
        else if (average >= 3.0) printf("Doing Okay. Balanced.\n");
        else printf("Heavy week. Please take some rest.\n");
    } else {
        printf("\tNo valid entries to calculate average.\n");
    }
    printf("\t=========================================\n");
}

int main() {
    int choice;

    do {
        printf("\n\t  _  _                 _     _                               _ ");
        printf("\n\t | |/ | ___  ___  ____| |   | | ___  _   _  ____ ____  ____ | |");
        printf("\n\t | ' / / _ \\/ _ \\/ _  | |   | |/ _ \\| | | |/ ___/  _ \\/ _  || |");
        printf("\n\t | . \\|  __/ /_/ / /| | |___| | /_/ | |_| | |   | / | / /| || |");
        printf("\n\t |_|\\_\\\\___|\\___/\\_||_|_____|_|\\___/ \\____|_|   |_| |_\\_||_||_|");
        
        printf("\n\n\t=========================================");
        printf("\n\t* MENTAL WELL-BEING JOURNAL             *");
        printf("\n\t=========================================");
        printf("\n\t  [1] Add Today's Mood & Thoughts");
        printf("\n\t  [2] View Journal History & Analytics");
        printf("\n\t  [3] Exit System");
        printf("\n\t-----------------------------------------");
        printf("\n\t[+] Enter choice (1-3): ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addNewEntry();
                break;
            case 2:
                viewJournalHistory();
                break;
            case 3:
                printf("\n\t>> Thank you for journaling. Take care of your mind! Goodbye.\n");
                break;
            default:
                printf("\n\t[!] Invalid selection! Try again.\n");
        }
    } while(choice != 3);

    return 0;
}
