 //
//  FighterMgr.cpp
//  fancyHeart
//
//  Created by 秦亮亮 on 14-8-14.
//
//

#include "FighterMgr.h"
FighterMgr* FighterMgr::create(FData* data)
{
    FighterMgr* pRet=new FighterMgr();
    if(pRet && pRet->init(data)){
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool FighterMgr::init(FData *data)
{
    this->pos = data->bd.pos;
    Size winSize=Director::getInstance()->getWinSize();

    this->mf=MFighter::create(data);
    this->mf->retain();
    
    this->view=VFighter::create("man2", "man20", pos);
    this->view->setPosition(Vec2(GRID_SIZE*3*(pos%5)+winSize.width,winSize.height/2+(pos%2?GRID_SIZE:-GRID_SIZE)));
    BattleMgr::getInstance()->view->heroNode->addChild(view,960-view->getPositionY());
    
    
    Director::getInstance()->getScheduler()->schedule(SEL_SCHEDULE(&FighterMgr::checkRun), this, 0, true);
    Director::getInstance()->getScheduler()->schedule(SEL_SCHEDULE(&FighterMgr::startAttack), this, 0.5, true);
    Director::getInstance()->getScheduler()->schedule(SEL_SCHEDULE(&FighterMgr::autoHeal), this, 1, true);
    
    this->pause();
    
    return true;
}

void FighterMgr::start()
{
    Director::getInstance()->getScheduler()->resumeTarget(this);
    this->mf->start();
    this->view->run();
}

void FighterMgr::pause()
{
    Director::getInstance()->getScheduler()->pauseTarget(this);
    this->mf->pause();
    this->view->stopActionByTag(ACTION_RUN_TAG);
}

void FighterMgr::autoHeal()
{
    int healHp=this->mf->autoHeal();
    //this->view->fallHp(Value(-healHp));
}

void FighterMgr::checkRun(float dt)
{
    if(view->state==fstate::run){
        FighterMgr* rf=BattleMgr::getInstance()->getFirst(pos);
        if(abs(this->getGrid() - rf->getGrid()) <= mf->getLockGrid()*2){
            this->view->stopActionByTag(ACTION_RUN_TAG);
            this->view->state=fstate::idle;
            this->startAttack();
        }
    }
}

void FighterMgr::startAttack()
{
    if(this->view->state!=fstate::idle){
        return;
    }
    
    std::vector<int> foes=BattleMgr::getInstance()->getFoes(pos);
    bool isFightOver=foes.size()==0;
    for(int i=0;i<foes.size();i++){
        FighterMgr* npc=BattleMgr::getInstance()->getHero(foes.at(i));
        if(npc->view->state==fstate::die){
            isFightOver=true;
            break;
        }
    }
    
    if(isFightOver){
        //战斗结果处理
        this->view->win();
        BattleMgr::getInstance()->stopAllFighter();
        return;
    }
    
    //技能列表，选择技能
    this->skill=this->mf->selectSkill();
    if(!skill){
        return;
    }
    //取mf普通攻击距离 和默认目标的位置计算是否移动
    FighterMgr* rf=BattleMgr::getInstance()->getFirst(pos);
    //检查攻击距离
    if(abs(this->getGrid() - rf->getGrid()) > mf->getLockGrid()*2){
        this->view->state=fstate::run;
        this->view->run();
        return;
    }
    this->view->state=fstate::start;
    this->skill->setIsReady(false);

    this->attack();

}

void FighterMgr::attack()
{
    //施法时间 1舜发 2吟唱（引导） 3蓄力
    XSkill* xSkill=XSkill::record(Value(skill->skillID));
    XSkillEffect* xse=XSkillEffect::record(Value(skill->skillID));
    this->targets=this->selectTarget();
    Director::getInstance()->getScheduler()->schedule(SEL_SCHEDULE(&FighterMgr::cast), this,0,0,xSkill->getSpellTime()/10000.0, false);

    //引导
    if(xSkill->getLeadNum()>0){
        this->view->spell(xse->getSpell());
        this->view->state=fstate::spell;
        return;
    }
    //射击  攻击动作-》弹道-》伤害
    if(xSkill->getRangeType()==4 && xSkill->getRangeParam2()>0){
        XSkillEffect* xse=XSkillEffect::record(Value(skill->skillID));
        this->view->state=fstate::cast;
        this->view->attack(xse->getCast());
        return;
    }
    //普通攻击
    if(xSkill->getLeadNum()==0){
        XSkillEffect* xse=XSkillEffect::record(Value(skill->skillID));
        this->view->state=fstate::cast;
        this->view->attack(xse->getCast());
        return;
    }
}

void FighterMgr::cast()
{
    XSkill* xskill=XSkill::record(Value(this->skill->skillID));
    XSkillEffect* xse=XSkillEffect::record(Value(skill->skillID));

    //射击 独立结算（同一个挨多下要延迟处理）
    if(xskill->getRangeType()==4){
        for(int pos : this->targets){
            FighterMgr* mf=BattleMgr::getInstance()->getHero(pos);
            float duration=this->view->lineThrow(xse->getBullet(),mf->view->getPosition());
            CallFuncN* fun=CallFuncN::create( CC_CALLBACK_0(FighterMgr::hitOne, this, mf));
            this->view->runAction(Sequence::create(DelayTime::create(duration),fun, NULL));
        }
        return;
    }
    //弹射，一个个来
    if(xskill->getRangeType()==5){
        for(int i=0;i<this->targets.size();i++){
            FighterMgr* mf=BattleMgr::getInstance()->getHero(targets.at(i));
            float duration=this->view->lineThrow(xse->getBullet(),mf->view->getPosition());
            CallFuncN* fun=CallFuncN::create( CC_CALLBACK_0(FighterMgr::bounce, this));
            this->view->runAction(Sequence::create(DelayTime::create(duration+0.2*i),fun, NULL));
        }
        return;
    }
    //穿透 一个个来
    if(xskill->getRangeType()==6){
        this->view->impaleThrow(xse->getBullet());
        for(int i=0;i<this->targets.size();i++){
            FighterMgr* mf=BattleMgr::getInstance()->getHero(targets.at(i));
            CallFuncN* fun=CallFuncN::create(CC_CALLBACK_0(FighterMgr::hitOne, this,mf));
            this->view->runAction(Sequence::create(DelayTime::create(0.1*i),fun, NULL));
        }
        return;
    }

    //引导完直接攻击
    this->hitAll();
}

void FighterMgr::bounce()
{
    FighterMgr* mf=BattleMgr::getInstance()->getHero(targets.at(0));
    this->targets.erase(targets.begin());
    if(this->targets.size()>0){
        BattleMgr::getInstance()->view->bounceTo(mf);
    }
}

void FighterMgr::hitOne(FighterMgr* npc)
{
    if(npc->view->state==fstate::die || !this->skill){
        return;
    }
    PHit pHit=this->mf->hit(npc->mf,this->skill);
    if(pHit.isdie()){
        npc->view->die();
        npc->view->state=fstate::die;
    }else{
        npc->view->attacked(pHit);
    }
}

void FighterMgr::hitAll()
{
    for(int pos : targets){
        FighterMgr* npc=BattleMgr::getInstance()->getHero(pos);
        this->hitOne(npc);
    }
}

int FighterMgr::getGrid()
{
    Size wsize=Director::getInstance()->getWinSize();
    float dx=(wsize.width-960)*0.5;
    float px=this->view->getPositionX()-dx;
    return MIN(24,MAX(0,ceil(MAX(px,0)/GRID_SIZE)));
}

std::vector<int> FighterMgr::selectTarget()
{
    std::vector<int> arr;

    XSkill* xSkill=XSkill::record(Value(skill->skillID));
    
    switch (xSkill->getRangeType()) {
        case 0: //自身
            arr.push_back(this->pos);
            break;
        case 1: //我方 影响人数 all
            arr=BattleMgr::getInstance()->getFoes(this->pos,true);
            arr=skill->selectStrategy(arr,xSkill->getRangeParam1());
            break;
        case 2: //近战 影响人数 all
            arr=BattleMgr::getInstance()->getFoes(this->pos);
            arr=skill->selectStrategy(arr,xSkill->getRangeParam1());
            skill->selectStrategy(arr,xSkill->getRangeParam2());
            break;
        case 3:{ //爆发 前排/中排/后排
            std::vector<int> vec=BattleMgr::getInstance()->getFoes(this->pos);
            int row1=0,row2=0,row3=0;
            
            for(int mPos : vec){
                FighterMgr* mf=BattleMgr::getInstance()->getHero(mPos);
                if(mf->getGrid() - mf->getGrid() <= 2){
                    if(row1 <= xSkill->getRangeParam1()){
                        arr.push_back(mPos);
                        row1++;
                    }
                }
                if(mf->getGrid() - mf->getGrid() <= 2){
                    if(row2 <= xSkill->getRangeParam2()){
                        arr.push_back(mPos);
                        row2++;
                    }
                }
                if(mf->getGrid() - mf->getGrid() <= 2){
                    if(row3 <= xSkill->getRangeParam3()){
                        arr.push_back(mPos);
                        row3++;
                    }
                }
            }
            break;
        }
        case 4: //最大距离/子弹数量 all
            arr=BattleMgr::getInstance()->getFoes(this->pos);
            for(int i=0;i<arr.size();i++)
            {
                FighterMgr* mf=BattleMgr::getInstance()->getHero(arr[i]);
                
                if(abs(mf->getGrid()-mf->getGrid()) > xSkill->getRangeParam1())
                {
                    arr.erase(arr.begin()+i);
                }
            }
            arr=skill->selectStrategy(arr,xSkill->getRangeParam2());
            break;
        case 5: //弹射 弹射次数
        {
            std::vector<int> vec=BattleMgr::getInstance()->getFoes(this->pos);
            int bondNum=xSkill->getRangeParam1();
            for(int i=0;i<bondNum;i++)
            {
                arr.push_back(vec.at(i%vec.size()));
            }
        }
            break;
        case 6: //穿透 最大距离
        {
            std::vector<int> vec=BattleMgr::getInstance()->getFoes(this->pos);
            for(int mPos : vec)
            {
                FighterMgr* mf=BattleMgr::getInstance()->getHero(mPos);
                if(mf->getGrid()-mf->getGrid() <= xSkill->getRangeParam1()){
                    arr.push_back(mPos);
                }
            }
        }
            break;
        default:
            log("error range type:%d,skillID:%d",xSkill->getRangeType(),skill->skillID);
            break;
    }
    return arr;
}

FighterMgr::~FighterMgr()
{
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
    this->mf->release();
    this->view->removeFromParent();
}