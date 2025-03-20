#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <nlohmann/json.hpp> // For JSON handling

using json = nlohmann::json;

struct MoodEntry {
    std::string mood;
    std::string timestamp;
};

class MoodsMonitor {
private:
    std::string file;
    std::vector<MoodEntry> moods;

public:
    MoodsMonitor(const std::string& file) : file(file) {
        moods = load_moods(file);
    }

    std::vector<MoodEntry> load_moods(const std::string& file) {
        std::ifstream f(file);
        if (!f) {
            std::ofstream create_file(file);
            return {};
        }
        json j;
        f >> j;
        return j.get<std::vector<MoodEntry>>();
    }

    void save_moods() {
        std::ofstream f(file);
        json j = moods;
        f << std::setw(4) << j << std::endl;
    }

    void log_mood(const std::string& mood) {
        MoodEntry entry;
        entry.mood = mood;
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        entry.timestamp = oss.str();
        moods.push_back(entry);
        save_moods();
        std::cout << "Mood logged successfully" << std::endl;
    }

    void view_moods() {
        if (moods.empty()) {
            std::cout << "No moods logged yet" << std::endl;
        } else {
            std::cout << "\nMood history:" << std::endl;
            for (const auto& entry : moods) {
                std::cout << "[" << entry.timestamp << "] - " << entry.mood << std::endl;
            }
        }
    }

    void analyze_mood() {
        if (moods.empty()) {
            std::cout << "No moods data to analyze" << std::endl;
            return;
        }
        std::unordered_map<std::string, size_t> mood_counts;
        for (const auto& entry : moods) {
            std::string mood = entry.mood;
            std::transform(mood.begin(), mood.end(), mood.begin(), ::tolower);
            mood_counts[mood]++;
        }
        auto most_common_mood = std::max_element(mood_counts.begin(), mood_counts.end(),
            [](const auto& a, const auto& b) { return a.second < b.second; });
        std::cout << "Most common mood: " << most_common_mood->first << " (logged " << most_common_mood->second << " times)" << std::endl;
    }

    void mood_suggestions(const std::string& mood) {
        std::unordered_map<std::string, std::string> suggestions = {
            {"happy", "Great! Keep up the good mood. Maybe share your happiness with someone!"},
            {"sad", "Try watching a funny movie or talking to a friend. You are not alone!"},
            {"stressed", "Take a deep breath, go for a walk, or try meditation."},
            {"excited", "Channel your excitement into something productive! Maybe start a new project?"},
            {"angry", "Listen to music, exercise, write down your thoughts, or take a walk to cool off."}
        };
        auto it = suggestions.find(mood);
        if (it != suggestions.end()) {
            std::cout << it->second << std::endl;
        } else {
            std::cout << "Mood not recognized, but stay positive!" << std::endl;
        }
    }

    void main() {
        while (true) {
            std::cout << "\nMood monitoring app" << std::endl;
            std::cout << "1. Log mood" << std::endl;
            std::cout << "2. View mood history" << std::endl;
            std::cout << "3. Analyze mood trends" << std::endl;
            std::cout << "4. Get mood-based suggestions" << std::endl;
            std::cout << "5. Exit" << std::endl;
            std::string choice;
            std::getline(std::cin, choice);
            if (choice == "1") {
                std::string mood;
                std::cout << "Enter your current mood: ";
                std::getline(std::cin, mood);
                log_mood(mood);
            } else if (choice == "2") {
                view_moods();
            } else if (choice == "3") {
                analyze_mood();
            } else if (choice == "4") {
                std::string mood;
                std::cout << "Enter your current mood: ";
                std::getline(std::cin, mood);
                mood_suggestions(mood);
            } else if (choice == "5") {
                break;
            } else {
                std::cout << "Invalid choice! Try again." << std::endl;
            }
        }
    }
};

int main() {
    MoodsMonitor app("moods.json");
    app.main();
}
