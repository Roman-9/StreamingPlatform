#pragma once
#include "CanalTV.h"
#include "ContinutVideo.h"
#include "Documentar.h"
#include "Film.h"
#include "Serial.h"
#include <memory>
#include <string>
#include <vector>

class ContinutFactory {
public:
  static std::shared_ptr<ContinutVideo>
  creeazaDinBazaDeDate(const std::string &tip, const std::string &titlu,
                       const std::string &gen, const std::string &descriere,
                       const std::string &valoareSpecifica, int varstaMinima,
                       const std::string &calePoster,
                       const std::string &linkVizionare);

  static std::shared_ptr<ContinutVideo>
  creeazaFilm(const std::string &titlu, const std::string &gen,
              const std::string &descriere, int durata, int varstaMinima,
              const std::string &calePoster, const std::string &linkVizionare);

  static std::shared_ptr<ContinutVideo>
  creeazaSerial(const std::string &titlu, const std::string &gen,
                const std::string &descriere,
                const std::vector<int> &durateEpisoade, int varstaMinima,
                const std::string &calePoster,
                const std::string &linkVizionare);

  static std::shared_ptr<ContinutVideo>
  creeazaDocumentar(const std::string &titlu, const std::string &gen,
                    const std::string &descriere, int durata,
                    const std::string &subiect, int varstaMinima,
                    const std::string &calePoster,
                    const std::string &linkVizionare);

  static std::shared_ptr<ContinutVideo>
  creeazaCanalTV(const std::string &titlu, const std::string &gen,
                 const std::string &descriere, int varstaMinima,
                 const std::string &programCurent, bool esteLive,
                 const std::string &calePoster,
                 const std::string &linkVizionare);
};
