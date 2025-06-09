// A multithreaded C++ application to analyze large log files efficiently.

#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <thread>
#include <vector>
#include <mutex>
#include <unordered_map>

std::mutex result_mutex;
std::unordered_map<std::string, int> error_counts;

void analyze_chunk(const std::vector<std::string>& lines, const std::regex& pattern) {
    std::unordered_map<std::string, int> local_counts;
    for (const auto& line : lines) {
        std::smatch match;
        if (std::regex_search(line, match, pattern)) {
            local_counts[match.str()]++;
        }
    }
    std::lock_guard<std::mutex> lock(result_mutex);
    for (const auto& pair : local_counts) {
        error_counts[pair.first] += pair.second;
    }
}

int main() {
    std::ifstream file("logfile.txt");
    if (!file) {
        std::cerr << "Failed to open log file." << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    size_t thread_count = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    size_t chunk_size = lines.size() / thread_count;
    std::regex error_pattern("ERROR.*");

    for (size_t i = 0; i < thread_count; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == thread_count - 1) ? lines.size() : start + chunk_size;
        std::vector<std::string> chunk(lines.begin() + start, lines.begin() + end);
        threads.emplace_back(analyze_chunk, chunk, error_pattern);
    }

    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Error Summary:\n";
    for (const auto& pair : error_counts) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    return 0;
}
