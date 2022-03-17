#include<iostream>
#include<string>
#include<sstream>
#include<math.h>
using namespace std;

string toBinary(int n) {
	string r;
	while (n != 0) {
		r = (n % 2 == 0 ? "0" : "1") + r;
		n /= 2;
	}
	return r;

}

string* getVet_octetos(string entrada) {
	for (int i = 0; i < entrada.size(); i++) {
		if (entrada[i] == '.')
			entrada[i] = ' ';
	}
	stringstream ss(entrada);
	string word;
	int cont = 0;
	string* vet = new string[4];
	while (ss >> word) {
		vet[cont] = word;
		cont++;
	}
	return vet;
}
bool validarEndereco(string entrada) { // retorna true para invalido
	for (int i = 0; i < entrada.size(); i++) {
		if (entrada[i] == '.')
			entrada[i] = ' ';
	}
	stringstream ss(entrada);
	string word;
	int cont = 0;
	while (ss >> word) {


		cont++;
		if (cont > 4)
			return 1;
		if (word[0] == '0' && (word.size() > 1))
			return 1;

		int num = atoi(word.c_str());
		if (num > 255)
			return 1;
		if (word.size() > 3)
			return 1;

	}
	if (cont < 4)
		return 1;
	return 0;
}
bool validaMascaraCidr(string mascara) {
	if (mascara[0] != '/')
		return 1;

	int num = atoi(mascara.substr(1, mascara.size()).c_str());

	if (num < 0 || num > 31)
		return 1;
	return 0;

}
bool validaMascaraDecimal(string mascara) { // retorna true para invalida
	for (int i = 0; i < mascara.size(); i++) {
		if (mascara[i] == '.')
			mascara[i] = ' ';
	}
	stringstream ss(mascara);
	string word;
	int cont = 0;
	while (ss >> word) {


		cont++;
		if (cont > 4)
			return 1;
		if (word[0] == '0' && word.size() > 1)
			return 1;

		int num = atoi(word.c_str());
		if (num > 255)
			return 1;
		if (word.size() > 3)
			return 1;
		int word_num = stoi(word);
		string binario = toBinary(word_num);

		bool flag = false;
		for (int k = 0; k < binario.size(); k++)
		{
			if (binario[k] == '0')
				flag = true;
			if (binario[k] == '1' && flag)
				return 1;
		}
	}
	if (cont < 4)
		return 1;
	return 0;

}
string getClasseByPrimeroOcteto(string primeiro_octeto)
{
	int num = atoi(primeiro_octeto.c_str());
	if (num <= 127)
		return "A";
	if (num <= 191)
		return "B";
	if (num <= 233)
		return "C";
	if (num <= 239)
		return "D";
	return "E";
}
string getDecimalByCidr(int mascara_num)
{
	string decimal = "";
	int qtd_inteiro = mascara_num / 8;

	int quebrado = mascara_num % 8;

	for (int i = 0; i < qtd_inteiro; ++i) {
		decimal += "255.";
	}
	string binario = "";
	for (int i = 0; i < quebrado; ++i) {
		binario += "1";
	}
	for (int i = 0; i < (8 - quebrado); ++i) {
		binario += "0";
	}

	int bin_num = stoi(binario, 0, 2);

	decimal += to_string(bin_num);
	for (int i = 0; i < (4 - qtd_inteiro) - 1; ++i) {
		decimal += ".0";
	}
	return decimal;
}


