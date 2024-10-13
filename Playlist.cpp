#include "Playlist.h"
#include <iostream>

using namespace std;

PlaylistNode::PlaylistNode() : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) {}

PlaylistNode::PlaylistNode(const std::string& id, const std::string& songName, const std::string& artistName, int songLength)
    : uniqueID(id), songName(songName), artistName(artistName), songLength(songLength), nextNodePtr(nullptr) {}

void PlaylistNode::InsertAfter(PlaylistNode* node) {
    if (node != nullptr) {
        node->SetNext(nextNodePtr);
        nextNodePtr = node;
    }
}

void PlaylistNode::SetNext(PlaylistNode* node) {
    nextNodePtr = node;
}

std::string PlaylistNode::GetID() const {
    return uniqueID;
}

std::string PlaylistNode::GetSongName() const {
    return songName;
}

std::string PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

void PlaylistNode::PrintPlaylistNode() const {
    std::cout << "Unique ID: " << uniqueID << endl;
    std::cout << "Song Name: " << songName << endl;
    std::cout << "Artist Name: " << artistName << endl;
    std::cout << "Song Length (in seconds): " << songLength;
}

void PrintMenu(const std::string& title);
void AddSong(PlaylistNode* &head, PlaylistNode* &tail);
void RemoveSong(PlaylistNode* &head);
void ChangePosition(PlaylistNode* &head);
void OutputSongsByArtist(PlaylistNode* head);
void OutputTotalTime(PlaylistNode* head);
void OutputFullPlaylist(PlaylistNode* head);

void PrintMenu(const std::string& title) {
    std::cout << title << " PLAYLIST MENU" << endl;
    std::cout << "a - Add song" << endl;
    std::cout << "d - Remove song" << endl;
    std::cout << "c - Change position of song" << endl;
    std::cout << "s - Output songs by specific artist" << endl;
    std::cout << "t - Output total time of playlist (in seconds)" << endl;
    std::cout << "o - Output full playlist" << endl;
    std::cout << "q - Quit" << endl << endl;

    std::cout << "Choose an option:" << endl; 
}

void AddSong(PlaylistNode* &head, PlaylistNode* &tail) {
    std::cout << "ADD SONG\n";
    std::string id, name, artist;
    int length;

    std::cout << "Enter song's unique ID:" << endl;
    std::cin >> id;
    std::cout << "Enter song's name:" << endl;
    std::cin.ignore();  
    std::getline(std::cin, name);
    std::cout << "Enter artist's name:" << endl;
    std::getline(std::cin, artist);
    std::cout << "Enter song's length (in seconds):" << endl;
    std::cout << std::endl;
    std::cin >> length;

    PlaylistNode* newNode = new PlaylistNode(id, name, artist, length);

    if (head == nullptr) {  
        head = newNode;
        tail = newNode;
    } else {
        tail->InsertAfter(newNode);
        tail = newNode;  
    }
}

void RemoveSong(PlaylistNode* &head) {
    std::cout << "REMOVE SONG\n";
    std::string id;
    std::cout << "Enter song's unique ID:\n";
    std::cin >> id;

    PlaylistNode* current = head;
    PlaylistNode* previous = nullptr;

    while (current != nullptr) {
        if (current->GetID() == id) {
            if (previous == nullptr) {  
                head = current->GetNext();
            } else {
                previous->SetNext(current->GetNext());
            }
            std::cout << "\"" << current->GetSongName() << "\" removed." << endl << endl;
            delete current;  
            return;
        }
        previous = current;
        current = current->GetNext();
    }
    std::cout << "Song not found.\n";
}

void ChangePosition(PlaylistNode* &head) {
    std::cout << "CHANGE POSITION OF SONG\n";
    int currentPosition, newPosition;
    std::cout << "Enter song's current position:\n";
    std::cin >> currentPosition;
    std::cout << "Enter new position for song:\n";
    std::cin >> newPosition;

    if (head == nullptr || currentPosition == newPosition) {
        return;
    }

    
    PlaylistNode* current = head;
    PlaylistNode* previous = nullptr;
    int position = 1;

    while (current != nullptr && position < currentPosition) {
        previous = current;
        current = current->GetNext();
        position++;
    }

    
    if (current == nullptr) {
        return;
    }

    PlaylistNode* songMoving = current;
    if (previous == nullptr) {
        head = head->GetNext();  
    } else {
        previous->SetNext(current->GetNext());
    }

    
    current = head;
    previous = nullptr;
    position = 1;

    while (current != nullptr && position < newPosition) {
        previous = current;
        current = current->GetNext();
        position++;
    }

    
    if (previous == nullptr) {
        songMoving->SetNext(head);
        head = songMoving;
    } else {
        songMoving->SetNext(previous->GetNext());
        previous->SetNext(songMoving);
    }

    std::cout << "\"" << songMoving->GetSongName() << "\" moved to position " << newPosition << std::endl << std::endl;
}



void OutputSongsByArtist(PlaylistNode* head) {
    std::cout << "OUTPUT SONGS BY SPECIFIC ARTIST\n";
    std::string artist;
    std::cout << "Enter artist's name:\n" << std::endl;
    std::cin.ignore();  
    std::getline(std::cin, artist);

    PlaylistNode* current = head;
    int position = 1;
    while (current != nullptr) {
        if (current->GetArtistName() == artist) {
            std::cout << position << ".\n";
            current->PrintPlaylistNode();
            std::cout << endl << endl;
        }
        current = current->GetNext();
        position++;
    }
}

void OutputTotalTime(PlaylistNode* head) {
    std::cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n";
    int totalTime = 0;

    PlaylistNode* current = head;
    while (current != nullptr) {
        totalTime += current->GetSongLength();
        current = current->GetNext();
    }

    std::cout << "Total time: " << totalTime << " seconds\n" << endl;
}

void OutputFullPlaylist(PlaylistNode* head) {
    if (head == nullptr) {
        std::cout << "Playlist is empty\n\n";
        return;
    }

    PlaylistNode* current = head;
    int position = 1;
    while (current != nullptr) {
        std::cout << position << ".\n";
        current->PrintPlaylistNode();
        if (current->GetNext() != nullptr) {
            std::cout << endl;
        }
        std::cout << endl;
        current = current->GetNext();
        position++;
    }
    std::cout << std::endl;
}
