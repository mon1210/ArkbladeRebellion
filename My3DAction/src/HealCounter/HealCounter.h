#include "DxLib.h"
#include "..\Constants.h"
#include "..\Game\Game.h"

// クラスの前方宣言
class Game;

class HealCounter
{
public:
	HealCounter(Game *Game_);
	~HealCounter();
	void draw();			// 描画メソッド
	void update();			// 更新メソッド		残り回数に合わせて色変更
private:
	Game *pGame = nullptr;
	int	  color = 0;		// UIの色
};

