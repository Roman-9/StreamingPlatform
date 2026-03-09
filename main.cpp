#include <iostream>
#include <string>
#include <vector>

class Content {
private:
    std::string title;
    int durata;
    std::string descriere;

public:
    explicit Content(const std::string &title = "Fara titlu", int durata = 0,
                     const std::string &descriere = "Fara descriere")
        : title(title),
          durata(durata),
          descriere(descriere) {
    }

    [[nodiscard]] const std::string& getTitle() const {
        return title;
    }

    [[nodiscard]] int getDurata() const {
        return durata;
    }

    [[nodiscard]] const std::string& getDescriere() const {
        return descriere;
    }

    friend std::ostream &operator<<(std::ostream &os, const Content &content) {
        os << content.title << " are o durata de " << content.durata << "\n";
        os << "Descriere: " << content.descriere << "\n";
        return os;
    }
};

class Watchlist {
private:
    std::vector<Content> filme;

public:
    Watchlist() = default;

    //Destructor
    ~Watchlist() {
        filme.clear();
    }

    //Constructorul de copiere
    Watchlist(const Watchlist &other) : filme(other.filme) {
        std::cout << "Constructor de copiere apelat.\n";
    }

    //Constructorul de atribuire
    Watchlist &operator=(const Watchlist &other) {
        if (this != &other) {
            filme = other.filme;
            std::cout << "Operator de atribuire apelat.\n";
        }
        return *this;
    }

    void adaugaFilm(const Content &filmNou) {
        filme.push_back(filmNou);
    }

    bool stergeFilmDupaTitlu(const std::string &titluCautat) {
        for (auto i = filme.begin(); i != filme.end(); ++i) {
            if (i->getTitle() == titluCautat) {
                filme.erase(i);
                std::cout << "Filmul '" << titluCautat << "' a fost sters cu succes.\n";
                return true;
            }
        }
        std::cout << "Filmul '" << titluCautat << "' nu a fost gasit in lista.\n";
        return false;
    }

    [[nodiscard]] int calculeazaDurataTotala() const {
        int durataTotala = 0;
        for (const auto& film : filme) {
            durataTotala += film.getDurata();
        }
        return durataTotala;
    }

    friend std::ostream &operator<<(std::ostream &os, const Watchlist &wl) {
        for (size_t i = 0; i < wl.filme.size(); ++i) {
            os << "Film " << i + 1 << ": " << wl.filme[i] ;
        }
        os << "Numar de filme: " << wl.filme.size() << "\n";
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

    void adaugaFilmInLista(const Content &film) {
        watchlist.adaugaFilm(film);
    }

    void afiseazaTimp() const {
        std::cout << nume << " are nevoie de " << watchlist.calculeazaDurataTotala() <<
                " minute pentru a vedea toata lista.\n";
    }

    void stergeDinLista(const std::string &titlu) {
        watchlist.stergeFilmDupaTitlu(titlu);
    }

    friend std::ostream &operator<<(std::ostream &os, const Utilizator &user) {
        os << "Utilizator: " << user.nume << " are planul tarifar: " << user.plan << "\n";
        os << "Lista de filme este: \n" << user.watchlist << "\n";
        return os;
    }
};

int main() {
    Content film1("Scream 7", 114,
                  "When a new Ghostface killer emerges in the town where Sidney Prescott has built a new life, her darkest fears are realized as her daughter becomes the next target.");
    Content film2("The Running Man", 133,
                  "A man joins a game show in which contestants, allowed to flee anywhere in the world, are pursued by hunters hired to kill them.");
    Content film3("F1: The Movie", 155,
                  "A Formula One driver comes out of retirement to mentor and team up with a younger driver.");
    std::cout << "Film 1: " << film1.getTitle() << ", Durata: " << film1.getDurata() << ", Descriere: " << film1.
            getDescriere() << "\n";
    Utilizator user1("Andrei", "Free");
    std::cout << "Nume utilizator: " << user1.getNume() << "\n";
    std::cout << "\nProfil initial: \n";
    std::cout << user1;
    user1.setPlan("Premium");
    user1.adaugaFilmInLista(film1);
    user1.adaugaFilmInLista(film2);
    user1.adaugaFilmInLista(film3);

    std::cout << "Profil dupa modificari \n";
    std::cout << user1;
    user1.afiseazaTimp();

    std::cout << "\nAndrei s-a uitat la The Running Man si il sterge din lista...\n";
    user1.stergeDinLista("The Running Man");
    std::cout << "\nAndrei vrea sa stearga un film care nu apare in lista...\n";
    user1.stergeDinLista("Scream 6");
    std::cout << "\nProfil dupa stergere \n";
    std::cout << user1 << "\n";
    user1.afiseazaTimp();

    std::cout << "\nTestare constructorul de copiere \n";
    Utilizator user2 = user1;
    user2.setPlan("Basic");
    std::cout << user1.getPlan() << "\n";
    std::cout << user2.getPlan() << "\n";

    std::cout << "\nTestare constructorul de atribuire \n";
    Utilizator user3("Ana", "Free");
    user3 = user1;
    std::cout << user3 << "\n";
    return 0;
}
