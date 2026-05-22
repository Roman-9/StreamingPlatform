#include "AplicatieGUI.h"
#include "Film.h"
#include "Serial.h"
#include "Documentar.h"
#include "Exceptii.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <sstream>

AplicatieGUI::AplicatieGUI(PlatformaStreaming& p)
    : platforma(p),
      mesajStatus("Selecteaza un profil sau intra ca Admin."),
      stareCurenta(StareAplicatie::Login),
      continutSelectat(nullptr),
      filtruCurent(FiltruCatalog::Toate),
      indexUserCurent(-1)
{
    platforma.incarcaCatalogDinDB();

    window.create(sf::VideoMode({1280, 720}), "Netflix C++ Clone");
    window.setFramerateLimit(60);

    if (!font.openFromFile("assets/fonts/Roboto.ttf")) {
        std::cerr << "[EROARE] Nu s-a putut incarca fontul Roboto.ttf! Asigura-te ca folderul assets exista.\n";
    }
    incarcaPostere();
}

void AplicatieGUI::incarcaPostere() {
    for (const auto& cv : platforma.getCatalogGlobal()) {
        if (!cv->getCalePoster().empty()) {
            sf::Texture textura;
            if (textura.loadFromFile(cv->getCalePoster())) {
                postere[cv->getTitlu()] = textura;
            } else {
                std::cerr << "[AVERTISMENT] Nu s-a putut incarca imaginea la calea: " << cv->getCalePoster() << "\n";
            }
        }
    }
}

void AplicatieGUI::randeazaBaraNavigatie() {
    sf::RectangleShape topBar({1280.f, 60.f});
    topBar.setFillColor(sf::Color(10, 10, 10));
    window.draw(topBar);

    sf::Text logo(font);
    logo.setString("NETFLIX C++"); logo.setCharacterSize(28);
    logo.setFillColor(sf::Color(229, 9, 20)); logo.setStyle(sf::Text::Bold);
    logo.setPosition({40.f, 15.f}); window.draw(logo);

    if (stareCurenta != StareAplicatie::Login && indexUserCurent != -1) {
        auto& user = platforma.getUtilizatori()[indexUserCurent];

        sf::RectangleShape profilBtn({140.f, 35.f});
        profilBtn.setFillColor(sf::Color(30, 30, 30));profilBtn.setPosition({1100.f, 12.f}); window.draw(profilBtn);

        sf::Text profilTxt(font); profilTxt.setString(user.getNume()); profilTxt.setCharacterSize(16);
        profilTxt.setFillColor(sf::Color::White); profilTxt.setStyle(sf::Text::Bold);
        profilTxt.setPosition({1115.f, 20.f}); window.draw(profilTxt);
    }

    sf::RectangleShape separator({1280.f, 1.f});
    separator.setFillColor(sf::Color(40, 40, 40)); separator.setPosition({0.f, 60.f});
    window.draw(separator);
}

void AplicatieGUI::randeazaStatus() {
    sf::Text status(font);
    status.setString(mesajStatus); status.setCharacterSize(16);
    status.setFillColor(sf::Color(200, 200, 200)); status.setPosition({40.f, 690.f});
    window.draw(status);
}

void AplicatieGUI::randeazaEcranLogin() {
    sf::Text invitatie(font);
    invitatie.setString("Cine se uita astazi?"); invitatie.setCharacterSize(42);
    invitatie.setFillColor(sf::Color::White); invitatie.setPosition({450.f, 140.f});
    invitatie.setStyle(sf::Text::Bold); window.draw(invitatie);

    auto& utilizatori = platforma.getUtilizatori();
    float startX = 350.f; float spatiuX = 160.f; float y = 260.f;

    for (size_t i = 0; i < utilizatori.size(); i++) {
        float x = startX + i * spatiuX;
        sf::RectangleShape avatar({110.f, 110.f}); avatar.setPosition({x, y});
        avatar.setFillColor(utilizatori[i].getVarsta() < 12 ? sf::Color(0, 150, 255) : (utilizatori[i].getVarsta() < 18 ? sf::Color(150, 0, 150) : sf::Color(229, 9, 20)));
        window.draw(avatar);

        sf::Text numeUser(font); numeUser.setString(utilizatori[i].getNume()); numeUser.setCharacterSize(18);
        numeUser.setFillColor(sf::Color::White); numeUser.setPosition({x + 10.f, y + 120.f});
        window.draw(numeUser);
    }

    float adaugaX = startX + utilizatori.size() * spatiuX;

    sf::RectangleShape btnCopil({140.f, 32.f}); btnCopil.setPosition({adaugaX, y});
    btnCopil.setFillColor(sf::Color(0, 150, 255));
    sf::Text txtCopil(font); txtCopil.setString("+ Copil (<12)"); txtCopil.setCharacterSize(14);
    txtCopil.setFillColor(sf::Color::White); txtCopil.setPosition({adaugaX + 15.f, y + 6.f});
    window.draw(btnCopil); window.draw(txtCopil);

    sf::RectangleShape btnTeen({140.f, 32.f}); btnTeen.setPosition({adaugaX, y + 42.f});
    btnTeen.setFillColor(sf::Color(150, 0, 150));
    sf::Text txtTeen(font); txtTeen.setString("+ Teen (15)"); txtTeen.setCharacterSize(14);
    txtTeen.setFillColor(sf::Color::White); txtTeen.setPosition({adaugaX + 15.f, y + 48.f});
    window.draw(btnTeen); window.draw(txtTeen);

    sf::RectangleShape btnAdult({140.f, 32.f}); btnAdult.setPosition({adaugaX, y + 84.f});
    btnAdult.setFillColor(sf::Color(229, 9, 20));
    sf::Text txtAdult(font); txtAdult.setString("+ Adult (18+)"); txtAdult.setCharacterSize(14);
    txtAdult.setFillColor(sf::Color::White); txtAdult.setPosition({adaugaX + 15.f, y + 90.f});
    window.draw(btnAdult); window.draw(txtAdult);

    sf::RectangleShape adminBtn({200.f, 45.f});
    adminBtn.setFillColor(sf::Color(30, 30, 30));adminBtn.setPosition({540.f, 520.f});
    window.draw(adminBtn);

    sf::Text adminTxt(font); adminTxt.setString("PANOU ADMIN"); adminTxt.setCharacterSize(16);
    adminTxt.setFillColor(sf::Color::White); adminTxt.setStyle(sf::Text::Bold);
    adminTxt.setPosition({585.f, 532.f}); window.draw(adminTxt);
}

