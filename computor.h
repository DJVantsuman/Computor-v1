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
    double a = 0;
    double b = 0;
    double c = 0;
    double discriminant;
    int degree = 0;
    double x1 = 0;
    double x2 = 0;

    struct member
    {
        int f = 1;
        double n;
        int degree;
    };

    void parser(std::string str);
    void parseMember(std::vector<std::string> members, int f);
    void culculate(std::vector<member> memberList);
    void print(int f);
    std::string getNumber(double n);
    double my_sqr(double number);

};

#endif // COMPUTOR_H
