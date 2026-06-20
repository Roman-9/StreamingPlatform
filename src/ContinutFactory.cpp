#include "ContinutFactory.h"

std::shared_ptr<ContinutVideo> ContinutFactory::creeazaFilm(
    const std::string& titlu, const std::string& gen, const std::string& descriere,
    int durata, int varstaMinima, const std::string& calePoster, const std::string& linkVizionare) 
{
    return std::make_shared<Film>(titlu, gen, descriere, durata, varstaMinima, calePoster, linkVizionare);
}

std::shared_ptr<ContinutVideo> ContinutFactory::creeazaSerial(
    const std::string& titlu, const std::string& gen, const std::string& descriere,
    const std::vector<int>& durateEpisoade, int varstaMinima, const std::string& calePoster, const std::string& linkVizionare) 
{
    return std::make_shared<Serial>(titlu, gen, descriere, durateEpisoade, varstaMinima, calePoster, linkVizionare);
}

std::shared_ptr<ContinutVideo> ContinutFactory::creeazaDocumentar(
    const std::string& titlu, const std::string& gen, const std::string& descriere,
    int durata, const std::string& subiect, int varstaMinima, const std::string& calePoster, const std::string& linkVizionare) 
{
    return std::make_shared<Documentar>(titlu, gen, descriere, durata, subiect, varstaMinima, calePoster, linkVizionare);
}

std::shared_ptr<ContinutVideo> ContinutFactory::creeazaCanalTV(
    const std::string& titlu, const std::string& gen, const std::string& descriere,
    int varstaMinima, const std::string& programCurent, bool esteLive, const std::string& calePoster, const std::string& linkVizionare) 
{
    return std::make_shared<CanalTV>(titlu, gen, descriere, varstaMinima, programCurent, esteLive, calePoster, linkVizionare);
}
