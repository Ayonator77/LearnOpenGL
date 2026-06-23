#include "exercise.h"

#include <iostream>
#include <string_view>

namespace {
struct Exercise {
    std::string_view id;
    std::string_view title;
    void (*run)();
};

constexpr Exercise kExercises[] = {
    {"1", "Hello Triangle - indexed rectangle", exercise1},
    {"1a", "Hello Triangle - two triangles", exercise1a},
    {"1a-1", "Hello Triangle - separate VAOs/shaders", exercise1a_1},
    {"2", "Shaders", exercise2},
    {"3", "Textures", exercise3},
    {"4", "Transformations", exercise4},
};

constexpr std::string_view kDefaultExercise = "4";

void printAvailableExercises() {
    std::cout << "Available exercises:\n";
    for (const Exercise& exercise : kExercises) {
        std::cout << "  " << exercise.id << " - " << exercise.title << '\n';
    }
}
}

int main(int argc, char* argv[]) {
    const std::string_view selected = argc > 1 ? argv[1] : kDefaultExercise;

    if (selected == "list" || selected == "help" || selected == "--help") {
        printAvailableExercises();
        return 0;
    }

    for (const Exercise& exercise : kExercises) {
        if (exercise.id == selected) {
            std::cout << "Running exercise " << exercise.id << ": " << exercise.title << '\n';
            exercise.run();
            return 0;
        }
    }

    std::cout << "Unknown exercise: " << selected << "\n\n";
    printAvailableExercises();
    return 0;
}
