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
	static EquipInfo* create(int index,XItem* xItem,int heroId);
	virtual bool init(std::string fileName,int index,XItem* xItem,int heroId);
	virtual void onEnter();
	virtual void onExit();

private:
	void initNetEvent();
    void touchBtnEvent(Ref *pSender, TouchEventType type);
    Widget*imgBg;
    int statusIndex;
    XItem* currentXItem;
    int heroId;
    std::vector<ColorInfo> qualitys={
        ColorInfo{1,""},
        ColorInfo{2,""},ColorInfo{2,"+1"},
        ColorInfo{3,""},ColorInfo{3,"+1"},ColorInfo{3,"+2"},
        ColorInfo{4,""},ColorInfo{4,"+1"},ColorInfo{4,"+2"},
        ColorInfo{5,""}};//颜色0白 1绿 2绿+1 3蓝 4蓝+1 5蓝+2 6紫 7紫+1 8紫+2 9金

private: //私有属性
 	BaseUI* preUI;

};
#endif /* defined(__fancyHeart__EquipInfo__) */