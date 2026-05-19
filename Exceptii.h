#pragma once
#include <exception>
#include <string>

class StreamingException : public std::exception {
protected:
    std::string mesaj;
public:
    explicit StreamingException(std::string m);
    [[nodiscard]] const char* what() const noexcept override;
};

class LimitaVarstaException : public StreamingException {
public:
    explicit LimitaVarstaException(const std::string& titlu, int varstaMinima);
};

class TitluInexistentException : public StreamingException {
public:
    explicit TitluInexistentException(const std::string& titlu);
};