#include<stdio.h>
#include<stdlib.h>

int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty = 0;
int Money = 50000;//초기 시작 스탯과 돈

class Status_Limit {
	int Power, Stamina, Intel, Luck, Dex, Wealth, Beauty; //캐릭터 스탯
	
	void Power_Limit() {
		if (Power <= 0) { Power = 0; };
		if (Power >= 100) { Power = 100;};
	}
	void Stamina_Limit() {
		if (Stamina <= 0) { Stamina = 0; };
		if (Stamina >= 100) { Stamina = 100; };
	}
	void Intel_Limit() {
		if (Intel <= 0) { Intel = 0; };
		if (Intel >= 100) { Intel = 100; };
	}
	void Luck_Limit() {
		if (Luck <= 0) { Luck = 0; };
		if (Luck >= 100) { Luck = 100; };
	}
	void Dex_Limit() {
		if (Dex <= 0) { Dex = 0; };
		if (Dex >= 100) { Dex = 100; };
	}
	void Wealth_Limit() {
		if (Wealth <= 0) { Wealth = 0; };
		if (Wealth >= 100) { Wealth = 100; };
	}
	void Beauty_Limit() {
		if (Beauty <= 0) { Beauty = 0; };
		if (Beauty >= 100) { Beauty = 100; };
	}
	//스탯의 범위를 제한하는 함수들이다.
};

void main() {



	getchar();
}