/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 04 - COLLISION
o
	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions:
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include<fstream>

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Brick.h"
#include "Goomba.h"
#include "FirePots.h"
#include "Map.h"
//#include "Camera.h";
#include "GameMap.h";

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_FIREPOTS 30
#define ID_TEX_MAP 40
CGame *game;

Simon *simon;
CGoomba *goomba;
FirePots *firepots;
Map *map;
Camera* camera;
GameMap* gameMap;

vector<LPGAMEOBJECT> objects;
vector<LPGAMEOBJECT> objects2;
//vector<LPGAMEOBJECT> GameMap;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_A: // reset
		simon->SetState(SIMON_STATE_IDLE);
		//simon->SetLevel(MARIO_LEVEL_BIG);
		simon->SetPosition(50.0f, 0.0f);
		simon->SetSpeed(0, 0);
		break;
	case DIK_Z:
		simon->SetState(SIMON_STATE_ATTACK);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die 
	if (simon->GetState() == SIMON_STATE_DIE) return;
	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (simon->isAttack())
			return;
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (simon->isAttack())
			return;
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	else
		simon->SetState(SIMON_STATE_IDLE);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	gameMap = new GameMap(L"textures\\map\\Level1Entrance.png", ID_TEX_MAP, 40, 0);
	gameMap->LoadMap("textures\\map\\Level1Entrance.txt");

	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_SIMON, L"textures\\Simon.png", D3DCOLOR_XRGB(0, 128, 128));
	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_FIREPOTS, L"textures\\FirePots.png", D3DCOLOR_XRGB(34, 177, 76));
	textures->Add(ID_TEX_MAP, L"textures\\Map.png", D3DCOLOR_XRGB(0,0,0));

	//textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);

	ifstream infile;
	infile.open("Simon.txt");
	int arr[5];
	while (infile)
	{
		infile >> arr[0] >> arr[1] >> arr[2] >> arr[3] >> arr[4];
		sprites->Add(arr[0], arr[1], arr[2], arr[3], arr[4], texSimon);
	}
	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 408, 225, 424, 241, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add(30001, 5, 14, 21, 29, texEnemy);
	sprites->Add(30002, 25, 14, 41, 29, texEnemy);

	sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite

	LPDIRECT3DTEXTURE9 texFirePots = textures->Get(ID_TEX_FIREPOTS);
	sprites->Add(20002, 3, 4, 19, 36, texFirePots);
	sprites->Add(20003, 30, 4, 46, 36, texFirePots);

	LPDIRECT3DTEXTURE9 texMap = textures->Get(ID_TEX_MAP);
	sprites->Add(0, 0, 0, 32, 32, texMap);
	sprites->Add(1, 32, 0, 64, 32, texMap);
	sprites->Add(2, 64, 0, 96, 32, texMap);
	sprites->Add(3, 92, 0, 128, 32, texMap);
	sprites->Add(4, 124, 0, 160, 32, texMap);

	LPANIMATION ani;
	/*infile.open("SimonAni.txt"); int n;
	while(infile)
	{
		infile >> n;
		if (n < 10)
		{
			infile.ignore('\n');
			while (infile)
			{
				int *arr = new int[n];
				for (int i=0;i<n;i++)
				{
					infile >> arr[i];
					ani->Add(arr[i]);
					infile.ignore('\n');
				}
				for
			}
		}

	}*/
	ani = new CAnimation(100);	//simon idle right
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new CAnimation(100);	// idle left
	ani->Add(10011);
	animations->Add(401, ani);


	ani = new CAnimation(100);	// simon walk right big
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new CAnimation(100);	// walk left big
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	ani = new CAnimation(100);	//simon attack right;
	ani->Add(10004);
	ani->Add(10005);
	ani->Add(10006);
	animations->Add(502, ani);

	ani = new CAnimation(100);	//simon attack left;
	ani->Add(10014);
	ani->Add(10015);
	ani->Add(10016);
	animations->Add(503, ani);

	ani = new CAnimation(100);		//simon die
	ani->Add(10099);
	animations->Add(599, ani);


	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);
	
	ani = new CAnimation(100);
	ani->Add(20002);
	ani->Add(20003);
	animations->Add(602, ani);

	ani = new CAnimation(100);
	ani->Add(0);
	animations->Add(603, ani);
	ani = new CAnimation(100);
	ani->Add(1);
	animations->Add(604, ani);
	ani = new CAnimation(100);
	ani->Add(2);
	animations->Add(605, ani);
	ani = new CAnimation(100);
	ani->Add(3);
	animations->Add(606, ani);
	ani = new CAnimation(100);
	ani->Add(4);
	animations->Add(607, ani);
	//ani = new CAnimation(300);		// Goomba walk
	//ani->Add(30001);
	//ani->Add(30002);
	//animations->Add(701, ani);
	//ani = new CAnimation(1000);		// Goomba dead
	//ani->Add(30003);
	//animations->Add(702, ani);

	simon = new Simon();
	simon->AddAnimation(400);		// idle right big
	simon->AddAnimation(401);		// idle left big

	simon->AddAnimation(500);		// walk right big
	simon->AddAnimation(501);		// walk left big
	simon->AddAnimation(599);		// die
	simon->AddAnimation(502);		//attack right
	simon->AddAnimation(503);		//attack left
	simon->SetPosition(100.0f, 0);
	objects.push_back(simon);



	for (int i = 0; i < 30; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(0 + i * 16.0f, 150);
		objects.push_back(brick);
	}
	for (int i = 0; i < 3; i++)
	{
		FirePots *firepots = new FirePots();
		firepots->AddAnimation(602);
		firepots->SetPosition(255 + i * 100.0f, 119);
		objects2.push_back(firepots);
	}
	//// and Goombas 
	//for (int i = 0; i < 4; i++)
	//{
	//	goomba = new CGoomba();
	//	goomba->AddAnimation(701);
	//	goomba->AddAnimation(702);
	//	goomba->SetPosition(200 + i * 60, 135);
	//	goomba->SetState(GOOMBA_STATE_WALKING);
	//	objects.push_back(goomba);
	//}
	//int x = 603, n = 0;
	//for (int i = 0; i < 5; i++)
	//{
	//	map = new Map();
	//	map->AddAnimation(x);
	//	map->SetPosition(-65+ i*n,0 );
	//	GameMap.push_back(map);
	//	x++;
	//	n = 31.0f;
	//}
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}


	// Update camera to follow simon
	float cx, cy;
	simon->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	camera = Camera::getInstance();
	camera->setPosition(cx, 0.0f);
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	camera = Camera::getInstance();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Render();
		}
		for (int i = 0; i < objects2.size(); i++)
		{
			objects2[i]->Render();
		}
		//for (int i = 0; i < GameMap.size(); i++)
		//{
		//	GameMap[i]->Render();
		//}
		spriteHandler->End();
		d3ddv->EndScene();
		gameMap->DrawMap(camera);
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);

	//render map
	gameMap->DrawMap(camera);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}