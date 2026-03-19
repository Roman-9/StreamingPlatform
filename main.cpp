#include <iostream>
#include <string>
#include <vector>

class Film {
private:
    std::string titlu;
    std::string gen;
    std::string descriere;
    int durata;
    int varstaMinima;
    std::vector<int> notePrimite;

public:
    explicit Film(const std::string &titlu = "Fara titlu", const std::string &gen = "Necunoscut",
                  const std::string &descriere = "Fara descriere", int durata = 0, int varstaMinima = 0)
        : titlu(titlu),
          gen(gen),
          descriere(descriere),
          durata(durata),
          varstaMinima(varstaMinima) {
    }

    [[nodiscard]] const std::string &getTitlu() const {
        return titlu;
    }

    [[nodiscard]] const std::string &getGen() const {
        return gen;
    }

    [[nodiscard]] const std::string &getDescriere() const {
        return descriere;
    }

    [[nodiscard]] int getDurata() const {
        return durata;
    }

    [[nodiscard]] int getVarstaMinima() const {
        return varstaMinima;
    }

    void adaugaRecenzie(int nota) {
        if (nota >= 1 && nota <= 10) {
            notePrimite.push_back(nota);
        } else {
            std::cout << "[Eroare] Nota trebuie sa fie intre 1 si 10!\n";
        }
    }

    [[nodiscard]] double getRating() const {
        if (notePrimite.empty()) return 0.0;
        double suma = 0.0;
        for (size_t i = 0; i < notePrimite.size(); ++i) {
            suma += notePrimite[i];
        }
        return suma / static_cast<double>(notePrimite.size());
    }

    friend std::ostream &operator<<(std::ostream &os, const Film &f) {
        os << "[FILM] " << f.titlu << " (gen: " << f.gen << ") | Nota: " << f.getRating() << " | Durata: " << f.durata
                << "min\n";
        os << "Descriere: " << f.descriere << "\n";
        return os;
    }
};

class Serial {
private:
    std::string titlu;
    std::string gen;
    std::string descriere;
    std::vector<int> durateEpisoade;
    size_t episodCurent;
    int varstaMinima;
    std::vector<int> notePrimite;

public:
    explicit Serial(const std::string &titlu = "Fara titlu", const std::string &gen = "Necunoscut",
                    const std::string &descriere = "Fara descriere", const std::vector<int> &durateEpisoade = {},
                    int varstaMinima = 0)
        : titlu(titlu),
          gen(gen),
          descriere(descriere),
          durateEpisoade(durateEpisoade),
          episodCurent(0),
          varstaMinima(varstaMinima) {
    }

    [[nodiscard]] const std::string &getTitlu() const {
        return titlu;
    }

    [[nodiscard]] const std::string &getGen() const {
        return gen;
    }

    [[nodiscard]] const std::string &getDescriere() const {
        return descriere;
    }

    [[nodiscard]] int getVarstaMinima() const {
        return varstaMinima;
    }

    void adaugaRecenzie(int nota) {
        if (nota >= 1 && nota <= 10) { notePrimite.push_back(nota); }
    }

    [[nodiscard]] double getRating() const {
        if (notePrimite.empty()) return 0.0;
        double suma = 0.0;
        for (size_t i = 0; i < notePrimite.size(); ++i) { suma += notePrimite[i]; }
        return suma / static_cast<double>(notePrimite.size());
    }

    [[nodiscard]] int getTimpRamas() const {
        int timpRamas = 0;
        for (size_t i = episodCurent; i < durateEpisoade.size(); ++i) {
            timpRamas += durateEpisoade[i];
        }
        return timpRamas;
    }

    [[nodiscard]] int getTimpVizionat() const {
        int timpVizionat = 0;
        for (size_t i = 0; i < episodCurent; ++i) {
            timpVizionat += durateEpisoade[i];
        }
        return timpVizionat;
    }

