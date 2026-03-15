#include <iostream>
#include <string>
#include <vector>

class Film {
private:
    std::string titlu;
    std::string gen;
    std::string descriere;
    int durata;
    double rating;

public:
    explicit Film(const std::string &titlu = "Fara titlu", const std::string &gen = "Necunoscut",
         const std::string &descriere = "Fara descriere", int durata = 0, double rating =0.0)
        : titlu(titlu),
          gen(gen),
          descriere(descriere),
          durata(durata),
          rating(rating) {
    }

    [[nodiscard]] const std::string& getTitlu() const {
        return titlu;
    }

    [[nodiscard]] const std::string& getGen() const {
        return gen;
    }

    [[nodiscard]] const std::string& getDescriere() const {
        return descriere;
    }

    [[nodiscard]] int getDurata() const {
        return durata;
    }

    [[nodiscard]] double getRating() const {
        return rating;
    }

    friend std::ostream &operator<<(std::ostream &os, const Film &f) {
        os << "[FILM] " << f.titlu << " (gen: " << f.gen << ") | Nota: " << f.rating << " | Durata: " << f.durata << "min\n";
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
    double rating;

    public:
    explicit Serial(const std::string &titlu = "Fara titlu", const std::string &gen = "Necunoscut",
           const std::string &descriere = "Fara descriere", const std::vector<int> &durateEpisoade = {}, double rating = 0.0)
        : titlu(titlu),
          gen(gen),
          descriere(descriere),
          durateEpisoade(durateEpisoade),
          episodCurent(0),
          rating(rating) {
    }

    [[nodiscard]] const std::string& getTitlu() const {
        return titlu;
    }

    [[nodiscard]] const std::string& getGen() const {
        return gen;
    }

    [[nodiscard]] const std::string& getDescriere() const {
        return descriere;
    }

    [[nodiscard]] double getRating() const {
        return rating;
    }

    [[nodiscard]] int getTimpRamas() const {
        int timpRamas = 0;
        for (size_t i = episodCurent; i < durateEpisoade.size(); ++i) {
            timpRamas += durateEpisoade[i];
        }
        return timpRamas;
    }

    bool vizioneazaEpisod() {
        if (episodCurent < durateEpisoade.size()) {
            episodCurent++;
            return true;
        }
        return false;
    }

    friend std::ostream &operator<<(std::ostream &os, const Serial &s) {
        os << "[SERIAL] " << s.titlu << " (gen: " << s.gen << ") | Nota: " << s.rating
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

    void vizioneazaEpisodDinSerial(const std::string& titluCautat) {
        for (auto& s : seriale) {
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

    void afiseazaDupaGen(const std::string& genCautat) const {
        std::cout << "Rezultate pentru genul: " << genCautat << "\n";
        bool gasit = false;
        for (const auto& f : filme) {
            if (f.getGen() == genCautat) { std::cout << f; gasit = true; }
        }
        for (const auto& s : seriale) {
            if (s.getGen() == genCautat) { std::cout << s; gasit = true; }
        }
        if (!gasit) std::cout << "Nu s-au gasit elemente.\n";
    }

    void afiseazaTopRating() const {
        double maxRating = -1.0;
        std::string topTitlu = "";
        for (const auto& f : filme) {
            if (f.getRating() > maxRating) {
                maxRating = f.getRating(); topTitlu = f.getTitlu();
            }
        }
        for (const auto& s : seriale) {
            if (s.getRating() > maxRating) {
                maxRating = s.getRating(); topTitlu = s.getTitlu();
            }
        }
        if (maxRating != -1.0) {
            std::cout << "Cel mai bine cotat titlu este: '" << topTitlu << "' cu nota " << maxRating << "\n";
        } else {
            std::cout << "Lista este goala.\n";
        }
    }

    [[nodiscard]] int calculeazaDurataTotala() const {
        int durataTotala = 0;
        for (const auto& film : filme) {
            durataTotala += film.getDurata();
        }
        for (const auto& s : seriale) {
            durataTotala += s.getTimpRamas();
        }
        return durataTotala;
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
    Watchlist watchlist;

public:
    explicit Utilizator(const std::string &nume = "Anon", const std::string &plan = "Free")
        : nume(nume),
          plan(plan),
          watchlist() {
    }

    [[nodiscard]] const std::string& getNume() const {
        return nume;
    }

    [[nodiscard]] const std::string& getPlan() const {
        return plan;
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

    void uitaTeLaEpisod(const std::string& titluSerial) { watchlist.vizioneazaEpisodDinSerial(titluSerial); }

    void afiseazaTimpRamas() const {
        std::cout << nume << " are nevoie de " << watchlist.calculeazaDurataTotala() << " minute pentru a vedea toata lista.\n";
    }

    void cautaGen(const std::string& gen) const { watchlist.afiseazaDupaGen(gen); }

    void recomandaTop() const { watchlist.afiseazaTopRating(); }

    friend std::ostream &operator<<(std::ostream &os, const Utilizator &user) {
        os << "Utilizator: " << user.nume << " are planul tarifar: " << user.plan << "\n";
        os << "Lista de vizionare este: \n" << user.watchlist << "\n";
        return os;
    }
};

int main() {
    Film f1("Scream 7", "Horror", "Un nou ucigas Ghostface apare in orasul in care Sidney Prescott isi construise o noua viata, transformand adolescentii in tinte.", 114, 6.5);
    Film f2("The Running Man", "Actiune", "A man joins a game show in which contestants, allowed to flee anywhere in the world, are pursued by hunters hired to kill them.", 152, 9.0);
    Film f3("Inception", "SF", "Un hot care fura secrete corporative folosind tehnologia de impartasire a viselor primeste sarcina inversa: sa implanteze o idee in mintea unui CEO.", 148, 8.8);

    Serial s1("Breaking Bad", "Drama", "Un profesor de chimie de liceu, diagnosticat cu cancer pulmonar inoperabil, apeleaza la productia si vanzarea de metamfetamina pentru a asigura viitorul familiei sale.", {48, 47, 43, 51, 46}, 9.5);
    Serial s2("Dexter", "Thriller", "E inteligent. E adorabil. E Dexter Morgan, criminalul in serie preferat al Americii, care isi petrece zilele rezolvand crime si noptile comitandu-le.", {45, 50, 55, 42}, 8.7);

    std::cout << "Test descriere Film: " << f1.getDescriere() << "\n";
    std::cout << "Test descriere Serial: " << s1.getDescriere() << "\n\n";

    Utilizator user1("Andrei", "Free");
    std::cout << "Utilizatorul " << user1.getNume() << " are initial planul " << user1.getPlan() << "\n\n";
    user1.setPlan("Premium");
    user1.adaugaFilm(f1);
    user1.adaugaFilm(f2);
    user1.adaugaFilm(f3);
    user1.adaugaSerial(s1);
    user1.adaugaSerial(s2);

    std::cout << user1;

    std::cout << "\nAfisare timp ramas inainte de vizionare:\n";
    user1.afiseazaTimpRamas();

    std::cout << "\nAndrei se uita la cateva episoade...\n";
    user1.uitaTeLaEpisod("Breaking Bad");
    user1.uitaTeLaEpisod("Breaking Bad");

    std::cout << "\nAfisare timp ramas dupa vizionare:\n";
    user1.afiseazaTimpRamas();

    std::cout << "\nStergem continut din lista:\n";
    user1.stergeDinLista("The Running Man");
    user1.stergeDinLista("Dexter");
    user1.stergeDinLista("Film Inexistent");

    std::cout << "\nProfil Actualizat:\n" << user1;

    std::cout << "\nCautare continut Horror:\n";
    user1.cautaGen("Horror");

    std::cout << "\nRecomandare:\n";
    user1.recomandaTop();

    std::cout << "\nTestare Memorie\n";
    Utilizator user2 = user1;
    Utilizator user3("Ana", "Free");
    user3 = user1;

    std::cout << "Test copie 1 (Nume): " << user2.getNume() << "\n";
    std::cout << "Test copie 2 (Plan): " << user3.getPlan() << "\n";

    return 0;
}
