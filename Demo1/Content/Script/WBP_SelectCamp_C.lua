--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_SelectCamp_C
local WBP_SelectCamp = UnLua.Class()

local IsFirstTimes = true;

function WBP_SelectCamp:Construct()
    self:Bind()
    self:Init()
end

function WBP_SelectCamp:Bind()
    self.SelectButton.OnClicked:Add(self, self.OnClickedSelectButton);
    self.ReturnButton.OnClicked:Add(self, self.OnClickedReturnButton);
    self.GameStartButton.OnClicked:Add(self, self.OnClickedStart);
end

-- 初始化一下阵营
function WBP_SelectCamp:Init()
    local GS = UE.UGameplayStatics.GetGameState(self);
    local CampInfoList = GS:GetCampInfoList();

    self.CampsList:ClearChildren()
    for i=1,CampInfoList:Length() do
        local CampSubUIClass = UE.UClass.Load("/Game/Demo/BluePrints/UI/WBP_Camps.WBP_Camps_C")    -- 注意路径
        local CampSubUI = NewObject(CampSubUIClass, self);
        
        self.CampsList:AddChild(CampSubUI);
        CampSubUI:InitInfo(CampInfoList[i].Type);   -- 初始化一下按钮的样式以及阵营信息
    end

    print("WBP_SelectCamp:Init");
    self:SetUIMode();
end

------------------------------ Event -------------------------------

function WBP_SelectCamp:OnClickedSelectButton()
    if(self.CampsList:IsVisible()) then
        self.CampsList:SetVisibility(UE.ESlateVisibility.Collapsed)
    else
        self.CampsList:SetVisibility(UE.ESlateVisibility.Visible)
    end
end

function WBP_SelectCamp:OnClickedReturnButton()
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_SelectCampReturn();
    end
end

function WBP_SelectCamp:OnClickedStart()
    self:ReleaseGame();
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_GameStart();
    end
end

-- function WBP_SelectCamp:PreConstruct(IsDesignTime)
-- end

--function WBP_SelectCamp:Initialize(Initializer)
--end

--function WBP_SelectCamp:Tick(MyGeometry, InDeltaTime)
--end

return WBP_SelectCamp