    bool vizioneazaEpisod() {
        if (episodCurent < durateEpisoade.size()) {
            episodCurent++;
            return true;
        }
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Serial &s) {
        os << "[SERIAL] " << s.titlu << " (gen: " << s.gen << ") | Nota: " << s.getRating()
                << " | Progres: Ep. " << s.episodCurent << " din " << s.durateEpisoade.size() << "\n";
        os << "Descriere: " << s.descriere << "\n";
        return os;
    }
};

class Watchlist {
private:
    std::vector<Film> filme;
    std::vector<Serial> seriale;

public:
    Watchlist() = default;

    //Destructor
    ~Watchlist() {
        filme.clear();
        seriale.clear();
    }

    //Constructorul de copiere
    Watchlist(const Watchlist &other) : filme(other.filme), seriale(other.seriale) {
        std::cout << "Constructor de copiere apelat.\n";
    }

    //Constructorul de atribuire
    Watchlist &operator=(const Watchlist &other) {
        if (this != &other) {
            filme = other.filme;
            seriale = other.seriale;
            std::cout << "Operator de atribuire apelat.\n";
        }
        return *this;
    }

    void adaugaFilm(const Film &f) {
        filme.push_back(f);
    }

    void adaugaSerial(const Serial &s) {
        seriale.push_back(s);
    }

    Film *gasesteFilm(const std::string &titluCautat) {
        for (auto &f: filme) {
            if (f.getTitlu() == titluCautat) return &f;
        }
        return nullptr;
    }

    Serial *gasesteSerial(const std::string &titluCautat) {
        for (auto &s: seriale) {
            if (s.getTitlu() == titluCautat) return &s;
        }
        return nullptr;
    }

    bool stergeDupaTitlu(const std::string &titluCautat) {
        for (auto it = filme.begin(); it != filme.end(); ++it) {
            if (it->getTitlu() == titluCautat) {
                filme.erase(it);
                return true;
            }
        }
        for (auto it = seriale.begin(); it != seriale.end(); ++it) {
            if (it->getTitlu() == titluCautat) {
                seriale.erase(it);
                return true;
            }
        }
        return false;
    }

    bool mutaInIstoric(const std::string &titluCautat, Watchlist &istoricDestinatie) {
        for (auto it = filme.begin(); it != filme.end(); ++it) {
            if (it->getTitlu() == titluCautat) {
                istoricDestinatie.adaugaFilm(*it); // Il copiem in istoric
                filme.erase(it); // Il stergem de aici
                return true;
            }
        }
        for (auto it = seriale.begin(); it != seriale.end(); ++it) {
            if (it->getTitlu() == titluCautat) {
                istoricDestinatie.adaugaSerial(*it);
                seriale.erase(it);
                return true;
            }
        }
        return false;
    }

    void vizioneazaEpisodDinSerial(const std::string &titluCautat) {
        for (auto &s: seriale) {
            if (s.getTitlu() == titluCautat) {
                if (s.vizioneazaEpisod()) {
                    std::cout << "Ai vizionat un episod nou din '" << titluCautat << "'.\n";
                } else {
                    std::cout << "Ai terminat deja serialul '" << titluCautat << "'!\n";
                }
                return;
            }
        }
        std::cout << "Serialul '" << titluCautat << "' nu a fost gasit in lista.\n";
    }

    void afiseazaDupaGen(const std::string &genCautat) const {
        std::cout << "Rezultate pentru genul: " << genCautat << "\n";
        bool gasit = false;
        for (const auto &f: filme) {
            if (f.getGen() == genCautat) {
                std::cout << f;
                gasit = true;
            }
        }
        for (const auto &s: seriale) {
            if (s.getGen() == genCautat) {
                std::cout << s;
                gasit = true;
            }
        }
        if (!gasit) std::cout << "Nu s-au gasit elemente.\n";
    }

    void afiseazaTopRating() const {
        double maxRating = -1.0;
        std::string topTitlu = "";
        for (const auto &f: filme) {
            if (f.getRating() > maxRating) {
                maxRating = f.getRating();
                topTitlu = f.getTitlu();
            }
        }
        for (const auto &s: seriale) {
            if (s.getRating() > maxRating) {
                maxRating = s.getRating();
                topTitlu = s.getTitlu();
            }
        }
        if (maxRating != -1.0) {
            std::cout << "Cel mai bine cotat titlu este: '" << topTitlu << "' cu nota " << maxRating << "\n";
        } else {
            std::cout << "Lista este goala.\n";
        }
    }

