#include <iostream>
#include<bits/stdc++.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<regex>
using namespace std;
vector <string> reserv;//reserve words
vector<string> reserv2;//reserve2 words
vector<string> sreserv;//reserved words in program
vector<string> sident;//identifiers.
vector<string> snum;//number.
vector<string> tokens;//it contains all tokens.
int token_size=0;//total number of tokens.
int token_count=0;
regex identifier("[a-zA-Z_][a-zA-Z0-9_]*");//regular expression for identifying valid identifier.
regex number("^0$|^[1-9][0-9]*$");//regular expression for identifying valid number.
bool decllist();
bool decl();
bool stmtlist();
bool typelist();
bool varlist();
bool type();
bool var();
bool assignment_stmt();
bool read_stmt();
bool print_stmt();
bool if_stmt();
bool else_part();
bool while_stmt();
bool bexp();
bool bexp1();
bool bexp2();
bool exp();
bool exp1();
bool exp2();
bool exp3();
bool exp4();
bool stmt();
string get_token()
{
    string a="";
    if(token_count<token_size)
    {
        a=tokens[token_count];
        token_count++;
    }
    return a;
}
bool match(string expec)
{
 string s=get_token();
 if(s==expec)
    return true;
 else
      return false;
}
bool program()
{
    bool a=match("global");
    bool b=true;
    bool c=true;
    bool d=true;
    bool e=true;
    bool f=true;
    if(tokens[token_count]=="def")//removal of epsilon in the grammar
         b=decllist();
    c=stmtlist();
    d=match("end");
    e=match(";");
    f=token_count==token_size;
   // cout<<a<<b<<c<<d<<e<<f;
    return (a&b&c&d&e&f);
}
bool decllist()
{
    bool a=decl();
    return a;
}
bool decl()
{
    bool a=match("def");
    bool b=typelist();
    bool c=match("end");
    return a&b&c;
}
bool typelist()
{
    bool a=varlist();
    bool b=match(":");
    bool c=type();
    bool d=match(";");
    if(tokens[token_count]!="end")//if next character is not end it means we have some more declarations.
        return typelist();
    return a&b&c&d;
}
bool varlist()
{
    bool a=var();
    if(tokens[token_count]==",")//if next character is , it means we have to call the varlist once again to match the identifier.
        {
            bool b=match(",");
            bool c=varlist();
        }
    return a;
}
bool var()
{
    string c=tokens[token_count];
    if(find(sident.begin(),sident.end(),c)!=sident.end())
        {
            token_count++;
            return true;
        }
        return false;
}
bool type()
{
    string c=tokens[token_count];
    if(c=="int"||c=="char")
    {
        token_count++;
        return true;
    }
    return false;
}
bool stmtlist()
{
    string s=tokens[token_count];
    bool a=true,c=true;
    if(s!="end")
    {
         a=stmt();
        if(tokens[token_count]==";")
        {
            bool b=match(";");
            c=stmtlist();
        }
    }
    return a;
    //return true;
}
bool stmt()
{
    bool a=true;
        while(tokens[token_count]!="end"&&tokens[token_count+1]!=";")
        {
            //cout<<"A";
            if(find(sident.begin(),sident.end(),tokens[token_count])!=sident.end())
                a=assignment_stmt();
            switch(tokens[token_count][0])
            {
            case 'r':
                a=read_stmt();
                break;
            case 'p':
                a=print_stmt();
                break;
            case 'i':
                a=if_stmt();
                break;
            case 'e':
                    return true;
                    break;
            case 'w':
                a=while_stmt();
                break;
            default:
                //cout<<"unexpected string encountered"<<tokens[token_count]<<endl;
                return false;
                break;
            }
        }
        return a;
}
bool assignment_stmt()
{
    bool a=true;
    bool b=true;
    bool c=true;
    if(find(sident.begin(),sident.end(),tokens[token_count])!=sident.end())
        token_count++;
    else
        a=false;
    b=match("=");
    c=exp();
   // bool d=match(";");
    return a&b&c;
}
bool read_stmt()
{
    bool a=true;
    bool b=true;
    bool c=true;
    if(find(sreserv.begin(),sreserv.end(),tokens[token_count])!=sreserv.end())
        token_count++;
    else
        a=false;
    if(find(sident.begin(),sident.end(),tokens[token_count])!=sident.end())
        token_count++;
    else
        b=false;
    c=match(";");
    if(tokens[token_count]==";")
    {
      return false;
    }
    return a&b&c;

}
bool print_stmt()
{

    bool a=true;
    bool b=true;
    bool c=true;
    if(find(sreserv.begin(),sreserv.end(),tokens[token_count])!=sreserv.end())
        token_count++;
    else
        a=false;
    b=exp();
    c=match(";");
    if(tokens[token_count]==";")
    {
      return false;
    }
   // cout<<a<<b<<c;
    return a&b&c;
}
bool if_stmt()
{
    bool a=true;
    bool b=true;
    bool c=true;
    bool d=true;
    bool e=true;
    bool f=true;
    if(find(sreserv.begin(),sreserv.end(),tokens[token_count])!=sreserv.end())
        token_count++;
    else
        a=false;
    b=bexp();
    c=match(":");
    d=stmtlist();
    if(tokens[token_count]=="else")
        e=else_part();
    f=match("end");
    return a&b&c&d&e&f;
}
bool else_part()
{
    bool a=true;
    bool b=true;
    bool c=true;
   // cout<<"CCCC";
    if(find(sreserv.begin(),sreserv.end(),tokens[token_count])!=sreserv.end())
        token_count++;
    else
        a=false;
    b=stmtlist();
    return a&b&c;
}
bool while_stmt()
{
    bool a=true;
    bool b=true;
    bool c=true;
    bool d=true;
    bool e=true;
    if(find(sreserv.begin(),sreserv.end(),tokens[token_count])!=sreserv.end())
        token_count++;
    b=bexp();
    c=match(":");
    d=stmtlist();
    e=match("end");
    return a&b&c&d&e;
}
bool bexp()
{
     bool a=true;
    bool b=true;
    bool c=true;
    bool d=true;
    bool e=true;
    bool f=true;
   string s=tokens[token_count];
   string s2=tokens[token_count+1];
   if(s=="not")
   {
       a=match("not");
       a=a&bexp();
   }
   if(s=="(")
   {
       b=b&match("(");
       b=b&bexp();
       b=b&match(")");
    }
   if(s2=="<")
   {
       c=exp();
       c=c&match("<");
       c=c&exp();
   }
   if(s2=="=")
   {
       d=exp();
       d=d&match("=");
       d=d&match("=");
       d=d&exp();
   }
   if(s2=="or")
   {
       e=bexp1();
   }
   if(s2=="and")
   {
       f=bexp2();
   }
   return a|b|c|d|e|f;
}
bool bexp1()
{
    bool a=bexp();
    bool b=match("or");
    bool c=bexp();
    return a&b&c;
}
bool bexp2()
{

    bool a=bexp();
    bool b=match("and");
    bool c=bexp();
    return a&b&c;
}
bool exp()
{
    bool a=true;
    bool b=true;
    bool c=true;
    bool d=true;
    bool e=true;
    bool g=true;
    bool h=true;
   // cout<<"exp\n";
    string s=tokens[token_count];
    string s2=tokens[token_count+1];
    //cout<<s<<" "<<s2;
    if(find(sident.begin(),sident.end(),s)!=sident.end())
    {
       // cout<<"K";
        a=match(s);
         //cout<<"dd"<<a<<"DD";
        //token_count++;
    }
    if(find(snum.begin(),snum.end(),s)!=snum.end())
    {
        //cout<<"L";
        token_count++;
    }
    if(tokens[token_count]=="(")
    {
        //cout<<"M";
        a=match("(");
        a=a&exp();
        a=a&match(")");
    }
    if(s2=="+")
    {
        //cout<<"N";
        b=exp1();
    }
    else if(s2=="-")
    {
        //cout<<"O";
        c=exp2();
    }
    else if(s2=="*")
    {
        //cout<<"P";
        d=exp3();
    }
   else if(s2=="/")
    {
        //cout<<"D";
        e=exp4();
    }
    return a|b|c|d|g|h|e;
}
bool exp1()
{
   // cout<<"exp1";
    bool a=true;
    bool b=true;
    bool c=true;
    a=exp();
    b=match("+");
    c=exp();
    return a&b&c;
}
bool exp2()
{
    bool a=true;
    bool b=true;
    bool c=true;
    a=exp();
    b=match("-");
    c=exp();
    return a&b&c;
}
bool exp3()
{
    bool a=true;
    bool b=true;
    bool c=true;
    a=exp();
    b=match("*");
    c=exp();
    //cout<<a<<" "<<b<<" "<<c;
    return a&b&c;
}
bool exp4()
{
    bool a=true;
    bool b=true;
    bool c=true;
    a=exp();
    b=match("/");
    c=exp();
    return a&b&c;
}
bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}
bool search(vector<string>& s)
{
    bool a=true;
    int n=s.size();//returns the number of lines in the source program.
    for(int i=0;i<n;i++)
    {
        string st="";
        for(int j=0;j<s[i].length();j++)
        {
            string t="";
            t=t+s[i][j];//checks for characters in resereve2
            if(find(reserv2.begin(),reserv2.end(),t)!=reserv2.end()||isspace(s[i][j])||s[i].at(j)=='\n')
            {
                auto b=find(reserv.begin(),reserv.end(),st);
                if(b==reserv.end())
                {
                   bool c=regex_match(st,identifier);
                   bool d=isNumber(st);
                   bool e=regex_match(st,number);
                   if(c)
                   {
                       if(st!="")
                       tokens.push_back(st);
                       if(find(sident.begin(),sident.end(),st)==sident.end())
                        sident.push_back(st);
                       st="";
                   }
                   else if(d)
                   {
                       if(st!="")
                       tokens.push_back(st);
                       if(find(snum.begin(),snum.end(),st)==snum.end())
                       snum.push_back(st);
                       st="";
                   }
                   else
                   {
                       if(st!="")
                      {
                          a=false;
                          cout<<"Scanning failed due to "<<st<<endl;
                          break;
                      }
                   }
                }
                else
                {
                    if(st!="")
                        tokens.push_back(st);
                    if(find(sreserv.begin(),sreserv.end(),st)==sreserv.end())
                    sreserv.push_back(st);
                    st="";
                }
             if(find(reserv2.begin(),reserv2.end(),t)!=reserv2.end()&&t!="")
                    tokens.push_back(t);

            }
            else
            {
                st=st+s[i][j];
            }
        }
    }
     return a;
}
int main()
{
    //pushing all the reserved words.
    reserv.push_back("global");
    reserv.push_back("end");
    reserv.push_back("def");
    reserv.push_back("bool");
    reserv.push_back("else");
    reserv.push_back("false");
    reserv.push_back("if");
    reserv.push_back("int");
    reserv.push_back("true");
    reserv.push_back("while");
    reserv.push_back("print");
    reserv.push_back("or");
    reserv.push_back("and");
    reserv.push_back("char");
    reserv.push_back("read");
    //pushing all the terminals.
    reserv2.push_back(",");
    reserv2.push_back(";");
    reserv2.push_back(":");
    reserv2.push_back("+");
    reserv2.push_back("-");
    reserv2.push_back("*");
    reserv2.push_back("/");
    reserv2.push_back("<");
    reserv2.push_back("==");
    reserv2.push_back("=");
    reserv2.push_back("(");
    reserv2.push_back(")");
    //reserv2.push_back("\n");
    string si;
    getline(cin,si,'~');//getting input
    int c=0;
    for(int i=0;i<si.length();i++)//counting the number of lines in the input
    {
        if(si[i]=='\n')
            c++;
    }
    vector<string> scaner;//to store each line
    string s="";
    for(int i=0;i<si.length();i++)
    {
        if(si[i]!='\n')
        {
            s=s+si[i];//appending each character.
        }
        else
        {
            s=s+'\n';//to recognize the end of line in scanning part
            scaner.push_back(s);
            s="";
        }
    }
    bool a=search(scaner);
    if(a)
        cout<<"'Scanning phase succesfull'\n";
    else
        cout<<"'Scanning phase not successfull'\n";
    cout<<"Reserved Words :";
    for(int i=0;i<sreserv.size();i++)
        cout<<sreserv[i]<< " ";
    cout<<endl;
    cout<<"Identifiers:";
    for(int i=0;i<sident.size();i++)
        cout<<sident[i]<< " ";
    cout<<endl;
    cout<<"Numbers:";
    for(int i=0;i<snum.size();i++)
        cout<<snum[i]<<" ";
    cout<<endl;
    if(a)
    {
        token_size=tokens.size();
        if(program())
            cout<<"Parsing Phase successfull"<<endl;
        else
            cout<<"Parsing Phase not successfull"<<endl;
    }
    return 0;
}
