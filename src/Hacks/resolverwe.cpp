// #include "resolverwe.h"

// #include "../ImGUI/imgui.h"
// std::vector<int64_t> CResolver::Players = {};

// #define RANDOME_FLOAT(x) ( static_cast<float>(static_cast<float>(rand()/ static_cast<float>(RAND_MAX/ ( x ) ))) )
// #define GetPercentVal(val, percent) (val * (percent/100.f))
//         C_BasePlayer *localplayer = (C_BasePlayer *)entityList->GetClientEntity(engine->GetLocalPlayer());

// static float NormalizeAsYaw(float flAngle)
// {
// 	if (flAngle > 180.f || flAngle < -180.f)
// 	{
// 		auto revolutions = round(abs(flAngle / 360.f));

// 		if (flAngle < 0.f)
// 			flAngle += 360.f * revolutions;
// 		else
// 			flAngle -= 360.f * revolutions;
// 	}

// 	return flAngle;
// }
// bool IsNearEqual(float v1, float v2, float Tolerance)
// {
//         return std::abs(v1 - v2) <= std::abs(Tolerance);
// };

// void CResolver::AnimationFix(C_BasePlayer *player)
// {
// 	// player->ClientAnimations(true);

// 	auto old_curtime = globalVars->curtime;
// 	auto old_frametime = globalVars->frametime;

// 	globalVars->curtime = player->GetSimulationTime();
// 	globalVars->frametime = globalVars->interval_per_tick;

// 	auto player_animation_state = player->GetAnimState();
// 	// auto player_model_time = reinterpret_cast<int*>(player_animation_state + 112);
// 	// if (player_animation_state && player_model_time)
// 	// 	if (*player_model_time == globalVars->frametime)
// 	// 		* player_model_time = globalVars->frametime - 1;


// 	// player->updateClientAnimation();

// 	globalVars->curtime = old_curtime;
// 	globalVars->frametime = old_frametime;

// 	//pEnt->SetAbsAngles(Vector3(0, player_animation_state->goalFeetYaw, 0));

// 	// player->ClientAnimations(false);
// }
// std::string ResolverMode[65];
// int last_ticks[65];

// float CResolver::GetAngle(C_BasePlayer* player) {
// 	return NormalizeAsYaw(player->GetEyeAngles()->y);
// }

// float CResolver::GetForwardYaw(C_BasePlayer* player) {
// 	return NormalizeAsYaw(GetBackwardYaw(player) - 180.f);
// }

// float CResolver::GetBackwardYaw(C_BasePlayer* player) {
// 	return Math::CalcAngle(localplayer->GetAbsOrigin(), player->GetAbsOrigin()).y;
// }

// float CResolver::GetLeftYaw(C_BasePlayer* player) {
// 	return NormalizeAsYaw(Math::CalcAngle(localplayer->GetAbsOrigin(), player->GetAbsOrigin()).y - 90.f);
// }

// float CResolver::GetRightYaw(C_BasePlayer* player) {
// 	return NormalizeAsYaw(Math::CalcAngle(localplayer->GetAbsOrigin(), player->GetAbsOrigin()).y + 90.f);
// }
// bool CResolver::TargetJitter(C_BasePlayer* player, bool v2) {
// 	float yaw = v2 ? GetRightYaw(player) : GetLeftYaw(player);
// 	return fabsf(GetAngle(player) - NormalizeAsYaw(yaw + 90.f))
// 		>= fabsf(GetAngle(player) - NormalizeAsYaw(yaw - 90.f));
// }
// bool CResolver::TargetSide(C_BasePlayer* player) {
// 	float yaw = NormalizeAsYaw(GetBackwardYaw(player));
// 	float angle = GetAngle(player);
// 	return fabsf(angle - NormalizeAsYaw(yaw + 90.f))
// 		>= fabsf(angle - NormalizeAsYaw(yaw - 90.f));
// }

// void CResolver::DetectSide(C_BasePlayer* player, int *side)
// {
// 	Vector src3D, dst3D, forward, right, up, src, dst;
// 	float back_two, right_two, left_two;
// 	trace_t tr;
// 	Ray_t ray, ray2, ray3, ray4, ray5;
// 	CTraceFilter filter;

// 	Math::AngleVectors(Vector(0, GetBackwardYaw(player), 0), &forward, &right, &up);

// 	filter.pSkip = player;
// 	src3D = player->GetEyePosition();
// 	dst3D = src3D + (forward * 384); //Might want to experiment with other numbers, incase you don't know what the number does, its how far the trace will go. Lower = shorter.

