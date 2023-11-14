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

-- Э��
local function run(self)
    UE.UKismetSystemLibrary.Delay(self, 0.5) -- �ӳ�һ��
    self:Bind()
    self:Init()
end

function WBP_PlaceAI:Construct()
    if(IsFirstTimes) then
        coroutine.resume(coroutine.create(run),self)
        IsFirstTimes = false;
    end
end

function WBP_PlaceAI:Bind()
    self.ReturnButton.OnClicked:Add(self, self.OnClickedReturnButton);
end

function WBP_PlaceAI:Init()
    local GS = UE.UGameplayStatics.GetGameState(self);
    local SoldierInfoList = GS:GetSoldierInfoList();

    for i=1,SoldierInfoList:Length() do
        local SoldierSubUIClass = UE.UClass.Load("/Game/Demo/BluePrints/UI/WBP_Soldiers.WBP_Soldiers_C")    -- ע��·��
        local SoldierSubUI = NewObject(SoldierSubUIClass, self);
        self.SoldierList:AddChild(SoldierSubUI);
        SoldierSubUI:InitInfo(SoldierInfoList[i].SoldierClass);   -- ��ʼ��һ�±��ֵ���ʽ
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

--function WBP_PlaceAI:Initialize(Initializer)
--end

--function WBP_PlaceAI:PreConstruct(IsDesignTime)
--end

--function WBP_PlaceAI:Tick(MyGeometry, InDeltaTime)
--end

return WBP_PlaceAI