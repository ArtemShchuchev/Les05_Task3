#include <iostream> // консоль - cout

// классы
class Figura
{
private:
    unsigned int qtySide;       // число сторон фигуры

protected:  // теперь к этим полям можно обращаться из производных классов
    bool figInit;               // false - объект не действителен
    bool rightFig;              // true - правильная фигура
    unsigned int* lenght;
    unsigned short* angle;

public:
    Figura()                    // конструктор по умолчанию
    {
        setQtySide(0);
    }
    Figura(int n)               // конструктор с параметрами
    {
        setQtySide(n);
    }
    ~Figura()   // деструктор, не уверен, что правильно освобождаю память?!
    {
        if (lenght) delete lenght;
        if (angle) delete angle;
    }

    virtual void setRight() { rightFig = true; }
    void setQtySide(int n)
    {
        if (n <= 0)
        {
            qtySide = 0;
            lenght = nullptr;
            angle = nullptr;
        }
        else
        {
            qtySide = static_cast<unsigned int>(n);
            lenght = new unsigned int[n](); // длины в кол-ве "n"
            angle = new unsigned short[n](); // углы в кол-ве "n"
        }
        figInit = false;
        setRight();
    }
    bool isAvailable() { return figInit; }
    bool isRight() { return rightFig; }
    unsigned int getQtySide() { return qtySide; }
    // не сущ. стророна фигуры имеет длину/угол = 0
    unsigned int getLen(int num)
    {
        if (num < 0 || num >= qtySide) return 0;
        else return lenght[num];
    }
    unsigned short getAng(int num)
    {
        if (num < 0 || num >= qtySide) return 0;
        else return angle[num];
    }
    virtual std::string getName() { return "Фигура:"; }
    virtual void printToCons()
    {
        using namespace std;
        cout << getName() << endl
            << (isRight() ? "Правильная" : "Не правильная") << endl
            << "Количество сторон: " << getQtySide() << endl << endl;
    }
};

class Triangle : public Figura
{
private:
    const std::string NAME_FIG = "Треугольник:";
protected:
public:
    // конструктор по умолчанию, запускает конструктор родителя с параметрами
    Triangle() : Figura(3) 
    { 
        rightFig = false; // при инициализации, фигура не правильная
    }
    bool checkTri()
    {
        return ((getAng(0) + getAng(1) + getAng(2)) == 180 && getQtySide() == 3);
    }
    void setRight() override
    { 
        rightFig = checkTri();
    }
    void setLengh(int a, int b, int c)
    {
        if (getQtySide() != 3 || a <= 0 || b <= 0 || c <= 0) figInit = false;
        else
        {
            lenght[0] = static_cast<unsigned int>(a);
            lenght[1] = static_cast<unsigned int>(b);
            lenght[2] = static_cast<unsigned int>(c);
            if (angle[0] && angle[1] && angle[2]) figInit = true;
            else figInit = false;
        }
        setRight();
    }
    void setAngle(short a, short b, short c)
    {
        if (getQtySide() != 3 || a <= 0 || b <= 0 || c <= 0) figInit = false;
        else
        {
            angle[0] = static_cast<unsigned short>(a);
            angle[1] = static_cast<unsigned short>(b);
            angle[2] = static_cast<unsigned short>(c);
            if (lenght[0] && lenght[1] && lenght[2]) figInit = true;
            else figInit = false;
        }
        setRight();
    }
    std::string getName() override {return "Треугольник:"; }
    void printToCons() override
    {
        using namespace std;
        cout << getName() << endl;
        if (isAvailable())
        {
            cout << (isRight() ? "Правильная" : "Не правильная") << endl
                << "Количество сторон: " << getQtySide() << endl
                << "Стороны: а=" << getLen(0) << " b=" << getLen(1)
                << " c=" << getLen(2) << std::endl
                << "Углы:    A=" << getAng(0) << " B=" << getAng(1)
                << " C=" << getAng(2) << std::endl;
        }
        else cout << "Фигура не определена!" << std::endl;
        cout << std::endl;
    }
};
class TriRight : public Triangle    // прямоугольный треугольник
{
private:
    const std::string NAME_FIG = "Прямоугольный треугольник:";
public:
    TriRight(int lenA, int lenB, int lenC, short angA, short angB)
    {
        setLengh(lenA, lenB, lenC);
        setAngle(angA, angB, 90);
    }
    void setRight() override
    {
        rightFig = (getAng(2) == 90 && checkTri());
    }
    std::string getName() override { return "Прямоугольный треугольник:"; }
};
class TriIsos : public Triangle    // равнобедренный треугольник
{
public:
    TriIsos(int lenA, int lenB, short angA, short angB)
    {
        setLengh(lenA, lenB, lenA);
        setAngle(angA, angB, angA);
    }
    void setRight() override
    {
        rightFig = (getLen(0) == getLen(2) && getAng(0) == getAng(2) && checkTri());
    }
    std::string getName() override { return "Равнобедренный треугольник:"; }
};
class TriEquil : public Triangle    // равносторонний треугольник
{
public:
    TriEquil(int lengh)
    {
        setLengh(lengh, lengh, lengh);
        setAngle(60, 60, 60);
    }
    void setRight() override
    {
        rightFig = (getLen(0) == getLen(1) && getLen(1) == getLen(2) &&
            getAng(0) == 60 && getAng(1) == 60 && getAng(2) == 60 && checkTri());
    }
    std::string getName() override { return "Равносторонний треугольник:"; }
};

