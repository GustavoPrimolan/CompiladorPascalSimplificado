#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <list>
#include <ctype.h>
#include <algorithm>

using namespace std;

bool contemString(std::string primeiraString, std::string segundaString)
{
	//SE O SEGUNDO � MAIOR QUE O PRIMEIRO � DIFERENTE
	if(segundaString.size() > primeiraString.size())
		return false;

	//VERIFICA SE O SEGUNDO CONT�M NO PRIMEIRO
	for (int i = 0; i < primeiraString.size(); i++)
	{
		int j = 0;
		if(primeiraString[i] == segundaString[j])
		{
			while (primeiraString[i] == segundaString[j] && j < segundaString.size())
			{
				j++;
				i++;
			}

			if (j == segundaString.size())
				return true;
		}
	}
	return false;
};

bool contemString(std::string primeiraString, char segundaString)
{

	//VERIFICA SE O SEGUNDO CONT�M NO PRIMEIRO
	for (int i = 0; i < primeiraString.size(); i++)
	{
		if(primeiraString[i] == segundaString)
		{
			return true;
		}

	}
	return false;
};

class Token
{

private:
	string n;
	string t;

public:
	void inicializa(string nome, string tipo)
	{
		n = nome;
		t = tipo;
	}

	string getNome()
	{
		return n;
	}

	string getTipo()
	{
		return t;
	}


};


list <Token> listaTokens;
string caracteres = "ABCDEFGHIJKLMNOPQRSTUVXYWZ";
string digitos = "1234567890";



class AnalisadorLexico
{

public:

	/*
		PALAVRARESERVADA
			(ABSOLUTE ARRAY BEGIN CASE CHAR CONST DIV DO DOWTO ELSE END
			EXTERNAL FILE FOR FORWARD FUNC FUNCTION GOTO IF IMPLEMENTATION IN
			INTEGER INTERFACE INTERRUPT LABEL MAIN NIL NIT OF PACKED PROC
			PROGRAM REAL RECORD REPEAT SET SHL SHR STRING THEN TO TYPE UNIT
			UNTIL USES VAR WHILE WITH XOR)


		SIMBOLOESPECIAL
			(�(�, �)�, �,�, �;�, �:�)



		ATRIBUICAO
			 (:=)


		OPERADORRELACIONAL
			   	 ( �=�, �>=�, � >�, �<� ,�<=� ,�<>�)



		OPERADORARITIMETICO
					 (�+�, �-, �*�, �/�)


		NUMEROINTEIRO
			 (Ex: 1, 13)


		NUMEROREAL
			(Ex: 1.33, 24.40e-04)


		FIM
			(.)


		IDENTIFICADOR
			 (Ex: x, variavel, i, var2)


	*/

