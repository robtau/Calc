#include <iostream>
#include <vector>
#include <stack>
class Kalkulator{
public:
unsigned long long int dokl=3;
unsigned long long int dok=100;
void blad_wejscia();
void usage();
void about();
void czysc(std::vector<char> &c);
std::vector <char> parser(std::vector <char> &znaki);
std::vector <char> obliczansko(std::vector <char> &komendy);
bool walidacja(std::vector <char> &znaki);
private:
unsigned long long int przecinek(std::vector<char> &a, std::vector<char> &b);
void wyrownaj(std::vector<char> &a, std::vector<char> &b);
void sprawdz(std::vector<char> &a);
bool czyWieksza(std::vector<char> &a, std::vector<char> &b);
std::vector<char> dodaj(std::vector<char> a, std::vector<char> b);
std::vector<char> odejmij(std::vector<char> a, std::vector<char> b);
std::vector<char> pomnoz(std::vector<char> a, std::vector<char> b);
std::vector <char> dzialanie(std::vector <char> a, std::vector <char> b, char znak);
std::vector<char> podziel(std::vector<char> a, std::vector<char> b);
};
int main(){
	std::ios::sync_with_stdio(false);
	setlocale(LC_ALL, "polish");
	Kalkulator calc;
    std::string komendy;
    std::cout<<"W razie wątpliwości wpisz 'help'"<<std::endl;
    while(true){
    bool cinek=false;
    unsigned long long int j=0;
    std::cout<<"\nWprowadź polecenie:"<<std::endl;
    std::cin>>komendy;
    if (komendy == "exit" || komendy == "q" || komendy == "quit")
        break;
    else if(komendy== "usage" || komendy=="manual" || komendy=="man" || komendy=="?" || komendy=="help")
        calc.usage();
    else if(komendy=="about")
        calc.about();
    else if(komendy=="dokl"){
    	std::cout << "Podaj nową dokładność wyniku: \n";
    	std::cin >> calc.dokl;
    	std::cout << "Podaj nową dokładność dzielenia: \n";
    	std::cin >> calc.dok;}
    else if(komendy=="clear" || komendy =="cls")
        system("cls");
    else{
        std::vector<char>znaki(komendy.begin(),komendy.end());
        komendy.erase();
        if(!calc.walidacja(znaki)){
            calc.blad_wejscia();
            continue;
        }
        znaki = calc.parser(znaki);
        znaki = calc.obliczansko(znaki);
        std::vector<char> wynik;
        for (auto i:znaki){
            if(i==',')
                cinek=true;
            else if(cinek && j>calc.dokl)
                break;
            if (cinek)
                j++;
            wynik.push_back(i);
    	}
    calc.czysc(wynik);
    for(auto i:wynik) std::cout << i;
    std::cout<<std::endl;
    }
}
return 0;
}
std::vector <char> Kalkulator::dzialanie(std::vector <char> a, std::vector <char> b, char znak){
    bool minusik1=false,minusik2=false;
    std::vector <char> wynik;
    if (a[0]=='-'){
        a.erase(a.begin());
        minusik1=true;}
    if (b[0]=='-'){
        b.erase(b.begin());
        minusik2=true;}
    if(znak=='+'){
        if (minusik1^minusik2)
            return odejmij(a,b);
        else
			wynik=dodaj(a,b);
		if(minusik1 && minusik2)
            wynik.insert(wynik.begin(),'-');
        return wynik;
    }
    else if(znak=='-'){
    	wynik=dodaj(a,b);
        if (minusik1 && !minusik2)
            wynik.insert(wynik.begin(),'-');
        else if(!(minusik1^minusik2))
            return odejmij(a,b);
        return wynik;
    }
    else if(znak=='*'){
    	wynik = pomnoz(a,b);
        if(minusik1^minusik2)
            wynik.insert(wynik.begin(),'-');
        return wynik;
    }
    else if(znak=='/'){
    	wynik = podziel(a,b);
        if(minusik1^minusik2)
            wynik.insert(wynik.begin(),'-');
        return wynik;
    }
    return {{0}};
}
std::vector <char> Kalkulator::parser(std::vector <char> &znaki){
    std::vector <char> wynik;
    std::stack <char> stos;
    for (unsigned long long int i=0;i<static_cast<unsigned long long int>(znaki.size());i++){
        if (znaki[i]=='('){
                stos.push(znaki[i]);
        }
        else if(znaki[i]==')'){
            while (stos.top()!='('){
                    wynik.push_back(stos.top());
                    stos.pop();
                }
            stos.pop();
        }
        else if(znaki[i]=='-' || znaki[i]=='+' || znaki[i]=='/' || znaki[i]=='*'){
            if(znaki[i]=='-'&&znaki[i-1]=='(')
               wynik.push_back('0');
            wynik.push_back('c');
            if(stos.empty() || ((znaki[i]=='/' || znaki[i]=='*')&&(stos.top()=='+' || stos.top()=='-' || stos.top()=='(')) || ((znaki[i]=='+' || znaki[i]=='-')&&stos.top()=='('))
                stos.push(znaki[i]);
            else{
                while(!(stos.empty() || ((znaki[i]=='/' || znaki[i]=='*')&&(stos.top()=='+' || stos.top()=='-' || stos.top()=='(')) || ((znaki[i]=='+' || znaki[i]=='-')&&stos.top()=='('))){
                    wynik.push_back(stos.top());
                    stos.pop();
                }
                stos.push(znaki[i]);
            }
        }
        else
            wynik.push_back(znaki[i]);
    }
    wynik.push_back('c');
if(!(stos.empty()))
    for (unsigned long long int i=0;i<=static_cast<unsigned long long int>(stos.size());i++){
        wynik.push_back(stos.top());
        stos.pop();
        }
    return wynik;
}
std::vector <char> Kalkulator::obliczansko(std::vector <char> &komendy){
    std::stack <std::vector<char>> stos;
    stos.push({{'0'}});
    std::vector <char> a,b,c;
    for (unsigned long long int i=0;i<static_cast<unsigned long long int>(komendy.size());i++){
        if(komendy[i]=='-' || komendy[i]=='+' || komendy[i]=='/' || komendy[i]=='*'){
            a=stos.top();
            stos.pop();
            b=stos.top();
            stos.pop();
            stos.push(dzialanie(b,a,komendy[i]));
            b.clear();
            a.clear();
        }
        else if (komendy[i]=='c')
            continue;
        else{
            while(komendy[i]!='c'){
                if(komendy[i]=='-' || komendy[i]=='+' || komendy[i]=='/' || komendy[i]=='*'){
                    i--;
                    break;
                }
                else{
                    c.push_back(komendy[i]);
                    i++;
                }
            }
            stos.push(c);
            c.clear();
        }
    }
    return stos.top();
}
bool Kalkulator::walidacja(std::vector <char> &znaki){
    bool przecinek=false;
    long long nawiasy=0;
    for(unsigned long long int i=0;i<static_cast<unsigned long long int>(znaki.size());i++){
        if (nawiasy<0)
            return false;
        if (!(znaki[i]=='-' || znaki[i]=='+' || znaki[i]=='/' || znaki[i]=='*' || znaki[i]=='(' || znaki[i]==')' || znaki[i]==',' || (znaki[i]>=48 && znaki[i]<=57)))
            return false;
        if (znaki[i]==','){
            if (!(znaki[i-1]<=57 && znaki[i-1]>=48 && znaki[i+1]<=57 && znaki[i+1]>=48))
                return false;
            else if (przecinek)
                return false;
            else
                przecinek=true;
        }
        else if(znaki[i]=='-' || znaki[i]=='+' || znaki[i]=='/' || znaki[i]=='*'){
            if (znaki[i+1]=='-' || znaki[i+1]=='*' || znaki[i+1]=='+' || znaki[i+1]=='/' || znaki[i+1]==')' || (i==znaki.size()-1))
                return false;
            if ((znaki[i-1]<=57 && znaki[i-1]>=48 && znaki[i+1]<=57 && znaki[i+1]>=48) || znaki[i+1]=='(')
                przecinek=false;
        }
        else if(znaki[i]=='('){
            nawiasy++;
            if (((znaki[i-1]=='*' || znaki[i-1]=='/' || znaki[i-1]=='+' || znaki[i-1]=='-' || znaki[i-1]=='(') && ((znaki[i+1]<=57 && znaki[i+1]>=48) || znaki[i+1]=='-')) || i==0 || znaki[i+1] =='(')
                    przecinek=false;
            else
                return false;
                }
        else if(znaki[i]==')'){
            if (((znaki[i+1]=='*' || znaki[i+1]=='/' || znaki[i+1]=='+' || znaki[i+1]=='-') && (znaki[i-1]<=57 && znaki[i-1]>=48)) || znaki[i-1]==')' || znaki[i+1]==')' || i==znaki.size()-1){
                nawiasy--;
                przecinek=false;}
            else
                return false;
        }
    }
if (nawiasy!=0)
    return false;
return true;
}
void Kalkulator::czysc(std::vector<char> &c) {
    while (c.front() == '0')
        c.erase(c.begin());
    if (c.front() == ',')
        c.insert(c.begin(),'0');
    while (c.back() == '0')
        c.pop_back();
    if (c.back() == ',')
        c.insert(c.end(),'0');
}
void Kalkulator::wyrownaj(std::vector<char> &a, std::vector<char> &b) {
    unsigned long long int pa=0,za=0,pb=0,zb=0;
    for(unsigned long long int i=0;i<a.size();i++)
        if(a[i]==','){
            za=a.size()-1-i;
            pa=i;
            break;
        }
    for(unsigned long long int i=0;i<b.size();i++)
        if(b[i]==','){
            zb=b.size()-1-i;
            pb=i;
            break;
        }
    pb<pa ? b.insert(b.begin(), pa - pb, '0') : a.insert(a.begin(), pb - pa, '0');
    zb<za ? b.insert(b.end(), za - zb, '0') : a.insert(a.end(), zb - za, '0');
}
void Kalkulator::sprawdz(std::vector<char> &a) {
    bool pa=false;
    for(auto i:a){ if(i==',') return;}
    if(!pa){
        a.push_back(',');
        a.push_back('0');
    }
    return;
}
std::vector<char> Kalkulator::dodaj(std::vector<char> a, std::vector<char> b) {
    sprawdz(a);
    sprawdz(b);
    wyrownaj(a,b);
    a.insert(a.begin(),'0');
    b.insert(b.begin(),'0');
    auto z=przecinek(a,b);
    int x=0;
    for(unsigned long long int i=a.size();i>0;i--){
        x=a[i-1] + b[i-1] - 96;
        a[i-1]= static_cast<char>(x % 10 + '0');
        if(x>=10) a[i-2]++;
    }
    a.insert((a.end()-z),',');
    czysc(a);
    return a;
}
bool Kalkulator::czyWieksza(std::vector<char> &a, std::vector<char> &b) {
    wyrownaj(a,b);
    for(unsigned long long int i=0;i<a.size();i++){
        if(a[i]<b[i]){
            return true;
        }else if(a[i]>b[i]){
            return false;
        }
    }
    return false;
}
std::vector<char> Kalkulator::odejmij(std::vector<char> a, std::vector<char> b) {
    bool minus=false;
    sprawdz(a);
    sprawdz(b);
    if(czyWieksza(a,b)){
        a.swap(b);
        minus=true;
    }
    auto z=przecinek(a, b);
    for(unsigned long long int i=a.size(); i > 0; i--){
        long long int j= i - 2;
        int x=a[i-1]-b[i-1];
        if(x>=0){
            b[i-1]= static_cast<char>(x + '0');
        }else{
            b[i-1]= static_cast<char>(x + 10 + '0');
            while(a[j]=='0') {
                a[j] = '9';
                j--;
            }
            a[j]--;
        }
    }
    b.insert((b.end()-z),',');
    czysc(b);
    if(minus) b.insert(b.begin(),'-');
    return b;
}
void Kalkulator::blad_wejscia(){
	system("cls");
    std::cout<<"Nie rozpoznano polecenia!"<<std::endl;
    usage();
}
std::vector<char> Kalkulator::pomnoz(std::vector<char> a, std::vector<char> b) {
    sprawdz(a);
	sprawdz(b);
    wyrownaj(a,b);
    auto x=przecinek(a,b);
    unsigned long long int m = a.size(), n = b.size();
    std::vector<int> dp(m+n,0);
    for ( long long int i = m-1; i >= 0; i-- ) {
        for ( long long int j = n-1; j >= 0; j-- ) {
            dp[m+n-i-j-2] += (a[i]-'0')*(b[j]-'0');
            dp[m+n-i-j-1] += dp[m+n-i-j-2]/10;
            dp[m+n-i-j-2] %= 10;
        }
    }
    a.clear();
    for ( long long int i = m+n-1; i >= 0; i-- )
            a.push_back(static_cast<char &&>(dp[i] + '0'));
            a.insert((a.end()-2*x),',');
            czysc(a);
            return a;
}
std::vector<char> Kalkulator::podziel(std::vector<char> a, std::vector<char> b) {
	std::vector<char> zero={{'0'},{','},{'0'}};
	sprawdz(a);
	sprawdz(b);
	wyrownaj(b,zero);
	if(b==zero) {
        std::cout<<"Dzielenie przez zero!"<<std::endl;
        return {{'0'},{','},{'0'}};}
	unsigned long long int x;
	for(unsigned long long int i=0;i<b.size();i++)
        if(b[i]==','){
            x=b.size()-1-i;
            b.erase(b.end()-x-1);
            break;
        }
	for(unsigned long long int i=0;i<a.size();i++)
        if(a[i]==','){
            x+=i;
            a.erase(a.begin()+i);
            break;
	}
    std::vector<char> w(a.size()+dok,'0'), c;
    for(unsigned long long int i=0;i<dok;i++) a.push_back('0');
	for(unsigned long long int i=0;i<a.size();i++){
	c.push_back(a[i]);
	sprawdz(c);
	sprawdz(b);
	while(!czyWieksza(c,b)){
		c=odejmij(c,b);
		w[i]++;
	}
	c.pop_back();
	c.pop_back();
	}
	//dopisz przecinek
	w.insert(w.begin()+x,',');
	czysc(w);
	return w;
}
unsigned long long int Kalkulator::przecinek(std::vector<char> &a, std::vector<char> &b){
    for(unsigned long long int i=a.size(); i > 0; i--){
        if(a[i-1]==','){
            a.erase(a.begin()+i-1);
            b.erase(b.begin()+i-1);
            return (a.size()-i+1);
        }
    }
}
void Kalkulator::usage(){
    std::cout<<"Program akceptuje równania z podstawowymi operatorami np. +,-,/,* oraz nawiasy wprowadzone w 1 wierszu, bez białych znaków, formalnie poprawne"<<std::endl;
    std::cout<<"Przykłady: "<<std::endl;
    std::cout<<"(2,5*(-(-(-2)))/2) = -2,5"<<std::endl;
    std::cout<<"2,345,2+4,2/3 = error (2 przecinki w 1 liczbie)"<<std::endl;
    std::cout<<"(2 + 2)/2 = error (spacje w równaniu)"<<std::endl<<std::endl;
    std::cout<<"Lista komend: "<<std::endl;
    std::cout<<"help/manual/? - zwraca tą wiadomość"<<std::endl;
    std::cout<<"dokl - ustawia nową dokładność wyniku oraz dzielenia."<<std::endl;
    std::cout<<"about - :)"<<std::endl;
    std::cout<<"clear/cls - czyści okno wiersza poleceń"<<std::endl;
    std::cout<<"quit/q/exit - wyjście z programu"<<std::endl;
    }
