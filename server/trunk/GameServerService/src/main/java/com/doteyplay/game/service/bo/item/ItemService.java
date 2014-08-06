package com.doteyplay.game.service.bo.item;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;

import com.doteyplay.core.bhns.AbstractSimpleService;
import com.doteyplay.core.dbcs.DBCS;
import com.doteyplay.game.config.template.CreateDataTemplate;
import com.doteyplay.game.config.template.ItemDataObject;
import com.doteyplay.game.constants.common.RewardType;
import com.doteyplay.game.constants.item.OutfitInstallResult;
import com.doteyplay.game.constants.item.OutfitUpgradeResult;
import com.doteyplay.game.domain.gamebean.ItemBean;
import com.doteyplay.game.domain.gamebean.OutfitBean;
import com.doteyplay.game.domain.item.RoleItem;
import com.doteyplay.game.domain.outfit.Outfit;
import com.doteyplay.game.domain.pet.Pet;
import com.doteyplay.game.domain.role.Role;
import com.doteyplay.game.domain.sprite.AbstractSprite;
import com.doteyplay.game.message.common.CommonItemUpdateMessage;
import com.doteyplay.game.message.proto.ItemProBuf.PItemChangeLog;
import com.doteyplay.game.persistence.serverdata.item.IItemBeanDao;
import com.doteyplay.game.persistence.serverdata.outfit.IOutfitBeanDao;
import com.doteyplay.game.service.runtime.GlobalRoleCache;
import com.doteyplay.game.util.excel.TemplateService;

