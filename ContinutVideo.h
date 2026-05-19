#pragma once
#include <string>
#include <vector>
#include <iostream>

class ContinutVideo {
protected: 
    std::string titlu;
    std::string gen;
    std::string descriere;
    int varstaMinima;
    std::vector<int> notePrimite;

public:
    explicit ContinutVideo(std::string t = "Fara titlu", std::string g = "Necunoscut",
                           std::string d = "Fara descriere", int v = 0);
    virtual ~ContinutVideo() = default;

    [[nodiscard]] const std::string& getTitlu() const;
    [[nodiscard]] const std::string& getGen() const;
    [[nodiscard]] const std::string& getDescriere() const;
    [[nodiscard]] int getVarstaMinima() const;

    void adaugaRecenzie(int nota);
    [[nodiscard]] double getRating() const;

    virtual void play() = 0; 
    virtual void afiseazaDetalii(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const ContinutVideo& cv);
};