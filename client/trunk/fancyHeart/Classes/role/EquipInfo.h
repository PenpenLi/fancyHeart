//
//  EquipInfo.h
//  fancyHeart
//
//  Created by doteyplay on 14-8-20.
//
//

#ifndef __fancyHeart__EquipInfo__
#define __fancyHeart__EquipInfo__

#include <iostream>
#include "cocos2d.h"
#include "Manager.h"
#include "BaseUI.h"
#include "XItem.h"
#include "Compose.h"
#include "Role.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;
struct ColorInfo{
    int color;
    std::string text;
};

class EquipInfo:public BaseUI
{
public:
	static EquipInfo* create(int index,XItem* xItem,int heroId,int posId,BaseUI* delebag);
	virtual bool init(std::string fileName,int index,XItem* xItem,int heroId,int posId,BaseUI* delebag);
	virtual void onEnter();
	virtual void onExit();

private:
	void initNetEvent();
    void touchBtnEvent(Ref *pSender, TouchEventType type);
    Widget*imgBg;
    int statusIndex;
    XItem* currentXItem;
    int posId;
    int heroId;
    BaseUI*role;

private: //私有属性
 	BaseUI* preUI;

};
#endif /* defined(__fancyHeart__EquipInfo__) */
