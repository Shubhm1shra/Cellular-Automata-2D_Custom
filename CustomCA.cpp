#include "CustomCA.hpp"

CustomCA::CustomCA(int rows, int cols, int cell_size) : m_rows(rows), m_cols(cols), m_cell_size(cell_size){
    initialize();
}

CustomCA::~CustomCA() = default;

void CustomCA::setStates(int num){
    states = num;

    stringStates.clear();

    for(int s = 0; s < states; s++) stringStates.push_back(std::to_string(s));
}

void CustomCA::setColors(std::vector<sf::Color> colors){
    colorList = colors;
}

void CustomCA::run(){
    state = getRandomScreen();

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed) window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) window.close();
        }
        
        window.clear();

        drawScreen();
        window.display();

        //sf::sleep(sf::milliseconds(50));

        state = getNextState();
    }
}

void CustomCA::initialize(){
    window.create(sf::VideoMode(m_cols * m_cell_size, m_rows * m_cell_size), "Custom 2D Cellular Automaton!");
    window.setVerticalSyncEnabled(true);

    userFuncDefined = false;

    rect.setSize(sf::Vector2f(m_cell_size, m_cell_size));
}

std::string CustomCA::defaultRule(std::string cellState, int stateCount[]){
    // Rule-Set for Conway's Game of Life

    if(cellState == stringStates[states - 1] && (stateCount[states - 1] < 2 || stateCount[states - 1] > 3)) return stringStates[0];
    if(cellState == stringStates[0] && stateCount[states - 1] == 3) return stringStates[states - 1];
    return cellState;
}

void CustomCA::setRule(RuleFunction func){
    userFuncDefined = true;

    ruleFunc = func;
}

std::string CustomCA::getnextState(int row, int col){
    int statePos = row * m_cols + col;
    
    int checkPos[8];
    checkPos[0] = statePos - m_cols - 1;
    checkPos[1] = statePos - m_cols;
    checkPos[2] = statePos - m_cols + 1;
    checkPos[3] = statePos - 1;
    checkPos[4] = statePos + 1;
    checkPos[5] = statePos + m_cols - 1;
    checkPos[6] = statePos + m_cols;
    checkPos[7] = statePos + m_cols + 1;

    int stateCount[states];
    for(int i = 0; i < states; i++) stateCount[i] = 0;

    for(int i = 0; i < 8; i++){
        if(checkPos[i] < 0 || checkPos[i] >= state.size()) continue;
        stateCount[std::stoi(state[checkPos[i]])]++;
    }

    if(userFuncDefined) return ruleFunc(state[statePos], stateCount);
    else return defaultRule(state[statePos], stateCount);
}

std::vector<std::string> CustomCA::getNextState(){
    std::vector<std::string> nextState;

    for(int row = 0; row < m_rows; row++) for(int col = 0; col < m_cols; col++) nextState.push_back(getnextState(row, col));

    return nextState;
}

std::vector<std::string> CustomCA::getRandomScreen(){
    std::vector<std::string> result;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for(int i = 0; i < m_rows * m_cols; i++) result.push_back(std::to_string(std::rand() % states));

    return result;
}

void CustomCA::drawScreen(){
    if(state.size() != m_rows * m_cols) return;

    for(int col = 0; col < m_cols; col++){
        for(int row = 0; row < m_rows; row++){
            for(int s = 0; s < states; s++) if(state[row * m_cols + col] == stringStates[s]) rect.setFillColor(colorList[s]);

            rect.setPosition(sf::Vector2f(col * m_cell_size, row * m_cell_size));

            window.draw(rect);
        }
    }
}