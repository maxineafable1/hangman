#include <iostream>
#include <vector>
#include <set>
#include <random>

#ifndef HANGMAN_H
#define HANGMAN_H

class Hangman
{
private:
    std::vector<std::string> words;
    unsigned int guess_count;
    bool is_guessed;
    std::set<char> letters_guessed;

    const char get_input() const;
    const std::string& get_word() const;
    std::string render_word(std::string word);
    void display_word(const std::string& word) const;
    bool check_input(const std::string& word, char input) const;
    const char play_again() const;

public:
    Hangman();
    void start();
};

#endif