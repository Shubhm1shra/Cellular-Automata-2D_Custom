#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <conio.h>

using RuleFunction = std::string (*)(std::string, int[]);

class CustomCA{
public:
    CustomCA(int rows, int cols, int cell_size);
    ~CustomCA();

    void setStates(int num);
    void setColors(std::vector<sf::Color> colors);

    std::string defaultRule(std::string cellState, int stateCount[]);
    void setRule(RuleFunction func);

    void run();

private:
    int states;
    std::vector<std::string> stringStates;

    RuleFunction ruleFunc;
    bool userFuncDefined;

    int m_rows, m_cols, m_cell_size;
    std::vector<std::string> state;

    std::vector<sf::Color> colorList;

    sf::RenderWindow window;
    sf::RectangleShape rect;

    void initialize();

    std::string getnextState(int row, int col);
    std::vector<std::string> getNextState();
    std::vector<std::string> getRandomScreen();

    void drawScreen();
};