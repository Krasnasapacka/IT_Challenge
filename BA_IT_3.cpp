//BA_IT_3_Liudas_Mazeika, 2018-09-08
//CodeBlocks13.12
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef> //null
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

void ReadData (string DARZ_ID[], string SCHOOL_NAME[], string TYPE_ID [], string TYPE_LABEL[], string LAN_ID[],
               string LAN_LABEL[], string CHILDS_COUNT[], string FREE_SPACE[], int & linecount)
{
    //visi duomenys nusiskaitomi kaip string masyvai
    int i=1;
    linecount=0;
    ifstream fd ("Darzeliu galimu priimti ir lankantys vaikai2018.csv");
    string FirstLine;
    fd>>FirstLine; //Pirma eilute nereikalinga
    while (fd.good())
    {
        getline(fd, DARZ_ID [i], ';');
        getline(fd, SCHOOL_NAME [i],';');
        getline(fd, TYPE_ID [i], ';');
        getline(fd, TYPE_LABEL [i], ';');
        getline(fd, LAN_ID [i], ';');
        getline(fd, LAN_LABEL [i], ';');
        getline(fd, CHILDS_COUNT [i], ';');
        getline(fd, FREE_SPACE [i], '\n');
        i++;
        linecount++;
    }
    fd.close();

}
void DataTypeConversion (string DARZ_ID[], string TYPE_ID [], string LAN_ID[], string CHILDS_COUNT[], string FREE_SPACE[],
                         int cDARZ_ID[], int cTYPE_ID[], int cLAN_ID[], int cCHILDS_COUNT[], int cFREE_SPACE[], int & linecount)
{
    for (int i=1; i<=linecount; i++)
    {
        cDARZ_ID[i]=atoi(DARZ_ID[i].c_str()); //cDARZ_ID-darzelio_id perverstas i int tipa.
        cTYPE_ID[i]=atoi(TYPE_ID[i].c_str());
        cLAN_ID[i]=atoi(LAN_ID[i].c_str());
        cCHILDS_COUNT[i]=atoi(CHILDS_COUNT[i].c_str());
        cFREE_SPACE[i]=atoi(FREE_SPACE[i].c_str());
    }

}
void ChildsCountToConsole (int cCHILDS_COUNT[], int & linecount, int & maxChilds, int & minChilds)
{
    // i ekrana isvedamas maksimalus ir minimalus vaiku skaiciai
    maxChilds=cCHILDS_COUNT[1];//kad nebutu siuksliu
    minChilds=cCHILDS_COUNT[1];
    for (int i=1; i<=linecount; i++)
    {
        if (cCHILDS_COUNT[i]>maxChilds)
        {
            maxChilds=cCHILDS_COUNT[i];
        }
        else if (cCHILDS_COUNT[i]<minChilds)
        {
            minChilds=cCHILDS_COUNT[i];
        }

    }
    cout<<"Didziausia reiksme: "<< maxChilds<<endl;
    cout<<"Maziausia reiksme: "<< minChilds<<endl;
}
void LinesMaxMinChildsCount (int cCHILDS_COUNT[], int LINES_CHILDS_COUNT[], int & linecount, int & maxChilds, int & minChilds,
                             int & ChildLines)
{
    //funkcija parodo, kuriose eilutese vaiku skaicius yra maksimalus arba minimalus.
    int a=1; //kintamasis, pasizemti kelintos eilutes yra MAX arba MIN CHILDS_COUNT.
    for (int i=1; i<=linecount; i++)
    {
        if (cCHILDS_COUNT[i]==maxChilds||cCHILDS_COUNT[i]==minChilds)
        {
            LINES_CHILDS_COUNT[a]=i; //eilutes numeris, kur vaiku skaicius Min arba Max
            a++;

        }
    }
    ChildLines=a;
}
void SchoolNameThreeChars (string SCHOOL_NAME[], char cSCHOOL_NAME[][50], int & linecount)
{
    //funkcija is string masyvo iskiria simbolius ir juos priskiria dvimaciam char masyvui (svarbus tik pirmi trys simboliai)
    for (int i=1; i<=linecount; i++)
    {

        strcpy(cSCHOOL_NAME[i], SCHOOL_NAME[i].c_str());

        if (cSCHOOL_NAME[i][0]=='"'||cSCHOOL_NAME[i][0]=='„') //tuo atveju, jei kabutes pirmas simbolis
        {
            cSCHOOL_NAME[i][0]=cSCHOOL_NAME[i][1];
            cSCHOOL_NAME[i][1]=cSCHOOL_NAME[i][2];
            cSCHOOL_NAME[i][2]=cSCHOOL_NAME[i][3];

            if (cSCHOOL_NAME[i][0]=='„')
            {
                 cSCHOOL_NAME[i][0]=cSCHOOL_NAME[i][1];
                 cSCHOOL_NAME[i][1]=cSCHOOL_NAME[i][2];
                 cSCHOOL_NAME[i][2]=cSCHOOL_NAME[i][3];
            }
        }
        if (cSCHOOL_NAME[i][2]==' ')
        {
            cSCHOOL_NAME[i][2]=cSCHOOL_NAME[i][4];
        }

    }

}
void Type_LabelNumbers (string TYPE_LABEL[], double TYPE_LABEL_NUM[][10], char cTYPE_LABEL[][50], int TEST[], int & linecount)
{
    // is string masyvo yra isrenkami skaiciai ir priskiriami double tipo masyvui. Susidaro daug if'u del galimu nesveiku skaiciu
   for(int i=1; i<=linecount; i++)
   {
       strcpy(cTYPE_LABEL[i], TYPE_LABEL[i].c_str()); //pasiverciame i char tipa

       if(cTYPE_LABEL[i][1]=='I')
       {
           TYPE_LABEL_NUM[i][1]=0;
           TYPE_LABEL_NUM[i][2]=cTYPE_LABEL[i][5]-'0';
           if(cTYPE_LABEL[i][6]==',')
           {
            TYPE_LABEL_NUM[i][4]=cTYPE_LABEL[i][7]-'0';
            TYPE_LABEL_NUM[i][2]=TYPE_LABEL_NUM[i][2]+TYPE_LABEL_NUM[i][4]/10;
           }
       }
       else
       {

       TYPE_LABEL_NUM[i][1]=cTYPE_LABEL[i][5]-'0'; //pirmas skaicius nuskaitomas kaip double
       if(cTYPE_LABEL[i][6]==',')
       {
           TYPE_LABEL_NUM[i][3]=cTYPE_LABEL[i][7]-'0'; //jei buna kablelis skaitome skaiciu po kableliu ir ji sudedame su jau nuskaitytu
           TYPE_LABEL_NUM[i][1]=TYPE_LABEL_NUM[i][1]+TYPE_LABEL_NUM[i][3]/10;
           TYPE_LABEL_NUM[i][2]=cTYPE_LABEL[i][13]-'0';
           if (cTYPE_LABEL[i][14]==',')
           {
               TYPE_LABEL_NUM[i][4]=cTYPE_LABEL[i][15]-'0';
               TYPE_LABEL_NUM[i][2]=TYPE_LABEL_NUM[i][2]+TYPE_LABEL_NUM[i][4]/10;
           }
       }
        else if (cTYPE_LABEL[i][6]!=',')
       {
           if (cTYPE_LABEL[i][11]!=NULL)
           {
             TYPE_LABEL_NUM[i][2]=cTYPE_LABEL[i][11]-'0';
           }
           else
           {
             TYPE_LABEL_NUM[i][2]=100;
           }

       }
        //skaitomas skaicius IKI (antrasis)
       if (cTYPE_LABEL[i][12]==',')
       {
           TYPE_LABEL_NUM[i][4]=cTYPE_LABEL[i][13]-'0';
           TYPE_LABEL_NUM[i][2]=TYPE_LABEL_NUM[i][2]+TYPE_LABEL_NUM[i][4]/10;
       }
       }
       if (TYPE_LABEL_NUM[i][1]==-48)
       {
           TYPE_LABEL_NUM[i][1]=0;
       }
       //cout<<TYPE_LABEL_NUM[i][1]<<" iki " <<TYPE_LABEL_NUM[i][2]<<endl;
       //cout<<i<<endl;

   }

}
void Lan_LabelFourChars (string LAN_LABEL[], char cLAN_LABEL[][50], int & linecount)
{
    // string masyvas yra perveciamas i char masyva, kad butu galima isvesti tik keturias pirmas raides.
     for (int i=1; i<=linecount; i++)
    {
        strcpy(cLAN_LABEL[i], LAN_LABEL[i].c_str());
    }

}
void ToFirstTextFile (char cSCHOOL_NAME[][50],double TYPE_LABEL_NUM[][10], char cLAN_LABEL[][50], int & linecount, int & ChildLines,
                      int LINES_CHILDS_COUNT[])
{
    //isvedimas i pirma rezultatu faila
    ofstream fr( "FirstResultFile.txt");
    for (int k=1; k<=ChildLines; k++)
    {
    for (int i=1; i<=linecount; i++)
    {
        if (LINES_CHILDS_COUNT[k]==i) //jeigu linija patenka tarp tu liniju kuriose vaiku yra max arba min tada jai leidziama iseit i rezultatus
        {
        for (int z=0; z<3; z++)
        {
           fr<<cSCHOOL_NAME[i][z];
        }
        fr<<"_";
        fr<<TYPE_LABEL_NUM[i][1]<<"-"<<TYPE_LABEL_NUM[i][2];
        fr<<"_";
        for (int j=0; j<=3; j++)
        {
            fr<<cLAN_LABEL[i][j];
        }
        fr<<endl;
        }
    }
    }
    fr.close();
}
void SpaceByLan (int cLAN_ID[], int cFREE_SPACE[],int TOTAL_FREE_SPACE[],int COUNT_LAN[], int cCHILDSCOUNT[],
                     int TOTAL_SPACE[], int & linecount)
{
    //randama visa bendra vieta (TOTAL_SPACE) ir visa laisva likusi vieta(TOTAL_FREE_SPACE)
    //(atskirti kalboms naudojamas kiekvienos kalbos id)
    for(int i=1; i<=linecount; i++)
    {
        for(int z=1; z<=10; z++)
        {
            if (z=cLAN_ID[i])
            {
                TOTAL_FREE_SPACE[z]=TOTAL_FREE_SPACE[z]+cFREE_SPACE[i];
                TOTAL_SPACE[z]=TOTAL_SPACE[z]+cFREE_SPACE[i]+cCHILDSCOUNT[i];
                COUNT_LAN[z]=COUNT_LAN[z]+1;
                break;
            }

        }
    }
}
void CountFreeSpacePercentage(int TOTAL_FREE_SPACE[], int COUNT_LAN[], double FREE_SPACE_PERCENTAGE[], int TOTAL_SPACE[], int & linecount,
                              double & maxPercentage, int & LanId, double dTOTAL_SPACE[], double dTOTAL_FREE_SPACE[])
{
    //funkcija randa kiek kiekvienos kalbos darzeliai turi laisvos vietos procentais ir randa didziausia verte. Lanid yra kalbos id, kurios procentas didziausias
    maxPercentage=-1; //del siuksliu
    double percent;
    for (int z=1; z<=10; z++)
    {
        if (COUNT_LAN[z]>0)
        {
            dTOTAL_FREE_SPACE[z]=TOTAL_FREE_SPACE[z];
            dTOTAL_SPACE[z]=TOTAL_SPACE[z]; //persiverciame i double
            FREE_SPACE_PERCENTAGE[z]=(dTOTAL_FREE_SPACE[z]*100)/dTOTAL_SPACE[z];
            if (FREE_SPACE_PERCENTAGE[z]>maxPercentage)
            {
                maxPercentage=FREE_SPACE_PERCENTAGE[z];
                LanId=z;
            }
        }
    }
}
void ToSecondTextFile(string LAN_LABEL[], int cLAN_ID[], double & maxPercentage, int & LanId, int & linecount )
{
    ofstream fr("SecondResultFile.txt");
    for (int i=1; i<=linecount; i++)
    {
        if (LanId==cLAN_ID[i])
        {
            fr<<LAN_LABEL[i];
            break;
        }
    }
    fr<<": "<<fixed<< setprecision(2)<< maxPercentage<<"%"<<endl;
    fr.close();

}
void FilterKindergartens(int cFREE_SPACE[], int LINE_NUMBER_SPACE[], int & linecount, int & LineNumberSpace)
{
    //funkcija isrusiuoja tuos darzelius, kurie turi vietu tarp 2-4
    int a=1;
    for (int i=1; i<=linecount; i++)
    {
        if (cFREE_SPACE[i]>=2 && cFREE_SPACE[i]<=4)
        {
            LINE_NUMBER_SPACE[a]=i; //issirusiuojame, kad zinotume kurios linijos atitinka kriteriju tarp 2-4 laisvu vietu
            a++;
        }
    }
    LineNumberSpace=a;
}
void RemoveQuotesFromSchoolName(string SCHOOL_NAME[], int LINE_NUMBER_SPACE[], int & LineNumberSpace)
{
    //panaikinamos kabutes, nes kai kurie darzeliu pavadinimai yra kabutese.
    int n=0;
    for (int i=1; i<=LineNumberSpace; i++)
    {
    n=LINE_NUMBER_SPACE[i];
    SCHOOL_NAME[n].erase
    (remove( SCHOOL_NAME[n].begin(), SCHOOL_NAME[n].end(), '\"' ),
    SCHOOL_NAME[n].end());
    }
}
void OrderingKindergartens(string SCHOOL_NAME[], int LINE_NUMBER_SPACE[], int & LineNumberSpace)
{
    //Darzeliai surikiuojami nuo Z iki A.
    int n=1;
    string ForOrdering;
    int n2=0;
    for (int i=1; i<= LineNumberSpace; i++)
    {
        for (int z=1; z<= LineNumberSpace; z++)
        {
            n=LINE_NUMBER_SPACE[z];
            n2=LINE_NUMBER_SPACE[z+1];
            if (SCHOOL_NAME[n]<SCHOOL_NAME[n2])
            {
                ForOrdering=SCHOOL_NAME[n];
                SCHOOL_NAME[n]=SCHOOL_NAME[n2]; //sukeiciami vietomis.
                SCHOOL_NAME[n2]=ForOrdering;

            }
        }
    }
}
void ToThirdTextFile(string SCHOOL_NAME[], int LINE_NUMBER_SPACE[], int & LineNumberSpace)
{
     int n=0;
     ofstream fr("ThirdResultFile.txt");
     for (int i=1; i<= LineNumberSpace; i++)
     {
         n=LINE_NUMBER_SPACE[i];
         fr<< SCHOOL_NAME[n]<<endl;
     }
     fr.close();
}
int main()
{
    //apsirasomi visi kintamuju dydziai ir issaukiamos funkcijos.
    string Line[2000], SCHOOL_NAME[2000],TYPE_LABEL[2000], LAN_LABEL[2000], DARZ_ID[2000],
    TYPE_ID [2000], LAN_ID[2000], CHILDS_COUNT[2000], FREE_SPACE[2000];

    int cDARZ_ID[2000], cTYPE_ID[2000], cLAN_ID[2000], cCHILDS_COUNT[2000], cFREE_SPACE[2000], linecount, maxChilds, minChilds,
    LINES_CHILDS_COUNT[2000], TEST[2000],TOTAL_FREE_SPACE[2000], COUNT_LAN[2000], TOTAL_SPACE[2000], LanId, ChildLines,
    LINE_NUMBER_SPACE[2000], LineNumberSpace;

    char cSCHOOL_NAME[2000][50], cTYPE_LABEL[2000][50], cLAN_LABEL[2000][50];

    double  TYPE_LABEL_NUM[2000][10], FREE_SPACE_PERCENTAGE[2000], maxPercentage, dTOTAL_SPACE[2000], dTOTAL_FREE_SPACE[2000];

    ReadData(DARZ_ID,SCHOOL_NAME,TYPE_ID,TYPE_LABEL,LAN_ID,LAN_LABEL,CHILDS_COUNT,FREE_SPACE, linecount);
    DataTypeConversion(DARZ_ID,TYPE_ID,LAN_ID,CHILDS_COUNT,FREE_SPACE,cDARZ_ID,cTYPE_ID,cLAN_ID,cCHILDS_COUNT,cFREE_SPACE, linecount);
    ChildsCountToConsole(cCHILDS_COUNT, linecount, maxChilds, minChilds);
    LinesMaxMinChildsCount(cCHILDS_COUNT, LINES_CHILDS_COUNT, linecount, maxChilds, minChilds, ChildLines);
    SchoolNameThreeChars(SCHOOL_NAME, cSCHOOL_NAME, linecount);
    Type_LabelNumbers(TYPE_LABEL, TYPE_LABEL_NUM, cTYPE_LABEL, TEST, linecount);
    Lan_LabelFourChars(LAN_LABEL, cLAN_LABEL, linecount);
    ToFirstTextFile(cSCHOOL_NAME, TYPE_LABEL_NUM, cLAN_LABEL, linecount, ChildLines, LINES_CHILDS_COUNT);
    SpaceByLan(cLAN_ID, cFREE_SPACE, TOTAL_FREE_SPACE, COUNT_LAN, cCHILDS_COUNT, TOTAL_SPACE, linecount);
    CountFreeSpacePercentage(TOTAL_FREE_SPACE, COUNT_LAN, FREE_SPACE_PERCENTAGE, TOTAL_SPACE, linecount, maxPercentage, LanId, dTOTAL_SPACE,
                             dTOTAL_FREE_SPACE);
    ToSecondTextFile(LAN_LABEL, cLAN_ID, maxPercentage, LanId, linecount);
    FilterKindergartens(cFREE_SPACE, LINE_NUMBER_SPACE, linecount, LineNumberSpace);
    RemoveQuotesFromSchoolName(SCHOOL_NAME, LINE_NUMBER_SPACE, LineNumberSpace);
    OrderingKindergartens(SCHOOL_NAME, LINE_NUMBER_SPACE, LineNumberSpace);
    ToThirdTextFile(SCHOOL_NAME, LINE_NUMBER_SPACE, LineNumberSpace);

    return 0;
}
