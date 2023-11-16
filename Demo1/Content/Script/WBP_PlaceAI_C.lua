--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type WBP_PlaceAI_C
local WBP_PlaceAI = UnLua.Class()

local IsFirstTimes = true;

function WBP_PlaceAI:Construct()
    self:Bind()
    self:Init()
end

function WBP_PlaceAI:Bind()
    self.ReturnButton.OnClicked:Add(self, self.OnClickedReturnButton);
    self.GameStartButton.OnClicked:Add(self, self.OnClickedStart);
end

function WBP_PlaceAI:Init()
    
    local GS = UE.UGameplayStatics.GetGameState(self);
    local SoldierInfoList = GS:GetSoldierInfoList();

    self.SoldierList:ClearChildren()
    for i=1,SoldierInfoList:Length() do
        local SoldierSubUIClass = UE.UClass.Load("/Game/Demo/BluePrints/UI/WBP_Soldiers.WBP_Soldiers_C")    -- 注意路径
        local SoldierSubUI = NewObject(SoldierSubUIClass, self);

        self.SoldierList:AddChild(SoldierSubUI);
        SoldierSubUI:InitInfo(SoldierInfoList[i]);   -- 初始化一下兵种的样式
    end
end

----------------------------- Event -------------------------

function WBP_PlaceAI:OnClickedReturnButton()
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_PlaceAIReturn();
    end
end

function WBP_PlaceAI:OnClickedStart()
    self:ReleaseGame();
    local MyPawn = UE.UGameplayStatics.GetPlayerPawn(self,0);
    local MyPC = MyPawn:GetController();
    if(MyPC) then
        MyPC:OnClick_GameStart();
    end
end

--function WBP_PlaceAI:Initialize(Initializer)
--end

--function WBP_PlaceAI:PreConstruct(IsDesignTime)
--end

--function WBP_PlaceAI:Tick(MyGeometry, InDeltaTime)
--end

return WBP_PlaceAI
