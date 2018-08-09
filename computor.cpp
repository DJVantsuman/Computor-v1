#include "computor.h"
#include "iostream"

Computor::Computor() { }

Computor::~Computor() { }

Computor &Computor::Instance()
{
    static Computor computor;
    return computor;
}

void Computor::start(std::string equation)
{
    try{
        parser(equation);
    }
    catch (std::string e)
    {
        std::cout << "EXEPTION: " << e << std::endl;
    }

}

void Computor::parser(std::string str)
{
    std::cout << str << std::endl;
    std::vector<std::string> members;
    std::string var;
    int t = 0;
    for(int i = 0; i <= str.length(); i++) {
        if((str[i] != '+' && str[i] != '-' && str[i] != '\0') ||
                ((members.size() == 0 || members.size() == t) && var.size() == 0))
        {
            if (str[i] == '=')
            {
                members.push_back(var);
                var.clear();
                t = members.size();
                continue;
            }
            if (str[i] != ' ')
                var += str[i];
        }
        else if (var.length() > 0)
        {
            members.push_back(var);
            var.clear();
            var += str[i];
        }
    }
    parseMember(members, t);
}

void Computor::parseMember(std::vector<std::string> members, int t)
{
    std::vector<member> memberList;
    std::string reducedForm;
    std::cmatch result;
    std::regex reg("([\\+\\-])?"
                    "((\\d+)|(\\d+\\.\\d+))?"
                    "(\\*)?"
                    "(X\\^)"
                    "(\\d+)");
    for(int i = 0; i < members.size(); i++) {
        if (std::regex_match(members[i].c_str(), result, reg))
        {
            member var;
            std::string s;
            if (result[2] == "")
            {
                s = (std::string)result[1] + std::to_string(1);
                var.f = 2;
            }
            else
                s = (std::string)result[1] + (std::string)result[2];
            if(s != "")
                var.n = std::stod(s);
            else
                var.n = 1;
            var.degree = std::stoi(result[7]);
            if(i >= t)
                var.n *= -1;
            memberList.push_back(var);
        }
        else if (members[i] != "0")
            throw "Syntax error in \"" + members[i] + "\"";
    }
    for(int i = 0; i < memberList.size(); i++) {
        if(memberList[i].f == 1)
        {
            std::string sing;
            if(memberList[i].n > 0 && i > 0)
                sing = (" + " + getNumber(memberList[i].n) + " * ");
            else if (memberList[i].n < 0 && i > 0)
                sing = (" - " + getNumber(memberList[i].n * -1) + " * ");
            else
                sing = (getNumber(memberList[i].n) + " * ");
            reducedForm += sing;
        }
        if(memberList[i].f == 2 && memberList[i].n < 0)
            reducedForm += (" - X^" + std::to_string(memberList[i].degree));
        else if (memberList[i].f == 2 && memberList[i].n > 0)
            reducedForm += (" + X^" + std::to_string(memberList[i].degree));
        else
            reducedForm += ("X^" + std::to_string(memberList[i].degree));
    }
    std::cout << "\nReduced form: " << reducedForm << " = 0" <<std::endl;
    culculate(memberList);
}

void Computor::culculate(std::vector<member> memberList)
{
    degree = memberList[0].degree;
    for(int i = 0; i < memberList.size(); i++) {
        if(memberList[i].degree > degree)
            degree = memberList[i].degree;
        if(memberList[i].degree == 0)
            c += memberList[i].n;
        else if(memberList[i].degree == 1)
            b += memberList[i].n;
        else if(memberList[i].degree == 2)
            a += memberList[i].n;
        else {
            std::cout << "Polynomial degree: " << degree << std::endl;
            std::cout << "The polynomial degree is stricly greater than 2, I can't solve." << std::endl;
            exit(1);
        }
    }
    discriminant = (b * b) - 4 * a * c;
    std::cout << "Polynomial degree: " << degree << std::endl;
    if(discriminant > 0 && degree == 2)
    {
        std::cout << "Discriminant is strictly positive, the two solutions are: " << std::endl;
        x1 = (-b + my_sqr(discriminant)) / (2 * a);
        x2 = (-b - my_sqr(discriminant)) / (2 * a);
        std::cout << x1 << std::endl;
        std::cout << x2 << std::endl;
        print(1);
    }
    else if(discriminant == 0 && degree == 2)
    {
        std::cout << "The solution is: " << std::endl;
        x1 = x2 = -b /(2 * a);
        std::cout << x1 << std::endl;
        print(2);
    }
    else if(discriminant > 0 && degree == 1)
    {
        std::cout << "The solution is: " << std::endl;
        if(c != 0)
        {
            x1 = -(c/b);
            std::cout << x1 << std::endl;
            print(3);
        }
        else
        {
            x1 = 0;
            std::cout << x1 << std::endl;
        }
    }
    else if(degree == 0 || discriminant < 0)
        std::cout << "The equation is not solved." << std::endl;
}

std::string Computor::getNumber(double n)
{
    std::string var = std::to_string(n), s, result;
    int f = 0;
    int i = 0;
    for(; i < var.size(); i++)
        if(var[i] != '.' )
            result += var[i];
        else break;
    for(; i < var.size(); i++)
    {
        if(var[i] == '.' && var[i + 1] != '0')
        {
            result += var[i];
            continue;
        }
        else if(var[i] == '.')
            break;
        if(var[i] == '0')
            break;
        result += var[i];
    }
    return result;
}

void Computor::print(int f)
{
    if(f == 1)
    {
        std::cout << "\nD = b^2 - 4ac = " << (b * b) << " - " << 4 * a * c << " = " << discriminant << std::endl;
        std::cout << "            ____________" << std::endl;
        std::cout << "     -b + \\/ b^2 - 4ac"   << std::endl;
        std::cout << "X1 = ------------------- = " << x1 << std::endl;
        std::cout << "            2a" << std::endl;
        std::cout << "            ____________" << std::endl;
        std::cout << "     -b - \\/ b^2 - 4ac"   << std::endl;
        std::cout << "X2 = ------------------- = " << x2 << std::endl;
        std::cout << "            2a\n" << std::endl;

    }
    else if(f == 2)
    {
        std::cout << "\n\nD = b^2 - 4ac = " << (b * b) << " - " << 4 * a * c << " = " << discriminant << std::endl;
        std::cout << "\n        -b"  << std::endl;
        std::cout << "X1,2 = ---- = " << x1 << std::endl;
        std::cout << "        2a\n" << std::endl;
    }
    else if(f == 3)
    {
        std::cout << "\n       c"  << std::endl;
        std::cout << "X = - --- = " << x1 << std::endl;
        std::cout << "       b\n" << std::endl;
    }
}

double Computor::my_sqr(double number){
    double pressision = 0.0000001;
    double n = number;

    while ((n - number / n) > pressision)
        n = (n + number / n) / 2;
    return n;
}
