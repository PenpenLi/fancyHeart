//
//  InfoPanel.cpp
//  fancyHeart
//
//  Created by doteyplay on 14-8-20.
//
//

#include "InfoPanel.h"

InfoPanel* InfoPanel::create(int status,PNpc pNpc)
{
    InfoPanel* infoPanel=new InfoPanel();
    if (infoPanel && infoPanel->init("publish/infoPanel/infoPanel.ExportJson",status,pNpc)) {
        infoPanel->autorelease();
        return infoPanel;
    }
    CC_SAFE_DELETE(infoPanel);
    return nullptr;
}

bool InfoPanel::init(std::string fileName,int status,PNpc pNpc)
{
	if(!BaseUI::init(fileName))
    {
        return false;
    }
	//如果需要对cocostudio 设计的ui进行调整
    
    this->pNpc = pNpc;
    this->imgBg = static_cast<Widget*>(layout->getChildByName("imgBg"));
    this->panel1 = static_cast<Widget*>(imgBg->getChildByName("panel1"));
    this->panel2 = static_cast<Widget*>(imgBg->getChildByName("panel2"));
    this->skillFrame = static_cast<Widget*>(imgBg->getChildByName("skillFrame"));
//    Widget* iconFrame2 = static_cast<Widget*>(panel1->getChildByName("iconFrame2"));
    
    Text* nameLabel = static_cast<Text*>(imgBg->getChildByName("nameLabel"));
    Text* explainLabel = static_cast<Text*>(this->skillFrame->getChildByName("explainLabel"));
    Button*sureBtn = static_cast<Button*>(imgBg->getChildByName("sureBtn"));
    sureBtn->addTouchEventListener(CC_CALLBACK_2(InfoPanel::touchBtnEvent, this));
    this->setPanelVisible();
    
    std::vector<PropertyInfo> infoVector;
    infoVector.push_back({"getAtk","getAtkRate","getAttackRate"});
    infoVector.push_back({"getHp","getHpRate","getHpRate"});
    infoVector.push_back({"getDf","getDfRate","getDfRate"});
    infoVector.push_back({"getMDf","getMDfRate","getMDfRate"});
    
    if (status == 0) {//升阶
        int quality = this->pNpc.quality();
        XRole*xRole = XRole::record(Value(this->pNpc.spriteid()));
        //升阶成功后若品阶等级等于1、3、6、9时,弹出的弹窗
        if (quality == 1||quality == 3||quality == 6||quality == 9) {
            if (quality == 1) this->xSkill =XSkill::record(Value(xRole->getSkill2()));
            else if (quality == 3) this->xSkill =XSkill::record(Value(xRole->getSkill3()));
            else if (quality == 6) this->xSkill =XSkill::record(Value(xRole->getSkill4()));
            else if (quality == 9) this->xSkill =XSkill::record(Value(xRole->getSkill5()));
        }
        this->panel1->setVisible(true);
        nameLabel->setString("升阶成功");
        this->setAscend(quality == 1||quality == 3||quality == 6||quality == 9?0:1);
    }else if(status == 2){//进化
        this->panel2->setVisible(true);
        nameLabel->setString("进化成功");
        this->setEvolve(status);
    }else if(status == 3||status == 4){//技能解锁和升级
        this->skillFrame->setVisible(true);
        nameLabel->setString(status == 3?"觉醒技解锁":"技能升级");
        setSkill(status);
    }
    
	return true;
}

void InfoPanel::onEnter()
{
    BaseUI::onEnter();
}