    [[nodiscard]] int calculeazaDurataTotalaRamas() const {
        int durataTotala = 0;
        for (const auto &film: filme) {
            durataTotala += film.getDurata();
        }
        for (const auto &s: seriale) {
            durataTotala += s.getTimpRamas();
        }
        return durataTotala;
    }

    [[nodiscard]] int calculeazaTimpPierdut() const {
        int durata = 0;
        for (const auto &f: filme) {
            durata += f.getDurata();
        }
        for (const auto &s: seriale) {
            durata += s.getTimpVizionat();
        }
        return durata;
    }

    friend std::ostream &operator<<(std::ostream &os, const Watchlist &wl) {
        os << "--- FILME (" << wl.filme.size() << ") ---\n";
        for (size_t i = 0; i < wl.filme.size(); ++i) { os << wl.filme[i]; }

        os << "\n--- SERIALE (" << wl.seriale.size() << ") ---\n";
        for (size_t i = 0; i < wl.seriale.size(); ++i) { os << wl.seriale[i]; }
        return os;
    }
};

class Utilizator {
private:
    std::string nume;
    std::string plan;
    int varsta;
    Watchlist watchlist;
    Watchlist istoricVizionari;

public:
    explicit Utilizator(const std::string &nume = "Anon", const std::string &plan = "Free", int varsta = 18)
        : nume(nume),
          plan(plan),
          varsta(varsta),
          watchlist(),
          istoricVizionari() {
    }

    [[nodiscard]] const std::string &getNume() const {
        return nume;
    }

    [[nodiscard]] const std::string &getPlan() const {
        return plan;
    }

    [[nodiscard]] int getVarsta() const {
        return varsta;
    }

    void setPlan(const std::string &planNou) {
        plan = planNou;
    }

    void adaugaFilm(const Film &film) {
        watchlist.adaugaFilm(film);
    }

    void adaugaSerial(const Serial &serial) {
        watchlist.adaugaSerial(serial);
    }

    void stergeDinLista(const std::string &titlu) {
        watchlist.stergeDupaTitlu(titlu);
    }

    void uitaTeLaEpisod(const std::string &titluSerial) { watchlist.vizioneazaEpisodDinSerial(titluSerial); }

    void marcheazaCaVazut(const std::string &titlu) {
        if (watchlist.mutaInIstoric(titlu, istoricVizionari)) {
            std::cout << "[INFO] '" << titlu << "' a fost mutat in Istoricul de Vizionari.\n";
        } else {
            std::cout << "[EROARE] Titlul nu a fost gasit in lista activa.\n";
        }
    }

    void acordaNota(const std::string &titlu, int nota) {
        Film *f = watchlist.gasesteFilm(titlu);
        if (f) {
            f->adaugaRecenzie(nota);
            std::cout << nume << " a acordat nota " << nota << " filmului " << titlu << ".\n";
            return;
        }

        Serial *s = watchlist.gasesteSerial(titlu);
        if (s) {
            s->adaugaRecenzie(nota);
            std::cout << nume << " a acordat nota " << nota << " serialului " << titlu << ".\n";
            return;
        }
    }

    void afiseazaTimpRamas() const {
        std::cout << nume << " are nevoie de " << watchlist.calculeazaDurataTotalaRamas() <<
                " minute pentru a vedea toata lista.\n";
    }

    void afiseazaStatistici() const {
        std::cout << nume << " a petrecut " << istoricVizionari.calculeazaTimpPierdut() <<
                " minute uitandu-se la continut din istoric.\n";
    }

    void cautaGen(const std::string &gen) const {
        watchlist.afiseazaDupaGen(gen);
    }

    void recomandaTop() const {
        watchlist.afiseazaTopRating();
    }

