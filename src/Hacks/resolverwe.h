// #pragma once

// #include "../SDK/IGameEvent.h"
// #include "../SDK/definitions.h"
// #include <cstdint>
// #include <vector>

// #include "../Utils/entity.h"
// #include "../Utils/math.h"
// #include "../Utils/xorstring.h"
// #include "../interfaces.h"
// #include "../settings.h"
// #include "antiaim.h"
// #include "ragebot.h"

// namespace CResolver
// {

//     struct resolvedPlayers
//     {
//         C_BasePlayer* enemy;
//         int PrevTrueDelta = 0;
//         int MissedCount = 0;
//     };

//     inline resolvedPlayers players[1000];
//     inline std::pair<C_BasePlayer*, int> player;
//     inline int TargetID = 0;
//     extern std::vector<int64_t> Players;
//         float GetLeftYaw(C_BasePlayer*);
//         float GetRightYaw(C_BasePlayer*);
//         bool TargetSide(C_BasePlayer*);
//         void DetectSide(C_BasePlayer*, int*);
//         bool TargetJitter(C_BasePlayer*, bool);
//         bool DoesHaveJitter(C_BasePlayer*, int*);
//         int FreestandSide[64];
//       float GetAngle(C_BasePlayer*);
//         float GetForwardYaw(C_BasePlayer*);
//         float GetBackwardYaw(C_BasePlayer*);
//         void Do(C_BasePlayer*);
//         void StoreAntifreestand();
// bool IsNearEqual(float*, float*, float*)

//     //Hooks
//     void FrameStageNotify(ClientFrameStage_t stage); // This is where the resolver happens.
//     void FireGameEvent(IGameEvent *event);			 // Strangely, I never see this getting called.
//     void CreateMove(CUserCmd* cmd);
//     void AnimationFix(C_BasePlayer *player);

// } 
