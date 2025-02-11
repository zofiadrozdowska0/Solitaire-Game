#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<ctime>
#include<iomanip>
#include<string>

using namespace std;

int gameState = 0; // 0 - nierozpoczeta, 1 - w trakcie

class Card
{
private:
    string value; 
    string colour;
    bool faceUp = true;
    bool isCovered = false; 
    string lowerValueVector;
    string lowerColourVector[2];
    string lowerValueStack;
public:
    string getValue()
    {
        return value;
    }
    string getColour()
    {
        return colour;
    }
    void setValue(string newValue)
    {
        value = newValue;
    }
    void setColour(string newColour)
    {
        colour = newColour;
    }
    string getFaceValue()
    {
        if (faceUp == true)
        {
            return value;
        }
        else
        {
            return "==";
        }
    }
    string getFaceColour()
    {
        if (faceUp == true)
        {
            return colour;
        }
        else
        {
            return "=";
        }
    }
    bool getFace()
    {
        return faceUp;
    }
    void setFace(bool maybe)
    {
        faceUp = maybe;
    }
    void setCover(bool x)
    {
        isCovered = x;
    }
    bool getCover()
    {
        return isCovered;
    }
    string getLowerValueVector()
    {
        return lowerValueVector;
    }
    string getLowerColourVector(int x)
    {
        return lowerColourVector[x];
    }
    void setLowerValueVector(string newValue)
    {
        lowerValueVector = newValue;
    }
    void setLowerColourVector(string newColour1, string newColour2)
    {
        lowerColourVector[0] = newColour1;
        lowerColourVector[1] = newColour2;
    }
    string getLowerValueStack()
    {
        return lowerValueStack;
    }
    void setLowerValueStack(string newValue)
    {
        lowerValueStack = newValue;
    }
    void setLowerCardVector()
    {
        string values[] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
        if (colour == "h" || colour == "d")
        {
            setLowerColourVector("c", "s");
        }
        else if (colour == "c" || colour == "s")
        {
            setLowerColourVector("h", "d");
        }
        for (int i = 1; i < 13; i++)
        {
            if (value == values[12])
            {
                setLowerValueVector(" ");
            }
            else if (value == values[i])
            {
                setLowerValueVector(values[i + 1]);
            }
        }
    }
    void setLowerCardStack()
    {
        string values[] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
        for (int i = 0; i < 13; i++)
        {

            if (value == values[0])
            {
                setLowerValueStack("X");
            }
            else if (value == values[i] && i != 0)
            {
                setLowerValueStack(values[i - 1]);
            }
        }

    }
};

class Move
{
private:
    string move1, move3;
    Card move2;
    bool isCorrect = true, isPossible = true;
    int source = 0, target = 1;
public:
    string setM1(string move)
    {
        move1 = move;
        return move1;
    }
    Card setM2(string move)
    {
        if (move.length() == 2)
        {
            move2.setValue(move.substr(0, 1));
            move2.setColour(move.substr(1, 1));
        }
        else if (move.length() == 3)
        {
            move2.setValue(move.substr(0, 2));
            move2.setColour(move.substr(2, 1));
        }
        else
        {
            isCorrect = false;
        }
        return move2;
    }
    string setM3(string move)
    {
        move3 = move;
        return move3;
    }
    string getM1()
    {
        return move1;
    }
    Card getM2()
    {
        return move2;
    }
    string getM3()
    {
        return move3;
    }
    void setCorrectness(bool x)
    {
        isCorrect = x;
    }
    bool getCorrectness()
    {
        return isCorrect;
    }
    void setPossibility(bool x)
    {
        isPossible = x;
    }
    bool getPossibility()
    {
        return isPossible;
    }
    void setSource(int a)
    {
        source = a;
    }
    void setTarget(int z)
    {
        target = z;
    }
    int getSource()
    {
        return source;
    }
    int getTarget()
    {
        return target;
    }
};

