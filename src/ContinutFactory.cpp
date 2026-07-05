#include "ContinutFactory.h"
#include <sstream>

std::shared_ptr<ContinutVideo> ContinutFactory::creeazaDinBazaDeDate(
    const std::string &tip, const std::string &titlu, const std::string &gen,
    const std::string &descriere, const std::string &valoareSpecifica,
    int varstaMinima, const std::string &calePoster,
    const std::string &linkVizionare) {
    if (tip == "FILM") {
        int durata = std::stoi(valoareSpecifica);
        return creeazaFilm(titlu, gen, descriere, durata, varstaMinima, calePoster,
                           linkVizionare);
    } else if (tip == "SERIAL") {
        std::vector<int> vectorDurate;
        std::stringstream ss(valoareSpecifica);
        std::string token;
        while (std::getline(ss, token, ',')) {
            if (!token.empty())
                vectorDurate.push_back(std::stoi(token));
        }
        return creeazaSerial(titlu, gen, descriere, vectorDurate, varstaMinima,
                             calePoster, linkVizionare);
    } else if (tip == "DOCUMENTAR") {
        int durata = std::stoi(valoareSpecifica);
        std::string subiect = gen;
        return creeazaDocumentar(titlu, gen, descriere, durata, subiect,
                                 varstaMinima, calePoster, linkVizionare);
    } else if (tip == "CANAL_TV") {
        std::string program = "Program Necunoscut";
        bool live = true;

        std::stringstream ss(valoareSpecifica);
        std::string token;
        if (std::getline(ss, token, ','))
            program = token;
        if (std::getline(ss, token, ','))
            live = (token == "1");

        return creeazaCanalTV(titlu, gen, descriere, varstaMinima, program, live,
                              calePoster, linkVizionare);
    }
    return nullptr;
}

std::shared_ptr<ContinutVideo>
ContinutFactory::creeazaFilm(const std::string &titlu, const std::string &gen,
                             const std::string &descriere, int durata,
                             int varstaMinima, const std::string &calePoster,
                             const std::string &linkVizionare) {
    return std::make_shared<Film>(titlu, gen, descriere, durata, varstaMinima,
                                  calePoster, linkVizionare);
}

std::shared_ptr<ContinutVideo>
ContinutFactory::creeazaSerial(const std::string &titlu, const std::string &gen,
                               const std::string &descriere,
                               const std::vector<int> &durateEpisoade,
                               int varstaMinima, const std::string &calePoster,
                               const std::string &linkVizionare) {
    return std::make_shared<Serial>(titlu, gen, descriere, durateEpisoade,
                                    varstaMinima, calePoster, linkVizionare);
}

std::shared_ptr<ContinutVideo> ContinutFactory::creeazaDocumentar(
    const std::string &titlu, const std::string &gen,
    const std::string &descriere, int durata, const std::string &subiect,
    int varstaMinima, const std::string &calePoster,
    const std::string &linkVizionare) {
    return std::make_shared<Documentar>(titlu, gen, descriere, durata, subiect,
                                        varstaMinima, calePoster, linkVizionare);
}

std::shared_ptr<ContinutVideo> ContinutFactory::creeazaCanalTV(
    const std::string &titlu, const std::string &gen,
    const std::string &descriere, int varstaMinima,
    const std::string &programCurent, bool esteLive,
    const std::string &calePoster, const std::string &linkVizionare) {
    return std::make_shared<CanalTV>(titlu, gen, descriere, varstaMinima,
                                     programCurent, esteLive, calePoster, linkVizionare);
}