	void reconheceTokens(string cFonte)
	{
		transform(cFonte.begin(), cFonte.end(), cFonte.begin(), ::toupper);
		//cout << cFonte;
		//getchar();




		string palavrasReservadas[] = {"ABSOLUTE", "ARRAY", "BEGIN", "CASE", "CHAR", "CONST", "DIV", "DO",
									   "DOWTO", "ELSE", "END",	"EXTERNAL", "FILE", "FOR", "FORWARD", "FUNC", "FUNCTION",
									   "GOTO", "IF", "IMPLEMENTATION", "IN", "INTEGER", "INTERFACE", "INTERRUPT",
									   "LABEL", "MAIN", "NIL", "NIT", "OF", "PACKED", "PROC", "PROGRAM", "REAL", "RECORD", "REPEAT",
									   "SET", "SHL", "SHR", "STRING", "THEN", "TO", "TYPE", "UNIT", "UNTIL", "USES", "VAR", "WHILE",
									   "WITH", "XOR"
									  };




		string palavra = "";
		string palavraAux = "";




		int estado = 1;

		int i = 0;
		//AUTOMATO PARA RECONHECER OS TOKENS
		while( i < cFonte.size())
		{


			//FAZ A VERFICIA��O DO COMENT�RIO
			if(cFonte[i] == '/' && cFonte[i + 1] == '*')
			{
				//PULA OS DOIS CARACTERES DE COMENT�RIO
				i += 2;
				while((cFonte[i] != '*') && (cFonte[i + 1] != '/'))
				{
					i++;
				}
				//COMO A CONDI��O DO WHILE VAI AT� O CARACTER SER ASTERISCO NOVAMENTE
				//ENT�O ELE IR� SAIR DO WHILE NA POSI��O DO ASTERISCO, SENDO NECESS�RIO
				//PULAR DOIS INDICES NO VETOR PARA QUE SEJA POSS�VEL CONTINUAR DE ONDE
				//PAROU
				i += 2;
				continue;
			}

			Token token;
			//ESTADO 1 DO AUTOMATO
			if(estado == 1)
			{
				//ESTADO 1 E CARACTER LIDO � "="
				//� UM ESTADO FINAL, POR CONTA DISSO SALVA O TOKEN E ARMAZENA NA LISTA
				//N�O TEM NECESSIDADE DE FAZER OUTRA
				if(cFonte[i] == '=')
				{
					palavra = cFonte[i];
					token.inicializa(palavra, "OPERADORRELACIONAL");
					palavra = "";
					estado = 1;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}

				//ESTADO 1 E CARACTER LIDO � ">"
				else if(cFonte[i] == '>')
				{
					palavra = cFonte[i];
					estado = 3;
				}


				//ESTADO 1 E CARACTER LIDO � "<"
				else if(cFonte[i] == '<')
				{
					palavra = cFonte[i];
					estado = 4;

				}


				//ESTADO 1 E CARACTER LIDO � "+","-","*","/"
				else if(cFonte[i] == '+'
						|| cFonte[i] == '-'
						|| cFonte[i] == '*'
						|| cFonte[i] == '/')
				{
					palavra = cFonte[i];
					token.inicializa(palavra, "OPERADORARITIMETICO");
					palavra = "";
					estado = 1;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);

				}


				//ESTADO 1 E CARACTER LIDO � ",", ";", "(", ")"
				else if(cFonte[i] == ','
						|| cFonte[i] == ';'
						|| cFonte[i] == '('
						|| cFonte[i] == ')')
				{
					palavra = cFonte[i];
					token.inicializa(palavra, "SIMBOLOESPECIAL");
					palavra = "";
					estado = 1;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);

				}

				//ESTADO 1 E CARACTER LIDO � ":"
				else if(cFonte[i] == ':')
				{
					palavra = cFonte[i];
					estado = 7;

				}

				//ESTADO 1 E CARACTER LIDO � "."
				else if(cFonte[i] == '.')
				{
					palavra = cFonte[i];
					token.inicializa(palavra, "FIM");
					palavra = "";
					estado = 1;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}

				//ESTADO 1 E CARACTER LIDO � QUALQUER DIGITO --- NUM�RICO INTEIRO
				else if(contemString(digitos, cFonte[i]))
				{
					palavra = cFonte[i];
					estado = 9;

				}



				//ESTADO 1 E CARACTER LIDO � QUALQUER CARACTER --- PALAVRA RESERVADA OU IDENTIFICADOR
				else if(contemString(caracteres, cFonte[i]))
				{
					palavra = cFonte[i];
					estado = 11;
				}


			}

			//ESTADO IGUAL A 3 ENT�O ESPERA O = PARA >=
			else if(estado == 3)
			{

				//ESTADO 3 E CARACTER = VAI SER� RECONHECIDO O ">=" (OPERADOR RELACIONAL)
				if(cFonte[i] == '=')
				{
					palavra = palavra + cFonte[i];
					token.inicializa(palavra, "OPERADORRELACIONAL");
					palavra = "";
					estado = 1;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}

				//SE N�O, IR� SER UM OUTRO TOKEN E POR CONTA DE ESTAR NO CARACTER
				//DE OUTRO TOKEN, � NECESS�RIO VOLTAR 1 NO i
				else
				{
					token.inicializa(palavra, "OPERADORRELACIONAL");
					palavra = "";
					estado = 1;
					i--;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}

			}


			//ESTADO IGUAL A 4
			else if(estado == 4)
			{

				//ESTADO 4 VERFICIA O <=
				if(cFonte[i] == '=')
				{
					palavra = palavra + cFonte[i];
					token.inicializa(palavra, "OPERADORRELACIONAL");
					palavra = "";
					estado = 1;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}

				//VERIFICA O <>
				else if(cFonte[i] == '>')
				{
					palavra = palavra + cFonte[i];
					token.inicializa(palavra, "OPERADORRELACIONAL");
					palavra = "";
					estado = 1;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}

				//SE N�O ELE IR� SER SOMENTO O < E SER� NECESS�RIO VOLTAR UM NO i
				else
				{
					token.inicializa(palavra, "OPERADORRELACIONAL");
					palavra = "";
					estado = 1;
					i--;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}



			}