class Quad : public Figura
{
private:
protected:
public:
    Quad()  // конструктор по умолчанию
    {
        setQtySide(4);  // создаю четырехугольник
    }
    bool checkQuad()
    {
        return ((getAng(0) + getAng(1) + getAng(2) + getAng(3)) == 360 && getQtySide() == 4);
    }
    void setRight() override
    {
        rightFig = checkQuad();
    }
    void setLengh(int a, int b, int c, int d)
    {
        if (getQtySide() != 4 || a <= 0 || b <= 0 || c <= 0 || d <= 0) figInit = false;
        else
        {
            lenght[0] = static_cast<unsigned int>(a);
            lenght[1] = static_cast<unsigned int>(b);
            lenght[2] = static_cast<unsigned int>(c);
            lenght[3] = static_cast<unsigned int>(d);
            if (angle[0] && angle[1] && angle[2] && angle[3]) figInit = true;
            else figInit = false;
        }
        setRight();
    }
    void setAngle(short a, short b, short c, short d)
    {
        if (getQtySide() != 4 || a <= 0 || b <= 0 || c <= 0 || d <= 0) figInit = false;
        else
        {
            angle[0] = static_cast<unsigned short>(a);
            angle[1] = static_cast<unsigned short>(b);
            angle[2] = static_cast<unsigned short>(c);
            angle[3] = static_cast<unsigned short>(d);
            if (lenght[0] && lenght[1] && lenght[2] && lenght[3]) figInit = true;
            else figInit = false;
        }
        setRight();
    }
    std::string getName() override { return "Четырехугольник:"; }
    void printToCons() override
    {
        using namespace std;
        cout << getName() << endl;
        if (isAvailable())
        {
            cout << (isRight() ? "Правильная" : "Не правильная") << endl
                << "Количество сторон: " << getQtySide() << endl
                << "Стороны: а=" << getLen(0) << " b=" << getLen(1)
                << " c=" << getLen(2) << " d=" << getLen(3) << std::endl
                << "Углы:    A=" << getAng(0) << " B=" << getAng(1)
                << " C=" << getAng(2) << " D=" << getAng(3) << std::endl;
        }
        else cout << "Фигура не определена!" << std::endl;
        cout << std::endl;
    }
};
class Rectangle : public Quad    // прямоугольник
{
public:
    Rectangle(int lenA, int lenB)
    {
        setLengh(lenA, lenB, lenA, lenB);
        setAngle(90, 90, 90, 90);
    }
    void setRight() override
    {
        // 4ый угол не проверяю, т.к. сумма углов = 360
        rightFig = (checkQuad() && getLen(0) == getLen(2) && getLen(1) == getLen(3) &&
            getAng(0) == 90 && getAng(1) == 90 && getAng(2) == 90);
    }
    std::string getName() override { return "Прямоугольник:"; }
};
class Square : public Quad    // квадрат
{
public:
    Square(int lengh)
    {
        setLengh(lengh, lengh, lengh, lengh);
        setAngle(90, 90, 90, 90);
    }
    void setRight() override
    {
        rightFig = (checkQuad() && getLen(0) == getLen(1) && getLen(1) == getLen(2) &&
            getLen(2) == getLen(3) && getAng(0) == 90 && getAng(1) == 90 && getAng(2) == 90);
    }
    std::string getName() override { return "Квадрат:"; }
};
class Parall : public Quad    // параллелограмм
{
public:
    Parall(int lenA, int lenB, short angA, short angB)
    {
        setLengh(lenA, lenB, lenA, lenB);
        setAngle(angA, angB, angA, angB);
    }
    void setRight() override
    {
        rightFig = (checkQuad() && getLen(0) == getLen(2) && getLen(1) == getLen(3) &&
            getAng(0) == getAng(2) && getAng(1) == getAng(3));
    }
    std::string getName() override { return "Параллелограмм:"; }
};
class Rhombus : public Quad    // ромб
{
public:
    Rhombus(int lengh, short angA, short angB)
    {
        setLengh(lengh, lengh, lengh, lengh);
        setAngle(angA, angB, angA, angB);
    }
    void setRight() override
    {
        rightFig = (checkQuad() && getLen(0) == getLen(1) && getLen(1) == getLen(2) && 
            getLen(2) == getLen(3) && getAng(0) == getAng(2) && getAng(1) == getAng(3));
    }
    std::string getName() override { return "Ромб:"; }
};

