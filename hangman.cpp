#include "hangman.h"

Hangman::Hangman()
{
    words = {"honda", "toyota", "mazda", "bmw", "porsche"};
    is_guessed = false;
    guess_count = 0;
}

const char Hangman::get_input() const
{
    std::string input;
    do
    {
        std::cout << "Enter a letter: ";
        std::getline(std::cin, input);
    } while (input.size() != 1);

    return input[0];
}

const std::string& Hangman::get_word() const
{
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(0, words.size() - 1);

    std::size_t index = dist(gen);
    const std::string& word = words[index];
    return word;
}

std::string Hangman::render_word(std::string word)
{
    for (size_t i{}; i < word.size(); i++)
    {
        word[i] = '_';
    }
    return word;
}

bool Hangman::check_input(const std::string& word, char input) const
{
    return word.find(input) != std::string::npos;
}

const char Hangman::play_again() const
{
    char response;
    std::cout << "Play again (y/n): ";
    std::cin >> response;
    response = tolower(response);
    return response;
}

void Hangman::display_word(const std::string& word) const
{
    // display either letter that is guessed or underscore if not
    for (size_t i{}; i < word.size(); i++)
    {
        std::cout << (word[i] == '_' ? '_' : word[i]) << "  ";
    }
    std::cout << '\n';
}

void Hangman::start()
{ 
    std::string word;
    // this will give you the underscore display of the word
    std::string blank_word;
    
    char response;
    do
    {
        std::cout << "Guess the word" << '\n'; 
        word = get_word();
        blank_word = render_word(word);
        display_word(blank_word);
        
        guess_count = 0;
        is_guessed = false;
        letters_guessed.clear();

        while (!is_guessed)
        {
            char input = get_input();
            if (check_input(word, input))
            {
                if (letters_guessed.count(input))
                    std::cout << input << " is already guessed" << '\n';
                else
                {
                    guess_count++;
                    // count for guessed letters
                    int c{};
                    letters_guessed.insert(input);

                    for (size_t i{}; i < blank_word.size(); i++)
                    {
                        // this changes the underscore from display if a letter is in the word
                        if (word[i] == input)
                            blank_word[i] = input;
                        
                        if (blank_word[i] != '_')
                            c++;
                    }
                    // this check if there's no more letter to guess
                    if (c == blank_word.size())
                        is_guessed = true;
                }
            }
            else
            {
                std::cout << input << " is not in the word" << '\n';
                guess_count++;
            }
            display_word(blank_word);
        }
        std::cout << "You guessed the word in " << guess_count << " attempts" << '\n';
        response = play_again();
    } while (response == 'y');
    
    std::cout << "thanks for playing" << '\n';
}