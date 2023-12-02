/*
* @file		Model.h
* @brief	�N���X Model �̐錾
* @note		
* 
*/
#pragma once


class Model
{
public:
	Model();
	~Model();
	virtual void LoadPlayerModel();	// Player���f���ǂݍ��݃��\�b�h
	virtual void LoadEnemyModel();	// Enemy���f���ǂݍ��݃��\�b�h
	virtual void LoadTileModel();	// Tile���f���ǂݍ��݃��\�b�h
	virtual int GetPlayerModel();	// Player���f���擾���\�b�h
	virtual int GetEnemyModel();	// Enemy���f���擾���\�b�h
	virtual int GetTileModel();		// Tile���f���擾���\�b�h
protected:
	int		playerHandle;
	int		enemyHandle;
	int		tileHandle;
};