// программа
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Russian");   // задаём русский текст
    system("chcp 1251");            // настраиваем кодировку консоли
    std::system("cls");

    std::cout << "Задача 3. Фигуры. Методы\n"
              << "------------------------\n\n";

    Figura* fig = nullptr;    // указатель на объект типа Figura

    // фигура ----------------------
    Figura figura;
    fig = &figura;
    fig->printToCons();

    // треугольники ----------------------
    Triangle triangle;
    triangle.setLengh(10, 20, 30);
    triangle.setAngle(50, 60, 70);
    fig = &triangle;
    fig->printToCons();

    fig = new TriRight(10, 20, 30, 50, 60);
    fig->printToCons();

    fig = new TriRight(10, 20, 30, 50, 40);
    fig->printToCons();

    fig = new TriIsos(10, 20, 50, 60);
    fig->printToCons();

    fig = new TriEquil(30);
    fig->printToCons();

    fig = new TriEquil(-10);  // ошибка инициализации, длина стороны = -10 !!!
    fig->printToCons();

    // четырехугольники ----------------------
    Quad quad;
    quad.setLengh(10, 20, 30, 40);
    quad.setAngle(50, 60, 70, 80);
    fig = &quad;
    fig->printToCons();

    fig = new Rectangle(10, 20);
    fig->printToCons();

    fig = new Square(20);
    fig->printToCons();

    fig = new Parall(20, 30, 30, 40);;
    fig->printToCons();

    fig = new Rhombus(30, 30, 40);;
    fig->printToCons();


    return 0;
}

/*
Задача 3. Фигуры. Методы
В этом задании вы добавите в вашу иерархию классов больше функциональности.

Теперь ваши фигуры должны уметь немного больше:

выводить информацию о себе;
проверять правильность своих данных.
Ваши фигуры:

фигура (количество сторон равно 0);
треугольник (стороны и углы произвольные, количество сторон равно 3, сумма углов равна 180);
прямоугольный треугольник (угол C всегда равен 90);
равнобедренный треугольник (стороны a и c равны, углы A и C равны);
равносторонний треугольник (все стороны равны, все углы равны 60);
четырёхугольник (стороны и углы произвольные, количество сторон равно 4, сумма углов равна 360);
прямоугольник (стороны a,c и b,d попарно равны, все углы равны 90);
квадрат (все стороны равны, все углы равны 90);
параллелограмм (стороны a,c и b,d попарно равны, углы A,C и B,D попарно равны);
ромб (все стороны равны, углы A,C и B,D попарно равны).
Вы должны иметь возможность попросить фигуру вывести информацию о себе на консоль, а также узнать,
является ли фигура правильной, то есть выполняются ли условия, указанные в списке выше.

Информация о фигуре включает в себя:

название фигуры;
количество сторон;
длины её сторон, если есть;
величины её углов, если есть;
является ли фигура правильной.
Задача: спроектировать и реализовать классы, описывающие предметную область. Продемонструйте их работу:
создайте по одному экземпляру каждой фигуры и выведите на экран информацию о фигурах.

Реализуйте методы вывода на консоль и проверки правильности фигуры с помощью виртуальных функций
и переопределений. Используйте вызов базовой версии метода.

Ваша задача — работать с экземплярами дочерних классов полиморфно, то есть с помощью указателя на базовый класс.

Пример работы программы
Консоль
Фигура:
Правильная
Количество сторон: 0

Треугольник:
Правильная
Количество сторон: 3
Стороны: a=10 b=20 c=30
Углы: A=50 B=60 C=70

Прямоугольный треугольник:
Неправильная
Количество сторон: 3
Стороны: a=10 b=20 c=30
Углы: A=50 B=60 C=90

Прямоугольный треугольник:
Правильная
Количество сторон: 3
Стороны: a=10 b=20 c=30
Углы: A=50 B=40 C=90

Равнобедренный треугольник:
Неправильная
Количество сторон: 3
Стороны: a=10 b=20 c=10
Углы: A=50 B=60 C=50

Равносторонний треугольник:
Правильная
Количество сторон: 3
Стороны: a=30 b=30 c=30
Углы: A=60 B=60 C=60

Четырёхугольник:
Неправильная
Количество сторон: 4
Стороны: a=10 b=20 c=30 d=40
Углы: A=50 B=60 C=70 D=80

Прямоугольник:
Правильная
Количество сторон: 4
Стороны: a=10 b=20 c=10 d=20
Углы: A=90 B=90 C=90 D=90

Квадрат:
Правильная
Количество сторон: 4
Стороны: a=20 b=20 c=20 d=20
Углы: A=90 B=90 C=90 D=90

Параллелограмм:
Неправильная
Количество сторон: 4
Стороны: a=20 b=30 c=20 d=30
Углы: A=30 B=40 C=30 D=40

Ромб:
Неправильная
Количество сторон: 4
Стороны: a=30 b=30 c=30 d=30
Углы: A=30 B=40 C=30 D=40
*/