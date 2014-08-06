package com.doteyplay.game.config.template;

import com.doteyplay.game.util.SimpleReflectUtils;
import com.doteyplay.game.util.excel.ExcelCellBinding;
import com.doteyplay.game.util.excel.ExcelRowBinding;
import com.doteyplay.game.util.excel.TemplateConfigException;
import com.doteyplay.game.util.excel.TemplateObject;

@ExcelRowBinding
public class BattleDataTemplate extends TemplateObject {

	/**
	 * ս������id
	 */
	@ExcelCellBinding
	protected String battleNameId;

	/**
	 * ս������Id
	 */
	@ExcelCellBinding
	protected String battleDescId;
	/**
	 * ������1Id
	 */
	@ExcelCellBinding
	protected int monsterGroup1Id;
	/**
	 * ������2Id
	 */
	@ExcelCellBinding
	protected int monsterGroup2Id;
	/**
	 * ������3Id
	 */
	@ExcelCellBinding
	protected int monsterGroup3Id;
	/**
	 * ������4Id
	 */
	@ExcelCellBinding
	protected int monsterGroup4Id;
	/**
	 * ������5Id
	 */
	@ExcelCellBinding
	protected int monsterGroup5Id;

	/**
	 * ��Ϸ��
	 */
	@ExcelCellBinding
	protected int gameCoin;
	/**
	 * ���ﾭ��
	 */
	@ExcelCellBinding
	protected int petExp;
	/**
	 * ������
	 */
	@ExcelCellBinding
	protected int dropGroupId;
	/**
	 * ����Id
	 */
	@ExcelCellBinding
	protected int sceneId;

	public void check() throws TemplateConfigException {
		// TODO Auto-generated method stub
	}

	public String getBattleNameId() {
		return battleNameId;
	}

	public void setBattleNameId(String battleNameId) {
		this.battleNameId = battleNameId;
	}

	public String getBattleDescId() {
		return battleDescId;
	}

	public void setBattleDescId(String battleDescId) {
		this.battleDescId = battleDescId;
	}

	public int getMonsterGroup1Id() {
		return monsterGroup1Id;
	}

	public void setMonsterGroup1Id(int monsterGroup1Id) {
		this.monsterGroup1Id = monsterGroup1Id;
	}

	public int getMonsterGroup2Id() {
		return monsterGroup2Id;
	}

	public void setMonsterGroup2Id(int monsterGroup2Id) {
		this.monsterGroup2Id = monsterGroup2Id;
	}

	public int getMonsterGroup3Id() {
		return monsterGroup3Id;
	}

	public void setMonsterGroup3Id(int monsterGroup3Id) {
		this.monsterGroup3Id = monsterGroup3Id;
	}

	public int getMonsterGroup4Id() {
		return monsterGroup4Id;
	}

	public void setMonsterGroup4Id(int monsterGroup4Id) {
		this.monsterGroup4Id = monsterGroup4Id;
	}

	public int getMonsterGroup5Id() {
		return monsterGroup5Id;
	}

	public void setMonsterGroup5Id(int monsterGroup5Id) {
		this.monsterGroup5Id = monsterGroup5Id;
	}

	public int getGameCoin() {
		return gameCoin;
	}

	public void setGameCoin(int gameCoin) {
		this.gameCoin = gameCoin;
	}

	public int getPetExp() {
		return petExp;
	}

	public void setPetExp(int petExp) {
		this.petExp = petExp;
	}

	public int getDropGroupId() {
		return dropGroupId;
	}

	public void setDropGroupId(int dropGroupId) {
		this.dropGroupId = dropGroupId;
	}

	public int getSceneId() {
		return sceneId;
	}

	public void setSceneId(int sceneId) {
		this.sceneId = sceneId;
	}

	@Override
	public String toString() {
		// TODO Auto-generated method
		return super.toString()+SimpleReflectUtils.reflect(this);
	}

}