    friend std::ostream &operator<<(std::ostream &os, const Utilizator &user) {
        os << "Utilizator: " << user.nume << " are planul tarifar: " << user.plan << "\n";
        os << "Lista de vizionare este: \n" << user.watchlist << "\n";
        return os;
    }
};

class PlatformaStreaming {
private:
    std::string numePlatforma;
    std::vector<Film> catalogFilme;
    std::vector<Serial> catalogSeriale;

public:
    explicit PlatformaStreaming(const std::string &numePlatforma = "MyStream")
        : numePlatforma(numePlatforma) {
    }

    void incarcaFilm(const Film &f) {
        catalogFilme.push_back(f);
    }
    void incarcaSerial(const Serial &s) {
        catalogSeriale.push_back(s);
    }

    void afiseazaCatalog() const {
        std::cout << "\n=== CATALOG GLOBAL " << numePlatforma << " ===\n";
        for (const auto &f: catalogFilme) {
            std::cout << f;
        }
        for (const auto &s: catalogSeriale) {
            std::cout << s;
        }
        std::cout << "================================\n";
    }

    // AICI E MAGIA OOP: Platforma decide cine primeste filmul
    void adaugaInListaUtilizator(Utilizator &user, const std::string &titluCautat) {
        // Cautam in filme
        for (const auto &f: catalogFilme) {
            if (f.getTitlu() == titluCautat) {
                if (user.getVarsta() >= f.getVarstaMinima()) {
                    user.adaugaFilm(f);
                    std::cout << "[Sistem] '" << titluCautat << "' adaugat in lista lui " << user.getNume() << ".\n";
                } else {
                    std::cout << "[BLOCAT] " << user.getNume() << " are doar " << user.getVarsta()
                            << " ani, varsta minima este " << f.getVarstaMinima() << "+!\n";
                }
                return;
            }
        }
        // Cautam in seriale
        for (const auto &s: catalogSeriale) {
            if (s.getTitlu() == titluCautat) {
                if (user.getVarsta() >= s.getVarstaMinima()) {
                    user.adaugaSerial(s);
                    std::cout << "[Sistem] '" << titluCautat << "' adaugat in lista lui " << user.getNume() << ".\n";
                } else {
                    std::cout << "[BLOCAT] " << user.getNume() << " are doar " << user.getVarsta()
                            << " ani, varsta minima este " << s.getVarstaMinima() << "+!\n";
                }
                return;
            }
        }
        std::cout << "[Eroare] Titlul '" << titluCautat << "' nu exista pe platforma.\n";
    }
};