// 	ray.Init(src3D, dst3D);
// 	trace->TraceRay(ray, MASK_SHOT, &filter, &tr);
// 	back_two = (tr.endpos - tr.startpos).Length();

// 	ray2.Init(src3D + right * 35, dst3D + right * 35);
// 	trace->TraceRay(ray2, MASK_SHOT, &filter, &tr);
// 	right_two = (tr.endpos - tr.startpos).Length();

// 	ray3.Init(src3D - right * 35, dst3D - right * 35);
// 	trace->TraceRay(ray3, MASK_SHOT, &filter, &tr);
// 	left_two = (tr.endpos - tr.startpos).Length();

// 	if (left_two > right_two) {
// 		*side = -1;
// 		//Body should be right
// 	}
// 	else if (right_two > left_two) {
// 		*side = 1;
// 	}
// 	else
// 		*side = 0;
// }

// bool CResolver::DoesHaveJitter(C_BasePlayer* player, int *new_side) {
// 	static float LastAngle[64];
// 	static int LastBrute[64];
// 	static bool Switch[64];
// 	static float LastUpdateTime[64];

// 	int i = player->GetIndex();

// 	float CurrentAngle = player->GetEyeAngles()->y;
// 	if (!IsNearEqual(CurrentAngle, LastAngle[i], 50.f)) {
// 		Switch[i] = !Switch[i];
// 		LastAngle[i] = CurrentAngle;
// 		*new_side = Switch[i] ? 1 : -1;
// 		LastBrute[i] = *new_side;
// 		LastUpdateTime[i] = globalVars->curtime;
// 		return true;
// 	}
// 	else {
// 		if (fabsf(LastUpdateTime[i] - globalVars->curtime >= TICKS_TO_TIME(17))) {
// 			LastAngle[i] = CurrentAngle;
// 		}
// 		*new_side = LastBrute[i];
// 	}
// 	return false;
// }


// void CResolver::StoreAntifreestand()
// {
// 	if (!localplayer->GetAlive())
// 		return;

// 	if (!csgo->weapon->IsGun())
// 		return;


// 	for (int i = 1; i < engine->GetMaxClients(); ++i)
// 	{
// 		auto player = Interfaces.ent_list->GetClientEntity(i);

// 		if (!player || !player->GetAlive() || player->IsDormant() || player->GetTeam() == localplayer->GetTeam())
// 			continue;

// 		bool Autowalled = false, HitSide1 = false, HitSide2 = false;
// 		auto idx = player->GetIndex();
// 		float angToLocal = Math::CalcAngle(localplayer->GetAbsOrigin(), player->GetAbsOrigin()).y;
// 		Vector ViewPoint = localplayer->GetAbsOrigin() + Vector(0, 0, 90);
// 		Vector2D Side1 = { (45 * sin(DEG2RAD(angToLocal))),(45 * cos(DEG2RAD(angToLocal))) };
// 		Vector2D Side2 = { (45 * sin(DEG2RAD(angToLocal + 180))) ,(45 * cos(DEG2RAD(angToLocal + 180))) };

// 		Vector2D Side3 = { (50 * sin(DEG2RAD(angToLocal))),(50 * cos(DEG2RAD(angToLocal))) };
// 		Vector2D Side4 = { (50 * sin(DEG2RAD(angToLocal + 180))) ,(50 * cos(DEG2RAD(angToLocal + 180))) };

// 		Vector Origin = player->GetAbsOrigin();

// 		Vector2D OriginLeftRight[] = { Vector2D(Side1.x, Side1.y), Vector2D(Side2.x, Side2.y) };

// 		Vector2D OriginLeftRightLocal[] = { Vector2D(Side3.x, Side3.y), Vector2D(Side4.x, Side4.y) };

// 		for (int side = 0; side < 2; side++)
// 		{
// 			Vector OriginAutowall = { Origin.x + OriginLeftRight[side].x,  Origin.y - OriginLeftRight[side].y , Origin.z + 90 };
// 			Vector ViewPointAutowall = { ViewPoint.x + OriginLeftRightLocal[side].x,  ViewPoint.y - OriginLeftRightLocal[side].y , ViewPoint.z };

// 			if (AutoWall.CanHitFloatingPoint(OriginAutowall, ViewPoint))
// 			{
// 				if (side == 0)
// 				{
// 					HitSide1 = true;
// 					FreestandSide[idx] = -1;
// 				}
// 				else if (side == 1)
// 				{
// 					HitSide2 = true;
// 					FreestandSide[idx] = 1;
// 				}

