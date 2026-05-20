#include "AplicatieGUI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

AplicatieGUI::AplicatieGUI(PlatformaStreaming& p) : platforma(p) {
    window = std::make_unique<sf::RenderWindow>(sf::VideoMode({1024, 768}), "Netflix C++ Clone");
    font = std::make_unique<sf::Font>();

    window->setFramerateLimit(60);
    if (!font->openFromFile("assets/fonts/Roboto.ttf")) {
        std::cerr << "Eroare: Nu s-a putut incarca fontul!\n";
    }
}

AplicatieGUI::~AplicatieGUI() = default;

void AplicatieGUI::randeazaCatalog() {
    auto& catalog = platforma.getCatalogGlobal();
    float pozitieY = 50.f;

    for (const auto& cv : catalog) {
        sf::Text text(*font);
        text.setString(cv->getTitlu());
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        text.setPosition({50.f, pozitieY});

        window->draw(text);
        pozitieY += 40.f;
    }
}

void AplicatieGUI::ruleaza() {
    while (window->isOpen()) {
        while (const std::optional event = window->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window->close();
            }
        }

        window->clear(sf::Color(20, 20, 20));
        randeazaCatalog();
        window->display();
    }
}