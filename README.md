# SuperSideScroller — UE5 横版动作原型(C++ / 蓝图混合)

用 UE5(5.3)做的横版动作原型:冲刺、投掷投射物、收集可拾取物、敌人接入行为树。C++ 写玩法逻辑,蓝图做资源与表现。

## 实现要点
- **投掷做成"动画驱动"**:按键只负责播动画,「什么时候真正生成投射物」交给动画通知决定,生成位置取动画骨骼上的挂点 —— 出手时机与动画严格对齐,不靠人为估算时间。
- **可拾取物做成基类 + 子类**:基类统一处理重叠检测、旋转展示、拾取音效与销毁,拾取的「具体效果」留给子类覆写 —— 后续加新道具只写子类,不动基类。
- **投射物**:关掉重力做直线飞行、用阻挡碰撞,命中敌人即销毁敌人并自爆,自身另设寿命兜底回收;收集数量通过只读接口暴露给 UI,界面与角色逻辑解耦。
- **输入**:同一个按键的「按下 / 松开」绑成两个事件,实现按住冲刺、松开恢复原速。
- **敌人 AI**:行为树 + 黑板 + AI 控制器驱动巡逻与攻击。

## 目录
```
Source/SuperSideScroller/   C++ 源码
  SuperSideScrollerCharacter.*   角色基类(移动、相机、动画)
  SuperSideScroller_Player.*     玩家(冲刺、投掷、收集计数、增强输入)
  EnemyBase.*                    敌人基类
  PlayerProjectile.*             投射物(直线飞行、命中销毁)
  Anim_ProjectileNotify.*        动画通知(在挥臂帧生成投射物)
  PickableActor_Base.*           可拾取物基类
  PickableActor_Collectable.*    可拾取物子类(收集物)
  SuperSideScrollerGameMode.*    游戏模式
Content/
  MainCharacter/     玩家角色与动画蒙太奇
  Enemy/             敌人与其 AI(行为树 / 黑板 / AI 控制器)
  PickableItems/     可拾取物蓝图
  ThirdPerson/       关卡与游戏模式蓝图
  StarterContent/    未包含(见下)
```

## 说明
模板资源(StarterContent、官方人形与第三人称模板资产)未包含在本仓库,自行从 UE 官方模板补齐即可打开。
