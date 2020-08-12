#include <string>
#include "voterevealer.h"
#include "../Utils/xorstring.h"
#include "../Utils/entity.h"
#include "../settings.h"
#include "../fonts.h"
#include "../interfaces.h"
#include "../Utils/draw.h"
#include "../Hooks/hooks.h"

void VoteRevealer::FireGameEvent(IGameEvent *event){

if (!Settings::voterevealer::enabled)
	return;

if (strstr(event->GetName(), XORSTR("vote_cast"))){ 
	int vote_player_id = event->GetInt(XORSTR("entityid"));
//	std::string team = event->GetString(XORSTR("team"));
	IEngineClient::player_info_t playerInfo;
        engine->GetPlayerInfo( vote_player_id, &playerInfo );
//	cvar->ConsoleDPrintf(std::string(playerInfo.name).c_str());
//	cvar->ConsoleDPrintf(XORSTR(" Casted a vote\n"));
	int option = event->GetInt("vote_option");
        cvar->ConsoleDPrintf(std::string(playerInfo.name).c_str());
		if (option == 0){
        cvar->ConsoleDPrintf(XORSTR(" Voted yes\n"));
		}else{
        cvar->ConsoleDPrintf(XORSTR(" Voted no\n"));		
		}
	//cvar->ConsoleDPrintf(std::string(team).c_str());
}
	}
