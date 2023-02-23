// SimpleInterpreter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <memory>
#include <vector>
using namespace std;

namespace MW
{

    struct CompileError{};


 
    static string _INTERGER = "INTERGER";
    static string _PLUS = "PLUS";
    static string _EOF = "EOF";

    class NullType{};
    static NullType NullValue{};

    class TokenBase
    {
    public: string Type;
          TokenBase(string InType) :Type(InType)
          {}

          virtual void foo() {};
    };

    template<typename T>
    class Token: public TokenBase
    {
    public:
        T Value;// T =  string, int, NullValue...
    public:
        Token(string InType, T InValue) :TokenBase(InType), Value(InValue)
        {}
    };

    class Interpreter
    {

        using IntToken = Token<int>;
        using StringToken = Token<string>;

    private:
        string Text;
        int Pos;
        //TODO:智能指针
        TokenBase* CurrentToken;
    public:
        Interpreter(string InText) :Text(InText), Pos(0), CurrentToken(nullptr)
        {}

        void Error()
        {
            throw CompileError{};
        }

        TokenBase* GetNextToken()
        {
            //;
         
            TokenBase* mToken = nullptr;
            if (this->Pos > (int)this->Text.size() - 1)
            {
                return new Token<NullType>(_EOF, NullValue);
            }
            
            char CurrentChar = Text[this->Pos];

          

            if (isdigit(CurrentChar))
            {
                mToken = new IntToken(_INTERGER, CurrentChar - 48);
            }else if (CurrentChar == '+')
            {
               mToken = new StringToken(_PLUS, "+");
            }
            else {
                this->Error();
            }
            this->Pos++;
            return mToken;
        }

        void Eat(string TokenType)
        {
            if (this->CurrentToken->Type == TokenType)
            {
                this->CurrentToken = this->GetNextToken();
            }
            else {
                this->Error();
            }
        }

        int Expr()
        {
            this->CurrentToken = this->GetNextToken();
            IntToken* Left = dynamic_cast<IntToken*>(this->CurrentToken);
            this->Eat(_INTERGER);

            StringToken* Op = dynamic_cast<StringToken*>(this->CurrentToken);
            this->Eat(_PLUS);

            IntToken* Right = dynamic_cast<IntToken*>(this->CurrentToken);
            this->Eat(_INTERGER);

            int Result = Left->Value + Right->Value;
            return Result;
        }
       
    };
}



int main()
{
    std::cout << "Hello World!\n";
    while (1)
    {
        string Text;
        std::cin >> Text;
        MW::Interpreter interpreter(Text);

        std::cout << interpreter.Expr() << endl;

    }

  
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
