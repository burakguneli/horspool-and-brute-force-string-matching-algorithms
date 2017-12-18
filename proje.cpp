#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <time.h>
#include <unistd.h>

using namespace std;

int bruteExecutionCounter = 0;
int horspoolExecutionCounter = 0;

int HorspoolMatch(int textLength,int patternLength,char patternArray[],char textArray[]){

    clock_t t;
    int shiftArray[300];
    t = clock();
	bool found = false;

    for(int i = 0; i < 256; i++){
        shiftArray[i] = patternLength;
    }
    for(int k = 0; k < patternLength - 1; k++){
        shiftArray[patternArray[k]] = patternLength - 1 - k;
    }

    int tempNumber = patternLength - 1;
    while(tempNumber <= textLength - 1){
		horspoolExecutionCounter++;
        int matchedChars = 0;

        while ((matchedChars <= patternLength - 1) && (patternArray[patternLength -  1  - matchedChars] == textArray[tempNumber - matchedChars])) {
        	horspoolExecutionCounter++;
            matchedChars++;
        }


        if(matchedChars == patternLength){
        	found = true;
        	t = clock() - t;
            cout<< "------------ Horspool algorithm found requested pattern at step "<< tempNumber - patternLength<<endl;
   	     	std::cout << "------------ Horspool algorithm executed : " << horspoolExecutionCounter <<" number of operations" <<" in "<<t<<" sec"<<'\n';

            return tempNumber - patternLength + 1;
        }else{
            tempNumber = tempNumber + shiftArray[textArray[tempNumber]];
	    }
    }
    if(found==false){
    	cout<<"Not found";
	}
    int horspoolExecutionCounter = 0;
    return 0;
}

int BruteMatch(int textLength,int patternLength,char patternArray[],char textArray[]){

    clock_t t;
    t = clock();
	bool found = false;

    for(int i = 0; i < (textLength-patternLength); i++){
    	int j = 0;
        bruteExecutionCounter++;
        while((j < patternLength) && (patternArray[j] == textArray[i + j])){
        	bruteExecutionCounter++;
            j++;
        }
        if(j == patternLength){
        	t = clock()- t;
        	cout<<"------------ Brute Force algorithm found requested pattern at step "<<i-1<<endl;
            cout << "------------ Brute Force algorithm executed " << bruteExecutionCounter <<" number of operations in "<<t<<" sec"<< '\n';

            found = true;
            break;
        }
    }
	if(found==false){
    	cout<<"Not Found";
	}
    int bruteExecutionCounter = 0;
    return 0;
}

int main()
{
    int choise = 10;
    unsigned int microseconds = 1500000;

    while (!(choise == 0)) {

        string text;

        ifstream infile;
        infile.open ("the_truman_show_script.txt");
            while(!infile.eof())
            {
                getline(infile, text);
            }
        infile.close();
        string pattern = "";
        char textArray[100000];
        int textLength = 0;
        textLength = text.length();
        strcpy(textArray, text.c_str());
        std::cout << "Choose one of the following" << '\n';
        std::cout << '\n';
        std::cout << "(1) Brute Force String Matching" << std::endl;
        std::cout << "(2) Horspool's String Matching" << std::endl;
        std::cout << "(3) Compare Brute Force Algorithm and Horspool Algorithm" << std::endl;
        std::cout << "(0) Exit" << std::endl;
        std::cout << '\n';
        std::cout << "Type in your selected number: ";
        std::cin >> choise;
        if(!(choise == 0) && !(choise == 1) && !(choise == 2) && !(choise == 3)){
            cout << "You choosed unavaiable number, please run the code again!" << endl;
            break;
        }

        if(choise == 0){
            break;
        }

        int patternLength = 0;

        cout << "Type pattern: ";
        cin >> pattern;
        char patternArray[100000];
        strcpy(patternArray, pattern.c_str());

        patternLength = pattern.length();


        if(choise == 1){
            BruteMatch(textLength,patternLength,patternArray,textArray);

            std::cout << '\n';
            std::cout << "You are being redirected to main menu..." << '\n';
            usleep(microseconds);
            std::cout << '\n';
        }


        if(choise == 2){
            HorspoolMatch(textLength,patternLength,patternArray,textArray);

            std::cout << '\n';
            std::cout << "You are being redirected to main menu..." << '\n';
            usleep(microseconds);
            std::cout << '\n';
        }


        if(choise == 3){
            BruteMatch(textLength,patternLength,patternArray,textArray);
            std::cout << '\n';
            HorspoolMatch(textLength,patternLength,patternArray,textArray);

            std::cout << '\n';
            std::cout << "You are being redirected to main menu..." << '\n';
            usleep(microseconds);
            std::cout << '\n';
        }
    }
    return 0;
}
