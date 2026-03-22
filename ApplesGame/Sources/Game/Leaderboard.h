//@file Leaderboard.h

#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace ApplesGame
{
    struct Record
    {
        std::string name;
        int score = 0;
    };

    class Leaderboard
    {
    public:
        void Load();
        void Save() const;

        void GenerateDefault();
        void UpdatePlayer(const std::string& name, int score);

        const std::vector<Record>& GetSorted() const;

    private:
        void RebuildSorted();
        static void Sort(std::vector<Record>& records);

    private:
        std::unordered_map<std::string, int> m_Data;
        std::vector<Record> m_Sorted;
    };
}