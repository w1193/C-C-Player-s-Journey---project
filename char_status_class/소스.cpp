#include<stdio.h>
#include<stdlib.h>
/*
구상 한 것, a가 상황에 따라 Power, Stamina, 기타 등등이 되는 것
*/
class Status {
	int iX, iY;
	int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty;

	void limit(int a) {
		if (a <= 0) {
			a = 0;
		}
		if (0<a<100)
		{
			a = a;
		}
		else {
			a = 100;
		};
	}

};