--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GamePlay_C
local WBP_GamePlay = UnLua.Class()

local IsFirstTimes = true;

function WBP_GamePlay:Construct()
    self:Bind()
    self:Init()
end

function WBP_GamePlay:Bind()
    self.PauseButton.OnClicked:Add(self, self.OnClickedPauseButton);
    self.ContinueButton.OnClicked:Add(self, self.OnClickedContinueButton);
    self.RestartButton.OnClicked:Add(self, self.OnClickedRestartButton);
    self.ExitButton.OnClicked:Add(self, self.OnClickedExitButton);
    self.GameDataButton.OnClicked:Add(self,self.OnClickedGameDataButton);

    local GS = UE.UGameplayStatics.GetGameState(self);
    GS.GameOverDelegate:Add(self,self.OnGameOver);
end

function WBP_GamePlay:Init()
    self:SetUIVisible(self.ButtonList,false);
    self:SetUIVisible(self.GameData, true);

    -- 初始化一下阵营数据按钮
    local GS = UE.UGameplayStatics.GetGameState(self);
    local CampInfoList = GS:GetCampInfoList();

    self.GameData:ClearChildren()
    for i=1,CampInfoList:Length() do
        local CampSubUIClass = UE.UClass.Load("/Game/Demo/BluePrints/UI/WBP_GameData_Camp.WBP_GameData_Camp_C")    -- 注意路径
        local CampSubUI = NewObject(CampSubUIClass, self);
        
        self.GameData:AddChild(CampSubUI);
        CampSubUI:InitInfo(CampInfoList[i]);   -- 初始化一下按钮的样式以及阵营信息
    end
end

------------------------- Event -------------------------

-- 游戏结束
function WBP_GamePlay:OnGameOver()
    -- self:QuitGame();
    local GS = UE.UGameplayStatics.GetGameState(self);
    local UIM = GS:GetUIManager();
    if(UIM) then
        UIM:ShowUI("UI_GameOver");
    end    
end

-- 退出按钮
function WBP_GamePlay:OnClickedExitButton()
    self:QuitGame();
end

-- 暂停按钮
function WBP_GamePlay:OnClickedPauseButton()
    self:PauseGame();   -- 蓝图，暂停游戏
    self:SetUIVisible(self.ButtonList,true);
    self:SetUIVisible(self.PauseButton,false);
    self:SetUIVisible(self.GameDataButton,false);
    self:SetUIVisible(self.GameData,false);
end

-- 继续按钮
function WBP_GamePlay:OnClickedContinueButton()
    self:ReleaseGame(); -- 蓝图，继续游戏
    self:SetUIVisible(self.ButtonList,false);
    self:SetUIVisible(self.PauseButton,true);
    self:SetUIVisible(self.GameDataButton,true);
end

-- 重新开始按钮
function WBP_GamePlay:OnClickedRestartButton()
    self:RestartGame();
end

-- 数据展示按钮
function WBP_GamePlay:OnClickedGameDataButton()
    self:ReverseUI(self.GameData);
end

------------------- 辅助函数 -----------------

-- 设置 UI 的显示隐藏
function WBP_GamePlay:SetUIVisible(UI, flag)
    if(flag) then
        if(UI:IsVisible() == false) then
            UI:SetVisibility(UE.ESlateVisibility.Visible)
        end
    else
        if(UI:IsVisible()) then
            UI:SetVisibility(UE.ESlateVisibility.Collapsed)
        end
    end
end

-- 反转 UI ，显示->隐藏，隐藏->显示
function WBP_GamePlay:ReverseUI(UI)
    if(UI:IsVisible()) then
        UI:SetVisibility(UE.ESlateVisibility.Collapsed)
    else
        UI:SetVisibility(UE.ESlateVisibility.Visible)
    end
end

--function WBP_GamePlay:Initialize(Initializer)
--end

--function WBP_GamePlay:PreConstruct(IsDesignTime)
--end

--function WBP_GamePlay:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GamePlay