void InfoPanel::setPanelVisible(){
    this->panel1->setVisible(false);
    this->panel2->setVisible(false);
    this->skillFrame->setVisible(false);
}
//设置升阶数据
void InfoPanel::setAscend(int status)
{
    Text* defAfterLabel = static_cast<Text*>(this->panel1->getChildByName("defAfterLabel"));
    Text* atkLabel= static_cast<Text*>(defAfterLabel->getChildByName("atkLabel"));
    Text* atkAfterLabel= static_cast<Text*>(defAfterLabel->getChildByName("atkAfterLabel"));
    Text* hpLabel= static_cast<Text*>(defAfterLabel->getChildByName("hpLabel"));
    Text* hpAfterLabel= static_cast<Text*>(defAfterLabel->getChildByName("hpAfterLabel"));
    Text* defLabel= static_cast<Text*>(defAfterLabel->getChildByName("defLabel"));
    Text* mDefLabel= static_cast<Text*>(defAfterLabel->getChildByName("mDefLabel"));
    Text* mDefAfterLabel= static_cast<Text*>(defAfterLabel->getChildByName("mDefAfterLabel"));
    Widget* skillFra= static_cast<Widget*>(this->panel1->getChildByName("skillFra"));
    Text* explainLabel= static_cast<Text*>(skillFra->getChildByName("explainLabel"));
    skillFra->setVisible(status == 0?true:false);
    if (status == 0) {//0:品阶等级等于1、3、6、9;1:品阶等级等于2、4、5、7、8
        //技能属性的显示
        explainLabel->setString(Value(this->xSkill->getDesc()).asString());
    }
    //人物颜色框
    std::vector<std::string> colors = {"1.png","2.png","2.png","3","3.png",
        "3.png","4.png","4.png","4.png","5.png"};
    
    ImageView* panel1=static_cast<ImageView*>(this->imgBg->getChildByName("panel1"));
    panel1->loadTexture("frame_"+Value(colors[this->pNpc.quality()-1]).asString(),TextureResType::PLIST);
    ImageView* iconFrame2 = static_cast<ImageView*>(this->panel1->getChildByName("iconFrame2"));
    iconFrame2->loadTexture("frame_"+Value(colors[this->pNpc.quality()]).asString(),TextureResType::PLIST);
    
    //升阶前数据
    XRoleData*xRoleDataBf = XRoleData::record(Value(Value(this->pNpc.spriteid()).asString()+Value(this->pNpc.quality()-1).asString()));
    XRoleData*xRoleDataAf = XRoleData::record(Value(Value(this->pNpc.spriteid()).asString()+Value(this->pNpc.quality()).asString()));
    //参数分别为——pNpc:角色信息，index:取哪种数据（攻击，生命，物防，法防）,status:表示的是0:升阶还是1:进化
    //攻击
    atkLabel->setString(Value(getQualityData(this->pNpc,0,0,-1)).asString());//——升阶之前的数据
    atkAfterLabel->setString(Value(getQualityData(this->pNpc,0,0,0)).asString());//升阶之后的数据npc值有变化
    //生命
    hpLabel->setString(Value(getQualityData(this->pNpc,1,0,-1)).asString());
    hpAfterLabel->setString(Value(getQualityData(this->pNpc,1,0,0)).asString());
    //物防
    defLabel->setString(Value(getQualityData(this->pNpc,2,0,-1)).asString());
    defAfterLabel->setString(Value(getQualityData(this->pNpc,2,0,0)).asString());
    //法防
    mDefLabel->setString(Value(getQualityData(this->pNpc,3,0,-1)).asString());
    mDefAfterLabel->setString(Value(getQualityData(this->pNpc,3,0,0)).asString());
    
}
//设置进化数据
void InfoPanel::setEvolve(int status)
{
    ImageView* frame1= static_cast<ImageView*>(this->panel2->getChildByName("frame1"));
    ImageView* frame2= static_cast<ImageView*>(this->panel2->getChildByName("frame2"));
    //人物颜色框
    std::vector<std::string> colors = {"1.png","2.png","2.png","3","3.png",
        "3.png","4.png","4.png","4.png","5.png"};
    
    frame1->loadTexture("frame_"+Value(colors[this->pNpc.quality()-1]).asString(),TextureResType::PLIST);
    frame2->loadTexture("frame_"+Value(colors[this->pNpc.quality()]).asString(),TextureResType::PLIST);
    
    XRoleData*xRoleDataBf = XRoleData::record(Value(Value(this->pNpc.spriteid()).asString()+Value(this->pNpc.quality()-1).asString()));
    XRoleData*xRoleDataAf = XRoleData::record(Value(Value(this->pNpc.spriteid()).asString()+Value(this->pNpc.quality()).asString()));
    Text* atkAdd= static_cast<Text*>(this->panel2->getChildByName("label1"));
    Text* hpAdd= static_cast<Text*>(this->panel2->getChildByName("label2"));
    Text* defAdd= static_cast<Text*>(this->panel2->getChildByName("label3"));
    Text* mDefAdd= static_cast<Text*>(this->panel2->getChildByName("label4"));
    Text* atk= static_cast<Text*>(this->panel2->getChildByName("atkLabel"));
    Text* atkAfter= static_cast<Text*>(this->panel2->getChildByName("atkAfterLabel"));
    Text* hp= static_cast<Text*>(this->panel2->getChildByName("hpLabel"));
    Text* hpAfter= static_cast<Text*>(this->panel2->getChildByName("hpAfterLabel"));
    Text* def= static_cast<Text*>(this->panel2->getChildByName("defLabel"));
    Text* defAfter = static_cast<Text*>(this->panel2->getChildByName("defAfterLabel"));
    Text* mDef= static_cast<Text*>(this->panel2->getChildByName("mDefLabel"));
    Text* mDefAfter= static_cast<Text*>(this->panel2->getChildByName("mDefAfterLabel"));
//    atk->setString(Value(floor(xRoleDataBf->getAtkRate()/100)/100).asString());
//    atkAfter->setString(Value(floor(xRoleDataAf->getAtkRate()/100)/100).asString());
//    hp->setString(Value(floor(xRoleDataBf->getHpRate()/100)/100).asString());
//    hpAfter->setString(Value(floor(xRoleDataAf->getHpRate()/100)/100).asString());
//    def->setString(Value(floor(xRoleDataBf->getDfRate()/100)/100).asString());
//    defAfter->setString(Value(floor(xRoleDataAf->getDfRate()/100)/100).asString());
//    mDef->setString(Value(floor(xRoleDataBf->getMDfRate()/100)/100).asString());
//    mDefAfter->setString(Value(floor(xRoleDataAf->getMDfRate()/100)/100).asString());
//    atkAdd->setString(Value(getQualityData(this->pNpc,0,1,0) - getQualityData(this->pNpc,0,1,-1)).asString());
//    hpAdd->setString(Value(getQualityData(this->pNpc,1,1,0) - getQualityData(this->pNpc,1,1,-1)).asString());
//    defAdd->setString(Value(getQualityData(this->pNpc,2,1,0) - getQualityData(this->pNpc,2,1,-1)).asString());
//    mDefAdd->setString(Value(getQualityData(this->pNpc,3,1,0) - getQualityData(this->pNpc,3,1,-1)).asString());
    
}
//设置技能解锁和升阶界面
void InfoPanel::setSkill(int status)
{
    Widget* skillIcon = static_cast<Widget*>(this->skillFrame->getChildByName("skillIcon"));
    Text* skillInfo= static_cast<Text*>(this->skillFrame->getChildByName("skillInfo"));
    Text* levelPercentLabel= static_cast<Text*>(this->skillFrame->getChildByName("levelPercentLabel"));
    skillInfo->setString(Value(this->xSkill->getDesc()).asString());
    //技能等级的显示
//    levelPercentLabel->setString();
}

