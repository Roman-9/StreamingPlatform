#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "Exceptii.h"

template <typename T>
class ListaGenerica {
private:
    std::vector<std::shared_ptr<T>> lista;

public:
    ListaGenerica() = default;

    ListaGenerica(const ListaGenerica& other) {
        for (const auto& elem : other.lista) {
            if (elem) { 
                lista.push_back(elem->clone()); 
            }
        }
    }

    void swap(ListaGenerica& other) noexcept {
        std::swap(lista, other.lista);
    }

    ListaGenerica& operator=(ListaGenerica other) {
        this->swap(other);
        return *this;
    }

    ~ListaGenerica() {
        lista.clear();
    }

    void adauga(const std::shared_ptr<T>& elem) {
        if (elem) lista.push_back(elem);
    }

    template <typename Predicat>
    void stergeDaca(Predicat conditie) {
        for (auto it = lista.begin(); it != lista.end(); ++it) {
            if (conditie(*it)) {
                lista.erase(it);
                return;
            }
        }
        throw StreamingException("Elementul cautat nu a fost gasit in lista!");
    }

    std::shared_ptr<T> operator[](size_t index) const {
        if (index < lista.size()) return lista[index];
        throw std::out_of_range("Index invalid in ListaGenerica!");
    }

    // cppcheck-suppress unusedFunction
    size_t size() const { return lista.size(); }

    const std::vector<std::shared_ptr<T>>& getLista() const { return lista; }

    // cppcheck-suppress unusedFunction
    friend std::ostream& operator<<(std::ostream& os, const ListaGenerica& wl) {
        if (wl.lista.empty()) { os << "Lista este goala.\n"; return os; }
        for (const auto& elem : wl.lista) os << *elem << "\n";
        return os;
    }
};

template <typename T, typename Predicat>
std::shared_ptr<T> gasesteDaca(const ListaGenerica<T>& colectie, Predicat conditie) {
    for (const auto& elem : colectie.getLista()) {
        if (conditie(elem)) {
            return elem;
        }
    }
    return nullptr;
}