			//ESTADO 7, VERIFICA :=
			else if(estado == 7)
			{

				//ESTADO 7 E VERIFICA SE � :=
				if(cFonte[i] == '=')
				{
					palavra = palavra + cFonte[i];
					token.inicializa(palavra, "ATRIBUICAO");
					palavra = "";
					estado = 1;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}

				//SE N�O FOR SER� O : E SER� NECESS�RIO VOLTAR O i
				else
				{
					token.inicializa(palavra, "SIMBOLOESPECIAL");
					palavra = "";
					estado = 1;
					i--;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);
				}

			}

			//ESTADO 9
			else if(estado == 9)
			{

				//VERIFICA SE AINDA CONTINUA SENDO DIGITO E PERMANECE NO ESTADO
				if(contemString(digitos, cFonte[i]))
				{
					palavra = palavra + cFonte[i];
				}

				//VERIFICA SE TEM .
				//SE TIVER VAI SER DECIMAL E PORTANTO IR� MUDAR DE ESTADO
				else if(cFonte[i] == '.')
				{
					palavra = palavra + cFonte[i];
					estado = 10;
				}

				//SE N�O FOR NENHUMA DAS OP��ES � POR QUE ACABOU O N�MERO
				//DEVER� SER SALVO NA LISTA DE TOKENS
				//E VOLTAR 1 NO i
				else
				{
					token.inicializa(palavra, "NUMEROINTEIRO");
					palavra = "";
					estado = 1;
					i--;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);


				}

			}

			//ESTADO 10 VERIFICA SE CONTINUA O N�MERO DECIMAL
			else if(estado == 10)
			{

				//SE CONTER DIGITO, CONTINUA CONTANDO E PERMANECE NO ESTADO
				if(contemString(digitos, cFonte[i]))
				{
					palavra = palavra + cFonte[i];

				}

				//SE N�O, SIGNIFICAR� QUE TODOS OS N�MEROS J� FORAM LIDOS
				//ENT�O IR� SALVAR NA LISTA E RETORNAR O i
				else
				{

					token.inicializa(palavra, "NUMEROREAL");
					palavra = "";
					estado = 1;
					i--;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);

				}

			}

			//VERIFICA AS PALAVRAS RESERVADAS E O IDENTIFICADOR
			else if(estado == 11)
			{
				//SE CONTER CARACTER, SER� CONCATENADO NA PALAVRA
				//E ENT�O SER� PROCURADO NO VETOR DE PALAVRAS RESERVADAS
				if(contemString(caracteres, cFonte[i]))
				{
					palavra = palavra + cFonte[i];

				}

				//SE TIVER N�MERO � CERTEZA QUE � IDENTIFICADOR
				else if(contemString(digitos, cFonte[i]))
				{
					palavra = palavra + cFonte[i];
					estado = 12;
				}

				//SE N�O, SE FOR QUALQUER OUTRO CARACTER
				//TERMINOU O IDENTIFICADOR E SER� NECESS�RIO VOLTAR O i
				else
				{
					bool palavraReservada = false;

					//VERIFICA NO VETOR DE PALAVRAS RESERVADAS
					for(int j = 0; j < 49; j++)
					{
						//SE TIVER A PALAVRA RESERVADA
						//SALVA NA LISTA DE TOKENS E JOGA O ESTADO PARA 1
						if(palavra == palavrasReservadas[j])
						{

							token.inicializa(palavra, "PALAVRARESERVADA");
							palavra = "";
							estado = 1;
							//INSERE TOKEN NA LISTA DE TOKENS
							listaTokens.push_back(token);
							palavraReservada = true;
							i--;
							break;

						}

					}

					if(!palavraReservada)
					{
						token.inicializa(palavra, "IDENTIFICADOR");
						palavra = "";
						estado = 1;
						i--;
						//INSERE TOKEN NA LISTA DE TOKENS
						listaTokens.push_back(token);
					}

				}

			}


			else if(estado == 12)
			{
				//VAI CONCATENANDO NA PALAVRA
				if(contemString(caracteres, cFonte[i]) || contemString(digitos, cFonte[i]))
				{
					palavra = palavra + cFonte[i];
				}

				//TERMINOU O IDENTIFICADOR
				else
				{
					token.inicializa(palavra, "IDENTIFICADOR");
					palavra = "";
					estado = 1;
					i--;
					//INSERE TOKEN NA LISTA DE TOKENS
					listaTokens.push_back(token);

				}

			}

			i++;

		}


		for (list<Token>::const_iterator it = listaTokens.begin(); it != listaTokens.end(); ++it)
		{
			Token t = *it;
			cout << t.getNome() << " " << t.getTipo() << "\n";
		}

	}
};


