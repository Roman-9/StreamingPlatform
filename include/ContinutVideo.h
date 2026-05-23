#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <memory>

class ContinutVideo {
private:
    std::string titlu;
    std::string gen;
    std::string descriere;
    int varstaMinima;
    std::string calePoster;
    std::string linkVizionare;
    std::vector<int> notePrimite;
    static int numarTotalContinut;

protected:
    virtual void do_afisare(std::ostream& os) const = 0;

public:
    ContinutVideo(std::string t, std::string g, std::string d, int v, std::string cp = "", std::string lv = "");
    ContinutVideo(const ContinutVideo& other);
    virtual ~ContinutVideo();

    const std::string& getTitlu() const;
    const std::string& getGen() const;
    const std::string& getDescriere() const;
    int getVarstaMinima() const;
    // cppcheck-suppress unusedFunction
    const std::string& getCalePoster() const { return calePoster; }
    // cppcheck-suppress unusedFunction
    const std::string& getLinkVizionare() const { return linkVizionare; }
    static int getNumarTotalContinut();

    void adaugaRecenzie(int nota);
    double getRating() const;
    bool aFostEvaluat() const;

    virtual void play() = 0;
    virtual int getTimpRamas() const = 0;
    virtual int getTimpVizionat() const = 0;
    virtual std::shared_ptr<ContinutVideo> clone() const = 0;
    void afisare(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const ContinutVideo& cv);
};