void InfoPanel::touchBtnEvent(Ref *pSender, TouchEventType type)
{
    Button* btn=static_cast<Button*>(pSender);
    if (!btn) {
        return;
    }
    
    if (btn->getTag() == 12725) {//确定按钮
        this->clear(true);
    }
}
//参数分别为——pNpc:角色信息，index:取哪种数据（攻击，生命，物防，法防）,status:表示的是0:升阶还是1:进化,qualityOrStarAdd:增加数值
float InfoPanel::getQualityData(PNpc pNpc,int index,int status,int qualityOrStarAdd)
{
    
    
    int id = pNpc.spriteid();
    XItem* xItem;
    XRoleData* xRoleData = XRoleData::record(Value(Value(id).asString()+Value(pNpc.quality()+qualityOrStarAdd).asString()));
    XRoleStar* xRoleStar =XRoleStar::record(Value(Value(id).asString()+Value(pNpc.star()+qualityOrStarAdd).asString()));
    //本品质基础数据 + 装备 + 等级 X（本品质成长率+星级成长率）
    int resuleNum;
    int equipNum = 0;
    if (index == 0) {
        if(status !=0){
            for (int i = 0; i<pNpc.equiplist_size(); i++) {
                xItem = XItem::record(Value(pNpc.equiplist(i).itemid()));
                equipNum +=xItem->getAtk();
            }
        }
        resuleNum = 100* floor(xRoleData->getAtk()+equipNum+pNpc.level()*(xRoleData->getAtkRate()/10000+xRoleStar->getAttackRate()/10000));
    }else if (index == 1){
        if(status !=0){
            for (int i = 0; i<PNpc().equiplist_size(); i++) {
                 xItem = XItem::record(Value(pNpc.equiplist(i).itemid()));
                equipNum +=xItem->getHp();
            }
        }
        resuleNum = 100* floor(xRoleData->getHp()+equipNum+pNpc.level()*(xRoleData->getHpRate()/10000+xRoleStar->getHpRate()/10000));
    }else if (index == 2){
        if(status !=0){
            for (int i = 0; i<PNpc().equiplist_size(); i++) {
                 xItem = XItem::record(Value(pNpc.equiplist(i).itemid()));
                equipNum +=xItem->getDef();
            }
        }
        resuleNum = 100* floor(xRoleData->getDf()+equipNum+pNpc.level()*(xRoleData->getDfRate()/10000+xRoleStar->getDfRate()/10000));
    }else if (index == 3){
        if(status !=0){
            for (int i = 0; i<PNpc().equiplist_size(); i++) {
                 xItem = XItem::record(Value(pNpc.equiplist(i).itemid()));
                equipNum +=xItem->getMDef();
            }
        }
        resuleNum = 100* floor(xRoleData->getMDf()+equipNum+pNpc.level()*(xRoleData->getMDfRate()/10000+xRoleStar->getMDfRate()/10000));
    }
    float result = resuleNum/100;
    return result;
    ///////////////////////////////////
    //infoVector
//    if(status !=0){
//        for (int i = 0; i<pNpc.equiplist_size(); i++) {
//            xItem = XItem::record(Value(pNpc.equiplist(i).itemid()));
//            equipNum +=xItem->getAtk();
//        }
//    }
//    resuleNum = 100* floor(xRoleData->getAtk()+equipNum+pNpc.level()*(xRoleData->getAtkRate()/10000+xRoleStar->getAttackRate()/10000));
    ///////////////////////////////////
}

void InfoPanel::onExit()
{
    BaseUI::onExit();
}