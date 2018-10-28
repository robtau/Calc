#include <iostream>
#include <vector>
#include <stack>
using namespace std;
class Kalkulator{
public:
unsigned long long int dokl=3;
unsigned long long int dok=100;
void blad_wejscia();
void usage();
void about();
void czysc(std::vector<char> &c);
void wyrownaj(std::vector<char> &a, std::vector<char> &b);
void sprawdz(std::vector<char> &a);
bool walidacja(vector <char> &znaki);
bool czyWieksza(std::vector<char> &a, std::vector<char> &b);
std::vector<char> dodaj(std::vector<char> a, std::vector<char> b);
std::vector<char> odejmij(std::vector<char> a, std::vector<char> b);
std::vector<char> pomnoz(std::vector<char> a, std::vector<char> b);
vector <char> dzialanie(vector <char> a, vector <char> b, char znak);
std::vector<char> podziel(std::vector<char> a, std::vector<char> b);
vector <char> parser(vector <char> &znaki);
vector <char> obliczansko(vector <char> &komendy);
unsigned long long int przecinek(std::vector<char> &a, std::vector<char> &b);
};
int main(){
	Kalkulator calc;
    string komendy;
    cout<<"If you feel a little lost just type 'help'"<<endl;
    while(true){
    bool cinek=false;
    unsigned long long int j=0;
    cout<<"\nProvide commands:"<<endl;
    cin>>komendy;
    if (komendy == "exit" || komendy == "q" || komendy == "quit")
        break;
    else if(komendy== "usage" || komendy=="manual" || komendy=="man" || komendy=="?" || komendy=="help")
        calc.usage();
    else if(komendy=="about")
        calc.about();
    else if(komendy=="dokl"){
    	cout << "New outcome precision: \n";
    	cin >> calc.dokl;
    	cout << "New division precision: \n";
    	cin >> calc.dok;}
    else if(komendy=="clear" || komendy =="cls")
        system("cls");
    else{
        vector<char>znaki(komendy.begin(),komendy.end());
        komendy.erase();
        if(!calc.walidacja(znaki)){
            calc.blad_wejscia();
            continue;
        }
        znaki = calc.parser(znaki);
        znaki = calc.obliczansko(znaki);
        vector<char> wynik;
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
    for(auto i:wynik) cout << i;
    cout<<endl;
    }
}
return 0;
}

vector <char> Kalkulator::dzialanie(vector <char> a, vector <char> b, char znak){
    bool minusik1=false,minusik2=false;
    vector <char> wynik;
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
vector <char> Kalkulator::parser(vector <char> &znaki){
    vector <char> wynik;
    stack <char> stos;
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
vector <char> Kalkulator::obliczansko(vector <char> &komendy){
    stack <vector<char>> stos;
    stos.push({{'0'}});
    vector <char> a,b,c;
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
bool Kalkulator::walidacja(vector <char> &znaki){
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
    cout<<"Commands you provided are not recognizable by program. Please refer to manual below."<<endl;
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
	vector<char> zero={{'0'},{','},{'0'}};
	sprawdz(a);
	sprawdz(b);
	wyrownaj(b,zero);
	if(b==zero) {
        cout<<"You just tried to divide by zero, please don't do that."<<endl;
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
    vector<char> w(a.size()+dok,'0'), c;
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
    cout<<"Program accepts equations with basic arithmetic operators, e.g +,-,/,* and paretheses provided as a one-liner, without white spaces and formally correct"<<endl;
    cout<<"Examples: "<<endl;
    cout<<"(2,5*(-(-(-2)))/2) gives as a return of -2,5"<<endl;
    cout<<"2,345,2+4,2/3 returns error because of 2 periods in one number"<<endl;
    cout<<"(2 + 2)/2 also returns error because of white spaces"<<endl<<endl;
    cout<<"List of recognized commands: "<<endl;
    cout<<"help/manual/? - prints out this message"<<endl;
    cout<<"dokl - used to set precision of results and precision of division."<<endl;
    cout<<"about - prints something cool"<<endl;
    cout<<"clear/cls - clears the console"<<endl;
    cout<<"quit/q/exit - it's pretty much self explanatory"<<endl;
    }
void Kalkulator::about()
{
	system("Color 02");
	std::string const abaut= R"~(
             ________________________________________________
            /                                                \
           |    _________________________________________     |
           |   |                                         |    |
           |   |  Big numbers calculator C++             |    |
           |   |  Made by Robert Taube && Michal Belzak  |    |
           |   |  github.com/robtau                      |    |
           |   |  github.com/R3zn0w                      |    |
           |   |                                         |    |
           |   |                                         |    |
           |   |                                         |    |
           |   |                                         |    |
           |   |                                         |    |
           |   |                                         |    |
           |   |                                         |    |
           |   |                                         |    |
           |   |_________________________________________|    |
           |                                                  |
            \_________________________________________________/
                   \___________________________________/
                ___________________________________________
             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_
          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_
       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_
    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_
 _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`-_
:-------------------------------------------------------------------------:
`---._.-------------------------------------------------------------._.---'
	)~";
	system("cls");
    cout<<abaut;
}
