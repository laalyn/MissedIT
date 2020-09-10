#include "fakelag.h"

#include "../settings.h"
#include "../interfaces.h"
#include "../Hooks/hooks.h"

int ticksMax = 20;

static void fakeDuck(CUserCmd* cmd )
{
	if (!Settings::AntiAim::FakeDuck::enabled)
		return;

	if (!inputSystem->IsButtonDown(Settings::AntiAim::FakeDuck::fakeDuckKey))
		return;

//	cmd->buttons |= IN_BULLRUSH;

	FakeLag::ticks = 14 ? cmd->buttons |= IN_DUCK : cmd->buttons &= ~IN_DUCK;
}
int random_int(int min, int max) {
   return min + rand() % (max - min);
}

static void randomLag(CUserCmd* cmd )
{
        if (!Settings::AntiAim::randomLag::enabled)
                return;
	if (Settings::FakeLag::adaptive)
		return;
        if (Settings::AntiAim::FakeDuck::enabled && inputSystem->IsButtonDown(Settings::AntiAim::FakeDuck::fakeDuckKey))
                return;

Settings::FakeLag::value = random_int(1, 14);
}

void FakeLag::CreateMove(CUserCmd* cmd)
{
//	fakeDuck( cmd ); // for fake ducking don't ask my why here

	if (!Settings::FakeLag::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer || !localplayer->GetAlive())
		return;

	if (localplayer->GetFlags() & FL_ONGROUND && Settings::FakeLag::adaptive)
		return;

	if (cmd->buttons & IN_ATTACK)
	{
		CreateMove::sendPacket = true;
		return;
	}

	if (FakeLag::ticks >= ticksMax)
	{
		CreateMove::sendPacket = true;
		FakeLag::ticks = 0;
	}
	else
	{
		if (Settings::FakeLag::adaptive)
		{
			int packetsToChoke;
			if (localplayer->GetVelocity().Length() > 0.f)
			{
				packetsToChoke = (int)((64.f / globalVars->interval_per_tick) / localplayer->GetVelocity().Length()) + 1;
				if (packetsToChoke >= 15)
					packetsToChoke = 14;
				if (packetsToChoke < Settings::FakeLag::value)
					packetsToChoke = Settings::FakeLag::value;
			}
			else
				packetsToChoke = 0;

			CreateMove::sendPacket = FakeLag::ticks < 16 - packetsToChoke;
		}
		else{
		if (!Settings::AntiAim::randomLag::enabled){
     auto velocity = localplayer->GetVelocity();
auto extrapolatedVelocity = sqrt(sqrt(velocity.x * velocity.y * velocity.z));
             auto requiredPacketsToBreakLagComp = 65 / extrapolatedVelocity;
     if (!(requiredPacketsToBreakLagComp < Settings::FakeLag::value) && requiredPacketsToBreakLagComp <= 16)
                CreateMove::sendPacket = FakeLag::ticks >= requiredPacketsToBreakLagComp;
            else
//                CreateMove::sendPacket  >= 16;
			CreateMove::sendPacket = FakeLag::ticks < 16 - Settings::FakeLag::value;

		}
		else {
CreateMove::sendPacket = FakeLag::ticks < 16 - random_int(1, 14);
		}
		}
	
	}

	FakeLag::ticks++;
}
