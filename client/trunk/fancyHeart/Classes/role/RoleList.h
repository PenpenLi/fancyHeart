//
//  RoleList.h
//  fancyHeart
//
//  Created by doteyplay on 14-8-12.
//
//

#ifndef __fancyHeart__RoleList__
#define __fancyHeart__RoleList__

#include <iostream>
#include "cocos2d.h"
#include "Manager.h"
#include "BaseUI.h"
#include "RotateList.h"
#include "XRole.h"
//#include "XItem.h"
#include "Role.h"
#include "XRoleData.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

struct notCalledData{
    std::string npcId;
    int isEnoughProp;
};

class RoleList:public BaseUI
{
public:
	static RoleList* create();
	virtual bool init(std::string fileName);
	virtual void onEnter();
	virtual void onExit();
	//virtual void onDlgClose(std::string data);

private:
	void initNetEvent();
	void touchEvent(Ref *pSender, TouchEventType type);

private: //私有属性
 	BaseUI* preUI;
    RotateList* rotateList;
    void rotateListCallback(RotateList::EventType type,Widget*item,int index);
    Slider* slider;
    void setItemData(Widget* item,XRole* itemData,int index);
    std::vector<Widget*> stars;//星级
    XRole* middleItemData;
    void setBottomData();
    Widget* progress;
    Button* btnCall;
    Widget* middleItem;//中间位置的item
    void showRolePanel();
    std::vector<int64> listIds;//id列表
    Widget* currentCalledItem;
    //对还未召唤的角色进行排序
    static bool sortNotalled(notCalledData data1,notCalledData data2);
    //对已经召唤的角色进行排序
    static bool sortCalled(int id1,int id2);
    static PNpc* getNpc(int spriteId);
    

};
#endif /* defined(__fancyHeart__RoleList__) */