void rules()
{
    cout << "Zasady gry:" << endl;
    cout << "1. Oznaczenia kart: numer (2-10, J, Q, K, A), kolor (s, c, h, d)." << endl;
    cout << "2. W celu podania ruchu nalezy wpisac skad pochodza karty (0-11), jaka to karta i gdzie ja kladziemy (1-11) " << endl;
    cout << "  -> przykladowo: 0 Kd 1 (rozdzielone spacja)" << endl;
    cout << "3. Czarne karty (s,c) mozna klasc wylacznie na czerwone (h,d) i odwrotnie." << endl;
    cout << "4. Do pustej kolumny mozna przelozyc tylko krola." << endl;
    cout << "5. Aby wygrac nalezy ulozyc wszystkie karty w stosach (pola 8-11) w tym samym kolorze, w odpowiedniej kolejnosci (od A do K)." << endl;
}

void board(vector< vector<Card>>& v, vector<stack<Card>>& s, stack<Card> toPick) //tablica
{
    long pickSize = toPick.size();
    string tempPick[3];
    if (!toPick.empty()) {
        for (int i = 0; i < pickSize; i++) {
            tempPick[i] = toPick.top().getFaceValue() + toPick.top().getFaceColour();
            toPick.pop();
        }
    }

    cout << "        0                               8     9     10     11   " << endl;
    cout << " -------------------------------------------------------------- " << endl;
    cout << "     " << setw(2) << tempPick[2] << " " << setw(2) << tempPick[1] << " " << setw(2) << tempPick[0] << "                         " << setw(2) << s[0].top().getValue() << setw(1) << s[0].top().getColour() << "   " << setw(2) << s[1].top().getValue() << setw(1) << s[1].top().getColour() << "    " << setw(2) << s[2].top().getValue() << setw(1) << s[2].top().getColour() << "    " << setw(2) << s[3].top().getValue() << setw(1) << s[3].top().getColour() << "   " << endl;
    cout << " -------------------------------------------------------------- " << endl;
    for (int i = 0; i < 18; i++)
    {
        cout << "|  " << setw(2) << v[0][i].getFaceValue() << setw(1) << v[0][i].getFaceColour() << "   |  " << setw(2) << v[1][i].getFaceValue() << setw(1) << v[1][i].getFaceColour() << "   |  " << setw(2) << v[2][i].getFaceValue() << setw(1) << v[2][i].getFaceColour() << "   |  " << setw(2) << v[3][i].getFaceValue() << setw(1) << v[3][i].getFaceColour() << "   |  " << setw(2) << v[4][i].getFaceValue() << setw(1) << v[4][i].getFaceColour() << "   |  " << setw(2) << v[5][i].getFaceValue() << setw(1) << v[5][i].getFaceColour() << "   |  " << setw(2) << v[6][i].getFaceValue() << setw(1) << v[6][i].getFaceColour() << "   | " << endl;
    }
    cout << "    1        2        3        4        5        6        7     " << endl;
}

void fillDeck(Card deck[52]) //talia kart z uporzadkowanymi wartosciami i kolorami
{
    string value[] = { "A","2","3","4","5","6","7","8","9","10","J","Q","K" };
    string colour[] = { "h","c","d","s" };
    for (int i = 0; i < 52; i++)
    {
        deck[i].setValue(value[i % 13]);
        deck[i].setColour(colour[(i / 13)]);
    }
}

void randomNumbers(int numbers[52]) //tablica losowo ułożonych liczb 0-51 bez powtórzeń, zrobiona do sterowania tablicą deck
{
    srand(time(NULL));
    for (int i = 0; i < 52; i++) {
        numbers[i] = i;
    }

    int j = 0;
    int temp = 0;

    for (int i = 0; i < 52; i++) {
        j = (rand() % 51);
        temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }
}

void arrangeCards(int numbers[52], Card deck[52], vector< vector<Card>>& v, vector<stack<Card>>& s, queue<Card>& q) //rozmieszczenie kart
{
    randomNumbers(numbers);     //pomieszanie liczb 0-51
    int i = 0;
    for (int k = 0; k < 7; k++)
    {
        for (int l = k; l < 7; l++)
        {
            v[l][k] = deck[numbers[i]];
            i++;
        }
    }
    while (i < 52)
    {
        q.push(deck[numbers[i]]);
        i++;
    }
    Card x;
    x.setValue("X");
    x.setColour("X"); //żeby bylo widoczne na planszy w trakcie gry gdzie są stosy zanim zostaną wypełnione kartami
    s[0].push(x);
    s[1].push(x);
    s[2].push(x);
    s[3].push(x);
}

