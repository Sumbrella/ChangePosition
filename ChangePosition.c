//
//  main.cpp
//  ChangePosition
//
//  Created by Sumbrella on 2020/4/28.
//  Copyright © 2020 Sumbrella All rights reserved.
//  This branch can read datafile saved as .csv

# include <stdio.h>
# include <math.h>

#define MAX_N 1010

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


void fileInputXYZ(double X[MAX_N], double Y[MAX_N], double Z[MAX_N], int *n)
{
    FILE* fp = fopen("cases.txt", "r");
    if (fp == NULL)
	{
		printf("File Read Error!\n");
        return;
	}
	char s[0xffff];
	fscanf(fp, "%s\n ", s); //跳过第一行
	int i = 0;
	while (fscanf(fp, "%lf,%lf,%lf,\n", &X[i], &Y[i], &Z[i]) == 3)
		i++;
	*n = i;
}

void showCase(double X, double Y, double Z, int kase)
{
    printf("------------------------------------------\n");
    printf("Case<%d>\n", kase);
    printf("当前读取到的数据为：\nX = %f, Y = %f, Z = %f\n", X, Y, Z);
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
    double L = atan2(Y, X);
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
	int n = 0;
    double AX[MAX_N], AY[MAX_N], AZ[MAX_N];
    double N, L, B, H;                // 定义变量

    fileInputXYZ(AX, AY, AZ, &n);     // 获取XYZ的值

	for (int i = 0; i < n; i++)
	{
        double X = AX[i],  Y = AY[i], Z = AZ[i];
        
		configure(X, Y, Z);               // 配置参数
        
        showCase(X, Y, Z, i + 1);         // 打印Case头
        
		getLBH(X, Y, Z, &N, &L, &B, &H);  // 计算LBH的值
        
		showLBH(L, B, H);                 // 输出LBH的值

		showXYZ(N, L, B, H);              // 输出计算得到的XYZ的值
	}
    
    return 0;
}

