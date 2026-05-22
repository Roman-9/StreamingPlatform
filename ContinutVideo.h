#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class ContinutVideo {
protected:
    std::string titlu;
    std::string gen;
    std::string descriere;
    int varstaMinima;
    std::string calePoster;
    std::string linkVizionare;
    std::vector<int> notePrimite;
    static int numarTotalContinut;

public:
ContinutVideo(std::string t, std::string g, std::string d, int v, std::string cp = "", std::string lv = "");    virtual ~ContinutVideo() = default;

    const std::string& getTitlu() const;
    const std::string& getGen() const;
    const std::string& getDescriere() const;
    int getVarstaMinima() const;
    const std::string& getCalePoster() const { return calePoster; }
    const std::string& getLinkVizionare() const { return linkVizionare; }
    static int getNumarTotalContinut();

    void adaugaRecenzie(int nota);
    double getRating() const;

    virtual void play() = 0;
    virtual int getTimpRamas() const = 0;
    virtual int getTimpVizionat() const = 0;
    virtual std::shared_ptr<ContinutVideo> clone() const = 0;
    virtual void afisare(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const ContinutVideo& cv);
};