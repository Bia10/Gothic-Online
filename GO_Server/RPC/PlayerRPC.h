#ifndef PLAYERRPC_H
#define PLAYERRPC_H

namespace PlayerRPC
{
	void HandlePlayerRPC(CNetwork* network, Packet* packet);

	void SetPosition(Packet* packet, BitStream& stream);
	void SetAngle(Packet* packet, BitStream& stream);
	void PlayAnimation(Packet* packet, BitStream& stream);
	void ChangeWeaponMode(Packet* packet, BitStream& stream);
	void WearArmor(Packet* packet, BitStream& stream);
	void EquipWeapon(Packet* packet, BitStream& stream);
	void ChangeInstance(Packet* packet, BitStream& stream);
	void ItemHand(Packet* packet, BitStream& stream);
	void ChangeLevel(Packet* packet, BitStream& stream);
	void EnterWorld(Packet* packet);
	void SetHealth(Packet* packet, BitStream& stream);
	void SetHealthMax(Packet* packet, BitStream& stream);
	void AttackHit(Packet* packet, BitStream& stream);
	void AttackDead(Packet* packet, BitStream& stream);
	void AttackUnconscious(Packet* packet, BitStream& stream);
	void StandUp(Packet* packet, BitStream& stream);
	void MagicSetup(Packet* packet, BitStream& stream);
	void MagicAttack(Packet* packet, BitStream& stream);
	//void SetProtection(Packet* packet, BitStream& stream);
	void SetOverlay(Packet* packet, BitStream& stream);
	void SetTimedOverlay(Packet* packet, BitStream& stream);
	void MobTrigger(Packet* packet, BitStream& stream);
	void ShootArrow(Packet* packet, BitStream& stream);
};

#endif //PLAYERRPC_H