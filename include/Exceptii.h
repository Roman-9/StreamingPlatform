#pragma once
#include <string>
#include <exception>

class StreamingException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit StreamingException(std::string m);
    const char* what() const noexcept override;
};

class LimitaVarstaException : public StreamingException {
public:
    LimitaVarstaException(const std::string& titlu, int varstaMinima);
};

class TitluInexistentException : public StreamingException {
public:
    explicit TitluInexistentException(const std::string& titlu);
};

class NotaInvalidaException : public StreamingException {
public:
    explicit NotaInvalidaException(int nota);
};

class RecenzieFaraVizionareException : public StreamingException {
public:
    explicit RecenzieFaraVizionareException(const std::string& titlu);
};