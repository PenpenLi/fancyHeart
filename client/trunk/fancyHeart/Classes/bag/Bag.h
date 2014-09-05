//
//  Bag.h
//  fancyHeart
//
//  Created by doteyplay on 14-8-5.
//
//

#ifndef __fancyHeart__Bag__
#define __fancyHeart__Bag__

#include <iostream>
#include "cocos2d.h"
#include "Manager.h"
#include "BaseUI.h"
#include "XItem.h"
#include "TabBar.h"
#include "BagSellProp.h"

using namespace ui;
using namespace cocos2d;
using namespace cocostudio;

class Bag:public BaseUI
{
public:
    static Bag* create();
	virtual bool init(std::string fileName);
	virtual void onEnter();
    virtual void onExit();
    void sendInfo(int selectNumber);
	//virtual void onDlgClose(std::string data);

private:
	void initNetEvent();
    void touchEvent(cocos2d::Ref *pSender, TouchEventType type);
    void itemTouchEvent(Ref *pSender, TouchEventType type);
    void touchButtonEvent(Ref *pSender, TouchEventType type);
    void getTypeInfo(int type);

private: //私有属性
 	BaseUI* preUI;
    Vector<Widget*> propItems;//道具数组
    TabBar* tabBar;
    void setItem(PItem item,int index);//设置单项并且赋予其显示数据
    void setPlayerInfo();//设置玩家信息（金币等信息）
    Widget* propItem;//单个模版
    Text* currentPropNum;//当前道具得数量
    Text* propertyTxt1;//属性描述
    Text* propertyTxt2;
    Text* propertyTxt3;
    Text* propertyTxt4;
    Text* propertyTxt5;
    Text* itemPriceTxt;//出售单价
    Text* desTxt;//描述
    Text*nameTxt;//名字
    void setProperty(PItem item,bool isHaveData);//设置被选中的道具的具体显示信息
    PItem itemInfo;//存储当前被显示道具的道具信息
    int currentType;//当前选中的tab列表中的type
    bool isShow;//左边界面是否需要显示
    bool isNotAllSell;//道具是否被全部卖出
    void setRightPosition();//设置右边素材得位置
    Widget* rightBg;//右边界面
    Widget* leftBg;//左边界面
    Widget* top;//上面界面

};
#endif /* defined(__fancyHeart__Bag__) */