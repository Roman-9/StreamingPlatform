#include "Exceptii.h"

StreamingException::StreamingException(std::string m) : mesaj(std::move(m)) {}

const char* StreamingException::what() const noexcept {
    return mesaj.c_str();
}

LimitaVarstaException::LimitaVarstaException(const std::string& titlu, int varstaMinima)
    : StreamingException("Acces blocat: '" + titlu + "' necesita varsta minima de " + std::to_string(varstaMinima) + " ani!") {}

TitluInexistentException::TitluInexistentException(const std::string& titlu)
    : StreamingException("Eroare: Titlul '" + titlu + "' nu a fost gasit!") {}

NotaInvalidaException::NotaInvalidaException(int nota)
    : StreamingException("Eroare: Nota " + std::to_string(nota) + " este invalida! Trebuie sa fie intre 1 si 10.") {}

RecenzieFaraVizionareException::RecenzieFaraVizionareException(const std::string& titlu)
    : StreamingException("Eroare: Nu poti acorda o nota titlului '" + titlu + "' fara sa il vizionezi!") {}