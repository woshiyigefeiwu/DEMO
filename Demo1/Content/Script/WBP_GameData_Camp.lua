--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_GameData_Camp_C
local WBP_GameData_Camp = UnLua.Class()

function WBP_GameData_Camp:Construct()
    self:Bind()
end

function WBP_GameData_Camp:Bind()
    self.CampTypeButton.OnClicked:Add(self, self.OnClickedCampTypeButton);    

    local GS = UE.UGameplayStatics.GetGameState(self);
    GS.OnAINumChange:Add(self,self.RefreshAINum);
end

function WBP_GameData_Camp:InitInfo(CampInfo)
    self.CampInfo = CampInfo;
    self.CampType = CampInfo.Type;
    self:SetUIVisible(self.SoliderList,false);
    self:SetUIVisible(self.BG,false);

    -- 初始化一下样式
    self.SetColor(self,CampInfo);
    self:RefreshAINum()
    
    -- 创建兵种
    local GS = UE.UGameplayStatics.GetGameState(self);
    local SoldierInfoList = GS:GetSoldierInfoList()
    for i=1,SoldierInfoList:Length() do
        local SoldierSubUIClass = UE.UClass.Load("/Game/Demo/BluePrints/UI/WBP_GameData_Solider.WBP_GameData_Solider_C")    -- 注意路径
        local SoldierSubUI = NewObject(SoldierSubUIClass, self);
        self.SoliderList:AddChild(SoldierSubUI);

        local SoliderType = GS:GetSoliderType(SoldierInfoList[i])
        SoldierSubUI:InitInfo(self.CampType, SoliderType);
    end
end

------------------- Event -------------------

function WBP_GameData_Camp:OnClickedCampTypeButton()
    self:ReverseUI(self.SoliderList);
    self:ReverseUI(self.BG);
end

function WBP_GameData_Camp:RefreshAINum()
    local GS = UE.UGameplayStatics.GetGameState(self);
    local num = GS:GetNumByCampType(self.CampType);
    local display_str = self.CampInfo.LeftNumDisplay..tostring(num);
    self.SetText(self,display_str);
end

------------------- 辅助函数 -----------------

-- 设置 UI 的显示隐藏
function WBP_GameData_Camp:SetUIVisible(UI, flag)
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
function WBP_GameData_Camp:ReverseUI(UI)
    if(UI:IsVisible()) then
        UI:SetVisibility(UE.ESlateVisibility.Collapsed)
    else
        UI:SetVisibility(UE.ESlateVisibility.Visible)
    end
end

--function WBP_GameData_Camp:Initialize(Initializer)
--end

--function WBP_GameData_Camp:PreConstruct(IsDesignTime)
--end

--function WBP_GameData_Camp:Tick(MyGeometry, InDeltaTime)
--end

return WBP_GameData_Camp
