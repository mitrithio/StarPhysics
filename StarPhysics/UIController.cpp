#include "UIController.h"
#include "../My_Libs/My_Libs.h"
#include "Character.h"
#include "Environment.h"
#include <cstdlib>
#include <string>

/*OTTIMIZZAZIONE ADVACED C++
Allocazione in memoria-> - 8 variabili non-allocate ui_font_H1, ui_font_H2, ui_font_H3, ui_interface_img, ui_hotkey_img, ui_redcross_img, ui_chicken_img, ui_joystick_img

Eliminati 8 IF nella funzione DrawTimeSpeed

Rimossi 10 Warnings dovuti alla funzione itoa, sostituita con _itoa_s. 
Rimossa la dichiarazione ci 8 variabili char[3] sostituite con 1 buffer che viene riutilizzato.

*/


UIController::UIController(Character *i_agent, Environment *i_world, My_Time *i_time) : ui_time(i_time)
																				      , ui_agent(i_agent)
																					  , ui_world(i_world)
																					  , ui_font_H1(16, 0, 0, false, false, false, "Impact")
																					  , ui_font_H2(20, 0, 0, false, false, false, "Impact")
																					  ,	ui_font_H3(30, 0, 0, false, false, false, "Impact")
																					  , ui_interface_img("Images//ui_interface_img.tga")
																					  , ui_hotkey_img("Images//HotKey_Img.tga")
																					  , ui_redcross_img("Images//RedCross_Img.tga")
																					  , ui_chicken_img("Images//Chicken_Img.tga")
																					  , ui_joystick_img("Images//Joystick_Img.tga")
																					  //CORRETTI NELL' ORDINE
																					  
{
	//OTTIMIZZATI
	/*ui_font_H1 = new Font(16, 0, 0, false, false, false, "Impact");
	ui_font_H2 = new Font(20, 0, 0, false, false, false, "Impact");
	ui_font_H3 = new Font(30, 0, 0, false, false, false, "Impact");

	ui_interface_img = new Bitmap("Images//ui_interface_img.tga");
	ui_hotkey_img = new Bitmap("Images//HotKey_Img.tga");

	ui_redcross_img = new Bitmap("Images//RedCross_Img.tga");
	ui_chicken_img = new Bitmap("Images//Chicken_Img.tga");
	ui_joystick_img = new Bitmap("Images//Joystick_Img.tga");*/
}


UIController::~UIController()
{

}