public class ItemService extends AbstractSimpleService<IItemService> implements
		IItemService
{
	private static final Logger logger = Logger.getLogger(ItemService.class);

	private ItemLock lock;

	private Map<Integer, RoleItem> bagItemMap = new HashMap<Integer, RoleItem>();
	private Map<Long, Outfit> outfitMap = new HashMap<Long, Outfit>();

	@Override
	public int getPortalId()
	{
		return IItemService.PORTAL_ID;
	}

	@Override
	public void initialize()
	{
		lock = new ItemLock(getServiceId());

		IOutfitBeanDao outfitDao = DBCS.getExector(IOutfitBeanDao.class);
		List<OutfitBean> outfitBeanList = outfitDao
				.selectOutfitBeanListByRoleId(getServiceId());
		Map<Long, OutfitBean> outfitBeanMap = new HashMap<Long, OutfitBean>();
		if (outfitBeanList != null)
		{
			for (OutfitBean bean : outfitBeanList)
				outfitBeanMap.put(bean.getPetId(), bean);
		}
		
		Role role = GlobalRoleCache.getInstance().getRoleById(getServiceId());
		for (Pet pet : role.getPetManager().getPetMap().values())
			outfitMap.put(pet.getId(), new Outfit(getServiceId(), pet,
					outfitBeanMap.get(pet.getId())));

		IItemBeanDao dao = DBCS.getExector(IItemBeanDao.class);
		List<ItemBean> itemBeanList = dao
				.selectItemBeanListByRoleId(getServiceId());

		if (itemBeanList != null)
		{
			for (ItemBean bean : itemBeanList)
			{
				RoleItem roleItem = new RoleItem(bean);

				bagItemMap.put(bean.getItemId(), roleItem);
			}
		}
	}

	public OutfitUpgradeResult upgradeQualityRemoveOutfit(long petId)
	{
		this.lockCheck();

		Outfit outfit = getOutfit(petId);
		if (outfit == null)
			return OutfitUpgradeResult.NOT_FOUND_SPRITE;

		boolean isFull = outfit.isOutfitFull();
		if (!isFull)
			return OutfitUpgradeResult.ITEM_NOT_ENOUGH;

		outfit.removeAll();

		return OutfitUpgradeResult.SUCCESS;
	}

	public boolean createItem(int itemId, int num)
	{
		this.lockCheck();

		ItemDataObject item = TemplateService.getInstance().get(itemId,
				ItemDataObject.class);
		if (item == null || item.getCreate() == null)
			return false;

		CreateDataTemplate createData = item.getCreate();
		if (createData.getInItemId1() > 0
				&& !this.hasItemInBag(createData.getInItemId1(),
						createData.getItemNum1() * num))
			return false;
		if (createData.getInItemId2() > 0
				&& !this.hasItemInBag(createData.getInItemId2(),
						createData.getItemNum2() * num))
			return false;
		if (createData.getInItemId3() > 0
				&& !this.hasItemInBag(createData.getInItemId3(),
						createData.getItemNum3() * num))
			return false;
		if (createData.getInItemId4() > 0
				&& !this.hasItemInBag(createData.getInItemId4(),
						createData.getItemNum4() * num))
			return false;
		if (createData.getInItemId5() > 0
				&& !this.hasItemInBag(createData.getInItemId5(),
						createData.getItemNum5() * num))
			return false;

		// ��Ǯ
		Role role = GlobalRoleCache.getInstance().getRoleById(getServiceId());
		if (role.addMoney(-item.getCreate().getCost(), RewardType.CREATE, true))
			return false;

		List<PItemChangeLog.Builder> itemList = new ArrayList<PItemChangeLog.Builder>();
		if (createData.getInItemId1() > 0)
		{
			RoleItem leftItem = this.addOrRemoveItem(createData.getInItemId1(),
					-createData.getItemNum1() * num,false);
			PItemChangeLog.Builder builder = PItemChangeLog.newBuilder();
			builder.setItemAddNum(-createData.getItemNum1() * num);
			builder.setItemFinalNum(leftItem.getBean().getItemNum());
			builder.setItemId(leftItem.getBean().getItemId());
			builder.setNpcId(0);
			
			itemList.add(builder);
		}
		if (createData.getInItemId2() > 0)
		{
			RoleItem leftItem = this.addOrRemoveItem(createData.getInItemId2(),
					-createData.getItemNum2() * num,false);
			PItemChangeLog.Builder builder = PItemChangeLog.newBuilder();
			builder.setItemAddNum(-createData.getItemNum2() * num);
			builder.setItemFinalNum(leftItem.getBean().getItemNum());
			builder.setItemId(leftItem.getBean().getItemId());
			builder.setNpcId(0);
			
			itemList.add(builder);
		}
		if (createData.getInItemId3() > 0)
		{
			RoleItem leftItem = this.addOrRemoveItem(createData.getInItemId3(),
					-createData.getItemNum3() * num,false);
			PItemChangeLog.Builder builder = PItemChangeLog.newBuilder();
			builder.setItemAddNum(-createData.getItemNum3() * num);
			builder.setItemFinalNum(leftItem.getBean().getItemNum());
			builder.setItemId(leftItem.getBean().getItemId());
			builder.setNpcId(0);
			
			itemList.add(builder);
		}
		if (createData.getInItemId4() > 0)
		{
			RoleItem leftItem = this.addOrRemoveItem(createData.getInItemId4(),
					-createData.getItemNum4() * num,false);
			PItemChangeLog.Builder builder = PItemChangeLog.newBuilder();
			builder.setItemAddNum(-createData.getItemNum4() * num);
			builder.setItemFinalNum(leftItem.getBean().getItemNum());
			builder.setItemId(leftItem.getBean().getItemId());
			builder.setNpcId(0);
			
			itemList.add(builder);
		}
		if (createData.getInItemId5() > 0)
		{
			RoleItem leftItem = this.addOrRemoveItem(createData.getInItemId5(),
					-createData.getItemNum5() * num,false);
			PItemChangeLog.Builder builder = PItemChangeLog.newBuilder();
			builder.setItemAddNum(-createData.getItemNum5() * num);
			builder.setItemFinalNum(leftItem.getBean().getItemNum());
			builder.setItemId(leftItem.getBean().getItemId());
			builder.setNpcId(0);
			
			itemList.add(builder);
		};

		RoleItem leftItem = this.addOrRemoveItem(itemId, num,false);
		PItemChangeLog.Builder builder = PItemChangeLog.newBuilder();
		builder.setItemAddNum(num);
		builder.setItemFinalNum(leftItem.getBean().getItemNum());
		builder.setItemId(itemId);
		builder.setNpcId(0);
		
		itemList.add(builder);
		
		CommonItemUpdateMessage message = new CommonItemUpdateMessage(itemList);
		this.sendMessage(message);
		return true;
	}

	@Override
	public RoleItem addOrRemoveItem(int itemId, int deltaItemNum,boolean isSync)
	{
		this.lockCheck();

		IItemBeanDao dao = DBCS.getExector(IItemBeanDao.class);
		RoleItem item = bagItemMap.get(itemId);

		if (item == null)
		{
			if (deltaItemNum <= 0)
				return null;

			item = RoleItem
					.createRoleItem(getServiceId(), itemId, deltaItemNum);
			bagItemMap.put(itemId, item);
			dao.insertItemBean(item.getBean());
		} else
		{
			int resultNum = item.getBean().getItemNum() + deltaItemNum;
			if (resultNum < 0)
				return null;

			item.getBean().setItemId(itemId);
			item.getBean().setItemNum(resultNum);
			if (item.getBean().getItemNum() <= 0)
			{
				dao.deleteItemBean(item.getBean());

				bagItemMap.remove(item.getBean().getItemId());
			} else
				dao.updateItemBean(item.getBean());
		}
		
		if(isSync)
		{
			PItemChangeLog.Builder builder = PItemChangeLog.newBuilder();
			builder.setItemAddNum(deltaItemNum);
			builder.setItemFinalNum(item.getBean().getItemNum());
			builder.setItemId(item.getBean().getItemId());
			builder.setNpcId(0);
			
			List<PItemChangeLog.Builder> itemList = new ArrayList<PItemChangeLog.Builder>();
			itemList.add(builder);
			CommonItemUpdateMessage message = new CommonItemUpdateMessage(itemList);
			this.sendMessage(message);
		}

		return item;

	}

	public boolean hasItemInBag(int itemId, int itemNum)
	{
		RoleItem item = this.findItemInBag(itemId);
		if (item == null)
			return false;
		if (item.getBean().getItemNum() < itemNum)
			return false;
		return true;
	}

	public RoleItem findItemInBag(int itemId)
	{
		return bagItemMap.get(itemId);
	}

	@Override
	public boolean useItem(int itemId, int itemNum)
	{
		this.lockCheck();

		return false;
	}

	public OutfitInstallResult installOutfit(long petId, int outfitIdx)
	{
		this.lockCheck();

		Outfit outfit = getOutfit(petId);
		if (outfit == null)
			return OutfitInstallResult.NOT_FOUND_SPRITE;

		int itemId = outfit.getQualityItemIdList().get(outfitIdx);
		RoleItem item = findItemInBag(itemId);
		if (item == null)
			return OutfitInstallResult.NOT_FOUND_ITEM;

		if (item.getData().getLevelLimit() > outfit.getSprite().getSpriteBean()
				.getLevel())
			return OutfitInstallResult.LEVEL_LIMIT;

		OutfitInstallResult result = outfit.installOutfitCheck(item);
		if(result != OutfitInstallResult.SUCCESS)
			return result;
		
		RoleItem resultItem = this.addOrRemoveItem(item.getBean().getItemId(), -1,true);

		if(resultItem == null)
			return OutfitInstallResult.ITEM_NOT_ENOUGH;
		
		outfit.installOutfit(item);
		return result;
	}

	private Outfit getOutfit(long petId)
	{
		Role role = GlobalRoleCache.getInstance().getRoleById(getServiceId());

		Outfit outfit = outfitMap.get(petId);
		if (outfit == null)
		{
			AbstractSprite sprite = null;
			sprite = role.getPetManager().getPetMap().get(petId);
			if (sprite == null)
				return null;
			outfit = new Outfit(getServiceId(), sprite, null);

			outfitMap.put(petId, outfit);
		}

		return outfit;
	}
	
	public Collection<RoleItem> getOutfitItemList(long petId)
	{
		return getOutfit(petId).getOutfitMap().values();
	}
	
	public Map<Long, Outfit> getAllOutfitMap()
	{
		return outfitMap;
	}

	public void initPetOutfit(AbstractSprite pet)
	{
		this.getOutfit(pet.getId());
	}
	
	private void lockCheck()
	{
		if (!lock.locked())
			throw new RuntimeException("û��lock������²�����Ʒ");
	}

	@Override
	public boolean lock()
	{
		return lock.lock();
	}

	@Override
	public void unlock()
	{
		lock.unlock();
	}

	@Override
	public Collection<RoleItem> getBagItemList()
	{
		return Collections.unmodifiableCollection(bagItemMap.values());
	}

}