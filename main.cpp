#include <iostream>
#include "Playlist.h"

using namespace std;

void PrintMenu(const std::string& title);
void AddSong(PlaylistNode*& head, PlaylistNode*& tail);
void RemoveSong(PlaylistNode*& head);
void ChangePosition(PlaylistNode*& head);
void OutputSongsByArtist(PlaylistNode* head);
void OutputTotalTime(PlaylistNode* head);
void OutputFullPlaylist(PlaylistNode* head);

int main() {
    std::string playlistTitle;

    
    std::cout << "Enter playlist's title:" << endl << endl;
    std::getline(std::cin, playlistTitle);

    PlaylistNode* head = nullptr; 
    PlaylistNode* tail = nullptr;

    char choice = ' '; 
    while (choice != 'q') {
        PrintMenu(playlistTitle);
        std::cin >> choice;

        if (choice == 'a') {
            AddSong(head, tail);
        } else if (choice == 'd') {
            RemoveSong(head);
        } else if (choice == 'c') {
            ChangePosition(head);
        } else if (choice == 's') {
            OutputSongsByArtist(head);
        } else if (choice == 't') {
            OutputTotalTime(head);
        } else if (choice == 'o') {
            std::cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;  
            OutputFullPlaylist(head);  
        } else if (choice != 'q') {
            std::cout << "Invalid option. Please try again." << endl << endl;
        }
    }

    
    while (head != nullptr) {
        PlaylistNode* temp = head;
        head = head->GetNext();
        delete temp;
    }

    return 0;
}
