package com.doteyplay.game.constants;

/**
 * 伤害类型
 * @author AllenGao
 *
 */
public enum DamageType
{	
	//无视防御
		NOTCARE()
		{
			@Override
			public String toString()
			{
				return "无视防御";
			}
		},
	//物理
	PHYSICS()
	{
		@Override
		public String toString()
		{
			return "物理";
		}
	},
	//法术
	MAGIC()
	{
		@Override
		public String toString()
		{
			return "法术";
		}
	},
	
}
