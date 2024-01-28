#include <iostream>

#include "CustomCA.hpp"

/*
g++ CustomCA.cpp -o main main.cpp -I\"C:\\msys64\\mingw64\\include\" -L\"C:\\msys64\\mingw64\\lib\" -lsfml-graphics -lsfml-window -lsfml-system
*/

int states = 10;

std::vector<sf::Color> getRandomColors(int n){
    std::vector<sf::Color> colors;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for(int i = 0; i < n; i++) colors.push_back(sf::Color(std::rand() % 255, std::rand() % 255, std::rand() % 255));

    return colors;
}

std::string myRule(std::string cellState, int stateCount[]){
    if(cellState == "0") return cellState;
    if(cellState == std::to_string(states - 1)) return cellState;

    if(stateCount[std::stoi(cellState) - 1] > 3) return std::to_string(std::stoi(cellState) + 1); // Evolution
    if(stateCount[std::stoi(cellState) - 1] > 2) return cellState; // Survive
    else return std::to_string(std::stoi(cellState) - 1); // De-Evolution
}

int main(){
    CustomCA ca(300, 300, 2);

    std::vector<sf::Color> colors2 = {sf::Color::Black, sf::Color::White};
    std::vector<sf::Color> colors3 = {sf::Color(28, 28, 28), sf::Color::Red, sf::Color::Green};

    std::vector<sf::Color> colors7 = {sf::Color(28, 28, 28), sf::Color(75, 0, 130), sf::Color::Blue,  sf::Color(0, 128, 0), sf::Color(255, 255, 0), sf::Color(255, 165, 0), sf::Color::Red};

    ca.setStates(states);
    ca.setColors(getRandomColors(states));
    ca.setRule(myRule);

    ca.run();

    return 0;
}