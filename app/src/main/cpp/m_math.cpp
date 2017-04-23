
/*============================================================================*\
 *
 *                     模拟实现 math.h 库中的函数
 *
 *                         樊列龙 2013/7/1
 *
\*============================================================================*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

using namespace std;

typedef int MODE;                                    // 计算sin(x)时采用弧度还是角度
const int BY_RADIDAN = 0;                           // 弧度
const int BY_ANGLE = 1;                                // 角度

const double RATIO = 0.01745329251994;                 // 角度转弧度的转换率

long Factorial( long x );                           // 阶乘
double Pow( double x, double y = 2 );               // 求x^y
double Square( double x );                          // 求平方
double Cube( double x );                            // 求立方
double Sin( double x, MODE mode = BY_RADIDAN );     // 计算sin(x)
double Cos( double x , MODE mode = BY_RADIDAN );    // 计算cos(x)
double Tan( double x , MODE mode = BY_RADIDAN );    // 计算tan(x)
int Int(double x);                                  // 取整, 不进行四舍五入
double Fabs( double x );                            // 求绝对值
double Arctanh(double x);                           // 求achtanh()
double Ln(double x);                                // 求自然对数
double Exp( double x );                             // 求e的x次幂
double Sinh( double x );                            // 求双曲正弦 sinh()
double Cosh( double x );                            // 求双曲余弦 cosh()
double Tanh(double x);                              // 求双曲正切 tanh()
double PI();                                        // 求圆周率
double gen(double x, double y);                     // 求根


// 计算阶乘
long Factorial( long x )
{
    if( 0 == x || 1 == x )
    {
        return 1;
    }

    long ans = 1;
    for( int i = 2; i <= x; i++ )
    {
        ans *= i;
    }

    return ans;
}


// 计算求幂, 默认是平方
// x^y=e^(ln(x)*y)
double Pow(double x, double y)
{
    return Exp( (Ln(x)*y) );
}

// 求根
double gen(double x, double y)
{
    return Pow(x,1/y);
}

// 计算绝对值
double Fabs( double x )
{
    if( x < -1e-9)
        return -x;
    return x;
}

int Int(double x)
{
    return static_cast<int>(Fabs( x ));
}

// 利用泰勒级数算 sin(x) , 默认传入弧度
// sinx ≈x-(x^3)/3!+(x^5)/5!-(x^7)/7!-(x^9)/9!...
// 计算精度为7位
double Sin( double x, MODE mode )
{
    // 如果是角度则转换成弧度计算
    if( BY_ANGLE ==  mode )
    {
        x *= RATIO;
    }
    x = x - Int( (x/( 2 * PI() ) ) ) * 2 * PI();
    if( 0 == x )
        return 0;

    double sum = 0, fs = x, fm = 1, t, t1 = 1;  //求和、分子、分母、精度、t1表示符号位
    int n=1;                                    //项数

    t = fs / fm;                                //精度赋值
    while( Fabs(t) >= 1e-8)                     //循环条件
    {
        sum = sum + t;                          //求和
        n++;                                    //基数增加
        fs = fs * x * x;                        //新分子
        fm = fm * ( 2*n - 2) * ( 2*n - 1 );     //新分母
        t1= -t1;                                //符号位　一正一负
        t = t1 * ( fs / fm );                   //精度
    }

    return sum;
}

// cos(x) = 1 - (x^2)/2! + (x^4)/4!......
// 结果精度为7位
double Cos( double x , MODE mode)
{
    double term,sum;
    int n = 2;

    sum = 1.0;
    term = 1.0;

    while(Fabs(term) > 1e-7)
    {
        term = term * x * x / (n * (n-1)) * (-1.0);
        sum = sum + term;
        n += 2;
    }

    return sum;
}

// tanθ = sinθ / cosθ
// 结果精度为7位
double Tan( double x , MODE mode)
{
    return ( Sin(x) / Cos(x) );
}


// 计算 x^2
double Square( double x )
{
    return ( x*x );
}

// 计算 x^3
double Cube( double x )
{
    return ( x*x*x );
}


// arctanh(x)= x + x^3/3 + x^5/5 + ...       (x≤1)
// 求sinh(y) 会用到
// 精度为7位
double Arctanh(double x)
{
    int n = 1;
    double sum = 0, term = x,  numer = x, denom = 1;
    while(Fabs(term) > 1e-8)
    {
        sum += term;                            // 求和
        numer = numer * x * x;                  // 分子
        denom = n+2;                            // 分母
        term = numer/denom;                     // 精度
        n += 2;                                 // 计数
    }

    return sum;
}


// ln(x) = 2 * arctanh((x-1)/(x+1))
// 调用了Arctanh(double) 方法
double Ln(double x)
{
    return 2 * Arctanh((x-1)/(x+1));
}

// 求e^x 用于Pow( double, double )调用
// e^x = 1+x+(x^2)/2!+(x^3)/3!+...
// 精度为7位
double Exp( double x )
{
    double ret = 1, term = x, numer = x, denom = 1;;
    int n = 1;
    while(Fabs(term) > 1e-8)
    {
        ret += term;                            // 求和
        numer *= x;                             // 分子
        denom = denom * (n+1);                  // 分母
        n++;                                    // 累加
        term = numer/denom;                     // 精度
    }

    return ret;

}

// sinh(x)=(exp(x) - exp(-x)) / 2.0
// 精度为7位
double Sinh(double x)
{
    return ( ( Exp(x) - Exp(-x) ) / 2.0 );
}

// cosh(x)=(exp(x) + exp(-x)) / 2.0;
// 精度为7位
double Cosh(double x)
{
    return ( ( Exp(x) + Exp(-x) ) / 2.0 );
}

// tanh(x) = sinh(x) / cosh(x);
// 精度为7位
double Tanh(double x)
{
    return ( Sinh(x) / Cosh(x) );
}


// 求PI: pi/4 = 1 - 1/3 + 1/5 - 1/7...
double PI()
{
    int a = 3, b = 1;
    double m = 1.0, sum = 1.0;

    while( Fabs(m) > 1e-7 )
    {
        b = -b;
        m = double(b) / a;
        sum = sum + m;
        a = a + 2;
    }
    return 4 * sum;
}


//==============================================================================
void drow_line(int i = 39,string s = "━", bool newline = false)
{
    if(newline) cout << endl;
    while(i--)
        cout << s;
    cout << endl;
}

void cls()
{
    system("cls");
}

void pause()
{
    system("pause");
    //getchar();
}

// 菜单选项
void menu_option(int& menu_op,
                 int max = 14,
                 int min = 0,
                 string s = " 请选择相应的菜单选项>>> ",
                 string error = " ERROR:请选择正确的菜单选项! >>> ")
{
    cout << s;
    cin >> menu_op;
    while(cin.fail() || menu_op < min || menu_op > max)
    {
        cout << error;
        cin.clear();
        fflush(stdin);
        cin >> menu_op;
    }
}

// 选择逻辑处理
bool choos()
{
    string contin;
    while(true)
    {
        getline(cin, contin);
        if(contin == "Y" || contin == "y" || contin == "是")
        {
            return true;
        }
        else if(contin == "N" || contin == "n" || contin == "否")
        {
            return false;
        }
        else
        {
            cout << " 提示：请输入(Y/N)！>>> ";
        }
    }

}

bool check_input(int& x,
                 string str = " 请输入数据x：",
                 string err = " 输入数据格式有误！")
{
    cout << str;
    cin >> x;
    if(cin.good())
        return true;
    cout << err << endl;
    return false;
}

bool check_input(double& x,
                 string str = " 请输入数据 x：",
                 string err = " 输入数据格式有误！")
{
    cout << str;
    cin >> x;
    if(cin.good())
        return true;
        cout << err << endl;
    return false;
}

void print_result(double ans, string str )
{
    cout << str << " = " << ans << endl;
    pause();
}

//==============================================================================

/**
 *
 * 主菜单
 */
