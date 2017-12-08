#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <locale>
using namespace std;

const char *inFile = "zmones.txt";
ofstream patalpink("vyrai.txt");

time_t theTime = time(NULL);
struct tm *aTime = localtime(&theTime);
int ymetai = aTime->tm_year+1900;



struct Zmogus
{
    private:
        string Vardas = "";
        string Pavarde = "";
        int gimimoMetai = 0;
        string Miestas = "";
        string Lytis = "";
    public:
        void reader(int kelintas)
        {
            ifstream duomenys(inFile);
            string trashBin = "";
            int iTrashBin = 0;
            try
            {
                 for(int i = 0; i < kelintas; i++)
                {
                    duomenys >> trashBin >> trashBin >> iTrashBin >> trashBin >> trashBin;
                }
                duomenys >> Vardas >> Pavarde >> gimimoMetai >> Miestas >> Lytis;
            }catch(int err)
            {
                cout << "fatal error : " << err << endl;

            }
            //cout << Vardas << "  " << Pavarde << " " << gimimoMetai << " " << Miestas << " " << Lytis << endl;


            duomenys.close();
        }
        void vyresnis(int &tMetai)
        {
            if(tMetai > gimimoMetai)
            {
                tMetai = gimimoMetai;
            }
        }
        void spauzdink(int uzd, int metai, string pMiestas, int &rado) // 1 = vyriausias // 2 = miestai
        {
            locale loc;


            for(int i = 0; i < Miestas.length(); i++)
            {
                Miestas[i] =  tolower(Miestas[i], loc);
            }

            for(int i = 0; i < pMiestas.length(); i++)
            {
                pMiestas[i] =  tolower(pMiestas[i], loc);
            }

            ///vyriausias-i
            if(uzd == 1)
                if(metai == gimimoMetai)
                    cout << Vardas << " " << Pavarde << " " << ymetai-gimimoMetai << " " << Miestas << " " << Lytis << endl;
            ///miestas
            if(uzd == 2)
                if(Miestas == pMiestas)
                    cout << Vardas << " " << Pavarde << " " << ymetai-gimimoMetai << " " << Miestas << " " << Lytis << endl;
            ///vyrai
            if(uzd == 3)
            {
                if(Lytis == "Vyras" or Lytis == "vyras" or Lytis == "v")
                {

                    patalpink << Vardas << " " << Pavarde << " " << ymetai-gimimoMetai << " " << Miestas << " " << Lytis << endl;

                }
            }


            if(uzd == 4)
            {
                if(pMiestas == Miestas)
                    if(metai >= gimimoMetai){
                        cout << Vardas << " " << Pavarde << " " << ymetai-gimimoMetai << " " << Miestas << " " << Lytis << endl;
                        rado++;
                    }

            }

        }
};

int kiekZmoniu(int ran);
void randa(Zmogus *masyvas, int kiek);

int main()
{
    int kiek = 0;
    int dabartinis = 0;

    kiek = kiekZmoniu(kiek); /// nusako kiek bus zmoniu

    Zmogus *masyvas = new Zmogus[kiek]; /// sukuria zmones



    ///nuskaito
    for(int i = 0; i < kiek; i++)
    {
        masyvas[i].reader(dabartinis);
        dabartinis++;
    }

    randa(masyvas, kiek);
    return 0;
}

int kiekZmoniu(int ran)
{
    ifstream duomenys(inFile);
    string trashStr = "";
    int trashInt = 0;

    while(duomenys)
    {
        try
        {
             duomenys >> trashStr;
             duomenys >> trashStr;
             duomenys >> trashInt;
             duomenys >> trashStr;
             duomenys >> trashStr;
             ran++;
        }
        catch(int err)
        {
            cout << "Fatal error: " << err << endl;
        }

    }

    ran--;
    duomenys.close();
    return ran;
}


void randa(Zmogus *masyvas, int kiek)
{
    int pasirinkimas = 0;
        int vyriausias = 3000;
        for(int i = 0; i < kiek; i++)
        {
            masyvas[i].vyresnis(vyriausias);
        }
    string pMiestas;
    int rado = 0;
    while(pasirinkimas != -1)
    {

        cout << "1. rasti vyriausia gyventoja" << endl;
        cout << "2. Atspauzdina visus pasirinkto miesto gyventojus" << endl;
        cout << "3. patalpinti visus vyrus i faila" << endl;
        cout << "4. atspauzdina vyresnius kaip 30 metu gyventojus" << endl;
        cin >> pasirinkimas;
        system("CLS");
        if(pasirinkimas == 1)
        {
            //vyriausias
            cout << endl << endl << endl;
            cout << "Vyriausias : ";
            for(int i = 0; i < kiek; i++)
            {
                masyvas[i].spauzdink(1, vyriausias, "", rado);
            }
            cout << endl;
        }
        if(pasirinkimas == 2)
        {
            ///pasirinktas miesas
            pMiestas = "";
            cout << "iveskite norima miesta: ";
            cin >> pMiestas;


            for(int i = 0; i < kiek; i++)
            {
                masyvas[i].spauzdink(2, 0, pMiestas, rado);
            }
        }
        if(pasirinkimas == 3)
        {
            /// visi vyrai lauk
            for(int i = 0; i < kiek; i++)
                masyvas[i].spauzdink(3,0,"",rado);
            patalpink.close();

        }

        if(pasirinkimas == 4)
        {
            cout << "Koksai miestas: ";
            cin >> pMiestas;
            char c;
            for(int i = 0; i < kiek; i++)
            masyvas[i].spauzdink(4, ymetai-30, pMiestas, rado);

            if(rado == 0)
            {
                cout << "Nerasta gyventoju" << endl;
            }
        }

        cout << endl << endl;
    }

    ///vyriausias
//
//    int vyriausias = 3000;
//    for(int i = 0; i < kiek; i++)
//    {
//        masyvas[i].vyresnis(vyriausias);
//    }
    /// vyriausias



//    ///pasirinktas miesas
//    string pMiestas = "";
//    cout << "iveskite norima miesta: ";
//    cin >> pMiestas;
//
//
//    for(int i = 0; i < kiek; i++)
//    {
//        masyvas[i].spauzdink(2, 0, pMiestas);
//    }

//    /// visi vyrai lauk
//
//    for(int i = 0; i < kiek; i++)
//        masyvas[i].spauzdink(3,0,"");
//    patalpink.close();


//    cout << "Koksai miestas: ";
//    cin >> pMiestas;
//    char c;
//    for(int i = 0; i < kiek; i++)
//        masyvas[i].spauzdink(4, ymetai-30, pMiestas);
}