string getRede(string octeto, int quebrados) {
	int	oct_num = stoi(octeto);
	string bin = toBinary(oct_num);
	for (int i = quebrados; i < bin.size(); i++) {
		bin[i] = '0';
	}

	int bin_num = stoi(bin, 0, 2);
	return to_string(bin_num);
	
}
string getBroadCast(string octeto, int quebrados) {
	int	oct_num = stoi(octeto);
	string bin = toBinary(oct_num);

	while (bin.size() < 8) {
		bin = '0' + bin;
	}
	for (int i = quebrados; i < 8; i++) {
		bin[i] = '1';
	}

	int bin_num = stoi(bin, 0, 2);
	return to_string(bin_num);
}
int main() {

	cout << "DIGITE 1 PARA ENDERECAMENTO COM CLASSES OU 0 PARA ENDERECAMENTO SEM CLASSES\n";
	int c;
	cin >> c;
	string* vet_octetos = new string[4];
	while (c != 0 && c != 1) {
		cout << "ENTRADA INVALIDA< DIGITE 1 PARA ENDERECAMENTO COM CLASSES OU 0 PARA ENDERECAMENTO SEM CLASSES\n";
		cin >> c;
	}
	if (c == 1) // com classes
	{
		string entrada;
		cout << "DIGITE O ENDERECO IPV4 SEPARANDO OS OCTETOS COM PONTO\n";
		cin >> entrada;
		bool invalido = false;
		invalido = validarEndereco(entrada);
		while (invalido) {
			cout << "ENTRADA INVALIDA! ";
			cout << "DIGITE O ENDERECO IPV4 SEPARANDO OS OCTETOS COM PONTO\n";
			cin >> entrada;
			invalido = validarEndereco(entrada);
		}
		// entrada com classes validada
		string* vet = getVet_octetos(entrada);

		string primeiro_octeto = vet[0];
		string classe = getClasseByPrimeroOcteto(primeiro_octeto);
		if (classe == "A") {
			cout << "CLASSE A DO ENDERECO IPV4" << endl;
			cout << "MASCARA NOTACAO CIDR : /8" << endl;
			cout << "NUMERO DE HOSTS POR REDE: " << "16777214" << endl;
			cout << "MASCARA NOTACAO DECIMAL: 255.0.0.0" << endl;
			cout << "ENDERECO DE REDE: " << vet[0] << ".0.0.0" << endl;
			cout << "ENDERECO INICIAL UTILIZAVEL: " << vet[0] << ".0.0.1" << endl;
			cout << "ENDERECO DE BROADCAST: " << vet[0] << ".255.255.255" << endl;
			cout << "ENDERECO FINAL UTILIZAVEL: " << vet[0] << ".255.255.254" << endl;

		}
		else if (classe == "B") {
			cout << "CLASSE B DO ENDERECO IPV4" << endl;
			cout << "MASCARA NOTACAO CIDR : /16" << endl;
			cout << "MASCARA NOTACAO DECIMAL: 255.255.0.0" << endl;
			cout << "NUMERO DE HOSTS POR REDE: " << pow(2, 32 - 16) - 2 << endl;
			cout << "ENDERECO DE REDE: " << vet[0] << "." << vet[1] << ".0.0" << endl;
			cout << "ENDERECO INICIAL UTILIZAVEL: " << vet[0] << "." << vet[1] << ".0.1" << endl;
			cout << "ENDERECO DE BROADCAST: " << vet[0] << "." << vet[1] << ".255.255" << endl;
			cout << "ENDERECO FINAL UTILIZAVEL: " << vet[0] << "." << vet[1] << ".255.254" << endl;
		}
		else if (classe == "C") {
			cout << "CLASSE C DO ENDERECO IPV4" << endl;
			cout << "MASCARA NOTACAO CIDR : /24" << endl;
			cout << "MASCARA NOTACAO DECIMAL: 255.255.255.0" << endl;
			cout << "NUMERO DE HOSTS POR REDE: " << pow(2, 32 - 24) - 2 << endl;
			cout << "ENDERECO DE REDE: " << vet[0] << "." << vet[1] << "." << vet[2] << ".0" << endl;
			cout << "ENDERECO INICIAL UTILIZAVEL: " << vet[0] << "." << vet[1] << "." << vet[2] << ".1" << endl;
			cout << "ENDERECO DE BROADCAST: " << vet[0] << "." << vet[1] << "." << vet[2] << ".255" << endl;
			cout << "ENDERECO FINAL UTILIZAVEL " << vet[0] << "." << vet[1] << "." << vet[2] << ".254" << endl;
		}
		else if (classe == "D") {
			cout << "CLASSE D DO ENDERECO IPV4" << endl;

		}
		else { // E
			cout << "CLASSE E DO ENDERECO IPV4" << endl;
		}
	}
	else { // sem classe

		cout << "DIGITE 1 PARA MASCARA NA NOTACAO DECIMAL E 0 PARA NOTACAO CIDR\n";
		int m;
		cin >> m;
		while (m != 0 && m != 1) {
			cout << "ENTRADA INVALIDA! DIGITE 1 PARA MASCARA NA NOTACAO DECIMAL E 0 PARA NOTACAO CIDR\n";
			cin >> m;
		}
		if (m == 1) { //notacao decimal
			string entrada;
			cout << "DIGITE O ENDERECO IPV4 SEPARANDO OS OCTETOS COM PONTO\n";
			cin >> entrada;
			bool invalido = false;
			invalido = validarEndereco(entrada);
			while (invalido) {
				cout << "ENTRADA INVALIDA! ";
				cout << "DIGITE O ENDERECO IPV4 SEPARANDO OS OCTETOS COM PONTO\n";
				cin >> entrada;
				invalido = validarEndereco(entrada);
			}
			// entrada validada
			string mascara;
			cout << "DIGITE A MASCARA NO FORMADO DECIMAL(n.n.n.n)\n";
			cin >> mascara;
			int mascara_decimal_invalida = validaMascaraDecimal(mascara);
			while (mascara_decimal_invalida)
			{
				cout<< "MASCARA INVALIDA! DIGITE A MASCARA NO FORMADO DECIMAL(n.n.n.n)\n";
				cin >> mascara;
				mascara_decimal_invalida = validaMascaraDecimal(mascara);
			}
			// mascara decimal validada
			string* vet = getVet_octetos(mascara);
			int mascara_cidr = 0;
			for (int v = 0; v < 4; v++) {
				string bin = toBinary(stoi(vet[v]));
				for (int b = 0; b < bin.size(); b++) {
					if (bin[b] == '1')
						mascara_cidr++;
				}
			}
			cout << "MASCARA NA NOTACAO CIDR: /" << mascara_cidr << endl;
			cout << "NUMERO DE HOSTS DA SUBREDE: " << pow(2, 32 - mascara_cidr) - 2 << endl;

			vet = getVet_octetos(entrada);
			int pos = mascara_cidr / 8;
			string rede = getRede(vet[pos], mascara_cidr % 8);
			cout << "ENDERECO REDE: ";
			for (int i = 0; i < pos; i++) {
				cout << vet[i] << ".";
			}
			cout << rede;
			for (int i = pos + 1; i < 4; i++) {
				cout << ".0";
			}
			cout << endl;

			string bradcast = getBroadCast(vet[pos], mascara_cidr % 8);

			cout << "ENDERECO BROADCAST: ";
			for (int i = 0; i < pos; i++) {
				cout << vet[i] << ".";
			}
			cout << bradcast;
			for (int i = pos + 1; i < 4; i++) {
				cout << ".255";
			}
			cout << endl;


			cout << "PRIMEIRO ENDERECO UTILIZAVEL: ";
			for (int i = 0; i < pos; i++) {
				cout << vet[i] << ".";
			}
			if (pos + 1 >= 4)
				cout << stoi(rede) + 1;
			else {
				cout << rede;
				for (int i = pos + 1; i < 4; i++) {
					i == 3 ? cout << ".1" : cout << ".0";
				}
			}
			cout << endl;


			cout << "ULTIMO ENDERECO UTILIZAVEL ";
			for (int i = 0; i < pos; i++) {
				cout << vet[i] << ".";
			}
			if (pos + 1 >= 4)
				cout << stoi(bradcast) - 1;
			else {
				cout << bradcast;
				for (int i = pos + 1; i < 4; i++) {
					i == 3 ? cout << ".254" : cout << ".255";
				}
				cout << endl;
			}


		}
		else { // notacao cidr
			string entrada;
			cout << "DIGITE O ENDERECO IPV4 SEPARANDO OS OCTETOS COM PONTO\n";
			cin >> entrada;
			bool invalido = false;
			invalido = validarEndereco(entrada);
			while (invalido) {
				cout << "ENTRADA INVALIDA! ";
				cout << "DIGITE O ENDERECO IPV4 SEPARANDO OS OCTETOS COM PONTO\n";
				cin >> entrada;
				invalido = validarEndereco(entrada);
			}
			string mascara;
			cout << "DIGITE A MASCARA NA NOTACAO CIDR (/n) \n";
			cin >> mascara;
			bool is_mascara_invalida = validaMascaraCidr(mascara);
			while (is_mascara_invalida) {
				cout << "MASCARA INVALIDA! DIGITE A MASCARA NA NOTACAO CIDR (/n) \n";


				cin >> mascara;

				is_mascara_invalida = validaMascaraCidr(mascara);
			}
			// mascara validada

			int mascara_num = atoi(mascara.substr(1, mascara.size()).c_str());
			string notacao_decimal = getDecimalByCidr(mascara_num);
			cout << "NOTACAO DECIMAL: " << notacao_decimal << endl;
			cout << "NUMERO DE HOSTS DA SUBREDE: " << pow(2, 32 - mascara_num) - 2 << endl;
			string* vet = getVet_octetos(entrada);
			int pos = mascara_num / 8;
			string rede = getRede(vet[pos], mascara_num%8);
			cout << "ENDERECO REDE: ";
			for (int i = 0; i < pos; i++) {
				cout << vet[i] << ".";
			}
			cout << rede;
			for (int i = pos + 1; i < 4; i++) {
				cout << ".0";
			}
			cout << endl;

			string bradcast = getBroadCast(vet[pos], mascara_num % 8);

			cout << "ENDERECO BROADCAST: ";
			for (int i = 0; i < pos; i++) {
				cout << vet[i] << ".";
			}
			cout << bradcast;
			for (int i = pos + 1; i < 4; i++) {
				cout << ".255";
			}
			cout << endl;


			cout << "PRIMEIRO ENDERECO UTILIZAVEL: ";
			for (int i = 0; i < pos; i++) {
				cout << vet[i] << ".";
			}
			if (pos + 1 >= 4)
				cout << stoi(rede) + 1;
			else {
				cout << rede;
				for (int i = pos + 1; i < 4; i++) {
					i == 3? cout<<".1" : cout << ".0";
				}
			}
			cout << endl;


			cout << "ULTIMO ENDERECO UTILIZAVEL ";
			for (int i = 0; i < pos; i++) {
				cout << vet[i] << ".";
			}
			if (pos + 1 >= 4)
				cout << stoi(bradcast) - 1;
			else {
				cout << bradcast;
				for (int i = pos + 1; i < 4; i++) {
					i == 3 ? cout << ".254" : cout << ".255";
				}
				cout << endl;
			}

		}

	}
}
