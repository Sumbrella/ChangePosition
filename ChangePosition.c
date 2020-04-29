//
//  main.cpp
//  ChangePosition
//
//  Created by Sumbrella on 2020/4/28.
//  Copyright © 2020 Sumbrella All rights reserved.
//
# include <stdio.h>
# include <math.h>

typedef long long ll;

const ll a = 6378137;
const ll b = 6356752;
const double epslion = 1e-15;
double e, R, K, C;

// 配置需要使用的中间参数。
void configure(double X, double Y, double Z)
{
    e = sqrt((a * a - b * b) / (a * a));
    R = sqrt(X * X + Y * Y);
    K = a * e * e / R;
    C = Z / R;
}

// 迭代法迭代一次
double Forward(double B)
{
    double tmp = sqrt(1 / (sin(B) * sin (B)) - e * e );
    return atan(K / tmp + C);
}


void inputXYZ(double *X,double *Y, double *Z)
{
    printf("请输入X，Y，Z的值>>>（空格隔开）");
    scanf("%lf %lf %lf", X, Y, Z);
}


void getLBH(double X, double Y, double Z, double *pN, double *pL, double *pB, double *pH)
{
    double B = C;                   // 让B的初始值为C
    while (1)
    {
        double nB = Forward(B);
        if (nB - B < epslion && nB - B > -epslion)
            break;
        B = nB;
    }
    double N = a / sqrt(1 - e * e * sin(B) * sin(B));
    double L = atan(Y / X);
    double H = R / cos(B) - N;
    
    *pN = N; *pL = L; *pB = B; *pH = H;
}


void showLBH(double L, double B, double H)
{
    printf("转换得到的大地坐标：\n");
    printf("L = %.3f, B = %.3f, H = %.3f\n", L, B, H);
}


void showXYZ(double N, double L, double B, double H)
{
    double X = (N + H) * cos(B) * cos(L);
    double Y = (N + H) * cos(B) * sin(L);
    double Z = (N * (1 - e * e) + H) * sin(B);
    printf("转换后得到的空间坐标：\n");
    // printf("N = %.6f", N);
    printf("X = %.6f, Y = %.6f, Z = %.6f\n", X, Y, Z);
}

int main()
{
    double X, Y, Z;
    double N, L, B, H;                // 定义变量

    inputXYZ(&X, &Y, &Z);             // 获取XYZ的值

    configure(X, Y, Z);               // 配置参数

    getLBH(X, Y, Z, &N, &L, &B, &H);  // 计算LBH的值

    showLBH(L, B, H);                 // 输出LBH的值

    showXYZ(N, L, B, H);              // 输出计算得到的XYZ的值

    
    return 0;
}