// 				Autowalled = true;
// 			}
// 			else
// 			{
// 				for (int sidealternative = 0; sidealternative < 2; sidealternative++)
// 				{
// 					Vector ViewPointAutowallalternative = { Origin.x + OriginLeftRight[sidealternative].x,  Origin.y - OriginLeftRight[sidealternative].y , Origin.z + 90 };

// 					if (AutoWall.CanHitFloatingPoint(ViewPointAutowallalternative, ViewPointAutowall))
// 					{
// 						if (sidealternative == 0)
// 						{
// 							HitSide1 = true;
// 							FreestandSide[idx] = -1;
// 							//FreestandAngle[pPlayerEntity->EntIndex()] = 90;
// 						}
// 						else if (sidealternative == 1)
// 						{
// 							HitSide2 = true;
// 							FreestandSide[idx] = 1;
// 							//FreestandAngle[pPlayerEntity->EntIndex()] = -90;
// 						}

// 						Autowalled = true;
// 					}
// 				}
// 			}
// 		}
// 	}
// }


// void CResolver::Do(C_BasePlayer* player) {
// 	auto animstate = player->GetAnimState();
// 	if (!animstate)
// 		return;
// 	animstate->goalFeetYaw = GetAngle(player);
// 	if (!vars.ragebot.resolver)
// 		return;

// 	int idx = player->GetIndex();

// 	float angle = GetAngle(player);
// 	int new_side = 0;
// 	/*if (DoesHaveJitter(player, &new_side) && player->GetEyeAngles().x < 45) {
// 		switch (csgo->missedshots[idx] % 2) {
// 		case 0:
// 			ResolverMode[idx] = "AB"();
// 			animstate->goalFeetYaw = NormalizeAsYaw(angle + 90.f * new_side);
// 			break;
// 		case 1:
// 			ResolverMode[idx] = "AC"();
// 			animstate->goalFeetYaw = NormalizeAsYaw(angle - 90.f * new_side);
// 			break;
// 		}
// 	}
// 	else*/
// 	{
// 		bool forward = fabsf(NormalizeAsYaw(GetAngle(player) - GetForwardYaw(player))) < 90.f;
// 		if (CResolver::players[player->GetIndex()].MissedCount == 0) {
// 			/*ResolverMode[idx] = "C";

// 			if (forward) {
// 				FreestandSide[idx] *= -1;
// 				ResolverMode[idx] += "B";
// 			}
// 			else
// 				ResolverMode[idx] += "A";
// 			animstate->goalFeetYaw = NormalizeAsYaw(angle - 90.f * FreestandSide[idx]);
// 		}
// 		else {*/
// 			if (forward) {
// 				switch (CResolver::players[player->GetIndex()].MissedCount % 2) {
// 				case 1:
// 					ResolverMode[idx] = "DA";
// 					if (FreestandSide[idx] == 1)
// 						animstate->goalFeetYaw = NormalizeAsYaw(angle - 90.f);
// 					else
// 						animstate->goalFeetYaw = NormalizeAsYaw(angle + 90.f);
// 					break;
// 				case 0:
// 					ResolverMode[idx] = "DB";
// 					if (FreestandSide[idx] == 1)
// 						animstate->goalFeetYaw = NormalizeAsYaw(angle + 90.f);
// 					else
// 						animstate->goalFeetYaw = NormalizeAsYaw(angle - 90.f);
// 					break;
// 				}
// 			}
// 			else {
// 				switch (csgo->missedshots[idx] % 2) {
// 				case 1:
// 					ResolverMode[idx] = "DA";
// 					if (FreestandSide[idx] == 1)
// 						animstate->goalFeetYaw = NormalizeAsYaw(angle + 90.f);
// 					else
// 						animstate->goalFeetYaw = NormalizeAsYaw(angle - 90.f);
// 					break;
// 				case 0:
// 					ResolverMode[idx] = "DB";
// 					if (FreestandSide[idx] == 1)
// 						animstate->goalFeetYaw = NormalizeAsYaw(angle - 90.f);
// 					else
// 						animstate->goalFeetYaw = NormalizeAsYaw(angle + 90.f);
// 					break;
// 				}
// 			}
// 		}
// 	}

// 	animstate->goalFeetYaw = NormalizeAsYaw(animstate->goalFeetYaw);
// }