class AnalisadorSintatico
{

public:

	void analisadorRecursivo(list<Token>::const_iterator it, int contador, int opcao){
		
		if(it == listaTokens.end()){
			return;
		}
		
		Token t = *it;
		//cout << "CONTADOR: " << contador  << "\n";
		//cout << "OPCAO: " << opcao  << "\n"; 
		//cout << "TOKEN ATUAL (NOME): " << t.getNome() << "\n";
		//cout << "TOKEN ATUAL (TIPO): " << t.getTipo() << "\n";		
		
		if(contador == 0){
			if(t.getNome() == "PROGRAM"){
				analisadorRecursivo(++(it), contador + 1, 0);
			}else{
				cout << "ERRO\nESPERADO: PROGRAM\nENCONTROU: " + t.getNome();
			}
		}
		
		else if(contador == 1){
			if(t.getTipo() == "IDENTIFICADOR"){
				analisadorRecursivo(++(it), contador +1, 0);
			}else{
				cout << "ERRO\nESPERADO: IDENTIFICADOR\nENCONTROU: " + t.getTipo();
			}
			
		}
		
		else if(contador == 2){
			if(t.getNome() == ";"){
				analisadorRecursivo(++(it), contador+1, 0);
			}else{
				cout << "ERRO\nESPERADO: ;\nENCONTROU: " + t.getNome();
			}
			
		}
		
		else if(contador == 3){
			if(t.getNome() == "VAR"){
				analisadorRecursivo(++(it), contador + 1, 0);
			}else{
				cout << "ERRO\nESPERADO: VAR\nENCONTROU: " + t.getNome();
			}
		}
		
		else if(contador == 4){
			if(t.getTipo() == "IDENTIFICADOR"){
				analisadorRecursivo(++(it), contador+1, 0);
			}else{
				cout << "ERRO\nESPERADO: IDENTIFICADOR\nENCONTROU: " + t.getTipo();
			}
		}
		
		else if(contador == 5){
			if(t.getNome() == ":"){
				analisadorRecursivo(++(it), contador+1, 0);
			}else{
				cout << "ERRO\nESPERADO: :\nENCONTROU: " + t.getNome();
			}
		}
		
		else if(contador == 6){
			if(t.getNome() == "INTEGER" || t.getNome() == "STRING"){
				analisadorRecursivo(++(it), contador+1, 0);
			}else{
				cout << "ERRO\nESPERADO: INTEGER OU STRING\nENCONTROU: " + t.getNome();
			}
		}
		
		else if(contador == 7){
			if(t.getNome() == ";"){
				analisadorRecursivo(++(it), contador+1, 0);
			}else{
				cout << "ERRO\nESPERADO: ;\nENCONTROU: " + t.getNome();
			}
		}
		
		else if(contador == 8){
			if(t.getNome() == "BEGIN"){
				analisadorRecursivo(++(it), contador+1, 0);
			}else{
				cout << "ERRO\nESPERADO: BEGIN\nENCONTROU: " + t.getNome();
			}
		}
		
		else if(contador == 9 && opcao == 0){
			if(t.getNome() == "READ"){
				analisadorRecursivo(++(it), contador+1, 1);
			
			}else if(t.getTipo() == "IDENTIFICADOR"){
				analisadorRecursivo(++(it), contador+1, 0);	
			}else{
				cout << "ERRO\nESPERADO: IDENTIFICADOR OU READ\nENCONTROU: "  + t.getNome();
			}
		}
		
		else if(contador == 10 && opcao == 0){
			if(t.getNome() == ":="){
				analisadorRecursivo(++(it), contador+1, 0);
			}else{
				cout << "ERRO\nESPERADO: :=\nENCONTROU: "  + t.getNome();
			}
			
		}
		
		else if(contador == 10 && opcao == 1){
			if(t.getNome() == "("){
				analisadorRecursivo(++(it), contador+1, 1);
			}else{
				cout << "ERRO\nESPERADO: (\nENCONTROU: "  + t.getNome();
			}
		}
		
		else if(contador == 11 && opcao == 0){
			if(t.getTipo() == "NUMEROREAL" || t.getTipo() == "NUMEROINTEIRO"){
				analisadorRecursivo(++(it), contador+1, 0);
			}
			else{
				cout << "ERRO\nESPERADO: NUMEROREAL OU NUMEROINTEIRO\nENCONTROU: "  + t.getTipo();
			}
		}
		
		else if(contador == 11 && opcao == 1){
			if(t.getTipo() == "IDENTIFICADOR"){
				analisadorRecursivo(++(it), contador+1, 1);
			}else{
				cout << "ERRO\nESPERADO: IDENTIFICADOR\nENCONTROU: "  + t.getTipo();
			}
		}
		
		else if(contador == 12 && opcao == 0){
			if(t.getNome() == ";"){
				analisadorRecursivo(++(it), contador +1, 0);
			}else{
				cout << "ERRO\nESPERADO: ;\nENCONTROU: "  + t.getNome();
			}
			
		}
		
		else if(contador == 12 && opcao == 1){
			if(t.getNome() == ")"){
				analisadorRecursivo(++(it), contador, 0);
			}else{
				cout << "ERRO\nESPERADO: )\nENCONTROU: "  + t.getNome();
			}
		}
		
		else if(contador == 13){
			if(t.getNome() == "END"){
				analisadorRecursivo(++(it), contador+1, 0);
			}else{
				cout << "ERRO\nESPERADO: END\nENCONTROU: "  + t.getNome();
			}
			
		}
		
		else if(contador == 14){
			if(t.getNome() == "."){
				cout << "\n\n\nCOMPILADO";
			}else{
				cout << "ERRO\nESPERADO: .\nENCONTROU: "  + t.getNome();
			}
		}
		
		
		
	}
	
	

};