//Disegna l'orologio sullo schermo acquisendo dalla classe time le informazioni e convertendole in stringhe
void UIController::DrawTime(Bitmap* renderTarget)
{
	char timeBufferUI[3];
	_itoa_s(ui_time->getSeconds(), timeBufferUI, 10);
	renderTarget->RenderText(215, 28, timeBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(215, 10, "sec", &ui_font_H1, 192, 192, 192);

	_itoa_s(ui_time->getMinutes(), timeBufferUI, 10);
	renderTarget->RenderText(185, 28, timeBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(185, 10, "min", &ui_font_H1, 192, 192, 192);

	_itoa_s(ui_time->getHours(), timeBufferUI, 10);
	renderTarget->RenderText(155, 28, timeBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(155, 10, "hour", &ui_font_H1, 192, 192, 192);

	_itoa_s(ui_time->getDays(), timeBufferUI, 10);
	renderTarget->RenderText(125, 28, timeBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(125, 10, "day", &ui_font_H1, 192, 192, 192);

	_itoa_s(ui_time->getYears(), timeBufferUI, 10);
	renderTarget->RenderText(95, 28, timeBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(95, 10, "year", &ui_font_H1, 192, 192, 192);

	//OTTIMIZZATI
	/*char secondsUI[3];
	renderTarget->RenderText(215, 28, itoa(ui_time->getSeconds(), secondsUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(215, 10, "sec", &ui_font_H1, 192, 192, 192);

	char minutesUI[3];
	renderTarget->RenderText(185, 28, itoa(ui_time->getMinutes(), minutesUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(185, 10, "min", &ui_font_H1, 192, 192, 192);

	char hoursUI[3];
	renderTarget->RenderText(155, 28, itoa(ui_time->getHours(), hoursUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(155, 10, "hour", &ui_font_H1, 192, 192, 192);

	char daysUI[3];
	renderTarget->RenderText(125, 28, itoa(ui_time->getDays(), daysUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(125, 10, "day", &ui_font_H1, 192, 192, 192);

	char yearsUI[3];
	renderTarget->RenderText(95, 28, itoa(ui_time->getYears(), yearsUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(95, 10, "year", &ui_font_H1, 192, 192, 192);
	*/

}


//Disegna la temperatura dell'ambiente acquisendo dalla classe environment le informazioni e convertendole in stringhe
void UIController::DrawTemperature(Bitmap* renderTarget)
{

	char tempertaureUI[4];
	_itoa_s(int(ui_world->getTemperature()), tempertaureUI, 10);
	renderTarget->RenderText(20, 10, tempertaureUI, &ui_font_H3, 192, 0, 0);
	renderTarget->RenderText(42, 10, "°C", &ui_font_H2, 192, 192, 192);

	//OTTIMIZZATI
	/*
	char tempertaureUI[4];
	renderTarget->RenderText(20, 10, itoa(int(ui_world->getTemperature()), tempertaureUI, 10), &ui_font_H3, 192, 0, 0);
	renderTarget->RenderText(42, 10, "°C", &ui_font_H2, 192, 192, 192);
	*/
}

//Disegna la velocità del tempo acquisendo dalla classe time le informazioni e selezionando la stringa corrispettiva
void UIController::DrawTimeSpeed(Bitmap* renderTarget)
{
	std::string x = std::to_string(ui_time->getTimeSpeed());
	char *tmp = new char[x.length() + 1];

	std::strcpy(tmp, x.c_str());

	renderTarget->RenderText(250, 10, tmp, &ui_font_H3, 192, 0, 0);

	delete[] tmp;

	//OTTIMZZATI
	/*if (timeSpeed == 1)
	{
		renderTarget->RenderText(250, 10, "1x", &ui_font_H3, 192, 0, 0);
	}
	else if (timeSpeed == 2)
	{
		renderTarget->RenderText(250, 10, "2x", &ui_font_H3, 192, 0, 0);
	}
	else if (timeSpeed == 16)
	{
		renderTarget->RenderText(250, 10, "16x", &ui_font_H3, 192, 0, 0);
	}
	else if (timeSpeed == 128)
	{
		renderTarget->RenderText(250, 10, "128x", &ui_font_H3, 192, 0, 0);
	}
	else if (timeSpeed == 512)
	{
		renderTarget->RenderText(250, 10, "512x", &ui_font_H3, 192, 0, 0);
	}
	else if (timeSpeed == 1024)
	{
		renderTarget->RenderText(250, 10, "1024x", &ui_font_H3, 192, 0, 0);
	}
	else if (timeSpeed == 4096)
	{
		renderTarget->RenderText(250, 10, "4096x", &ui_font_H3, 192, 0, 0);
	}*/
}


//Disegna i tasti utlizzabili dall'utente per le varie funzioni del gioco
void UIController::DrawHotKey(Bitmap* renderTarget)
{
	//TimeSpeed Hotkey = S
	ui_hotkey_img.DrawTo(renderTarget, 244, 35);
	renderTarget->RenderText(249, 35, "S", &ui_font_H1, 0, 0, 255);

	
	//Eat Hotkey = F
	if (ui_agent->getHunger() != 0)
	{
		ui_hotkey_img.DrawTo(renderTarget, 44, 530);
		renderTarget->RenderText(49, 530, "F", &ui_font_H1, 0, 0, 255);
	}
	//Heal Hotkey = H
	if (ui_agent->getLifePoint() != 10)
	{
		ui_hotkey_img.DrawTo(renderTarget, 134, 530);
		renderTarget->RenderText(139, 530, "H", &ui_font_H1, 0, 0, 255);
	}
	//Play Hotkey = P
	if (ui_agent->getHappines() != 10)
	{
		ui_hotkey_img.DrawTo(renderTarget, 224, 530);
		renderTarget->RenderText(229, 530, "P", &ui_font_H1, 0, 0, 255);
	}
}

//Disegna le statistiche dell'tamagotchi acquisendo dalla classe character le informazioni e convertendole in stringhe
void UIController::DrawCharacterStatistic(Bitmap* renderTarget)
{
	char statBufferUI[3];
	_itoa_s(ui_agent->getLifePoint(), statBufferUI, 10);
	renderTarget->RenderText(75, 468, statBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(76, 455, "LP", &ui_font_H1, 192, 192, 192);

	_itoa_s(ui_agent->getHunger(), statBufferUI, 10);
	renderTarget->RenderText(125, 468, statBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(126, 455, "HG", &ui_font_H1, 192, 192, 192);

	_itoa_s(ui_agent->getEnergy(), statBufferUI, 10);
	renderTarget->RenderText(175, 468, statBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(176, 455, "EN", &ui_font_H1, 192, 192, 192);

	_itoa_s(ui_agent->getHappines(), statBufferUI, 10);
	renderTarget->RenderText(225, 468, statBufferUI, &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(226, 455, "HY", &ui_font_H1, 192, 192, 192);

	//OTTIMIZZATI
	/*
	char lpUI[3];
	renderTarget->RenderText(75, 468, itoa(ui_agent->getLifePoint(), lpUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(76, 455, "LP", &ui_font_H1, 192, 192, 192);

	char hgUI[3];
	renderTarget->RenderText(125, 468, itoa(ui_agent->getHunger(), hgUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(126, 455, "HG", &ui_font_H1, 192, 192, 192);

	char enUI[3];
	renderTarget->RenderText(175, 468, itoa(ui_agent->getEnergy(), enUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(176, 455, "EN", &ui_font_H1, 192, 192, 192);

	char hyUI[3];
	renderTarget->RenderText(225, 468, itoa(ui_agent->getHappines(), hyUI, 10), &ui_font_H2, 192, 0, 0);
	renderTarget->RenderText(226, 455, "HY", &ui_font_H1, 192, 192, 192);
	*/
}

//disegna le icone per le 3 funzioni attivabili dal player
void UIController::DrowPlayerInput(Bitmap* renderTarget)
{
	ui_chicken_img.DrawTo(renderTarget, 44, 490);
	ui_redcross_img.DrawTo(renderTarget, 134, 490);
	ui_joystick_img.DrawTo(renderTarget, 224, 490);
}

//effettua la drow di tutta la UI tenendo conto dei livelli di disegno e della possibilità che il tamagotchi sia morto
//in tal caso disegna la scritta GAME OVER
void UIController::Draw(Bitmap* renderTarget)
{ 
	ui_interface_img.DrawTo(renderTarget, 0, 0);
	DrawTemperature(renderTarget);
	DrawTime(renderTarget);
	DrawCharacterStatistic(renderTarget);
	DrowPlayerInput(renderTarget);

	if (!ui_agent->getIsDead())
	{
		DrawTimeSpeed(renderTarget);
		DrawHotKey(renderTarget);
	}
	else
	{
		renderTarget->RenderText(110, 255, "GAME OVER", &ui_font_H3, 192, 0, 0);
	}
}