void AplicatieGUI::randeazaCatalog() {
    std::vector<std::string> numeFiltre = {"TOATE", "FILME", "SERIALE", "DOCUMENTARE"};
    float filtruX = 40.f;
    for (int i = 0; i < 4; i++) {
        sf::RectangleShape btnFiltru({150.f, 30.f}); btnFiltru.setPosition({filtruX, 75.f});
        btnFiltru.setFillColor(i == static_cast<int>(filtruCurent) ? sf::Color(229, 9, 20) : sf::Color(40, 40, 40));
        window.draw(btnFiltru);

        sf::Text txtFiltru(font);
        txtFiltru.setString(numeFiltre[i]); txtFiltru.setCharacterSize(14);
        txtFiltru.setFillColor(sf::Color::White); txtFiltru.setStyle(sf::Text::Bold);
        txtFiltru.setPosition({filtruX + 25.f, 80.f}); window.draw(txtFiltru);
        filtruX += 170.f;
    }

    auto& catalog = platforma.getCatalogGlobal();
    float startX = 40.f; float startY = 140.f;
    float cardWidth = 280.f; float cardHeight = 160.f;
    float spatiuX = 30.f; float spatiuY = 40.f;
    int coloane = 4;

    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);

    int indexDesenat = 0;
    for (const auto& cv : catalog) {
        bool eFilm = std::dynamic_pointer_cast<Film>(cv) != nullptr;
        bool eSerial = std::dynamic_pointer_cast<Serial>(cv) != nullptr;
        bool eDoc = std::dynamic_pointer_cast<Documentar>(cv) != nullptr;

        if (filtruCurent == FiltruCatalog::Filme && !eFilm) continue;
        if (filtruCurent == FiltruCatalog::Seriale && !eSerial) continue;
        if (filtruCurent == FiltruCatalog::Documentare && !eDoc) continue;

        int rand = indexDesenat / coloane; int col = indexDesenat % coloane;
        float x = startX + col * (cardWidth + spatiuX); float y = startY + rand * (cardHeight + spatiuY);

        sf::FloatRect cardRect({x, y}, {cardWidth, cardHeight});
        bool isHovered = cardRect.contains(mousePos);

        if (postere.find(cv->getTitlu()) != postere.end()) {
            sf::Sprite poster(postere[cv->getTitlu()]); poster.setPosition({x, y});
            sf::Vector2u size = postere[cv->getTitlu()].getSize();
            poster.setScale({cardWidth / size.x, cardHeight / size.y}); window.draw(poster);

            sf::RectangleShape filtru({cardWidth, cardHeight}); filtru.setPosition({x, y});
            filtru.setFillColor(sf::Color(0, 0, 0, 150));
            if (isHovered) { filtru.setOutlineThickness(2.f); filtru.setOutlineColor(sf::Color(229, 9, 20)); }
            window.draw(filtru);
        } else {
            sf::RectangleShape card({cardWidth, cardHeight}); card.setPosition({x, y});
            card.setFillColor(isHovered ? sf::Color(60, 60, 60) : sf::Color(35, 35, 35));
            if (isHovered) { card.setOutlineThickness(2.f); card.setOutlineColor(sf::Color(229, 9, 20)); }
            window.draw(card);
        }

        sf::Text titlu(font);
        titlu.setString(cv->getTitlu()); titlu.setCharacterSize(22);
        titlu.setFillColor(sf::Color::White); titlu.setStyle(sf::Text::Bold);
        titlu.setPosition({x + 15.f, y + 15.f}); window.draw(titlu);

        std::string detalii = cv->getGen() + " | " + std::to_string(cv->getVarstaMinima()) + "+";
        sf::Text textDetalii(font);
        textDetalii.setString(detalii); textDetalii.setCharacterSize(14);
        textDetalii.setFillColor(sf::Color(200, 200, 200)); textDetalii.setPosition({x + 15.f, y + 50.f});
        window.draw(textDetalii);

        indexDesenat++;
    }

    sf::Text totalTxt(font);
    totalTxt.setString("Titluri in memorie RAM: " + std::to_string(ContinutVideo::getNumarTotalContinut()));
    totalTxt.setCharacterSize(14); totalTxt.setFillColor(sf::Color(100, 100, 100));
    totalTxt.setPosition({1080.f, 680.f}); window.draw(totalTxt);
}


