//======================================================================
//  comptty
//    Author: Dave Freese, W1HKJ <w1hkj@w1hkj.com>
//
//  based on the program RTTY Compare by
//    Alex Shovkoplyas, VE3NEA ve3nea@dxatlas.com
//  Original written in Pascal and distributed only for Windows OS
//
//  This program is distributed under the GPL license
//======================================================================

#include "comp_tty.h"

unsigned char BaudotTable[256];

string Encode(string S)
{
	unsigned char Byte;

//massage input string
	for (size_t i = 0; i < S.length(); i++)
		S[i] = toupper(S[i]);

	for (size_t i = 0; i < S.length(); i++)
		if ( (S[i] == ' ') || (S[i] == 0x0a) || (S[i] == 0x0d) || (S[i] == '0') )
			S[i] = '_';

//remove CR, LF, LTRS, FIGS, and Space
	size_t p;
	while( (p = S.find('_')) != string::npos) S.erase(p,1);

//MMTTY specific (S-Bell assumed)
	while( (p = S.find('"')) != string::npos) S.replace(p,1,"+");
	while( (p = S.find(';')) != string::npos) S.replace(p,1,"=");

  //MixW specific
	while( (p = S.find('J')) != string::npos) S.replace(p,1,"'");
	while( (p = S.find('S')) != string::npos) S.replace(p,1,"'");

	string result;

//encode message
	for (size_t i = 0; i < S.length(); i++) {
		Byte = BaudotTable[static_cast<int>(S[i])];
		if (Byte == 0xFF)
			printf("\nerror: Character not in Baudot table: %4x\n", S[i]);
		else
			result += Byte & 0x1F;
	}
	return result;
}

void PrepareBaudotTable() {
	string BaudotChars;
	BaudotChars.append ("°E|A_S");
	BaudotChars.append ("IU¦DRJNFCKTZLWHYPQOBG«MXV»");
	BaudotChars.append ("°3|-_'");
	BaudotChars.append ("87¦$4*,!:(5+)2#6Ø19?&«./=»");

	for (size_t i = 0; i < sizeof(BaudotTable); i++) BaudotTable[i] = 0xFF;
	for (size_t i = 0; i < 64;  i++)
		BaudotTable[static_cast<int>(BaudotChars[i])] = i;
}


void comp_tty(string ref_file, string comp_file, string &results)
{
	results.clear();
	if (ref_file.empty() || comp_file.empty()) return;

	PrepareBaudotTable();

	string sent = "";
	string rcvd = "";
	char ch;
	ifstream f1;
	f1.open(ref_file.c_str(), ios::binary);
	while (f1) {
		f1.get(ch);
		if (f1 && ch) sent += ch;
	}
	f1.close();
	sent = Encode(sent);

	ifstream f2;
	f2.open(comp_file.c_str(), ios::binary);
	while (f2) {
		f2.get(ch);
		if (f2 && ch) rcvd += ch;
	}
	f2.close();
	rcvd = Encode(rcvd);

	if (sent.empty() || rcvd.empty()) return;

	int error_count = Compare(sent, rcvd);

	double ber = 1.0 * error_count / (8.0 * sent.length());
	double cer = 1.0 - pow((1.0 - ber), 8.0);

	char temp[200];

	snprintf(temp, sizeof(temp), "Chars: %d, Errors: %d, CER: %5.4f, BER: %5.4f",
		(int)sent.length(), error_count, cer, ber);
	results = temp;
//	cout << temp << "\n";
}

int Compare(string sent, string rcvd)
{
//missing or extra char is most likely a single bit error
//thus Weights[true] <- 1
// in original Pascal program RTTYcompare the second array is never used
//	int Weights[] = { 1, 1 };
//	int Weights[] = { 1, 5 };

	if (sent == rcvd) return 0;

	string s1 = sent;
	string s2 = rcvd;

	int CerDistance[32] = {
		0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

	int *distance = CerDistance;

	vector<int> Row1(s1.length() + 1, 0);
	vector<int> Row2(s1.length() + 1, 0);

	int T, L, D;

//dynamic programming algorithm

	for (size_t i = 1; i < Row2.size(); i++)
		Row2[i] = Row2[i-1] + 1;

	for (size_t r = 0; r < s2.length(); r++) {
		Row1 = Row2;
		Row2.clear();
		for (size_t i = 0; i < s1.length() + 1; i++)
			Row2.push_back(0);
		Row2[0] = r + 1;
		for (size_t s = 1; s < Row2.size(); s++) {
			D = Row1[s-1] + distance[(s1[s-1] ^ s2[r])];
			L = Row2[s-1] + 1;
			T = Row1[s];
			Row2[s] = min(L, min(T, D));
		}
	}

	return Row2[Row2.size() - 1];
}
