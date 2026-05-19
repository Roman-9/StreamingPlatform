#pragma once
#include "ContinutVideo.h"
#include <vector>
#include <memory>

class Serial : public ContinutVideo {
private:
    std::vector<int> durateEpisoade;
    size_t episodCurent;

public:
    Serial(std::string t, std::string g, std::string d, std::vector<int> durate, int v);
    ~Serial() override = default;

    void play() const override;
    bool vizioneazaEpisod();

    int getTimpRamas() const override;
    int getTimpVizionat() const override;
    void afisare(std::ostream& os) const override;

    [[nodiscard]] int getNumarEpisoade() const;
    [[nodiscard]] const std::vector<int>& getDurateEpisoade() const;

    [[nodiscard]] std::string getDurateAsConversieString() const;
    [[nodiscard]] std::shared_ptr<ContinutVideo> clone() const override;
};