void Kalkulator::about(){
	char tab[]={32,32,32,32,32,32,32,32,32,32,32,32,32,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,10,32,32,32,32,32,32,32,32,32,32,32,32,47,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,32,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,75,97,108,107,117,108,97,116,111,114,32,100,117,122,121,99,104,32,108,105,99,122,98,32,67,43,43,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,77,97,100,101,32,98,121,32,82,111,98,101,114,116,32,84,97,117,98,101,32,38,38,32,77,105,99,104,97,108,32,66,101,108,122,97,107,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,103,105,116,104,117,98,46,99,111,109,47,114,111,98,116,97,117,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,103,105,116,104,117,98,46,99,111,109,47,82,51,122,110,48,119,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,124,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,124,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,124,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,124,10,32,32,32,32,32,32,32,32,32,32,32,32,92,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,47,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,92,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,47,10,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,95,10,32,32,32,32,32,32,32,32,32,32,32,32,32,95,45,39,32,32,32,32,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,32,32,45,45,45,32,96,45,95,10,32,32,32,32,32,32,32,32,32,32,95,45,39,46,45,46,45,46,32,46,45,45,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,45,46,32,32,46,45,46,45,46,96,45,95,10,32,32,32,32,32,32,32,95,45,39,46,45,46,45,46,45,46,32,46,45,45,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,96,95,95,96,46,32,46,45,46,45,46,45,46,96,45,95,10,32,32,32,32,95,45,39,46,45,46,45,46,45,46,45,46,32,46,45,45,45,45,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,46,45,45,45,45,45,46,32,46,45,46,45,46,45,46,45,46,96,45,95,10,32,95,45,39,46,45,46,45,46,45,46,45,46,45,46,32,46,45,45,45,46,45,46,32,46,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,46,32,46,45,46,45,45,45,46,32,46,45,45,45,46,45,46,45,46,45,46,96,45,95,10,58,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,58,10,96,45,45,45,46,95,46,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,45,46,95,46,45,45,45,39};
	system("Color 02");
	system("cls");
    for(auto i:tab) std::cout<<i;
}