void AplicatieGUI::randeazaPaginaDetalii() {
    if (!continutSelectat) return;

    if (postere.find(continutSelectat->getTitlu()) != postere.end()) {
        sf::Sprite fundal(postere[continutSelectat->getTitlu()]); fundal.setPosition({0.f, 60.f});
        sf::Vector2u size = postere[continutSelectat->getTitlu()].getSize();
        fundal.setScale({1280.f / size.x, 620.f / size.y});
        window.draw(fundal);

        sf::RectangleShape strat({1280.f, 620.f}); strat.setPosition({0.f, 60.f});
        strat.setFillColor(sf::Color(0, 0, 0, 190));
        window.draw(strat);
    }

    sf::RectangleShape backBtn({100.f, 40.f});
    backBtn.setFillColor(sf::Color(40, 40, 40)); backBtn.setPosition({40.f, 80.f});
    window.draw(backBtn);

    sf::Text backTxt(font);
    backTxt.setString("< INAPOI"); backTxt.setCharacterSize(18);
    backTxt.setFillColor(sf::Color::White); backTxt.setPosition({50.f, 88.f});
    window.draw(backTxt);


    float contentLeftX = 60.f;
    float startY = 140.f;

    sf::Text titlu(font);
    titlu.setString(continutSelectat->getTitlu()); titlu.setCharacterSize(48);
    titlu.setFillColor(sf::Color::White); titlu.setStyle(sf::Text::Bold);
    titlu.setPosition({contentLeftX, startY}); window.draw(titlu);

    sf::Text ratingTxt(font);
    std::string ratingGlobal = std::to_string(continutSelectat->getRating());
    ratingGlobal = ratingGlobal.substr(0, ratingGlobal.find('.') + 2);
    ratingTxt.setString("Rating Platforma: " + ratingGlobal + " / 10.0");
    ratingTxt.setFillColor(sf::Color(255, 215, 0)); ratingTxt.setCharacterSize(20);
    ratingTxt.setStyle(sf::Text::Bold); ratingTxt.setPosition({contentLeftX, startY + 80.f}); window.draw(ratingTxt);

    std::string infoStr = "Gen: " + continutSelectat->getGen() + "  |  " + std::to_string(continutSelectat->getVarstaMinima()) + "+";
    if (auto doc = std::dynamic_pointer_cast<Documentar>(continutSelectat)) {
        infoStr += "  |  Subiect: " + doc->getSubiect();
    }
    sf::Text infoTxt(font);
    infoTxt.setString(infoStr); infoTxt.setCharacterSize(20);
    infoTxt.setFillColor(sf::Color(200, 200, 200)); infoTxt.setPosition({contentLeftX, startY + 120.f});
    window.draw(infoTxt);

    sf::Text descriereTitluTxt(font); descriereTitluTxt.setString("Descriere:"); descriereTitluTxt.setCharacterSize(20);
    descriereTitluTxt.setFillColor(sf::Color(229, 9, 20)); descriereTitluTxt.setStyle(sf::Text::Bold);
    descriereTitluTxt.setPosition({contentLeftX, startY + 170.f}); window.draw(descriereTitluTxt);

    std::string descriereOriginala = continutSelectat->getDescriere();
    std::string descriereFormatata = "";
    std::string cuvant;
    std::string linieCurenta = "";
    sf::Text testWidth(font); testWidth.setCharacterSize(18);
    float latimeMaxima = 700.f;

    std::stringstream ss(descriereOriginala);
    while (ss >> cuvant) {
        std::string testLine = linieCurenta.empty() ? cuvant : linieCurenta + " " + cuvant;
        testWidth.setString(testLine);
        if (testWidth.getLocalBounds().size.x > latimeMaxima) {
            descriereFormatata += linieCurenta + "\n";
            linieCurenta = cuvant;
        } else {
            linieCurenta = testLine;
        }
    }
    descriereFormatata += linieCurenta;

    sf::Text descriereTxt(font);
    descriereTxt.setString(descriereFormatata);
    descriereTxt.setCharacterSize(18); descriereTxt.setFillColor(sf::Color::White);
    descriereTxt.setPosition({contentLeftX, startY + 200.f}); window.draw(descriereTxt);

    float btnY = 560.f;

    sf::RectangleShape playBtn({140.f, 50.f});
    playBtn.setFillColor(sf::Color(229, 9, 20)); playBtn.setPosition({contentLeftX, btnY});
    window.draw(playBtn);
    sf::Text playTxt(font); playTxt.setString("PLAY"); playTxt.setCharacterSize(18);
    playTxt.setFillColor(sf::Color::White); playTxt.setStyle(sf::Text::Bold);
    playTxt.setPosition({contentLeftX + 45.f, btnY + 12.f}); window.draw(playTxt);

    sf::RectangleShape wlBtn({160.f, 50.f});
    wlBtn.setFillColor(sf::Color(45, 45, 45)); wlBtn.setPosition({contentLeftX + 155.f, btnY});
    window.draw(wlBtn);
    sf::Text wlTxt(font); wlTxt.setString("+ WATCHLIST"); wlTxt.setCharacterSize(18);
    wlTxt.setFillColor(sf::Color::White); wlTxt.setPosition({contentLeftX + 180.f, btnY + 12.f});
    window.draw(wlTxt);

    sf::RectangleShape likeBtn({100.f, 50.f});
    likeBtn.setFillColor(sf::Color(30, 30, 30)); likeBtn.setOutlineThickness(1.f); likeBtn.setOutlineColor(sf::Color(0, 210, 100));
    likeBtn.setPosition({contentLeftX + 330.f, btnY}); window.draw(likeBtn);
    sf::Text likeTxt(font); likeTxt.setString("LIKE"); likeTxt.setCharacterSize(16);
    likeTxt.setFillColor(sf::Color(0, 210, 100)); likeTxt.setPosition({contentLeftX + 360.f, btnY + 15.f});
    window.draw(likeTxt);

    sf::RectangleShape dislikeBtn({100.f, 50.f});
    dislikeBtn.setFillColor(sf::Color(30, 30, 30)); dislikeBtn.setOutlineThickness(1.f); dislikeBtn.setOutlineColor(sf::Color(229, 9, 20));
    dislikeBtn.setPosition({contentLeftX + 445.f, btnY}); window.draw(dislikeBtn);
    sf::Text dislikeTxt(font); dislikeTxt.setString("DISLIKE"); dislikeTxt.setCharacterSize(16);
    dislikeTxt.setFillColor(sf::Color(229, 9, 20)); dislikeTxt.setPosition({contentLeftX + 465.f, btnY + 15.f});
    window.draw(dislikeTxt);


    if (auto serial = std::dynamic_pointer_cast<Serial>(continutSelectat)) {
        float episodesRightX = 800.f;
        sf::Text epTitlu(font);
        epTitlu.setString("Ghid Episoade:");
        epTitlu.setCharacterSize(20); epTitlu.setFillColor(sf::Color(229, 9, 20));
        epTitlu.setPosition({episodesRightX, startY + 170.f}); window.draw(epTitlu);

        auto durate = serial->getDurateEpisoade(); float epY = startY + 210.f;
        int epSesiuneVazut = progresSeriale[serial->getTitlu()];

        for(size_t i = 0; i < std::min<size_t>(durate.size(), 3); i++) {
            sf::RectangleShape epRow({450.f, 35.f});
            if (static_cast<int>(i) < epSesiuneVazut) epRow.setFillColor(sf::Color(20, 120, 20));
            else epRow.setFillColor(sf::Color(40, 40, 40));
            epRow.setPosition({episodesRightX, epY}); window.draw(epRow);

            sf::Text epInfo(font);
            epInfo.setString(std::to_string(i+1) + ". Episodul " + std::to_string(i+1) + " (" + std::to_string(durate[i]) + " min)");
            epInfo.setCharacterSize(16); epInfo.setFillColor(sf::Color::White);
            epInfo.setPosition({episodesRightX + 15.f, epY + 8.f}); window.draw(epInfo);
            epY += 40.f;
        }
    }
}
void AplicatieGUI::randeazaPaginaStatistici() {
    if (indexUserCurent == -1) return;
    auto& user = platforma.getUtilizatori()[indexUserCurent];

    sf::RectangleShape backBtn({100.f, 40.f});
    backBtn.setFillColor(sf::Color(40, 40, 40)); backBtn.setPosition({40.f, 80.f});
    window.draw(backBtn);
    sf::Text backTxt(font); backTxt.setString("< CATALOG"); backTxt.setCharacterSize(16);
    backTxt.setFillColor(sf::Color::White); backTxt.setPosition({48.f, 90.f});
    window.draw(backTxt);

    sf::RectangleShape logoutBtn({150.f, 40.f});
    logoutBtn.setFillColor(sf::Color(150, 20, 20)); logoutBtn.setPosition({1090.f, 80.f});
    window.draw(logoutBtn);
    sf::Text logoutTxt(font); logoutTxt.setString("DECONECTARE"); logoutTxt.setCharacterSize(16);
    logoutTxt.setFillColor(sf::Color::White); logoutTxt.setStyle(sf::Text::Bold);
    logoutTxt.setPosition({1105.f, 90.f}); window.draw(logoutTxt);

    sf::Text titru(font);
    titru.setString("Profilul lui " + user.getNume()); titru.setCharacterSize(36);
    titru.setFillColor(sf::Color::White); titru.setStyle(sf::Text::Bold);
    titru.setPosition({40.f, 150.f}); window.draw(titru);

    int minuteVizionate = user.getTimpTotalVizionat();
    int minuteRamase = user.getTimpRamasWatchlist();
    std::string recomandareTop = user.getTopRecomandare(platforma.getCatalogGlobal());

    std::string detaliiCont = "Abonament: " + user.getPlan() + "\n";
    detaliiCont += "Varsta: " + std::to_string(user.getVarsta()) + " ani\n\n";
    detaliiCont += "[ ANALYTICS LIVE ]\n";
    detaliiCont += "-> Timp total vizionat: " + std::to_string(minuteVizionate) + " min\n";
    detaliiCont += "-> Watchlist ramas:   " + std::to_string(minuteRamase) + " min\n\n";
    detaliiCont += "[ TOP RECOMANDARE ]\n";
    detaliiCont += recomandareTop;

    sf::Text detaliiTxt(font);
    detaliiTxt.setString(detaliiCont); detaliiTxt.setCharacterSize(18);
    detaliiTxt.setFillColor(sf::Color(220, 220, 220)); detaliiTxt.setPosition({40.f, 230.f});
    window.draw(detaliiTxt);

    sf::RectangleShape upgradeBtn({160.f, 40.f});
    upgradeBtn.setFillColor(sf::Color(255, 215, 0)); upgradeBtn.setPosition({40.f, 480.f});
    window.draw(upgradeBtn);
    sf::Text upgradeTxt(font); upgradeTxt.setString("UPGRADE PLAN"); upgradeTxt.setCharacterSize(16);
    upgradeTxt.setFillColor(sf::Color::Black); upgradeTxt.setStyle(sf::Text::Bold);
    upgradeTxt.setPosition({55.f, 490.f}); window.draw(upgradeTxt);

    sf::RectangleShape downgradeBtn({180.f, 40.f});
    downgradeBtn.setFillColor(sf::Color(100, 100, 100)); downgradeBtn.setPosition({210.f, 480.f});
    window.draw(downgradeBtn);
    sf::Text downgradeTxt(font); downgradeTxt.setString("DOWNGRADE (Basic)"); downgradeTxt.setCharacterSize(14);
    downgradeTxt.setFillColor(sf::Color::White); downgradeTxt.setStyle(sf::Text::Bold);
    downgradeTxt.setPosition({230.f, 492.f}); window.draw(downgradeBtn); window.draw(downgradeTxt);

    sf::Text wlTitlu(font); wlTitlu.setString("Watchlist (Click pentru stergere):");
    wlTitlu.setCharacterSize(20); wlTitlu.setFillColor(sf::Color(229, 9, 20));
    wlTitlu.setPosition({420.f, 230.f}); window.draw(wlTitlu);

    float wlY = 270.f;
    auto& listaWatchlist = user.getWatchlist().getLista();
    if (listaWatchlist.empty()) {
        sf::Text golTxt(font); golTxt.setString("(Lista este goala)");
        golTxt.setCharacterSize(16); golTxt.setFillColor(sf::Color(120, 120, 120));
        golTxt.setPosition({420.f, wlY}); window.draw(golTxt);
    } else {
        for (const auto& item : listaWatchlist) {
            sf::RectangleShape itemBg({350.f, 30.f});
            itemBg.setPosition({420.f, wlY}); itemBg.setFillColor(sf::Color(30, 30, 30));
            window.draw(itemBg);
            sf::Text itemTxt(font); itemTxt.setString("[X] " + item->getTitlu());
            itemTxt.setCharacterSize(14); itemTxt.setFillColor(sf::Color(255, 100, 100));
            itemTxt.setPosition({430.f, wlY + 5.f}); window.draw(itemTxt);
            wlY += 35.f;
        }
    }

    sf::Text istoricTitlu(font); istoricTitlu.setString("Istoric Sesiune:");
    istoricTitlu.setCharacterSize(20); istoricTitlu.setFillColor(sf::Color(229, 9, 20));
    istoricTitlu.setPosition({820.f, 230.f}); window.draw(istoricTitlu);

    float istY = 270.f;
    auto& istoricList = istoricUtilizatori[user.getNume()];
    if (istoricList.empty()) {
        sf::Text golTxt(font); golTxt.setString("(Nu ai vizionat nimic)");
        golTxt.setCharacterSize(16); golTxt.setFillColor(sf::Color(120, 120, 120));
        golTxt.setPosition({820.f, istY}); window.draw(golTxt);
    } else {
        for (const auto& t : istoricList) {
            sf::Text itemTxt(font); itemTxt.setString(t);
            itemTxt.setCharacterSize(14); itemTxt.setFillColor(sf::Color::White);
            itemTxt.setPosition({820.f, istY}); window.draw(itemTxt);

            sf::RectangleShape trackBar({400.f, 4.f}); trackBar.setFillColor(sf::Color(60, 60, 60));
            trackBar.setPosition({820.f, istY + 22.f}); window.draw(trackBar);

            sf::RectangleShape progressBar({400.f, 4.f}); progressBar.setFillColor(sf::Color(0, 200, 100));
            progressBar.setPosition({820.f, istY + 22.f}); window.draw(progressBar);
            istY += 45.f;
        }
    }
}
void AplicatieGUI::randeazaPanouAdmin() {
    sf::RectangleShape backBtn({100.f, 40.f});
    backBtn.setFillColor(sf::Color(40, 40, 40)); backBtn.setPosition({40.f, 80.f});
    window.draw(backBtn);
    sf::Text backTxt(font); backTxt.setString("< INAPOI"); backTxt.setCharacterSize(16);
    backTxt.setFillColor(sf::Color::White); backTxt.setPosition({48.f, 90.f});
    window.draw(backTxt);

    sf::Text titru(font);
    titru.setString("Panou Control Administrator"); titru.setCharacterSize(36);
    titru.setFillColor(sf::Color::White); titru.setStyle(sf::Text::Bold);
    titru.setPosition({40.f, 150.f}); window.draw(titru);

    sf::RectangleShape fBtn({350.f, 50.f}); fBtn.setFillColor(sf::Color(229, 9, 20));
    fBtn.setPosition({40.f, 300.f}); window.draw(fBtn);
    sf::Text fTxt(font); fTxt.setString("+ Adauga Film Nou");
    fTxt.setCharacterSize(16); fTxt.setFillColor(sf::Color::White); fTxt.setStyle(sf::Text::Bold);
    fTxt.setPosition({60.f, 315.f}); window.draw(fTxt);

    sf::RectangleShape sBtn({350.f, 50.f}); sBtn.setFillColor(sf::Color(229, 9, 20));
    sBtn.setPosition({40.f, 370.f}); window.draw(sBtn);
    sf::Text sTxt(font); sTxt.setString("+ Adauga Serial Nou");
    sTxt.setCharacterSize(16); sTxt.setFillColor(sf::Color::White); sTxt.setStyle(sf::Text::Bold);
    sTxt.setPosition({60.f, 385.f}); window.draw(sTxt);

    sf::RectangleShape dBtn({350.f, 50.f}); dBtn.setFillColor(sf::Color(229, 9, 20));
    dBtn.setPosition({40.f, 440.f}); window.draw(dBtn);
    sf::Text dTxt(font); dTxt.setString("+ Adauga Documentar Nou");
    dTxt.setCharacterSize(16); dTxt.setFillColor(sf::Color::White); dTxt.setStyle(sf::Text::Bold);
    dTxt.setPosition({60.f, 455.f}); window.draw(dTxt);

    sf::RectangleShape mBtn({400.f, 50.f}); mBtn.setFillColor(sf::Color(255, 165, 0));
    mBtn.setPosition({40.f, 510.f}); window.draw(mBtn);
    sf::Text mTxt(font); mTxt.setString("TESTEAZA EXCEPTII DB");
    mTxt.setCharacterSize(16); mTxt.setFillColor(sf::Color::Black); mTxt.setStyle(sf::Text::Bold);
    mTxt.setPosition({60.f, 525.f}); window.draw(mTxt);
}


