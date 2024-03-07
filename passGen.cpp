#include <iostream> // Biblioteca de entrada/saída padrão
#include <cstdlib> // Biblioteca para funções de uso geral
#include <string> // Biblioteca para manipulação de strings
#include <ctime> // Biblioteca para trabalhar com tempo
#include <algorithm> // Biblioteca para algoritmos gerais
#include <vector> // Biblioteca para trabalhar com vetores
#include <fstream>
#include <sstream>

// Função auxiliar para converter uma string para minúsculas
std:: string toLowercase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Recebe uma string como entrada e verifica se ela é "sim" ou "nao" (ignorando maiúsculas/minúsculas). A função usa a função "toLowercase" definida anteriormente.
bool inputValido(const std::string& input) {
    std::string LowercaseInput = toLowercase(input);
    return LowercaseInput == "sim" || LowercaseInput == "nao";
}

// Recebe uma string como entrada (prompt) e solicita ao usuário que digite "Sim" ou "Nao". A função verifica se a entrada é válida usando a função "inputValido" e repete a solicitação até que uma entrada válida seja fornecida. A função retorna um valor booleano indicando se o usuário respondeu "Sim" ou "Nao".
bool getEntradaSimNao(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::cin >> input;

    while (!inputValido(input)) {
        std::cout << "Opcao invalida. Por favor, responda 'Sim' ou 'Nao': ";
        std::cin >> input;
    }

    return toLowercase(input) == "sim";
}

int main() {
    std::srand(std::time(nullptr));
    int length; //armazena comprimento da senha.
    std::string password = ""; //armazena senha.
    const std::string numbers = "0123456789";
    const std::string uppercaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowercaseLetters = "abcdefghijklmnopqrstuvwxyz";
    const std::string symbols = "!@#$%^&*()[]=-/|";
    std::vector<std::string> userInputs(4); // Vetor para armazenar as opções do usuário
    std::vector<bool> useOptions(4); // Vetor para armazenar as opções de uso

    std::cout << "\n*******************//////////////*****************\n";
    std::cout << "//////////////////////////////////////////////////\n";
    std::cout << "//////////////////PASSWORD GEN///////////////////\n";
    std::cout << "////////////////////////////////////////////////\n";
    std::cout << "****************/////////////**********v00.9***\n";

    std::cout << "\nDigite o comprimento da senha: ";
    std::cin >> length; //armazena o valor.

    while (length <= 0) {
        std::cout << "\nComprimento invalido. Digite um valor maior que 0: ";
        std::cin >> length;
    }

    useOptions[0] = getEntradaSimNao("\nUsar numeros? (Sim/Nao): ");
    useOptions[1] = getEntradaSimNao("Usar letras maiusculas? (Sim/Nao): ");
    useOptions[2] = getEntradaSimNao("Usar letras minusculas? (Sim/Nao): ");
    useOptions[3] = getEntradaSimNao("Usar simbolos? (Sim/Nao): ");

    std::string availableChars = ""; // String para armazenar os caracteres disponíveis para a senha

    // Adiciona os caracteres correspondentes às opções selecionadas à string de caracteres disponíveis
    if (useOptions[0]) {
        availableChars += numbers;
    }
    if (useOptions[1]) {
        availableChars += uppercaseLetters;
    }
    if (useOptions[2]) {
        availableChars += lowercaseLetters;
    }
    if (useOptions[3]) {
        availableChars += symbols;
    }
    
    int maxRand = availableChars.length() - 1;

     // Gera a senha aleatória usando a distribuição dist e o gerador gen, seleciona um caractere aleatório de availableChars. E Adiciona o caractere à senha na variável password.
    for (int i = 0; i < length; i++) {
        char randomChar = availableChars[std::rand() % (maxRand + 1)]; // Gera um número aleatório e usa-o para selecionar um caractere aleatório de availableChars
        password += randomChar; // Adiciona o caractere à senha
    }

    std::cout << "\nSenha gerada: " << password << std::endl; // exibe a senha gerada no console.

    bool savePassword = getEntradaSimNao("Deseja salvar a senha em um arquivo? (Sim/Nao): ");
    if (savePassword) {
        std::ofstream file("senha.txt", std::ios_base::app); // Modo de apêndice (append) para adicionar ao final do arquivo
        if (file.is_open()) {
            file << "Senha gerada: " << password << std::endl;
            file.close();
            std::cout << "Senha salva no arquivo 'senha.txt'." << std::endl;
        } else {
            std::cout << "Erro ao criar o arquivo." << std::endl;
        }
    }
 
    std::cout << "\nDigite /q para fechar o programa: ";
    std::string input;
    std::cin >> input;

    if (input == "/q") {
        // O usuário digitou "/q", então o programa irá encerrar
        return 0;
    }

    return 0;
}
