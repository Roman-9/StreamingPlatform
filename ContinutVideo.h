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
    std::vector<int> notePrimite;
    static int numarTotalContinut;

public:
    ContinutVideo(std::string t, std::string g, std::string d, int v);
    virtual ~ContinutVideo() = default;

    virtual void play() const = 0;
    virtual int getTimpRamas() const = 0;
    virtual int getTimpVizionat() const = 0;

    [[nodiscard]] const std::string& getTitlu() const;
    [[nodiscard]] const std::string& getGen() const;
    [[nodiscard]] const std::string& getDescriere() const;
    [[nodiscard]] int getVarstaMinima() const;

    [[nodiscard]] virtual std::shared_ptr<ContinutVideo> clone() const = 0;

    static int getNumarTotalContinut();

    void adaugaRecenzie(int nota);
    [[nodiscard]] double getRating() const;

    friend std::ostream& operator<<(std::ostream& os, const ContinutVideo& cv);
    virtual void afisare(std::ostream& os) const = 0;
};