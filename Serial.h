#pragma once
#include "ContinutVideo.h"
#include <vector>

class Serial : public ContinutVideo {
private:
    std::vector<int> durateEpisoade;
    int episodCurent;
public:
    Serial(std::string t, std::string g, std::string d, std::vector<int> durate, int v, std::string cp = "", std::string lv = "");
    void play() override;
    bool vizioneazaEpisod();
    int getEpisodCurent() const;
    int getTimpRamas() const override;
    int getTimpVizionat() const override;
    int getNumarEpisoade() const;
    const std::vector<int>& getDurateEpisoade() const;
    void afisare(std::ostream& os) const override;
    std::string getDurateAsConversieString() const;
    std::shared_ptr<ContinutVideo> clone() const override;
};