#include "MainState.hpp"

#include <iostream>

MainState::MainState() {

}
MainState::~MainState() {

}

void MainState::Initialize() {
    std::cout << "## Initializing Server MainState..." << std::endl;
}
void MainState::Shutdown() {
    std::cout << "## Shutting down Server MainState..." << std::endl;
}

void MainState::Update(float time_delta) {

}

