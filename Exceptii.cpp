#include "Exceptii.h"

StreamingException::StreamingException(std::string m) : mesaj(std::move(m)) {}

const char* StreamingException::what() const noexcept {
    return mesaj.c_str();
}

LimitaVarstaException::LimitaVarstaException(const std::string& titlu, int varstaMinima)
    : StreamingException("Acces blocat: '" + titlu + "' necesita varsta minima de " + std::to_string(varstaMinima) + " ani!") {}

TitluInexistentException::TitluInexistentException(const std::string& titlu)
    : StreamingException("Eroare: Titlul '" + titlu + "' nu a fost gasit!") {}