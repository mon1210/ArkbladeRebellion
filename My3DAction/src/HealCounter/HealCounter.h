#include "DxLib.h"
#include "..\Constants.h"
#include "..\Game\Game.h"

// �N���X�̑O���錾
class Game;

class HPCounter
{
public:
	HPCounter(Game *Game_);
	~HPCounter();
	void draw();			// �`�惁�\�b�h
	void update();			// �X�V���\�b�h		�c��񐔂ɍ��킹�ĐF�ύX
private:
	Game *pGame = nullptr;
	int	  color = 0;		// UI�̐F
};

