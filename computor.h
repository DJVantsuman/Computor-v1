#ifndef COMPUTOR_H
#define COMPUTOR_H

#include <string>
#include <regex>
#include <exception>


class Computor
{
public:
    Computor();
    Computor(Computor const &src) = delete;
    Computor &operator=(Computor const &rhs) = delete;
    ~Computor();

public:
    static Computor &Instance();
    void start(std::string equation);

private:
    int a = 0;
    int b = 0;
    int c = 0;
    int discriminant;
    int power = 0;

    struct member
    {
        int f = 1;
        float n;
        int power;
    };

    void parser(std::string str);
    void parseMember(std::vector<std::string> members, int f);
    void culculate(std::vector<member> memberList);
};

#endif // COMPUTOR_H
