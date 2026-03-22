//@file Leaderboard.cpp

#include "Leaderboard.h"

#include <cstdlib>
#include <fstream>
#include <utility>

namespace ApplesGame
{
    namespace
    {
        const char* k_FileName = "scores.txt";

        constexpr int k_FakePlayersCount = 6;

        const char* k_FakeNames[k_FakePlayersCount] =
        {
            "Rodion",
            "Tikhon",
            "Missha",
            "Eva",
            "Dassha",
            "Sergey"
        };

        int RandomScore()
        {
            return 30 + (std::rand() % 121);
        }
    }

    void Leaderboard::Load()
    {
        m_Data.clear();

        std::ifstream file(k_FileName);

        if (!file.is_open())
        {
            GenerateDefault();
            return;
        }

        std::string name;
        int score = 0;

        while (file >> name >> score)
        {
            m_Data[name] = score;
        }

        file.close();

        if (m_Data.empty())
        {
            GenerateDefault();
            return;
        }

        RebuildSorted();
    }

    void Leaderboard::Save() const
    {
        std::ofstream file(k_FileName, std::ios::trunc);

        for (const auto& pair : m_Data)
        {
            file << pair.first << " " << pair.second << "\n";
        }

        file.close();
    }

    void Leaderboard::GenerateDefault()
    {
        m_Data.clear();

        for (int i = 0; i < k_FakePlayersCount; ++i)
        {
            m_Data[k_FakeNames[i]] = RandomScore();
        }

        m_Data["Player"] = 0;
        RebuildSorted();
    }

    void Leaderboard::UpdatePlayer(const std::string& name, int score)
    {
        m_Data[name] = score;
        RebuildSorted();
    }

    const std::vector<Record>& Leaderboard::GetSorted() const
    {
        return m_Sorted;
    }

    void Leaderboard::RebuildSorted()
    {
        m_Sorted.clear();
        m_Sorted.reserve(m_Data.size());

        for (const auto& pair : m_Data)
        {
            m_Sorted.push_back({ pair.first, pair.second });
        }

        Sort(m_Sorted);
    }

    void Leaderboard::Sort(std::vector<Record>& records)
    {
        const size_t count = records.size();

        if (count < 2)
        {
            return;
        }

        for (size_t i = 0; i + 1 < count; ++i)
        {
            for (size_t j = 0; j + 1 < count - i; ++j)
            {
                if (records[j].score < records[j + 1].score)
                {
                    std::swap(records[j], records[j + 1]);
                }
            }
        }
    }
}