void menu_main()
{
    cls();
    cout << endl << endl << endl;

    cout << "\t";
    drow_line(35);

    cout << "\t\t\t\t*** 主菜单选项 ***" << endl;

    cout << "\t";
    drow_line(35);

    cout << left;
    cout << "\t        " << setw(25) << "1. 取整 Int( x )";
    cout << setw(25) << "2. 计算 sinh( x )" << endl;
    cout << "\t        " << setw(25) << "3. 计算 sin( x )";
    cout << setw(25) << "4. 计算 n^2 " << endl;
    cout << "\t        " << setw(25) << "5. 计算 n!";
    cout << setw(25) << "6. 计算 cosh( x ) " << endl;
    cout << "\t        " << setw(25) << "7. 计算 cos( x )";
    cout << setw(25) << "8. 计算 x^y" << endl;
    cout << "\t        " << setw(25) << "9. 计算 y√x ";
    cout << setw(25) << "10. 计算 tanh( x ) " << endl;
    cout << "\t        " << setw(25) << "11. 计算 Π";
    cout << setw(25) << "12. 计算 tan( x )" << endl;
    cout << "\t        " << setw(25) << "13. 计算 x^3";
    cout << setw(25) << "14. 计算 3√x" << endl;
    cout << "\t        " << setw(25) << "0. 退出系统"  << endl;

    cout << "\t";
    drow_line(35);

    cout << endl << endl;
    drow_line(39,"><");
    cout << endl;

}

