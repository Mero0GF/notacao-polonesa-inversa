#include <iostream>
#include <string>

using namespace std;

const int STACK_CAPACITY = 4;

struct Stack
{
	int count;
	char elements[STACK_CAPACITY]; 
};

Stack create(){ // Coloca o valor \0 em todos os index da pilha
    Stack stack;
    stack.count = 0;
    for (int i = 0;i < STACK_CAPACITY;i++){
        stack.elements[i] = '\0';
    }
    return stack;
}

bool push(Stack &stack, char e){ // Empurra um elemento para cima da pilha
    if (stack.count == STACK_CAPACITY){
        return false;
    }
    else{
        stack.elements[stack.count] = e;
        stack.count++;
        return true;
    } 
}

char pop(Stack &stack){ // Apaga o ultimo elemento colocado na pilha
    if (stack.count == 0){
        return false;
    }
    char value = stack.elements[stack.count-1];
    stack.elements[stack.count-1] = '\0'; 
    stack.count--;
    return value;
}

char top(Stack &stack){ // Checa o valor da do ultimo elemento da pilha
    if (stack.count == 0){
        return '\0';
    }
    return stack.elements[stack.count-1];
}

void print_top(Stack &stack) { // Apenas printa o valor do ultimo elemento para o usuario
    char topo = top(stack);
    if (topo == '\0')
        cout << "Pilha vazia. \n";
    else
        cout << "Topo da pilha: " << topo << '\n';
}

int count_stack(Stack &stack){ // Retorna quantos elementos a pilha possui
    if (stack.count > 0){
        return stack.count;
    }
    else{
        cout << "A pilha nao possui elementos.";
        return 0;
    }
}

void print_count(Stack &stack){ // Printa para o usuario quantos elementos a pilha possui
    int count = count_stack(stack);
    cout << "Quantidade de elementos na pilha: " << count << "\n";
}

bool is_empty(Stack &stack){ // Checa se a pilha esta vazia
    return stack.count == 0;
}

int size(Stack &stack){
    return STACK_CAPACITY;
}

const char alfabeto[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                           'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                           'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

const char operators[5] = {'+', '*', '/', '^', '-'};

string variable_substitution(string &equation,char letter,char value){
  for (int i = 0;i < equation.length();i++){
    if (toupper(equation[i]) == letter){
      equation[i] = value;
    }
  }
  return equation;
}

string posfixa(Stack &stack,string equation,string output){
  for (int i = 0;i < equation.length();i++){
    cout << "topo da pilha: " << top(stack) << "\n";
    if ((equation[i] != '+') && (equation[i] != '^') &&(equation[i] != '-') &&(equation[i] != '/') &&(equation[i] != '*') &&(equation[i] != '(') &&(equation[i] != ')') && (equation[i] != ' ')){
      output = output + equation[i];
    }
    else{
      if (stack.count == 0){
        push(stack,equation[i]);
      }
      else if (equation[i] == '('){
        push(stack,equation[i]);
      }
      else if ((equation[i] == '*') ||(equation[i] == '/')){
        if ((top(stack) == '*') ||(top(stack) == '/')){
          output = output + pop(stack);
        }
        push(stack,equation[i]);
      }
      else if ((equation[i] == '+') ||(equation[i] == '-')){
        if ((top(stack) == '*') ||(top(stack) == '/') ||(top(stack) == '+') ||(top(stack) == '-')){
          output = output + pop(stack);
        }
        push(stack,equation[i]);
      }
      else if (equation[i] == ')'){
        while (top(stack) != '('){
          output = output + pop(stack);
        }
        pop(stack);
      }
    }
  }
  for (int i = 0;i < STACK_CAPACITY;i++){
    if (stack.count == 0){
      break;
    }
    output = output + pop(stack);
  }
  return output;
}

int main() {
  bool flag = false;
  char value;
  int entry,num;
  string equation = "",equation_new,output;
  Stack stack = create();
  cout << "-------------------- Bem-vindo ao sistema! --------------------\n";
  while (true){
    cout << "Escolha uma das opcoes abaixo:\n" << "1. Entrada da expressão aritmética na notação infixa.\n2. Entrada dos valores numéricos associados às variáveis.\n3. Conversão da expressão, da notação infixa para a notação posfixa, e exibição da expressão convertida para posfixa.\n4. Avaliação da expressão (apresentação do resultado do cálculo, mostrando a expressão e os valores das variáveis).\n5. Encerramento do programa.\n";
    cin >> entry;
    if (entry == 1){
      cout << "Digite sua equacao:\n";
      cin.ignore(256,'\n');
      getline(cin,equation);
      for (int i = 0;i < equation.length();i++){
        equation[i] = toupper(equation[i]);
      }
      cout << equation << '\n';
    }
    else if(entry == 2){
      if (equation == "") cout << "Nao ha uma equacao definida para isso.";
      for(int i = 0;i < equation.length();i++){
        for (int j = 0;j < 26;j++){
          if (toupper(equation[i]) == alfabeto[j]){
            cout << "Digite o valor de " << alfabeto[j] << ":";
            cin >> value;
            equation_new = variable_substitution(equation,alfabeto[j],value);
          }
        }
      }
      cout << equation_new << "\n";
    }
    else if(entry == 3){
      cout << "Expressao inicial:" << equation << "\n";
      output = posfixa(stack,equation,output);
      cout << "Expressao posfixa:" << output << "\n";
    }
    else if(entry == 4){
      int a = a;
    }
    else if (entry == 5){
      cout << "Fechando terminal...";
      break;
    }
    else{
      cout << "Digite uma opcao valida.\n";
    }
  }
}