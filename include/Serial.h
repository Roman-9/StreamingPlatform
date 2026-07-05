#pragma once
#include "ContinutVideo.h"
#include <vector>

class Serial : public ContinutVideo {
private:
  std::vector<int> durateEpisoade;
  int episodCurent;

protected:
  void do_afisare(std::ostream &os) const override;

public:
  Serial(std::string t, std::string g, std::string d, std::vector<int> durate,
         int v, std::string cp = "", std::string lv = "");
  void play() override;
  bool vizioneazaEpisod();
  int getEpisodCurent() const override;
  void setEpisodCurent(int ep) override;
  int getTimpRamas() const override;
  int getTimpVizionat() const override;
  int getNumarEpisoade() const override;
  const std::vector<int> &getDurateEpisoade() const override;
  std::shared_ptr<ContinutVideo> clone() const override;

  bool matchesFilter(FiltruCatalog filtru) const override;
  std::string getDetaliiSpecifice() const override;
  // cppcheck-suppress unusedFunction
  bool areEpisoade() const override { return true; }
};