void setFacing(vector< vector<Card>>& v)  //ustawienie zakrytych kart na starcie
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = i + 1; j < 7; j++)
        {
            v[j][i].setFace(false);
        }
    }
}

void emptyPlaces(vector< vector<Card>>& v) //puste miejsca w wektorze
{
    Card empty;
    empty.setValue(" ");
    empty.setColour(" ");
    for (int i = 7; i < 18; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            v[j][i] = empty;
        }
    }
    for (int i = 1; i < 7; i++)
    {
        for (int j = 0; j < i; j++)
        {
            v[j][i] = empty;
        }
    }
}

void clear(vector< vector<Card>>& v, vector<stack<Card>>& s, queue<Card>& q1, queue<Card>& q2, stack<Card>& toPick) //czyszczenie w celu zrestartowania
{
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            v[j][i].setFace(true);
        }
    }
    while (!s[0].empty())
    {
        s[0].pop();
    }
    while (!s[1].empty())
    {
        s[1].pop();
    }
    while (!s[2].empty())
    {
        s[2].pop();
    }
    while (!s[3].empty())
    {
        s[3].pop();
    }
    while (!q1.empty())
    {
        q1.pop();
    }
    while (!q2.empty())
    {
        q2.pop();
    }
    while (!toPick.empty())
    {
        toPick.pop();
    }
}

int searchVector(vector< vector<Card>>& v, int x) //szukanie najwyższego miejsca bez karty w wektorze w danej kolumnie
{
    for (int i = 0; i < 18; i++)
    {
        if (v[x][i].getValue() == " ")
        {
            return i;
        }
    }
    return 18;
}

