#include <iostream>
#include <vector>
#include <string>
#include <fstream> // For file handling
#include <cstdlib> // For system("cls") 
#include <locale.h>
#include <utility>
#include <sstream> 
#include <algorithm> 
using namespace std;

struct Question {
    int id;
    string text;
    vector<string> options;
    char correctAnswer;

};

// "&" is used to pass by reference, avoiding copying the string and vector
// "const" is used to indicate that the function will not modify the string and vector passed to it
Question makeaquestion(const string& text, const vector<string>& options, char correctAnswer) {
    Question q;
    q.text = text;
    q.options = options;
    q.correctAnswer = correctAnswer;
    return q;
}


vector<Question> quiz;

void PrintQuestion(Question q) {
    string a(50, '-');
    cout << a << endl;
    cout << q.text << endl;
    for (int i = 0; i < q.options.size(); i++) {
        cout << char('A' + i) << ": " << q.options[i] << endl;
    }
}

void WriteRanking(const string& firstName, int score) {
    ofstream outputFile("ranking.txt", ios::app);

    if (!outputFile.is_open()) {
        cout << "Erro: Arquivo 'ranking.txt' nao encontrado ou invalido." << endl;
        return;
    }

    outputFile << firstName << " " << score << endl;
    outputFile.close(); 
}

void PrintRanking() {
    ifstream inputFile("ranking.txt");

    int file_open = inputFile.is_open();
    if (!file_open) {
        cout << "Erro: Arquivo 'perguntas.txt' nao encontrado ou invalido." << endl;
    }

    vector<pair<int, string>> ranking; 
    string line;
    while (getline(inputFile, line)) {
        string name;
        int score;
        istringstream iss(line); 
        iss >> name >> score; 
        ranking.push_back(make_pair(score, name)); 

    }

    sort(ranking.begin(), ranking.end(), greater<pair<int, string>>()); 

    for (int i = 0; i < ranking.size(); i++) {
        cout << ranking[i].second << ": " << ranking[i].first << endl;
    }

    inputFile.close();

};


int score;

int main(){
    system("cls");
    setlocale(LC_ALL, "pt_BR.utf8"); // Set locale to Portuguese
    ifstream inputFile("perguntas.txt");

    int file_open = inputFile.is_open();
    if (!file_open) {
        cout << "Erro: Arquivo 'perguntas.txt' nao encontrado ou invalido." << endl;
    }

    string line;
    int line_number = 0;
    Question question = makeaquestion("", {}, ' '); // Create a blank question
    while (getline(inputFile, line)) {
        line_number++;
        if (line_number == 1) {
            question.text = line; 
        } else if (line_number > 1 && line_number < 6) {
            question.options.push_back(line); 
        } else if (line_number == 6) {
            question.correctAnswer = line[0]; // line returns a string, so we take the first character
        } else if (line_number > 6) {
            line_number = 0; // Reset line number for the next question
            quiz.push_back(question); // Add the question to the quiz
            question = makeaquestion("", {}, ' ');
        }
    }    
    quiz.push_back(question); // Add the last question to the quiz
    
    while(file_open){
        score = 0;
        
        for (int i = 0; i < 10; i++) {
            
            PrintQuestion(quiz[i]);
            cout << "Digite sua resposta: ";
            char answer;
            cin >> answer;
            answer = toupper(answer);
            while(answer < 'A' || answer > 'D') { // ascii saving the day
                cout << "Opcao invalida. Digite novamente (A-D):";
                cin >> answer;
                answer = toupper(answer);
            }
            if (answer == quiz[i].correctAnswer) {
                cout << "Correto!" << endl;
                score++;
            } else {
                cout << "Incorreto! A resposta correta era: " << quiz[i].correctAnswer << endl;
            }

        }
        cout << "Voce acertou " << score << " de " << quiz.size() << endl;
        cout << endl << "Digite seu primeiro nome: ";
        string firstName;
        cin >> firstName;
        WriteRanking(firstName, score);
        PrintRanking();
        
        cout << "Deseja jogar novamente? (s/n): ";
        char playAgain;
        cin >> playAgain;
        if (tolower(playAgain) != 's') {
            break; 
        }
    }


    inputFile.close();
    return 0;
}