#include <bangtal>
using namespace bangtal;

int main()
{
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	// 장면을 생성한다.
	ScenePtr scene = Scene::create("SantaRace", "Images/background.png");
	
	auto santa_x = 0;
	auto santa = Object::create("Images/santa.png", scene, santa_x, 500);
	auto startB = Object::create("Images/start.png", scene, 590, 70);
	auto endB = Object::create("Images/end.png", scene, 590, 20);
	auto playB = Object::create("Images/play.png", scene, 610, 30, false);
	auto timer = Timer::create(10.f);

	startB->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		startB->hide();
		endB->hide();
		playB->show();

		santa_x = 0;
		santa->locate(scene, santa_x, 500);

		timer->set(10.f);
		timer->start();

		return true;
		});

	endB->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
	});

	playB->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		// 산타를 x축으로 30만큼 이동한다.
		santa_x = santa_x + 30;
		santa->locate(scene, santa_x, 500);
		if (santa_x > 1280) {
			showMessage("Success!! :)");
			timer->stop();
			playB->hide();
			startB->setImage("Images/restart.png");
			startB->show();
			endB->show();
		}

		return true;
	});

	showTimer(timer);
	timer->setOnTimerCallback([&](TimerPtr)->bool {
		showMessage("Failed to deliver :(");
		
		playB->hide();
		startB->setImage("Images/restart.png");
		startB->show();
		endB->show();

		return true;
	});

	// 게임을 시작한다.
	startGame(scene);

	return 0;
}