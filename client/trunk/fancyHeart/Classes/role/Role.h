//
//  Role.h
//  fancyHeart
//
//  Created by doteyplay on 14-8-12.
//
//

#ifndef __fancyHeart__Role__
#define __fancyHeart__Role__

#include <iostream>
#include "cocos2d.h"
#include "Manager.h"
#include "BaseUI.h"
#include "TabBar.h"
#include "XRoleData.h"
#include "XItem.h"
#include "XCraft.h"
#include "EquipInfo.h"
#include "XRole.h"
#include "InfoPanel.h"
#include "Manager.h"
#include "Utils.h"
#include "XRoleStar.h"
#include "XExp.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

class Role:public BaseUI
{
public:
	static Role* create(PNpc itemData);
	virtual bool init(std::string fileName,PNpc itemData);
	virtual void onEnter();
	virtual void onExit();

private:
	void initNetEvent();
	void touchEvent(Ref *pSender, TouchEventType type);
    void touchBtnEvent(Ref *pSender, TouchEventType type);

private: //私有属性
 	BaseUI* preUI;
    Widget* propertyPanel;
    Widget* skillPanel;
    Widget* rolePic;
    Widget*equipPanel;
    TabBar* tabBar;
    Widget* panel;
    Button*changeBtn;
    Widget* progress;
    Text* desc;
    void setBtnVisible();
    PNpc itemData;
    XRoleData*xRoleData;//角色属性表中对应的数据
    void setEquips();
    std::vector<Sprite*> equips;//装备位列表
    std::vector<int> equipStatus;//装备位列表状态
    void setEquipToPos(int index,int posIndex);//设置装备位上得状态
    bool propIsEnough(int itemId,int num);
    std::vector<int> equipsData;//存储需要装备的id
    void openInfoPanel(int index);//点击装备位弹出弹窗方法
    bool isMayPress;//升级按钮是否可点击
    void setProgressData();//设置进度条数据
    void openAscendSuccess();
    int status;//0:为进化  1:为变异
    void createIconBox(int itemId,string parentName,int index);
    void setData();
};
#endif /* defined(__fancyHeart__Role__) */