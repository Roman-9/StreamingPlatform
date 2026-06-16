#pragma once
#include "ContinutVideo.h"
#include <string>

class CanalTV : public ContinutVideo {
private:
    std::string programCurent;
    bool esteLive;
    bool inregistreazaAcum = false;

protected:
    void do_afisare(std::ostream& os) const override;

public:
    CanalTV(std::string t, std::string g, std::string d, int varsta, std::string program, bool live, std::string cp = "", std::string lv = "");

    void play() override;
    int getTimpRamas() const override;
    int getTimpVizionat() const override;
    std::shared_ptr<ContinutVideo> clone() const override;
    
    bool matchesFilter(FiltruCatalog filtru) const override;
    std::string getDetaliiSpecifice() const override;
    
    const std::string& getProgramCurent() const;
    bool getEsteLive() const;
    void setEsteLive(bool status);
    bool getInregistreazaAcum() const;
    void inregistreazaProgram();
};