//int main()
//{
//    int ansInt;
//    double ans;
//    int xi;
//    double x,y;
//
//    while(true)
//    {
//        cls();
//        menu_main();
//        int option;
//        menu_option(option);                            // 选择功能
//        switch(option)
//        {
//        case 0 :
//            cout << "是否退出？(Y/N)";
//            if(choos())
//                exit(0);
//            break;
//        case 1:
//            check_input(x);
//            ansInt = Int(x);
//            drow_line(39,"**");
//            cout << "Int(" << x << ") = " << ansInt << endl;
//            pause();
//            break;
//        case 2:
//            check_input(x);
//            ans = Sinh(x);
//            drow_line(39,"**");
//            cout << "sinh(" << x << ") = " << ans << endl;
//            pause();
//            break;
//        case 3:
//            check_input(x);
//            ans = Sin(x);
//            drow_line(39,"**");
//            cout << "sin(" << x << ") = " << ans << endl;
//            pause();
//            break;
//        case 4:
//            check_input(x);
//            ans = Square(x);
//            drow_line(39,"**");
//            cout << x << "^2 = " << ans << endl;
//            pause();
//            break;
//        case 5:
//            check_input(xi, " 请输入整数n: ");
//            ansInt = Factorial(xi);
//            drow_line(39,"**");
//            cout << xi << "! = " << ansInt << endl;
//            pause();
//            break;
//        case 6:
//            check_input(x);
//            ans = Cosh(x);
//            drow_line(39,"**");
//            cout << "cosh(" << x << ") = " << ans << endl;
//            pause();
//            break;
//        case 7:
//            check_input(x);
//            ans = Cos(x);
//            drow_line(39,"**");
//            cout << "cos(" << x << ") = " << ans << endl;
//            pause();
//            break;
//        case 8:
//            check_input(x, " 请输入数据 x y : ");
//            check_input(y, "");
//            ans = Pow(x,y);
//            drow_line(39,"**");
//            cout << x << "^" << y << " = " << ans << endl;
//            pause();
//            break;
//        case 9:
//            check_input(x, " 请输入数据 x y : ");
//            check_input(y, "");
//            ans = gen(x,y);
//            drow_line(39,"**");
//            cout << y << "√" << x << " = " << ans << endl;
//            pause();
//            break;
//        case 10:
//            check_input(x);
//            ans = Tanh(x);
//            drow_line(39,"**");
//            cout << "tanh(" << x << ") = " << ans << endl;
//            pause();
//            break;
//        case 11:
//            ans = PI();
//            drow_line(39,"**");
//            cout << "π = " << ans << endl;
//            pause();
//            break;
//        case 12:
//            check_input(x);
//            ans = Tan(x);
//            drow_line(39,"**");
//            cout << "tan(" << x << ") = " << ans << endl;
//            pause();
//            break;
//        case 13:
//            check_input(x);
//            ans = Cube(x);
//            drow_line(39,"**");
//            cout << x << "^3 = " << ans << endl;
//            pause();
//            break;
//        case 14:
//            check_input(x);
//            ans = gen(x,3);
//            drow_line(39,"**");
//            cout << "3√" << x << " = " << ans << endl;
//            pause();
//            break;
//        default:
//            break;
//        }
//    }
//    return 0;
//}
