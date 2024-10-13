#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <iostream>
#include <string>

using namespace std;

class PlaylistNode {
public:
    // Constructors
    PlaylistNode();
    PlaylistNode(const std::string& id, const std::string& songName, const std::string& artistName, int songLength);

    // Member functions
    void InsertAfter(PlaylistNode* newNode);
    void SetNext(PlaylistNode* nextNode);
    std::string GetID() const;
    std::string GetSongName() const;
    std::string GetArtistName() const;
    int GetSongLength() const;
    PlaylistNode* GetNext() const;
    void PrintPlaylistNode() const;

private:
    std::string uniqueID;
    std::string songName;
    std::string artistName;
    int songLength;
    PlaylistNode* nextNodePtr;
};

class Playlist {
public:
    Playlist();
    void AddSong(const std::string& id, const std::string& songName, const std::string& artistName, int songLength);
    void RemoveSong(const std::string& id);
    void ChangePosition(int currentPosition, int newPosition);
    void OutputFullPlaylist() const;
    int OutputTotalTime() const;
    void OutputSongsByArtist(const std::string& artistName) const;
    int CountSongs() const;

private:
    PlaylistNode* head;
    PlaylistNode* tail;
};


void PrintMenu(const std::string& playlistTitle);

#endif