# SuperSideScroller — UE5 横版动作原型

> 用 UE5 做的横版动作原型:冲刺、投掷投射物、收集可拾取物、敌人接入行为树。
> **C++ 写玩法逻辑,蓝图做资源与表现**;投掷做成"动画驱动"、可拾取物做成基类 + 子类 —— 结构优先。

## 简介

| | |
|---|---|
| **项目类型** | 横版动作 / 平台跳跃原型(移动、冲刺、投掷、收集、敌人 AI) |
| **引擎版本** | Unreal Engine 5.3 |
| **实现方式** | C++(玩法逻辑)+ 蓝图(资源与表现)混合 |
| **C++ 规模** | 18 个头文件 / 源文件,约 680 行 |
| **用到的引擎系统** | 增强输入、动画通知(AnimNotify)、投射物移动组件、基类 + 子类(可拾取物)、行为树 + 黑板 + AI 控制器、只读接口暴露状态 |
| **仓库规模** | C++ 源码 18 个文件 + 蓝图与资产 40 个 |
| **入口关卡** | `/Game/ThirdPerson/Maps/ThirdPersonMap`,默认 GameMode 为 C++ 的 `SuperSideScrollerGameMode` |

## 功能流程

```
按键 → 播放投掷动画 →(动画通知在挥臂帧触发)→ 从骨骼挂点生成投射物 → 直线飞行
                                                              ↓
                                        命中敌人 → 销毁敌人 + 自身销毁(另设寿命兜底)
重叠到可拾取物 → 基类统一处理(旋转展示 / 拾取音效 / 销毁)→ 子类覆写「具体效果」→ 计数经只读接口给 UI
敌人 ← AI 控制器 + 行为树 + 黑板:巡逻 / 发现玩家 / 攻击
```

## 实现要点(结构)

- **投掷做成"动画驱动"**:按键只负责播动画,「什么时候真正生成投射物」交给动画通知决定,生成位置取动画骨骼上的挂点 —— 出手时机与动画严格对齐,不靠人为估算时间。
- **可拾取物做成基类 + 子类**:基类统一处理重叠检测、旋转展示、拾取音效与销毁,拾取的「具体效果」留给子类覆写 —— 后续加新道具只写子类,不动基类。
- **投射物**:关掉重力做直线飞行、用阻挡碰撞,命中敌人即销毁敌人并自爆,自身另设寿命兜底回收;收集数量通过只读接口暴露给 UI,界面与角色逻辑解耦。
- **输入**:同一个按键的「按下 / 松开」绑成两个事件,实现按住冲刺、松开恢复原速。
- **敌人 AI**:行为树 + 黑板 + AI 控制器驱动巡逻与攻击,行为树负责决策、C++ 负责暴露可被决策的状态。

## 目录结构

```
Source/SuperSideScroller/            C++ 源码
  SuperSideScroller.*                模块与角色基类(移动、相机、动画)
  SuperSideScroller_Player.*         玩家(冲刺、投掷、收集计数、增强输入)
  SuperSideScrollerGameMode.*        游戏模式
  EnemyBase.*                        敌人基类
  PlayerProjectile.*                 投射物(直线飞行、命中销毁、寿命兜底)
  Anim_ProjectileNotify.*            动画通知(在挥臂帧生成投射物)
  PickableActor_Base.*               可拾取物基类
  PickableActor_Collectable.*        可拾取物子类(收集物)
Content/
  MainCharacter/                     玩家角色与动画蒙太奇
  Enemy/                             敌人与其 AI(行为树 / 黑板 / AI 控制器)
  PickableItems/                     可拾取物蓝图
  ThirdPerson/                       关卡与 GameMode 蓝图
Config/                              项目与输入配置
```

## 如何打开

1. 安装 **Unreal Engine 5.3** 与 **Visual Studio 2022**(需含「使用 C++ 的游戏开发」工作负载)。
2. `git clone` 本仓库,右键 `SuperSideScroller.uproject` → **Generate Visual Studio project files** → 编译
   (或直接双击 `.uproject`,提示编译模块时选 Yes)。
3. 本仓库不含 UE 官方模板资源:用 UE 新建一个 **Third Person C++ 模板** 工程,把 `Content/StarterContent`、
   `Content/Characters`(含官方人形)、`Content/ThirdPerson/Maps` 补进本项目 `Content/` 下。
4. 入口关卡 `/Game/ThirdPerson/Maps/ThirdPersonMap`,PlayerStart 与敌人 / 收集物的摆放都在关卡里。

## 说明

- 仓库只包含本人产出的 C++ 源码、蓝图与资源;UE 官方模板资源未包含(见"如何打开"第 3 步)。
- 投掷物与收集物的数值都有默认值,可在蓝图上直接覆盖调整。