int main(int argc, char** argv)
{

	AnalisadorLexico analisadorLexico;
	
	AnalisadorSintatico analisadorSintatico;
	
	
	string codigoFonte = "";
	//PONTEIRO PARA LER O ARQUIVO COMO ARGUMENTO
	char* nomeArquivo;

	//TIPO PARA MANIPULAR ARQUIVO
	ifstream leituraArquivo;

	char caracter;


	if(argc > 1)
	{
		//PEGA O PRIMEIRO ARGUMENTO DO PROMPT DE COMANDO(NOME DO ARQUIVO + EXTENS�O)
		nomeArquivo = argv[1];
		//ABRE O ARQUIVO EM MEM�RIA
		leituraArquivo.open(nomeArquivo);

		//SE N�O CONSEGUIU LER O ARQUIVO OU O ARQUIVO N�O POSSUIR A EXTENS�O .pas
		//ENT�O O ARQUIVO EST� INCORRETO
		if(!leituraArquivo.is_open() || !contemString(nomeArquivo, ".pas"))
		{
			cout << "ARQUIVO NAO EXISTE OU NOME DO ARQUIVO INCORRETO (EXTENSAO .pas NECESSARIA)";
			leituraArquivo.clear();
			return 1;
		}

	}
	else
	{
		cout << "ERRO - ARQUIVO ESPERADO";
		return 1;
	}
	string carac;
	//ENQUANTO TIVER CARACTERE NO ARQUIVO, L� 1 POR 1
	while(leituraArquivo.get(caracter))
	{
		//CAPTURA O C�DIGO FONTE INTEIRO QUE EST� NO ARQUIVO
		codigoFonte = codigoFonte + caracter;

	}

	//RECONHECE OS TOKENS NO C�DIGO FONTE
	cout << "\n\n-----------COMECO ANALISADOR LEXICO-----------\n\n";
	
	analisadorLexico.reconheceTokens(codigoFonte);
	
	cout << "\n\n-----------FIM ANALISADOR LEXICO-----------\n\n";
	getchar();
	
	cout << "\n\n-----------COMECO ANALISADOR SINTATICO-----------\n\n";
	analisadorSintatico.analisadorRecursivo(listaTokens.begin(), 0, 0);
	cout << "\n\n-----------FIM ANALISADOR SINTATICO-----------\n\n";
	
	return 0;
}
