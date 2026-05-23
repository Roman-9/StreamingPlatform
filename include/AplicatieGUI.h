#pragma once
#include "PlatformaStreaming.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>
#include <vector>

enum class StareAplicatie {
    Login,
    Catalog,
    Detalii,
    Statistici,
    AdminPanel
};

enum class FiltruCatalog {
    Toate,
    Filme,
    Seriale,
    Documentare
};

class AplicatieGUI {
private:
    sf::RenderWindow window;
    sf::Font font;
    PlatformaStreaming& platforma;

    std::string mesajStatus;
    StareAplicatie stareCurenta;
    std::shared_ptr<ContinutVideo> continutSelectat;
    FiltruCatalog filtruCurent;
    int indexUserCurent;

    std::map<std::string, sf::Texture> postere;
    std::map<std::string, std::vector<std::string>> istoricUtilizatori;
    std::map<std::string, int> noteAcordate;

    void incarcaPostere();
    void randeazaBaraNavigatie();
    void randeazaStatus();
    void randeazaEcranLogin();
    void randeazaCatalog();
    void randeazaPaginaDetalii();
    void randeazaPaginaStatistici();
    void randeazaPanouAdmin();

    void proceseazaClick(sf::Vector2i pozitieMouse);

public:
    explicit AplicatieGUI(PlatformaStreaming& p);
    void ruleaza();

    friend std::ostream& operator<<(std::ostream& os, const AplicatieGUI& gui);
};