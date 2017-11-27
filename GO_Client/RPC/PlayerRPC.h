#ifndef PLAYERRPC_H
#define PLAYERRPC_H

namespace PlayerRPC
{
	void HandlePlayerRPC(CNetwork* network, Packet* packet);
	
	void CreatePlayer(CNetwork* network, BitStream& stream);
	void CreateAndSpawnPlayer(BitStream& stream);
	void DestroyPlayer(CNetwork* network, BitStream& stream);

	void Spawn(CNetwork* network, BitStream& stream);
	void Unspawn(CNetwork* network, BitStream& stream);

	void SetPosition(BitStream& stream);
	void SetAngle(BitStream& stream);
	void PlayAnimation(BitStream& stream);
	void ChangeWeaponMode(BitStream& stream);
	void WearArmor(BitStream& stream) ;
	void EquipWeapon(BitStream& stream) ;
	void ChangeInstance(BitStream& stream);
	void ItemHand(BitStream& stream);
	void SetHealth(BitStream& stream);
	void SetHealthMax(BitStream& stream);
	void AttackHit(BitStream& stream);
	void AttackDead(BitStream& stream);
	void AttackUnconscious(BitStream& stream);
	void StandUp(BitStream& stream);
	void MagicSetup(BitStream& stream);
	void MagicAttack(BitStream& stream);
	void PlayerList(BitStream& stream);
	//void SetProtection(BitStream& stream);
	void SetOverlay(BitStream& stream);
	void MobTrigger(BitStream& stream);
	void ShootArrow(BitStream& stream);
	void ForceStandUp(BitStream& stream);
};

#endif //PLAYERRPC_H