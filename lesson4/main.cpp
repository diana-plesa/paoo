#include <iostream>
#include <string>
using namespace std;

//item4
class Player 
{
public:
    Player(string name, int hp) : name(name), hp(hp), level(1) {}

    void show() {
        cout << name << " hp: " << hp << " level: " << level << endl;
    }

private:
    string name;
    int hp;
    int level;
};

class GameWorld 
{
public:
    GameWorld() { cout << "world loaded" << endl; }
};

GameWorld& world() 
{
    static GameWorld w;
    return w;
}

//item5
class Coin {};

class Enemy 
{
public:
    Enemy(string& name, int damage) : name(name), damage(damage) {}

private:
    string& name;
    const int damage;
};

//item6
class Uncopyable 
{
protected:
    Uncopyable() {}
    ~Uncopyable() {}
private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class SaveFile : private Uncopyable {};

class Boss {
public:
    Boss() {}
    Boss(const Boss&) = delete;
    Boss& operator=(const Boss&) = delete;
};

int main() {
    //item4
    int score = 0;
    cout << "score: " << score << endl;

    Player p("Hero", 100);
    p.show();

    world();

    //item5
    Coin c1;
    Coin c2(c1);
    c2 = c1;

    string n1 = "Goblin";
    string n2 = "Orc";
    Enemy e1(n1, 10);
    Enemy e2(n2, 20);
    Enemy e3(e1);
    // e1 = e2; // error

    //item6
    SaveFile s1;
    SaveFile s2;
    // SaveFile s3(s1); // error
    // s1 = s2; // error

    Boss b1;
    Boss b2;
    // Boss b3(b1); // error
    // b1 = b2; // error

    return 0;
}