bool isCardInVector(Move m, vector< vector<Card>>& v) //szukanie karty w wektorze w danej kolumnie
{
    for (int i = 0; i < 18; i++)
    {
        if (v[m.getSource() - 1][i].getValue() == m.getM2().getValue() && v[m.getSource() - 1][i].getColour() == m.getM2().getColour())
        {
            if (v[m.getSource() - 1][i].getFace() == true) //czy karta o wartosci m2 znajduje sie w wektorze a jesli tak to czy jest odkryta
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

int findCardRow(Move m, vector< vector<Card>>& v) //zwraca numer wiersza w ktorym znajduje sie karta przekładana
{
    for (int i = 0; i < 18; i++)
    {
        if (v[m.getSource() - 1][i].getValue() == m.getM2().getValue() && v[m.getSource() - 1][i].getColour() == m.getM2().getColour())
        {
            return i;
        }
    }
    return 20;
}

void setCovers(Move* m, vector< vector<Card>>& v) //zakrywa karty do przepisania przy przekładaniu z wektora do wektora
{
    for (int i = findCardRow(*m, v); i < searchVector(v, m->getSource() - 1); i++)
    {
        v[m->getSource() - 1][i].setCover(true);
    }
}

void makeMove(Move m, vector< vector<Card>>& v, vector<stack<Card>>& s, stack<Card>& toPick)
{
    if (m.getSource() > 0 && m.getSource() < 8) //przenoszenie kart z wektora
    {
        if (m.getTarget() > 0 && m.getTarget() < 8)//do wektora 
        {
            int xs = findCardRow(m, v);
            int xt = searchVector(v, m.getTarget() - 1);
            int ys = m.getSource() - 1;
            int yt = m.getTarget() - 1;
            if (xs != 0)
            {
                v[ys][xs - 1].setFace(true);
            }
            while (v[ys][xs].getCover() == true)
            {
                v[yt][xt].setValue(v[ys][xs].getValue());
                v[yt][xt].setColour(v[ys][xs].getColour());
                v[ys][xs].setValue(" ");
                v[ys][xs].setColour(" ");
                v[yt][xt].setCover(false);
                v[ys][xs].setCover(false);
                xt++;
                xs++;
            }
        }
        else if (m.getTarget() > 7) //do stosu 
        {
            int t = m.getTarget() - 8;
            int so = m.getSource() - 1;
            int x = findCardRow(m, v);
            Card temp;
            temp.setValue(m.getM2().getValue());
            temp.setColour(m.getM2().getColour());
            s[t].push(temp);
            v[so][x].setValue(" ");
            v[so][x].setColour(" ");
            v[so][x].setCover(false);
            if (x != 0)
            {
                v[so][x - 1].setFace(true);
            }
        }
    }
    else if (m.getSource() == 0) //przenoszenie kart z kolejki
    {
        if (m.getTarget() > 0 && m.getTarget() < 8) //do wektora 
        {
            int yt = m.getTarget() - 1;
            int xt = searchVector(v, yt);
            v[yt][xt].setValue(toPick.top().getValue());
            v[yt][xt].setColour(toPick.top().getColour());
            toPick.pop();
        }
        else if (m.getTarget() > 7) //do stosu 
        {
            Card moving;
            moving.setValue(toPick.top().getValue());
            moving.setColour(toPick.top().getColour());
            int t = m.getTarget() - 8;
            s[t].push(moving);
            toPick.pop();
        }
    }
    else //przenoszenie kart ze stosu
    {
        if (m.getTarget() > 0 && m.getTarget() < 8) //do wektora
        {
            int so = m.getSource() - 8;
            int t = m.getTarget() - 1;
            int x = searchVector(v, t);
            v[t][x].setValue(s[so].top().getValue());
            v[t][x].setColour(s[so].top().getColour());
            s[so].pop();
        }
    }
}

void setPossibility(Move* m, vector< vector<Card>>& v, vector<stack<Card>>& s, stack<Card>& toPick)
{
    Card temp;
    temp.setValue(m->getM2().getValue());
    temp.setColour(m->getM2().getColour());
    temp.setLowerCardVector();
    temp.setLowerCardStack();
    if (m->getSource() > 0 && m->getSource() < 8) //z wektora
    {
        if (isCardInVector(*m, v) == false) //gdy nie istnieje
        {
            m->setPossibility(false);
        }
        else if (m->getTarget() > 0 && m->getTarget() < 8) //do wektora
        {
            int tv = m->getTarget() - 1;
            int firstEmpty = searchVector(v, tv);
            if (firstEmpty != 0)
            {
                if (v[tv][firstEmpty - 1].getValue() != temp.getLowerValueVector())
                {
                    m->setPossibility(false);
                }
                else if (v[tv][firstEmpty - 1].getColour() != temp.getLowerColourVector(0) && v[tv][firstEmpty - 1].getColour() != temp.getLowerColourVector(1))
                {
                    m->setPossibility(false);
                }
                else
                {
                    m->setPossibility(true);
                }
            }    
            else if (firstEmpty==0 && temp.getValue() != "K")
            {
                m->setPossibility(false);
            }
            else
            {
                m->setPossibility(true);
            }
        }
        else if (m->getTarget() > 7) //do stosu
        {
            int row = findCardRow(*m, v);
            int ts = m->getTarget() - 8;
            int sv = m->getSource() - 1;
            if (s[ts].top().getValue() != temp.getLowerValueStack())
            {
                m->setPossibility(false);
            }
            else if (s[ts].top().getColour() != temp.getColour() && s[ts].top().getValue() != "X")
            {
                m->setPossibility(false);
            }
            else if (row < 17 && v[sv][row + 1].getValue() != " ")
            {
                m->setPossibility(false);
            }
            else
            {
                m->setPossibility(true);
            }
        } 
    }
    else if (m->getSource() == 0) //z kolejki
    {
        if (toPick.top().getValue() != temp.getValue() || toPick.top().getColour() != temp.getColour()) //gdy nie istnieje
        {
            m->setPossibility(false);
        }
        else if (m->getTarget() > 0 && m->getTarget() < 8) //do wektora
        {
            int tv = m->getTarget() - 1;
            int firstEmpty = searchVector(v, tv);
            if (firstEmpty != 0)
            {
                if (v[tv][firstEmpty - 1].getValue() != temp.getLowerValueVector())
                {
                    m->setPossibility(false);
                }
                else if (v[tv][firstEmpty - 1].getColour() != temp.getLowerColourVector(0) && v[tv][firstEmpty - 1].getColour() != temp.getLowerColourVector(1))
                {
                    m->setPossibility(false);
                }
                else
                {
                    m->setPossibility(true);
                }
            }
            else if (firstEmpty == 0 && temp.getValue() != "K")
            {
                m->setPossibility(false);
            }
            else
            {
                m->setPossibility(true);
            }
        }
        else if (m->getTarget() > 7) //do stosu
        {
            int ts = m->getTarget() - 8;
            if (s[ts].top().getValue() != temp.getLowerValueStack())
            {
                m->setPossibility(false);
            }
            else if (s[ts].top().getColour() != temp.getColour() && s[ts].top().getValue() != "X")
            {
                m->setPossibility(false);
            }
            else
            {
                m->setPossibility(true);
            }
        }
    }
    else //ze stosu
    {
        if (s[m->getSource() - 8].top().getValue() != temp.getValue() || s[m->getSource() - 8].top().getColour() != temp.getColour())  //gdy nie istnieje
        {
            m->setPossibility(false);
        }
        else if (m->getTarget() > 0 && m->getTarget() < 8) //do wektora
        {
            int tv = m->getTarget() - 1;
            int firstEmpty = searchVector(v, tv);
            if (firstEmpty != 0)
            {
                if (v[tv][firstEmpty - 1].getValue() != temp.getLowerValueVector())
                {
                    m->setPossibility(false);
                }
                else if (v[tv][firstEmpty - 1].getColour() != temp.getLowerColourVector(0) && v[tv][firstEmpty - 1].getColour() != temp.getLowerColourVector(1))
                {
                    m->setPossibility(false);
                }
                else
                {
                    m->setPossibility(true);
                }
            }
            else if (firstEmpty == 0 && temp.getValue() != "K")
            {
                m->setPossibility(false);
            }
            else
            {
                m->setPossibility(true);
            }
        }
    }
}

void setMove(Move* m, Card deck[52], vector< vector<Card>>& v, vector<stack<Card>>& s, stack<Card>& toPick) //poprawność zapisu ruchu
{
    if (m->getM1() != "0" && m->getM1() != "1" && m->getM1() != "2" && m->getM1() != "3" && m->getM1() != "4" && m->getM1() != "5" && m->getM1() != "6" && m->getM1() != "7" && m->getM1() != "8" && m->getM1() != "9" && m->getM1() != "10" && m->getM1() != "11") //karte można wziąć z miejsc 0-11
    {
        m->setCorrectness(false);
    }
    else if (m->getM3() != "1" && m->getM3() != "2" && m->getM3() != "3" && m->getM3() != "4" && m->getM3() != "5" && m->getM3() != "6" && m->getM3() != "7" && m->getM3() != "8" && m->getM3() != "9" && m->getM3() != "10" && m->getM3() != "11") //karty nie można położyć na miejsce 0 (kolejka)
    {
        m->setCorrectness(false);
    }
    else if (m->getM1() == m->getM3() && m->getSource() > 7)
    {
        m->setCorrectness(false);
    }
    else
    {
        m->setCorrectness(false);
        for (int i = 0; i < 52; i++)
        {
            if (deck[i].getValue() == m->getM2().getValue() && deck[i].getColour() == m->getM2().getColour()) //czy karta ogólnie istnieje
            {
                m->setCorrectness(true);
                break;
            }
        }
    }
}

bool ifWin(vector<stack<Card>>& s) //warunek wygranej
{
    if (s[0].top().getValue() == "K" && s[1].top().getValue() == "K" && s[2].top().getValue() == "K" && s[3].top().getValue() == "K")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void getNextCards(queue<Card>& currentQ, queue<Card>& nextQ, stack<Card>& toPick) { //kolejka
    long pickSize = toPick.size();
    for (int i = 0; i < pickSize; i++) {
        nextQ.push(toPick.top());
        toPick.pop();
    }
    toPick = stack<Card>();

    long remaining = currentQ.size();

    if (remaining <= 0) {
        currentQ = nextQ;
        nextQ = queue<Card>();
        remaining = currentQ.size();
    }

    if (remaining > 3) {
        remaining = 3;
    }

    for (int i = 0; i < remaining; i++) {
        Card card = currentQ.front();
        currentQ.pop();
        toPick.push(card);
    }

    cout << "Remaining cards: " << currentQ.size() << endl << endl;
}

int main()
{
    vector<Card> rows(18);
    vector< vector<Card> > columns(7, rows);
    queue<Card> currentQ, nextQ;
    stack<Card> toPick;
    vector<stack<Card>> stacks(4);
    Card deck[52];
    int numbers[52];
    string move1, move2, move3;
    Move move;
    int what;
    rules();
    cout << endl;
    fillDeck(deck);
    arrangeCards(numbers, deck, columns, stacks, currentQ);
    while (!ifWin(stacks))
    {
        cout << endl;
        cout << "Co chcesz zrobic?" << endl;
        cout << "  1 - rozpocznij nowa gre" << endl;
        cout << "  2 - zakoncz gre" << endl;
        cout << "  3 - wyswietl zasady" << endl;
        cout << "  4 - wykonaj ruch w grze" << endl;
        cout << "  5 - nastepne karty z kolejki" << endl;
        cout << "Wybor: ";
        cin >> what;
        cout << endl;
        switch (gameState)
        {
        case 0:
        {
            if (what == 1)//rozpocznij
            {
                emptyPlaces(columns);
                setFacing(columns);
                board(columns, stacks, toPick);
                gameState++;
            }
            else if (what == 2)//zakończ
            {
                cout << "szkoda :((" << endl;
                return 0;
            }
            else if (what == 3)//zasady
            {
                rules();
            }
            else
            {
                cout << "Zla komenda" << endl;
            }
            break;
        }
        case 1:
        {
            if (what == 1) //rozpocznij nową
            {
                clear(columns, stacks, currentQ, nextQ, toPick);
                int numbers[52];
                arrangeCards(numbers, deck, columns, stacks, currentQ);
                emptyPlaces(columns);
                setFacing(columns);
                board(columns, stacks, toPick);
            }
            else if (what == 2)//zakończ
            {
                cout << "szkoda :((" << endl;
                return 0;
            }
            else if (what == 3)//zasady
            {
                rules();
            }
            else if (what == 4)//ruch w grze
            {
                cin >> move1 >> move2 >> move3;
                move.setM1(move1);
                move.setM2(move2);
                move.setM3(move3);
                move.setSource(stoi(move.getM1()));
                move.setTarget(stoi(move.getM3()));
                setMove(&move, deck, columns, stacks, toPick);
                if (move.getCorrectness() == true)
                {
                    move.getM2().setLowerCardVector();
                    move.getM2().setLowerCardStack();
                    setPossibility(&move, columns, stacks, toPick);
                    if (move.getPossibility() == true)
                    {
                        if (move.getSource() > 0 && move.getSource() < 8)
                        {
                            setCovers(&move, columns);
                            makeMove(move, columns, stacks, toPick);
                        }
                        else
                        {
                            makeMove(move, columns, stacks, toPick);
                        }
                    }
                    else
                    {
                        cout << "Niepoprawny ruch." << endl;
                    }
                }
                else
                {
                    cout << "Niepoprawny ruch." << endl;
                }
                board(columns, stacks, toPick);
            }
            else if (what == 5)  //przetasowanie kolejki
            {
                getNextCards(currentQ, nextQ, toPick);
                board(columns, stacks, toPick);
            }
            else
            {
                cout << "Zla komenda" << endl;
            }
            break;
        }
        }
    }
    cout << "Brawo. Zmarnowales mnostwo czasu." << endl;
    return 0;
}