void AplicatieGUI::proceseazaClick(sf::Vector2i pozitieMouse) {
    sf::Vector2f coordMouse = window.mapPixelToCoords(pozitieMouse);

    if (stareCurenta == StareAplicatie::Login) {
        auto& utilizatori = platforma.getUtilizatori();
        float startX = 350.f; float spatiuX = 160.f; float y = 260.f;

        for (size_t i = 0; i < utilizatori.size(); i++) {
            if (sf::FloatRect({startX + i * spatiuX, y}, {110.f, 110.f}).contains(coordMouse)) {
                indexUserCurent = static_cast<int>(i); stareCurenta = StareAplicatie::Catalog;
                mesajStatus = "Conectat ca: " + utilizatori[i].getNume(); return;
            }
        }

        float adaugaX = startX + utilizatori.size() * spatiuX;
        std::string numeNou = "User_" + std::to_string(utilizatori.size() + 1);

        if (sf::FloatRect({adaugaX, y}, {140.f, 32.f}).contains(coordMouse)) {
            platforma.inregistreazaUtilizator(numeNou + "_Copil", 10);
            mesajStatus = "[BACKEND] S-a inregistrat un Copil (10 ani)."; return;
        }
        if (sf::FloatRect({adaugaX, y + 42.f}, {140.f, 32.f}).contains(coordMouse)) {
            platforma.inregistreazaUtilizator(numeNou + "Teen", 15);
            mesajStatus = "[BACKEND] S-a inregistrat un Adolescent (15 ani)."; return;
        }
        if (sf::FloatRect({adaugaX, y + 84.f}, {140.f, 32.f}).contains(coordMouse)) {
            platforma.inregistreazaUtilizator(numeNou + "_Adult", 25);
            mesajStatus = "[BACKEND] S-a inregistrat un Adult (25 ani)."; return;
        }

        if (sf::FloatRect({540.f, 520.f}, {200.f, 45.f}).contains(coordMouse)) {
            stareCurenta = StareAplicatie::AdminPanel; mesajStatus = "Panou administrare activat."; return;
        }
    }
    else if (stareCurenta == StareAplicatie::Catalog) {
        if (sf::FloatRect({1100.f, 12.f}, {140.f, 35.f}).contains(coordMouse)) {
            stareCurenta = StareAplicatie::Statistici;
            mesajStatus = "Statistici generate in consola.";
            std::cout << "\n========== RAPORT PROFIL ==========\n";
            auto& u = platforma.getUtilizatori()[indexUserCurent];
            std::cout << u;
            std::cout << "===================================\n";
            return;
        }

        float filtruX = 40.f;
        for (int i = 0; i < 4; i++) {
            if (sf::FloatRect({filtruX, 75.f}, {150.f, 30.f}).contains(coordMouse)) {
                filtruCurent = static_cast<FiltruCatalog>(i); mesajStatus = "Catalog filtrat."; return;
            }
            filtruX += 170.f;
        }

        auto& catalog = platforma.getCatalogGlobal();
        int coloane = 4; float startX = 40.f, startY = 140.f;
        float cardWidth = 280.f; float cardHeight = 160.f;
        float spatiuX = 30.f; float spatiuY = 40.f;
        int indexDesenat = 0;
        for (const auto& cv : catalog) {
            bool eFilm = std::dynamic_pointer_cast<Film>(cv) != nullptr;
            bool eSerial = std::dynamic_pointer_cast<Serial>(cv) != nullptr;
            bool eDoc = std::dynamic_pointer_cast<Documentar>(cv) != nullptr;
            if (filtruCurent == FiltruCatalog::Filme && !eFilm) continue;
            if (filtruCurent == FiltruCatalog::Seriale && !eSerial) continue;
            if (filtruCurent == FiltruCatalog::Documentare && !eDoc) continue;

            int rand = indexDesenat / coloane; int col = indexDesenat % coloane;
            if (sf::FloatRect({startX + col * (cardWidth + spatiuX), startY + rand * (cardHeight + spatiuY)}, {cardWidth, cardHeight}).contains(coordMouse)) {
                continutSelectat = cv; stareCurenta = StareAplicatie::Detalii; mesajStatus = "Detalii: " + cv->getTitlu(); return;
            }
            indexDesenat++;
        }
    }
    else if (stareCurenta == StareAplicatie::Detalii) {
        if (sf::FloatRect({40.f, 80.f}, {100.f, 40.f}).contains(coordMouse)) {
            continutSelectat = nullptr; stareCurenta = StareAplicatie::Catalog; return;
        }

        if (sf::FloatRect({1100.f, 12.f}, {140.f, 35.f}).contains(coordMouse)) {
            continutSelectat = nullptr;
            stareCurenta = StareAplicatie::Statistici;
            return;
        }

        float contentLeftX = 60.f;
        float btnY = 550.f;
        auto& user = platforma.getUtilizatori()[indexUserCurent];

        if (sf::FloatRect({contentLeftX, btnY}, {140.f, 50.f}).contains(coordMouse)) {
            if (user.getVarsta() < continutSelectat->getVarstaMinima()) {
                mesajStatus = "[BLOCAT] Varsta insuficienta! Necesita minim " + std::to_string(continutSelectat->getVarstaMinima()) + " ani.";
                return;
            }
            if (std::dynamic_pointer_cast<Documentar>(continutSelectat) && user.getPlan() != "Premium") {
                mesajStatus = "[LOCKED] Documentarele sunt exclusive pentru utilizatorii PREMIUM!";
                return;
            }
            user.marcheazaCaVazut(continutSelectat);
            auto& hist = istoricUtilizatori[user.getNume()];
            if (std::find(hist.begin(), hist.end(), continutSelectat->getTitlu()) == hist.end()) hist.push_back(continutSelectat->getTitlu());
            mesajStatus = "[PLAY] Se incarca playerul...";
            continutSelectat->play();
            std::string comanda = "start " + continutSelectat->getLinkVizionare();
            system(comanda.c_str());
            return;
        }

        if (sf::FloatRect({contentLeftX + 155.f, btnY}, {160.f, 50.f}).contains(coordMouse)) {
            try { user.adaugaInWatchlist(continutSelectat); mesajStatus = "[SUCCES] Adaugat in Watchlist."; }
            catch (const std::exception& e) { mesajStatus = "[BLOCAT] " + std::string(e.what()); }
            return;
        }

        if (sf::FloatRect({contentLeftX + 330.f, btnY}, {100.f, 50.f}).contains(coordMouse)) {
            try {
                user.acordaNota(continutSelectat->getTitlu(), 10);
                noteAcordate[continutSelectat->getTitlu()] = 10;
                mesajStatus = "[VOT] Ai trimis nota 10. Media s-a actualizat!";
            } catch (const StreamingException& e) {
                mesajStatus = std::string("[BLOCAT] ") + e.what();
            }
            return;
        }

        if (sf::FloatRect({contentLeftX + 445.f, btnY}, {100.f, 50.f}).contains(coordMouse)) {
            try {
                user.acordaNota(continutSelectat->getTitlu(), 1);
                noteAcordate[continutSelectat->getTitlu()] = 1;
                mesajStatus = "[VOT] Ai trimis nota 1. Media s-a actualizat!";
            } catch (const StreamingException& e) {
                mesajStatus = std::string("[BLOCAT] ") + e.what();
            }
            return;
        }

        if (auto serial = std::dynamic_pointer_cast<Serial>(continutSelectat)) {
            float episodesRightX = 800.f;
            float epY = 350.f;
            for(size_t i = 0; i < std::min<size_t>(serial->getDurateEpisoade().size(), 3); i++) {
                if (sf::FloatRect({episodesRightX, epY}, {450.f, 35.f}).contains(coordMouse)) {
                    if (user.getVarsta() < serial->getVarstaMinima()) {
                        mesajStatus = "[BLOCAT] Acest serial contine scene restrictionate varstei tale!"; return;
                    }
                    user.uitaTeLaEpisod(serial->getTitlu());
                    int urmat = progresSeriale[serial->getTitlu()];
                    if (static_cast<size_t>(urmat) <= i) progresSeriale[serial->getTitlu()] = static_cast<int>(i) + 1;
                    auto& hist = istoricUtilizatori[user.getNume()];
                    std::string labelEp = serial->getTitlu() + " (Vizionat Ep. " + std::to_string(i + 1) + ")";
                    if (std::find(hist.begin(), hist.end(), labelEp) == hist.end()) hist.push_back(labelEp);
                    mesajStatus = "[SERIAL] Ai terminat de vizionat Episodul " + std::to_string(i + 1); return;
                }
                epY += 40.f;
            }
        }
    }
    else if (stareCurenta == StareAplicatie::Statistici) {
        if (sf::FloatRect({40.f, 80.f}, {100.f, 40.f}).contains(coordMouse)) { stareCurenta = StareAplicatie::Catalog; return; }

        if (sf::FloatRect({1090.f, 80.f}, {150.f, 40.f}).contains(coordMouse)) {
            indexUserCurent = -1; stareCurenta = StareAplicatie::Login; mesajStatus = "Te-ai deconectat."; return;
        }

        auto& user = platforma.getUtilizatori()[indexUserCurent];

        if (sf::FloatRect({40.f, 480.f}, {160.f, 40.f}).contains(coordMouse)) {
            user.setPlan("Premium"); mesajStatus = "Felicitari! Ai acum acces la planul PREMIUM."; return;
        }

        if (sf::FloatRect({210.f, 480.f}, {180.f, 40.f}).contains(coordMouse)) {
            user.setPlan("Basic"); mesajStatus = "Plan retrogradat la standardul Basic."; return;
        }

        auto& listaWatchlist = user.getWatchlist().getLista();
        float wlY = 280.f;
        for (size_t i = 0; i < listaWatchlist.size(); i++) {
            if (sf::FloatRect({360.f, wlY}, {420.f, 30.f}).contains(coordMouse)) {
                std::string titluSters = listaWatchlist[i]->getTitlu();
                user.stergeDinWatchlistDupaTitlu(titluSters);
                mesajStatus = "[BACKEND] Eliminat cu succes: " + titluSters; return;
            }
            wlY += 35.f;
        }
    }
    else if (stareCurenta == StareAplicatie::AdminPanel) {
        if (sf::FloatRect({40.f, 80.f}, {100.f, 40.f}).contains(coordMouse)) { stareCurenta = StareAplicatie::Login; return; }

        // 1. Adauga Film
        if (sf::FloatRect({40.f, 300.f}, {350.f, 50.f}).contains(coordMouse)) {
            platforma.adaugaContinutInCatalog(std::make_shared<Film>(
                "The Batman", "Actiune", "O noua investigatie intunecata in Gotham...", 170, 16,
                "assets/images/batman.jpg", "https://www.youtube.com/watch?v=mqqft2x_Aa4"));
            incarcaPostere();
            mesajStatus = "[ADMIN] Filmul The Batman adaugat in catalog."; return;
        }

        // 2. Adauga Serial
        if (sf::FloatRect({40.f, 370.f}, {350.f, 50.f}).contains(coordMouse)) {
            platforma.adaugaContinutInCatalog(std::make_shared<Serial>(
                "The Last of Us S2", "Thriller", "Continuarea calatoriei pline de pericole a lui Ellie...",
                std::vector<int>{55, 62, 58}, 18,
                "assets/images/tlou.jpg", "https://www.youtube.com/watch?v=uLtkt8BonwM"));
            incarcaPostere();
            mesajStatus = "[ADMIN] Serialul The Last of Us adaugat."; return;
        }

        // 3. Adauga Documentar
        if (sf::FloatRect({40.f, 440.f}, {350.f, 50.f}).contains(coordMouse)) {
            platforma.adaugaContinutInCatalog(std::make_shared<Documentar>(
                "Free Solo", "Sport", "National Geographic", 100, "Alpinism", 12,
                "assets/images/free_solo.jpg", "https://www.youtube.com/watch?v=urRVZ4SW7WU"));
            incarcaPostere();
            mesajStatus = "[ADMIN] Documentarul Free Solo adaugat."; return;
        }

        if (sf::FloatRect({40.f, 510.f}, {400.f, 50.f}).contains(coordMouse)) {
            try {
                // Fortam o eroare cautand ceva ce sigur nu exista in baza de date
                platforma.cautaContinutDupaTitlu("Acest Film Nu Exista");
            }
            catch (const StreamingException& e) {
                // Prindem exceptia si o afisam direct pe ecranul utilizatorului!
                mesajStatus = std::string("[EXCEPTIE] Baza de date a raspuns: ") + e.what();
            }
            return;
        }
    }
}

void AplicatieGUI::ruleaza() {
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) { window.close(); }
            if (const auto* mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mouseClick->button == sf::Mouse::Button::Left) { proceseazaClick(mouseClick->position); }
            }
        }

        window.clear(sf::Color(15, 15, 15));

        randeazaBaraNavigatie();
        randeazaStatus();

        if (stareCurenta == StareAplicatie::Login) randeazaEcranLogin();
        else if (stareCurenta == StareAplicatie::Catalog) randeazaCatalog();
        else if (stareCurenta == StareAplicatie::Detalii) randeazaPaginaDetalii();
        else if (stareCurenta == StareAplicatie::Statistici) randeazaPaginaStatistici();
        else if (stareCurenta == StareAplicatie::AdminPanel) randeazaPanouAdmin();

        window.display();
    }
}