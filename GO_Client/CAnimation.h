#ifndef CANIMATION_H
#define CANIMATION_H

//Tablice
static const char BlockedAnimationsForAll[8][30] =
{
	{"T_STUMBLE"},
	{"T_STUMBLEB"},
	{"T_GOTHIT"},
	{"C_LOOK_1"},
    {"R_ROAM1"},
    {"R_ROAM2"},
    {"R_ROAM3"},
	{"C_BOW_1"},
};

static const char AnimationMove[22][30] =
{
	//Atakowanie w biegu
	{"T_FISTATTACKMOVE"},
	{"T_1HATTACKMOVE"},
	{"T_2HATTACKMOVE"},

	//Wyciaganie broni w biegu
	{"T_MOVE_2_FISTMOVE"},
	{"T_MOVE_2_1HMOVE"},
	{"T_MOVE_2_2HMOVE"},

	//Chowanie broni w biegu
	{"T_FISTMOVE_2_MOVE"},
	{"T_1HMOVE_2_MOVE"},
	{"T_2HMOVE_2_MOVE"},

	//Chodzenie tylem
	{"T_JUMPB"},
	{"T_FISTJUMPB"},
	{"S_FISTWALKBL"},
	{"S_WALKBL"},
	{"T_2HJUMPB"},
	{"S_2HWALKBL"},
	{"T_1HJUMPB"},
	{"S_1HWALKBL"},

	//Schodzenie na boki
	{"T_RUNSTRAFER"},
	{"T_RUNSTRAFEL"},
	{"T_WALKSTRAFER"},
	{"T_WALKSTRAFEL"},

	//Rozpoczecie animacji chodzenia
	{"T_RUN_2_RUNL"}

};

static const char AnimationTurning[44][30] =
{
	//Rotacja
	{"T_RUNTURNL"},
	{"T_RUNTURNR"},
	
	//Podczas plywania
	{"T_SWIMTURNL"},
	{"T_SWIMTURNR"},

	//Rotacja podczas chodzenia
	{"T_WALKTURNL"},
	{"T_WALKTURNR"},

	//Rotacja podczas skradania sie
	{"T_SNEAKTURNL"},
	{"T_SNEAKTURNR"},

	//Rotacja z podniesionymi rekami
	{"T_FISTRUNTURNL"},
	{"T_FISTRUNTURNR"},
	{"T_FISTWALKTURNL"},
	{"T_FISTWALKTURNR"},
	{"T_FISTSNEAKTURNL"},
	{"T_FISTSNEAKTURNR"},


	//Rotacja z 1h
	{"T_1HRUNTURNL"},
	{"T_1HRUNTURNR"},
	{"T_1HWALKTURNL"},
	{"T_1HWALKTURNR"},
	{"T_1HSNEAKTURNL"},
	{"T_1HSNEAKTURNR"},

	//Rotacja z 2h
	{"T_2HRUNTURNL"},
	{"T_2HRUNTURNR"},
	{"T_2HWALKTURNL"},
	{"T_2HWALKTURNR"},
	{"T_2HSNEAKTURNL"},
	{"T_2HSNEAKTURNR"},

	//Rotacja z kusz¹
	{"T_CBOWRUNTURNL"},
	{"T_CBOWRUNTURNR"},
	{"T_CBOWWALKTURNL"},
	{"T_CBOWWALKTURNR"},
	{"T_CBOWSNEAKTURNL"},
	{"T_CBOWSNEAKTURNR"},

	//Rotacja z ³ukiem
	{"T_BOWRUNTURNL"},
	{"T_BOWRUNTURNR"},
	{"T_BOWWALKTURNL"},
	{"T_BOWWALKTURNR"},
	{"T_BOWSNEAKTURNL"},
	{"T_BOWSNEAKTURNR"},

	//Rotacja z czarami
	{"T_MAGRUNTURNL"},
	{"T_MAGRUNTURNR"},
	{"T_MAGWALKTURNL"},
	{"T_MAGWALKTURNR"},
	{"T_MAGSNEAKTURNL"},
	{"T_MAGSNEAKTURNR"}
};

static const char AnimationHandAction[21][30] =
{
	//Du¿e jedzenie
	{"T_FOODHUGE_STAND_2_S0"},
	{"S_FOODHUGE_S0"},
	{"T_FOODHUGE_S0_2_STAND"},

	//Jedzenie
	{"T_FOOD_STAND_2_S0"},
	{"S_FOOD_S0"},
	{"T_FOOD_S0_2_STAND"},

	//Miêso
	{"T_MEAT_STAND_2_S0"},
	{"S_MEAT_S0"},
	{"T_MEAT_S0_2_STAND"},

	//Ry¿/zupy
	{"T_RICE_STAND_2_S0"},
	{"S_RICE_S0"},
	{"T_RICE_S0_2_STAND"},

	//Mikstura
	{"T_POTION_STAND_2_S0"},
	{"S_POTION_S0"},
	{"T_POTION_S0_2_STAND"},

	//Szybkie mikstury
	{"T_POTIONFAST_STAND_2_S0"},
	{"S_POTIONFAST_S0"},
	{"T_POTIONFAST_S0_2_STAND"},

	//Skun
	{"T_JOINT_STAND_2_S0"},
	{"S_JOINT_S0"},
	{"T_JOINT_S0_2_STAND"}
};

class CAnimation
{
private:
	CAnimation();
	CAnimation( const CAnimation & ) {};
	~CAnimation();

public:
	static CAnimation & GetInstance()
	{
		static CAnimation animgr;
		return animgr;
	}

	bool IsAnimationTurning(RakString aniName);
	int GetAnimationMove(oCNpc* npc);
	bool IsAnimationMoveActive(oCNpc* npc);
	int GetAnimationHandAction(oCNpc* npc);
	bool IsAnimationHandActionActive(oCNpc* npc);
	bool IsAniBlockedForAll(zCModelAni* modelAni);
};

#endif //CANIMATION_H