int main() {
    std::cout << "=== INITIALIZARE PLATFORMA ===\n";
    PlatformaStreaming netflix("Netflex");

    //Content
    Film f1("Scream 7", "Horror",
            "Un nou ucigas Ghostface apare in orasul in care Sidney Prescott isi construise o noua viata, transformand adolescentii in tinte.",
            114, 18);
    Film f2("The Running Man", "Actiune",
            "A man joins a game show in which contestants, allowed to flee anywhere in the world, are pursued by hunters hired to kill them.",
            152, 15);
    Film f3("Inception", "SF",
            "Un hot care fura secrete corporative folosind tehnologia de impartasire a viselor primeste sarcina inversa: sa implanteze o idee in mintea unui CEO.",
            148, 12);

    Serial s1("Breaking Bad", "Drama",
              "Un profesor de chimie de liceu, diagnosticat cu cancer pulmonar inoperabil, apeleaza la productia si vanzarea de metamfetamina pentru a asigura viitorul familiei sale.",
              {48, 47, 43, 51, 46}, 18);
    Serial s2("Dexter", "Thriller",
              "E inteligent. E adorabil. E Dexter Morgan, criminalul in serie preferat al Americii, care isi petrece zilele rezolvand crime si noptile comitandu-le.",
              {45, 50}, 18);

    // Test Recenzii
    f1.adaugaRecenzie(6);
    f1.adaugaRecenzie(7);
    f2.adaugaRecenzie(10);
    f3.adaugaRecenzie(9);
    s1.adaugaRecenzie(10);
    s1.adaugaRecenzie(9);
    s2.adaugaRecenzie(9);
    f1.adaugaRecenzie(15);
    f1.adaugaRecenzie(-3);


    //Incarcam platforma cu continut
    netflix.incarcaFilm(f1);
    netflix.incarcaFilm(f2);
    netflix.incarcaFilm(f3);
    netflix.incarcaSerial(s1);
    netflix.incarcaSerial(s2);
    netflix.afiseazaCatalog();

    std::cout << "\n=== TESTE FUNCTIONALITATI DE BAZA ===\n";
    std::cout << "Test descriere Film: " << f1.getDescriere() << "\n";
    std::cout << "Test descriere Serial: " << s1.getDescriere() << "\n\n";

    // Cream utilizator
    Utilizator user1("Andrei", "Free", 25);
    std::cout << "Utilizatorul " << user1.getNume() << " are initial planul " << user1.getPlan() << "\n\n";
    user1.setPlan("Premium");

    //Platforma adauga filmele dupa ce verifica varsta
    netflix.adaugaInListaUtilizator(user1, "Scream 7");
    netflix.adaugaInListaUtilizator(user1, "The Running Man");
    netflix.adaugaInListaUtilizator(user1, "Inception");
    netflix.adaugaInListaUtilizator(user1, "Breaking Bad");
    netflix.adaugaInListaUtilizator(user1, "Dexter");

    //Control Parental
    std::cout << "\n--- TEST CONTROL PARENTAL ---\n";
    Utilizator userCopil("Matei", "Free", 14);
    netflix.adaugaInListaUtilizator(userCopil, "Inception"); // Are voie (14 >= 12)
    netflix.adaugaInListaUtilizator(userCopil, "Scream 7"); // BLOCAT (14 < 18)

    std::cout << "\n--- PROFIL ANDREI ---\n";
    std::cout << user1;

    std::cout << "\nAfisare timp ramas inainte de vizionare:\n";
    user1.afiseazaTimpRamas();

    std::cout << "\n--- TEST VIZIONARE SERIAL PANA LA CAPAT ---\n";
    user1.uitaTeLaEpisod("Dexter"); // Vede ep 1
    user1.uitaTeLaEpisod("Dexter"); // Vede ep 2
    user1.uitaTeLaEpisod("Dexter"); // Eroare! Nu mai sunt episoade

    std::cout << "\nAfisare timp ramas dupa vizionare:\n";
    user1.afiseazaTimpRamas();

    std::cout << "\n--- TEST NOTARE FILM INEXISTENT ---\n";
    user1.acordaNota("Film Fals", 10);

    std::cout << "\nRecomandare top din lista activa:\n";
    user1.recomandaTop();

    // Istoric vizionari si Acordare Note
    std::cout << "\n[Actiune] Andrei termina 'The Running Man' si acorda o nota!\n";
    user1.acordaNota("The Running Man", 10);
    user1.marcheazaCaVazut("The Running Man");

    // Eroare mutare in istoric de 2 ori
    std::cout << "\n--- TEST DE STRES: MUTARE IN ISTORIC DUBLA ---\n";
    user1.marcheazaCaVazut("The Running Man"); // Eroare, e deja in istoric

    std::cout << "\nStergem continut din lista activa:\n";
    user1.stergeDinLista("Scream 7");
    user1.stergeDinLista("Film Inexistent");

    std::cout << "\nProfil Actualizat:\n";
    std::cout << user1;
    user1.afiseazaStatistici();

    std::cout << "\nCautare continut Horror:\n";
    user1.cautaGen("Horror");

    std::cout << "\nCautare continut SF:\n";
    user1.cautaGen("SF");

    std::cout << "\nRecomandare top din lista activa:\n";
    user1.recomandaTop(); // Running Man nu mai e aici, deci topul ar trebui sa fie Breaking Bad

    std::cout << "\nTestare Memorie\n";
    Utilizator user2 = user1;
    Utilizator user3("Ana", "Free", 22);
    user3 = user1;

    std::cout << "Test copie 1 (Nume): " << user2.getNume() << "\n";
    std::cout << "Test copie 2 (Plan): " << user3.getPlan() << "\n";

    return 0;
}
