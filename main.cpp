#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>


using namespace std;

bool contem_string(std::string primeira_string, std::string segunda_string)
{
	//SE O SEGUNDO É MAIOR QUE O PRIMEIRO É DIFERENTE
	if(segunda_string.size() > primeira_string.size())
		return false;

	//VERIFICA SE O SEGUNDO CONTÉM NO PRIMEIRO
	for (int i = 0; i < primeira_string.size(); i++)
	{
		int j = 0;
		if(primeira_string[i] == segunda_string[j])
		{
			while (primeira_string[i] == segunda_string[j] && j < segunda_string.size())
			{
				j++;
				i++;
			}

			if (j == segunda_string.size())
				return true;
		}
	}
	return false;
}

int main(int argc, char** argv)
{

	string conjuntoCaracteres = "abcdefghijklmnopqrstuvwxyzABCDEF";
	string conjuntoNumeros = "0123456789";


	string palavra = "";
	string palavra_aux = "";
	//PONTEIRO PARA LER O ARQUIVO COMO ARGUMENTO
	char* nome_arquivo;

	//TIPO PARA MANIPULAR ARQUIVO
	ifstream leitura_arquivo;

	char caracter;


	if(argc > 1)
	{
		//PEGA O PRIMEIRO ARGUMENTO DO PROMPT DE COMANDO(NOME DO ARQUIVO + EXTENSÃO)
		nome_arquivo = argv[1];
		//ABRE O ARQUIVO EM MEMÓRIA
		leitura_arquivo.open(nome_arquivo);

		//SE NÃO CONSEGUIU LER O ARQUIVO OU O ARQUIVO NÃO POSSUIR A EXTENSÃO .pas
		//ENTÃO O ARQUIVO ESTÁ INCORRETO
		if(!leitura_arquivo.is_open() || !contem_string(nome_arquivo, ".pas"))
		{
			cout << "ARQUIVO NAO EXISTE OU NOME DO ARQUIVO INCORRETO (EXTENSAO .pas NECESSARIA)";
			leitura_arquivo.clear();
			return 1;
		}

	}
	else
	{
		cout << "ERRO - ARQUIVO ESPERADO";
		return 1;
	}

	//ENQUANTO TIVER CARACTERE NO ARQUIVO, LE 1 POR 1
	while(leitura_arquivo.get(caracter))
	{
		cout << caracter;
		getchar();
		//UTILIZA A VARIAVEL AUXILIAR PARA VER SE POSSUI ESPAÇO OU ENTER
		//SE NÃO POSSUI ATRIBUI O CARACTER A PALAVRA ORIGINAL
		//SE POSSUI ZERA A PALAVRA AUXILIAR
		cout << palavra_aux;
		if(!contem_string(palavra_aux, "\n") || !contem_string(palavra_aux, " "))
		{
			palavra = palavra + caracter;
		}
		else{
			cout << palavra;
			cout << "\n" << "FIM PALAVRA";
			palavra_aux = "";
			getchar();
		}

	}



	return 0;
}
